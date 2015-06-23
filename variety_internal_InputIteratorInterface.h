/*
 *  variety_internal_InputIteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once
#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
				
		template <typename ValueTemplate>
		class InputIteratorInterface :
		public virtual Implementation
		{
		public:
			typedef ValueTemplate ValueType;
		public:
			ValueType get_value() const { return get_instance(); }
			virtual ValueType get_instance() const = 0;
		};
		
		
		template <typename ValueTemplate>
		class InputIteratorInterface<const ValueTemplate&> :
		public virtual InputIteratorInterface<ValueTemplate>
		{
		public:
			typedef const ValueTemplate& ValueType;
		public:
			ValueType get_value() const { return get_const_reference(); }
			virtual ValueType get_const_reference () const = 0;
		};
		
		
		template <typename ValueTemplate>
		class InputIteratorInterface<ValueTemplate&> :
		public virtual InputIteratorInterface<const ValueTemplate&>
		{
		public:
			typedef ValueTemplate& ValueType;
		public:
			ValueType get_value() const { return get_reference(); }
			virtual ValueType get_reference() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety