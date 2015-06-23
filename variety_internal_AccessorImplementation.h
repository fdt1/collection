/*
 *  variety_internal_AccessorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 08/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_InputAccessorInterface.h"
#include "variety_internal_Implementation.h"
// for shared_ptr
#include <tr1/memory> 

namespace variety {
	
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename BridgeTemplate>
		class AccessorImplementation : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<ValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate ValueType;
			typedef InputIteratorInterface<PrevValueTemplate> PrevInputIteratorInterface;
			typedef InputAccessorInterface<ValueTemplate, PrevValueTemplate> InputAccessorInterface;
		private:
#ifdef TYPED_IMPLEMENTATION
			internal::SharedImplementation<PrevInputIteratorInterface> _shared_prev_input_iterator_interface;
			internal::SharedImplementation<InputAccessorInterface> _shared_input_accessor_interface;
#else
			internal::SharedImplementation<Implementation> _shared_prev_input_iterator_interface;
			internal::SharedImplementation<Implementation> _shared_input_accessor_interface;
#endif		
		public:
			AccessorImplementation(const internal::SharedImplementation<Implementation>& shared_prev_input_iterator_interface, const internal::SharedImplementation<Implementation>& shared_input_accessor_interface) : _shared_prev_input_iterator_interface(shared_prev_input_iterator_interface), _shared_input_accessor_interface(shared_input_accessor_interface) {}
			virtual ~AccessorImplementation() {}
		public:
			// Implementation
			virtual AccessorImplementation* duplicate() const { return new AccessorImplementation(*this); }
			virtual std::string get_name() const { return typeid(AccessorImplementation).name(); }
		public:			
			const PrevInputIteratorInterface& get_prev_input_iterator_interface() const { return dynamic_cast<const PrevInputIteratorInterface&> (*_shared_prev_input_iterator_interface.get_implementation()); }
			const InputAccessorInterface& get_input_accessor_interface() const { return dynamic_cast<const InputAccessorInterface&> (*_shared_input_accessor_interface.get_implementation()); }
		public:			
			// InputIteratorInterface
			virtual ValueType get_instance() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
		public:
			// BridgeTemplate
			Implementation* get_implementation() { return _shared_prev_input_iterator_interface.get_implementation(); }
			const Implementation* get_implementation() const { return _shared_prev_input_iterator_interface.get_implementation(); }
			
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename BridgeTemplate>
		class AccessorImplementation<const ValueTemplate&, PrevValueTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<const ValueTemplate&>,
		public virtual Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef InputIteratorInterface<PrevValueTemplate> PrevInputIteratorInterface;
			typedef InputAccessorInterface<ValueTemplate, PrevValueTemplate> InputAccessorInterface;
		private:
			internal::SharedImplementation<Implementation> _shared_prev_input_iterator_interface;
			internal::SharedImplementation<Implementation> _shared_input_accessor_interface;
		public:
			AccessorImplementation(const internal::SharedImplementation<Implementation>& shared_prev_input_iterator_interface, const internal::SharedImplementation<Implementation>& shared_input_accessor_interface) : _shared_prev_input_iterator_interface(shared_prev_input_iterator_interface), _shared_input_accessor_interface(shared_input_accessor_interface) {}
			virtual ~AccessorImplementation() {}
		public:
			// Implementation
			virtual AccessorImplementation* duplicate() const { return new AccessorImplementation(*this); }
			virtual std::string get_name() const { return typeid(AccessorImplementation).name(); }
		public:			
			const PrevInputIteratorInterface& get_prev_input_iterator_interface() const { return dynamic_cast<const PrevInputIteratorInterface&> (*_shared_prev_input_iterator_interface.get_implementation()); }
			const InputAccessorInterface& get_input_accessor_interface() const { return dynamic_cast<const InputAccessorInterface&> (*_shared_input_accessor_interface.get_implementation()); }
		public:			
			// InputIteratorInterface
			virtual ValueType get_const_reference() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
			
			virtual InstanceValueType get_instance() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename BridgeTemplate>
		class AccessorImplementation<ValueTemplate&, PrevValueTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<ValueTemplate&>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef InputIteratorInterface<PrevValueTemplate> PrevInputIteratorInterface;
			typedef InputAccessorInterface<ValueTemplate, PrevValueTemplate> InputAccessorInterface;
		private:
			internal::SharedImplementation<Implementation> _shared_prev_input_iterator_interface;
			internal::SharedImplementation<Implementation> _shared_input_accessor_interface;
		public:
			AccessorImplementation(const internal::SharedImplementation<Implementation>& shared_prev_input_iterator_interface, const internal::SharedImplementation<Implementation>& shared_input_accessor_interface) : _shared_prev_input_iterator_interface(shared_prev_input_iterator_interface), _shared_input_accessor_interface(shared_input_accessor_interface) {}
			virtual ~AccessorImplementation() {}
		public:
			// Implementation
			virtual AccessorImplementation* duplicate() const { return new AccessorImplementation(*this); }
			virtual std::string get_name() const { return typeid(AccessorImplementation).name(); }
		public:			
			const PrevInputIteratorInterface& get_prev_input_iterator_interface() const { return dynamic_cast<const PrevInputIteratorInterface&> (*_shared_prev_input_iterator_interface.get_implementation()); }
			const InputAccessorInterface& get_input_accessor_interface() const { return dynamic_cast<const InputAccessorInterface&> (*_shared_input_accessor_interface.get_implementation()); }
		public:			
			// InputIteratorInterface
			virtual ValueType get_reference() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
			
			virtual ConstReferenceValueType get_const_reference() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
			
			virtual InstanceValueType get_instance() const
			{
				return get_input_accessor_interface().get_member(get_prev_input_iterator_interface().get_value());
			}
		};		
		
	} // namespace internal
	
} // namespace variety