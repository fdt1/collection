/*
 *  lazy4_internal_PairWithPermutation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/02/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IPair.h"
#include "lazy4_internal_PairBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"

namespace lazy4 {
	
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class PairWithPermutation is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template>
		class PairWithPermutation : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<second_template> FirstUtility;
			typedef typename internal::SecondUtility<first_template> SecondUtility;
			
		public:
			typedef typename internal::PairBridge<second_template, first_template> PairBridge;
			
		public:
			PairBridge _bridge;
			
		public:
			PairWithPermutation(const PairBridge& bridge) : _bridge(bridge) {}
			
			PairWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithPermutation* clone() const { return new PairWithPermutation(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return SecondUtility::getConstSecond(_bridge); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return FirstUtility::getConstFirst(_bridge); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
