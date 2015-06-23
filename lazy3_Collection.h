/*
 *  lazy3_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#pragma once

#include "lazy3_Modifier.h"
#include "lazy3_Accessor.h"
#include "lazy3_Iterator.h"
#include "lazy3_internal_IteratorAbstractBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IteratorWithModifierOnFirst.h"
#include "lazy3_internal_IteratorWithFilterOnFirst.h"
#include "lazy3_internal_IteratorWithStaticCast.h"
#include "lazy3_internal_IteratorElement.h"

namespace lazy3 {
	
	
	
	
	//--------------------------------------------------------------------------------
	//! @class Collection is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_type = void, typename second_type = void, typename container_type = void>
	class Collection :
	public Modifier<container_type, Collection<first_type, second_type, container_type>, internal::IIterator<first_type, second_type, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Collection() : InheritModifier(new IteratorElement()) {}
		Collection(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		Collection(const Collection& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename new_first_type>
		Collection<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Collection filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Collection.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Collection 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename second_type>
	class Collection<first_type, second_type, void> :
	public Modifier<void, Collection<first_type, second_type, void>, internal::IIterator<first_type, second_type, void>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
	public:
		Collection() {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_container_type>
		Collection(const Collection<first_type, second_type, any_container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename new_first_type>
		Collection<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Collection filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Collection.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Collection 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename container_type>
	class Collection<first_type, void, container_type> :
	public Modifier<container_type, Collection<first_type, void, container_type>, internal::IIterator<first_type, void, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Collection, IIterator* > InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Collection() : InheritModifier(new IteratorElement()) {}
		Collection(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_second_type>
		Collection(const Collection<first_type, any_second_type, container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
		//! @return a new Collection modified on the first value.
		template<typename new_first_type>
		Collection<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type, typename container_type>
	class Collection<void, second_type, container_type> :
	public Modifier<container_type, Collection<void, second_type, container_type>, internal::IIterator<void, second_type, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<void, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void first_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Collection() : InheritModifier(new IteratorElement()) {}
		Collection(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_first_type>
		Collection(const Collection<any_first_type, second_type, container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type>
	class Collection<first_type, void, void> :
	public Modifier<void, Collection<first_type, void, void>, internal::IIterator<first_type, void, void>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
		typedef typename internal::Value<first_type>::parameter_type parameter_first_type;
	public:
		Collection() {}
		// FIXME: duplicate this constructor in all Collection without container ..
		//template<typename any_container_type>
		//Collection(const any_container_type& container) : InheritModifier(new internal::IteratorElement<first_type, second_type, any_container_type, Collection<first_type, second_type, any_container_type> >(container)) {}
		
		//FIXME: shall we distribute	this constructor in all classes ?
		Collection(parameter_first_type container) : InheritModifier(new internal::IteratorElement<first_type, second_type, first_type>(container)) {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_second_type, typename any_container_type>
		Collection(const Collection<first_type, any_second_type, any_container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename new_first_type>
		Collection<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Collection filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Collection.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Collection 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type>
	class Collection<void, second_type, void> :
	public Modifier<void, Collection<void, second_type, void>, internal::IIterator<void, second_type, void>* >,
	protected virtual internal::IteratorAbstractBridge<void, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void first_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
	public:
		Collection() {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template<typename any_first_type, typename any_container_type>
		Collection(const Collection<any_first_type, second_type, any_container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <typename container_type>
	class Collection<void, void, container_type> :
	public Modifier<container_type, Collection<void, void, container_type>, internal::IIterator<void, void, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<void, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		typedef void first_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Collection() : InheritModifier(new IteratorElement()) {}
		Collection(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type>
		Collection(const Collection<any_first_type, any_second_type, container_type>& Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Collection))) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Collection specialization.
	//--------------------------------------------------------------------------------
	template <>
	class Collection<void, void, void> :
	public Modifier<void, Collection<void, void, void>, internal::IIterator<void, void, void>* >,
	protected virtual internal::IteratorAbstractBridge<void, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		typedef void first_type;
		typedef Iterator<first_type, second_type, container_type> Iterator;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Collection, IIterator*> InheritModifier;
	public:
		Collection() {}
		Collection(const IIterator* Collection) : InheritModifier(Collection) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Collection(const Collection<any_first_type, any_second_type, any_container_type>& Collection) : InheritModifier(Collection) {}
	public:
		//! @return the iterator on the beginning of the collection
		Iterator begin() { return *this; }
		//! @return the iterator on the beginning of the collection
		Iterator end() { Iterator it = *this; it.flush(); return it; }
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Collection empty
		//! @return the number of elements 
		//! that have been removed from the Collection
		void flush() {  IteratorAbstractBridge::flush(); }
	protected:
		Collection(const Generic& generic) : InheritModifier(generic) {}
	};
	
	
	
} // namespace lazy2
