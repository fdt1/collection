/*
 *  lazy_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_Generic.h"
#include "lazy_internal_IModifier.h"
#include "lazy_internal_ModifierImplementation.h"

namespace lazy {
	
	template <typename ValueTemplate, typename NewValueTemplate = ValueTemplate, typename AssociateTemplate = bool, typename NewAssociateTemplate = bool>
	class Modifier : 
	public virtual Generic,
	protected virtual internal::ModifierImplementation<internal::IModifier<NewValueTemplate, NewAssociateTemplate>, ValueTemplate, AssociateTemplate>
	{
	protected:
		typedef typename internal::IModifier<ValueTemplate, AssociateTemplate> ModifierInterfaceType;
	public:
		Modifier() {}
		
		explicit Modifier(const Generic& generic) { 
			if (ModifierInterfaceType::isCompatible(generic)) {
				Bridge::setImplementation(generic);
			}
		}

		template<typename ValueTemplate2, typename NewValueTemplate2, typename AssociateTemplate2, typename NewAssociateTemplate2>
		Modifier<ValueTemplate, NewValueTemplate2, AssociateTemplate2, NewAssociateTemplate2> concatenate(const Modifier<ValueTemplate2, NewValueTemplate2, AssociateTemplate2, NewAssociateTemplate2>& modifier) {
			Modifier copy(*this);
			copy.setModifier(modifier);
			return copy;
		}
	};
	
} // namespace lazy
