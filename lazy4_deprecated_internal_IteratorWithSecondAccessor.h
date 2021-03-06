/*
 *  lazy4_internal_IteratorWithSecondAccessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_ModifierBridge.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_FunctorUtility.h"
#include "lazy4_internal_CollectionWithSecondAccessor.h"


namespace lazy4 {
	
	namespace internal {
		
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
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _modifier.isValid(); }
			
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
			virtual bool isBegin() const { return _bridge.isBegin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return _bridge.isEnd(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirst() { return FirstUtility::getFirst(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findFirst(const_ref_first_type first) { return FirstUtility::findFirst(_bridge, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindFirst(const_ref_first_type first) { return FirstUtility::rfindFirst(_bridge, first); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecond() { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecond(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecond() const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecond(_bridge)); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findSecond(const_ref_second_type second) { 
				if (isValid()) { 
					while (!isEnd()) {
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
			virtual bool rfindSecond(const_ref_second_type second) { 
				if (isValid()) { 
					while (!isBegin()) {
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
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				if (isValid()) { 
					while (!isEnd()) {
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
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second){ 
				if (isValid()) { 
					while (!isBegin()) {
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
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4