/*
 *  variety_internal_InputIteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_Bridge.h"

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class InputIteratorBridge :
		public virtual Bridge,
		public virtual InputIteratorInterface<ValueTemplate>
		{
		public:
			typedef ValueTemplate ValueType;
			typedef InputIteratorInterface<ValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_instance() const { return get_interface().get_instance(); }
		};
		
		
		template <typename ValueTemplate>
		class InputIteratorBridge<const ValueTemplate&> :
		public virtual Bridge,
		public virtual InputIteratorBridge<ValueTemplate>,
		public virtual InputIteratorInterface<const ValueTemplate&>
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef InputIteratorInterface<ValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_const_reference () const { return get_interface().get_const_reference(); }
		};
		
		
		template <typename ValueTemplate>
		class InputIteratorBridge<ValueTemplate&> :
		public virtual Bridge,
		public virtual InputIteratorBridge<const ValueTemplate&>,
		public virtual InputIteratorInterface<ValueTemplate&>
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef InputIteratorInterface<ValueType> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual ValueType get_reference() const { return get_interface().get_reference(); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety