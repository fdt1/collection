/*
 *  lazy3_internal_PairAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IPair.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnFirst is a subdivision implementation of IPair.
		//! it is dedicated on first_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class PairAbstractBridgeOnFirst : 
		public virtual IBridge, 
		public virtual IPairOnFirst<first_type> 
		{
			typedef typename internal::Value<first_type>::template_type template_first_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
		public:
			typedef IPairOnFirst<first_type> IPairOnFirst;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnFirst* getIPairOnFirst() const { return dynamic_cast<IPairOnFirst*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnFirst* getUniqueIPairOnFirst() { return dynamic_cast<IPairOnFirst*> (getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual template_first_type getFirst()  { return this->getIPairOnFirst()->getConstFirst(); }
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return this->getIPairOnFirst()->getConstFirst(); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnFirst is a subdivision implementation of IPair.
		//! it is dedicated on first_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename prime_first_type>
		class PairAbstractBridgeOnFirst<prime_first_type&> : 
		public virtual IBridge, 
		public virtual IPairOnFirst<prime_first_type&> 
		{
			typedef prime_first_type& first_type;
			typedef typename internal::Value<first_type>::template_type template_first_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
		public:
			typedef IPairOnFirst<first_type> IPairOnFirst;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnFirst* getIPairOnFirst() const { return dynamic_cast<IPairOnFirst*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnFirst* getUniqueIPairOnFirst() { return dynamic_cast<IPairOnFirst*> (getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual template_first_type getFirst()  { return this->getUniqueIPairOnFirst()->getFirst(); }
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return this->getIPairOnFirst()->getConstFirst(); }
		};
		
#if 1
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnFirst is a subdivision implementation of IPair.
		//! The current definition is specialization on void type
		//! that disables concerned methods.
		//--------------------------------------------------------------------------------
		template<>
		class PairAbstractBridgeOnFirst<void> : 
		public virtual IBridge, 
		public virtual IPairOnFirst<void> 
		{
		public:
			typedef void first_type;
			typedef IPairOnFirst<first_type> IPairOnFirst;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnFirst* getIPairOnFirst() const { return dynamic_cast<IPairOnFirst*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnFirst* getUniqueIPairOnFirst() { return dynamic_cast<IPairOnFirst*> (getUniqueImplementation()); } 
		};
#endif
		
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnSecond is a subdivision implementation of IPair.
		//! it is dedicated on second_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class PairAbstractBridgeOnSecond : 
		public virtual IBridge, 
		public virtual IPairOnSecond<second_type> 
		{
			typedef typename internal::Value<second_type>::template_type template_second_type;
			typedef typename internal::Value<second_type>::const_type const_second_type;
		public:
			typedef IPairOnSecond<second_type> IPairOnSecond;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnSecond* getIPairOnSecond() const { return dynamic_cast<IPairOnSecond*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnSecond* getUniqueIPairOnSecond() { return dynamic_cast<IPairOnSecond*> (getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual template_second_type getSecond() { return this->getIPairOnSecond()->getConstSecond(); }
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return this->getIPairOnSecond()->getConstSecond(); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnSecond is a subdivision implementation of IPair.
		//! it is dedicated on second_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename prime_second_type>
		class PairAbstractBridgeOnSecond<prime_second_type&> : 
		public virtual IBridge, 
		public virtual IPairOnSecond<prime_second_type&> 
		{
			typedef prime_second_type& second_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
			typedef typename internal::Value<second_type>::const_type const_second_type;
		public:
			typedef IPairOnSecond<second_type> IPairOnSecond;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnSecond* getIPairOnSecond() const { return dynamic_cast<IPairOnSecond*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnSecond* getUniqueIPairOnSecond() { return dynamic_cast<IPairOnSecond*> (getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual template_second_type getSecond() { return this->getUniqueIPairOnSecond()->getSecond(); }
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return this->getIPairOnSecond()->getConstSecond(); }
		};
		
#if 1
		//--------------------------------------------------------------------------------
		//! @class PairAbstractBridgeOnSecond is a subdivision implementation of IPair.
		//! The current defintion is specialization on void type
		//! that disables concerned methods.
		//--------------------------------------------------------------------------------
		template<>
		class PairAbstractBridgeOnSecond<void> : 
		public virtual IBridge, 
		public virtual IPairOnSecond<void> 
		{
		public:
			typedef void second_type;
			typedef IPairOnSecond<second_type> IPairOnSecond;
		public:
			//! @return the current implementation nested in the Bridge
			const IPairOnSecond* getIPairOnSecond() const { return dynamic_cast<IPairOnSecond*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPairOnSecond* getUniqueIPairOnSecond() { return dynamic_cast<IPairOnSecond*> (getUniqueImplementation()); } 
		};
#endif
		
		//--------------------------------------------------------------------------------
		//! @class Pair wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class PairAbstractBridge :
		public virtual IPair<first_type, second_type>,
		public virtual PairAbstractBridgeOnFirst<first_type>,
		public virtual PairAbstractBridgeOnSecond<second_type>
		{
		public:
			typedef IPair<first_type, second_type> IPair;
		public:
			//! @return the current implementation nested in the Bridge
			const IPair* getIPair() const { return dynamic_cast<IPair*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPair* getUniqueIPair() { return dynamic_cast<IPair*> (this->getUniqueImplementation()); } 
		};
#else
		//--------------------------------------------------------------------------------
		//! @class Pair wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class PairAbstractBridge :
		public virtual IPair<first_type, second_type>, 
		public virtual IBridge
		{
		public:
			typedef IPair<first_type, second_type> IPair;
			typedef typename internal::Value<first_type>::template_type template_first_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
			typedef typename internal::Value<second_type>::const_type const_second_type;
		public:
			//! @return the current implementation nested in the Bridge
			const IPair* getIPair() const { return dynamic_cast<IPair*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPair* getUniqueIPair() { return dynamic_cast<IPair*> (this->getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual template_first_type getFirst()  { return this->getUniqueIPair()->getFirst(); }
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return this->getIPair()->getConstFirst(); }			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual template_second_type getSecond() { return this->getUniqueIPair()->getSecond(); }
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return this->getIPair()->getConstSecond(); }
		};
		
#endif
		
		
	} // namespace internal
	
	
} // namespace lazy2
