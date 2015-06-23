/*
 *  lazy4_internal_CollectionWithBounds.h
 *  collection
 *
 *  Created by Francois et Fabienne on 12/01/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_CollectionBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_IteratorWithBounds.h"
#include "lazy4_internal_IteratorBridge.h"
#include <stdexcept>

namespace lazy4 {
	
	
	namespace internal {
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class IteratorWithBounds;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithBounds is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class CollectionWithBounds : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
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
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithBounds<first_template, second_template, content_template> IteratorWithBounds;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			
		public:
			IteratorBridge _begin;
			IteratorBridge _end;
			
		public:
			CollectionWithBounds(const IteratorBridge& begin, const IteratorBridge& end) : _begin(begin), _end(end) {}
			
			CollectionWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _begin.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _begin.isValid() && _end.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithBounds* clone() const { return new CollectionWithBounds(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithBounds* cloneIterator() const { return new IteratorWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _begin.remains() - _end.remains(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return _begin.getID() == _end.getID(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.isEnd()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.isEnd()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps)  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps)  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.isEnd()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.isEnd()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const { 
				IteratorBridge current = _begin;
				return current.findFirst(first);
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { 
				IteratorBridge current = _begin;
				return current.findSecond(second);
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { 
				IteratorBridge current = _begin;
				return current.findPair(first, second);
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_begin); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_begin); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
