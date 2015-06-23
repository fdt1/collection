/*
 *  lazy4_internal_PairWithFirstAccessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/02/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_IPair.h"
#include "lazy4_internal_ModifierBridge.h"
#include "lazy4_internal_PairBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_FunctorUtility.h"


namespace lazy4 {
	
	namespace internal {
				
		//--------------------------------------------------------------------------------
		//! @class PairWithStaticCast is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename old_first_template, typename closure_template>
		class PairWithFirstAccessor :
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			
		public:
			typedef typename internal::PairBridge<old_first_template, second_template> PairBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			PairBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			PairWithFirstAccessor(const PairBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _modifier.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithFirstAccessor* clone() const { return new PairWithFirstAccessor(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
