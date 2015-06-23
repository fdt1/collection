/*
 *  lazy4_internal_Flow_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once


#include "lazy4_Flow.h"
#include "lazy4_Iterator_std_vector.h"

#include <vector>

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Flow<first_template, second_template, const std::vector<element_template, allocator_template>& > : 
		public IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::const_iterator> FlowStdVector;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdVector(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Flow<first_template, second_template, std::vector<element_template, allocator_template>& >  : 
		public IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::iterator>
		{
		public:
			typedef std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::iterator> FlowStdVector;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdVector(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Flow<first_template, second_template, std::vector<element_template, allocator_template> > : 
		public IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::iterator> 
		{
		public:
			typedef std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::iterator> FlowStdVector;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdVector(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Flow<first_template, second_template, const std::vector<element_template, allocator_template> > : 
		public IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::const_iterator> FlowStdVector;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdVector(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
