/*
 *  lazy4_internal_Pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Content.h"
#include "lazy4_internal_Modifier.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template, bool is_bridge_template = true>
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
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_first((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct FirstUtility<void, true>
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
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { return false; }
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<first_template&, true>
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
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_first((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<const first_template&, true>
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
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_first((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<first_template, false>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
			
		public:
			// no use to build a unique implementation because it doesn't return a reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.first()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.first()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.first(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.at_first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.at_first(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { return bridge.exist_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { return bridge.find_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { return bridge.rfind_first((typename bridge_template::const_first_type) (first)); }
			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<first_template&, false>
		{
			typedef typename internal::Type<first_template&>::type first_type;
			typedef typename internal::Type<first_template&>::const_type const_first_type;
			typedef typename internal::Type<first_template&>::const_ref_type const_ref_first_type;
			
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.first()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.first()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.first(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.at_first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.at_first(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { return bridge.exist_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { return bridge.find_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { return bridge.rfind_first((typename bridge_template::const_first_type) (first)); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct FirstUtility<const first_template&, false>
		{
			typedef typename internal::Type<const first_template&>::type first_type;
			typedef typename internal::Type<const first_template&>::const_type const_first_type;
			typedef typename internal::Type<const first_template&>::const_ref_type const_ref_first_type;
			
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge) { return (first_type) (bridge.first()); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge) { return (const_first_type) (bridge.first()); }			
			
			template <typename bridge_template>
			static inline first_type getFirst(bridge_template& bridge, size_t steps) { return (first_type) (bridge.first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirst(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.first(steps)); }			
			
			template <typename bridge_template>
			static inline first_type getFirstWithThrow(bridge_template& bridge, size_t steps) { return (first_type) (bridge.at_first(steps)); }
			
			template <typename bridge_template>
			static inline const_first_type getConstFirstWithThrow(const bridge_template& bridge, size_t steps) { return (const_first_type) (bridge.at_first(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { return bridge.exist_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { return bridge.find_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { return bridge.rfind_first((typename bridge_template::const_first_type) (first)); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct FirstUtility<void, false>
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
			static inline bool exist_first(const bridge_template& bridge, const_ref_first_type first) { return false; }
			
			template <typename bridge_template>
			static inline bool find_first(bridge_template& bridge, const_ref_first_type first) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfind_first(bridge_template& bridge, const_ref_first_type first) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename second_template, bool is_bridge_template = true>
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
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_second((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct SecondUtility<void, true>
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
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { return false; }
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<second_template&, true>
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
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_second((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<const second_template&, true>
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
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_second((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct SecondUtility<void, false>
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
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { return false; }
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { return false; }			
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { return false; }			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<second_template, false>
		{
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.second()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.second()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.second(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.at_second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridgeat_second(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { return bridge.exist_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { return bridge.find_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { return bridge.rfind_second((typename bridge_template::const_second_type) (second)); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<second_template&, false>
		{
			typedef typename internal::Type<second_template&>::type second_type;
			typedef typename internal::Type<second_template&>::const_type const_second_type;
			typedef typename internal::Type<second_template&>::const_ref_type const_ref_second_type;
		public:
			// build a unique implementation because it returns a reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.second()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.second()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.second(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.at_second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridgeat_second(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { return bridge.exist_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { return bridge.find_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { return bridge.rfind_second((typename bridge_template::const_second_type) (second)); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct SecondUtility<const second_template&, false>
		{
			typedef typename internal::Type<const second_template&>::type second_type;
			typedef typename internal::Type<const second_template&>::const_type const_second_type;
			typedef typename internal::Type<const second_template&>::const_ref_type const_ref_second_type;
			
		public:
			// no use to build a unique implementation because it returns a const reference
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge) { return (second_type) (bridge.second()); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge) { return (const_second_type) (bridge.second()); }			
			
			template <typename bridge_template>
			static inline second_type getSecond(bridge_template& bridge, size_t steps) { return (second_type) (bridge.second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecond(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridge.second(steps)); }			
			
			template <typename bridge_template>
			static inline second_type getSecondWithThrow(bridge_template& bridge, size_t steps) { return (second_type) (bridge.at_second(steps)); }
			
			template <typename bridge_template>
			static inline const_second_type getConstSecondWithThrow(const bridge_template& bridge, size_t steps) { return (const_second_type) (bridgeat_second(steps)); }			
			
			template <typename bridge_template>
			static inline bool exist_second(const bridge_template& bridge, const_ref_second_type second) { return bridge.exist_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool find_second(bridge_template& bridge, const_ref_second_type second) { return bridge.find_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool rfind_second(bridge_template& bridge, const_ref_second_type second) { return bridge.rfind_second((typename bridge_template::const_second_type) (second)); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template, typename second_template, bool is_bridge_template = true>
		struct PairUtility
		{
		public:
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* embeddedInterface = bridge.getImplementation()) {
					return embeddedInterface->exist((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind((typename IEmbeddedInterface::const_first_type) (first), (typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct PairUtility<first_template, void, true>
		{
		public:
			typedef void second_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_first((typename IEmbeddedInterface::const_first_type) (first));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_first((typename IEmbeddedInterface::const_first_type) (first)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct PairUtility<void, second_template, true>
		{
		public:
			typedef void first_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (const IEmbeddedInterface* Collection = bridge.getImplementation()) {
					return Collection->exist_second((typename IEmbeddedInterface::const_second_type) (second));
				} else { 
					return false;
				}
			}
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->find_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				typedef typename bridge_template::interface_type IEmbeddedInterface;
				if (IEmbeddedInterface* embeddedInterface = bridge.getUniqueImplementation()) {
					return embeddedInterface->rfind_second((typename IEmbeddedInterface::const_second_type) (second)); 
				} else {
					return false;
				}
			}	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct PairUtility<void, void, true>
		{
		public:
			typedef void first_template;
			typedef void second_template;
			typedef internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
		};
		

				//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename first_template, typename second_template>
		struct PairUtility<first_template, second_template, false>
		{
		public:
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.exist((typename bridge_template::const_first_type) (first), (typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.find((typename bridge_template::const_first_type) (first), (typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.rfind((typename bridge_template::const_first_type) (first), (typename bridge_template::const_second_type) (second)); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename first_template>
		struct PairUtility<first_template, void, false>
		{
		public:
			typedef void second_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.exist_first((typename bridge_template::const_first_type) (first)); }
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.find_first((typename bridge_template::const_first_type) (first)); }
			
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.rfind_first((typename bridge_template::const_first_type) (first)); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename second_template>
		struct PairUtility<void, second_template, false>
		{
		public:
			typedef void first_template;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.exist_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.find_second((typename bridge_template::const_second_type) (second)); }
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { return bridge.rfind_second((typename bridge_template::const_second_type) (second)); }
			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <>
		struct PairUtility<void, void, false>
		{
		public:
			typedef void first_template;
			typedef void second_template;
			typedef internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef internal::Type<second_template>::const_ref_type const_ref_second_type;
			
		public:
			template <typename bridge_template>
			static inline bool exist(const bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}
			
			template <typename bridge_template>
			static inline bool find(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
			
			template <typename bridge_template>
			static inline bool rfind(bridge_template& bridge, const_ref_first_type first, const_ref_second_type second) { 
				return false;
			}	
		};
		

		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class IPair
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			
		public:
			//! @return duplicate of the current implementation
			virtual IPair* clone() const = 0;
			
		public:
			//! @return the pointer ID
			virtual const void* where() const = 0;
			
			//! @return the first
			virtual first_type getFirst() = 0;
			
			//! @return the first
			virtual const_first_type getConstFirst() const = 0;
			
			//! @return the second
			virtual second_type getSecond() = 0;
			
			//! @return the second
			virtual const_second_type getConstSecond() const = 0;
			
			//! @return true if initialized
			virtual bool good() const = 0;			
		};

		
		//--------------------------------------------------------------------------------
		//! @class Pair wraps an implementation of a forward Pair.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class PairBridge :
		public Bridge<IPair<first_template, second_template> >
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::ref_type ref_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
		public:
			typedef typename internal::IPair<first_template, second_template> IEmbeddedPair;
			typedef typename internal::Bridge<IEmbeddedPair> Bridge;
		public:
			typedef IEmbeddedPair interface_type;
			
		public:
			PairBridge() {}
			
			PairBridge(const IEmbeddedPair* implementation) : Bridge(implementation) {}
			
			PairBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline PairBridge& operator= (const IEmbeddedPair* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const PairBridge& cast(const lazy4::Pair<first_template, second_template>& pair) { return pair; }
			
			//! for compatibility
			static inline PairBridge& cast(lazy4::Pair<first_template, second_template>& pair) { return pair; }
			
			//! for compatibility
			static inline const PairBridge& cast(const PairBridge& pair) { return pair; }
			
			//! for compatibility
			static inline PairBridge& cast(PairBridge& pair) { return pair; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedPair* pair = Bridge::getImplementation()) return pair->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedPair* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedPair* clone() const { if (const IEmbeddedPair* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline ref_first_type getFirst() { return FirstUtility::getFirst(*this); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_ref_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline ref_second_type getSecond() { return SecondUtility::getSecond(*this); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_ref_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
		};	
		
		
		
		//--------------------------------------------------------------------------------
		//! @class PairWithStaticCast is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, 
		typename old_first_template, typename old_second_template>
		class PairWithStaticCast : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			
		public:
			typedef typename internal::PairBridge<old_first_template, old_second_template> PairBridge;
			
		public:
			PairBridge _bridge;
			
		public:
			PairWithStaticCast(const PairBridge& bridge) : _bridge(bridge) {}
			
			PairWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithStaticCast* clone() const { return new PairWithStaticCast(*this); }
			
		public: // IPair
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
		};
		
		//--------------------------------------------------------------------------------
		//! @class PairWithStaticCast is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename old_first_template, typename closure_template>
		class PairWithFirstAccessor :
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			
		public:
			typedef typename internal::PairBridge<old_first_template, second_template> PairBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			PairBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			PairWithFirstAccessor(const PairBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithFirstAccessor* clone() const { return new PairWithFirstAccessor(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
		};
		
		
		
		//--------------------------------------------------------------------------------
		//! @class PairWithPermutation is an implementation of a Pair to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template>
		class PairWithPermutation : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::FirstUtility<second_template> FirstUtility;
			typedef typename internal::SecondUtility<first_template> SecondUtility;
			
		public:
			typedef typename internal::PairBridge<second_template, first_template> PairBridge;
			
		public:
			PairBridge _bridge;
			
		public:
			PairWithPermutation(const PairBridge& bridge) : _bridge(bridge) {}
			
			PairWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual PairWithPermutation* clone() const { return new PairWithPermutation(*this); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return SecondUtility::getConstSecond(_bridge); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return FirstUtility::getConstFirst(_bridge); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is an implementation of IContent
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class PairWithContent : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::ref_type ref_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			
		public:
			Content<first_template> _first;
			Content<second_template> _second;
			
		public:
			PairWithContent(parameter_first_type first, parameter_second_type second) : _first(first), _second(second) {}
			
			PairWithContent() {}
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() ? _first.where() : NULL; }
			
			//! @href lazy3::internal::IImplementation::duplicate
			virtual PairWithContent* clone() const { return new PairWithContent(*this); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _first.good() && _second.good(); }
			
		public:
			//! @return the first
			virtual ref_first_type getFirst() { return _first.getContent(); }
			
			//! @return the first
			virtual const_ref_first_type getConstFirst() const { return _first.getConstContent(); }
			
			//! @return the second
			virtual ref_second_type getSecond() { return _second.getContent(); }
			
			//! @return the second
			virtual const_ref_second_type getConstSecond() const { return _second.getConstContent(); }
			
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
