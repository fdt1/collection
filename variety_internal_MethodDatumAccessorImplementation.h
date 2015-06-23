/*
 *  variety_internal_MethodDatumAccessorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/02/11.
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
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodDatumAccessorImplementation : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual SetDatumAccessorInterface<DatumTemplate>,
		public Implementation
		{
		public:
			typedef ValueTemplate ValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef typename GenericTraits<DatumTemplate>::ValueType DatumType;
		private:
			DatumType _datum;
			MethodTemplate _method;
		public:
			MethodDatumAccessorImplementation(const MethodTemplate& method, const DatumType& datum) : _method(method), _datum(datum) {}
			virtual ~MethodDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodDatumAccessorImplementation* duplicate() const { return new MethodDatumAccessorImplementation(_method, _datum); }
			virtual std::string get_name() const { return typeid(MethodDatumAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (get_pointer_to_reference(prev_value).*_method)();
			}
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodDatumAccessorImplementation<const ValueTemplate&, PrevValueTemplate, DatumTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual SetDatumAccessorInterface<DatumTemplate>,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef typename GenericTraits<DatumTemplate>::ValueType DatumType;
		private:
			MethodTemplate _method;
			DatumType _datum;
		public:
			MethodDatumAccessorImplementation(const MethodTemplate& method, const DatumType& datum) : _method(method), _datum(datum) {}
			virtual ~MethodDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodDatumAccessorImplementation* duplicate() const { return new MethodDatumAccessorImplementation(_method, _datum); }
			virtual std::string get_name() const { return typeid(MethodDatumAccessorImplementation).name(); }
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
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename MethodTemplate, typename BridgeTemplate>
		class MethodDatumAccessorImplementation<ValueTemplate&, PrevValueTemplate, DatumTemplate, MethodTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual SetDatumAccessorInterface<DatumTemplate>,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef typename GenericTraits<DatumTemplate>::ValueType DatumType;
		private:
			MethodTemplate _method;
			DatumType _datum;
		public:
			MethodDatumAccessorImplementation(const MethodTemplate& method, const DatumType& datum) : _method(method), _datum(datum) {}
			virtual ~MethodDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual MethodDatumAccessorImplementation* duplicate() const { return new MethodDatumAccessorImplementation(_method, _datum); }
			virtual std::string get_name() const { return typeid(MethodDatumAccessorImplementation).name(); }
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
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
	} // namespace internal
	
} // namespace variety