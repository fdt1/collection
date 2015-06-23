/*
 *  lazy_internal_IteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Bridge.h"
#include "lazy_internal_IteratorInterface.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class IteratorBridge :
		public virtual Bridge,
		public virtual IteratorInterface<ValueTemplate, AssociateTemplate>
		{
			virtual IteratorBridge* duplicate() const { return new IteratorBridge(*this); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy