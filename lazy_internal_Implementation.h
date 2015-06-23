/*
 *  lazy_internal_Implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


namespace lazy {
	
	namespace internal {
		
		class Implementation {
		public:
			virtual Implementation* duplicate() const = 0;
			virtual ~Implementation() {}
		};
		
	} // namespace internal
	
} // namespace lazy