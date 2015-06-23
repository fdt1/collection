/*
 *  lazy3_internal_IteratorWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IteratorAbstractBridge.h"
#include "lazy3_internal_IteratorBridge.h"
#include "lazy3_internal_IIterator.h"

namespace lazy3 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnFirst is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class IteratorWithStaticCastOnFirst : 
		public virtual IIterator<new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef IIterator<old_first_type, old_second_type, old_content_type> IOldIterator;
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldIterator* getIOldIterator() const = 0;
			//! @return the current implementation nested in the Bridge
			virtual IOldIterator* getUniqueIOldIterator() = 0; 
			//! @href lazy3::internal::IIteratorOnFirst::getFirst
			virtual new_first_type getFirst()  { return static_cast<new_first_type> (getUniqueIOldIterator()->getFirst()); }
			//! @href lazy3::internal::IIteratorOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return static_cast<const_new_first_type> (getIOldIterator()->getConstFirst()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnFirst is a dummy specialization 
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_second_type, typename new_content_type>
		class IteratorWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, void, new_second_type, new_content_type> : 
		public virtual IIterator<void, new_second_type, new_content_type>,
		public IteratorBridge<old_first_type, old_second_type, old_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnSecond is an implementation of a Iterator to overwrite 
		//! the second type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class IteratorWithStaticCastOnSecond : 
		public IteratorWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_second_type>::const_type const_new_second_type;
		public:
			//! @href lazy3::internal::IIteratorOnFirst::getSecond
			virtual new_second_type getSecond()  { return static_cast<new_second_type> (this->getUniqueIOldIterator()->getSecond()); }
			//! @href lazy3::internal::IIteratorOnFirst::getConstSecond
			virtual const_new_second_type getConstSecond() const { return static_cast<const_new_second_type> (this->getIOldIterator()->getConstSecond()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnSecond is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_content_type>
		class IteratorWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type> : 
		public IteratorWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnContent is an implementation of a Iterator to overwrite 
		//! the content type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class IteratorWithStaticCastOnContent : 
		public IteratorWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_content_type>::ref_type ref_new_content_type;
			typedef typename internal::Value<new_content_type>::const_ref_type const_ref_new_content_type;
			typedef typename internal::Value<new_content_type>::parameter_type parameter_new_content_type;
			typedef typename internal::Value<old_content_type>::parameter_type parameter_content_type;
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getContent() const { return static_cast<ref_new_content_type> (this->getIOldIterator()->getContent()); }
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getUniqueContent()  { return static_cast<ref_new_content_type> (this->getUniqueIOldIterator()->getUniqueContent()); }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_new_content_type getConstContent() const { return static_cast<const_ref_new_content_type> (this->getIOldIterator()->getConstContent()); }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_new_content_type setContent(parameter_new_content_type content) { return static_cast<const_ref_new_content_type> (this->getUniqueIOldIterator()->setContent(static_cast<parameter_content_type> (content))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCastOnContent is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type>
		class IteratorWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void> : 
		public IteratorWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class IteratorWithStaticCast : 
		public IteratorWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>,
		public IteratorBridge<void, void, void>
		{
			typedef IteratorBridge<void, void, void> IteratorBridge;
			typedef IIterator<old_first_type, old_second_type, old_content_type> IOldIterator;
			typedef IIterator<new_first_type, new_second_type, new_content_type> INewIterator;
			typedef IteratorAbstractBridge<old_first_type, old_second_type, old_content_type> OldIteratorAbstractBridge;
			typedef typename internal::Value<new_content_type>::parameter_type parameter_new_content_type;
			typedef typename internal::Value<old_content_type>::parameter_type parameter_old_content_type;
			typedef INewIterator* change_type;
		public:
			IteratorWithStaticCast(const OldIteratorAbstractBridge& Iterator) 
			: IteratorBridge(Iterator) {}
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldIterator* getIOldIterator() const { return dynamic_cast<IOldIterator*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			virtual IOldIterator* getUniqueIOldIterator() { return dynamic_cast<IOldIterator*> (this->getUniqueImplementation()); } 
			//! @href lazy3::internal::IModifierOnBase::change
			virtual change_type change(parameter_new_content_type new_content) { IteratorWithStaticCast* newElement = new IteratorWithStaticCast(*this); newElement->setContent(new_content); return newElement; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
