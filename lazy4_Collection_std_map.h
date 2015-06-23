/*
 *  lazy4_internal_Collection_std_map.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/03/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Collection.h"
#include "lazy4_Iterator_std_map.h"
#include <map>

namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class CollectionStdMap : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			typedef typename internal::Type<content_template>::prime_type::const_iterator const_iterator_type;
			typedef typename internal::Type<content_template>::prime_type::iterator iterator_type;
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
			typedef typename internal::Collection<first_template, second_template, content_template> Collection; 
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator;
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			
		public:
			ContentBridge<content_template> _mapBridge;
			
		public:
			CollectionStdMap() : _mapBridge(new Content<content_template>()) {}
			
			CollectionStdMap(parameter_content_type content) : _mapBridge(new Content<content_template>(content)) {}
			
			CollectionStdMap(const ContentBridge<content_template>& content) : _mapBridge(content) {}
			
		public:
			inline ref_content_type getMap() { return _mapBridge.getContent(); }
			
			inline const_ref_content_type getConstMap() const { return _mapBridge.getConstContent(); }
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual IIterator* cloneIterator() const { return new Iterator(_mapBridge); }			
			
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
				const_iterator_type it = getConstMap().begin();
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
				const_iterator_type it = getConstMap().begin();
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
				throw std::out_of_range("Collection::out of range");
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				if (good()) { 
					const_iterator_type end = getConstMap().end();
					const_iterator_type it = getConstMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->first;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Collection::out of range");
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
				throw std::out_of_range("Collection::out of range");
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				if (good()) { 
					const_iterator_type end = getConstMap().end();
					const_iterator_type it = getConstMap().begin();
					while (it != end) {
						if (steps == 0) {
							return it->second;
						}
						++it;
						--steps;
					}
				}
				throw std::out_of_range("Collection::out of range");
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _mapBridge.good(); }
			
			//! @return true if the Collection is at the beginning.
			virtual size_t size() const { return good() ? getConstMap().size() : 0; }
			
			//! @return true if the Collection is at the end.
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
					const_iterator_type end = getConstMap().end();
					const_iterator_type it = getConstMap().begin();
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
					const_iterator_type end = getConstMap().end();
					const_iterator_type it = getConstMap().find((key_type) first);
					return it != end && it->second == second;
				}
				return false;
			}
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Collection(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Collection(input); }
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::map and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Collection<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>& > : 
		public CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator> CollectionStdMap;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdMap(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::map and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Collection<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>& >  : 
		public CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator>
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>&, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator> CollectionStdMap;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdMap(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::map and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Collection<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template> > : 
		public CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator > 
		{
		public:
			typedef std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::iterator > CollectionStdMap;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdMap(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getMap()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::map and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename key_template, typename value_template, typename compare_template, typename allocator_template>
		class Collection<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template> > : 
		public CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator > 
		{
		public:
			typedef const std::map<key_template, value_template, compare_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdMap<first_template, second_template, const std::map<key_template, value_template, compare_template, allocator_template>, typename std::map<key_template, value_template, compare_template, allocator_template>::const_iterator > CollectionStdMap;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdMap(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdMap(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getMap()); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
