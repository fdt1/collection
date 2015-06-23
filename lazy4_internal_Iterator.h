/*
 *  lazy4_internal_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Flow.h"
#include <map>


namespace lazy4 {
	
	template<typename first_template, typename second_template, typename container_template>
	class Iterator;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class ICollection;
		
		template<typename first_template, typename second_template, typename content_template>
		class Collection;
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IIterator :
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef content_template input_template;
			typedef IIterator* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> ICollection;
			typedef typename internal::IPair<first_template, second_template> IPair;
			
		public:
			//! @return duplicate of the current implementation
			virtual IIterator* clone() const = 0;
			
			//! @return the corresponding collection of the current Iterator
			virtual ICollection* cloneCollection() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		public:
			//! step backward element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t backward(size_t steps) = 0;
			
			//! make the iterator restart.
			virtual void rewind() = 0;
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const = 0;
			
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual size_t remains() const = 0;
			
		public:
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) = 0;
			
			//! iterate backward until we reach a given element.
			//! @return true if the wanted element has been met.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) = 0;
			
		public:
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) = 0;
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorBridge :
		public Bridge<IIterator<first_template, second_template, content_template> >
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
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> ICollection;
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			typedef typename internal::IModifier<IIterator*, content_template, content_template> IModifier;
			typedef typename internal::Bridge<IEmbeddedIterator> Bridge;
			
		public:
			typedef IEmbeddedIterator interface_type;
			
		public:
			IteratorBridge() {}
			
			IteratorBridge(const IEmbeddedIterator* implementation) : Bridge(implementation) {}
			
			IteratorBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline IteratorBridge& operator= (const IEmbeddedIterator* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const IteratorBridge& cast(const lazy4::Iterator<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline IteratorBridge& cast(lazy4::Iterator<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline const IteratorBridge& cast(const IteratorBridge& iterator) { return iterator; }
			
			//! for compatibility
			static inline IteratorBridge& cast(IteratorBridge& iterator) { return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedIterator* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedIterator* clone() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->clone(); else return NULL; }
			
			//! @return build the corresponding collection
			inline ICollection* cloneCollection() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->cloneCollection(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			inline size_t forward(size_t steps) { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) return Iterator->forward(steps); else return 0; }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			inline void flush() { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) Iterator->flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t distance() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->distance(); else return 0; }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			inline size_t backward(size_t steps) { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) return Iterator->backward(steps); else return 0; }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			inline void rewind() { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) Iterator->rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			inline size_t remains() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->remains(); else return 0; }			
			
			//! @return true if the iterator is at the beginning.
			inline bool top() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->top(); else return true; }
			
			//! @return true if the iterator is at the end.
			inline bool eof() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->eof(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst() { return FirstUtility::getFirst(*this); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool find_first(const_ref_first_type first) { return FirstUtility::find_first(*this, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool rfind_first(const_ref_first_type first) { return FirstUtility::rfind_first(*this, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond() { return SecondUtility::getSecond(*this); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool find_second(const_ref_second_type second) { return SecondUtility::find_second(*this, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool rfind_second(const_ref_second_type second) { return SecondUtility::rfind_second(*this, second); }
			
		public:
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(*this, first, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool rfind(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfind(*this, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	

	
		template<typename     first_template, typename     second_template, typename     content_template>
		class CollectionWithPermutation;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithPermutation is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class IteratorWithPermutation : 
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
			typedef typename internal::FirstUtility<second_template> FirstUtility;
			typedef typename internal::SecondUtility<first_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<second_template, first_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithPermutation<first_template, second_template, content_template> CollectionWithPermutation;
			typedef typename internal::IteratorBridge<second_template, first_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			
		public:
			IteratorWithPermutation(const IteratorBridge& bridge) : _bridge(bridge) {}
			
			IteratorWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPermutation* clone() const { return new IteratorWithPermutation(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithPermutation* cloneCollection() const { return new CollectionWithPermutation(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { return SecondUtility::find_second(_bridge, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { return SecondUtility::rfind_second(_bridge, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return FirstUtility::find_first(_bridge, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return FirstUtility::rfind_first(_bridge, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(_bridge, second, first); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfind(_bridge, second, first); }
		};
		
		
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
			virtual const void* where() const { return _current.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
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
				if (!good()) {
					return 0;
				}
				size_t count = 0;
				const void* endID = _end.where();
				for (; count != steps && _current.where() != endID; ++count) {
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
				if (!good()) {
					return 0;
				}
				size_t count = 0;
				const void* beginID = _begin.where();
				for (; count != steps && _current.where() != beginID; ++count) {
					_current.backward(1);
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _current = _begin; }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _current.remains() - _end.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _current.where() == _begin.where(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _current.where() == _end.where(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_current); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_current); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				if (!good()) {
					return false;
				}
				const void* endID = _end.where();
				while (_current.where() != endID) {
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
			virtual bool rfind_first(const_ref_first_type first) {
				if (!good()) {
					return false;
				}
				const void* beginID = _begin.where();
				
				if (_current.where() == beginID) {
					return FirstUtility::getConstFirst(_current) == first;
				}
				do {
					_current.backward(1);
					if (FirstUtility::getConstFirst(_current) == first) {
						return true;
					}
				} while (_current.where() != beginID);
				
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
			virtual bool find_second(const_ref_second_type second) { 
				if (!good()) {
					return false;
				}
				const void* endID = _end.where();
				while (_current.where() != endID) {
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
			virtual bool rfind_second(const_ref_second_type second) { 
				if (!good()) {
					return false;
				}
				const void* beginID = _begin.where();
				
				if (_current.where() == beginID) {
					return SecondUtility::getConstSecond(_current) == second;
				}
				do {
					_current.backward(1);
					if (SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
				} while (_current.where() != beginID);
				
				return false; 
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (!good()) {
					return false;
				}
				const void* endID = _end.where();
				while (_current.where() != endID) {
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
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { 
				if (!good()) {
					return false;
				}
				const void* beginID = _begin.where();
				
				if (_current.where() == beginID) {
					return FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second;
				}
				do {
					_current.backward(1);
					if (FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
				} while (_current.where() != beginID);
				
				return false; 
			}
			
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_current); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_current); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class CollectionWithStaticCast;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class IteratorWithStaticCast : 
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
			typedef typename internal::FunctorUtility<internal::IIterator<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::CollectionWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> CollectionWithStaticCast;
			typedef typename internal::IteratorBridge<old_first_template, old_second_template, old_content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			
		public:
			IteratorWithStaticCast(const IteratorBridge& bridge) : _bridge(bridge) {}
			
			IteratorWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithStaticCast* clone() const { return new IteratorWithStaticCast(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithStaticCast* cloneCollection() const { return new CollectionWithStaticCast(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { return FirstUtility::find_first(_bridge, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { return FirstUtility::rfind_first(_bridge, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return SecondUtility::find_second(_bridge, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return SecondUtility::rfind_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(_bridge, first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfind(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class CollectionWithFirstDynamicCast;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class IteratorWithFirstDynamicCast : 
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
			typedef typename internal::FunctorUtility<internal::IIterator<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::CollectionWithFirstDynamicCast<first_template, second_template, content_template, old_first_template> CollectionWithFirstDynamicCast;
			typedef typename internal::IteratorBridge<old_first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::DynamicCast<first_template, old_first_template> DynamicCast;
			
		public:
			IteratorBridge _bridge;
			
		public:
			IteratorWithFirstDynamicCast(const IteratorBridge& bridge) : _bridge(bridge) {}
			
			IteratorWithFirstDynamicCast() {}
			
		public:		
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return DynamicCast::isMatch(_bridge.getConstFirst()); }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstDynamicCast* clone() const { return new IteratorWithFirstDynamicCast(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithFirstDynamicCast* cloneCollection() const { return new CollectionWithFirstDynamicCast(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!_bridge.eof() && count != steps) {
						if (isMatch()) {
							++count;
						}
						if (_bridge.forward(1) == 0) {
							break;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithFirstDynamicCast* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithFirstDynamicCast* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<IteratorWithFirstDynamicCast*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return DynamicCast::convert(_bridge.getFirst()); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstDynamicCast*>(this)->forward(1) == 0) {
						break;
					}
				}
				return DynamicCast::convert(_bridge.getConstFirst()); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstDynamicCast*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (isMatch() && getConstFirst() == first && getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (isMatch() && getConstFirst() == first && getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class CollectionWithFirstAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class IteratorWithFirstAccessor :
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
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithFirstAccessor<first_template, second_template, content_template, old_first_template, closure_template> CollectionWithFirstAccessor;
			typedef typename internal::IteratorBridge<old_first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithFirstAccessor(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstAccessor* clone() const { return new IteratorWithFirstAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithFirstAccessor* cloneCollection() const { return new CollectionWithFirstAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return SecondUtility::find_second(_bridge, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return SecondUtility::rfind_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first && getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first && getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class CollectionWithSecondAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class IteratorWithSecondAccessor :
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
			typedef typename internal::SecondUtility<old_second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<second_template, old_second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithSecondAccessor<first_template, second_template, content_template, old_second_template, closure_template> CollectionWithSecondAccessor;
			typedef typename internal::IteratorBridge<first_template, old_second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithSecondAccessor(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithSecondAccessor* clone() const { return new IteratorWithSecondAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithSecondAccessor* cloneCollection() const { return new CollectionWithSecondAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirst() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_first(const_ref_first_type first) { return FirstUtility::find_first(_bridge, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_first(const_ref_first_type first) { return FirstUtility::rfind_first(_bridge, first); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecond() { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecond(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecond() const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecond(_bridge)); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_second(const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first && getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first && getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class CollectionWithPairAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class IteratorWithPairAccessor :
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
			typedef typename lazy4::Pair<old_first_template, old_second_template> OldPair;
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<Pair, OldPair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithPairAccessor<first_template, second_template, content_template, old_first_template, old_second_template, closure_template> CollectionWithPairAccessor;
			typedef typename internal::IteratorBridge<old_first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<Pair, OldPair, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithPairAccessor(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPairAccessor* clone() const { return new IteratorWithPairAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithPairAccessor* cloneCollection() const { return new CollectionWithPairAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithPairAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithPairAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return FunctorUtility::getOutput(_modifier, OldPair(FirstUtility::getConstFirst(_bridge), FirstUtility::getConstSecond(_bridge))).first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FunctorUtility::getConstOutput(_modifier, OldPair(FirstUtility::getConstFirst(_bridge), FirstUtility::getConstSecond(_bridge))).first; }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return FunctorUtility::getOutput(_modifier, OldPair(FirstUtility::getConstFirst(_bridge), FirstUtility::getConstSecond(_bridge))).first(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return FunctorUtility::getConstOutput(_modifier, OldPair(FirstUtility::getConstFirst(_bridge), FirstUtility::getConstSecond(_bridge))).first; }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) {
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}

			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (good()) { 
					while (!eof()) {
						if (getConstFirst() == first && getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				if (good()) { 
					while (!top()) {
						if (backward(1) == 0) {
							break;
						}
						if (getConstFirst() == first && getConstSecond() == second) {
							forward(1);
							return true;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithFirstFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithFirstFilter :
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
			typedef typename internal::FunctorUtility<filter_template, first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithFirstFilter<first_template, second_template, content_template, filter_template, closure_template> CollectionWithFirstFilter;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithFirstFilter(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:		
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstFilter* clone() const { return new IteratorWithFirstFilter(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithFirstFilter* cloneCollection() const { return new CollectionWithFirstFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithFirstFilter* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithFirstFilter* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<IteratorWithFirstFilter*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithSecondFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithSecondFilter :
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
			typedef typename internal::FunctorUtility<filter_template, second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithSecondFilter<first_template, second_template, content_template, filter_template, closure_template> CollectionWithSecondFilter;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<filter_template, second_template, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithSecondFilter(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:		
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstSecond(_bridge)); }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithSecondFilter* clone() const { return new IteratorWithSecondFilter(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithSecondFilter* cloneCollection() const { return new CollectionWithSecondFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithSecondFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithSecondFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithSecondFilter* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithSecondFilter* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<IteratorWithSecondFilter*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithSecondFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithSecondFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};


		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithPairFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithPairFilter :
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
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<filter_template, Pair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::CollectionWithPairFilter<first_template, second_template, content_template, filter_template, closure_template> CollectionWithPairFilter;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::ModifierBridge<filter_template, Pair, closure_template> ModifierBridge;
			
		public:
			IteratorBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IteratorWithPairFilter(const IteratorBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:		
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return FunctorUtility::getOutput(_modifier, Pair(FirstUtility::getConstFirst(_bridge), SecondUtility::getConstSecond(_bridge))); }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPairFilter* clone() const { return new IteratorWithPairFilter(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithPairFilter* cloneCollection() const { return new CollectionWithPairFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithPairFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithPairFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithPairFilter* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (isMatch()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithPairFilter* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<IteratorWithPairFilter*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithPairFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithPairFilter*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		

		
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithFirstUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithFirstUnique :
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
			typedef typename internal::CollectionWithFirstUnique<first_template, second_template, content_template> CollectionWithFirstUnique;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			mutable std::map<first_type, int> _visited;
			
		public:
			IteratorWithFirstUnique(const IteratorBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return _visited[FirstUtility::getConstFirst(_bridge)] <= 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool add() const { return ++_visited[FirstUtility::getConstFirst(_bridge)] == 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool sub() const { 
				typename std::map<first_type, int>::iterator it = _visited.find(FirstUtility::getConstFirst(_bridge));
				if (it == _visited.end()) {
					return true;
				} else if (it->second == 1) {
					_visited.erase(it);
					return true;
				} else {
					--it->second;
					return false;
				}
			}
			
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstUnique* clone() const { return new IteratorWithFirstUnique(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithFirstUnique* cloneCollection() const { return new CollectionWithFirstUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (add()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { forward(-1); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithFirstUnique* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (sub()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithFirstUnique* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstUnique*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithFirstUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithSecondUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithSecondUnique :
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
			typedef typename internal::CollectionWithSecondUnique<first_template, second_template, content_template> CollectionWithSecondUnique;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			mutable std::map<second_type, int> _visited;
			
		public:
			IteratorWithSecondUnique(const IteratorBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return _visited[SecondUtility::getConstSecond(_bridge)] <= 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool add() const { return ++_visited[SecondUtility::getConstSecond(_bridge)] == 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool sub() const { 
				typename std::map<first_type, int>::iterator it = _visited.find(SecondUtility::getConstSecond(_bridge));
				if (it == _visited.end()) {
					return true;
				} else if (it->second == 1) {
					_visited.erase(it);
					return true;
				} else {
					--it->second;
					return false;
				}
			}
			
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithSecondUnique* clone() const { return new IteratorWithSecondUnique(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithSecondUnique* cloneCollection() const { return new CollectionWithSecondUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithSecondUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithSecondUnique(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (add()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { forward(-1); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithSecondUnique* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (sub()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithSecondUnique* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!isMatch()) {
					if (const_cast<IteratorWithSecondUnique*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithSecondUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithSecondUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithPairUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithPairUnique :
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
			typedef typename internal::CollectionWithPairUnique<first_template, second_template, content_template> CollectionWithPairUnique;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			mutable std::map<std::pair<first_type, second_type>, int> _visited;
			
		public:
			IteratorWithPairUnique(const IteratorBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return _visited[std::pair<first_type, second_type>(FirstUtility::getConstFirst(_bridge), SecondUtility::getConstSecond(_bridge))] <= 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool add() const { return ++_visited[std::pair<first_type, second_type>(FirstUtility::getConstFirst(_bridge), SecondUtility::getConstSecond(_bridge))] == 1; }
			
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool sub() const { 
				typename std::map<first_type, int>::iterator it = _visited.find(std::pair<first_type, second_type>(FirstUtility::getConstFirst(_bridge), SecondUtility::getConstSecond(_bridge)));
				if (it == _visited.end()) {
					return true;
				} else if (it->second == 1) {
					_visited.erase(it);
					return true;
				} else {
					--it->second;
					return false;
				}
			}
			
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPairUnique* clone() const { return new IteratorWithPairUnique(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithPairUnique* cloneCollection() const { return new CollectionWithPairUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithPairUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithPairUnique(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (!eof() && count != steps) {
						if (_bridge.forward(1) == 0) {
							break;
						}
						if (add()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { forward(-1); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				IteratorWithPairUnique* newIterator = clone();
				size_t count = newIterator->backward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = 0;
				if (good()) {
					while (count != steps) {
						if (_bridge.backward(1) == 0) {
							break;
						}
						if (sub()) {
							++count;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				IteratorWithPairUnique* newIterator = clone();
				size_t count = newIterator->forward(-1 /* maximum size */);
				delete newIterator;
				return count;
			}			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!isMatch()) {
					if (const_cast<IteratorWithPairUnique*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getFirst(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithPairUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return FirstUtility::getConstFirst(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				while (_bridge.find_first(first)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<IteratorWithPairUnique*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				while (_bridge.find_second(second)) {
					if (isMatch()) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				while (_bridge.rfind_second(second)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch()) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.find_first(first)) {
					if (isMatch() && _bridge.getConstSecond() == second) {
						return true;
					}
					if (_bridge.forward(1) == 0) {
						break;
					}
				}	
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfind_first(first)) {
					if (_bridge.backward(1) == 0) {
						break;
					}
					if (isMatch() && _bridge.getConstSecond() == second) {
						_bridge.forward(1);
						return true;
					}
				}	
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithReverse;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithReverse :
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
			typedef typename internal::CollectionWithReverse<first_template, second_template, content_template> CollectionWithReverse;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
		public:
			IteratorBridge _bridge;
			
		public:
			IteratorWithReverse(const IteratorBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline internal::IteratorBridge<first_template, second_template, content_template> cloneIterator(size_t steps) const { IteratorWithReverse* iterator = clone(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithReverse* clone() const { return new IteratorWithReverse(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithReverse* cloneCollection() const { return new CollectionWithReverse(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithReverse(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithReverse(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.remains(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _bridge.distance(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.eof(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.top(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return cloneIterator(1).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return cloneIterator(1).getConstFirst(); } 
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { return rfind_first(first); } 
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { return find_first(first); } 
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return cloneIterator(1).getSecond(); } 
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return cloneIterator(1).getConstSecond(); } 
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return rfind_second(second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return find_second(second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfind(_bridge, first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		
		
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
			virtual const void* where() const { return _prev.eof() ? _next.where() : _prev.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good() && content_template::Bridge::cast(_content).good(); }
			
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
			virtual bool top() const { return _prev.top() && _next.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _prev.eof() && _next.eof(); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return _prev.eof() ? _next.getFirst() : _prev.getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return _prev.eof() ? _next.getConstFirst() : _prev.getConstFirst(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { return _prev.find_first(first) || _next.find_first(first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { return _next.rfind_first(first) || _prev.rfind_first(first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return _prev.eof() ? _next.getSecond() : _prev.getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return _prev.eof() ? _next.getConstSecond() : _prev.getConstSecond(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return _prev.find_second(second) || _next.find_second(second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return _next.rfind_second(second) || _prev.rfind_second(second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return _prev.find(first, second) || _next.find(first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return _next.rfind(first, second) || _prev.rfind(first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
		};
		
		template<typename container_first_template, typename other_second_template, typename content_template>
		class CollectionWithFirstFlatten;
		
		template<typename first_template, typename second_template, typename content_template>
		class CollectionBridge;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFirstFlatten is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class IteratorWithFirstFlatten :
		public IIterator<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
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
			typedef typename internal::CollectionWithFirstFlatten<container_first_template, other_second_template, content_template> CollectionWithFirstFlatten;
			typedef typename internal::IteratorBridge<container_first_template, other_second_template, content_template> IteratorBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, other_content_template> NestedIteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, other_content_template> NestedCollectionBridge;
			typedef typename lazy4::Iterator<first_template, second_template, other_content_template> NestedIterator;
			typedef typename lazy4::Collection<first_template, second_template, other_content_template> NestedCollection;
			typedef typename internal::IteratorBridge<NestedIterator, other_second_template, content_template> IteratorIteratorBridge;
			typedef typename internal::IteratorBridge<NestedCollection, other_second_template, content_template> CollectionIteratorBridge;
			typedef typename internal::IteratorBridge<NestedIterator&, other_second_template, content_template> RefIteratorIteratorBridge;
			typedef typename internal::IteratorBridge<NestedCollection&, other_second_template, content_template> RefCollectionIteratorBridge;
			typedef typename internal::IteratorBridge<const NestedIterator&, other_second_template, content_template> ConstRefIteratorIteratorBridge;
			typedef typename internal::IteratorBridge<const NestedCollection&, other_second_template, content_template> ConstRefCollectionIteratorBridge;
			typedef typename internal::IteratorBridge<const NestedIterator, other_second_template, content_template> ConstIteratorIteratorBridge;
			typedef typename internal::IteratorBridge<const NestedCollection, other_second_template, content_template> ConstCollectionIteratorBridge;
			
			
		public:
			IteratorBridge _bridge;
			NestedIteratorBridge _nested;
			
		public:
			IteratorWithFirstFlatten(const IteratorBridge& bridge) : _bridge(bridge), _nested(getNestedIterator(_bridge)) {}
			
		public:
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(CollectionIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedCollectionBridge nested = NestedCollectionBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(RefCollectionIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedCollectionBridge nested = NestedCollectionBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(ConstCollectionIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedCollectionBridge nested = NestedCollectionBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(ConstRefCollectionIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedCollectionBridge nested = NestedCollectionBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(IteratorIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(RefIteratorIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstIteratorIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstRefIteratorIteratorBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(IteratorIteratorBridge& bridge) { return getNestedIterator(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(RefIteratorIteratorBridge& bridge) { return getNestedIterator(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(ConstIteratorIteratorBridge& bridge) { return getNestedIterator(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedCollectionBridge getNestedCollection(ConstRefIteratorIteratorBridge& bridge) { return getNestedIterator(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(CollectionIteratorBridge& bridge) { return getNestedCollection(bridge).cloneIterator(); }			
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(RefCollectionIteratorBridge& bridge) { return getNestedCollection(bridge).cloneIterator(); }			
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstCollectionIteratorBridge& bridge) { return getNestedCollection(bridge).cloneIterator(); }			
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstRefCollectionIteratorBridge& bridge) { return getNestedCollection(bridge).cloneIterator(); }			
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _nested.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _nested.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstFlatten* clone() const { return new IteratorWithFirstFlatten(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithFirstFlatten* cloneCollection() const { return new CollectionWithFirstFlatten(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IteratorWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IteratorWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = _nested.forward(steps);	
				while (count != steps) {
					if (_bridge.forward(1) == 0) {
						return count;
					}
					_nested = getNestedIterator(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); _nested = getNestedIterator(_bridge); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				size_t count = _nested.distance();	
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.backward(1) != 0) {
					count += getNestedCollection(newIteratorBridge).size();
				}
				return count;
			} 
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = _nested.backward(steps);	
				while (count != steps) {
					if (_bridge.backward(1) == 0) {
						return count;
					}
					_nested = getNestedIterator(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _bridge.rewind(); _nested = getNestedIterator(_bridge); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				size_t count = _nested.remains();	
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.forward(1) != 0) {
					count += getNestedCollection(newIteratorBridge).size();
				}
				return count;
			}
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.top() && _nested.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.eof(); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return _nested.getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return _nested.getConstFirst(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { 
				if (_nested.find_first(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.find_first(first)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { 
				if (_nested.rfind_first(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfind_first(first)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return _nested.getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return _nested.getConstSecond(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { 
				if (_nested.find_second(second)) {
					return true;
				}
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.find_second(second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { 
				if (_nested.rfind_second(second)) {
					return true;
				}
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfind_second(second)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { 
				if (_nested.find_first(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.find(first, second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { 
				if (_nested.rfind_first(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfind(first, second)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename container_first_template, typename other_second_template, typename content_template, typename     inheritance_template>
		class CollectionWithInheritance;
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithExternal is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class IteratorWithInheritance : 
		public IIterator<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IEmbeddedIterator;
			typedef content_template input_template;
			typedef IEmbeddedIterator* output_template;			
			typedef inheritance_template InheritIterator;
			typedef IEmbeddedIterator interface_type;			
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
			typedef typename internal::FirstUtility<first_template, false> FirstUtility;
			typedef typename internal::SecondUtility<second_template, false> SecondUtility;
			typedef typename internal::ContentUtility<content_template, false> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template, false> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template, false> FunctorUtility;
			
		public:
			typedef typename internal::CollectionWithInheritance<first_template, second_template, content_template, typename InheritIterator::Collection> CollectionWithInheritance;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			InheritIterator _iterator;
			
		public:
			IteratorWithInheritance(const InheritIterator& iterator) : _iterator(iterator) {}
			
			IteratorWithInheritance(parameter_input_type input) : _iterator(input) {}
			
			IteratorWithInheritance() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return InheritIterator::Bridge::cast(_iterator).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _iterator.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithInheritance* clone() const { return new IteratorWithInheritance(*this); }
			
			//! @return build the corresponding collection
			virtual CollectionWithInheritance* cloneCollection() const { return new CollectionWithInheritance(_iterator.collection()); }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				if (!good()) {
					return 0;
				}
				size_t count = 0;
				for (; count != steps && !_iterator.eof(); ++count) {
					++_iterator;
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _iterator.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _iterator.distance(); }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { 
				if (!good()) {
					return 0;
				}
				size_t count = 0;
				for (; count != steps && !_iterator.top(); ++count) {
					--_iterator;
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { _iterator.rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return _iterator.remains(); }			
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _iterator.top(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _iterator.eof(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_iterator); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_iterator); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) { return FirstUtility::find_first(_iterator, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfind_first(const_ref_first_type first) { return FirstUtility::rfind_first(_iterator, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_iterator); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_iterator); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return SecondUtility::find_second(_iterator, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfind_second(const_ref_second_type second) { return SecondUtility::rfind_second(_iterator, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(_iterator, first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfind(_iterator, first, second); }			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_iterator); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_iterator); }
		};
		
		
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class Iterator : 
		public IIterator<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::prime_type prime_first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::prime_type prime_second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		public:
			typedef typename internal::Collection<first_template, second_template, content_template> Collection;			
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class Iterator<first_template, second_template, void> : 
		public IIterator<first_template, second_template, void>
		{
		public:
			typedef void content_template;
			typedef typename internal::IIterator<first_template, second_template, content_template> IEmbeddedIterator;
			typedef content_template input_template;
			typedef IEmbeddedIterator* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
		public:
			typedef typename internal::Collection<first_template, second_template, content_template> Collection;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			bool _isBegin;
			
		public:
			Iterator() : _isBegin(false) {}
			
			Iterator(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second), _isBegin(true) {}
			
			Iterator(parameter_first_type first) : _firstContent(first), _isBegin(true) {}
			
			Iterator(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent), _isBegin(true) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* clone() const { return new Iterator(*this); }			
			
			//! @return build the corresponding collection
			virtual Collection* cloneCollection() const { return new Collection(_firstContent, _secondContent); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() ? _firstContent.where() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool find_first(const_ref_first_type first) { if (good() && _isBegin && _firstContent.getContent() == first) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! @href lazy3::internal::IPairOnFirst::rfindFirst implementation.
			virtual bool rfind_first(const_ref_first_type first) { if (good() && !_isBegin && _firstContent.getContent() == first) { _isBegin = true; return true; } else { _isBegin = true; return false; } }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool find_second(const_ref_second_type second) { if (good() && _isBegin && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! @href lazy3::internal::IPairOnFirst::rfindSecond implementation.
			virtual bool rfind_second(const_ref_second_type second) { if (good() && !_isBegin && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = true; return false; } }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { if (good() && _isBegin && _firstContent.getContent() == first && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfind(const_ref_first_type first, const_ref_second_type second) { if (good() && !_isBegin && _firstContent.getContent() == first && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = true; return false; } }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _firstContent.good() && _secondContent.good(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return good() && _isBegin; }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return !good() || !_isBegin; }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (steps && good() && _isBegin) { 
					_isBegin = false; 
					return 1; 
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { forward(1); }
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { return good() && this->top() == false; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { static content_type content; return content; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { static content_type content; return content; }
			
		public:
			//! @href lazy3::internal::IIteratorOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (steps && good() && !_isBegin) { 
					_isBegin = true; 
					return 1; 
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IIteratorOnBase::rewind implementation.
			virtual void rewind() { backward(1); }
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { return good() && this->top(); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
