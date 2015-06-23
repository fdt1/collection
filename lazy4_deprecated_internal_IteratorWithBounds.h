/*
 *  lazy4_internal_IteratorWithBounds.h
 *  collection
 *
 *  Created by Francois et Fabienne on 12/01/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_CollectionWithBounds.h"

namespace lazy4 {
	
	
	namespace internal {
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class CollectionWithBounds;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithBounds is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class IteratorWithBounds : 
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
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithBounds<first_template, second_template, content_template> CollectionWithBounds;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _begin;
			IteratorBridge _end;
			IteratorBridge _current;
			
		public:
			IteratorWithBounds(const IteratorBridge& begin, const IteratorBridge& end) : _begin(begin), _end(end), _current(begin) {}
			
			IteratorWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _current.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _begin.isValid() && _end.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithBounds* clone() const { return new IteratorWithBounds(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithBounds* cloneCollection() const { return new CollectionWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				if (!isValid()) {
					return 0;
				}
				size_t count = 0;
				const void* endID = _end.getID();
				for (; count != steps && _current.getID() != endID; ++count) {
					_current.forward(1);
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _current = _end; }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _current.distance() - _begin.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				if (!isValid()) {
					return 0;
				}
				size_t count = 0;
				const void* beginID = _begin.getID();
				for (; count != steps && _current.getID() != beginID; ++count) {
					_current.backward(1);
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _current = _begin; }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _current.remains() - _end.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const { return _current.getID() == _begin.getID(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return _current.getID() == _end.getID(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_current); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_current); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (FirstUtility::getConstFirst(_current) == first) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) {
				if (!isValid()) {
					return false;
				}
				const void* beginID = _begin.getID();
				
				if (_current.getID() == beginID) {
					return FirstUtility::getConstFirst(_current) == first;
				}
				do {
					_current.backward(1);
					if (FirstUtility::getConstFirst(_current) == first) {
						return true;
					}
				} while (_current.getID() != beginID);
				
				return false; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_current); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_current); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* beginID = _begin.getID();
				
				if (_current.getID() == beginID) {
					return SecondUtility::getConstSecond(_current) == second;
				}
				do {
					_current.backward(1);
					if (SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
				} while (_current.getID() != beginID);
				
				return false; 
			}

		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* beginID = _begin.getID();
				
				if (_current.getID() == beginID) {
					return FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second;
				}
				do {
					_current.backward(1);
					if (FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
				} while (_current.getID() != beginID);
				
				return false; 
			}
			
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_current); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_current); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
