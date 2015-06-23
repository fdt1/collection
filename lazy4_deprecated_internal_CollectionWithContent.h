/*
 *  lazy4_internal_CollectionWithContent.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_ICollection.h"
#include "lazy4_internal_Content.h"
#include "lazy4_internal_IteratorWithContent.h"


namespace lazy4 {
	
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithContent;
		
		//--------------------------------------------------------------------------------
		//! @class Collection to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithContent : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;			
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::prime_type prime_first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::prime_type prime_second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IteratorWithContent<first_template, second_template, content_template> IteratorWithContent;		
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Collection specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class CollectionWithContent<first_template, second_template, void > : 
		public ICollection<first_template, second_template, void >
		{
		public:
			typedef void content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IteratorWithContent<first_template, second_template, content_template> IteratorWithContent;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			
		public:
			CollectionWithContent() {}
			
			CollectionWithContent(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second) {}
			
			CollectionWithContent(parameter_first_type first) : _firstContent(first) {}
			
			CollectionWithContent(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual CollectionWithContent* clone() const { return new CollectionWithContent(*this); }			
			
			//! @href lazy3::internal::ICommon::clone
			virtual IteratorWithContent* cloneIterator() const { return new IteratorWithContent(_firstContent, _secondContent); }			
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const { return isValid() ? _firstContent.getID() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _firstContent.isValid() && _secondContent.isValid(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return !isValid(); }
			
			//! @return true if the Collection is at the end.
			virtual size_t size() const { return isValid(); }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { static content_type content; return content; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { static content_type content; return content; }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const { return isValid() && _firstContent.getConstContent() == first; }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { return isValid() && _secondContent.getConstContent() == second; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { return isValid() && _firstContent.getConstContent() == first && _secondContent.getConstContent() == second; }
		};

#if 0
		//--------------------------------------------------------------------------------
		//! @class Collection specialization
		//--------------------------------------------------------------------------------
		template<typename first_template>
		class CollectionWithContent<first_template, void, first_template> : 
		public ICollection<first_template, void, first_template>
		{
		public:
			typedef void second_template;
			typedef first_template content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IteratorWithContent<first_template, second_template, content_template> IteratorWithContent;
			
		public:
			Content<first_template> _firstContent;
			
		public:
			CollectionWithContent() {}
			
			CollectionWithContent(parameter_first_type first) : _firstContent(first) {}
			
			CollectionWithContent(const Content<first_template>& firstContent) : _firstContent(firstContent) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual CollectionWithContent* clone() const { return new CollectionWithContent(*this); }			
			
			//! @href lazy3::internal::ICommon::clone
			virtual IteratorWithContent* cloneIterator() const { return new IteratorWithContent(_firstContent); }			
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const { return isValid() ? _firstContent.getID() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { static second_type second = NULL; return second; }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _firstContent.isValid(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return !isValid(); }
			
			//! @return true if the Collection is at the end.
			virtual size_t size() const { return isValid(); }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { return _firstContent.getConstContent(); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool existFirst(const_ref_first_type first) const { return isValid() && _firstContent.getConstContent() == first; }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool existSecond(const_ref_second_type second) const { return false; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool existPair(const_ref_first_type first, const_ref_second_type second) const { return isValid() && _firstContent.getConstContent() == first; }
		};
#endif
		
		
	} // namespace internal
	
	
} // namespace lazy4
