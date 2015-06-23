/*
 *  lazy4_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Collection.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Iterator;
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
		
	//--------------------------------------------------------------------------------
	//! @class Collection is a forward Collection.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void, typename container_template = void>
	class Collection :
	protected internal::CollectionBridge<first_template, second_template, container_template>
	{
		friend class internal::CollectionBridge<first_template, second_template, container_template>;
		
	public:
		typedef typename internal::Type<first_template>::type first_type;
		typedef typename internal::Type<first_template>::const_type const_first_type;
		typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
		typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
		typedef typename internal::Type<first_template>::const_template_type const_template_first_type;
		typedef typename internal::Type<second_template>::type second_type;
		typedef typename internal::Type<second_template>::const_type const_second_type;
		typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
		typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
		typedef typename internal::Type<second_template>::const_template_type const_template_second_type;
		typedef typename internal::Type<container_template>::type container_type;
		typedef typename internal::Type<container_template>::ref_type ref_container_type;
		typedef typename internal::Type<container_template>::const_type const_container_type;
		typedef typename internal::Type<container_template>::const_ref_type const_ref_container_type;
		typedef typename internal::Type<container_template>::parameter_type parameter_container_type;
		typedef typename internal::Type<container_template>::const_template_type const_template_container_type;

	public:
		typedef typename internal::ICollection<first_template, second_template, container_template> Implementation;
		typedef typename internal::CollectionBridge<first_template, second_template, container_template> Bridge;
		
	public:
		typedef lazy4::Collection<const_first_type, const_second_type, const_container_type> ConstCollection;
		typedef lazy4::Iterator<const_template_first_type, const_template_second_type, const_template_container_type> ConstIterator;
		typedef lazy4::Iterator<first_template, second_template, container_template> Iterator;
		typedef lazy4::Collection<typename internal::NestedType<first_template>::first_type, typename internal::NestedType<first_template>::second_type, container_template> NestedCollection;
		typedef lazy4::Modifier<Collection, container_template, container_template> Modifier;
		typedef lazy4::Modifier<ConstCollection, const_template_container_type, const_template_container_type> ConstModifier;
		
	protected:
		typedef typename internal::Collection<first_template, second_template, container_template> CollectionWithContent;
		typedef typename internal::CollectionWithBounds<first_template, second_template, container_template> CollectionWithBounds;
		typedef typename internal::ICollection<first_template, second_template, container_template> ICollection;
		typedef typename internal::IIterator<first_template, second_template, container_template> IIterator;
		typedef typename internal::IModifier<ICollection*, container_template, container_template> IModifier;
		typedef typename internal::ModifierWithStaticCast<Collection, container_template, container_template, Bridge> ModifierWithStaticCast;		
		
	protected:
	public:
		//! default constructor
		Collection() : Bridge(new CollectionWithContent()) {}
		
		//! constructor with bounds
		Collection(const Iterator& begin, const Iterator& end) : Bridge(new CollectionWithBounds(Iterator::Bridge::cast(begin), Iterator::Bridge::cast(end))) {}
		
		//! constructor with a container
		Collection(parameter_container_type container) : Bridge(new CollectionWithContent(container)) {}

		//! constructor that convert into other templates
		template <typename inherited_collection_template>
		Collection(const inherited_collection_template& anyCollection)
		: Bridge(new internal::CollectionWithInheritance<first_template, second_template, container_template, inherited_collection_template>(anyCollection)) {}
	
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		Collection(const Collection<any_first_template, any_second_template, any_container_template>& anyCollection)
		: Bridge(new internal::CollectionWithStaticCast<first_template, second_template, container_template, 
				 any_first_template, any_second_template, any_container_template>(Collection<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyCollection))) {}
		
		//! internal constructor
		template <typename Implementation>
		Collection(Implementation* implementation) : Bridge(implementation) {}	
		
	public:
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		ConstModifier modifier() const { return ConstModifier(modifier()); }
		
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		Modifier modifier() { return Modifier(new ModifierWithStaticCast(*this), true, true); }
		
		//! @return the corresponding Iterator set at the beginning.
		Iterator begin() { return Bridge::cloneIterator(); }
		
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator begin() const { Iterator it = Bridge::cloneIterator(); return ConstIterator(it); }
		
		//! @return the corresponding Iterator set at the beginning.
		Iterator end() { Iterator it = begin(); it.flush(); return it; }
		
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator end() const { Iterator it = begin(); it.flush(); return ConstIterator(it); }
		
		//! @return the corresponding Iterator set at the beginning.
		Iterator rbegin() { Iterator it = begin(); it.flush(); return it.reverse(); }
		
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator rbegin() const { Iterator it = begin(); it.flush(); return ConstIterator(it.reverse()); }
		
		//! @return the corresponding Iterator set at the beginning.
		Iterator rend() { Iterator it = begin(); return it.reverse(); }
		
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator rend() const { Iterator it = begin(); return ConstIterator(it.reverse()); }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Iterator set at the beginning.
		Iterator find_first(const_ref_first_type first) { Iterator it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		Iterator rfind_first(const_ref_first_type first) { Iterator it = rbegin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator find_first(const_ref_first_type first) const { Iterator it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		ConstIterator rfind_first(const_ref_first_type first) const { Iterator it = rbegin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return the corresponding Iterator set at the beginning.
		Iterator find_second(const_ref_second_type second) { Iterator it = begin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		Iterator rfind_second(const_ref_second_type second) { Iterator it = rbegin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator find_second(const_ref_second_type second) const { Iterator it = begin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		ConstIterator rfind_second(const_ref_second_type second) const { Iterator it = rbegin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Iterator set at the beginning.
		Iterator find(const_ref_first_type first, const_ref_second_type second) { Iterator it = begin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		Iterator rfind(const_ref_first_type first, const_ref_second_type second) { Iterator it = rbegin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Iterator set at the beginning.
		ConstIterator find(const_ref_first_type first, const_ref_second_type second) const { Iterator it = begin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair in the reverse order from the current step.
		//! @return the corresponding reverse Iterator set at the beginning.
		ConstIterator rfind(const_ref_first_type first, const_ref_second_type second) const { Iterator it = rbegin(); it.find(first, second); return it; }
		
	public:		
		//! @return the size of the current Collection. 
		size_t size() const { return Bridge::size(); }
		
		//! @return the emptyness of the current Collection. 
		bool empty() const { return Bridge::empty(); }
		
		//! @return the validity of the current Collection. 
		bool good() const { return Bridge::good(); }
		
		//! @return the first_type value
		first_type at_first(size_t steps) { return Bridge::getFirstWithThrow(steps); }
		
		//! @return the first_type value
		const_first_type at_first(size_t steps) const { return Bridge::getConstFirstWithThrow(steps); }
		
		//! @return the second_type value
		second_type at_second(size_t steps) { return Bridge::getSecondWithThrow(steps); }
		
		//! @return the second_type value
		const_second_type at_second(size_t steps) const { return Bridge::getConstSecondWithThrow(steps); }
		
		//! @return the first_type value
		first_type first(size_t steps) { return Bridge::getFirst(steps); }
		
		//! @return the first_type value
		const_first_type first(size_t steps) const { return Bridge::getConstFirst(steps); }
		
		//! @return the second_type value
		second_type second(size_t steps) { return Bridge::getSecond(steps); }
		
		//! @return the second_type value
		const_second_type second(size_t steps) const { return Bridge::getConstSecond(steps); }
		
		//! @return the prime container
		const_ref_container_type container() const { return Bridge::getConstContent(); }
		
		//! @return the prime container
		ref_container_type container() { return Bridge::getContent(); }
		
		//! @return true if an occurrence of first exists in the current collection.
		bool exist_first(const_ref_first_type first) const { return Bridge::exist_first(first); }
		
		//! @return true if an occurrence of second exists in the current collection.
		bool exist_second(const_ref_second_type second) const { return Bridge::exist_second(second); }
		
		//! @return true if an occurrence of second exists in the current collection.
		bool exist(const_ref_first_type first, const_ref_second_type second) const { return Bridge::exist(first, second); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator Collection<first_template> () { return new internal::CollectionWithStaticCast<first_template, void, void, first_template, second_template, container_template>(*this); }
		
		//! cast operator which converts in a more agnostic type
		operator Collection<first_template, second_template> () const { return new internal::CollectionWithStaticCast<first_template, second_template, void, first_template, second_template, container_template>(*this); }
		
	public:
		//! @return a copy of the current collection with only unique occurrence for first member 
		Collection unique_first() const { return new internal::CollectionWithFirstUnique<first_template, second_template, container_template> (*this); }
		
		//! @return a reverse copy of the current collection. 
		Collection reverse() const { return new internal::CollectionWithReverse<first_template, second_template, container_template> (*this); }
		
		//! @return a collection with first and second swapped. 
		Collection<second_template, first_template, container_template> permute() const { return new internal::CollectionWithPermutation<second_template, first_template, container_template> (*this); }
		
		//! @return a new Iterator flatten on the first value.
		NestedCollection flatten_first() const { 
			return new internal::CollectionWithFirstFlatten<first_template, second_template, container_template>(*this);
		}
		
		//! compare two collections
		//! @return true if they contains the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator== (const Collection<any_first_template, any_second_template, any_container_template>& anyCollection) const { 
			typedef typename Collection<any_first_template, any_second_template, any_container_template>::Bridge AnyCollectionBridge;
			typedef typename internal::IIterator<any_first_template, any_second_template, any_container_template> IAnyIterator;			
			const AnyCollectionBridge& anyCollectionBridge =  AnyCollectionBridge::cast(anyCollection);
			if (!anyCollectionBridge.good()) {
				return !Bridge::good();
			} else if (!Bridge::good()) {
				return false;
			}
			
			IAnyIterator* it2 = anyCollectionBridge.cloneIterator();
			IIterator* it = Bridge::cloneIterator();
			
			for (; !it->eof(); it->forward(1)) {
				if (it2->eof() || it->getConstFirst() != it2->getConstFirst() || it->getConstSecond() != it2->getConstSecond()) {
					delete it;
					delete it2;
					return false;
				}
				it2->forward(1);
			}
			
			bool isEqual = it2->eof();
			delete it;
			delete it2;
			return isEqual;
		}
		
		//! compare two collections
		//! @return true if they don't contain the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator!= (const Collection<any_first_template, any_second_template, any_container_template>& anyCollection) const { return !operator==(anyCollection); }		
		
		//! @return a collection of the concatenation of the two collections.
		template <typename other_container_template>
		Collection<first_template, second_template, Pair<typename internal::Type<container_template>::ref_type, typename internal::Type<other_container_template>::ref_type> > 
		operator+ (const Collection<first_template, second_template, other_container_template>& collection) const { 
			return new internal::CollectionWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, Collection<first_template, second_template, other_container_template>::Bridge::cast(collection));
		}
		
		//! @return a new Collection modified on the first value.
		//! a dynamic_cast is proceeded on each first value. if it fails it is removed from the collection.
		template<typename new_first_template>
		Collection<new_first_template, second_template, container_template> 
		dynamic_cast_first() const { 
			return new internal::CollectionWithFirstDynamicCast<new_first_template, second_template, container_template, first_template>(*this);
		}
		
	public:
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename new_first_template, typename closure_template>
		Collection<new_first_template, second_template, container_template> 
		change_first(const lazy4::Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::CollectionWithFirstAccessor<new_first_template, second_template, container_template, first_template, closure_template>(*this, lazy4::Modifier<new_first_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename new_second_template, typename closure_template>
		Collection<first_template, new_second_template, container_template> 
		change_second(const lazy4::Modifier<new_second_template, second_template, closure_template>& modifier) const { 
			return new internal::CollectionWithSecondAccessor<first_template, new_second_template, container_template, second_template, closure_template>(*this, lazy4::Modifier<new_second_template, second_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Collection modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Collection.
		template<typename filter_template, typename closure_template>
		Collection<first_template, second_template, container_template> 
		filter_first(const lazy4::Modifier<filter_template, first_template, closure_template>& modifier) const { 
			return new internal::CollectionWithFirstFilter<first_template, second_template, container_template, filter_template, closure_template>(*this, lazy4::Modifier<filter_template, first_template, closure_template>::Bridge::cast(modifier));
		}
				
	};
	
	template <typename first_template>
	static inline Collection<first_template> make_collection(const first_template& first) { 
		typedef typename internal::Collection<first_template, void, void> CollectionWithContent;
		return new CollectionWithContent(first); 
	}
	
	template <typename first_template, typename second_template>
	static inline Collection<first_template, second_template> make_collection(const first_template& first, const second_template& second) { 
		typedef typename internal::Collection<first_template, second_template, void> CollectionWithContent;
		return new CollectionWithContent(first, second); 
	}
	
	
} // namespace lazy4

