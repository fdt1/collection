/*
 *  lazy3_internal_ModifierAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_GenericAbstractBridge.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class ModifierAbstractBridge is the wrapper for a Modifier.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type>
		class ModifierAbstractBridge :
		public virtual IModifier<old_type, new_type>,
		public virtual GenericAbstractBridge
		{
			typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
			typedef IModifier<old_type, new_type> IModifier;
		public:
			//! @return the current implementation nested in the Bridge
			const IModifier* getIModifier() const { return dynamic_cast<IModifier*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IModifier* getUniqueIModifier() { return dynamic_cast<IModifier*> (getUniqueImplementation()); } 
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual new_type change(parameter_old_type old_value) { return getUniqueIModifier()->change(old_value); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierAbstractBridge is a specialization.
		//--------------------------------------------------------------------------------
		template<typename old_type>
		class ModifierAbstractBridge<old_type, void> :
		public virtual IModifier<old_type, void>,
		public virtual GenericAbstractBridge
		{
			typedef void new_type;
			typedef IModifier<old_type, new_type> IModifier;
		public:
			//! @return the current implementation nested in the Bridge
			const IModifier* getIModifier() const { return dynamic_cast<IModifier*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IModifier* getUniqueIModifier() { return dynamic_cast<IModifier*> (getUniqueImplementation()); } 
		public:
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierAbstractBridge is a specialization.
		//--------------------------------------------------------------------------------
		template<typename new_type>
		class ModifierAbstractBridge<void, new_type> :
		public virtual IModifier<void, new_type>,
		public virtual GenericAbstractBridge
		{
			typedef void old_type;
			typedef IModifier<old_type, new_type> IModifier;
		public:
			//! @return the current implementation nested in the Bridge
			const IModifier* getIModifier() const { return dynamic_cast<IModifier*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IModifier* getUniqueIModifier() { return dynamic_cast<IModifier*> (getUniqueImplementation()); } 
		public:
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierAbstractBridge is a specialization.
		//--------------------------------------------------------------------------------
		template<>
		class ModifierAbstractBridge<void, void> :
		public virtual IModifier<void, void>,
		public virtual GenericAbstractBridge
		{
			typedef void new_type;
			typedef void old_type;
			typedef IModifier<old_type, new_type> IModifier;
		public:
			//! @return the current implementation nested in the Bridge
			const IModifier* getIModifier() const { return dynamic_cast<IModifier*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IModifier* getUniqueIModifier() { return dynamic_cast<IModifier*> (getUniqueImplementation()); } 
		public:
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
