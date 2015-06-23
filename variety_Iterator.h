/*
 *  variety_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_Generic.h"
#include "variety_Accessor.h"
#include "variety_Modifier.h"
#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_IteratorInterface.h"
#include "variety_internal_IteratorBridge.h"
#include "variety_internal_AccessorImplementation.h"

namespace variety {
	
	template <typename ValueTemplate>
	class Iterator : 
	public virtual Generic
	{
	public:
		typedef ValueTemplate ValueType;
		typedef internal::IteratorInterface<ValueType> InterfaceType;
		typedef internal::IteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef Iterator<NewValueType> Type;
		};
		template <typename InterfaceTemplate, typename dummy = bool>
		struct RemoveInterface {
			typedef Iterator<ValueTemplate&> IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::ForwardIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::BasicIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<ValueTemplate>, dummy > {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<const ValueTemplate&>, dummy > {
			typedef Iterator<ValueTemplate> IteratorType;
		};
	protected:
		typedef Iterator<ValueType> SelfType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
	protected:
		BasicIteratorInterface& get_basic_iterator_interface() { return dynamic_cast<BasicIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BasicIteratorInterface& get_basic_iterator_interface() const {  return dynamic_cast<const BasicIteratorInterface&> (*Generic::get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface() { return dynamic_cast<InputIteratorInterface&> (*Generic::get_unique_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*Generic::get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface() { return dynamic_cast<ForwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*Generic::get_implementation()); }
	public:
		explicit Iterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		Iterator() {}
		virtual ~Iterator() {}
	public:
		// BasicIteratorInterface
		bool is_valid() const { return get_basic_iterator_interface().is_valid(); }
		void restart() { get_basic_iterator_interface().restart(); }
		bool operator==(const SelfType& other) const { return get_basic_iterator_interface().is_equal(other.get_basic_iterator_interface()); }
	public:
		// InputIteratorInterface
		ValueType operator*() const { return get_input_iterator_interface().get_value(); }
	public:
		// ForwardIteratorInterface
		SelfType& operator++() { get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }
	public:
		// FIXME : comment faire pour changer le type de collection : downgrade faut-il faire un type Mutable ?
		template <typename NewValueTemplate>
		Iterator<NewValueTemplate> apply(const Accessor<NewValueTemplate, ValueType>& accessor) const 
		{ 
			typedef internal::AccessorImplementation<NewValueTemplate, ValueType, BridgeType> ImplementationType;
			Iterator<NewValueTemplate> new_object; 
			new_object.set_implementation(new ImplementationType(get_shared_implementation(), accessor.get_shared_implementation())); 
			return new_object; 
		}
	};

	template <typename ValueTemplate>
	class Iterator<const ValueTemplate&> : 
	public virtual Iterator<ValueTemplate>
	{
	public:
		typedef const ValueTemplate& ValueType;
		typedef internal::IteratorInterface<ValueType> InterfaceType;
		typedef internal::IteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef Iterator<NewValueType> Type;
		};
		template <typename InterfaceTemplate, typename dummy = bool>
		struct RemoveInterface {
			typedef Iterator<ValueTemplate&> IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::ForwardIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::BasicIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<ValueTemplate>, dummy > {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<const ValueTemplate&>, dummy > {
			typedef Iterator<ValueTemplate> IteratorType;
		};
		
	protected:
		typedef Iterator<ValueType> SelfType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
	protected:
		BasicIteratorInterface& get_basic_iterator_interface() { return dynamic_cast<BasicIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BasicIteratorInterface& get_basic_iterator_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*Generic::get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface() { return dynamic_cast<InputIteratorInterface&> (*Generic::get_unique_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*Generic::get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface() { return dynamic_cast<ForwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*Generic::get_implementation()); }
	public:
		explicit Iterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		Iterator() {}
		virtual ~Iterator() {}
	public:
		// InputIteratorInterface
		ValueType operator*() const { return get_input_iterator_interface().get_value(); }
	public:
		// redefine ForwardIteratorInterface
		SelfType& operator++() { get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }
	};

	template <typename ValueTemplate>
	class Iterator<ValueTemplate&> : 
	public virtual Iterator<const ValueTemplate&>
	{
	public:
		typedef ValueTemplate& ValueType;
		typedef internal::IteratorInterface<ValueType> InterfaceType;
		typedef internal::IteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef Iterator<NewValueType> Type;
		};
		template <typename InterfaceTemplate, typename dummy = bool>
		struct RemoveInterface {
			typedef Iterator<ValueTemplate&> IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::ForwardIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::BasicIteratorInterface, dummy> {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<ValueTemplate>, dummy > {
			typedef Generic IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<const ValueTemplate&>, dummy > {
			typedef Iterator<ValueTemplate> IteratorType;
		};
		
		template <typename dummy>
		struct RemoveInterface<internal::InputIteratorInterface<ValueTemplate&>, dummy  > {
			typedef Iterator<const ValueTemplate&> IteratorType;
		};
		
	protected:
		typedef Iterator<ValueType> SelfType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
	protected:
		BasicIteratorInterface& get_basic_iterator_interface() { return dynamic_cast<BasicIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BasicIteratorInterface& get_basic_iterator_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*Generic::get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface() { return dynamic_cast<InputIteratorInterface&> (*Generic::get_unique_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*Generic::get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface() { return dynamic_cast<ForwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*Generic::get_implementation()); }
	public:
		// FIXME : plutôt qu'un assert renvoyer une implementation NULL !
		// idem pour RandomIterator !
		explicit Iterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		Iterator() {}
		virtual ~Iterator() {}
	public:
		// FIXME: faire l'opérateur de cast avec un Accessor ou autre chose ! Collection<long> = Collection<int>
	public:
		// redefine InputIteratorInterface
		ValueType operator*() const { return get_input_iterator_interface().get_value(); }
	public:
		// redefine ForwardIteratorInterface
		SelfType& operator++() { get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }

	};
	
	template <typename GenericTemplate, typename InterfaceTemplate>
	struct RemoveInterface {
		typedef GenericTemplate IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate>, internal::ForwardIteratorInterface> {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate>, internal::BasicIteratorInterface> {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<const ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<const ValueTemplate&>, internal::InputIteratorInterface<const ValueTemplate&> > {
		typedef Iterator<ValueTemplate> IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate&>, internal::InputIteratorInterface<const ValueTemplate&> > {
		typedef Iterator<ValueTemplate> IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<Iterator<ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate&> > {
		typedef Iterator<const ValueTemplate&> IteratorType;
	};
	
	
} // namespace variety

