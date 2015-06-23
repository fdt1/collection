/*
 *  lazy4_internal_FirstUtility.h
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
		template <typename first_template>
		struct FirstUtility
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
		
		public:
			// no use to build a unique implementation because it doesn't return a reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.getImplementation()->getConstFirst()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.getImplementation()->getConstFirst()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getImplementation()->getConstFirst(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirst(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getImplementation()->getConstFirstWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirstWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existFirst(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existFirst((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findFirst(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindFirst(bridge_template& bridge, const_ref_first_type first) { 
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
		template <>
		struct FirstUtility<void>
		{
			typedef void first_template;
			typedef internal::Type<first_template>::type first_type;
			typedef internal::Type<first_template>::const_type const_first_type;
			typedef internal::Type<first_template>::const_ref_type const_ref_first_type;
		
		public:
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { static first_type first = NULL; return first; }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { static first_type first = NULL; return first; }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { static first_type first = NULL; return first; }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { static first_type first = NULL; return first; }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { static first_type first = NULL; return first; }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { static first_type first = NULL; return first; }			
			
			template <typename bridge_template>
			static inline bool existFirst(const bridge_template& bridge, const_ref_first_type first) { return false; }
			
			template <typename bridge_template>
			static inline bool findFirst(bridge_template& bridge, const_ref_first_type first) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfindFirst(bridge_template& bridge, const_ref_first_type first) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<first_template&>
		{
			typedef typename internal::Type<first_template&>::type first_type;
			typedef typename internal::Type<first_template&>::const_type const_first_type;
			typedef typename internal::Type<first_template&>::const_ref_type const_ref_first_type;
		
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.getUniqueImplementation()->getFirst()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.getImplementation()->getConstFirst()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getUniqueImplementation()->getFirst(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirst(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getUniqueImplementation()->getFirstWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirstWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existFirst(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existFirst((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findFirst(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindFirst(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<const first_template&>
		{
			typedef typename internal::Type<const first_template&>::type first_type;
			typedef typename internal::Type<const first_template&>::const_type const_first_type;
			typedef typename internal::Type<const first_template&>::const_ref_type const_ref_first_type;
		
		public:
			// no use to build a unique implementation because it returns a const reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.getImplementation()->getConstFirst()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.getImplementation()->getConstFirst()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getImplementation()->getConstFirst(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirst(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.getImplementation()->getConstFirstWithThrow(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.getImplementation()->getConstFirstWithThrow(steps)); }			
			
			template <typename bridge_template>
			static inline bool existFirst(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->existFirst((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool findFirst(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->findFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfindFirst(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfindFirst((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
	} // namespace internal
	
} // namespace lazy4