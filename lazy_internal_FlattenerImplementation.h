/*
 *  lazy_internal_FlattenerImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_ModifierImplementation.h"
#include "lazy_internal_GenericBridge.h"


namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ContainerTemplate>
		class FlattenerImplementation : 
		public virtual ModifierImplementation
		{
		protected:
			GenericBridge _iterator;
		public:
			FlattenerImplementation(const GenericBridge& modified) : ModifierImplementation(modified), _iterator(NULL) {}
		public:
			// Implementation
			virtual FlattenerImplementation* duplicate() const { return new FlattenerImplementation(*this); }
		public:
			virtual size_t increment_at(size_t index) {
				if (_iterator == NULL) {
					_iterator = _modified.get_value().get_begin();
				}
				while ((index -= _iterator.increment_at(index)) != 0) {
					if (!_modified.is_valid()) {
						return index;
					}
					_modified.increment(1);
					_iterator = _modified.get_value().get_begin();
				}
				
				return 0;
			}
			
			virtual GenericBridge get_begin() const {
				return GenericBridge(this);
			}
			
			virtual boolean is_valid() const {
				return _modified.is_valid();
			}
			
			virtual ConstValueType get_value() const {
				if (_iterator == NULL) {
					_iterator = _modified.get_value().get_begin();
				}
				return _iterator.get_value();
			}
			
			virtual ValueType get_value() {
				if (_iterator == NULL) {
					_iterator = _modified.get_value().get_begin();
				}				
				return _iterator.get_value();
			}
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy