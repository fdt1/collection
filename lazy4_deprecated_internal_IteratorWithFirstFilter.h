/*
 *  lazy4_internal_IteratorWithFirstFilter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_ModifierBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_FunctorUtility.h"
#include "lazy4_internal_CollectionWithFirstFilter.h"


namespace lazy4 {
	
	namespace internal {

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
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _modifier.isValid(); }
			
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
				if (isValid()) {
					while (!isEnd() && count != steps) {
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
				if (isValid()) {
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
			virtual bool isBegin() const { return _bridge.isBegin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const {
				if (!isValid()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.isEnd() && !isMatch()) {
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
			virtual bool findFirst(const_ref_first_type first) { 
				while (_bridge.findFirst(first)) {
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
			virtual bool rfindFirst(const_ref_first_type first) { 
				while (_bridge.rfindFirst(first)) {
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
			virtual bool findSecond(const_ref_second_type second) { 
				while (_bridge.findSecond(second)) {
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
			virtual bool rfindSecond(const_ref_second_type second) { 
				while (_bridge.rfindSecond(second)) {
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
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				while (_bridge.findFirst(first)) {
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
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second){ 
				while (_bridge.rfindFirst(first)) {
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
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
