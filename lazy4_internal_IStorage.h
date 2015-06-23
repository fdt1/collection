/*
 *  lazy4_internal_IStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy4_Query.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I>
		class IStorage {
		public:
			virtual bool exist(const I& objectID) const = 0;
			virtual Query<I> all() const = 0;
			virtual bool unset(const I& objectID) = 0;
			virtual bool copy(const I& sourceID, const I& targetID) = 0;
			virtual bool move(const I& sourceID, const I& targetID) = 0;
		};
		
	}
}