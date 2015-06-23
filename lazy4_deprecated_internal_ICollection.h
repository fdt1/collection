/*
 *  lazy4_internal_ICollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IModifier.h"


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Collection;
	
	template <typename first_template, typename second_template, typename container_template>
	class Query;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IIterator;
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ICollection :
		public IContent<content_template>
		{
		public:
			typedef content_template input_template;
			typedef ICollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			
		public:
			//! @return duplicate of the current implementation
			virtual ICollection* clone() const = 0;
			
			//! @return the corresponding Iterator set at the beginning.
			virtual IIterator* cloneIterator() const = 0;
			
		public:
			//! count the distance between the starting point and the end iterator.
			//! @return the distance.
			virtual size_t size() const = 0;
			
			//! @return true if collection is empty.
			virtual bool empty() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		public:
			//! @return the first_type value
			virtual first_type getFirst(size_t steps) = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirst(size_t steps) const = 0;
			
			//! @return the first_type value
			virtual first_type getFirstWithThrow(size_t steps) = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirstWithThrow(size_t steps) const = 0;
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const = 0;
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const = 0;
			
		public:
			//! @return the second_type value
			virtual second_type getSecond(size_t steps) = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecond(size_t steps) const = 0;
			
			//! @return the second_type value
			virtual second_type getSecondWithThrow(size_t steps) = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecondWithThrow(size_t steps) const = 0;
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const = 0;
		};
		
	} // namespace internal
	
	
} // namespace lazy4
