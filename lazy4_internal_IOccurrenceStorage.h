/*
 *  lazy4_internal_IOccurrenceStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy4_internal_IInheritanceStorage.h"



namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C>
		class IOccurrenceStorage :
		public IInheritanceStorage<I, T, C, false> 
		{
		};
		
	}
	
	
}

