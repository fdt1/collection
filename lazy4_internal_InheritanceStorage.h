/*
 *  lazy4_internal_InheritanceStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_internal_IDualStorage.h"
#include "lazy4_internal_IInheritanceStorage.h"
#include "lazy4_Iterator.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C = false, bool D = false >
		class InheritanceStorage :
		public IInheritanceStorage<I, T, C, D>
		{
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class InheritanceStorage<I, T, false, true> :
		public IInheritanceStorage<I, T, false, true>
		{
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class InheritanceStorage<I, T, true, false> :
		public IInheritanceStorage<I, T, true, false>
		{
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class InheritanceStorage<I, T, true, true> :
		public IInheritanceStorage<I, T, true, true>
		{
		};
		
	}
}