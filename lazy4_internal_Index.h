/*
 *  lazy4_internal_Index.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Iterator.h"
#include <map>


namespace lazy4 {
	
	template<typename first_template, typename second_template, typename container_template>
	class Index;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IList;
		
		template<typename first_template, typename second_template, typename content_template>
		class List;
		
		//--------------------------------------------------------------------------------
		//! @class Index to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IIndex :
		public IIterator<first_template, second_template, content_template>
		{
		public:
			typedef content_template input_template;
			typedef IIndex* output_template;
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
			typedef typename internal::IList<first_template, second_template, content_template> IList;
			typedef typename internal::IPair<first_template, second_template> IPair;
			
		public:
			//! @return duplicate of the current implementation
			virtual IIndex* clone() const = 0;
			
			//! @return the corresponding collection of the current Index
			virtual IList* cloneCollection() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Index wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IndexBridge :
		public Bridge<IIndex<first_template, second_template, content_template> >
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;
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
			typedef typename internal::IList<first_template, second_template, content_template> IList;
			typedef typename internal::IIndex<first_template, second_template, content_template> IIndex;
			typedef typename internal::IModifier<IIndex*, content_template, content_template> IModifier;
			typedef typename internal::Bridge<IEmbeddedIndex> Bridge;
			
		public:
			typedef IEmbeddedIndex interface_type;
			
		public:
			IndexBridge() {}
			
			IndexBridge(const IEmbeddedIndex* implementation) : Bridge(implementation) {}
			
			IndexBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline IndexBridge& operator= (const IEmbeddedIndex* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const IndexBridge& cast(const lazy4::Index<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline IndexBridge& cast(lazy4::Index<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline const IndexBridge& cast(const IndexBridge& iterator) { return iterator; }
			
			//! for compatibility
			static inline IndexBridge& cast(IndexBridge& iterator) { return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedIndex* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedIndex* clone() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->clone(); else return NULL; }
			
			//! @return build the corresponding collection
			inline IList* cloneCollection() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->cloneCollection(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			inline size_t forward(size_t steps) { if (IEmbeddedIndex* Index = Bridge::getUniqueImplementation()) return Index->forward(steps); else return 0; }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			inline void flush() { if (IEmbeddedIndex* Index = Bridge::getUniqueImplementation()) Index->flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t distance() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->distance(); else return 0; }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			inline size_t backward(size_t steps) { if (IEmbeddedIndex* Index = Bridge::getUniqueImplementation()) return Index->backward(steps); else return 0; }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			inline void rewind() { if (IEmbeddedIndex* Index = Bridge::getUniqueImplementation()) Index->rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			inline size_t remains() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->remains(); else return 0; }			
			
			//! @return true if the iterator is at the beginning.
			inline bool top() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->top(); else return true; }
			
			//! @return true if the iterator is at the end.
			inline bool eof() const { if (const IEmbeddedIndex* Index = Bridge::getImplementation()) return Index->eof(); else return true; }
			
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
		class ListWithPermutation;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithPermutation is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class IndexWithPermutation : 
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithPermutation<first_template, second_template, content_template> ListWithPermutation;
			typedef typename internal::IndexBridge<second_template, first_template, content_template> IndexBridge;
			
		public:
			IndexBridge _bridge;
			
		public:
			IndexWithPermutation(const IndexBridge& bridge) : _bridge(bridge) {}
			
			IndexWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithPermutation* clone() const { return new IndexWithPermutation(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithPermutation* cloneCollection() const { return new ListWithPermutation(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithBounds;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithBounds is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class IndexWithBounds : 
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithBounds<first_template, second_template, content_template> ListWithBounds;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			IndexBridge _begin;
			IndexBridge _end;
			IndexBridge _current;
			
		public:
			IndexWithBounds(const IndexBridge& begin, const IndexBridge& end) : _begin(begin), _end(end), _current(begin) {}
			
			IndexWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _current.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithBounds* clone() const { return new IndexWithBounds(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithBounds* cloneCollection() const { return new ListWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IIndex
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
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _current = _begin; }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithStaticCast;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class IndexWithStaticCast : 
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::FunctorUtility<internal::IIndex<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::ListWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> ListWithStaticCast;
			typedef typename internal::IndexBridge<old_first_template, old_second_template, old_content_template> IndexBridge;
			
		public:
			IndexBridge _bridge;
			
		public:
			IndexWithStaticCast(const IndexBridge& bridge) : _bridge(bridge) {}
			
			IndexWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithStaticCast* clone() const { return new IndexWithStaticCast(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithStaticCast* cloneCollection() const { return new ListWithStaticCast(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithFirstDynamicCast;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class IndexWithFirstDynamicCast : 
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::FunctorUtility<internal::IIndex<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::ListWithFirstDynamicCast<first_template, second_template, content_template, old_first_template> ListWithFirstDynamicCast;
			typedef typename internal::IndexBridge<old_first_template, second_template, content_template> IndexBridge;
			typedef typename internal::DynamicCast<first_template, old_first_template> DynamicCast;
			
		public:
			IndexBridge _bridge;
			
		public:
			IndexWithFirstDynamicCast(const IndexBridge& bridge) : _bridge(bridge) {}
			
			IndexWithFirstDynamicCast() {}
			
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
			virtual IndexWithFirstDynamicCast* clone() const { return new IndexWithFirstDynamicCast(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithFirstDynamicCast* cloneCollection() const { return new ListWithFirstDynamicCast(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IIndex
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
				IndexWithFirstDynamicCast* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithFirstDynamicCast* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithFirstDynamicCast*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstDynamicCast*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstDynamicCast*>(this)->forward(1) == 0) {
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
		class ListWithFirstAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class IndexWithFirstAccessor :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithFirstAccessor<first_template, second_template, content_template, old_first_template, closure_template> ListWithFirstAccessor;
			typedef typename internal::IndexBridge<old_first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithFirstAccessor(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithFirstAccessor* clone() const { return new IndexWithFirstAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithFirstAccessor* cloneCollection() const { return new ListWithFirstAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithSecondAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class IndexWithSecondAccessor :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithSecondAccessor<first_template, second_template, content_template, old_second_template, closure_template> ListWithSecondAccessor;
			typedef typename internal::IndexBridge<first_template, old_second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithSecondAccessor(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithSecondAccessor* clone() const { return new IndexWithSecondAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithSecondAccessor* cloneCollection() const { return new ListWithSecondAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithPairAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class IndexWithPairAccessor :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithPairAccessor<first_template, second_template, content_template, old_first_template, old_second_template, closure_template> ListWithPairAccessor;
			typedef typename internal::IndexBridge<old_first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<Pair, OldPair, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithPairAccessor(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithPairAccessor* clone() const { return new IndexWithPairAccessor(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithPairAccessor* cloneCollection() const { return new ListWithPairAccessor(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithPairAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithPairAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithFirstFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IndexWithFirstFilter :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithFirstFilter<first_template, second_template, content_template, filter_template, closure_template> ListWithFirstFilter;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithFirstFilter(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
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
			virtual IndexWithFirstFilter* clone() const { return new IndexWithFirstFilter(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithFirstFilter* cloneCollection() const { return new ListWithFirstFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
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
				IndexWithFirstFilter* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithFirstFilter* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithFirstFilter*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstFilter*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstFilter*>(this)->forward(1) == 0) {
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
		class ListWithSecondFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IndexWithSecondFilter :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithSecondFilter<first_template, second_template, content_template, filter_template, closure_template> ListWithSecondFilter;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<filter_template, second_template, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithSecondFilter(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
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
			virtual IndexWithSecondFilter* clone() const { return new IndexWithSecondFilter(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithSecondFilter* cloneCollection() const { return new ListWithSecondFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithSecondFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithSecondFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
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
				IndexWithSecondFilter* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithSecondFilter* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithSecondFilter*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithSecondFilter*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithSecondFilter*>(this)->forward(1) == 0) {
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
		class ListWithPairFilter;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IndexWithPairFilter :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithPairFilter<first_template, second_template, content_template, filter_template, closure_template> ListWithPairFilter;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ModifierBridge<filter_template, Pair, closure_template> ModifierBridge;
			
		public:
			IndexBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			IndexWithPairFilter(const IndexBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
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
			virtual IndexWithPairFilter* clone() const { return new IndexWithPairFilter(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithPairFilter* cloneCollection() const { return new ListWithPairFilter(_bridge.cloneCollection(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithPairFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithPairFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IIndex
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
				IndexWithPairFilter* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithPairFilter* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithPairFilter*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithPairFilter*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithPairFilter*>(this)->forward(1) == 0) {
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
		class ListWithFirstUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithFirstUnique :
		public IIndex<first_template, second_template, content_template>		
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithFirstUnique<first_template, second_template, content_template> ListWithFirstUnique;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			IndexBridge _bridge;
			mutable std::map<first_type, int> _visited;
			
		public:
			IndexWithFirstUnique(const IndexBridge& bridge) : _bridge(bridge) {}
			
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
			virtual IndexWithFirstUnique* clone() const { return new IndexWithFirstUnique(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithFirstUnique* cloneCollection() const { return new ListWithFirstUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // IIndex
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
				IndexWithFirstUnique* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithFirstUnique* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithFirstUnique*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstUnique*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithFirstUnique*>(this)->forward(1) == 0) {
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
		class ListWithSecondUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithSecondUnique :
		public IIndex<first_template, second_template, content_template>		
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithSecondUnique<first_template, second_template, content_template> ListWithSecondUnique;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			IndexBridge _bridge;
			mutable std::map<second_type, int> _visited;
			
		public:
			IndexWithSecondUnique(const IndexBridge& bridge) : _bridge(bridge) {}
			
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
			virtual IndexWithSecondUnique* clone() const { return new IndexWithSecondUnique(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithSecondUnique* cloneCollection() const { return new ListWithSecondUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithSecondUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithSecondUnique(_bridge.getConstOutput(input)); }
			
		public: // IIndex
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
				IndexWithSecondUnique* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithSecondUnique* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithSecondUnique*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithSecondUnique*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithSecondUnique*>(this)->forward(1) == 0) {
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
		class ListWithPairUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithPairUnique :
		public IIndex<first_template, second_template, content_template>		
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithPairUnique<first_template, second_template, content_template> ListWithPairUnique;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			IndexBridge _bridge;
			mutable std::map<std::pair<first_type, second_type>, int> _visited;
			
		public:
			IndexWithPairUnique(const IndexBridge& bridge) : _bridge(bridge) {}
			
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
			virtual IndexWithPairUnique* clone() const { return new IndexWithPairUnique(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithPairUnique* cloneCollection() const { return new ListWithPairUnique(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithPairUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithPairUnique(_bridge.getConstOutput(input)); }
			
		public: // IIndex
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
				IndexWithPairUnique* newIndex = clone();
				size_t count = newIndex->backward(-1 /* maximum size */);
				delete newIndex;
				return count;
			}			
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _visited.clear(); _bridge.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				IndexWithPairUnique* newIndex = clone();
				size_t count = newIndex->forward(-1 /* maximum size */);
				delete newIndex;
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
					if (const_cast<IndexWithPairUnique*> (this)->forward(1) == 0) {
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
					if (const_cast<IndexWithPairUnique*>(this)->forward(1) == 0) {
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
					if (const_cast<IndexWithPairUnique*>(this)->forward(1) == 0) {
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
		class ListWithReverse;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithReverse :
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithReverse<first_template, second_template, content_template> ListWithReverse;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
		public:
			IndexBridge _bridge;
			
		public:
			IndexWithReverse(const IndexBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline internal::IndexBridge<first_template, second_template, content_template> cloneIndex(size_t steps) const { IndexWithReverse* iterator = clone(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithReverse* clone() const { return new IndexWithReverse(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithReverse* cloneCollection() const { return new ListWithReverse(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithReverse(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithReverse(_bridge.getConstOutput(input)); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.backward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.rewind(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.remains(); }
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { return _bridge.distance(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return _bridge.eof(); }
			
			//! @return true if the iterator is at the end.
			virtual bool eof() const { return _bridge.top(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return cloneIndex(1).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return cloneIndex(1).getConstFirst(); } 
			
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
			virtual second_type getSecond() { return cloneIndex(1).getSecond(); } 
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return cloneIndex(1).getConstSecond(); } 
			
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
		class ListWithConcatenation;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithStaticCast is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class IndexWithConcatenation :
		public IIndex<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
			
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
			typedef typename internal::ListWithConcatenation<first_template, second_template, prev_content_template, next_content_template> ListWithConcatenation;
			typedef typename internal::IndexBridge<first_template, second_template, prev_content_template> PrevIndexBridge;
			typedef typename internal::IndexBridge<first_template, second_template, next_content_template> NextIndexBridge;
			
		public:
			PrevIndexBridge _prev;
			NextIndexBridge _next;
			content_template _content;
			
		public:
			IndexWithConcatenation(const PrevIndexBridge& prev, const NextIndexBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _prev.eof() ? _next.where() : _prev.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good() && content_template::Bridge::cast(_content).good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithConcatenation* clone() const { return new IndexWithConcatenation(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithConcatenation* cloneCollection() const { return new ListWithConcatenation(_prev.cloneCollection(), _next.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // IIndex
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
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = _next.backward(steps);
				if (count == steps) {					
					return count;
				} else {
					return count + _prev.backward(steps - count);
				}
			}
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _prev.rewind(); _next.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		class ListWithFirstFlatten;
		
		template<typename first_template, typename second_template, typename content_template>
		class ListBridge;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithFirstFlatten is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class IndexWithFirstFlatten :
		public IIndex<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
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
			typedef typename internal::ListWithFirstFlatten<container_first_template, other_second_template, content_template> ListWithFirstFlatten;
			typedef typename internal::IndexBridge<container_first_template, other_second_template, content_template> IndexBridge;
			typedef typename internal::IndexBridge<first_template, second_template, other_content_template> NestedIndexBridge;
			typedef typename internal::ListBridge<first_template, second_template, other_content_template> NestedListBridge;
			typedef typename lazy4::Index<first_template, second_template, other_content_template> NestedIndex;
			typedef typename lazy4::List<first_template, second_template, other_content_template> NestedList;
			typedef typename internal::IndexBridge<NestedIndex, other_second_template, content_template> IndexIndexBridge;
			typedef typename internal::IndexBridge<NestedList, other_second_template, content_template> ListIndexBridge;
			typedef typename internal::IndexBridge<NestedIndex&, other_second_template, content_template> RefIndexIndexBridge;
			typedef typename internal::IndexBridge<NestedList&, other_second_template, content_template> RefListIndexBridge;
			typedef typename internal::IndexBridge<const NestedIndex&, other_second_template, content_template> ConstRefIndexIndexBridge;
			typedef typename internal::IndexBridge<const NestedList&, other_second_template, content_template> ConstRefListIndexBridge;
			typedef typename internal::IndexBridge<const NestedIndex, other_second_template, content_template> ConstIndexIndexBridge;
			typedef typename internal::IndexBridge<const NestedList, other_second_template, content_template> ConstListIndexBridge;
			
			
		public:
			IndexBridge _bridge;
			NestedIndexBridge _nested;
			
		public:
			IndexWithFirstFlatten(const IndexBridge& bridge) : _bridge(bridge), _nested(getNestedIndex(_bridge)) {}
			
		public:
			//! cast for compatibility
			static inline NestedListBridge getNestedList(ListIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedListBridge nested = NestedListBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(RefListIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedListBridge nested = NestedListBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(ConstListIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedListBridge nested = NestedListBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(ConstRefListIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedListBridge nested = NestedListBridge::cast(bridge.getFirst());
					if (!nested.empty()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(IndexIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIndexBridge nested = NestedIndexBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(RefIndexIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIndexBridge nested = NestedIndexBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(ConstIndexIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIndexBridge nested = NestedIndexBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(ConstRefIndexIndexBridge& bridge) { 
				while (!bridge.eof()) {
					NestedIndexBridge nested = NestedIndexBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(IndexIndexBridge& bridge) { return getNestedIndex(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(RefIndexIndexBridge& bridge) { return getNestedIndex(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(ConstIndexIndexBridge& bridge) { return getNestedIndex(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedListBridge getNestedList(ConstRefIndexIndexBridge& bridge) { return getNestedIndex(bridge).cloneCollection(); }			
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(ListIndexBridge& bridge) { return getNestedList(bridge).cloneIndex(); }			
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(RefListIndexBridge& bridge) { return getNestedList(bridge).cloneIndex(); }			
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(ConstListIndexBridge& bridge) { return getNestedList(bridge).cloneIndex(); }			
			
			//! cast for compatibility
			static inline NestedIndexBridge getNestedIndex(ConstRefListIndexBridge& bridge) { return getNestedList(bridge).cloneIndex(); }			
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _nested.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _nested.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithFirstFlatten* clone() const { return new IndexWithFirstFlatten(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithFirstFlatten* cloneCollection() const { return new ListWithFirstFlatten(_bridge.cloneCollection()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new IndexWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new IndexWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IIndex
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = _nested.forward(steps);	
				while (count != steps) {
					if (_bridge.forward(1) == 0) {
						return count;
					}
					_nested = getNestedIndex(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); _nested = getNestedIndex(_bridge); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				size_t count = _nested.distance();	
				IndexBridge newIndexBridge = _bridge;
				while (newIndexBridge.backward(1) != 0) {
					count += getNestedList(newIndexBridge).size();
				}
				return count;
			} 
			
			//! @href lazy3::internal::IIndexOnBase::pop
			virtual size_t backward(size_t steps) { 
				size_t count = _nested.backward(steps);	
				while (count != steps) {
					if (_bridge.backward(1) == 0) {
						return count;
					}
					_nested = getNestedIndex(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _bridge.rewind(); _nested = getNestedIndex(_bridge); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { 
				size_t count = _nested.remains();	
				IndexBridge newIndexBridge = _bridge;
				while (newIndexBridge.forward(1) != 0) {
					count += getNestedList(newIndexBridge).size();
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
					_nested = getNestedIndex(_bridge);
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
					_nested = getNestedIndex(_bridge);
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
				IndexBridge newIndexBridge = _bridge;
				while (newIndexBridge.forward(1) != 0) {
					_nested = getNestedIndex(_bridge);
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
				IndexBridge newIndexBridge = _bridge;
				while (newIndexBridge.backward(1) != 0) {
					_nested = getNestedIndex(_bridge);
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
					_nested = getNestedIndex(_bridge);
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
					_nested = getNestedIndex(_bridge);
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
		class ListWithInheritance;
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithExternal is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class IndexWithInheritance : 
		public IIndex<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;			
			typedef inheritance_template InheritIndex;
			typedef IEmbeddedIndex interface_type;			
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
			typedef typename internal::ListWithInheritance<first_template, second_template, content_template, typename InheritIndex::List> ListWithInheritance;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			InheritIndex _iterator;
			
		public:
			IndexWithInheritance(const InheritIndex& iterator) : _iterator(iterator) {}
			
			IndexWithInheritance(parameter_input_type input) : _iterator(input) {}
			
			IndexWithInheritance() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return InheritIndex::Bridge::cast(_iterator).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _iterator.good(); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithInheritance* clone() const { return new IndexWithInheritance(*this); }
			
			//! @return build the corresponding collection
			virtual ListWithInheritance* cloneCollection() const { return new ListWithInheritance(_iterator.collection()); }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IIndex
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
			
			//! @href lazy3::internal::IIndexOnBase::pop
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
			
			//! @href lazy3::internal::IIndexOnBase::flush
			virtual void rewind() { _iterator.rewind(); }	
			
			//! @href lazy3::internal::IIndexOnBase::remains
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
		//! @class Index to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class Index : 
		public IIndex<first_template, second_template, content_template>
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
			typedef typename internal::List<first_template, second_template, content_template> List;			
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Index specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class Index<first_template, second_template, void> : 
		public IIndex<first_template, second_template, void>
		{
		public:
			typedef void content_template;
			typedef typename internal::IIndex<first_template, second_template, content_template> IEmbeddedIndex;
			typedef content_template input_template;
			typedef IEmbeddedIndex* output_template;
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
			typedef typename internal::List<first_template, second_template, content_template> List;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			bool _isBegin;
			
		public:
			Index() : _isBegin(false) {}
			
			Index(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second), _isBegin(true) {}
			
			Index(parameter_first_type first) : _firstContent(first), _isBegin(true) {}
			
			Index(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent), _isBegin(true) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Index* clone() const { return new Index(*this); }			
			
			//! @return build the corresponding collection
			virtual List* cloneCollection() const { return new List(_firstContent, _secondContent); }
			
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
			//! @href lazy3::internal::IIndexOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (steps && good() && !_isBegin) { 
					_isBegin = true; 
					return 1; 
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IIndexOnBase::rewind implementation.
			virtual void rewind() { backward(1); }
			
			//! @href lazy3::internal::IIndexOnBase::remains
			virtual size_t remains() const { return good() && this->top(); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
