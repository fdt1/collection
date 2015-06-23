/*
 *  lazy4_Flow.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Flow.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template>
	class Pair;
		
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void, typename container_template = void>
	class Flow :
	protected internal::FlowBridge<first_template, second_template, container_template>
	{
		friend class internal::FlowBridge<first_template, second_template, container_template>;
	public:
		typedef typename std::forward_iterator_tag iterator_category;
		typedef typename std::ptrdiff_t                  difference_type;
		typedef typename internal::Type<first_template>::type  value_type;
		typedef typename internal::Type<first_template>::ref_type reference;
		typedef typename internal::Type<first_template>::pointer_type pointer;
		
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
		typedef typename internal::FlowBridge<first_template, second_template, container_template> Bridge;
		typedef typename internal::IFlow<first_template, second_template, container_template> Implementation;
		
	public:
		typedef lazy4::Flow<const_template_first_type, const_template_second_type, const_template_container_type> ConstFlow;
		typedef lazy4::Modifier<Flow, container_template, container_template> Modifier;
		typedef lazy4::Modifier<ConstFlow, const_template_container_type, const_template_container_type> ConstModifier;
		typedef lazy4::Pair<const_template_first_type, const_template_second_type> ConstPair;
		typedef lazy4::Pair<first_template, second_template> Pair;
		typedef lazy4::Flow<typename internal::NestedType<first_template>::first_type, typename internal::NestedType<first_template>::second_type, container_template> NestedFlow;
		
	protected:
		typedef typename internal::Flow<first_template, second_template, container_template> FlowWithContent;
		typedef typename internal::ModifierWithStaticCast<Flow, container_template, container_template, Bridge> ModifierWithStaticCast;
		typedef typename internal::FlowWithBounds<first_template, second_template, container_template> FlowWithBounds;
		
	public:
		//! default constructor
		Flow() : Bridge(new FlowWithContent()) {}
		
		//! constructor with a container
		Flow(parameter_container_type container) : Bridge(new FlowWithContent(container)) {}
		
		//! constructor with bounds
		Flow(const Flow& begin, const Flow& end) : Bridge(new FlowWithBounds(Flow::Bridge::cast(begin), Flow::Bridge::cast(end))) {}
		
		//! internal constructor
		Flow(Implementation* implementation) : Bridge(implementation) {}
		
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		Flow(const Flow<any_first_template, any_second_template, any_container_template>& anyFlow)
		: Bridge(new internal::FlowWithStaticCast<first_template, second_template, container_template, 
				 any_first_template, any_second_template, any_container_template>(Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow))) {}		 
		
	public:
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		ConstModifier modifier() const { return ConstModifier(modifier()); }
		
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		Modifier modifier() { return Modifier(new ModifierWithStaticCast(*this), true, true); }
		
		//! @return the current pointed pair
		Pair pair() { return Bridge::clone(); }
		
		//! @return the current pointed pair
		ConstPair pair() const { Pair pair = Bridge::clone(); return ConstPair(pair); }
		
	public:
		//! @return the validity of the current Iterator. 
		bool good() const { return Bridge::good(); }
		
		//! @return the validity of the current Iterator. 
		bool eof() const { return Bridge::eof(); }
		
		//! @return the position of the current iterator. 
		size_t distance() const { return Bridge::distance(); }
		
	public:
		
		//! @return the first_type value
		first_type first() { return Bridge::getFirst(); }
		
		//! @return the first_type value
		const_first_type first() const { return Bridge::getConstFirst(); }
		
		//! @return the second_type value
		second_type second() { return Bridge::getSecond(); }
		
		//! @return the second_type value
		const_second_type second() const { return Bridge::getConstSecond(); }
		
		//! @return the prime container
		const_ref_container_type container() const { return Bridge::getConstContent(); }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return true if the wanted element has been met.
		bool find_first(const_ref_first_type first) { return Bridge::find_first(first); }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return true if the wanted element has been met.
		bool find_second(const_ref_second_type second) { return Bridge::find_second(second); }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return true if the wanted element has been met.
		bool find(const_ref_first_type first, const_ref_second_type second) { return Bridge::find(first, second); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator Flow<first_template> () { return new internal::FlowWithStaticCast<first_template, void, void, first_template, second_template, container_template>(*this); }
		
		//! cast operator which converts in a more agnostic type
		operator Flow<first_template, second_template> () const { return new internal::FlowWithStaticCast<first_template, second_template, void, first_template, second_template, container_template>(*this); }
		
		//! @return the first_type value
		first_type operator* () { return Bridge::getFirst(); }
		
		//! @return the first_type value
		const_first_type operator* () const { return Bridge::getConstFirst(); }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return a new iterator set to the new position.
		Flow operator+ (int steps) const { Implementation* implementation = Bridge::clone(); if (steps < 0) implementation->forward((size_t) steps); else implementation->backward((size_t) -steps); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return the current iterator set to the new position.
		Flow& operator+= (int steps) { if (steps < 0) Bridge::forward((size_t) steps); else Bridge::backward((size_t) -steps); return *this; }
		
		//! move forward the current iterator 
		//! @return the current iterator set to the new position.
		Flow& operator++ () { Bridge::forward(1); return *this; }
		
		//! move forward the current iterator 
		//! @return a new iterator set to the previous position.
		Flow operator++ (int) { Implementation* implementation = Bridge::clone(); Bridge::forward(1); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return a new iterator set to the new position.
		Flow operator- (int steps) const { Implementation* implementation = Bridge::clone(); if (steps < 0) implementation->backward((size_t) steps); else implementation->forward((size_t) -steps); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return the current iterator set to the new position.
		Flow& operator-= (int steps) { if (steps < 0) Bridge::backward((size_t) steps); else Bridge::forward((size_t) -steps); return *this; }
		
		//! move backward the current iterator 
		//! @return the current iterator set to the new position.
		Flow& operator-- () { Bridge::backward(1); return *this; }
		
		//! move backward the current iterator 
		//! @return a new iterator set to the previous position.
		Flow operator-- (int) { Implementation* implementation = Bridge::clone(); Bridge::backward(1); return implementation; }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator== (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() == Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator!= (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() != Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator< (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() < Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator<= (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() <= Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator> (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() > Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator>= (const Flow<any_first_template, any_second_template, any_container_template>& anyFlow) const { return Bridge::where() >= Flow<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyFlow).where(); }
		
		//! @return an iterator on the concatenation of the two lists. 
		template <typename other_container_template>
		Flow<first_template, second_template, lazy4::Pair<typename internal::Type<container_template>::ref_type, typename internal::Type<other_container_template>::ref_type> >
		operator+ (const Flow<first_template, second_template, other_container_template>& anyFlow) const { 
			return new internal::FlowWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, Flow<first_template, second_template, other_container_template>::Bridge::cast(anyFlow));
		}
		
	public:
		//! @return an Iterator with first and secon swapped.
		Flow<second_template, first_template, container_template> permute() const { return new internal::FlowWithPermutation<second_template, first_template, container_template> (*this); }
		
		//! @return a copy of the current iterator with only unique occurrence for first member 
		Flow unique_first() const { return new internal::FlowWithFirstUnique<first_template, second_template, container_template> (*this); }
		
		//! @return a new Iterator flatten on the first value.
		NestedFlow flatten_first() const { 
			return new internal::FlowWithFirstFlatten<first_template, second_template, container_template>(*this);
		}
		
		//! @return a new Iterator modified on the first value.
		//! a dynamic_cast is proceeded on each first value. if it fails it is removed from the iterator.
		template<typename new_first_template>
		Flow<new_first_template, second_template, container_template> 
		dynamic_cast_first() const { 
			return new internal::FlowWithFirstDynamicCast<new_first_template, second_template, container_template, first_template>(*this);
		}
		
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename new_first_template, typename closure_template>
		Flow<new_first_template, second_template, container_template> 
		change_first(const lazy4::Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::FlowWithFirstAccessor<new_first_template, second_template, container_template, first_template, closure_template>(*this, lazy4::Modifier<new_first_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename new_second_template, typename closure_template>
		Flow<first_template, new_second_template, container_template> 
		change_second(const lazy4::Modifier<new_second_template, second_template, closure_template>& modifier) const { 
			return new internal::FlowWithSecondAccessor<first_template, new_second_template, container_template, second_template, closure_template>(*this, lazy4::Modifier<new_second_template, second_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Iterator modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Iterator.
		template<typename filter_template, typename closure_template>
		Flow
		filter_first(const lazy4::Modifier<filter_template, first_template, closure_template>& modifier) const { 
			return new internal::FlowWithFirstFilter<first_template, second_template, container_template, filter_template, closure_template>(*this, lazy4::Modifier<filter_template, first_template, closure_template>::Bridge::cast(modifier));
		}		
	};
	
	template <typename first_template>
	static inline Flow<first_template> make_flow(const first_template& first) { 
		typedef typename internal::Flow<first_template, void, void> FlowWithContent;
		return new FlowWithContent(first); 
	}
	
	template <typename first_template, typename second_template>
	static inline Flow<first_template, second_template> make_flow(const first_template& first, const second_template& second) { 
		typedef typename internal::Flow<first_template, second_template, void> FlowWithContent;
		return new FlowWithContent(first, second); 
	}

	
} // namespace lazy4

//! add a displacement to the current iterator 
//! @param steps number of elements to skip
//! @return a new iterator set to the new position.
template <typename first_template, typename second_template, typename container_template>
static inline lazy4::Flow<first_template, second_template, container_template>
operator+ (int steps, const lazy4::Flow<first_template, second_template, container_template>& flow) { return flow + steps; }


