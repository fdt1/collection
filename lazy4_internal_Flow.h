/*
 *  lazy4_internal_Flow.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Pair.h"
#include <map>



namespace lazy4 {
	
	template<typename first_template, typename second_template, typename container_template>
	class Flow;
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IFlow :
		public IPair<first_template, second_template>
		{
		public:
			typedef content_template input_template;
			typedef IFlow* output_template;
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
			//! @return duplicate of the current implementation
			virtual IFlow* clone() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		public:
			//! @return the content
			virtual ref_content_type getContent() = 0;
			
			//! @return the content
			virtual const_ref_content_type getConstContent() const = 0;
			
		public:
			//! remove the front element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t forward(size_t steps) = 0;
			
			//! make the flow empty.
			virtual void flush() = 0;
			
			//! @return true if the iterator is at the end or rend.
			virtual bool eof() const = 0;
			
			//! count the distance between the starting point and the current iterator.
			//! @return the distance.
			virtual size_t distance() const = 0;
			
		public:
			//! @return the first_type value
			virtual first_type getFirst() = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirst() const = 0;
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool find_first(const_ref_first_type first) = 0;
			
		public:
			//! @return the second_type value
			virtual second_type getSecond() = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecond() const = 0;
			
			//! iterate until we reach a given element.
			//! @return true if the wanted element has been met.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) = 0;
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) = 0;
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow wraps an implementation of a forward Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class FlowBridge :
		public Bridge<IFlow<first_template, second_template, content_template> >
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;
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
			typedef typename internal::IFlow<first_template, second_template, content_template> IFlow;
			typedef typename internal::IModifier<IFlow*, content_template, content_template> IModifier;
			typedef typename internal::Bridge<IEmbeddedFlow> Bridge;
			
		public:
			typedef IEmbeddedFlow interface_type;
			
		public:
			FlowBridge() {}
			
			FlowBridge(const IEmbeddedFlow* implementation) : Bridge(implementation) {}
			
			FlowBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline FlowBridge& operator= (const IEmbeddedFlow* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const FlowBridge& cast(const lazy4::Flow<first_template, second_template, content_template>& Flow) { return Flow; }
			
			//! for compatibility
			static inline FlowBridge& cast(lazy4::Flow<first_template, second_template, content_template>& Flow) { return Flow; }
			
			//! for compatibility
			static inline const FlowBridge& cast(const FlowBridge& Flow) { return Flow; }
			
			//! for compatibility
			static inline FlowBridge& cast(FlowBridge& Flow) { return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedFlow* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedFlow* clone() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->clone(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			inline size_t forward(size_t steps) { if (IEmbeddedFlow* Flow = Bridge::getUniqueImplementation()) return Flow->forward(steps); else return 0; }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			inline void flush() { if (IEmbeddedFlow* Flow = Bridge::getUniqueImplementation()) Flow->flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t distance() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->distance(); else return 0; }
			
			//! @return true if the Flow is at the end.
			inline bool eof() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->eof(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst() { return FirstUtility::getFirst(*this); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool find_first(const_ref_first_type first) { return FirstUtility::find_first(*this, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond() { return SecondUtility::getSecond(*this); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool find_second(const_ref_second_type second) { return SecondUtility::find_second(*this, second); }
			
		public:
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(*this, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithPermutation is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class FlowWithPermutation : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef internal::FlowBridge<second_template, first_template, content_template> FlowBridge;
			
		public:
			FlowBridge _bridge;
			
		public:
			FlowWithPermutation(const FlowBridge& bridge) : _bridge(bridge) {}
			
			FlowWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithPermutation* clone() const { return new FlowWithPermutation(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @return true if the Flow is at the end.
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
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return FirstUtility::find_first(_bridge, second); }
			
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
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithBounds is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class FlowWithBounds : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			FlowBridge _begin;
			FlowBridge _end;
			FlowBridge _current;
			
		public:
			FlowWithBounds(const FlowBridge& begin, const FlowBridge& end) : _begin(begin), _end(end), _current(begin) {}
			
			FlowWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _current.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithBounds* clone() const { return new FlowWithBounds(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IFlow
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
			
			//! @return true if the Flow is at the end.
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
			
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_current); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_current); }
		};
		
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class FlowWithStaticCast : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FunctorUtility<internal::IFlow<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::FlowBridge<old_first_template, old_second_template, old_content_template> FlowBridge;
			
		public:
			FlowBridge _bridge;
			
		public:
			FlowWithStaticCast(const FlowBridge& bridge) : _bridge(bridge) {}
			
			FlowWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithStaticCast* clone() const { return new FlowWithStaticCast(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @return true if the Flow is at the end.
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
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return SecondUtility::find_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { return PairUtility::find(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class FlowWithFirstDynamicCast : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FunctorUtility<internal::IFlow<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::FlowBridge<old_first_template, second_template, content_template> FlowBridge;
			typedef typename internal::DynamicCast<first_template, old_first_template> DynamicCast;
			
		public:
			FlowBridge _bridge;
			
		public:
			FlowWithFirstDynamicCast(const FlowBridge& bridge) : _bridge(bridge) {}
			
			FlowWithFirstDynamicCast() {}
			
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
			virtual FlowWithFirstDynamicCast* clone() const { return new FlowWithFirstDynamicCast(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IFlow
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
				FlowWithFirstDynamicCast* newFlow = clone();
				size_t count = newFlow->backward(-1 /* maximum size */);
				delete newFlow;
				return count;
			}			
			
			//! @return true if the Flow is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<FlowWithFirstDynamicCast*> (this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstDynamicCast*>(this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstDynamicCast*>(this)->forward(1) == 0) {
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
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class FlowWithFirstAccessor :
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<old_first_template, second_template, content_template> FlowBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			FlowBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			FlowWithFirstAccessor(const FlowBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstAccessor* clone() const { return new FlowWithFirstAccessor(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @return true if the Flow is at the end.
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
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool find_second(const_ref_second_type second) { return SecondUtility::find_second(_bridge, second); }
			
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
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class FlowWithSecondAccessor :
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<first_template, old_second_template, content_template> FlowBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			FlowBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			FlowWithSecondAccessor(const FlowBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithSecondAccessor* clone() const { return new FlowWithSecondAccessor(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @return true if the Flow is at the end.
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
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class FlowWithFirstFilter :
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			
		public:
			FlowBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			FlowWithFirstFilter(const FlowBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
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
			virtual FlowWithFirstFilter* clone() const { return new FlowWithFirstFilter(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // IFlow
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
				FlowWithFirstFilter* newFlow = clone();
				size_t count = newFlow->backward(-1 /* maximum size */);
				delete newFlow;
				return count;
			}			
			
			//! @return true if the Flow is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.eof() && !isMatch()) {
					if (const_cast<FlowWithFirstFilter*> (this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstFilter*>(this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstFilter*>(this)->forward(1) == 0) {
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
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class FlowWithFirstUnique :
		public IFlow<first_template, second_template, content_template>		
		{
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			FlowBridge _bridge;
			mutable std::map<first_type, int> _visited;
			
		public:
			FlowWithFirstUnique(const FlowBridge& bridge) : _bridge(bridge) {}
			
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
				typename std::map<first_type, int>::Flow it = _visited.find(FirstUtility::getConstFirst(_bridge));
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
			virtual FlowWithFirstUnique* clone() const { return new FlowWithFirstUnique(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // IFlow
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
				FlowWithFirstUnique* newFlow = clone();
				size_t count = newFlow->backward(-1 /* maximum size */);
				delete newFlow;
				return count;
			}			
			
			//! @return true if the Flow is at the end.
			virtual bool eof() const {
				if (!good()) {
					return true;
				}
				
				// search one that matches
				while (!isMatch()) {
					if (const_cast<FlowWithFirstUnique*> (this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstUnique*>(this)->forward(1) == 0) {
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
					if (const_cast<FlowWithFirstUnique*>(this)->forward(1) == 0) {
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
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class FlowWithConcatenation :
		public IFlow<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
			
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
			typedef typename internal::FlowBridge<first_template, second_template, prev_content_template> PrevFlowBridge;
			typedef typename internal::FlowBridge<first_template, second_template, next_content_template> NextFlowBridge;
			
		public:
			PrevFlowBridge _prev;
			NextFlowBridge _next;
			content_template _content;
			
		public:
			FlowWithConcatenation(const PrevFlowBridge& prev, const NextFlowBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _prev.eof() ? _next.where() : _prev.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good() && content_template::Bridge::cast(_content).good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithConcatenation* clone() const { return new FlowWithConcatenation(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // IFlow
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
			
			//! @return true if the Flow is at the end.
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
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithFirstFlatten is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class FlowWithFirstFlatten :
		public IFlow<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
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
			typedef typename internal::FlowBridge<container_first_template, other_second_template, content_template> FlowBridge;
			typedef typename internal::FlowBridge<first_template, second_template, other_content_template> NestedFlowBridge;
			typedef typename lazy4::Flow<first_template, second_template, other_content_template> NestedFlow;
			typedef typename internal::FlowBridge<NestedFlow, other_second_template, content_template> FlowFlowBridge;
			typedef typename internal::FlowBridge<NestedFlow&, other_second_template, content_template> RefFlowFlowBridge;
			typedef typename internal::FlowBridge<const NestedFlow&, other_second_template, content_template> ConstRefFlowFlowBridge;
			typedef typename internal::FlowBridge<const NestedFlow, other_second_template, content_template> ConstFlowFlowBridge;
			
			
		public:
			FlowBridge _bridge;
			NestedFlowBridge _nested;
			
		public:
			FlowWithFirstFlatten(const FlowBridge& bridge) : _bridge(bridge), _nested(getNestedFlow(_bridge)) {}
			
		public:			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(FlowFlowBridge& bridge) { 
				while (!bridge.eof()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(RefFlowFlowBridge& bridge) { 
				while (!bridge.eof()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(ConstFlowFlowBridge& bridge) { 
				while (!bridge.eof()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(ConstRefFlowFlowBridge& bridge) { 
				while (!bridge.eof()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.eof()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _nested.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _nested.good(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstFlatten* clone() const { return new FlowWithFirstFlatten(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = _nested.forward(steps);	
				while (count != steps) {
					if (_bridge.forward(1) == 0) {
						return count;
					}
					_nested = getNestedFlow(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); _nested = getNestedFlow(_bridge); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				size_t count = _nested.distance();	
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.backward(1) != 0) {
					count += getNestedCollection(newFlowBridge).size();
				}
				return count;
			} 
			
			//! @return true if the Flow is at the end.
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
					_nested = getNestedFlow(_bridge);
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
					_nested = getNestedFlow(_bridge);
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
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.forward(1) != 0) {
					_nested = getNestedFlow(_bridge);
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
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.backward(1) != 0) {
					_nested = getNestedFlow(_bridge);
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
					_nested = getNestedFlow(_bridge);
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
					_nested = getNestedFlow(_bridge);
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
		
		//--------------------------------------------------------------------------------
		//! @class Flow to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class Flow : 
		public IFlow<first_template, second_template, content_template>
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
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class Flow<first_template, second_template, void> : 
		public IFlow<first_template, second_template, void>
		{
		public:
			typedef void content_template;
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;
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
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			bool _isBegin;
			
		public:
			Flow() : _isBegin(false) {}
			
			Flow(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second), _isBegin(true) {}
			
			Flow(parameter_first_type first) : _firstContent(first), _isBegin(true) {}
			
			Flow(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent), _isBegin(true) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Flow* clone() const { return new Flow(*this); }			
			
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
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool find_second(const_ref_second_type second) { if (good() && _isBegin && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool find(const_ref_first_type first, const_ref_second_type second) { if (good() && _isBegin && _firstContent.getContent() == first && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _firstContent.good() && _secondContent.good(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool top() const { return good() && _isBegin; }
			
			//! @return true if the Flow is at the end.
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
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
