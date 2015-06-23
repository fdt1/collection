/*
 *  lazy_internal_FilterImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_Implementation.h"


namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ContainerTemplate>
		class ModifierImplementation : 
		public virtual InterfaceTemplate,
		public virtual ModifierInterface,
		public virtual Implementation
		{
		protected:
			typename typename InterfaceTemplate::Iterator IteratorType;
		private:
			InterfaceTemplate _bridge;
		public:
			ModifierImplementation(const InterfaceTemplate& bridge) : _bridge(bridge) {}
		public:
			virtual size_t increment_at(size_t index) {
				while (index != 0) {
					if (!_bridge.is_valid()) {
						return index;
					}
					if (!_bridge.is_skipped()) {
						--index;
					}
					_bridge.increment();
				}
				return 0;
			}
			
			virtual boolean is_skipped() {
				// TODO ....
			}
			
			virtual boolean is_valid() const {
				while (_bridge.is_skipped()) {
					if (!_bridge.is_valid()) {
						return false;
					}
					_bridge.increment();
				}
				
				return _bridge.is_valid();
			}
			
			virtual size_t get_size() const {
				size_t size = 0;
				for (InterfaceTemplate bridge2 = _bridge.duplicate(); bridge2.is_valid(); bridge2.increment_at(1)) {
					if (!bridge2.is_skipped()) {
						++size;
					}
				}
			}
			
			virtual ConstValueType get_value() const {
				for (InterfaceTemplate bridge2 = _bridge.duplicate(); bridge2.is_valid(); bridge2.increment_at(1)) {
					if (!bridge2.is_skipped()) {
						return bridge2.get_value();
					}
				}
				return bridge2.get_value();
			}
			
			virtual ValueType get_value() {
				for (InterfaceTemplate bridge2 = _bridge.duplicate(); bridge2.is_valid(); bridge2.increment_at(1)) {
					if (!bridge2.is_skipped()) {
						return bridge2.get_value();
					}
				}
				return bridge2.get_value();
			}
			
			virtual InterfaceTemplate* get_begin() const {
				InterfaceTemplate bridge2 = _bridge.duplicate();
				for (; bridge2.is_valid(); bridge2.increment_at(1)) {
					if (!bridge2.is_skipped()) {
						return bridge2;
					}
				}
				return bridge2;
			}
			
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy