/*
 *  lazy4_internal_IteratorWithConcatenation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 02/11/13.
 *  Copynext 2013 __MyCompanyName__. All nexts reserved.
 *
 */

#pragma once

#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_CollectionWithConcatenation.h"
#include "lazy4_internal_Content.h"



namespace lazy4 {
	
	template <typename first_template, typename second_template>
	class Pair;

	namespace internal {

		
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class CollectionWithConcatenation;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class IteratorWithConcatenation :
		public IIterator<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
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
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			
		public:
			typedef typename internal::CollectionWithConcatenation<first_template, second_template, prev_content_template, next_content_template> CollectionWithConcatenation;
			typedef typename internal::IteratorBridge<first_template, second_template, prev_content_template> PrevIteratorBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, next_content_template> NextIteratorBridge;
			
		public:
			PrevIteratorBridge _prev;
			NextIteratorBridge _next;
			content_template _content;
			
		public:
			IteratorWithConcatenation(const PrevIteratorBridge& prev, const NextIteratorBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _prev.isEnd() ? _next.getID() : _prev.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _prev.isValid() && _next.isValid() && content_template::Bridge::cast(_content).isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithConcatenation* clone() const { return new IteratorWithConcatenation(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithConcatenation* cloneCollection() const { return new CollectionWithConcatenation(_prev.cloneCollection(), _next.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = _prev.forward(steps);
				if (count == steps) {					
					return count;
				} else {
					return count + _next.forward(steps - count);
				}
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _prev.flush(); _next.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _prev.distance() + _next.distance(); } 
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = _next.backward(steps);
				if (count == steps) {					
					return count;
				} else {
					return count + _prev.backward(steps - count);
				}
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _prev.rewind(); _next.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _prev.remains() + _next.remains(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const { return _prev.isBegin() && _next.isBegin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return _prev.isEnd() && _next.isEnd(); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return _prev.isEnd() ? _next.getFirst() : _prev.getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return _prev.isEnd() ? _next.getConstFirst() : _prev.getConstFirst(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { return _prev.findFirst(first) || _next.findFirst(first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) { return _next.rfindFirst(first) || _prev.rfindFirst(first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return _prev.isEnd() ? _next.getSecond() : _prev.getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return _prev.isEnd() ? _next.getConstSecond() : _prev.getConstSecond(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { return _prev.findSecond(second) || _next.findSecond(second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) { return _next.rfindSecond(second) || _prev.rfindSecond(second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { return _prev.findPair(first, second) || _next.findPair(first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { return _next.rfindPair(first, second) || _prev.rfindPair(first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
		};
		

		
	} // namespace internal
	
	
} // namespace lazy4
