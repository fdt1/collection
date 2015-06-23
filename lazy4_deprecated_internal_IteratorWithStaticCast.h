/*
 *  lazy4_internal_IteratorWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 04/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_CollectionWithStaticCast.h"

namespace lazy4 {
	
	
	namespace internal {
		
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
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
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
			virtual bool isBegin() const { return _bridge.isBegin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return _bridge.isEnd(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { return FirstUtility::findFirst(_bridge, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) { return FirstUtility::rfindFirst(_bridge, first); }
		
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { return SecondUtility::findSecond(_bridge, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) { return SecondUtility::rfindSecond(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { return PairUtility::findPair(_bridge, first, second); }
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfindPair(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
