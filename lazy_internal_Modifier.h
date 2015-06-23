/*
 *  lazy_internal_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_IModifier.h"
#include "lazy_internal_Iterator.h"
#include "lazy_internal_IGeneric.h"


namespace lazy {
	
	namespace internal {
		
		//! adapter of interface IModifier
		template <typename ValueTemplate, typename AssociateTemplate>
		class Modifier : 
		public virtual IModifier<ValueTemplate, AssociateTemplate>,
		public virtual Iterator<ValueTemplate, AssociateTemplate>,
		public virtual Generic
		{
		protected:
			typedef IModifier<ValueTemplate, AssociateTemplate> IModifier;
		public:
			const IModifier& getBridgeToModifier() const { return dynamic_cast<const IModifier&> (getBridgeToGeneric()); }
			IModifier& getBridgeToModifier() { return dynamic_cast<IModifier&> (getBridgeToGeneric()); }
		public:
			// --- interface of IModifier ---
			virtual IGeneric& getModified() { return getBridgeToModifier().getModified(); }		
			virtual const IGeneric& getModified() const { return getBridgeToModifier().getModified(); }			
			virtual void setModified(const IGeneric& modified) { getBridgeToModifier().setModified(modified); }			
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy