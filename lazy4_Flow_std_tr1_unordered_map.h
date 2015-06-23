/*
 *  lazy4_internal_Flow_std_tr1_unordered_map.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_Flow.h"

#if defined( _MSC_VER )
#include <unordered_map>
#else
#include <tr1/unordered_map>
namespace std { namespace tr1 { using namespace std; } }
#endif

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class FlowStdTr1UnorderedMap : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
			typedef typename internal::Type<content_template>::prime_type::key_type key_type;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			
		public:		
			typedef typename internal::Type<iterator_template>::ref_type ref_iterator_type;
			typedef typename internal::Type<iterator_template>::const_ref_type const_ref_iterator_type;
			typedef typename internal::Flow<first_template, second_template, content_template> Flow; 
			
		public:
			ContentBridge<content_template> _mapBridge;
			Content<iterator_template> _FlowBridge;
			
		public:
			FlowStdTr1UnorderedMap() : _mapBridge(new Content<content_template>())/*, _FlowBridge(const_cast<ref_content_type>(getConstMap()).begin()) */ {}
			
			FlowStdTr1UnorderedMap(parameter_content_type content) : _mapBridge(new Content<content_template>(content)), _FlowBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
			FlowStdTr1UnorderedMap(const ContentBridge<content_template>& content) : _mapBridge(content.good() ? content : new Content<content_template>()), _FlowBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
		public:
			inline ref_content_type getMap() { return _mapBridge.getContent(); }
			
			inline const_ref_content_type getConstMap() const { return _mapBridge.getConstContent(); }
			
			inline ref_iterator_type getIterator() { return _FlowBridge.getContent(); }
			
			inline const_ref_iterator_type getConstIterator() const { return _FlowBridge.getConstContent(); }
						
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Flow(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Flow(input); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() && getConstIterator() != getConstMap().end() ? &(getConstIterator()->first) : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return (getIterator())->first; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return (getConstIterator())->first; }
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool find_first(const_ref_first_type first) { 
				if (good()) {
					iterator_template end = const_cast<ref_content_type>(getMap()).end();
					iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
					if (it != end) {
						ref_iterator_type current_it = getIterator();
						if (getMap().begin() == current_it) {
							current_it = it;
							return true;
						} else {
							while (current_it != end) {
								if (current_it == it) {
									return true;
								}
								++current_it;
							}
						}
					} else {
						_FlowBridge = end;
					}
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return (getIterator())->second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return (getConstIterator())->second; }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool find_second(const_ref_second_type second) { 
				if (good()) { 
					iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
					ref_iterator_type it = getIterator();
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
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) {
					iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
					ref_iterator_type current_it = getIterator();
					if (current_it != end && current_it->first <= first) { 
						iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
						if (it != end && it->second == second) {
							_FlowBridge = it;
							return true;
						}
						_FlowBridge = end;
					}
				}
				return false;
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _mapBridge.good() && _FlowBridge.good(); }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (good()) { 
					iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
					ref_iterator_type it = getIterator();
					size_t left = 0;
					while (it != end && left != steps) {
						++left;
						++it;
					}
					return left;
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { 
				if (good()) { 
					_FlowBridge = (const_cast<ref_content_type>(getConstMap()).end()); 
				}
			}
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (good()) { 
					return std::distance(const_cast<ref_content_type>(getConstMap()).begin(), getConstIterator()); 
				} else {
					return 0;
				}
			}
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return getConstIterator() == getConstMap().end(); }
			
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getMap(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstMap(); }
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::unordered_map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template>& > : 
		public FlowStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template>&, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::unordered_map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::FlowStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template>&, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::const_iterator> FlowStdTr1UnorderedMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdTr1UnorderedMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::unordered_map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template>& >  : 
		public FlowStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template>&, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::iterator>
		{
		public:
			typedef std::unordered_map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::FlowStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template>&, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::iterator> FlowStdTr1UnorderedMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdTr1UnorderedMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::unordered_map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template> > : 
		public FlowStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template>, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::iterator> 
		{
		public:
			typedef std::unordered_map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::FlowStdTr1UnorderedMap<first_template, second_template, std::unordered_map<key_template, value_template, compare_template, allocator_template>, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::iterator> FlowStdTr1UnorderedMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdTr1UnorderedMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::unordered_map and its Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Flow<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template> > : 
		public FlowStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template>, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::unordered_map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::FlowStdTr1UnorderedMap<first_template, second_template, const std::unordered_map<key_template, value_template, compare_template, allocator_template>, typename std::unordered_map<key_template, value_template, compare_template, allocator_template>::const_iterator> FlowStdTr1UnorderedMap;
			
		public:
			Flow() {}
			
			Flow(parameter_content_type content) : FlowStdTr1UnorderedMap(content) {}
			
			Flow(const ContentBridge<content_template>& content) : FlowStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
