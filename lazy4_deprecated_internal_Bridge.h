/*
 *  lazy4_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


// for shared_ptr
#include <tr1/memory> 


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Bridge hides an implementation and shared allocation
		//! strategy
		//--------------------------------------------------------------------------------
		template <typename interface_template>
		class Bridge
		{
		public:
			typedef interface_template interface_type;
			
		protected:
			std::tr1::shared_ptr<interface_template> _shared_implementation;
			
		public:
			Bridge() {}
			
			Bridge(const interface_template* implementation) : _shared_implementation(const_cast<interface_template*> (implementation)) {}
			
			~Bridge() {}
			
		public:
			Bridge& operator= (const interface_template* implementation) { _shared_implementation = std::tr1::shared_ptr<interface_template>(implementation); return *this; }
			
		public:
			//! @href lazy3::internal::IBridge::getSharedImplementation
			inline const std::tr1::shared_ptr<interface_template>& getSharedImplementation() const { return _shared_implementation; }
			
			//! @href lazy3::internal::IBridge::getImplementation
			inline const interface_template* getImplementation() const { return _shared_implementation.get(); }
			
			//! @href lazy3::internal::IBridge::duplicateImplementation
			inline interface_template* duplicateImplementation() const { return dynamic_cast<interface_template*> (getImplementation()->clone()); }
			
			//! @href lazy3::internal::IBridge::getUniqueImplementation
			inline interface_template* getUniqueImplementation() { return !isUniqueImplementation() ? setImplementation(duplicateImplementation()) : const_cast<interface_template*> (getImplementation()); }
			
			//! @href lazy3::internal::IBridge::setImplementation
			inline interface_template* setImplementation(interface_template* implementation) { _shared_implementation = std::tr1::shared_ptr<interface_template>(implementation); return implementation; }
			
			//! @href lazy3::internal::IBridge::countUse
			inline size_t countUse() const { return _shared_implementation.use_count(); }
			
			//! @href lazy3::internal::IBridge::isUniqueImplementation
			inline bool isUniqueImplementation() const { return countUse() <= 1; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4