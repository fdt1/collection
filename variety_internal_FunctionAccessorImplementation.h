/*
 *  variety_internal_FunctionAccessorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/11.
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
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionAccessorImplementation : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			FunctionTemplate _Function;
		public:
			FunctionAccessorImplementation(const FunctionTemplate& Function) : _Function(Function) {}
			virtual ~FunctionAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionAccessorImplementation* duplicate() const { return new FunctionAccessorImplementation(_Function); }
			virtual std::string get_name() const { return typeid(FunctionAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionAccessorImplementation<const ValueTemplate&, PrevValueTemplate, FunctionTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			FunctionTemplate _Function;
		public:
			FunctionAccessorImplementation(const FunctionTemplate& Function) : _Function(Function) {}
			virtual ~FunctionAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionAccessorImplementation* duplicate() const { return new FunctionAccessorImplementation(_Function); }
			virtual std::string get_name() const { return typeid(FunctionAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
			virtual ValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionAccessorImplementation<ValueTemplate&, PrevValueTemplate, FunctionTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
		private:
			FunctionTemplate _Function;
		public:
			FunctionAccessorImplementation(const FunctionTemplate& Function) : _Function(Function) {}
			virtual ~FunctionAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionAccessorImplementation* duplicate() const { return new FunctionAccessorImplementation(_Function); }
			virtual std::string get_name() const { return typeid(FunctionAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual InstanceValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
			virtual ConstReferenceValueType get_member_const_reference(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
			virtual ValueType get_member_reference(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
		};		
		
	} // namespace internal
	
} // namespace variety