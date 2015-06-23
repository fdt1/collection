/*
 *  lazy4_internal_CollectionWithConcatenation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 02/11/13.
 *  Copynext 2013 __MyCompanyName__. All nexts reserved.
 *
 */



#pragma once

#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_IteratorWithConcatenation.h"
#include "lazy4_internal_Content.h"
#include <stdexcept>


namespace lazy4 {

	template <typename first_template, typename second_template>
	class Pair;

	namespace internal {
		
		
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class IteratorWithConcatenation;
		
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class CollectionWithConcatenation :
		public ICollection<first_template, second_template, 
			lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef typename lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			
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
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithConcatenation<first_template, second_template, prev_content_template, next_content_template> IteratorWithConcatenation;
			typedef typename internal::CollectionBridge<first_template, second_template, prev_content_template> PrevCollectionBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, next_content_template> NextCollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			PrevCollectionBridge _prev;
			NextCollectionBridge _next;
			content_template _content;
			
		public:
			CollectionWithConcatenation(const PrevCollectionBridge& prev, const NextCollectionBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return content_template::Bridge::cast(_content).getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _prev.isValid() && _next.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithConcatenation* clone() const { return new CollectionWithConcatenation(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithConcatenation* cloneIterator() const { return new IteratorWithConcatenation(_prev.cloneIterator(), _next.cloneIterator()); }
			
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			IteratorBridge cloneIterator(size_t steps) const { IteratorWithConcatenation* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _prev.size() + _next.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _prev.empty() && _next.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.isEnd()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.isEnd()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.isEnd()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.isEnd()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const { return _prev.existFirst(first) || _next.existFirst(first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { return _prev.existSecond(second) || _next.existSecond(second); } 
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { return _prev.existPair(first, second) || _next.existPair(first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
		};

		
		
	} // namespace internal
	
	
} // namespace lazy4
