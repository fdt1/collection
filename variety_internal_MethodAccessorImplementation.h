/*
 *  variety_internal_MethodAccessorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_GenericTraits.h"
#include "variety_internal_InputAccessorInterface.h"
#include "variety_internal_Implementation.h"
// for shared_ptr
#include <tr1/memory> 

namespace variety {
	
	
	namespace internal {
		
#if 1
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation<const ValueTemplate&, PrevValueTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<const ValueTemplate&, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation<ValueTemplate&, PrevValueTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate&, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ConstReferenceValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ValueType get_member_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
#else
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<ValueTemplate>,
		public virtual Bridge,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
			std::tr1::shared_ptr<Implementation> _shared_implementation;			
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// Bridge
			virtual void set_implementation(internal::Implementation* implementation) = 0;
			virtual internal::Implementation* get_implementation() = 0;
			virtual const internal::Implementation* get_implementation() const { return _shared_implementation.get(); }
		public:
			// InputIteratorInterface
			virtual ValueType get_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation<const ValueTemplate&, PrevValueTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<const ValueTemplate&>,
		public virtual Bridge,
		public virtual Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// InputIteratorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodAccessorImplementation<ValueTemplate&, PrevValueTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputIteratorInterface<ValueTemplate&>,
		public virtual Bridge,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			MethodTemplate _method;
		public:
			MethodAccessorImplementation(const MethodTemplate& method) : _method(method) {}
			virtual ~MethodAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodAccessorImplementation* duplicate() const { return new MethodAccessorImplementation(_method); }
			virtual std::string get_name() const { return typeid(MethodAccessorImplementation).name(); }
		public:
			// InputIteratorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ConstReferenceValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
			virtual ValueType get_member_reference(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		};		
#endif
		
	} // namespace internal
	
} // namespace variety