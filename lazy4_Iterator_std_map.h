/*
 *  lazy4_internal_Iterator_std_map.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/03/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_Iterator.h"
#include "lazy4_Collection_std_map.h"
#include <map>

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class IteratorStdMap : 
		public IIterator<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IEmbeddedIterator;
			typedef content_template input_template;
			typedef IEmbeddedIterator* output_template;			
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
			typedef typename internal::Collection<first_template, second_template, content_template> Collection;
			typedef typename internal::ICollection<first_template, second_template, content_template> ICollection;
			typedef typename internal::Type<iterator_template>::ref_type ref_iterator_type;
			typedef typename internal::Type<iterator_template>::const_ref_type const_ref_iterator_type;
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator; 
			
		public:
			ContentBridge<content_template> _mapBridge;
			Content<iterator_template> _iteratorBridge;
			
		public:
			IteratorStdMap() : _mapBridge(new Content<content_template>())/*, _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) */ {}
			
			IteratorStdMap(parameter_content_type content) : _mapBridge(new Content<content_template>(content)), _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
			IteratorStdMap(const ContentBridge<content_template>& content) : _mapBridge(content.good() ? content : new Content<content_template>()), _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
		public:
			inline ref_content_type getMap() { return _mapBridge.getContent(); }
			
			inline const_ref_content_type getConstMap() const { return _mapBridge.getConstContent(); }
			
			inline ref_iterator_type getIterator() { return _iteratorBridge.getContent(); }
			
			inline const_ref_iterator_type getConstIterator() const { return _iteratorBridge.getConstContent(); }
			
		public:
			//! @return build the corresponding collection
			virtual Collection* cloneCollection() const { return new Collection(_mapBridge); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Iterator(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Iterator(input); }
			
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
					ref_iterator_type current_it = getIterator();
					if (current_it != end && current_it->first <= first) { 
						iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
						if (it != end) {
							_iteratorBridge = it;
							return true;
						}
						_iteratorBridge = end;
					}
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::rfindFirst implementation.
			virtual bool rfind_first(const_ref_first_type first) { 
				if (good()) {
					iterator_template end = const_cast<ref_content_type>(getMap()).end();
					ref_iterator_type current_it = getIterator();
					if (current_it == end || current_it->first >= first) { 
						iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
						if (it != end) {
							_iteratorBridge = it;
							return true;
						}
						_iteratorBridge = end;
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
			
			//! @href lazy3::internal::IPairOnFirst::rfindSecond implementation.
			virtual bool rfind_second(const_ref_second_type second) { 
				if (good()) { 
					ref_iterator_type it = getIterator();
					iterator_template begin = const_cast<ref_content_type>(getConstMap()).begin();
					while (it != begin) {
						--it;
						if (it->second == second) {
							++it;
							return true;
						}
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
							_iteratorBridge = it;
							return true;
						}
						_iteratorBridge = end;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) {
					iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
					ref_iterator_type current_it = getIterator();
					if (current_it == end || current_it->first >= first) { 
						iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
						if (it != end && it->second == second) {
							_iteratorBridge = ++it;
							return true;
						}
						_iteratorBridge = end;
					}
				}
				return false;
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _mapBridge.good() && _iteratorBridge.good(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return getConstIterator() == getConstMap().begin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return getConstIterator() == getConstMap().end(); }
			
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
					_iteratorBridge = (const_cast<ref_content_type>(getConstMap()).end()); 
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
			
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getMap(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstMap(); }
			
		public:
			//! @href lazy3::internal::IIteratorOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (good()) { 
					iterator_template begin = const_cast<ref_content_type>(getConstMap()).begin();
					ref_iterator_type it = getIterator();
					size_t left = 0;
					while (it != begin && left != steps) {
						++left;
						--it;
					}
					return left;
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::rewind implementation.
			virtual void rewind() { 
				if (good()) { 
					this->_iteratorBridge = (const_cast<ref_content_type>(getConstMap()).begin()); 
				}
			}
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const  { 
				if (good()) { 
					return std::distance(getConstIterator(), const_cast<ref_content_type>(getConstMap()).end()); 
				} else {
					return 0;
				}
			}
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Iterator<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>& > : 
		public IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> IteratorStdMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Iterator<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>& >  : 
		public IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator>
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> IteratorStdMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Iterator<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template> > : 
		public IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> 
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> IteratorStdMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Iterator<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template> > : 
		public IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> IteratorStdMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
				
	} // namespace internal
	
	
} // namespace lazy4
