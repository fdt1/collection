/*
 *  lazy4_internal_Iterator_std_tr1_unordered_map.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Iterator.h"
#include "lazy4_internal_Collection.h"
#include "lazy4_internal_Collection_std_map.h"
#include "lazy4_internal_Content.h"
#include <tr1/unordered_map>

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class IteratorStdTr1UnorderedMap : 
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
			IteratorStdTr1UnorderedMap() : _mapBridge(new Content<content_template>())/*, _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) */ {}
			
			IteratorStdTr1UnorderedMap(parameter_content_type content) : _mapBridge(new Content<content_template>(content)), _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
			IteratorStdTr1UnorderedMap(const ContentBridge<content_template>& content) : _mapBridge(content.isValid() ? content : new Content<content_template>()), _iteratorBridge(const_cast<ref_content_type>(getConstMap()).begin()) {}
			
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
			virtual const void* getID() const { return isValid() && getConstIterator() != getConstMap().end() ? &(getConstIterator()->first) : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return (getIterator())->first; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return (getConstIterator())->first; }
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool findFirst(const_ref_first_type first) { 
				iterator_template end = const_cast<ref_content_type>(getMap()).end();
				ref_iterator_type current_it = getIterator();
				if (isValid() && current_it != end && current_it->first <= first) { 
					iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
					if (it != end) {
						_iteratorBridge = it;
						return true;
					}
					_iteratorBridge = end;
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::rfindFirst implementation.
			virtual bool rfindFirst(const_ref_first_type first) { 
				iterator_template end = const_cast<ref_content_type>(getMap()).end();
				ref_iterator_type current_it = getIterator();
				if (isValid() && (current_it == end || current_it->first >= first)) { 
					iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
					if (it != end) {
						_iteratorBridge = it;
						return true;
					}
					_iteratorBridge = end;
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return (getIterator())->second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return (getConstIterator())->second; }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool findSecond(const_ref_second_type second) { 
				if (isValid()) { 
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
			virtual bool rfindSecond(const_ref_second_type second) { 
				if (isValid()) { 
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
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
				ref_iterator_type current_it = getIterator();
				if (isValid() && current_it != end && current_it->first <= first) { 
					iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
					if (it != end && it->second == second) {
						_iteratorBridge = it;
						return true;
					}
					_iteratorBridge = end;
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { 
				iterator_template end = const_cast<ref_content_type>(getConstMap()).end();
				ref_iterator_type current_it = getIterator();
				if (isValid() && (current_it == end || current_it->first >= first)) { 
					iterator_template it = const_cast<ref_content_type>(getConstMap()).find((key_type) first);
					
					if (it != end && it->second == second) {
						_iteratorBridge = ++it;
						return true;
					}
					_iteratorBridge = end;
				}
				return false;
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _mapBridge.isValid() && _iteratorBridge.isValid(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const { return getConstIterator() == getConstMap().begin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return getConstIterator() == getConstMap().end(); }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (isValid()) { 
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
				if (isValid()) { 
					_iteratorBridge = (const_cast<ref_content_type>(getConstMap()).end()); 
				}
			}
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (isValid()) { 
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
				if (isValid()) { 
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
				if (isValid()) { 
					this->_iteratorBridge = (const_cast<ref_content_type>(getConstMap()).begin()); 
				}
			}
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const  { 
				if (isValid()) { 
					return std::distance(getConstIterator(), const_cast<ref_content_type>(getConstMap()).end()); 
				} else {
					return 0;
				}
			}
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::tr1::unordered_map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc, bool __cache_hash_code>
		class Iterator<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>& > : 
		public IteratorStdTr1UnorderedMap<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>&, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::const_iterator> 
		{
		public:
			typedef const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdTr1UnorderedMap<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>&, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::const_iterator> IteratorStdTr1UnorderedMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdTr1UnorderedMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::tr1::unordered_map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc, bool __cache_hash_code>
		class Iterator<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>& >  : 
		public IteratorStdTr1UnorderedMap<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>&, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::iterator>
		{
		public:
			typedef std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdTr1UnorderedMap<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>&, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::iterator> IteratorStdTr1UnorderedMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdTr1UnorderedMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::tr1::unordered_map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc, bool __cache_hash_code>
		class Iterator<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code> > : 
		public IteratorStdTr1UnorderedMap<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::iterator> 
		{
		public:
			typedef std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdTr1UnorderedMap<first_template, second_template, std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::iterator> IteratorStdTr1UnorderedMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdTr1UnorderedMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::tr1::unordered_map and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename _Hash, typename _Pred, typename _Alloc, bool __cache_hash_code>
		class Iterator<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code> > : 
		public IteratorStdTr1UnorderedMap<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::const_iterator> 
		{
		public:
			typedef const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdTr1UnorderedMap<first_template, second_template, const std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>, typename std::tr1::unordered_map<key_template, value_template, _Hash, _Pred, _Alloc, __cache_hash_code>::const_iterator> IteratorStdTr1UnorderedMap;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdTr1UnorderedMap(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdTr1UnorderedMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
