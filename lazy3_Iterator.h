/*
 *  lazy3_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */




#pragma once

#include "lazy3_Modifier.h"
#include "lazy3_Accessor.h"
#include "lazy3_internal_IteratorAbstractBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IteratorWithModifierOnFirst.h"
#include "lazy3_internal_IteratorWithFilterOnFirst.h"
#include "lazy3_internal_IteratorWithStaticCast.h"
#include "lazy3_internal_IteratorElement.h"

namespace lazy3 {
	
	template <typename first_type, typename second_type, typename container_type>
	class Collection;
	
	
	
	//--------------------------------------------------------------------------------
	//! @class Iterator is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_type = void, typename second_type = void, typename container_type = void>
	class Iterator :
	public Modifier<container_type, Iterator<first_type, second_type, container_type>, internal::IIterator<first_type, second_type, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Iterator() : InheritModifier(new IteratorElement()) {}
		Iterator(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		Iterator(const Iterator& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
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
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename new_first_type>
		Iterator<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Iterator filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Iterator.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Iterator 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename second_type>
	class Iterator<first_type, second_type, void> :
	public Modifier<void, Iterator<first_type, second_type, void>, internal::IIterator<first_type, second_type, void>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
	public:
		Iterator() {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_container_type>
		Iterator(const Iterator<first_type, second_type, any_container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename new_first_type>
		Iterator<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Iterator filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Iterator.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Iterator 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename container_type>
	class Iterator<first_type, void, container_type> :
	public Modifier<container_type, Iterator<first_type, void, container_type>, internal::IIterator<first_type, void, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Iterator, IIterator* > InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Iterator() : InheritModifier(new IteratorElement()) {}
		Iterator(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_second_type>
		Iterator(const Iterator<first_type, any_second_type, container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
		//! @return a new Iterator modified on the first value.
		template<typename new_first_type>
		Iterator<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type, typename container_type>
	class Iterator<void, second_type, container_type> :
	public Modifier<container_type, Iterator<void, second_type, container_type>, internal::IIterator<void, second_type, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<void, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void first_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Iterator() : InheritModifier(new IteratorElement()) {}
		Iterator(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type>
		Iterator(const Iterator<any_first_type, second_type, container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
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
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type>
	class Iterator<first_type, void, void> :
	public Modifier<void, Iterator<first_type, void, void>, internal::IIterator<first_type, void, void>* >,
	protected virtual internal::IteratorAbstractBridge<first_type, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
		typedef typename internal::Value<first_type>::parameter_type parameter_first_type;
	public:
		Iterator() {}
		// FIXME: duplicate this constructor in all Iterator without container ..
		//template<typename any_container_type>
		//Iterator(const any_container_type& container) : InheritModifier(new internal::IteratorElement<first_type, second_type, any_container_type, Iterator<first_type, second_type, any_container_type> >(container)) {}
		
		//FIXME: shall we distribute	this constructor in all classes ?
		Iterator(parameter_first_type container) : InheritModifier(new internal::IteratorElement<first_type, second_type, first_type>(container)) {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_second_type, typename any_container_type>
		Iterator(const Iterator<first_type, any_second_type, any_container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return IteratorAbstractBridge::getFirst(); }
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename new_first_type>
		Iterator<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::IteratorWithModifierOnFirst<first_type, new_first_type, second_type, container_type> IteratorWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new Iterator filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the Iterator.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Iterator 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::IteratorWithFilterOnFirst<first_type, filter_type, second_type, container_type> IteratorWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new IteratorWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type>
	class Iterator<void, second_type, void> :
	public Modifier<void, Iterator<void, second_type, void>, internal::IIterator<void, second_type, void>* >,
	protected virtual internal::IteratorAbstractBridge<void, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void first_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
	public:
		Iterator() {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template<typename any_first_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, second_type, any_container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the second_type value
		second_type second() { return IteratorAbstractBridge::getSecond(); }
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <typename container_type>
	class Iterator<void, void, container_type> :
	public Modifier<container_type, Iterator<void, void, container_type>, internal::IIterator<void, void, container_type>* >,
	protected virtual internal::IteratorAbstractBridge<void, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		typedef void first_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef internal::IteratorElement<first_type, second_type, container_type> IteratorElement;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Iterator() : InheritModifier(new IteratorElement()) {}
		Iterator(parameter_container_type container) : InheritModifier(new IteratorElement(container)) {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type>
		Iterator(const Iterator<any_first_type, any_second_type, container_type>& Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator)
		: InheritModifier(new internal::IteratorWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>&> (Iterator))) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
		//! @return the prime container
		const prime_container_type& container() const { return IteratorAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return IteratorAbstractBridge::setContent(container); }
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Iterator specialization.
	//--------------------------------------------------------------------------------
	template <>
	class Iterator<void, void, void> :
	public Modifier<void, Iterator<void, void, void>, internal::IIterator<void, void, void>* >,
	protected virtual internal::IteratorAbstractBridge<void, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		typedef void first_type;
		friend class Collection<first_type, second_type, container_type>;
		typedef internal::IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
		typedef internal::IIterator<first_type, second_type, container_type> IIterator;
		typedef Modifier<container_type, Iterator, IIterator*> InheritModifier;
	public:
		Iterator() {}
		Iterator(const IIterator* Iterator) : InheritModifier(Iterator) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Iterator(const Iterator<any_first_type, any_second_type, any_container_type>& Iterator) : InheritModifier(Iterator) {}
	public:
		//! @return true if forward succeed
		bool forward() { return IteratorAbstractBridge::forward(1); }
		//! @return true if backward succeed
		bool backward() { return IteratorAbstractBridge::backward(1); }
		//! make the Iterator empty
		//! @return the number of elements 
		//! that have been removed from the Iterator
		void flush() {  IteratorAbstractBridge::flush(); }
	protected:
		Iterator(const Generic& generic) : InheritModifier(generic) {}
	};
	
	
	
} // namespace lazy2


