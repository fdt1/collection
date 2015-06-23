/*
 *  lazy4_internal_IDualStorage.h
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
		template <typename I, typename T, bool C, bool D>
		class IDualStorage :
		public IAssociativeStorage<I, T, C, T, I, D> 
		{
		};
		
	}
	
	
}

