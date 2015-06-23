/*
 *  lazy4_internal_ContentBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 15/01/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IContent.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_ContentUtility.h"


namespace lazy4 {
	
	template <typename content_template>
	class Content;
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Content wraps an implementation of a forward Content.
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class ContentBridge :
		public Bridge<IContent<content_template> >
		{
		public:
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
		public:
			typedef typename internal::IContent<content_template> IEmbeddedContent;
			typedef typename internal::Bridge<IEmbeddedContent> Bridge;
		public:
			typedef IEmbeddedContent interface_type;
			
		public:
			ContentBridge() {}
			
			ContentBridge(const IEmbeddedContent* implementation) : Bridge(implementation) {}
			
			ContentBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline ContentBridge& operator= (const IEmbeddedContent* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const ContentBridge& cast(const lazy4::Content<content_template>& Content) { return Content; }
			
			//! for compatibility
			static inline ContentBridge& cast(lazy4::Content<content_template>& Content) { return Content; }
			
			//! for compatibility
			static inline const ContentBridge& cast(const ContentBridge& Content) { return Content; }
			
			//! for compatibility
			static inline ContentBridge& cast(ContentBridge& Content) { return Content; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedContent* Content = Bridge::getImplementation()) return Content->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedContent* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedContent* clone() const { if (const IEmbeddedContent* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
		public:
			//! @href lazy3::internal::IContentOncontent::content
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContentOncontent::content
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
						
		};	
		
	} // namespace internal
	
	
} // namespace lazy4
