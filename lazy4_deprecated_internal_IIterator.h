/*
 *  lazy4_internal_IIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IContent.h"
#include "lazy4_internal_IFlow.h"


namespace lazy4 {
	
	template<typename first_template, typename second_template, typename container_template>
	class Iterator;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class ICollection;
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class IIterator :
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef content_template input_template;
			typedef IIterator* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> ICollection;
			typedef typename internal::IPair<first_template, second_template> IPair;
			
		public:
			//! @return duplicate of the current implementation
			virtual IIterator* clone() const = 0;
			
			//! @return the corresponding collection of the current Iterator
			virtual ICollection* cloneCollection() const = 0;
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const = 0;
			
			//! @return the content
			virtual ref_content_type getContent() = 0;
			
			//! @return the content
			virtual const_ref_content_type getConstContent() const = 0;
			
			//! @return true if initialized
			virtual bool isValid() const = 0;	
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		public:
			//! remove the front element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t forward(size_t steps) = 0;
			
			//! make the flow empty.
			virtual void flush() = 0;
			
			//! @return true if the iterator is at the end or rend.
			virtual bool isEnd() const = 0;
			
			//! count the distance between the starting point and the current iterator.
			//! @return the distance.
			virtual size_t distance() const = 0;

		public:
			//! step backward element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t backward(size_t steps) = 0;
			
			//! make the iterator restart.
			virtual void rewind() = 0;
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const = 0;
			
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual size_t remains() const = 0;

		public:
			//! @return the first_type value
			virtual first_type getFirst() = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirst() const = 0;
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) = 0;
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) = 0;
			
		public:
			//! @return the second_type value
			virtual second_type getSecond() = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecond() const = 0;
			
			//! iterate until we reach a given element.
			//! @return true if the wanted element has been met.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) = 0;
			
			//! iterate backward until we reach a given element.
			//! @return true if the wanted element has been met.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) = 0;

		public:
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) = 0;
			
			};
		
	} // namespace internal
	
	
} // namespace lazy4
