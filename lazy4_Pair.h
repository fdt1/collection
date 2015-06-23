/*
 *  lazy4_Pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Pair.h"


namespace lazy4 {
	
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
	
	//--------------------------------------------------------------------------------
	//! @class Pair is a forward Pair.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_template = void, typename second_template = void>
	class Pair :
	protected internal::PairBridge<first_template, second_template>
	{
		friend class internal::PairBridge<first_template, second_template>;
		
	public:
		typedef typename internal::Type<first_template>::type first_type;
		typedef typename internal::Type<first_template>::ref_type ref_first_type;
		typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
		typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
		typedef typename internal::Type<second_template>::type second_type;
		typedef typename internal::Type<second_template>::ref_type ref_second_type;
		typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
		typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
		
	public:
		typedef typename internal::IPair<first_template, second_template> Implementation;
		typedef typename internal::PairBridge<first_template, second_template> Bridge;
		typedef typename internal::PairWithContent<first_template, second_template> PairWithContent;
		
	public:
		//! default constructor // FIXME
		Pair() /*: Bridge(new PairWithContent())*/ {}
		
		//! constructor with a container
		Pair(parameter_first_type first, parameter_second_type second) : Bridge(new PairWithContent(first, second)) {}
		
		//! internal constructor
		Pair(Implementation* implementation) : Bridge(implementation) {}
		
		//! constructor that convert into other templates
		template <typename any_first_template, typename any_second_template>
		Pair(const Pair<any_first_template, any_second_template>& anyPair)
		: Bridge(new internal::PairWithStaticCast<first_template, second_template, 
						   any_first_template, any_second_template>(Pair<any_first_template, any_second_template>::Bridge::cast(anyPair))) {}
		
	public:
		//! @return the validity of the current Pair. 
		bool good() const { return Bridge::good(); }
		
		//! @return the first_type value
		ref_first_type first() { return Bridge::getFirst(); }
		
		//! @return the first_type value
		const_ref_first_type first() const { return Bridge::getConstFirst(); }
		
		//! @return the second_type value
		ref_second_type second() { return Bridge::getSecond(); }
		
		//! @return the second_type value
		const_ref_second_type second() const { return Bridge::getConstSecond(); }
		
	public:
		//! @return a pair with first and second swapped.
		Pair<second_template, first_template> permute() const { return new internal::PairWithPermutation<second_template, first_template> (*this); }
		
	public:
		//! cast operator which converts in a more agnostic type
		operator Pair<first_template> () const { return new internal::PairWithStaticCast<first_template, void, first_template, second_template>(*this); }
				
		
#if 0 // FIXME : TODO
	public:
#ifdef NO_ERROR_CONCAT
		//! @return a Pair of the concatenation of the two Pairs. 
		Pair operator+ (const Pair& Pair) const { return new internal::PairWithConcatenation<first_template, second_template, container_template> (*this, Pair.__bridge()); }
#elif 0
		//! @return a Pair of the concatenation of the two Pairs.
		template <typename other_container_template>
		Pair<first_template, second_template, std::pair<Pair, Pair<first_template, second_template, other_container_template> > > 
		operator+ (const Pair<first_template, second_template, other_container_template>& Pair) const { 
			return new internal::PairWithConcatenation<first_template, second_template, container_template, other_container_template> (*this, Pair.__bridge());
		}
#else
		//! @return a Pair of the concatenation of the two Pairs.
		template <typename other_container_template>
		Pair<first_template, second_template, std::pair<Pair, Pair<first_template, second_template, other_container_template> > > 
		operator+ (const Pair<first_template, second_template, other_container_template>& Pair) const { 
			return new internal::PairWithConcatenation<first_template, second_template, Pair, Pair<first_template, second_template, other_container_template> > (*this, Pair);
		}
#endif
#endif
		//! compare two collections
		//! @return true if they contains the same data 
		template <typename any_first_template, typename any_second_template>
		bool operator== (const Pair<any_first_template, any_second_template>& anyPair) const { 
			typedef typename Pair<any_first_template, any_second_template>::Bridge AnyPairBridge;
			const AnyPairBridge& anyPairBridge =  AnyPairBridge::cast(anyPair);
			if (!anyPairBridge.good()) {
				return !Bridge::good();
			} else if (!Bridge::good()) {
				return false;
			}			
			return Bridge::getConstFirst() == anyPairBridge.getConstFirst() && Bridge::getConstSecond() == anyPairBridge.getConstSecond();
		}
		
		//! compare two collections
		//! @return true if they don't contain the same data 
		template <typename any_first_template, typename any_second_template>
		bool operator!= (const Pair<any_first_template, any_second_template>& anyPair) const { return !operator==(anyPair); }		
		
		
	public:
		//! @return a new Pair modified on the first value.
		//! @param modifier the modifier will change the first typed values of the Pair.
		template<typename new_first_template, typename closure_template>
		Pair<new_first_template, second_template> 
		change_first(const Modifier<new_first_template, first_template, closure_template>& modifier) const { 
			return new internal::PairWithFirstAccessor<new_first_template, second_template, first_template, closure_template>(*this, modifier.__bridge());
		}
		
		
	};
	
	
} // namespace lazy4

