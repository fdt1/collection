/*
 *  lazy4_internal_PairWithContent.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy4_internal_IPair.h"
#include "lazy4_internal_Content.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is an implementation of IContent
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class PairWithContent : 
		public IPair<first_template, second_template>
		{
		public:
			typedef typename internal::Type<first_template>::ref_type ref_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::ref_type ref_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			
		public:
			Content<first_template> _first;
			Content<second_template> _second;
			
		public:
			PairWithContent(parameter_first_type first, parameter_second_type second) : _first(first), _second(second) {}
			
			PairWithContent() {}
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const { return isValid() ? _first.getID() : NULL; }
			
			//! @href lazy3::internal::IImplementation::duplicate
			virtual PairWithContent* clone() const { return new PairWithContent(*this); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _first.isValid() && _second.isValid(); }
			
		public:
			//! @return the first
			virtual ref_first_type getFirst() { return _first.getContent(); }
			
			//! @return the first
			virtual const_ref_first_type getConstFirst() const { return _first.getConstContent(); }
			
			//! @return the second
			virtual ref_second_type getSecond() { return _second.getContent(); }
			
			//! @return the second
			virtual const_ref_second_type getConstSecond() const { return _second.getConstContent(); }
						
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
