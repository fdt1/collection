/*
 *  lazy4_Index.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Index.h"
#include "lazy4_Iterator.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class List;
	
	template <typename first_template, typename second_template, typename container_template>
	class Flow;
	
	template <typename first_template, typename second_template>
	class Pair;
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
	
	
	//--------------------------------------------------------------------------------
	//! @class Index is a bidirectional iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void, typename container_template = void>
	class Index :
	protected internal::IndexBridge<first_template, second_template, container_template>
	{
		friend class internal::IndexBridge<first_template, second_template, container_template>;
		friend class List<first_template, second_template, container_template>;
	public:
		typedef typename std::bidirectional_iterator_tag iterator_category;
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
		typedef typename internal::IndexBridge<first_template, second_template, container_template> Bridge;
		typedef typename internal::IIndex<first_template, second_template, container_template> Implementation;
		
	public:
		typedef lazy4::Index<const_template_first_type, const_template_second_type, const_template_container_type> ConstIndex;
		typedef lazy4::List<const_template_first_type, const_template_second_type, const_template_container_type> ConstList;
		typedef lazy4::List<first_template, second_template, container_template> List;
		typedef lazy4::Modifier<Index, container_template, container_template> Modifier;
		typedef lazy4::Modifier<ConstIndex, const_template_container_type, const_template_container_type> ConstModifier;
		typedef lazy4::Pair<const_template_first_type, const_template_second_type> ConstPair;
		typedef lazy4::Pair<first_template, second_template> Pair;
		typedef lazy4::Flow<const_template_first_type, const_template_second_type, const_template_container_type> ConstFlow;
		typedef lazy4::Flow<first_template, second_template, container_template> Flow;
		typedef lazy4::Iterator<typename internal::NestedType<first_template>::first_type, typename internal::NestedType<first_template>::second_type, container_template> NestedIterator;
		
	protected:
		typedef typename internal::Index<first_template, second_template, container_template> IndexWithContent;
		typedef typename internal::ModifierWithStaticCast<Index, container_template, container_template, Bridge> ModifierWithStaticCast;
		typedef typename internal::IndexWithBounds<first_template, second_template, container_template> IndexWithBounds;
	
	public:
		//! default constructor
		Index() : Bridge(new IndexWithContent()) {}
		
		//! constructor with a container
		Index(parameter_container_type container) : Bridge(new IndexWithContent(container)) {}
		
		//! constructor with bounds
		Index(const Index& begin, const Index& end) : Bridge(new IndexWithBounds(Index::Bridge::cast(begin), Index::Bridge::cast(end))) {}
		
		//! constructor that convert into other templates
		template <typename inherited_iterator_template>
		Index(const inherited_iterator_template& anyIndex)
		: Bridge(new internal::IndexWithInheritance<first_template, second_template, container_template, inherited_iterator_template>(anyIndex)) {}
		
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		Index(const Index<any_first_template, any_second_template, any_container_template>& anyIndex)
		: Bridge(new internal::IndexWithStaticCast<first_template, second_template, container_template, 
				 any_first_template, any_second_template, any_container_template>(Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex))) {}		 
		
		//! internal constructor
		template <typename Implementation>
		Index(Implementation* implementation) : Bridge(implementation) {}
		
	public:
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		ConstModifier modifier() const { return ConstModifier(modifier()); }
		
		//! @return the corresponding modifier that afords to change any container into this kind of iterator
		Modifier modifier() { return Modifier(new ModifierWithStaticCast(*this), true, true); }
		
		//! @return the corresponding collection
		List collection() { return Bridge::cloneList(); }
		
		//! @return the corresponding collection
		ConstList collection() const { List collection = Bridge::cloneList(); return ConstList(collection); }
		
		//! @return the current pointed pair
		Pair pair() { return Bridge::clone(); }
		
		//! @return the current pointed pair
		ConstPair pair() const { Pair new_pair = Bridge::clone(); return ConstPair(new_pair); }
		
		//! @return the current pointed pair
		Flow flow() { return Bridge::clone(); }
		
		//! @return the current pointed pair
		ConstFlow flow() const { Flow new_flow = flow(); return ConstFlow(new_flow); }
		
	public:
		//! @return the validity of the current Index. 
		bool good() const { return Bridge::good(); }
		
		//! @return the validity of the current Index. 
		bool top() const { return Bridge::top(); }
		
		//! @return the validity of the current Index. 
		bool eof() const { return Bridge::eof(); }
		
		//! @return the position of the current iterator. 
		size_t distance() const { return Bridge::distance(); }
		
		//! @return the number of elements until the end.
		size_t remains() const { return Bridge::remains(); }
		
		//! @return the number of elements until the end.
		void flush() { return Bridge::flush(); }
		
		//! @return the number of elements until the end.
		void rewind() { return Bridge::rewind(); }
		
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
		
		//! @return the prime container
		ref_container_type container() { return Bridge::getContent(); }
		
		//! set the iterator to the primary occurrence of first from the current step.
		//! @return true if the wanted element has been met.
		bool find_first(const_ref_first_type first) { return Bridge::find_first(first); }
		
		//! set the iterator to the primary occurrence of first in the reverse order from the current step.
		//! @return true if the wanted element has been met.
		bool rfind_first(const_ref_first_type first) { return Bridge::rfind_first(first); }
		
		//! set the iterator to the primary occurrence of second from the current step.
		//! @return true if the wanted element has been met.
		bool find_second(const_ref_second_type second) { return Bridge::find_second(second); }
		
		//! set the iterator to the primary occurrence of second in the reverse order from the current step.
		//! @return true if the wanted element has been met.
		bool rfind_second(const_ref_second_type second) { return Bridge::rfind_second(second); }
		
		//! set the iterator to the primary occurrence of pair from the current step.
		//! @return true if the wanted element has been met.
		bool find(const_ref_first_type first, const_ref_second_type second) { return Bridge::find(first, second); }
		
		//! set the iterator to the primary occurrence of pair in the reverse order from the current step.
		//! @return true if the wanted element has been met.
		bool rfind(const_ref_first_type first, const_ref_second_type second) { return Bridge::rfind(first, second); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator Index<first_template> () { return new internal::IndexWithStaticCast<first_template, void, void, first_template, second_template, container_template>(*this); }
		
		//! cast operator which converts in a more agnostic type
		operator Index<first_template, second_template> () const { return new internal::IndexWithStaticCast<first_template, second_template, void, first_template, second_template, container_template>(*this); }
		
		//! @return the first_type value
		first_type operator* () { return first(); }
		
		//! @return the first_type value
		const_first_type operator* () const { return first(); }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return a new iterator set to the new position.
		Index operator+ (long long steps) const { Implementation* implementation = Bridge::clone(); if (steps < 0) implementation->forward((size_t) steps); else implementation->backward((size_t) -steps); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return the current iterator set to the new position.
		Index& operator+= (long long steps) { if (steps < 0) Bridge::forward((size_t) steps); else Bridge::backward((size_t) -steps); return *this; }
		
		//! move forward the current iterator 
		//! @return the current iterator set to the new position.
		Index& operator++ () { Bridge::forward(1); return *this; }
		
		//! move forward the current iterator 
		//! @return a new iterator set to the previous position.
		Index operator++ (int) { Implementation* implementation = Bridge::clone(); Bridge::forward(1); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return a new iterator set to the new position.
		Index operator- (long long steps) const { Implementation* implementation = Bridge::clone(); if (steps < 0) implementation->backward((size_t) steps); else implementation->forward((size_t) -steps); return implementation; }
		
		//! add a displacement to the current iterator 
		//! @param steps number of elements to skip
		//! @return the current iterator set to the new position.
		Index& operator-= (long long steps) { if (steps < 0) Bridge::backward((size_t) steps); else Bridge::forward((size_t) -steps); return *this; }
		
		//! move backward the current iterator 
		//! @return the current iterator set to the new position.
		Index& operator-- () { Bridge::backward(1); return *this; }
		
		//! move backward the current iterator 
		//! @return a new iterator set to the previous position.
		Index operator-- (int) { Implementation* implementation = Bridge::clone(); Bridge::backward(1); return implementation; }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator== (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() == Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator!= (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() != Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }

		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator< (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() < Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator<= (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() <= Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator> (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() > Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }
		
		//! compare two iterators of a same container
		//! @return true if they point on the same data 
		template <typename any_first_template, typename any_second_template, typename any_container_template>
		bool operator>= (const Iterator<any_first_template, any_second_template, any_container_template>& anyIndex) const { return Bridge::where() >= Index<any_first_template, any_second_template, any_container_template>::Bridge::cast(anyIndex).where(); }
	/*	
		//! fill element and increment the iterator.
		//! @param pair element to fill.
		//! @return itself. 
		Index& operator>> (Pair& pair) { pair = *this; Bridge::forward(1); return *this; }
		
		//! fill element and increment the iterator.
		//! @param pair element to fill.
		//! @return itself. 
		Index& operator>> (Pair& pair) { pair = *this; Bridge::forward(1); return *this; }
	 */
		
		//! @return an iterator on the concatenation of the two lists. 
		template <typename other_container_template>
		Iterator<first_template, second_template, lazy4::Pair<typename internal::Type<container_template>::ref_type, typename internal::Type<other_container_template>::ref_type> >
		operator+ (const Iterator<first_template, second_template, other_container_template>& iterator) const { 
			return new internal::IteratorWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, Index<first_template, second_template, other_container_template>::Bridge::cast(iterator));
		}
		
	public:
		//! @return a reversed copy of the current iterator. 
		Index reverse() const { return new internal::IndexWithReverse<first_template, second_template, container_template> (*this); }
		
		//! @return an Index with first and secon swapped.
		Index<second_template, first_template, container_template> permute() const { return new internal::IndexWithPermutation<second_template, first_template, container_template> (*this); }
		
		//! @return a copy of the current iterator with only unique occurrence for first member 
		Iterator<first_template, second_template, container_template> unique_first() const { return new internal::IteratorWithFirstUnique<first_template, second_template, container_template> (*this); }
		
		//! @return a new Index flatten on the first value.
		NestedIterator flatten_first() const { 
			return new internal::IteratorWithFirstFlatten<first_template, second_template, container_template>(*this);
		}

		//! @return a new Index modified on the first value.
		//! a dynamic_cast is proceeded on each first value. if it fails it is removed from the iterator.
		template<typename new_first_template>
		Iterator<new_first_template, second_template, container_template> 
		dynamic_cast_first() const { 
			return new internal::IteratorWithFirstDynamicCast<new_first_template, second_template, container_template, first_template>(*this);
		}
		
		//! @return a new Index modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Index.
		template<typename new_first_template, typename closure_template>
		Iterator<new_first_template, second_template, container_template> 
		change_first(const lazy4::Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::IteratorWithFirstAccessor<new_first_template, second_template, container_template, first_template, closure_template>(*this, lazy4::Modifier<new_first_template, first_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Index modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Index.
		template<typename new_second_template, typename closure_template>
		Iterator<first_template, new_second_template, container_template> 
		change_second(const lazy4::Modifier<new_second_template, second_template, closure_template>& modifier) const { 
			return new internal::IteratorWithSecondAccessor<first_template, new_second_template, container_template, second_template, closure_template>(*this, lazy4::Modifier<new_second_template, second_template, closure_template>::Bridge::cast(modifier));
		}
		
		//! @return a new Index modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Index.
		template<typename filter_template, typename closure_template>
		Iterator<first_template, second_template, container_template>
		filter_first(const lazy4::Modifier<filter_template, first_template, closure_template>& modifier) const { 
			return new internal::IteratorWithFirstFilter<first_template, second_template, container_template, filter_template, closure_template>(*this, lazy4::Modifier<filter_template, first_template, closure_template>::Bridge::cast(modifier));
		}		
	};

	template <typename first_template>
	static inline Index<first_template> make_index(const first_template& first) { 
		typedef typename internal::Index<first_template, void, void> IndexWithContent;
		return new IndexWithContent(first); 
	}
	
	template <typename first_template, typename second_template>
	static inline Index<first_template, second_template> make_index(const first_template& first, const second_template& second) { 
		typedef typename internal::Index<first_template, second_template, void> IndexWithContent;
		return new IndexWithContent(first, second); 
	}
	
} // namespace lazy4


//! add a displacement to the current iterator 
//! @param steps number of elements to skip
//! @return a new iterator set to the new position.
template <typename first_template, typename second_template, typename container_template>
static inline lazy4::Index<first_template, second_template, container_template> 
operator+ (int steps, const lazy4::Index<first_template, second_template, container_template>& iterator) { return iterator + steps; }



