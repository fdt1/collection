/*
 *  lazy3_internal_AccessorElement.h
 *  collection
 *
 *  Created by Francois et Fabienne on 18/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ContentElement.h"
#include "lazy3_internal_AccessorAdapter.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class AccessorElement is an implementation of IAccessor
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type, typename functor_type>
		class AccessorElement : 
		public AccessorAdapter<old_type, new_type, auxilary_type, functor_type>
		{
			typedef AccessorAdapter<old_type, new_type, auxilary_type, functor_type> AccessorAdapter;
			typedef typename internal::Value<auxilary_type>::ref_type ref_auxilary_type;
			typedef typename internal::Value<auxilary_type>::const_ref_type const_ref_auxilary_type;
			typedef typename internal::Value<auxilary_type>::parameter_type parameter_auxilary_type;
			typedef ContentElement<auxilary_type> AuxilaryBridge;
		public:
			AuxilaryBridge _auxilaryBridge;
		public:
			AccessorElement(const functor_type& functor) : AccessorAdapter(functor) {}
			AccessorElement(const functor_type& functor, parameter_auxilary_type auxilary) : AccessorAdapter(functor), _auxilaryBridge(auxilary) {}
		public:
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new AccessorElement(*this); }
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _auxilaryBridge.isValid(); }
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_auxilary_type getContent() const { return _auxilaryBridge.getContent(); }
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_auxilary_type getUniqueContent() { return _auxilaryBridge.getUniqueContent(); }
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_auxilary_type getConstContent() const { return _auxilaryBridge.getConstContent(); }
			//! @href lazy3::internal::IContent::setContent implementation.
			virtual const_ref_auxilary_type setContent(parameter_auxilary_type auxilary) {
				_auxilaryBridge.setContent(auxilary); 
				return _auxilaryBridge.getConstContent();
			}
		};
		
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class AccessorElement specialization.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename functor_type>
		class AccessorElement<old_type, new_type, void, functor_type> : 
		public AccessorAdapter<old_type, new_type, void, functor_type>
		{
			typedef void auxilary_type;
			typedef AccessorAdapter<old_type, new_type, auxilary_type, functor_type> AccessorAdapter;
		public:
			AccessorElement(const functor_type& functor) : AccessorAdapter(functor) {}
		public:
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new AccessorElement(*this); }
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return true; }
		};
#endif
		
		
	} // namespace internal
	
	
} // namespace lazy3
