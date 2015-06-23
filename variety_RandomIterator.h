/*
 *  variety_RandomIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_Iterator.h"
#include "variety_internal_BackwardIteratorInterface.h"
#include "variety_internal_PtrDiffIteratorInterface.h"
#include "variety_internal_RandomIteratorInterface.h"
#include "variety_internal_RandomIteratorBridge.h"

namespace variety {
		
	template <typename ValueTemplate>
	class RandomIterator : 
	public virtual Iterator<ValueTemplate>
	{
	public:
		typedef ValueTemplate ValueType;
		typedef internal::RandomIteratorInterface<ValueType> InterfaceType;
		typedef internal::RandomIteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef RandomIterator<NewValueType> Type;
		};
		
	protected:
		typedef RandomIterator<ValueType> SelfType;
		typedef Iterator<ValueType> Iterator;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		typedef internal::PtrDiffIteratorInterface PtrDiffIteratorInterface;
	protected:
		BackwardIteratorInterface& get_backward_iterator_interface() { return dynamic_cast<BackwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*Generic::get_implementation()); }
		PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() { return dynamic_cast<PtrDiffIteratorInterface&> (*Generic::get_unique_implementation()); }
		const PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() const { return dynamic_cast<const PtrDiffIteratorInterface&> (*Generic::get_implementation()); }
	public:
		explicit RandomIterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		RandomIterator() {}
		virtual ~RandomIterator() {}
	public:
		// redefine ForwardIteratorInterface
		SelfType& operator++() { Iterator::get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; Iterator::get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { Iterator::get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }
	public:
		// BackwardIteratorInterface
		SelfType& operator--() { get_backward_iterator_interface().decrement(); return *this; }
		SelfType operator--(int) { SelfType it = *this; get_backward_iterator_interface().decrement(); return it; }
		SelfType& operator-=(int offset) { get_backward_iterator_interface().decrement(offset); return *this; }
		SelfType operator-(int offset) { SelfType it = *this; it.get_backward_iterator_interface().decrement(offset); return it; }
	public:	
		// PtrDiffIteratorInterface
		int operator-(const SelfType& other) const { return get_ptr_diff_iterator_interface().diff(other.get_ptr_diff_iterator_interface()); }
		bool operator<(const SelfType& other) const { return get_ptr_diff_iterator_interface().diff(other.get_ptr_diff_iterator_interface()) < 0; }
		bool operator<=(const SelfType& other) const { return get_ptr_diff_iterator_interface().diff(other.get_ptr_diff_iterator_interface()) <= 0; }
	};
	
	template <typename ValueTemplate>
	class RandomIterator<const ValueTemplate&> : 
	public virtual Iterator<const ValueTemplate&>,
	public virtual RandomIterator<ValueTemplate>
	{
	public:
		typedef const ValueTemplate& ValueType;
		typedef internal::RandomIteratorInterface<ValueType> InterfaceType;
		typedef internal::RandomIteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef RandomIterator<NewValueType> Type;
		};
	protected:
		typedef RandomIterator<ValueType> SelfType;
		typedef Iterator<ValueType> Iterator;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		typedef internal::PtrDiffIteratorInterface PtrDiffIteratorInterface;
	protected:
		BackwardIteratorInterface& get_backward_iterator_interface() { return dynamic_cast<BackwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*Generic::get_implementation()); }
		PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() { return dynamic_cast<PtrDiffIteratorInterface&> (*Generic::get_unique_implementation()); }
		const PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() const { return dynamic_cast<const PtrDiffIteratorInterface&> (*Generic::get_implementation()); }
	public:
		explicit RandomIterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		RandomIterator() {}
		virtual ~RandomIterator() {}
	public:
		// redefine ForwardIteratorInterface
		SelfType& operator++() { Iterator::get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; Iterator::get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { Iterator::get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }
	public:
		// redefine BackwardIteratorInterface
		SelfType& operator--() { get_backward_iterator_interface().decrement(); return *this; }
		SelfType operator--(int) { SelfType it = *this; get_backward_iterator_interface().decrement(); return it; }
		SelfType& operator-=(int offset) { get_backward_iterator_interface().decrement(offset); return *this; }
		SelfType operator-(int offset) { SelfType it = *this; it.get_backward_iterator_interface().decrement(offset); return it; }
	};

	template <typename ValueTemplate>
	class RandomIterator<ValueTemplate&> : 
	public virtual Iterator<ValueTemplate&>,
	public virtual RandomIterator<const ValueTemplate&>
	{
	public:
		typedef ValueTemplate& ValueType;
		typedef internal::RandomIteratorInterface<ValueType> InterfaceType;
		typedef internal::RandomIteratorBridge<ValueType> BridgeType;
		template <typename NewValueType>
		struct ChangeValue {
			typedef RandomIterator<NewValueType> Type;
		};
	protected:
		typedef RandomIterator<ValueType> SelfType;
		typedef Iterator<ValueType> Iterator;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		typedef internal::PtrDiffIteratorInterface PtrDiffIteratorInterface;
	protected:
		BackwardIteratorInterface& get_backward_iterator_interface() { return dynamic_cast<BackwardIteratorInterface&> (*Generic::get_unique_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*Generic::get_implementation()); }
		PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() { return dynamic_cast<PtrDiffIteratorInterface&> (*Generic::get_unique_implementation()); }
		const PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() const { return dynamic_cast<const PtrDiffIteratorInterface&> (*Generic::get_implementation()); }
	public:
		explicit RandomIterator(const Generic& generic) { 
			if (InterfaceType::is_compatible(generic.get_implementation())) {
				Generic::set_shared_implementation(generic.Generic::get_shared_implementation());
			}
		}
		RandomIterator() {}
		virtual ~RandomIterator() {}
	public:
		// redefine ForwardIteratorInterface
		SelfType& operator++() { Iterator::get_forward_iterator_interface().increment(); return *this; }
		SelfType operator++(int) { SelfType it = *this; Iterator::get_forward_iterator_interface().increment(); return it; }
		SelfType& operator+=(int offset) { Iterator::get_forward_iterator_interface().increment(offset); return *this; }
		SelfType operator+(int offset) { SelfType it = *this; it.get_forward_iterator_interface().increment(offset); return it; }
	public:
		// redefine BackwardIteratorInterface
		SelfType& operator--() { get_backward_iterator_interface().decrement(); return *this; }
		SelfType operator--(int) { SelfType it = *this; get_backward_iterator_interface().decrement(); return it; }
		SelfType& operator-=(int offset) { get_backward_iterator_interface().decrement(offset); return *this; }
		SelfType operator-(int offset) { SelfType it = *this; it.get_backward_iterator_interface().decrement(offset); return it; }
	};
	
	
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate>, internal::PtrDiffIteratorInterface> {
		// FIXME: should be BidirIterator
		typedef Iterator<ValueTemplate> IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate>, internal::BackwardIteratorInterface> {
		typedef Iterator<ValueTemplate> IteratorType;
	};
	 
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate>, internal::ForwardIteratorInterface> {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate>, internal::BasicIteratorInterface> {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};

	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<const ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<const ValueTemplate&>, internal::InputIteratorInterface<const ValueTemplate&> > {
		typedef RandomIterator<ValueTemplate> IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate> > {
		typedef Generic IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate&>, internal::InputIteratorInterface<const ValueTemplate&> > {
		typedef RandomIterator<ValueTemplate&> IteratorType;
	};
	
	template <typename ValueTemplate>
	struct RemoveInterface<RandomIterator<ValueTemplate&>, internal::InputIteratorInterface<ValueTemplate&> > {
		typedef RandomIterator<const ValueTemplate&> IteratorType;
	};
	
	
} // namespace variety