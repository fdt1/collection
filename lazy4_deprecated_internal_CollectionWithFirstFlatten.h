/*
 *  lazy4_internal_CollectionWithFirstFlatten.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/12/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_IteratorBridge.h"
#include "lazy4_internal_CollectionBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_IteratorWithFirstFlatten.h"
#include <stdexcept>



namespace lazy4 {
	
	template<typename first_template, typename second_template, typename content_template>
	class Iterator;
	
	template<typename first_template, typename second_template, typename content_template>
	class Collection;
	
	
	namespace internal {
		
		template<typename container_first_template, typename other_second_template, typename content_template>
		class IteratorWithFirstFlatten;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFirstFlatten is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class CollectionWithFirstFlatten :
		public ICollection<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
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
			typedef typename internal::IteratorWithFirstFlatten<container_first_template, other_second_template, content_template> IteratorWithFirstFlatten;
			typedef typename internal::IteratorBridge<container_first_template, other_second_template, content_template> IteratorBridge;
			typedef typename internal::CollectionBridge<container_first_template, other_second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, other_content_template> NestedIteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, other_content_template> NestedCollectionBridge;			
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithFirstFlatten(const CollectionBridge& bridge) : _bridge(bridge) {}
						
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline NestedIteratorBridge cloneIterator(size_t steps) const { IteratorWithFirstFlatten* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstFlatten* clone() const { return new CollectionWithFirstFlatten(*this); }
			
			//! @return build the corresponding collection
			virtual IteratorWithFirstFlatten* cloneIterator() const { return new IteratorWithFirstFlatten(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithFirstFlatten* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isEnd = iterator->isEnd();
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
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.isEnd()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.isEnd()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
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
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.isEnd()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.isEnd()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->findFirst(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->findSecond(second);
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
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->findPair(first, second);
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
		
		
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
