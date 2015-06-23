/*
 *  variety_internal_InputAccessorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 08/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputAccessorInterface.h"
#include "variety_internal_Bridge.h"

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorBridge :
		public virtual Bridge,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>
		{
		public:
			typedef ValueTemplate ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef InputAccessorInterface<ValueType, PrevValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const { return get_interface().get_member_instance(); }
		};
		
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorBridge<const ValueTemplate&, PrevValueTemplate> :
		public virtual Bridge,
		public virtual InputAccessorBridge<ValueTemplate, PrevValueTemplate>,
		public virtual InputAccessorInterface<const ValueTemplate&, PrevValueTemplate>
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef InputAccessorInterface<ValueType, PrevValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_member_const_reference (const PrevValueType& prev_value) const { return get_interface().get_member_const_reference(); }
		};
		
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorBridge<ValueTemplate&, PrevValueTemplate> :
		public virtual Bridge,
		public virtual InputAccessorBridge<const ValueTemplate&, PrevValueTemplate>,
		public virtual InputAccessorInterface<ValueTemplate&, PrevValueTemplate>
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef InputAccessorInterface<ValueType, PrevValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_member_reference(const PrevValueType& prev_value) const { return get_interface().get_member_reference(); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety