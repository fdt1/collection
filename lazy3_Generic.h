/*
 *  lazy3_Generic.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_GenericAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	//--------------------------------------------------------------------------------
	//! @class Generic base for all user objects of the lazy library
	//--------------------------------------------------------------------------------
	class Generic :
	protected virtual internal::GenericAbstractBridge,
	protected internal::Bridge
	{
		friend class internal::GenericAbstractBridge;
	public:
		Generic() {}
		Generic(const internal::IGeneric* generic)
		: internal::Bridge(generic) {}
		Generic(const Generic& generic)
		: internal::Bridge(generic) {}
	public:
		//! @return true if unitialized or empty
		bool empty() const { return !this->isValid(); }
	};
	
} // namespace lazy2
