/*
 *  lazy4_internal_PairUtility.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/02/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template, typename second_template>
		struct PairUtility
		{
		public:
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool existPair(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* embeddedInterface = bridge.getImplementation()) {
					return embeddedInterface->existPair((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findPair((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindPair((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};

		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct PairUtility<first_template, void>
		{
		public:
			typedef void second_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool existPair(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existFirst((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct PairUtility<void, second_template>
		{
		public:
			typedef void first_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool existPair(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existSecond((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct PairUtility<void, void>
		{
		public:
			typedef void first_template;
			typedef void second_template;
			typedef internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool existPair(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}
			
			template <typename bridge_template>
			static inline bool findPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
			
			template <typename bridge_template>
			static inline bool rfindPair(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
		};
		
		
		
	} // namespace internal
	
} // namespace lazy4