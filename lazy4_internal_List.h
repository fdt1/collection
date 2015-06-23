/*
 *  lazy4_internal_List.h
 *  list
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Collection.h"
#include <stdexcept>


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class List;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IIndex;
		
		template<typename first_template, typename second_template, typename content_template>
		class Index;
		
		
		//--------------------------------------------------------------------------------
		//! @class Index to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IList :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef content_template input_template;
			typedef IList* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IIndex;
			
		public:
			//! @return duplicate of the current implementation
			virtual IList* clone() const = 0;
			
			//! @return the corresponding Index set at the beginning.
			virtual IIndex* cloneIterator() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class List wraps an implementation of a forward List.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ListBridge :
		public Bridge<IList<first_template, second_template, content_template> >
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::IIndex<first_template, second_template, content_template> IIndex;
			typedef typename internal::Bridge<IEmbeddedList> Bridge;
		public:
			typedef IEmbeddedList interface_type;
			
		public:
			ListBridge() {}
			
			ListBridge(const IEmbeddedList* implementation) : Bridge(implementation) {}
			
			ListBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline ListBridge& operator= (const IEmbeddedList* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const ListBridge& cast(const lazy4::List<first_template, second_template, content_template>& list) { return list; }
			
			//! for compatibility
			static inline ListBridge& cast(lazy4::List<first_template, second_template, content_template>& list) { return list; }
			
			//! for compatibility
			static inline const ListBridge& cast(const ListBridge& list) { return list; }
			
			//! for compatibility
			static inline ListBridge& cast(ListBridge& list) { return list; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedList* List = Bridge::getImplementation()) return List->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedList* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedList* clone() const { if (const IEmbeddedList* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
			//! @return build the corresponding iterator
			inline IIndex* cloneIterator() const { if (const IEmbeddedList* List = const_cast<ListBridge*> (this)->Bridge::getUniqueImplementation()) return List->cloneIterator(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IList
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t size() const { if (const IEmbeddedList* List = Bridge::getImplementation()) return List->size(); else return 0; }
			
			//! @href lazy3::internal::IListOnBase::pop
			inline bool empty() const { if (const IEmbeddedList* List = Bridge::getImplementation()) return List->empty(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst(size_t steps) { return FirstUtility::getFirst(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirstWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(*this, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond(size_t steps) { return SecondUtility::getSecond(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(*this, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			inline bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(*this, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			inline bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(*this, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			inline bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(*this, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class IndexWithBounds;
		
		template<typename first_template, typename second_template, typename content_template>
		class IndexBridge;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithBounds is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class ListWithBounds : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::IndexWithBounds<first_template, second_template, content_template> IndexWithBounds;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			
		public:
			IndexBridge _begin;
			IndexBridge _end;
			
		public:
			ListWithBounds(const IndexBridge& begin, const IndexBridge& end) : _begin(begin), _end(end) {}
			
			ListWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _begin.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithBounds* clone() const { return new ListWithBounds(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithBounds* cloneIterator() const { return new IndexWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IList
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _begin.remains() - _end.remains(); }
			
			//! @return true if the List is at the beginning.
			virtual bool empty() const { return _begin.where() == _end.where(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				IndexBridge current = _begin;
				current.forward(steps);
				return current.getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				IndexBridge current = _begin;
				current.forward(steps);
				return current.getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps)  { 
				IndexBridge current = _begin;
				current.forward(steps);
				return current.getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const  { 
				IndexBridge current = _begin;
				current.forward(steps);
				return current.getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps)  { 
				IndexBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const  { 
				IndexBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				IndexBridge current = _begin;
				return current.find_first(first);
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				IndexBridge current = _begin;
				return current.find_second(second);
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				IndexBridge current = _begin;
				return current.find(first, second);
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_begin); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_begin); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class IndexWithPermutation;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithPermutation is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class ListWithPermutation : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::FirstUtility<second_template> FirstUtility;
			typedef typename internal::SecondUtility<first_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<second_template, first_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithPermutation<first_template, second_template, content_template> IndexWithPermutation;
			typedef typename internal::ListBridge<second_template, first_template, content_template> ListBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithPermutation(const ListBridge& bridge) : _bridge(bridge) {}
			
			ListWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithPermutation* clone() const { return new ListWithPermutation(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithPermutation* cloneIterator() const { return new IndexWithPermutation(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // IList
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the List is at the beginning.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return SecondUtility::exist_second(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return FirstUtility::exist_first(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, second, first); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class IndexWithStaticCast;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class ListWithStaticCast : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::IList<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> IndexWithStaticCast;
			typedef typename internal::ListBridge<old_first_template, old_second_template, old_content_template> ListBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithStaticCast(const ListBridge& bridge) : _bridge(bridge) {}
			
			ListWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithStaticCast* clone() const { return new ListWithStaticCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithStaticCast* cloneIterator() const { return new IndexWithStaticCast(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IList
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the List is at the beginning.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class IndexWithFirstDynamicCast;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class ListWithFirstDynamicCast : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::IList<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithFirstDynamicCast<first_template, second_template, content_template, old_first_template> IndexWithFirstDynamicCast;
			typedef typename internal::ListBridge<old_first_template, second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithFirstDynamicCast(const ListBridge& bridge) : _bridge(bridge) {}
			
			ListWithFirstDynamicCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithFirstDynamicCast* clone() const { return new ListWithFirstDynamicCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithFirstDynamicCast* cloneIterator() const { return new IndexWithFirstDynamicCast(_bridge.cloneIterator()); }
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithFirstDynamicCast* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithFirstDynamicCast* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
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
		class IndexWithFirstAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class ListWithFirstAccessor :
		public IList<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithFirstAccessor<first_template, second_template, content_template, old_first_template, closure_template> IndexWithFirstAccessor;
			typedef typename internal::ListBridge<old_first_template, second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithFirstAccessor(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithFirstAccessor* clone() const { return new ListWithFirstAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithFirstAccessor* cloneIterator() const { return new IndexWithFirstAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList			
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirstWithThrow(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirstWithThrow(_bridge, steps)); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithFirstAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _bridge.exist_second(second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithFirstAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
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
		class IndexWithSecondAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class ListWithSecondAccessor :
		public IList<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::SecondUtility<old_second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<second_template, old_second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithSecondAccessor<first_template, second_template, content_template, old_second_template, closure_template> IndexWithSecondAccessor;
			typedef typename internal::ListBridge<first_template, old_second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithSecondAccessor(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithSecondAccessor* clone() const { return new ListWithSecondAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithSecondAccessor* cloneIterator() const { return new IndexWithSecondAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList			
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirst(size_t steps) { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirstWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_first(const_ref_first_type first) const { return _bridge.exist_first(first); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecond(size_t steps) { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecond(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecond(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecond(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecondWithThrow(size_t steps) { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecondWithThrow(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecondWithThrow(_bridge, steps)); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithSecondAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithSecondAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
#if 1
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class IndexWithPairAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class ListWithPairAccessor :
		public IList<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename lazy4::Pair<old_first_template, old_second_template> OldPair;
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<old_second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<Pair, OldPair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::IndexWithPairAccessor<first_template, second_template, content_template, old_first_template, old_second_template, closure_template> IndexWithPairAccessor;
			typedef typename internal::ListBridge<old_first_template, second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<Pair, OldPair, closure_template> ModifierBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithPairAccessor(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithPairAccessor* clone() const { return new ListWithPairAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithPairAccessor* cloneIterator() const { return new IndexWithPairAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithPairAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithPairAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList			
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { IndexWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { IndexWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { IndexWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { IndexWithPairAccessor* it = cloneIterator(); if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.first(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { IndexWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { IndexWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { IndexWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { IndexWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.second(); }
			
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const {
				if (IndexWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
#endif
		
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IndexWithFirstFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class ListWithFirstFilter :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::FunctorUtility<filter_template, first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithFirstFilter<first_template, second_template, content_template, filter_template, closure_template> IndexWithFirstFilter;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithFirstFilter(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithFirstFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithFirstFilter* clone() const { return new ListWithFirstFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithFirstFilter* cloneIterator() const { return new IndexWithFirstFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithFirstFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithFirstFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
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
		class IndexWithSecondFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class ListWithSecondFilter :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::FunctorUtility<filter_template, second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithSecondFilter<first_template, second_template, content_template, filter_template, closure_template> IndexWithSecondFilter;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<filter_template, second_template, closure_template> ModifierBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithSecondFilter(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithSecondFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithSecondFilter* clone() const { return new ListWithSecondFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithSecondFilter* cloneIterator() const { return new IndexWithSecondFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithSecondFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithSecondFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithSecondFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithSecondFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
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
		class IndexWithPairFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class ListWithPairFilter :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<filter_template, Pair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithPairFilter<first_template, second_template, content_template, filter_template, closure_template> IndexWithPairFilter;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::ModifierBridge<filter_template, Pair, closure_template> ModifierBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ListWithPairFilter(const ListBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithPairFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithPairFilter* clone() const { return new ListWithPairFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithPairFilter* cloneIterator() const { return new IndexWithPairFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithPairFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithPairFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithPairFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithPairFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
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
		class IndexWithFirstUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ListWithFirstUnique :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithFirstUnique<first_template, second_template, content_template> IndexWithFirstUnique;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithFirstUnique(const ListBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithFirstUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithFirstUnique* clone() const { return new ListWithFirstUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IndexWithFirstUnique* cloneIterator() const { return new IndexWithFirstUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithFirstUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithFirstUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithSecondUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ListWithSecondUnique :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithSecondUnique<first_template, second_template, content_template> IndexWithSecondUnique;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithSecondUnique(const ListBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithSecondUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithSecondUnique* clone() const { return new ListWithSecondUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IndexWithSecondUnique* cloneIterator() const { return new IndexWithSecondUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithSecondUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithSecondUnique(_bridge.getConstOutput(input)); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithSecondUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithSecondUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithPairUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ListWithPairUnique :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithPairUnique<first_template, second_template, content_template> IndexWithPairUnique;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithPairUnique(const ListBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithPairUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithPairUnique* clone() const { return new ListWithPairUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IndexWithPairUnique* cloneIterator() const { return new IndexWithPairUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithPairUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithPairUnique(_bridge.getConstOutput(input)); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithPairUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithPairUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IndexWithReverse;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ListWithReverse :
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithReverse<first_template, second_template, content_template> IndexWithReverse;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithReverse(const ListBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IndexBridge cloneIterator(size_t steps) const { IndexWithReverse* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithReverse* clone() const { return new ListWithReverse(*this); }
			
			//! @return the corresponding iterator
			virtual IndexWithReverse* cloneIterator() const { return new IndexWithReverse(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithReverse(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithReverse(_bridge.getConstOutput(input)); }
			
		public: // IList			
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst();	}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps);	
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const {
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return _bridge.exist_first(first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _bridge.exist_second(second); } 
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class IndexWithConcatenation;
		
		
		
		//--------------------------------------------------------------------------------
		//! @class ListWithStaticCast is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class ListWithConcatenation :
		public IList<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef typename lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
			
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
			typedef typename internal::IndexWithConcatenation<first_template, second_template, prev_content_template, next_content_template> IndexWithConcatenation;
			typedef typename internal::ListBridge<first_template, second_template, prev_content_template> PrevListBridge;
			typedef typename internal::ListBridge<first_template, second_template, next_content_template> NextListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			
		public:
			PrevListBridge _prev;
			NextListBridge _next;
			content_template _content;
			
		public:
			ListWithConcatenation(const PrevListBridge& prev, const NextListBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return content_template::Bridge::cast(_content).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithConcatenation* clone() const { return new ListWithConcatenation(*this); }
			
			//! @return the corresponding iterator
			virtual IndexWithConcatenation* cloneIterator() const { return new IndexWithConcatenation(_prev.cloneIterator(), _next.cloneIterator()); }
			
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			IndexBridge cloneIterator(size_t steps) const { IndexWithConcatenation* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // IList			
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { return _prev.size() + _next.size(); }			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { return _prev.empty() && _next.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IndexBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return _prev.exist_first(first) || _next.exist_first(first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _prev.exist_second(second) || _next.exist_second(second); } 
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return _prev.exist(first, second) || _next.exist(first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
		};
		
		
		template<typename container_first_template, typename other_second_template, typename content_template>
		class IndexWithFirstFlatten;
		
		
		//--------------------------------------------------------------------------------
		//! @class IndexWithFirstFlatten is an implementation of a Index to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class ListWithFirstFlatten :
		public IList<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithFirstFlatten<container_first_template, other_second_template, content_template> IndexWithFirstFlatten;
			typedef typename internal::IndexBridge<container_first_template, other_second_template, content_template> IndexBridge;
			typedef typename internal::ListBridge<container_first_template, other_second_template, content_template> ListBridge;
			typedef typename internal::IndexBridge<first_template, second_template, other_content_template> NestedIndexBridge;
			typedef typename internal::ListBridge<first_template, second_template, other_content_template> NestedListBridge;			
			
		public:
			ListBridge _bridge;
			
		public:
			ListWithFirstFlatten(const ListBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline NestedIndexBridge cloneIterator(size_t steps) const { IndexWithFirstFlatten* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithFirstFlatten* clone() const { return new ListWithFirstFlatten(*this); }
			
			//! @return build the corresponding list
			virtual IndexWithFirstFlatten* cloneIterator() const { return new IndexWithFirstFlatten(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new ListWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new ListWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IList		
			//! @href lazy3::internal::IListOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IndexWithFirstFlatten* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the List is at the end.
			virtual bool empty() const { 
				if (IndexWithFirstFlatten* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				NestedIndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				NestedIndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				NestedIndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				NestedIndexBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("List::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IndexWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IndexWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IndexWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class IndexWithInheritance;
		
		//--------------------------------------------------------------------------------
		//! @class ListWithBounds is an implementation of a List to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class ListWithInheritance : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
			typedef inheritance_template InheritList;
			typedef IEmbeddedList interface_type;			
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
			typedef typename internal::FirstUtility<first_template, false> FirstUtility;
			typedef typename internal::SecondUtility<second_template, false> SecondUtility;
			typedef typename internal::PairUtility<first_template, second_template, false> PairUtility;
			typedef typename internal::ContentUtility<content_template, false> ContentUtility;
			typedef typename internal::FunctorUtility<output_template, input_template, false> FunctorUtility;
			
		public:
			typedef typename internal::IndexWithInheritance<first_template, second_template, content_template, typename InheritList::Index> IndexWithInheritance;
			typedef typename internal::IndexBridge<first_template, second_template, content_template> IndexBridge;
			typedef typename internal::ListBridge<first_template, second_template, content_template> ListBridge;
			
		public:
			InheritList _list;
			
		public:
			ListWithInheritance(const InheritList& list) : _list(list) {}
			
			ListWithInheritance(parameter_input_type input) : _list(input) {}
			
			ListWithInheritance() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return InheritList::Bridge::cast(_list).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _list.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ListWithInheritance* clone() const { return new ListWithInheritance(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IndexWithInheritance* cloneIterator() const { return new IndexWithInheritance(_list.begin()); }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IList
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _list.size(); }
			
			//! @return true if the List is at the beginning.
			virtual bool empty() const { return _list.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return FirstUtility::getFirst(_list, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_list, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return FirstUtility::getFirstWithThrow(_list, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_list, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_list, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_list, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_list, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_list, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_list, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_list, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_list, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_list); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_list); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class List to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class List : 
		public IList<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;			
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
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::Index<first_template, second_template, content_template> Index;		
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class List specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class List<first_template, second_template, void > : 
		public IList<first_template, second_template, void >
		{
		public:
			typedef void content_template;
			typedef typename internal::IList<first_template, second_template, content_template> IEmbeddedList;
			typedef content_template input_template;
			typedef IEmbeddedList* output_template;
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
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::Index<first_template, second_template, content_template> Index;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			
		public:
			List() {}
			
			List(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second) {}
			
			List(parameter_first_type first) : _firstContent(first) {}
			
			List(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual List* clone() const { return new List(*this); }			
			
			//! @href lazy3::internal::ICommon::clone
			virtual Index* cloneIterator() const { return new Index(_firstContent, _secondContent); }			
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() ? _firstContent.where() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _firstContent.good() && _secondContent.good(); }
			
			//! @return true if the List is at the beginning.
			virtual bool empty() const { return !good(); }
			
			//! @return true if the List is at the end.
			virtual size_t size() const { return good(); }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { static content_type content; return content; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { static content_type content; return content; }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return good() && _firstContent.getConstContent() == first; }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return good() && _secondContent.getConstContent() == second; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return good() && _firstContent.getConstContent() == first && _secondContent.getConstContent() == second; }
		};
		
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
