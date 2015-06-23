/*
 *  lazy2_Transform.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_Generic.h"
#include "lazy2_Collection.h"
#include "lazy2_Iterator.h"
#include "lazy2_internal_AccessorCallback.h"
#include "lazy2_internal_AccessorImplementation.h"
#include "lazy2_internal_InstanceImplementation.h"



namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate = ValueTemplate>
	class Accessor : 
	public Generic,
	protected internal::AccessorCallback<ValueTemplate, AssociateTemplate>
	{
		friend class Generic;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef typename internal::ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		//typedef ValueTemplate (AssociatePrimeType::*ConstMethodType)() const;
		typedef ValueTemplate (*ConstRefInFunctionType)(const AssociatePrimeType&);
		typedef ValueTemplate (*ConstFunctionType)(AssociatePrimeType);
	public:
		ValueTemplate dynamic_castFunction(const AssociatePrimeType& associate) {
			return dynamic_cast<ValuePrimeType&> (const_cast<AssociatePrimeType&>(associate));
		}
	public:
		// FIXME: fill implementation of Generic!
		Accessor() : Generic(new typename internal::AccessorImplementation<ValueTemplate, AssociateTemplate, ConstRefInFunctionType>(new internal::InstanceImplementation<ConstRefInFunctionType>(dynamic_castFunction))) {}
		Accessor(const ConstRefInFunctionType& func) : Generic(new typename internal::AccessorImplementation<ValueTemplate, AssociateTemplate, ConstRefInFunctionType>(new internal::InstanceImplementation<ConstRefInFunctionType>(func))) {}
		Accessor(const ConstFunctionType& func) : Generic(new typename internal::AccessorImplementation<ValueTemplate, AssociateTemplate, ConstFunctionType>(new internal::InstanceImplementation<const ConstFunctionType&>(func))) {}
	};
	
	
} // namespace lazy2



