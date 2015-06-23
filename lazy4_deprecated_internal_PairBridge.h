/*
 *  lazy4_internal_PairBridge.h
 *  Pair
 *
 *  Created by Francois et Fabienne on 17/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IPair.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Pair wraps an implementation of a forward Pair.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class PairBridge :
		public Bridge<IPair<first_template, second_template> >
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::ref_type ref_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
		public:
			typedef typename internal::IPair<first_template, second_template> IEmbeddedPair;
			typedef typename internal::Bridge<IEmbeddedPair> Bridge;
		public:
			typedef IEmbeddedPair interface_type;
			
		public:
			PairBridge() {}
			
			PairBridge(const IEmbeddedPair* implementation) : Bridge(implementation) {}
			
			PairBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline PairBridge& operator= (const IEmbeddedPair* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const PairBridge& cast(const lazy4::Pair<first_template, second_template>& pair) { return pair; }
			
			//! for compatibility
			static inline PairBridge& cast(lazy4::Pair<first_template, second_template>& pair) { return pair; }
			
			//! for compatibility
			static inline const PairBridge& cast(const PairBridge& pair) { return pair; }
			
			//! for compatibility
			static inline PairBridge& cast(PairBridge& pair) { return pair; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedPair* pair = Bridge::getImplementation()) return pair->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedPair* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedPair* clone() const { if (const IEmbeddedPair* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline ref_first_type getFirst() { return FirstUtility::getFirst(*this); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_ref_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline ref_second_type getSecond() { return SecondUtility::getSecond(*this); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_ref_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
		};	
		
	} // namespace internal
	
	
} // namespace lazy4
