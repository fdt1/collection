/*
 *  lazy3_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IImplementation.h"
#include "lazy3_internal_IBridge.h"
// for shared_ptr
#include <tr1/memory> 


namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Bridge hides an implementation and shared allocation
		//! strategy
		//--------------------------------------------------------------------------------
		class Bridge :
		public virtual IBridge
		{
		private:
			std::tr1::shared_ptr<IImplementation> _shared_implementation;
		public:
			Bridge() {}
			Bridge(const IImplementation* implementation) : _shared_implementation(const_cast<IImplementation*> (implementation)) {}
			Bridge(const IBridge& bridge) : _shared_implementation(bridge.getSharedImplementation()) {}
			virtual ~Bridge() {}
		public:
			//! @href lazy3::internal::IBridge::getSharedImplementation
			virtual const std::tr1::shared_ptr<IImplementation>& getSharedImplementation() const { return _shared_implementation; }
			//! @href lazy3::internal::IBridge::getImplementation
			virtual IImplementation* getImplementation() const { return _shared_implementation.get(); }
			//! @href lazy3::internal::IBridge::duplicateImplementation
			virtual IImplementation* duplicateImplementation() const { return getImplementation()->duplicate(); }
			//! @href lazy3::internal::IBridge::getUniqueImplementation
			virtual IImplementation* getUniqueImplementation() { return !isUniqueImplementation() ? setImplementation(duplicateImplementation()) : const_cast<IImplementation*> (getImplementation()); }
			//! @href lazy3::internal::IBridge::setImplementation
			virtual IImplementation* setImplementation(IImplementation* implementation) { _shared_implementation = std::tr1::shared_ptr<IImplementation>(implementation); return implementation; }
			//! @href lazy3::internal::IBridge::countUse
			virtual size_t countUse() const { return _shared_implementation.use_count(); }
			//! @href lazy3::internal::IBridge::isUniqueImplementation
			virtual bool isUniqueImplementation() const { return countUse() <= 1; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy