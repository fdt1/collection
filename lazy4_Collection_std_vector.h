/*
 *  lazy4_internal_Collection_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Collection.h"
#include "lazy4_Iterator_std_vector.h"
#include <vector>

namespace lazy4 {
	
	namespace internal {
		
				
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionStdVector : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			typedef typename internal::Type<content_template>::prime_type::const_iterator const_iterator_type;
			typedef typename internal::Type<content_template>::prime_type::iterator iterator_type;
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
			ContentBridge<content_template> _vectorBridge;
			
		public:
			CollectionStdVector() : _vectorBridge(new Content<content_template>()) {}
			
			CollectionStdVector(parameter_content_type content) : _vectorBridge(new Content<content_template>(content)) {}
			
			CollectionStdVector(const ContentBridge<content_template>& content) : _vectorBridge(content) {}

		public:
			inline ref_content_type getVector() { return _vectorBridge.getContent(); }
			
			inline const_ref_content_type getConstVector() const { return _vectorBridge.getConstContent(); }
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual IIterator* cloneIterator() const { return new Iterator(_vectorBridge); }			
			
			//! @return the pointer ID
			virtual const void* where() const { return _vectorBridge.where(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return (first_type) steps; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return (const_first_type) steps; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { return (getVector())[steps]; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { return (getConstVector())[steps]; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { 
				if (steps >= (getConstVector()).size()) {
					throw std::out_of_range("out of range");
				}
				return (first_type) steps; 
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				if (steps >= (getConstVector()).size()) {
					throw std::out_of_range("out of range");
				}
				return (const_first_type) steps; 
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { return (getVector()).at(steps); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return (getConstVector()).at(steps); }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _vectorBridge.good(); }
			
			//! @return true if the Collection is at the beginning.
			virtual size_t size() const { return good() ? getConstVector().size() : 0; }
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return good() ? getConstVector().empty() : true; }
						
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getVector(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstVector(); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				return first < (first_type) (getConstVector()).size(); 
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (good()) { 
					const_iterator_type end = getConstVector().end();
					const_iterator_type it = getConstVector().begin();
					while (it != end) {
						if (*it == second) {
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
				if (first < (first_type) getConstVector().size()) {
					return getConstVector()[first] == second;
				} else {
					return false;
				}
			}
		
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Collection(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Collection(input); }
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename content_template>
		class CollectionStdVector<first_template, void, content_template> : 
		public ICollection<first_template, void, content_template>
		{
		public:
			typedef void second_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			typedef typename internal::Type<content_template>::prime_type::const_iterator const_iterator_type;
			typedef typename internal::Type<content_template>::prime_type::iterator iterator_type;
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
			ContentBridge<content_template> _vectorBridge;
			
		public:
			CollectionStdVector() : _vectorBridge(new Content<content_template>()) {}
			
			CollectionStdVector(parameter_content_type content) : _vectorBridge(new Content<content_template>(content)) {}
			
			CollectionStdVector(const ContentBridge<content_template>& content) : _vectorBridge(content) {}

		public:
			inline ref_content_type getVector() { return _vectorBridge.getContent(); }
			
			inline const_ref_content_type getConstVector() const { return _vectorBridge.getConstContent(); }
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual IIterator* cloneIterator() const { return new Iterator(_vectorBridge); }			
			
			//! @return the pointer ID
			virtual const void* where() const { return _vectorBridge.where(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return (getVector())[steps]; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return (getConstVector())[steps]; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { return (getVector()).at(steps); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return (getConstVector()).at(steps); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _vectorBridge.good(); }
			
			//! @return true if the Collection is at the beginning.
			virtual size_t size() const { return good() ? getConstVector().size() : 0; }
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return good() ? getConstVector().empty() : true; }
						
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getVector(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstVector(); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (good()) { 
					const_iterator_type end = getConstVector().end();
					const_iterator_type it = getConstVector().begin();
					while (it != end) {
						if (*it == first) {
							return true;
						}
						++it;
					}
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return false; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return exist_first(first); }
		
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Collection(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Collection(input); }
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::vector and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Collection<first_template, second_template, const std::vector<element_template, allocator_template>& > : 
		public CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&> 
		{
		public:
			typedef const std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&> CollectionStdVector;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdVector(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::vector and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Collection<first_template, second_template, std::vector<element_template, allocator_template>& >  : 
		public CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template>&>
		{
		public:
			typedef std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template>&> CollectionStdVector;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdVector(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::vector and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Collection<first_template, second_template, std::vector<element_template, allocator_template> > : 
		public CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template> > 
		{
		public:
			typedef std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, std::vector<element_template, allocator_template> > CollectionStdVector;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdVector(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}

			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getVector()); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionAdapter specialization. It wraps here std::vector and its Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Collection<first_template, second_template, const std::vector<element_template, allocator_template> > : 
		public CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template> > 
		{
		public:
			typedef const std::vector<element_template, allocator_template> content_template;
			typedef void second_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::CollectionStdVector<first_template, second_template, const std::vector<element_template, allocator_template> > CollectionStdVector;
			
		public:
			Collection() {}
			
			Collection(parameter_content_type content) : CollectionStdVector(content) {}
			
			Collection(const ContentBridge<content_template>& content) : CollectionStdVector(content) {}

		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(const_cast<Collection*>(this)->getVector()); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
