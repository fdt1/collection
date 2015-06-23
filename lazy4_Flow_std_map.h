/*
 *  lazy4_internal_Flow_std_map.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy4_Flow.h"
#include "lazy4_Iterator_std_map.h"
#include <map>

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>& > : 
		public IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> FlowStdMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>& >  : 
		public IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator>
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> FlowStdMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template> > : 
		public IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> 
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> FlowStdMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template> > : 
		public IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> FlowStdMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4