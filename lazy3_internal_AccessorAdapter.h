/*
 *  lazy3_internal_AccessorAdapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 18/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IAccessor.h"
#include "lazy3_internal_ContentElement.h"

namespace lazy3 {
	
	namespace internal {
		
		
		
		//--------------------------------------------------------------------------------
		//! @class AccessorAdapterOnFunctionWithAuxilary applies a function with
		//! an auxilary value.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type, typename functor_type>
		class AccessorAdapterOnFunctionWithAuxilary : 
		public virtual IAccessor<old_type, new_type, auxilary_type>
		{
			typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
		public:
			functor_type _functor;
		public:
			AccessorAdapterOnFunctionWithAuxilary(const functor_type& functor) : _functor(functor) {}
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual new_type change(parameter_old_type old_value) { return (*_functor)(old_value, this->getConstContent()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class AccessorAdapterOnFunction applies a function.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename functor_type>
		class AccessorAdapterOnFunction : 
		public virtual IAccessor<old_type, new_type, void>
		{
			typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
		public:
			functor_type _functor;
		public:
			AccessorAdapterOnFunction(const functor_type& functor) : _functor(functor) {}
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual new_type change(parameter_old_type old_value) { return (*_functor)(old_value); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class AccessorAdapter wraps all methods of the container to match 
		//! a given interface.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type, typename functor_type>
		class AccessorAdapter :
		public AccessorAdapterOnFunctionWithAuxilary<old_type, new_type, auxilary_type, functor_type>
		{
			typedef AccessorAdapterOnFunctionWithAuxilary<old_type, new_type, auxilary_type, functor_type> AccessorAdapterOnFunctionWithAuxilary;
		public:
			AccessorAdapter(const functor_type& functor) : AccessorAdapterOnFunctionWithAuxilary(functor) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class AccessorAdapter specialization.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename functor_type>
		class AccessorAdapter<old_type, new_type, void, functor_type> :
		public AccessorAdapterOnFunction<old_type, new_type, functor_type>
		{
			typedef AccessorAdapterOnFunction<old_type, new_type, functor_type> AccessorAdapterOnFunction;
		public:
			AccessorAdapter(const functor_type& functor) : AccessorAdapterOnFunction(functor) {}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
