/*
 *  lazy3_internal_ModifierWithLink.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ModifierBridge.h"
#include "lazy3_internal_IModifier.h"

namespace lazy3 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class ModifierWithLink is an implementation of a modifier to overwrite the 
		//! return type value.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename renew_type>
		class ModifierWithLink : 
		public virtual IModifier<old_type, renew_type>,
		public ModifierBridge<old_type, void>
		{
			typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
			typedef ModifierAbstractBridge<old_type, new_type> CurrentModifierAbstractBridge;
			typedef IModifier<old_type, new_type> ICurrentModifier;
			typedef ModifierAbstractBridge<new_type, renew_type> LinkModifierAbstractBridge;
			typedef ModifierBridge<new_type, renew_type> LinkModifierBridge;
		public:
			LinkModifierBridge _modifier;
		public:
			ModifierWithLink(const CurrentModifierAbstractBridge& current, const LinkModifierAbstractBridge& link) 
			: ModifierBridge<old_type, void>(current), _modifier(link) {}
		public:
			//! @return the current implementation nested in the Bridge
			ICurrentModifier* getICurrentModifier() const { return dynamic_cast<ICurrentModifier*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			ICurrentModifier* getUniqueICurrentModifier() { return dynamic_cast<ICurrentModifier*> (this->getUniqueImplementation()); } 
			//! @href lazy3::internal::IFlowOnFirst::change
			virtual renew_type change(parameter_old_type old_value)  { new_type elem = getICurrentModifier()->change(old_value); return _modifier.change(elem); }
		};		
	
	} // namespace internal
	
	
} // namespace lazy2
