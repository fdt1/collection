/*
 *  lazy_internal_ContainerImplementation_gnu_cxx_normal_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once



#include "lazy_internal_Bridge.h"
#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_Implementation.h"
#include <iterator>

namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ValueTemplate, typename ContainerTemplate>
		class IteratorImplementation<InterfaceTemplate, __gnu_cxx::__normal_iterator<ValueTemplate, ContainerTemplate> > :
		public virtual InterfaceTemplate,
		public virtual Implementation
		{
		protected:
			typedef typename ValueTraits<IteratorTemplate>::PrimeType IteratorPrimeType;
		private:		
			IteratorPrimeType _iterator;
			Bridge _container_bridge;
		public:
			IteratorImplementation(const IteratorPrimeType& iter) : _iterator(iter)  {}
			IteratorImplementation(const IteratorPrimeType& iter, const Bridge& container_bridge) : _iterator(iter), _container_bridge(container_bridge)  {}
		public:
			// Implementation
			virtual IteratorImplementation* duplicate() const { return new IteratorImplementation(*this); }
		public:
			// BasicIteratorInterface
			virtual bool is_valid() const { return _iterator != _container_bridge.get_implementation()->end(); }
		public:
			// InputIteratorInterface
			virtual ValuePrimeType get_instance() const { return *_iterator; }
			virtual ValueReferenceType get_reference() const { return *_iterator; }
			virtual ValueConstRefType get_const_reference() const { return *_iterator; }
		public:
			// AddressInterface
			virtual ValuePrimeType* get_pointed_address() const { return _iterator; }
		public:
			// RestartInterface
			virtual void restart() { _iterator = _container_bridge.get_implementation()->get_begin(); }
		public:
			// ForwardIteratorInterface
			virtual void increment() { ++_iterator; }
			virtual void increment(int offset) { _iterator += offset; }
			virtual int increment_if_possible(int offset) { 
				int max_offset = get_container().end() - _iterator;
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
			// FIXME: cela ne marche pas avec PtrDiffIteratorInterface
			virtual int diff(const PtrDiffIteratorInterface& other) const { return get_iterator() - (dynamic_cast<const SelfType&> (other)).get_iterator(); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy