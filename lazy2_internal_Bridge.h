/*
 *  lazy2_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 12/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_Callback.h"
// for shared_ptr
#include <tr1/memory> 


namespace lazy2 {
	
	namespace internal {
		
		// bridge between an implementation
		class Bridge :
		public virtual Callback
		{
		private:
			std::tr1::shared_ptr<Implementation> _shared_implementation;
		public:
			Bridge(Implementation* implementation) : _shared_implementation(implementation) {}
			virtual ~Bridge() {}
		public:
			virtual const Implementation* getImplementation() const { return _shared_implementation.get(); }
			virtual Implementation* getduplicateImplementation() const { return getImplementation()->duplicate(); }
			virtual Implementation* getUniqueImplementation() { return !isUniqueImplementation() ? setImplementation(getduplicateImplementation()) : (Implementation*) getImplementation(); }
			Implementation* setImplementation(Implementation* implementation) { _shared_implementation = std::tr1::shared_ptr<Implementation>(implementation); return implementation; }
			size_t countUse() const { return _shared_implementation.use_count(); }
			bool isUniqueImplementation() const { return countUse() <= 1; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy