/*
 *  lazy4_internal_CollectionWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_CollectionBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_IteratorWithStaticCast.h"

namespace lazy4 {
	
	
	namespace internal {
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class IteratorWithStaticCast;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
				 typename old_first_template, typename old_second_template, typename old_content_template>
		class CollectionWithStaticCast : 
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
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::ICollection<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> IteratorWithStaticCast;
			typedef typename internal::CollectionBridge<old_first_template, old_second_template, old_content_template> CollectionBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithStaticCast(const CollectionBridge& bridge) : _bridge(bridge) {}
			
			CollectionWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithStaticCast* clone() const { return new CollectionWithStaticCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithStaticCast* cloneIterator() const { return new IteratorWithStaticCast(_bridge.cloneIterator()); }

		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the Collection is at the beginning.
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
			virtual bool existFirst(const_ref_first_type first) const { return FirstUtility::existFirst(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { return SecondUtility::existSecond(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::existPair(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
