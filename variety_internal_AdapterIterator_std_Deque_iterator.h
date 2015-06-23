/*
 *  variety_internal_AdapterIterator_std_Deque_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once



#include "variety_internal_AdapterIterator.h"
#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_BackwardIteratorInterface.h"
#include "variety_internal_PtrDiffIteratorInterface.h"
#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_GenericTraits.h"
#include "variety_internal_AdapterIteratorInterface.h"
#include <deque>

namespace variety {
	
	namespace internal {
		
		template <typename _Tp, typename _Ref, typename _Ptr, typename ContainerTemplate>
		class AdapterIterator<std::_Deque_iterator<_Tp, _Ref, _Ptr>, ContainerTemplate> :
		public virtual AdapterIteratorInterface<std::_Deque_iterator<_Tp, _Ref, _Ptr>, ContainerTemplate>,
		public virtual InputIteratorInterface<typename std::_Deque_iterator<_Tp, _Ref, _Ptr>::reference>,
		public virtual BasicIteratorInterface,
		public virtual ForwardIteratorInterface,
		public virtual BackwardIteratorInterface,
		public virtual PtrDiffIteratorInterface	
		{
		protected:
			typedef std::_Deque_iterator<_Tp, _Ref, _Ptr> IteratorTemplate;
		public:
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ValueType ValueType;
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ReferenceType ReferenceType;
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ConstRefType ConstRefType;
		protected:
			typedef AdapterIterator<IteratorTemplate, ContainerTemplate> SelfType;
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef typename GenericTraits<IteratorTemplate>::ValueType IteratorType;
		public:
			// AdapterIteratorInterface
			virtual ContainerType& get_container() = 0;
			virtual const ContainerType& get_container() const = 0;
			virtual IteratorType& get_iterator() = 0;
			virtual const IteratorType& get_iterator() const = 0;
		public:
			// BasicIteratorInterface
			virtual bool is_valid() const { return get_iterator() != get_container().end(); }
			virtual void restart() { get_iterator() = get_container().begin(); }
			virtual bool is_equal(const BasicIteratorInterface& other) const { return get_iterator() == (dynamic_cast<const SelfType&> (other)).get_iterator(); }
		public:
			// InputIteratorInterface
			virtual ValueType get_instance() const { return *get_iterator(); }
			virtual ReferenceType get_reference() const { return *get_iterator(); }
			virtual ConstRefType get_const_reference() const { return *get_iterator(); }
		public:
			// ForwardIteratorInterface
			virtual void increment() { ++get_iterator(); }
			virtual void increment(int offset) { get_iterator() += offset; }
			virtual int increment_if_possible(int offset) { 
				int max_offset = get_container().end() - get_iterator();
				if (offset <= max_offset) {
					get_iterator() += offset; 
					return 0;
				} else {
					get_iterator() = get_container().begin(); 
					return offset - max_offset;
				}
			}
		public:
			// BackwardIteratorInterface
			virtual void decrement() { --get_iterator(); }
			virtual void decrement(int offset) { get_iterator() -= offset; }
			virtual int decrement_if_possible(int offset) { 
				int max_offset = get_iterator() - get_container().begin();
				if (offset <= max_offset) {
					get_iterator() -= offset; 
					return 0;
				} else {
					get_iterator() = get_container().end(); 
					return offset - max_offset;
				}
			}
		public:	
			// PtrDiffIteratorInterface
			virtual int diff(const PtrDiffIteratorInterface& other) const { return get_iterator() - (dynamic_cast<const SelfType&> (other)).get_iterator(); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety