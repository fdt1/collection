/*
 *  lazy4_internal_SecondUtility.h
 *  collection
 *
 *  Created by Francois et Fabienne on 03/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility
		{
		public:
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
		
		public:
			// no use to build a unique implementation because it doesn't return a reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.getImplementation()->getConstSecond()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.getImplementation()->getConstSecond()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getImplementation()->getConstSecond(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecond(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getImplementation()->getConstSecondWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecondWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existSecond(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existSecond((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findSecond(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	

			template <typename bridge_template>
			static inline bool rfindSecond(bridge_template& bridge, const_ref_second_type second) { 
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
		struct SecondUtility<void>
		{
			typedef void second_template;
			typedef internal::Type<second_template>::type second_type;
			typedef internal::Type<second_template>::const_type const_second_type;
			typedef internal::Type<second_template>::const_ref_type const_ref_second_type;
		
		public:
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { static second_type second = NULL; return second; }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { static second_type second = NULL; return second; }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { static second_type second = NULL; return second; }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { static second_type second = NULL; return second; }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { static second_type second = NULL; return second; }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { static second_type second = NULL; return second; }			
			
			template <typename bridge_template>
			static inline bool existSecond(const bridge_template& bridge, const_ref_second_type second) { return false; }
			
			template <typename bridge_template>
			static inline bool findSecond(bridge_template& bridge, const_ref_second_type second) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfindSecond(bridge_template& bridge, const_ref_second_type second) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<second_template&>
		{
			typedef typename internal::Type<second_template&>::type second_type;
			typedef typename internal::Type<second_template&>::const_type const_second_type;
			typedef typename internal::Type<second_template&>::const_ref_type const_ref_second_type;
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.getUniqueImplementation()->getSecond()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.getImplementation()->getConstSecond()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getUniqueImplementation()->getSecond(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecond(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getUniqueImplementation()->getSecondWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecondWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existSecond(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existSecond((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findSecond(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindSecond(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<const second_template&>
		{
			typedef typename internal::Type<const second_template&>::type second_type;
			typedef typename internal::Type<const second_template&>::const_type const_second_type;
			typedef typename internal::Type<const second_template&>::const_ref_type const_ref_second_type;
		
		public:
			// no use to build a unique implementation because it returns a const reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.getImplementation()->getConstSecond()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.getImplementation()->getConstSecond()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getImplementation()->getConstSecond(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecond(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.getImplementation()->getConstSecondWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.getImplementation()->getConstSecondWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existSecond(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existSecond((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findSecond(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindSecond(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindSecond((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
	} // namespace internal
	
} // namespace lazy4