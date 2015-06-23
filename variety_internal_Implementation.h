/*
 *  variety_internal_Implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once


namespace variety {
	
	namespace internal {
		
		class Implementation {
		public:
			virtual Implementation* duplicate() const = 0;
			virtual std::string get_name() const = 0;
			virtual ~Implementation() {}
		};
		
	} // namespace internal
	
} // namespace variety