/*
 *  variety_internal_FunctionDatumAccessorImplementation.h
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
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionDatumAccessorImplementation : 
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
			FunctionTemplate _Function;
			DatumType _datum;
		public:
			FunctionDatumAccessorImplementation(const FunctionTemplate& Function, const DatumType& datum) : _Function(Function), _datum(datum) {}
			virtual ~FunctionDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionDatumAccessorImplementation* duplicate() const { return new FunctionDatumAccessorImplementation(_Function, _datum); }
			virtual std::string get_name() const { return typeid(FunctionDatumAccessorImplementation).name(); }
		public:
			// InputAccessorInterface
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const 
			{ 
				return (*_Function)(prev_value);
			}
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionDatumAccessorImplementation<const ValueTemplate&, PrevValueTemplate, DatumTemplate, FunctionTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual SetDatumAccessorInterface<DatumTemplate>,
		public Implementation
		{
		public:
			typedef const ValueTemplate& ValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef typename GenericTraits<DatumTemplate>::ValueType DatumType;
		private:
			FunctionTemplate _Function;
			DatumType _datum;
		public:
			FunctionDatumAccessorImplementation(const FunctionTemplate& Function, const DatumType& datum) : _Function(Function), _datum(datum) {}
			virtual ~FunctionDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionDatumAccessorImplementation* duplicate() const { return new FunctionDatumAccessorImplementation(_Function, _datum); }
			virtual std::string get_name() const { return typeid(FunctionDatumAccessorImplementation).name(); }
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
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate, typename FunctionTemplate, typename BridgeTemplate>
		class FunctionDatumAccessorImplementation<ValueTemplate&, PrevValueTemplate, DatumTemplate, FunctionTemplate, BridgeTemplate> : 
		public virtual BridgeTemplate,
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual SetDatumAccessorInterface<DatumTemplate>,
		public Implementation
		{
		public:
			typedef ValueTemplate& ValueType;
			typedef const ValueTemplate& ConstReferenceValueType;
			typedef ValueTemplate InstanceValueType;
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef typename GenericTraits<DatumTemplate>::ValueType DatumType;
		private:
			FunctionTemplate _Function;
			DatumType _datum;
		public:
			FunctionDatumAccessorImplementation(const FunctionTemplate& Function, const DatumType& datum) : _Function(Function), _datum(datum) {}
			virtual ~FunctionDatumAccessorImplementation() {}
		public:
			// Implementation
			virtual FunctionDatumAccessorImplementation* duplicate() const { return new FunctionDatumAccessorImplementation(_Function, _datum); }
			virtual std::string get_name() const { return typeid(FunctionDatumAccessorImplementation).name(); }
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
		public:
			// SetDatumAccessorInterface
			virtual void set_datum(const DatumType& value) const { _datum = value; }
			virtual const DatumType& get_datum() const { return _datum; }
		};		
		
	} // namespace internal
	
} // namespace variety