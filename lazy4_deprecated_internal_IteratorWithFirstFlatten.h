/*
 *  lazy4_internal_IteratorWithFirstFlatten.h
 *  collection
 *
 *  Created by Francois et Fabienne on 03/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_CollectionBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_CollectionWithFirstFlatten.h"



namespace lazy4 {
	
	template<typename first_template, typename second_template, typename content_template>
	class Iterator;

	template<typename first_template, typename second_template, typename content_template>
	class Collection;
	
	
	namespace internal {
		
		template<typename container_first_template, typename other_second_template, typename content_template>
		class CollectionWithFirstFlatten;
		
	
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
				while (!bridge.isEnd()) {
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
				while (!bridge.isEnd()) {
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
				while (!bridge.isEnd()) {
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
				while (!bridge.isEnd()) {
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
				while (!bridge.isEnd()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(RefIteratorIteratorBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstIteratorIteratorBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedIteratorBridge getNestedIterator(ConstRefIteratorIteratorBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedIteratorBridge nested = NestedIteratorBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
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
			virtual const void* getID() const { return _nested.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _nested.isValid(); }
			
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
			virtual bool isBegin() const { return _bridge.isBegin() && _nested.isBegin(); }
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const { return _bridge.isEnd(); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return _nested.getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return _nested.getConstFirst(); }
				
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { 
				if (_nested.findFirst(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.findFirst(first)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) { 
				if (_nested.rfindFirst(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfindFirst(first)) {
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
			virtual bool findSecond(const_ref_second_type second) { 
				if (_nested.findSecond(second)) {
					return true;
				}
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.findSecond(second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) { 
				if (_nested.rfindSecond(second)) {
					return true;
				}
				IteratorBridge newIteratorBridge = _bridge;
				while (newIteratorBridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfindSecond(second)) {
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
				if (_nested.findFirst(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					if (_nested.findPair(first, second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { 
				if (_nested.rfindFirst(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedIterator(_bridge);
					_nested.flush();
					if (_nested.rfindPair(first, second)) {
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
