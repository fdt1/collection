/*
 *  variety_internal_InputAccessorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_GenericTraits.h"
#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorInterface :
		public virtual Implementation 
		{
		public:
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef ValueTemplate ValueType;
		public:
			ValueType get_member(const PrevValueType& prev_value) const { return get_member_instance(prev_value); }
			virtual ValueType get_member_instance(const PrevValueType& prev_value) const = 0;
		};
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorInterface<const ValueTemplate&, PrevValueTemplate> :
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>
		{
		public:
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef const ValueTemplate& ValueType;
		public:
			ValueType get_member(const PrevValueType& prev_value) const { return get_member_const_reference(prev_value); }
			virtual ValueType get_member_const_reference(const PrevValueType& prev_value) const = 0;
		};
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class InputAccessorInterface<ValueTemplate&, PrevValueTemplate> :
		public virtual InputAccessorInterface<const ValueTemplate&, PrevValueTemplate>
		{
		public:
			typedef typename GenericTraits<PrevValueTemplate>::ValueType PrevValueType;
			typedef ValueTemplate& ValueType;
		public:
			ValueType get_member(const PrevValueType& prev_value) const { return get_member_reference(prev_value); }
			virtual ValueType get_const_reference(const PrevValueType& prev_value) const = 0;
		};
		
	} // namespace internal
	
	
} // namespace variety