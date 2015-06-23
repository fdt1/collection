/*
 *  lazy3_internal_PairBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_PairAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class PairBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class PairBridge :
		public Bridge,
		public virtual PairAbstractBridge<first_type, second_type>
		{
			typedef PairAbstractBridge<first_type, second_type> PairAbstractBridge;
		public:
			PairBridge() {}
			PairBridge(const PairAbstractBridge& Pair) : Bridge(Pair) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairBridge specialization.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class PairBridge<void, second_type> :
		public Bridge,
		public virtual PairAbstractBridge<void, second_type>
		{
		public:
			PairBridge() {}
			template<typename any_first_type>
			PairBridge(const PairAbstractBridge<any_first_type, second_type>& Pair) : Bridge(Pair) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairBridge specialization.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class PairBridge<first_type, void> :
		public Bridge,
		public virtual PairAbstractBridge<first_type, void>
		{
		public:
			PairBridge() {}
			template<typename any_second_type>
			PairBridge(const PairAbstractBridge<first_type, any_second_type>& Pair) : Bridge(Pair) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairBridge specialization.
		//--------------------------------------------------------------------------------
		template<>
		class PairBridge<void, void> :
		public Bridge,
		public virtual PairAbstractBridge<void, void>
		{
		public:
			PairBridge() {}
			template<typename any_first_type, typename any_second_type>
			PairBridge(const IPair<any_first_type, any_second_type>& Pair) : Bridge(Pair) {}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
Accessor