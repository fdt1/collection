/*
 *  lazy3_internal_FlowWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/01/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_FlowAbstractBridge.h"
#include "lazy3_internal_FlowBridge.h"
#include "lazy3_internal_IFlow.h"

namespace lazy3 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnFirst is an implementation of a flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class FlowWithStaticCastOnFirst : 
		public virtual IFlow<new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef IFlow<old_first_type, old_second_type, old_content_type> IOldFlow;
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldFlow* getIOldFlow() const = 0;
			//! @return the current implementation nested in the Bridge
			virtual IOldFlow* getUniqueIOldFlow() = 0; 
			//! @href lazy3::internal::IFlowOnFirst::getFirst
			virtual new_first_type getFirst()  { return static_cast<new_first_type> (getUniqueIOldFlow()->getFirst()); }
			//! @href lazy3::internal::IFlowOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return static_cast<const_new_first_type> (getIOldFlow()->getConstFirst()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnFirst is a dummy specialization 
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_second_type, typename new_content_type>
		class FlowWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, void, new_second_type, new_content_type> : 
		public virtual IFlow<void, new_second_type, new_content_type>,
		public FlowBridge<old_first_type, old_second_type, old_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnSecond is an implementation of a flow to overwrite 
		//! the second type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class FlowWithStaticCastOnSecond : 
		public FlowWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_second_type>::const_type const_new_second_type;
		public:
			//! @href lazy3::internal::IFlowOnFirst::getSecond
			virtual new_second_type getSecond()  { return static_cast<new_second_type> (this->getUniqueIOldFlow()->getSecond()); }
			//! @href lazy3::internal::IFlowOnFirst::getConstSecond
			virtual const_new_second_type getConstSecond() const { return static_cast<const_new_second_type> (this->getIOldFlow()->getConstSecond()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnSecond is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_content_type>
		class FlowWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type> : 
		public FlowWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnContent is an implementation of a flow to overwrite 
		//! the content type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class FlowWithStaticCastOnContent : 
		public FlowWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_content_type>::ref_type ref_new_content_type;
			typedef typename internal::Value<new_content_type>::const_ref_type const_ref_new_content_type;
			typedef typename internal::Value<new_content_type>::parameter_type parameter_new_content_type;
			typedef typename internal::Value<old_content_type>::parameter_type parameter_content_type;
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getContent() const { return static_cast<ref_new_content_type> (this->getIOldFlow()->getContent()); }
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getUniqueContent()  { return static_cast<ref_new_content_type> (this->getUniqueIOldFlow()->getUniqueContent()); }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_new_content_type getConstContent() const { return static_cast<const_ref_new_content_type> (this->getIOldFlow()->getConstContent()); }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_new_content_type setContent(parameter_new_content_type content) { return static_cast<const_ref_new_content_type> (this->getUniqueIOldFlow()->setContent(static_cast<parameter_content_type> (content))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCastOnContent is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type>
		class FlowWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void> : 
		public FlowWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class FlowWithStaticCast : 
		public FlowWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>,
		public FlowBridge<void, void, void>
		{
			typedef FlowBridge<void, void, void> FlowBridge;
			typedef IFlow<old_first_type, old_second_type, old_content_type> IOldFlow;
			typedef FlowAbstractBridge<old_first_type, old_second_type, old_content_type> OldFlowAbstractBridge;
		public:
			FlowWithStaticCast(const OldFlowAbstractBridge& flow) 
			: FlowBridge(flow) {}
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldFlow* getIOldFlow() const { return dynamic_cast<IOldFlow*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			virtual IOldFlow* getUniqueIOldFlow() { return dynamic_cast<IOldFlow*> (this->getUniqueImplementation()); } 
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
