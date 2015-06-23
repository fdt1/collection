/*
 *  lazy_internal_IGeneric.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


namespace lazy {
	
	namespace internal {
		
		class IGeneric 
		{
		public:
			virtual ~IGeneric() {}
		public:
	//		ValueTemplate getValue() const { return getValuePrimeType(); }
		public:
			virtual bool isValid() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return true;
			}
		};
				
	} // namespace internal
	
	
} // namespace lazy