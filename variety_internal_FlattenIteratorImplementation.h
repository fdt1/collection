/*
 *  variety_internal_FlattenIteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 04/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_SharedImplementation.h"
// for std::pair
#include <list>
// for shared_ptr
#include <tr1/memory> 

namespace variety {
	
	
	namespace internal {
		
		template <typename BridgeTemplate>
		class FlattenIteratorImplementation : 
		public virtual BridgeTemplate,
		public virtual ForwardIteratorInterface,
		public virtual BackwardIteratorInterface,
		public virtual BasicIteratorInterface,
		public virtual Implementation
		{
		public:
			typedef SharedImplementation<Implementation> SharedImplementation;
		protected:
			SharedImplementation _shared_implementation;
			SharedImplementation _shared_implementation_nested;
		public:
		public:
			TransformIteratorImplementation(const SharedImplementation& shared_implementation) : _shared_implementation(shared_implementation) {}
			//TransformIteratorImplementation(const SharedImplementation<Implementation>& shared_implementation, const BridgeTemplate& bridge) : BridgeTemplate(bridge), SharedImplementation<Implementation>(shared_implementation) {}
			virtual ~TransformIteratorImplementation() {}
			// Implementation
			virtual TransformIteratorImplementation* duplicate() const { return new TransformIteratorImplementation(_shared_implementation); }
			virtual std::string get_name() const { return typeid(TransformIteratorImplementation).name(); }
			// Bridge
			//virtual void set_implementation(internal::Implementation* implementation) = 0;
			// ForwardIteratorInterface
			virtual void increment() { 
				if (get_basic_iterator_nested_interface().is_valid()) {
					get_forward_iterator_nested_interface().increment(); 
				} else {
					get_forward_iterator_interface().increment();
					// FIXME :
					get_input_iterator_interface().get_value();
				}
			}
			virtual void increment(int offset) { get_forward_iterator_nested_interface().increment_if_possible(offset); }
			// BackwardIteratorInterface
			virtual void decrement() { get_backward_iterator_nested_interface().decrement(); }
			virtual void decrement(int offset) { get_backward_iterator_nested_interface().decrement_if_possible(offset); }
			
		public:			
			ForwardIteratorInterface& get_forward_iterator_interface() { return dynamic_cast<ForwardIteratorInterface&> (*_shared_implementation.get_implementation()); }
			BackwardIteratorInterface& get_backward_iterator_interface() { return dynamic_cast<BackwardIteratorInterface&> (*_shared_implementation.get_implementation()); }
			ForwardIteratorInterface& get_forward_iterator_nested_interface() { return dynamic_cast<ForwardIteratorInterface&> (*_shared_implementation_nested.get_implementation()); }
			BackwardIteratorInterface& get_backward_iterator_nested_interface() { return dynamic_cast<BackwardIteratorInterface&> (*_shared_implementation_nested.get_implementation()); }
			const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*_shared_implementation.get_implementation()); }
			const InputIteratorInterface& get_input_iterator_nested_interface() const { return dynamic_cast<const InputIteratorInterface&> (*_shared_implementation_nested.get_implementation()); }
			const BasicIteratorInterface& get_basic_iterator_nested_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*_shared_implementation_nested.get_implementation()); }
		public:
			virtual const internal::Implementation* get_implementation() const { return _shared_implementation.get_implementation_nested(); }
			virtual internal::Implementation* get_implementation() { return _shared_implementation.get_implementation_nested(); }
			
		};		
		
	} // namespace internal

} // namespace variety