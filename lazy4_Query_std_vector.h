/*
 *  lazy4_Query_std_vector.h
 *  Query
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Query.h"
#include "lazy4_Collection_std_vector.h"
#include <vector>

namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::vector and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Query<first_template, second_template, const std::vector<element_template, allocator_template>& > : 
		public CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&> 
		{
		public:
			typedef const std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&> CollectionStdVector;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdVector(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::vector and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Query<first_template, second_template, std::vector<element_template, allocator_template>& >  : 
		public CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template>&>
		{
		public:
			typedef std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template>&> CollectionStdVector;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdVector(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::vector and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Query<first_template, second_template, std::vector<element_template, allocator_template> > : 
		public CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template> > 
		{
		public:
			typedef std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template> > CollectionStdVector;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdVector(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::vector and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Query<first_template, second_template, const std::vector<element_template, allocator_template> > : 
		public CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template> > 
		{
		public:
			typedef const std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template> > CollectionStdVector;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdVector(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getVector()); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
