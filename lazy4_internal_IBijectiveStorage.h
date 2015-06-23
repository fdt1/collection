/*
 *  lazy4_internal_IKeyStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/06/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IAssociativeStorage.h"



namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C = false>
		class IBijectiveStorage :
		public IAssociativeStorage<I, T, false, T, I, false>  
		{
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class IBijectiveStorage<I, T, true> :
		public IAssociativeStorage<I, T, true, Collection<const T&>, I, false> 
		{
		};
		
	}
	
	
}

