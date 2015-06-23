/*
 *  lazy4_Query_std_map.h
 *  Query
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Query.h"
#include "lazy4_Collection_std_map.h"
#include <map>

namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Query<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>& > : 
		public CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> CollectionStdMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Query<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>& >  : 
		public CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator>
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> CollectionStdMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Query<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template> > : 
		public CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator > 
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator > CollectionStdMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Query<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template> > : 
		public CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator > 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator > CollectionStdMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : CollectionStdMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
