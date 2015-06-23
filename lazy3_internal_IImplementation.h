/*
 *  lazy3_internal_Implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		class IImplementation
		{
		public:
			virtual ~IImplementation() {}
		public:
			//! @return duplicate of the nested implementation
			virtual IImplementation* duplicate() const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2