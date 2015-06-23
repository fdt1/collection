/*
 *  lazy_internal_ModifierImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_Implementation.h"
#include "lazy_internal_IModifier.h"
#include "lazy_internal_Generic.h"
#include "lazy_internal_Bridge.h"


namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ValueTemplate, typename AssociateTemplate>
		class ModifierImplementation : 
		public virtual InterfaceTemplate,
		public virtual Implementation
		{
			typedef IModifier<ValueTemplate, AssociateTemplate> IModifier;
		protected:
			Generic& _modified;
		public:
			ModifierImplementation(const Generic& modified) : _modified(modified) {}
		public:
			// --- interface of Generic ---
		/*	virtual const IGeneric& getBridgeToGeneric() const { return *this; }
			virtual IGeneric& getBridgeToGeneric() { return *this; }
			virtual void setBridgeToGeneric(const IGeneric& generic) {  }
		 */
		public:
			// --- interface of IGeneric ---
			virtual bool isValid() const { return true; }
		public:
			// Implementation
			virtual ModifierImplementation* duplicate() const { return new ModifierImplementation(*this); }
		public:
			virtual void setModified(const Generic& modified) {
				if (IModifier* modifier = dynamic_cast<IModifier*> (&_modified)) {
					modifier->setModified(modified);
				} else {
					_modified = modified;
				}
			}
		public:
			// --- interface of IIterator ---
			virtual size_t incrementAt(size_t index) = 0;			
			virtual size_t countToEnd() const = 0;			
			virtual Bridge getImmediate() const = 0;
			virtual Bridge getEnd() const = 0;
			virtual ValueTemplate getValuePrimeType() const = 0;
			virtual AssociateTemplate getAssociatePrimeType() const = 0;
			
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy