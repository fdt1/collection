/*
 *  lazy4_internal_CollectionBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_PairUtility.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Collection wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionBridge :
		public Bridge<ICollection<first_template, second_template, content_template> >
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			typedef typename internal::Bridge<IEmbeddedCollection> Bridge;
		public:
			typedef IEmbeddedCollection interface_type;
			
		public:
			CollectionBridge() {}
			
			CollectionBridge(const IEmbeddedCollection* implementation) : Bridge(implementation) {}
			
			CollectionBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline CollectionBridge& operator= (const IEmbeddedCollection* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const CollectionBridge& cast(const lazy4::Collection<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline CollectionBridge& cast(lazy4::Collection<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline const CollectionBridge& cast(const lazy4::Query<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline CollectionBridge& cast(lazy4::Query<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline const CollectionBridge& cast(const CollectionBridge& collection) { return collection; }
			
			//! for compatibility
			static inline CollectionBridge& cast(CollectionBridge& collection) { return collection; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedCollection* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedCollection* clone() const { if (const IEmbeddedCollection* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
			//! @return build the corresponding iterator
			inline IIterator* cloneIterator() const { if (const IEmbeddedCollection* Collection = const_cast<CollectionBridge*> (this)->Bridge::getUniqueImplementation()) return Collection->cloneIterator(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t size() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->size(); else return 0; }
			
			//! @href lazy3::internal::ICollectionOnBase::pop
			inline bool empty() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->empty(); else return true; }
			
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
			inline bool existFirst(const_ref_first_type first) const { return FirstUtility::existFirst(*this, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			inline bool existSecond(const_ref_second_type second) const { return SecondUtility::existSecond(*this, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			inline bool existPair(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::existPair(*this, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
	} // namespace internal
	
	
} // namespace lazy4
