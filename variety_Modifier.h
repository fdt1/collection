/*
 *  variety_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_Generic.h"
#include "variety_internal_GenericTraits.h"
#include "variety_internal_InputAccessorInterface.h"
#include "variety_internal_MethodAccessorImplementation.h"
#include "variety_internal_FunctionAccessorImplementation.h"
#include "variety_internal_AccessorBridge.h"
#include "variety_internal_AccessorInterface.h"
#include "variety_internal_DatumAccessorInterface.h"
#include "variety_internal_DatumAccessorBridge.h"
#include "variety_internal_MethodDatumAccessorImplementation.h"
#include "variety_internal_FunctionDatumAccessorImplementation.h"


namespace variety {

	template<typename ValueTemplate, typename PrevValueTemplate>
	class Modifier :
	public virtual Generic
	{
	};
	
	template<typename ValueTemplate, typename PrevValueTemplate>
	class ConstModifier :
	public virtual Modifier<ValueTemplate, PrevValueTemplate>
	{
	protected:
		
	};
	
	template<typename ValueTemplate, typename PrevValueTemplate>
	class Accessor2 :
	public virtual Accessor<ValueTemplate, PrevValueTemplate>
	{
	public:
		typedef ValueTemplate ValueType;
		typedef PrevValueTemplate PrevValueType;
		typedef internal::AccessorInterface<ValueType, PrevValueType> InterfaceType;
		typedef internal::AccessorBridge<ValueType, PrevValueType> BridgeType;
		template <typename NewValueType, typename NewPrevValueType = PrevValueType>
		struct ChangeValue {
			typedef Accessor<NewValueType, NewPrevValueType> Type;
		};
	protected:
		typedef Accessor2<ValueType, PrevValueType> SelfType;
		typedef internal::InputAccessorInterface<ValueType, PrevValueType> InputAccessorInterface;
		typedef typename internal::GenericTraits<PrevValueType>::ValueType RawPrevValueType;
		typedef typename internal::GenericTraits<ValueType>::ValueType RawValueType;
		//typedef ValueType (RawPrevValueType::*ConstMethodType)() const;
		typedef RawValueType (*ConstRefInFunctionType)(const RawPrevValueType&);
		typedef RawValueType (*ConstFunctionType)(RawPrevValueType);
		typedef const RawValueType& (*ConstRefOutConstRefInFunctionType)(const RawPrevValueType&);
		typedef const RawValueType& (*ConstRefOutFunctionType)(RawPrevValueType);
		typedef RawValueType& (*RefOutConstRefInFunctionType)(const RawPrevValueType&);
		typedef RawValueType& (*RefOutFunctionType)(RawPrevValueType);
	protected:
		InputAccessorInterface& get_input_accessor_interface() { return dynamic_cast<InputAccessorInterface&> (*Generic::get_unique_implementation()); }
		const InputAccessorInterface& get_input_accessor_interface() const { return dynamic_cast<const InputAccessorInterface&> (*Generic::get_implementation()); }
	public:
		template<typename InheritedPrevValueTemplate>
		Accessor2(ValueType (InheritedPrevValueTemplate::*method)() const) { set_implementation(new internal::MethodAccessorImplementation<ValueType, PrevValueType, ValueType (InheritedPrevValueTemplate::*)() const, InterfaceType>(method)); }
		Accessor2(const ConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor2(const ConstFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstFunctionType, InterfaceType>(function)); }				
		Accessor2(const ConstRefOutConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefOutConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor2(const ConstRefOutFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefOutFunctionType, InterfaceType>(function)); }				
		Accessor2(const RefOutConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, RefOutConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor2(const RefOutFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, RefOutFunctionType, InterfaceType>(function)); }				
	};
} // namespace variety
