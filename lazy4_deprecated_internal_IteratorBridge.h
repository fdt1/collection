/*
 *  lazy4_internal_IteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IIterator.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_PairUtility.h"
#include "lazy4_internal_FunctorUtility.h"

namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IteratorBridge :
		public Bridge<IIterator<first_template, second_template, content_template> >
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
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> ICollection;
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			typedef typename internal::IModifier<IIterator*, content_template, content_template> IModifier;
			typedef typename internal::Bridge<IEmbeddedIterator> Bridge;
			
		public:
			typedef IEmbeddedIterator interface_type;
		
		public:
			IteratorBridge() {}
		
			IteratorBridge(const IEmbeddedIterator* implementation) : Bridge(implementation) {}
		
			IteratorBridge(const Bridge& bridge) : Bridge(bridge) {}
		
		public:
			inline IteratorBridge& operator= (const IEmbeddedIterator* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const IteratorBridge& cast(const lazy4::Iterator<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline IteratorBridge& cast(lazy4::Iterator<first_template, second_template, content_template>& iterator) { return iterator; }
			
			//! for compatibility
			static inline const IteratorBridge& cast(const IteratorBridge& iterator) { return iterator; }
			
			//! for compatibility
			static inline IteratorBridge& cast(IteratorBridge& iterator) { return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedIterator* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedIterator* clone() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->clone(); else return NULL; }
	
			//! @return build the corresponding collection
			inline ICollection* cloneCollection() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->cloneCollection(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			inline size_t forward(size_t steps) { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) return Iterator->forward(steps); else return 0; }
	
			//! @href lazy3::internal::IFlowOnBase::flush
			inline void flush() { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) Iterator->flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t distance() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->distance(); else return 0; }
			
			//! @href lazy3::internal::IIteratorOnBase::pop
			inline size_t backward(size_t steps) { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) return Iterator->backward(steps); else return 0; }
			
			//! @href lazy3::internal::IIteratorOnBase::flush
			inline void rewind() { if (IEmbeddedIterator* Iterator = Bridge::getUniqueImplementation()) Iterator->rewind(); }	
			
			//! @href lazy3::internal::IIteratorOnBase::remains
			inline size_t remains() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->remains(); else return 0; }			
			
			//! @return true if the iterator is at the beginning.
			inline bool isBegin() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->isBegin(); else return true; }
			
			//! @return true if the iterator is at the end.
			inline bool isEnd() const { if (const IEmbeddedIterator* Iterator = Bridge::getImplementation()) return Iterator->isEnd(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst() { return FirstUtility::getFirst(*this); }
		
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool findFirst(const_ref_first_type first) { return FirstUtility::findFirst(*this, first); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool rfindFirst(const_ref_first_type first) { return FirstUtility::rfindFirst(*this, first); }

		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond() { return SecondUtility::getSecond(*this); }
		
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool findSecond(const_ref_second_type second) { return SecondUtility::findSecond(*this, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool rfindSecond(const_ref_second_type second) { return SecondUtility::rfindSecond(*this, second); }
			
		public:
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool findPair(const_ref_first_type first, const_ref_second_type second) { return PairUtility::findPair(*this, first, second); }
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool rfindPair(const_ref_first_type first, const_ref_second_type second) { return PairUtility::rfindPair(*this, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
		
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
	} // namespace internal
	
	
} // namespace lazy4
