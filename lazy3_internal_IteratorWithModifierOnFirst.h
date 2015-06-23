/*
 *  lazy3_internal_IteratorWithModifierOnFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IteratorAbstractBridge.h"
#include "lazy3_internal_IteratorBridge.h"
#include "lazy3_internal_ModifierBridge.h"
#include "lazy3_internal_IIterator.h"

namespace lazy3 {
	
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithModifierOnPrime is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename new_first_type, typename second_type, typename container_type>
		class IteratorWithModifierOnFirst : 
		public virtual IIterator<new_first_type, second_type, container_type>,
		public IteratorBridge<void, second_type, container_type>
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef ModifierBridge<old_first_type, new_first_type> ModifierBridge;
			typedef ModifierAbstractBridge<old_first_type, new_first_type> ModifierAbstractBridge;
			typedef IteratorBridge<void, second_type, container_type> IteratorBridge;
#if !defined(VALUE_VOID)
			typedef IPairOnFirst<old_first_type> ICurrentPairOnFirst;
#else
			typedef IPair<old_first_type, second_type> ICurrentPairOnFirst;
#endif
			typedef IteratorAbstractBridge<old_first_type, second_type, container_type> OldIteratorAbstractBridge;
		public:
			ModifierBridge _modifier;
		public:
			IteratorWithModifierOnFirst(const OldIteratorAbstractBridge& Iterator, const ModifierAbstractBridge& modifier) 
			: IteratorBridge(Iterator), _modifier(modifier) {}
		public:
			//! @return the current implementation nested in the Bridge
			const ICurrentPairOnFirst* getICurrentPairOnFirst() const { return dynamic_cast<ICurrentPairOnFirst*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			ICurrentPairOnFirst* getUniqueICurrentPairOnFirst() { return dynamic_cast<ICurrentPairOnFirst*> (this->getUniqueImplementation()); } 
			//! @href lazy3::internal::IIteratorOnFirst::getFirst
			virtual new_first_type getFirst()  { return _modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
			//! @href lazy3::internal::IIteratorOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return const_cast<IteratorWithModifierOnFirst*> (this)->_modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
