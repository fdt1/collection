/*
 *  lazy4_internal_Query.h
 *  Query
 *
 *  Created by Francois et Fabienne on 17/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Content.h"
#include <stdexcept>


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Query;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IFlow;
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IQuery :
		public IContent<content_template>
		{
		public:
			typedef content_template input_template;
			typedef IQuery* output_template;
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
			typedef typename internal::IFlow<first_template, second_template, content_template> IFlow;
			
		public:
			//! @return duplicate of the current implementation
			virtual IQuery* clone() const = 0;
			
			//! @return the corresponding Flow set at the beginning.
			virtual IFlow* cloneIterator() const = 0;
			
		public:
			//! count the distance between the starting point and the end Flow.
			//! @return the distance.
			virtual size_t size() const = 0;
			
			//! @return true if Query is empty.
			virtual bool empty() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		public:
			//! @return the first_type value
			virtual first_type getFirst(size_t steps) = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirst(size_t steps) const = 0;
			
			//! @return the first_type value
			virtual first_type getFirstWithThrow(size_t steps) = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirstWithThrow(size_t steps) const = 0;
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const = 0;
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const = 0;
			
		public:
			//! @return the second_type value
			virtual second_type getSecond(size_t steps) = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecond(size_t steps) const = 0;
			
			//! @return the second_type value
			virtual second_type getSecondWithThrow(size_t steps) = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecondWithThrow(size_t steps) const = 0;
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const = 0;
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Query wraps an implementation of a forward Query.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class QueryBridge :
		public Bridge<IQuery<first_template, second_template, content_template> >
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::IFlow<first_template, second_template, content_template> IFlow;
			typedef typename internal::Bridge<IEmbeddedQuery> Bridge;
		public:
			typedef IEmbeddedQuery interface_type;
			
		public:
			QueryBridge() {}
			
			QueryBridge(const IEmbeddedQuery* implementation) : Bridge(implementation) {}
			
			QueryBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline QueryBridge& operator= (const IEmbeddedQuery* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const QueryBridge& cast(const lazy4::Query<first_template, second_template, content_template>& Query) { return Query; }
			
			//! for compatibility
			static inline QueryBridge& cast(lazy4::Query<first_template, second_template, content_template>& Query) { return Query; }
			
			//! for compatibility
			static inline const QueryBridge& cast(const QueryBridge& Query) { return Query; }
			
			//! for compatibility
			static inline QueryBridge& cast(QueryBridge& Query) { return Query; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedQuery* Query = Bridge::getImplementation()) return Query->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedQuery* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedQuery* clone() const { if (const IEmbeddedQuery* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
			//! @return build the corresponding Flow
			inline IFlow* cloneIterator() const { if (const IEmbeddedQuery* Query = const_cast<QueryBridge*> (this)->Bridge::getUniqueImplementation()) return Query->cloneIterator(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IQuery
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t size() const { if (const IEmbeddedQuery* Query = Bridge::getImplementation()) return Query->size(); else return 0; }
			
			//! @href lazy3::internal::IQueryOnBase::pop
			inline bool empty() const { if (const IEmbeddedQuery* Query = Bridge::getImplementation()) return Query->empty(); else return true; }
			
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
		class FlowWithBounds;
		
		template<typename first_template, typename second_template, typename content_template>
		class FlowBridge;
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithBounds is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class QueryWithBounds : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithBounds<first_template, second_template, content_template> FlowWithBounds;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			typedef typename internal::QueryBridge<first_template, second_template, content_template> QueryBridge;
			
		public:
			FlowBridge _begin;
			FlowBridge _end;
			
		public:
			QueryWithBounds(const FlowBridge& begin, const FlowBridge& end) : _begin(begin), _end(end) {}
			
			QueryWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _begin.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithBounds* clone() const { return new QueryWithBounds(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithBounds* cloneIterator() const { return new FlowWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IQuery
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _begin.remains() - _end.remains(); }
			
			//! @return true if the Query is at the beginning.
			virtual bool empty() const { return _begin.where() == _end.where(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				FlowBridge current = _begin;
				current.forward(steps);
				return current.getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				FlowBridge current = _begin;
				current.forward(steps);
				return current.getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				FlowBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				FlowBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps)  { 
				FlowBridge current = _begin;
				current.forward(steps);
				return current.getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const  { 
				FlowBridge current = _begin;
				current.forward(steps);
				return current.getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps)  { 
				FlowBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const  { 
				FlowBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				FlowBridge current = _begin;
				return current.find_first(first);
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				FlowBridge current = _begin;
				return current.find_second(second);
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				FlowBridge current = _begin;
				return current.find(first, second);
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_begin); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_begin); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class FlowWithPermutation;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithPermutation is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class QueryWithPermutation : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithPermutation<first_template, second_template, content_template> FlowWithPermutation;
			typedef typename internal::QueryBridge<second_template, first_template, content_template> QueryBridge;
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithPermutation(const QueryBridge& bridge) : _bridge(bridge) {}
			
			QueryWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithPermutation* clone() const { return new QueryWithPermutation(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithPermutation* cloneIterator() const { return new FlowWithPermutation(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // IQuery
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the Query is at the beginning.
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
		class FlowWithStaticCast;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class QueryWithStaticCast : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FunctorUtility<internal::IQuery<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::FlowWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> FlowWithStaticCast;
			typedef typename internal::QueryBridge<old_first_template, old_second_template, old_content_template> QueryBridge;
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithStaticCast(const QueryBridge& bridge) : _bridge(bridge) {}
			
			QueryWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithStaticCast* clone() const { return new QueryWithStaticCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithStaticCast* cloneIterator() const { return new FlowWithStaticCast(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IQuery
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the Query is at the beginning.
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
		class FlowWithFirstDynamicCast;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class QueryWithFirstDynamicCast : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FunctorUtility<internal::IQuery<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::FlowWithFirstDynamicCast<first_template, second_template, content_template, old_first_template> FlowWithFirstDynamicCast;
			typedef typename internal::QueryBridge<old_first_template, second_template, content_template> QueryBridge;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithFirstDynamicCast(const QueryBridge& bridge) : _bridge(bridge) {}
			
			QueryWithFirstDynamicCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithFirstDynamicCast* clone() const { return new QueryWithFirstDynamicCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstDynamicCast* cloneIterator() const { return new FlowWithFirstDynamicCast(_bridge.cloneIterator()); }
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline FlowBridge cloneIterator(size_t steps) const { FlowWithFirstDynamicCast* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IQuery		
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const FlowWithFirstDynamicCast* Flow = cloneIterator()) {
					count = Flow->remains();
					delete Flow;
				}
				return count;
			}			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { 
				if (FlowWithFirstDynamicCast* Flow = cloneIterator()) {
					bool isEnd = Flow->eof();
					delete Flow;
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (FlowWithFirstDynamicCast* Flow = cloneIterator()) {
					bool isFound = Flow->find_first(first);
					delete Flow;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (FlowWithFirstDynamicCast* Flow = cloneIterator()) {
					bool isFound = Flow->find_second(second);
					delete Flow;
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
				if (FlowWithFirstDynamicCast* Flow = cloneIterator()) {
					bool isFound = Flow->find(first, second);
					delete Flow;
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
		class FlowWithFirstAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class QueryWithFirstAccessor :
		public IQuery<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithFirstAccessor<first_template, second_template, content_template, old_first_template, closure_template> FlowWithFirstAccessor;
			typedef typename internal::QueryBridge<old_first_template, second_template, content_template> QueryBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			QueryBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			QueryWithFirstAccessor(const QueryBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithFirstAccessor* clone() const { return new QueryWithFirstAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstAccessor* cloneIterator() const { return new FlowWithFirstAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IQuery			
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Query is at the end.
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
				if (FlowWithFirstAccessor* Flow = cloneIterator()) {
					bool isFound = Flow->find_first(first);
					delete Flow;
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
				if (FlowWithFirstAccessor* Flow = cloneIterator()) {
					bool isFound = Flow->find(first, second);
					delete Flow;
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
		class FlowWithSecondAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class QueryWithSecondAccessor :
		public IQuery<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithSecondAccessor<first_template, second_template, content_template, old_second_template, closure_template> FlowWithSecondAccessor;
			typedef typename internal::QueryBridge<first_template, old_second_template, content_template> QueryBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			QueryBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			QueryWithSecondAccessor(const QueryBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithSecondAccessor* clone() const { return new QueryWithSecondAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithSecondAccessor* cloneIterator() const { return new FlowWithSecondAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IQuery			
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Query is at the end.
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
				if (FlowWithSecondAccessor* Flow = cloneIterator()) {
					bool isFound = Flow->find_second(second);
					delete Flow;
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
				if (FlowWithSecondAccessor* Flow = cloneIterator()) {
					bool isFound = Flow->find(first, second);
					delete Flow;
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
		class FlowWithFirstFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class QueryWithFirstFilter :
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithFirstFilter<first_template, second_template, content_template, filter_template, closure_template> FlowWithFirstFilter;
			typedef typename internal::QueryBridge<first_template, second_template, content_template> QueryBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			QueryBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			QueryWithFirstFilter(const QueryBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline FlowBridge cloneIterator(size_t steps) const { FlowWithFirstFilter* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithFirstFilter* clone() const { return new QueryWithFirstFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstFilter* cloneIterator() const { return new FlowWithFirstFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IQuery		
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const FlowWithFirstFilter* Flow = cloneIterator()) {
					count = Flow->remains();
					delete Flow;
				}
				return count;
			}			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { 
				if (FlowWithFirstFilter* Flow = cloneIterator()) {
					bool isEnd = Flow->eof();
					delete Flow;
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (FlowWithFirstFilter* Flow = cloneIterator()) {
					bool isFound = Flow->find_first(first);
					delete Flow;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (FlowWithFirstFilter* Flow = cloneIterator()) {
					bool isFound = Flow->find_second(second);
					delete Flow;
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
				if (FlowWithFirstFilter* Flow = cloneIterator()) {
					bool isFound = Flow->find(first, second);
					delete Flow;
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
		class FlowWithFirstUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class QueryWithFirstUnique :
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithFirstUnique<first_template, second_template, content_template> FlowWithFirstUnique;
			typedef typename internal::QueryBridge<first_template, second_template, content_template> QueryBridge;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithFirstUnique(const QueryBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding Flow incremented
			//! param steps number of increments
			inline FlowBridge cloneIterator(size_t steps) const { FlowWithFirstUnique* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithFirstUnique* clone() const { return new QueryWithFirstUnique(*this); }
			
			//! @return the corresponding Flow
			virtual FlowWithFirstUnique* cloneIterator() const { return new FlowWithFirstUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // IQuery		
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const FlowWithFirstUnique* Flow = cloneIterator()) {
					count = Flow->remains();
					delete Flow;
				}
				return count;
			}			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { 
				if (FlowWithFirstUnique* Flow = cloneIterator()) {
					bool isEnd = Flow->eof();
					delete Flow;
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
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
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
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
		class FlowWithReverse;
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class QueryWithReverse :
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithReverse<first_template, second_template, content_template> FlowWithReverse;
			typedef typename internal::QueryBridge<first_template, second_template, content_template> QueryBridge;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithReverse(const QueryBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding Flow incremented
			//! param steps number of increments
			inline FlowBridge cloneIterator(size_t steps) const { FlowWithReverse* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithReverse* clone() const { return new QueryWithReverse(*this); }
			
			//! @return the corresponding Flow
			virtual FlowWithReverse* cloneIterator() const { return new FlowWithReverse(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithReverse(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithReverse(_bridge.getConstOutput(input)); }
			
		public: // IQuery			
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst();	}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				FlowBridge current = cloneIterator(steps);	
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const {
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
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
		class FlowWithConcatenation;
		
		
		
		//--------------------------------------------------------------------------------
		//! @class QueryWithStaticCast is an implementation of a Query to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class QueryWithConcatenation :
		public IQuery<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef typename lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
			
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
			typedef typename internal::FlowWithConcatenation<first_template, second_template, prev_content_template, next_content_template> FlowWithConcatenation;
			typedef typename internal::QueryBridge<first_template, second_template, prev_content_template> PrevQueryBridge;
			typedef typename internal::QueryBridge<first_template, second_template, next_content_template> NextQueryBridge;
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			PrevQueryBridge _prev;
			NextQueryBridge _next;
			content_template _content;
			
		public:
			QueryWithConcatenation(const PrevQueryBridge& prev, const NextQueryBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return content_template::Bridge::cast(_content).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithConcatenation* clone() const { return new QueryWithConcatenation(*this); }
			
			//! @return the corresponding Flow
			virtual FlowWithConcatenation* cloneIterator() const { return new FlowWithConcatenation(_prev.cloneIterator(), _next.cloneIterator()); }
			
			//! @return the corresponding Flow incremented
			//! param steps number of increments
			FlowBridge cloneIterator(size_t steps) const { FlowWithConcatenation* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // IQuery			
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { return _prev.size() + _next.size(); }			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { return _prev.empty() && _next.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				FlowBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
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
		class FlowWithFirstFlatten;
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithFirstFlatten is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class QueryWithFirstFlatten :
		public IQuery<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::FlowWithFirstFlatten<container_first_template, other_second_template, content_template> FlowWithFirstFlatten;
			typedef typename internal::FlowBridge<container_first_template, other_second_template, content_template> FlowBridge;
			typedef typename internal::QueryBridge<container_first_template, other_second_template, content_template> QueryBridge;
			typedef typename internal::FlowBridge<first_template, second_template, other_content_template> NestedFlowBridge;
			typedef typename internal::QueryBridge<first_template, second_template, other_content_template> NestedQueryBridge;			
			
		public:
			QueryBridge _bridge;
			
		public:
			QueryWithFirstFlatten(const QueryBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding Flow incremented
			//! param steps number of increments
			inline NestedFlowBridge cloneIterator(size_t steps) const { FlowWithFirstFlatten* Flow = cloneIterator(); Flow->forward(steps); return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual QueryWithFirstFlatten* clone() const { return new QueryWithFirstFlatten(*this); }
			
			//! @return build the corresponding Query
			virtual FlowWithFirstFlatten* cloneIterator() const { return new FlowWithFirstFlatten(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new QueryWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new QueryWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IQuery		
			//! @href lazy3::internal::IQueryOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const FlowWithFirstFlatten* Flow = cloneIterator()) {
					count = Flow->remains();
					delete Flow;
				}
				return count;
			}			
			
			//! @return true if the Query is at the end.
			virtual bool empty() const { 
				if (FlowWithFirstFlatten* Flow = cloneIterator()) {
					bool isEnd = Flow->eof();
					delete Flow;
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
				NestedFlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				NestedFlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Query::out of range");
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
				NestedFlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				NestedFlowBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Query::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (FlowWithFirstFlatten* Flow = cloneIterator()) {
					bool isFound = Flow->find_first(first);
					delete Flow;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (FlowWithFirstFlatten* Flow = cloneIterator()) {
					bool isFound = Flow->find_second(second);
					delete Flow;
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
				if (FlowWithFirstFlatten* Flow = cloneIterator()) {
					bool isFound = Flow->find(first, second);
					delete Flow;
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
		class Flow;
		
		//--------------------------------------------------------------------------------
		//! @class Query to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class Query : 
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;			
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
			typedef typename internal::Flow<first_template, second_template, content_template> Flow;		
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Query specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class Query<first_template, second_template, void > : 
		public IQuery<first_template, second_template, void >
		{
		public:
			typedef void content_template;
			typedef typename internal::IQuery<first_template, second_template, content_template> IEmbeddedQuery;
			typedef content_template input_template;
			typedef IEmbeddedQuery* output_template;
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
			typedef typename internal::Flow<first_template, second_template, content_template> Flow;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			
		public:
			Query() {}
			
			Query(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second) {}
			
			Query(parameter_first_type first) : _firstContent(first) {}
			
			Query(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Query* clone() const { return new Query(*this); }			
			
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* cloneIterator() const { return new Flow(_firstContent, _secondContent); }			
			
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
			
			//! @return true if the Query is at the beginning.
			virtual bool empty() const { return !good(); }
			
			//! @return true if the Query is at the end.
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

