/*
 *  lazy4_internal_OccurrenceStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_internal_IInheritanceStorage.h"
#include "lazy4_internal_IOccurrenceStorage.h"
#include "lazy4_Iterator.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C = false >
		class OccurrenceStorage :
		public IOccurrenceStorage<I, T, C>
		{
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class OccurrenceStorage<I, T, true> :
		public IOccurrenceStorage<I, T, true>
		{
		};
		
	}
}