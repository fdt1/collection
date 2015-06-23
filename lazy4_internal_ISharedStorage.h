/*
 *  lazy4_internal_ISharedStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IAssociativeStorage.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C, typename E>
		class ISharedStorage :
		public IAssociativeStorage<I, T, C, I, E, C> 
		{
		public:
			virtual const T& get_value(const E& key) = 0; 
			virtual const E& get_key(const T& value) = 0; 
			virtual const T* find_value(const E& key) const = 0; 
			virtual const E* find_key(const T& value) const = 0; 
			virtual bool set_key(const E& key, const T& value) = 0; 			
			virtual bool set_key(const E& key, const T& value, const T*& new_value, T& old_value) = 0; 		
		};
				
	}
}

