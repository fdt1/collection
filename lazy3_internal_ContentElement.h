/*
 *  lazy3_internal_ContentElement.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy3_internal_IContent.h"


namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is an implementation of IContent
		//--------------------------------------------------------------------------------
		template<typename content_type>
		class ContentElement : 
		public virtual IContent<content_type>
		{
			typedef typename internal::Value<content_type>::template_type template_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
		public:
			template_content_type _content;
		public:
			ContentElement(parameter_content_type content) : _content(content) {}
			ContentElement() : _content() {}
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() const { return const_cast<ref_content_type> (_content); }
			//! @href lazy3::internal::IContent::getUniqueContent
			virtual ref_content_type getUniqueContent() { return _content; }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_content_type setContent(parameter_content_type content) { _content = content; return _content; }
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new ContentElement(*this); }
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return true; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is a specialization
		//--------------------------------------------------------------------------------
		template<typename content_type>
		class ContentElement<content_type&> : 
		public virtual IContent<content_type&>
		{
			typedef typename internal::Value<content_type>::template_type template_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
		public:
			template_content_type* _content;
		public:
			ContentElement(parameter_content_type content) : _content(&content) {}
			ContentElement() : _content(NULL) {}
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() const { return const_cast<ref_content_type> (*_content); }
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getUniqueContent() { return *_content; }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return *_content; }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_content_type setContent(parameter_content_type content) { _content = &content; return _content; }
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new ContentElement(*this); }
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _content; }
		};
		
				
	} // namespace internal
	
	
} // namespace lazy3
