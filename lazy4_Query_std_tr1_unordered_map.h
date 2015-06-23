/*
 *  lazy4_internal_Query_std_tr1_unordered_map.h
 *  Query
 *
 *  Created by Francois et Fabienne on 17/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Query.h"
#include "lazy4_Flow_std_tr1_unordered_map.h"

#if defined( _MSC_VER )
#include <unordered_map>
#else
#include <tr1/unordered_map>
namespace std { namespace tr1 { using namespace std; } }
#endif

namespace lazy4 {
	
	namespace internal {

		
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class QueryStdTr1UnorderedMap : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
			typedef typename internal::Type<content_template>::prime_type::const_iterator const_Query_type;
			typedef typename internal::Type<content_template>::prime_type::iterator Query_type;
			typedef typename internal::Type<content_template>::prime_type::key_type key_type;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:		
			typedef typename internal::Query<first_template, second_template, content_template> Query; 
			typedef typename internal::Flow<first_template, second_template, content_template> Flow; 
			typedef typename internal::IFlow<first_template, second_template, content_template> IFlow;
			
		public:
			ContentBridge<content_template> _mapBridge;
			
		public:
			QueryStdTr1UnorderedMap() : _mapBridge(new Content<content_template>()) {}
			
			QueryStdTr1UnorderedMap(parameter_content_type content) : _mapBridge(new Content<content_template>(content)) {}
			
			QueryStdTr1UnorderedMap(const ContentBridge<content_template>& content) : _mapBridge(content) {}
			
		public:
			inline ref_content_type getMap() { return _mapBridge.getContent(); }
			
			inline const_ref_content_type getConstMap() const { return _mapBridge.getConstContent(); }
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual IFlow* cloneIterator() const { return new Flow(_mapBridge); }			
			
			//! @return the pointer ID
			virtual const void* where() const { return _mapBridge.where(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { 
				iterator_template it = getMap().begin();
				while (steps != 0) {
					++it;
					--steps;
				}
				return it->first;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const {
				const_Query_type it = getConstMap().begin();
				while (steps != 0) {
					++it;
					--steps;
				}
				return it->first;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) {
				iterator_template it = getMap().begin();
				while (steps != 0) {
					++it;
					--steps;
				}
				return it->second;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const {
				const_Query_type it = getConstMap().begin();
				while (steps != 0) {
					++it;
					--steps;
				}
				return it->second;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { 
				if (good()) { 
					iterator_template end = getMap().end();
					iterator_template it = getMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->first;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Query::out of range");
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				if (good()) { 
					const_Query_type end = getConstMap().end();
					const_Query_type it = getConstMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->first;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Query::out of range");
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { 
				if (good()) { 
					iterator_template end = getMap().end();
					iterator_template it = getMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->second;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Query::out of range");
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				if (good()) { 
					const_Query_type end = getConstMap().end();
					const_Query_type it = getConstMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->second;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Query::out of range");
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _mapBridge.good(); }
			
			//! @return true if the Query is at the beginning.
			virtual size_t size() const { return good() ? getConstMap().size() : 0; }
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { return good() ? getConstMap().empty() : true; }
			
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getMap(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstMap(); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return getConstMap().find((key_type) first) != getConstMap().end(); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (good()) { 
					const_Query_type end = getConstMap().end();
					const_Query_type it = getConstMap().begin();
					while (it != end) {
						if (it->second == second) {
							return true;
						}
						++it;
					}
				}
				return false;
			}
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (good()) { 
					const_Query_type end = getConstMap().end();
					const_Query_type it = getConstMap().find((key_type) first);
					return it != end && it->second == second;
				}
				return false;
			}
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Query(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Query(input); }
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::unordered_map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc>
		class Query<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>& > : 
		public QueryStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>&, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::const_iterator> 
		{
		public:
			typedef const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::QueryStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>&, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::const_iterator> QueryStdTr1UnorderedMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : QueryStdTr1UnorderedMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : QueryStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::unordered_map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc>
		class Query<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>& >  : 
		public QueryStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>&, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::iterator>
		{
		public:
			typedef std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::QueryStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>&, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::iterator> QueryStdTr1UnorderedMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : QueryStdTr1UnorderedMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : QueryStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::unordered_map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc>
		class Query<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc> > : 
		public QueryStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::iterator > 
		{
		public:
			typedef std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::QueryStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::iterator > QueryStdTr1UnorderedMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : QueryStdTr1UnorderedMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : QueryStdTr1UnorderedMap(content) {}
			
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class QueryAdapter specialization. It wraps here std::unordered_map and its Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc>
		class Query<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc> > : 
		public QueryStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::const_iterator > 
		{
		public:
			typedef const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::QueryStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>, typename std::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc>::const_iterator > QueryStdTr1UnorderedMap;
			
		public:
			Query() {}
			
			Query(parameter_content_type content) : QueryStdTr1UnorderedMap(content) {}
			
			Query(const ContentBridge<content_template>& content) : QueryStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(const_cast<Query*>(this)->getMap()); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
