/*
 *  lazy4_internal_Iterator_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_Iterator.h"
#include "lazy4_Collection_std_vector.h"
#include <vector>

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename iterator_template>
		class IteratorStdVector : 
		public IIterator<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IEmbeddedIterator;
			typedef content_template input_template;
			typedef IEmbeddedIterator* output_template;			
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
			typedef typename internal::Type<iterator_template>::type iterator_type;
			typedef typename internal::Type<iterator_template>::ref_type ref_iterator_type;
			typedef typename internal::Type<iterator_template>::const_ref_type const_ref_iterator_type;
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator; 
			
		public:
			ContentBridge<content_template> _vectorBridge;
			Content<iterator_template> _iteratorBridge;
			
		public:
			IteratorStdVector() : _vectorBridge(new Content<content_template>())/*, _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) */ {}
			
			IteratorStdVector(parameter_content_type content) : _vectorBridge(new Content<content_template>(content)), _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) {}
			
			IteratorStdVector(const ContentBridge<content_template>& content) : _vectorBridge(content.good() ? content : new Content<content_template>()), _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) {}
			
		public:
			inline ref_content_type getVector() { return _vectorBridge.getContent(); }
			
			inline const_ref_content_type getConstVector() const { return _vectorBridge.getConstContent(); }
			
			inline ref_iterator_type getIterator() { return _iteratorBridge.getContent(); }
			
			inline const_ref_iterator_type getConstIterator() const { return _iteratorBridge.getConstContent(); }
			
		public:
			//! @return build the corresponding collection
			virtual Collection* cloneCollection() const { return new Collection(_vectorBridge); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Iterator(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Iterator(input); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() && getConstIterator() != getConstVector().end() ? &(*getConstIterator()) : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { 
				 return (first_type) std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator());
			}
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { 
				 return (const_first_type) std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator());
			}
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool find_first(const_ref_first_type first) { 
				if (first < (first_type) getConstVector().size() && first >= (first_type) std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator())) {
					getIterator() = const_cast<ref_content_type>(getConstVector()).begin() + first;
					return true;
				} else {
					getIterator() = const_cast<ref_content_type>(getConstVector()).end();
					return false;
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::rfindFirst implementation.
			virtual bool rfind_first(const_ref_first_type first) { 
				if (first >= 0 && first <= (first_type) std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator())) {
					getIterator() = const_cast<ref_content_type>(getConstVector()).begin() + first + 1;
					return true;
				} else {
					getIterator() = const_cast<ref_content_type>(getConstVector()).begin();
					return false;
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return *(getIterator()); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return *(getConstIterator()); }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool find_second(const_ref_second_type second) { 
				if (good()) { 
					iterator_template end = const_cast<ref_content_type>(getConstVector()).end();
					iterator_template it = getIterator();
					while (it != end) {
						if (*it == second) {
							_iteratorBridge = it;
							return true;
						}
						++it;
					}
					_iteratorBridge = it;
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::rfindSecond implementation.
			virtual bool rfind_second(const_ref_second_type second) {
				if (good()) { 
					iterator_template it = getIterator();
					iterator_template begin = const_cast<ref_content_type>(getConstVector()).begin();
					while (it != begin) {
						if (*(it - 1) == second) {
							_iteratorBridge = it;
							return true;
						}
						--it;
					}
					_iteratorBridge = it;
				}
				return false;
			}
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (rfind_first(first)) {
					if (*getConstIterator() == second) {
						return true;
					} else {
						getIterator() = const_cast<ref_content_type>(getConstVector()).begin();
						return false;
					}
				} else {
					return false; 
				}
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { 
				if (rfind_first(first)) {
					if (*(getConstIterator() - 1) == second) {
						return true;
					} else {
						getIterator() = const_cast<ref_content_type>(getConstVector()).begin();
						return false;
					}
				} else {
					return false; 
				}
			}
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _vectorBridge.good() && _iteratorBridge.good(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return getConstIterator() == getConstVector().begin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return getConstIterator() == getConstVector().end(); }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (good()) { 
					size_t left = remains();
					if (left < steps) {
						getIterator() += left;
						return left;
					} else {
						getIterator() += steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { 
				if (good()) { 
					_iteratorBridge = (const_cast<ref_content_type>(getConstVector()).end()); 
				}
			}
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (good()) { 
					return std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator()); 
				} else {
					return 0;
				}
			}
			
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getVector(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstVector(); }
			
		public:
			//! @href lazy3::internal::IIteratorOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (good()) { 
					size_t left = distance();
					if (left < steps) {
						this->getIterator() -= left;
						return left;
					} else {
						this->getIterator() -= steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::rewind implementation.
			virtual void rewind() { 
				if (good()) { 
					this->_iteratorBridge = (const_cast<ref_content_type>(getConstVector()).begin()); 
				}
			}
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const  { 
				if (good()) { 
					return std::distance(getConstIterator(), const_cast<ref_content_type>(getConstVector()).end()); 
				} else {
					return 0;
				}
			}
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_template, typename content_template, typename iterator_template>
		class IteratorStdVector<first_template, void, content_template, iterator_template> : 
		public IIterator<first_template, void, content_template>
		{
		public:
			typedef void second_template;
			typedef typename internal::IIterator<first_template, second_template, content_template> IEmbeddedIterator;
			typedef content_template input_template;
			typedef IEmbeddedIterator* output_template;			
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
			typedef typename internal::Type<iterator_template>::type iterator_type;
			typedef typename internal::Type<iterator_template>::ref_type ref_iterator_type;
			typedef typename internal::Type<iterator_template>::const_ref_type const_ref_iterator_type;
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator; 
			
		public:
			ContentBridge<content_template> _vectorBridge;
			Content<iterator_template> _iteratorBridge;
			
		public:
			IteratorStdVector() : _vectorBridge(new Content<content_template>())/*, _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) */ {}
			
			IteratorStdVector(parameter_content_type content) : _vectorBridge(new Content<content_template>(content)), _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) {}
			
			IteratorStdVector(const ContentBridge<content_template>& content) : _vectorBridge(content.good() ? content : new Content<content_template>()), _iteratorBridge(const_cast<ref_content_type>(getConstVector()).begin()) {}
			
		public:
			inline ref_content_type getVector() { return _vectorBridge.getContent(); }
			
			inline const_ref_content_type getConstVector() const { return _vectorBridge.getConstContent(); }
			
			inline ref_iterator_type getIterator() { return _iteratorBridge.getContent(); }
			
			inline const_ref_iterator_type getConstIterator() const { return _iteratorBridge.getConstContent(); }
			
		public:
			//! @return build the corresponding collection
			virtual Collection* cloneCollection() const { return new Collection(_vectorBridge); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new Iterator(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new Iterator(input); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() && getConstIterator() != getConstVector().end() ? &(*getConstIterator()) : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return *(getIterator()); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return *(getConstIterator()); }
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool find_first(const_ref_first_type first) { 
				if (good()) { 
					iterator_template end = const_cast<ref_content_type>(getConstVector()).end();
					iterator_template it = getIterator();
					while (it != end) {
						if (*it == first) {
							_iteratorBridge = it;
							return true;
						}
						++it;
					}
					_iteratorBridge = it;
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::rfindFirst implementation.
			virtual bool rfind_first(const_ref_first_type first) { 
				if (good()) { 
					iterator_template it = getIterator();
					iterator_template begin = const_cast<ref_content_type>(getConstVector()).begin();
					while (it != begin) {
						if (*(it - 1) == first) {
							_iteratorBridge = it;
							return true;
						}
						--it;
					}
					_iteratorBridge = it;
				}
				return false;
			}
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool find_second(const_ref_second_type ) { return false; }
			
			//! @href lazy3::internal::IPairOnFirst::rfindSecond implementation.
			virtual bool rfind_second(const_ref_second_type ) { return false; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return find_first(first); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return rfind_first(first); }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _vectorBridge.good() && _iteratorBridge.good(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return getConstIterator() == getConstVector().begin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return getConstIterator() == getConstVector().end(); }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (good()) { 
					size_t left = remains();
					if (left < steps) {
						getIterator() += left;
						return left;
					} else {
						getIterator() += steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { 
				if (good()) { 
					_iteratorBridge = (const_cast<ref_content_type>(getConstVector()).end()); 
				}
			}
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (good()) { 
					return std::distance(const_cast<ref_content_type>(getConstVector()).begin(), getConstIterator()); 
				} else {
					return 0;
				}
			}
			
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return getVector(); }
			
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return getConstVector(); }
			
		public:
			//! @href lazy3::internal::IIteratorOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (good()) { 
					size_t left = distance();
					if (left < steps) {
						this->getIterator() -= left;
						return left;
					} else {
						this->getIterator() -= steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::rewind implementation.
			virtual void rewind() { 
				if (good()) { 
					this->_iteratorBridge = (const_cast<ref_content_type>(getConstVector()).begin()); 
				}
			}
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const  { 
				if (good()) { 
					return std::distance(getConstIterator(), const_cast<ref_content_type>(getConstVector()).end()); 
				} else {
					return 0;
				}
			}
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Iterator<first_template, second_template, const std::vector<element_template, allocator_template>& > : 
		public IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::const_iterator> IteratorStdVector;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdVector(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Iterator<first_template, second_template, std::vector<element_template, allocator_template>& >  : 
		public IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::iterator>
		{
		public:
			typedef std::vector<element_template, allocator_template>& content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>&, typename std::vector<element_template, allocator_template>::iterator> IteratorStdVector;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdVector(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Iterator<first_template, second_template, std::vector<element_template, allocator_template> > : 
		public IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::iterator> 
		{
		public:
			typedef std::vector<element_template, allocator_template> content_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::iterator> IteratorStdVector;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdVector(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename element_template, typename allocator_template>
		class Iterator<first_template, second_template, const std::vector<element_template, allocator_template> > : 
		public IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::const_iterator> 
		{
		public:
			typedef const std::vector<element_template, allocator_template> content_template;
			typedef void second_template;
		public:
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::IteratorStdVector<first_template, second_template, const std::vector<element_template, allocator_template>, typename std::vector<element_template, allocator_template>::const_iterator> IteratorStdVector;
			
		public:
			Iterator() {}
			
			Iterator(parameter_content_type content) : IteratorStdVector(content) {}
			
			Iterator(const ContentBridge<content_template>& content) : IteratorStdVector(content) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
