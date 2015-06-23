/*
 *  variety_Accessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/01/11.
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
	
	/* FIXME
	 to make it work more generically :
	   1. add get_value(optional_impl* impl = NULL)
	   2. l'accessor ne fait que redefinir le ou les interfaces!
	   3. dans les bridges tester si l'optional impl est castable si oui alors l'appeler en priorite!
	 */
	template<typename ValueTemplate, typename PrevValueTemplate = ValueTemplate>
	class Accessor :
	public virtual Generic
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
		typedef Accessor<ValueType, PrevValueType> SelfType;
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
		Accessor(ValueType (InheritedPrevValueTemplate::*method)() const) { set_implementation(new internal::MethodAccessorImplementation<ValueType, PrevValueType, ValueType (InheritedPrevValueTemplate::*)() const, InterfaceType>(method)); }
		Accessor(const ConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor(const ConstFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstFunctionType, InterfaceType>(function)); }				
		Accessor(const ConstRefOutConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefOutConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor(const ConstRefOutFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstRefOutFunctionType, InterfaceType>(function)); }				
		Accessor(const RefOutConstRefInFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, RefOutConstRefInFunctionType, InterfaceType>(function)); }				
		Accessor(const RefOutFunctionType& function) { set_implementation(new internal::FunctionAccessorImplementation<ValueType, PrevValueType, RefOutFunctionType, InterfaceType>(function)); }				
	};

	template<typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate>
	class DatumAccessor :
	public virtual Accessor<ValueTemplate, PrevValueTemplate>
	{
	public:
		typedef ValueTemplate ValueType;
		typedef PrevValueTemplate PrevValueType;
		typedef DatumTemplate DatumType;
		typedef internal::DatumAccessorInterface<ValueType, PrevValueType, DatumType> InterfaceType;
		typedef internal::DatumAccessorBridge<ValueType, PrevValueType, DatumType> BridgeType;
		template <typename NewValueType, typename NewPrevValueType = PrevValueType, typename NewDatumType = DatumType>
		struct ChangeValue {
			typedef DatumAccessor<NewValueType, NewPrevValueType, NewDatumType> Type;
		};
	protected:
		typedef DatumAccessor<ValueType, PrevValueType, DatumType> SelfType;
		typedef internal::SetDatumAccessorInterface<DatumType> SetDatumAccessorInterface;
		typedef typename internal::GenericTraits<PrevValueType>::ValueType RawPrevValueType;
		typedef typename internal::GenericTraits<DatumType>::ValueType RawDatumType;
		typedef ValueType (RawPrevValueType::*ConstMethodType)(const RawDatumType&) const;
		typedef ValueType (*ConstFunctionType)(const RawPrevValueType&, const RawDatumType&);
	protected:
		SetDatumAccessorInterface& get_set_datum_accessor_interface() { return dynamic_cast<SetDatumAccessorInterface&> (*Generic::get_unique_implementation()); }
		const SetDatumAccessorInterface& get_set_datum_accessor_interface() const { return dynamic_cast<const SetDatumAccessorInterface&> (*Generic::get_implementation()); }
	public:
		DatumAccessor(const ConstMethodType& method) : Generic(new internal::MethodDatumAccessorImplementation<ValueType, PrevValueType, DatumType, ConstMethodType, InterfaceType>(method)) {}
		DatumAccessor(const ConstFunctionType& function) : Generic(internal::FunctionDatumAccessorImplementation<ValueType, PrevValueType, DatumType, ConstFunctionType, InterfaceType>(function)) {}				
	public:
		DatumAccessor operator() (const RawDatumType& datum) const { SelfType accessor = *this; get_set_datum_accessor_interface().set_datum(datum); return accessor; }
	};
	
	/* FIXME peut-on resoudre cela par un const Accessor dans le apply de l'iterateur:
	   apply(const Accessor&) -> pas de modif alors ok
	   apply(Accessor&) -> modif alors modif de la collection
	   Pb aussi avec le datum!
	template<typename ValueTemplate, typename PrevValueTemplate>
	class MutableAccessor :
	public virtual Accessor<ValueTemplate, PrevValueTemplate>
	{
	public:
		typedef ValueTemplate ValueType;
		typedef PrevValueTemplate PrevValueType;
		typedef internal::MutableAccessorInterface<ValueType, PrevValueType> InterfaceType;
		typedef internal::MutableAccessorBridge<ValueType, PrevValueType> BridgeType;
		template <typename NewValueType, typename NewPrevValueType = PrevValueType>
		struct ChangeValue {
			typedef MutableAccessor<NewValueType, NewPrevValueType> Type;
		};
	protected:
		typedef MutableAccessor<ValueType, PrevValueType> SelfType;
		typedef internal::InputAccessorInterface<ValueType, PrevValueType> InputAccessorInterface;
		typedef typename internal::GenericTraits<PrevValueType>::ValueType RawPrevValueType;
		typedef ValueType (RawPrevValueType::*MethodType)();
		typedef ValueType (RawPrevValueType::*ConstMethodType)() const;
		typedef ValueType (*FunctionType)(RawPrevValueType&);
		typedef ValueType (*ConstFunctionType)(const RawPrevValueType&);		
	public:
		MutableAccessor(const MethodType& method) : Generic(new internal::MethodAccessorImplementation<ValueType, PrevValueType, MethodType, InterfaceType>(method)) {}
		MutableAccessor(const ConstMethodType& method) : Generic(new internal::MethodAccessorImplementation<ValueType, PrevValueType, ConstMethodType, InterfaceType>(method)) {}
		MutableAccessor(const FunctionType& function) : Generic(internal::FunctionAccessorImplementation<ValueType, PrevValueType, FunctionType, InterfaceType>(function)) {}				
		MutableAccessor(const ConstFunctionType& function) : Generic(internal::FunctionAccessorImplementation<ValueType, PrevValueType, ConstFunctionType, InterfaceType>(function)) {}				
	};
	 */
	
} // namespace variety

/* FIXME : ici 
 template <typename GenericTemplate, typename InterfaceTemplate>
 struct RemoveInterface {
 typedef GenericTemplate IteratorType;
 };
 
*/
 
#if 0 //FIXME : faire le DatumAccessor :public Accessor
namespace variety {
	
	template<typename ValueTemplate, typename PrevValueTemplate>
	class Accessor :
	public virtual Generic
	{
	public:
		typedef ValueTemplate ValueType ;
	protected:
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
	protected:
		InputIteratorInterface& get_input_iterator_interface() { return dynamic_cast<InputIteratorInterface&> (*Generic::get_unique_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*Generic::get_implementation()); }
		
	public:
		template<typename X>    
		Accessor(ValueType (X::*member)()) : Generic(new internal::alMemberAccessor<E, A, D>(member)) {}
		template<typename X>
		Accessor(ValueType (X::*member)() const) : Generic(new internal::alMemberAccessor<E, A, D>(member)) {}
		template<typename X, typename DatumType>
		Accessor(ValueType (X::*member)(DatumType datum)) : Generic(new internal::alMemberDatumAccessor<E, A, D>(member)) {}
		template<typename X, typename DatumType>
		Accessor(ValueType (X::*member)(DatumType datum) const) : Generic(new internal::alMemberDatumAccessor<E, A, D>(member)) {}
		template<typename PrevValueType>
		Accessor(ValueType (*function)(PrevValueType value)) : Generic(new internal::alFunctionAccessor<E, A, D>(function)) {}
		template<typename PrevValueType, typename DatumType>
		Accessor(ValueType (*function)(PrevValueType value, DatumType datum)) : Generic(new internal::alFunctionDatumAccessor<E, A, D>(function)) {}		
	public:
		Accessor<E, A, D>&        operator=(Driver* driver);
		Accessor<E, A, D>&        operator=(const Accessor<E, A, D>& accessor);
		
	public:
		Accessor<E, A, D>        operator()() const;
		Accessor<E, A, D>        operator()(const DatumType& DatumType datum) const;
	public:
		ValueType get_value() const {}
		
		
	};
	
	
} // namespace variety
#endif