/*
 *  lazy3_Accessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_Modifier.h"
#include "lazy3_internal_AccessorElement.h"
#include "lazy3_internal_AccessorAbstractBridge.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	
	//--------------------------------------------------------------------------------
	//! @class Accessor is a modifier.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename old_type, typename new_type, typename auxilary_type = void>
	class Accessor :
	public Modifier<old_type, new_type>,
	protected virtual internal::AccessorAbstractBridge<old_type, new_type, auxilary_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef internal::AccessorAbstractBridge<old_type, new_type, auxilary_type> AccessorAbstractBridge;
		typedef internal::IAccessor<old_type, new_type, auxilary_type> IAccessor;
		typedef Modifier<old_type, new_type> InheritModifier;
		typedef new_type (*ConstRefInFunctionType)(old_type&, auxilary_type&);
		typedef new_type (*InFunctionType)(old_type, auxilary_type);
	public:
		Accessor(const ConstRefInFunctionType& functor) : InheritModifier(new internal::AccessorElement<old_type, new_type, auxilary_type, ConstRefInFunctionType>(functor)) {}
		Accessor(const InFunctionType& functor) : InheritModifier(new internal::AccessorElement<old_type, new_type, auxilary_type, InFunctionType>(functor)) {}
		Accessor(const IAccessor* accessor) : InheritModifier(accessor) {}
		Accessor(const Modifier<old_type, new_type>& accessor) : InheritModifier(accessor) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Accessor specialization.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename old_type, typename new_type>
	class Accessor<old_type,  new_type, void> :
	public Modifier<old_type, new_type>,
	protected virtual internal::AccessorAbstractBridge<old_type, new_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void auxilary_type;
		typedef internal::AccessorAbstractBridge<old_type, new_type, auxilary_type> AccessorAbstractBridge;
		typedef internal::IAccessor<old_type, new_type, auxilary_type> IAccessor;
		typedef Modifier<old_type, new_type> InheritModifier;
		typedef new_type (*ConstRefInFunctionType)(old_type&);
		typedef new_type (*InFunctionType)(old_type);
	public:
		Accessor(const ConstRefInFunctionType& functor) : InheritModifier(new internal::AccessorElement<old_type, new_type, auxilary_type, ConstRefInFunctionType>(functor)) {}
		Accessor(const InFunctionType& functor) : InheritModifier(new internal::AccessorElement<old_type, new_type, auxilary_type, InFunctionType>(functor)) {}
		Accessor(const IAccessor* accessor) : InheritModifier(accessor) {}
		Accessor(const Modifier<old_type, new_type>& accessor) : InheritModifier(accessor) {}
	};
	
	
} // namespace lazy2
