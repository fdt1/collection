/*
 *  lazy4_internal_PairWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/02/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

/*
 *  lazy4_internal_PairWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 04/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
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
		//! @class PairWithStaticCast is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, 
		typename old_first_template, typename old_second_template>
		class PairWithStaticCast : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			
		public:
			typedef typename internal::PairBridge<old_first_template, old_second_template> PairBridge;
			
		public:
			PairBridge _bridge;
			
		public:
			PairWithStaticCast(const PairBridge& bridge) : _bridge(bridge) {}
			
			PairWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithStaticCast* clone() const { return new PairWithStaticCast(*this); }
						
		public: // IPair
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
