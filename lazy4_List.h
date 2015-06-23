/*
 *  lazy4_List.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_List.h"
#include "lazy4_Collection.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Index;
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
		
	//--------------------------------------------------------------------------------
	//! @class List is a forward List.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void, typename container_template = void>
	class List :
	protected internal::ListBridge<first_template, second_template, container_template>
	{
		friend class internal::ListBridge<first_template, second_template, container_template>;
		
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
		typedef typename internal::IList<first_template, second_template, container_template> Implementation;
		typedef typename internal::ListBridge<first_template, second_template, container_template> Bridge;
		
	public:
		typedef lazy4::List<const_first_type, const_second_type, const_container_type> ConstList;
		typedef lazy4::Index<const_template_first_type, const_template_second_type, const_template_container_type> ConstIndex;
		typedef lazy4::Index<first_template, second_template, container_template> Index;
		typedef lazy4::Collection<typename internal::NestedType<first_template>::first_type, typename internal::NestedType<first_template>::second_type, container_template> NestedCollection;
		typedef lazy4::Modifier<List, container_template, container_template> Modifier;
		typedef lazy4::Modifier<ConstList, const_template_container_type, const_template_container_type> ConstModifier;
		
	protected:
		typedef typename internal::List<first_template, second_template, container_template> ListWithContent;
		typedef typename internal::ListWithBounds<first_template, second_template, container_template> ListWithBounds;
		typedef typename internal::IList<first_template, second_template, container_template> IList;
		typedef typename internal::IIndex<first_template, second_template, container_template> IIndex;
		typedef typename internal::IModifier<IList*, container_template, container_template> IModifier;
		typedef typename internal::ModifierWithStaticCast<List, container_template, container_template, Bridge> ModifierWithStaticCast;		
		
	protected:
	public:
		//! default constructor
		List() : Bridge(new ListWithContent()) {}
		
		//! constructor with bounds
		List(const Index& begin, const Index& end) : Bridge(new ListWithBounds(Index::Bridge::cast(begin), Index::Bridge::cast(end))) {}
		
		//! constructor with a container
		List(parameter_container_type container) : Bridge(new ListWithContent(container)) {}

		//! constructor that convert into other templates
		template <typename inherited_list_template>
		List(const inherited_list_template& anyList)
		: Bridge(new internal::ListWithInheritance<first_template, second_template, container_template, inherited_list_template>(anyList)) {}
	
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		List(const List<any_first_template, any_second_template, any_container_template>& anyList)
		: Bridge(new internal::ListWithStaticCast<first_template, second_template, container_template, 
				 any_first_template, any_second_template, any_container_template>(List<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyList))) {}
		
		//! internal constructor
		template <typename Implementation>
		List(Implementation* implementation) : Bridge(implementation) {}	
		
	public:
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		ConstModifier modifier() const { return ConstModifier(modifier()); }
		
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		Modifier modifier() { return Modifier(new ModifierWithStaticCast(*this), true, true); }
		
		//! @return the corresponding Index set at the beginning.
		Index begin() { return Bridge::cloneIndex(); }
		
		//! @return the corresponding Index set at the beginning.
		ConstIndex begin() const { Index it = Bridge::cloneIndex(); return ConstIndex(it); }
		
		//! @return the corresponding Index set at the beginning.
		Index end() { Index it = begin(); it.flush(); return it; }
		
		//! @return the corresponding Index set at the beginning.
		ConstIndex end() const { Index it = begin(); it.flush(); return ConstIndex(it); }
		
		//! @return the corresponding Index set at the beginning.
		Index rbegin() { Index it = begin(); it.flush(); return it.reverse(); }
		
		//! @return the corresponding Index set at the beginning.
		ConstIndex rbegin() const { Index it = begin(); it.flush(); return ConstIndex(it.reverse()); }
		
		//! @return the corresponding Index set at the beginning.
		Index rend() { Index it = begin(); return it.reverse(); }
		
		//! @return the corresponding Index set at the beginning.
		ConstIndex rend() const { Index it = begin(); return ConstIndex(it.reverse()); }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Index set at the beginning.
		Index find_first(const_ref_first_type first) { Index it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		Index rfind_first(const_ref_first_type first) { Index it = rbegin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Index set at the beginning.
		ConstIndex find_first(const_ref_first_type first) const { Index it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		ConstIndex rfind_first(const_ref_first_type first) const { Index it = rbegin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return the corresponding Index set at the beginning.
		Index find_second(const_ref_second_type second) { Index it = begin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		Index rfind_second(const_ref_second_type second) { Index it = rbegin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return the corresponding Index set at the beginning.
		ConstIndex find_second(const_ref_second_type second) const { Index it = begin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of second in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		ConstIndex rfind_second(const_ref_second_type second) const { Index it = rbegin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Index set at the beginning.
		Index find(const_ref_first_type first, const_ref_second_type second) { Index it = begin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		Index rfind(const_ref_first_type first, const_ref_second_type second) { Index it = rbegin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Index set at the beginning.
		ConstIndex find(const_ref_first_type first, const_ref_second_type second) const { Index it = begin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair in the reverse order from the current step.
		//! @return the corresponding reverse Index set at the beginning.
		ConstIndex rfind(const_ref_first_type first, const_ref_second_type second) const { Index it = rbegin(); it.find(first, second); return it; }
		
	public:		
		//! @return the size of the current List. 
		size_t size() const { return Bridge::size(); }
		
		//! @return the emptyness of the current List. 
		bool empty() const { return Bridge::empty(); }
		
		//! @return the validity of the current List. 
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
		
		//! @return true if an occurrence of first exists in the current list.
		bool exist_first(const_ref_first_type first) const { return Bridge::exist_first(first); }
		
		//! @return true if an occurrence of second exists in the current list.
		bool exist_second(const_ref_second_type second) const { return Bridge::exist_second(second); }
		
		//! @return true if an occurrence of second exists in the current list.
		bool exist(const_ref_first_type first, const_ref_second_type second) const { return Bridge::exist(first, second); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator List<first_template> () { return new internal::ListWithStaticCast<first_template, void, void, first_template, second_template, container_template>(*this); }
		
		//! cast operator which converts in a more agnostic type
		operator List<first_template, second_template> () const { return new internal::ListWithStaticCast<first_template, second_template, void, first_template, second_template, container_template>(*this); }
		
	public:
		//! @return a copy of the current list with only unique occurrence for first member 
		Collection<first_template, second_template, container_template> unique_first() const { return new internal::CollectionWithFirstUnique<first_template, second_template, container_template> (*this); }
		
		//! @return a reverse copy of the current list. 
		List reverse() const { return new internal::ListWithReverse<first_template, second_template, container_template> (*this); }
		
		//! @return a list with first and second swapped. 
		List<second_template, first_template, container_template> permute() const { return new internal::ListWithPermutation<second_template, first_template, container_template> (*this); }
		
		//! @return a new Index flatten on the first value.
		NestedCollection flatten_first() const { 
			return new internal::CollectionWithFirstFlatten<first_template, second_template, container_template>(*this);
		}
		
		//! compare two lists
		//! @return true if they contains the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator== (const Collection<any_first_template, any_second_template, any_container_template>& anyList) const { 
			typedef typename Collection<any_first_template, any_second_template, any_container_template>::Bridge AnyListBridge;
			typedef typename internal::IIndex<any_first_template, any_second_template, any_container_template> IAnyIndex;			
			const AnyListBridge& anyListBridge =  AnyListBridge::cast(anyList);
			if (!anyListBridge.good()) {
				return !Bridge::good();
			} else if (!Bridge::good()) {
				return false;
			}
			
			IAnyIndex* it2 = anyListBridge.cloneIndex();
			IIndex* it = Bridge::cloneIndex();
			
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
		
		//! compare two lists
		//! @return true if they don't contain the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator!= (const Collection<any_first_template, any_second_template, any_container_template>& anyList) const { return !operator==(anyList); }		
		
		//! @return a collection of the concatenation of the two collections.
		template <typename other_container_template>
		Collection<first_template, second_template, Pair<typename internal::Type<container_template>::ref_type, typename internal::Type<other_container_template>::ref_type> > 
		operator+ (const Collection<first_template, second_template, other_container_template>& collection) const { 
			return new internal::CollectionWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, List<first_template, second_template, other_container_template>::Bridge::cast(collection));
		}
		
		//! @return a new List modified on the first value.
		//! a dynamic_cast is proceeded on each first value. if it fails it is removed from the collection.
		template<typename new_first_template>
		Collection<new_first_template, second_template, container_template> 
		dynamic_cast_first() const { 
			return new internal::CollectionWithFirstDynamicCast<new_first_template, second_template, container_template, first_template>(*this);
		}
		
	public:
		//! @return a new List modified on the first value.
		//! @param modifier the modifier will change the first typed values of the List.
		template<typename new_first_template, typename closure_template>
		Collection<new_first_template, second_template, container_template> 
		change_first(const lazy4::Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::CollectionWithFirstAccessor<new_first_template, second_template, container_template, first_template, closure_template>(*this, lazy4::Modifier<new_first_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new List modified on the first value.
		//! @param modifier the modifier will change the first typed values of the List.
		template<typename new_second_template, typename closure_template>
		Collection<first_template, new_second_template, container_template> 
		change_second(const lazy4::Modifier<new_second_template, second_template, closure_template>& modifier) const { 
			return new internal::CollectionWithSecondAccessor<first_template, new_second_template, container_template, second_template, closure_template>(*this, lazy4::Modifier<new_second_template, second_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new List modified on the first value.
		//! @param modifier the modifier will change the first typed values of the List.
		template<typename filter_template, typename closure_template>
		Collection<first_template, second_template, container_template> 
		filter_first(const lazy4::Modifier<filter_template, first_template, closure_template>& modifier) const { 
			return new internal::CollectionWithFirstFilter<first_template, second_template, container_template, filter_template, closure_template>(*this, lazy4::Modifier<filter_template, first_template, closure_template>::Bridge::cast(modifier));
		}
				
	};
	
	template <typename first_template>
	static inline List<first_template> make_list(const first_template& first) { 
		typedef typename internal::List<first_template, void, void> ListWithContent;
		return new ListWithContent(first); 
	}
	
	template <typename first_template, typename second_template>
	static inline List<first_template, second_template> make_list(const first_template& first, const second_template& second) { 
		typedef typename internal::List<first_template, second_template, void> ListWithContent;
		return new ListWithContent(first, second); 
	}
	
	
} // namespace lazy4

