/*
 *  lazy3_internal_ContentAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_GenericAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class ContentAbstractBridge base for all lazy objects that have a content.
		//--------------------------------------------------------------------------------
		template<typename content_type>
		class ContentAbstractBridge :
		public virtual IContent<content_type>, 
		public virtual GenericAbstractBridge
		{
		public:
			typedef IContent<content_type> IContent;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
			
		public:
			//! @return the current implementation nested in the Bridge
			const IContent* getIContent() const { return dynamic_cast<IContent*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IContent* getUniqueIContent()  { return dynamic_cast<IContent*> (getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getUniqueContent() { return this->getUniqueIContent()->getUniqueContent(); }
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() const { return this->getIContent()->getContent(); }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return this->getIContent()->getConstContent(); }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_content_type setContent(parameter_content_type content) { return this->getUniqueIContent()->setContent(content); }
		};
		
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class ContentAbstractBridge specialization.
		//--------------------------------------------------------------------------------
		template<>
		class ContentAbstractBridge<void> :
		public virtual IContent<void>,
		public virtual GenericAbstractBridge
		{
		public:
			typedef void content_type;
			typedef IContent<content_type> IContent;
			
		public:
			//! @return the current implementation nested in the Bridge
			IContent* getIContent() const { return dynamic_cast<IContent*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IContent* getUniqueIContent()  { return dynamic_cast<IContent*> (getUniqueImplementation()); } 			
		};
#endif
			
	} // namespace internal
	
	
} // namespace lazy3
