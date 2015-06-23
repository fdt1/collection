/*
 *  lazy_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Implementation.h"
// for shared_ptr
#include <tr1/memory> 


namespace lazy {
	
	namespace internal {
		
		// bridge between an implementation
		class Bridge 
		{
		private:
			std::tr1::shared_ptr<Implementation> _shared_implementation;
		public:
			virtual ~Bridge() {}
		public:
			const Implementation* getImplementation() const { return _shared_implementation.get(); }
			Implementation* duplicateImplementation() const { return getImplementation()->duplicate(); }
			Implementation* getUniqueImplementation() const { return isUniqueImplementation() ? duplicateImplementation() : (Implementation*) getImplementation(); }
			void setImplementation(Implementation* implementation) { _shared_implementation = std::tr1::shared_ptr<Implementation>(implementation); }
			void setImplementation(const Bridge& bridge) { _shared_implementation = bridge._shared_implementation; }
			size_t countUse() const { return _shared_implementation.use_count(); }
			bool isUniqueImplementation() const { return countUse() <= 1; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy