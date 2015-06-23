/*
 *  lazy4_Query.h
 *  Query
 *
 *  Created by Francois et Fabienne on 17/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Query.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Flow;
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
	
	//--------------------------------------------------------------------------------
	//! @class Query is a forward Query.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void, typename container_template = void>
	class Query :
	protected internal::QueryBridge<first_template, second_template, container_template>
	{
		friend class internal::QueryBridge<first_template, second_template, container_template>;
		
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
		typedef typename internal::IQuery<first_template, second_template, container_template> Implementation;
		typedef typename internal::QueryBridge<first_template, second_template, container_template> Bridge;
		
	public:
		typedef lazy4::Query<const_first_type, const_second_type, const_container_type> ConstQuery;
		typedef lazy4::Flow<const_template_first_type, const_template_second_type, const_template_container_type> ConstFlow;
		typedef lazy4::Flow<first_template, second_template, container_template> Flow;
		typedef lazy4::Query<typename internal::NestedType<first_template>::first_type, typename internal::NestedType<first_template>::second_type, container_template> NestedQuery;
		typedef lazy4::Modifier<Query, container_template, container_template> Modifier;
		typedef lazy4::Modifier<ConstQuery, const_template_container_type, const_template_container_type> ConstModifier;
		
	protected:
		typedef typename internal::Query<first_template, second_template, container_template> QueryWithContent;
		typedef typename internal::QueryWithBounds<first_template, second_template, container_template> QueryWithBounds;
		typedef typename internal::IQuery<first_template, second_template, container_template> IQuery;
		typedef typename internal::IFlow<first_template, second_template, container_template> IFlow;
		typedef typename internal::IModifier<IQuery*, container_template, container_template> IModifier;
		typedef typename internal::ModifierWithStaticCast<Query, container_template, container_template, Bridge> ModifierWithStaticCast;
		
	public:
		//! default constructor
		Query() : Bridge(new QueryWithContent()) {}
		
		//! constructor with a container
		Query(parameter_container_type container) : Bridge(new QueryWithContent(container)) {}
		
		//! constructor with bounds
		Query(const Flow& begin, const Flow& end) : Bridge(new QueryWithBounds(Flow::Bridge::cast(begin), Flow::Bridge::cast(end))) {}
		
		//! internal constructor
		Query(Implementation* implementation) : Bridge(implementation) {}
		
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		Query(const Query<any_first_template, any_second_template, any_container_template>& anyQuery)
		: Bridge(new internal::QueryWithStaticCast<first_template, second_template, container_template, 
				 any_first_template, any_second_template, any_container_template>(Query<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyQuery))) {}
		
	public:
		//! @return the corresponding modifier that afords to change any container into this kind of query
		ConstModifier modifier() const { return ConstModifier(modifier()); }
		
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		Modifier modifier() { return Modifier(new ModifierWithStaticCast(*this), true, true); }
		
		//! @return the corresponding Iterator set at the beginning.
		Flow begin() { return Bridge::cloneFlow(); }
		
		//! @return the corresponding Iterator set at the beginning.
		ConstFlow begin() const { Flow it = Bridge::cloneFlow(); return ConstFlow(it); }
		
		//! @return the corresponding Flow set at the beginning.
		Flow end() { Flow it = Bridge::cloneFlow(); it.flush(); return it; }
		
		//! @return the corresponding Flow set at the beginning.
		ConstFlow end() const { Flow it = Bridge::cloneFlow(); it.flush(); return ConstFlow(it); }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Flow set at the beginning.
		Flow find_first(const_ref_first_type first) { Flow it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return the corresponding Flow set at the beginning.
		ConstFlow find_first(const_ref_first_type first) const { Flow it = begin(); it.find_first(first); return it; }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return the corresponding Flow set at the beginning.
		ConstFlow find_second(const_ref_second_type second) const { Flow it = begin(); it.find_second(second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Flow set at the beginning.
		Flow find(const_ref_first_type first, const_ref_second_type second) { Flow it = begin(); it.find(first, second); return it; }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return the corresponding Flow set at the beginning.
		ConstFlow find(const_ref_first_type first, const_ref_second_type second) const { Flow it = begin(); it.find(first, second); return it; }
		
	public:		
		//! @return the size of the current Query. 
		size_t size() const { return Bridge::size(); }
		
		//! @return the emptyness of the current Query. 
		bool empty() const { return Bridge::empty(); }
		
		//! @return the validity of the current Query. 
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
		
		//! @return true if an occurrence of first exists in the current Query.
		bool exist_first(const_ref_first_type first) const { return Bridge::exist_first(first); }
		
		//! @return true if an occurrence of second exists in the current Query.
		bool exist_second(const_ref_second_type second) const { return Bridge::exist_second(second); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator Query<first_template> () { return new internal::QueryWithStaticCast<first_template, void, void, first_template, second_template, container_template>(*this); }
		
		//! cast operator which converts in a more agnostic type
		operator Query<first_template, second_template> () const { return new internal::QueryWithStaticCast<first_template, second_template, void, first_template, second_template, container_template>(*this); }
		
	public:
		//! @return a copy of the current Query with only unique occurrence for first member 
		Query unique_first() const { return new internal::QueryWithFirstUnique<first_template, second_template, container_template> (*this); }
		
		//! @return a Query with first and second swapped. 
		Query<second_template, first_template, container_template> permute() const { return new internal::QueryWithPermutation<second_template, first_template, container_template> (*this); }
		
		//! @return a new Query flatten on the first value.
		NestedQuery flatten_first() const { 
			return new internal::QueryWithFirstFlatten<first_template, second_template, container_template>(*this);
		}
		
		//! compare two Querys
		//! @return true if they contains the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator== (const Query<any_first_template, any_second_template, any_container_template>& anyQuery) const { 
			typedef typename Query<any_first_template, any_second_template, any_container_template>::Bridge AnyQueryBridge;
			typedef typename internal::IFlow<any_first_template, any_second_template, any_container_template> IAnyFlow;			
			const AnyQueryBridge& anyQueryBridge =  AnyQueryBridge::cast(anyQuery);
			if (!anyQueryBridge.good()) {
				return !Bridge::good();
			} else if (!Bridge::good()) {
				return false;
			}
			
			IAnyFlow* it2 = anyQueryBridge.cloneFlow();
			IFlow* it = Bridge::cloneFlow();
			
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
		
		//! compare two Querys
		//! @return true if they don't contain the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator!= (const Query<any_first_template, any_second_template, any_container_template>& anyQuery) const { return !operator==(anyQuery); }		
		
		//! @return a Query of the concatenation of the two Querys.
		template <typename other_container_template>
		Query<first_template, second_template, Pair<typename internal::Type<container_template>::ref_type, typename internal::Type<other_container_template>::ref_type> > 
		operator+ (const Query<first_template, second_template, other_container_template>& query) const { 
			return new internal::QueryWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, Query<first_template, second_template, other_container_template>::Bridge::cast(query));
		}
		
		//! @return a new Query modified on the first value.
		//! a dynamic_cast is proceeded on each first value. if it fails it is removed from the Query.
		template<typename new_first_template>
		Query<new_first_template, second_template, container_template> 
		dynamic_cast_first() const { 
			return new internal::QueryWithFirstDynamicCast<new_first_template, second_template, container_template, first_template>(*this);
		}
		
	public:
		//! @return a new Query modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Query.
		template<typename new_first_template, typename closure_template>
		Query<new_first_template, second_template, container_template> 
		change_first(const lazy4::Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::QueryWithFirstAccessor<new_first_template, second_template, container_template, first_template, closure_template>(*this, lazy4::Modifier<new_first_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Query modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Query.
		template<typename new_second_template, typename closure_template>
		Query<first_template, new_second_template, container_template> 
		change_second(const lazy4::Modifier<new_second_template, second_template, closure_template>& modifier) const { 
			return new internal::QueryWithSecondAccessor<first_template, new_second_template, container_template, second_template, closure_template>(*this, lazy4::Modifier<new_second_template, second_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Query modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Query.
		template<typename filter_template, typename closure_template>
		Query<first_template, second_template, container_template> 
		filter_first(const lazy4::Modifier<filter_template, first_template, closure_template>& modifier) const { 
			return new internal::QueryWithFirstFilter<first_template, second_template, container_template, filter_template, closure_template>(*this, lazy4::Modifier<filter_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
	};
	
	template <typename first_template>
	static inline Query<first_template> make_query(const first_template& first) { 
		typedef typename internal::Query<first_template, void, void> QueryWithContent;
		return new QueryWithContent(first); 
	}
	
	template <typename first_template, typename second_template>
	static inline Query<first_template, second_template> make_query(const first_template& first, const second_template& second) { 
		typedef typename internal::Query<first_template, second_template, void> QueryWithContent;
		return new QueryWithContent(first, second); 
	}
	
	
} // namespace lazy4

