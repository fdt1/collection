/*
 *  lazy3_internal_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_Generic.h"
#include "lazy3_internal_ModifierAbstractBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_ModifierWithLink.h"



namespace lazy3 {
	
		
	
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename old_type, typename new_type, typename internal_type = new_type>
	class Modifier :
	public Generic,
	protected virtual internal::ModifierAbstractBridge<old_type, internal_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef internal::ModifierAbstractBridge<old_type, internal_type> ModifierAbstractBridge;
		typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
	public:
		Modifier() {}
		Modifier(const internal::IModifier<old_type, internal_type>* modifier)
		: Generic(modifier) {}
		template<typename any_internal_type>
		Modifier(const Modifier<old_type, new_type, any_internal_type>& modifier)
		: Generic(modifier) {}
	public:
		//! transform a value into another value which could be of different types.
		//! @return the output value
		//! @param old_value the input value
		new_type build(parameter_old_type old_value) const { return (const_cast<Modifier*> (this))->ModifierAbstractBridge::change(old_value); }
		//! transform a value into another value which could be of different types.
		//! @return the output value
		//! @param old_value the input value
		template <typename renew_type, typename any_internal_type>
		Modifier<old_type, renew_type, any_internal_type> link(const Modifier<new_type, renew_type, any_internal_type>& modifier) const { 
			typedef typename internal::ModifierWithLink<old_type, internal_type, any_internal_type> ModifierWithLink;
			typedef typename internal::ModifierAbstractBridge<internal_type, any_internal_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new ModifierWithLink(*this, abstract_modifier); 
		}
	protected:
		Modifier(const Generic& generic) : Generic(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename old_type, typename internal_type>
	class Modifier<old_type, void, internal_type> :
	public Generic,
	protected virtual internal::ModifierAbstractBridge<old_type, internal_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void new_type;
	public:
		Modifier() {}
		template<typename any_internal_type>
		Modifier(const internal::IModifier<old_type, any_internal_type>* modifier)
		: Generic(modifier) {}
		template<typename any_new_type, typename any_internal_type>
		Modifier(const Modifier<old_type, any_new_type, any_internal_type>& modifier)
		: Generic(modifier) {}
	protected:
		Modifier(const Generic& generic) : Generic(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename new_type, typename internal_type>
	class Modifier<void, new_type, internal_type> :
	public Generic,
	protected virtual internal::ModifierAbstractBridge<void, internal_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void old_type;
	public:
		Modifier() {}
		template<typename any_old_type>
		Modifier(const internal::IModifier<any_old_type, internal_type>* modifier)
		: Generic(modifier) {}
		template<typename any_old_type>
		Modifier(const Modifier<any_old_type, new_type, internal_type>& modifier)
		: Generic(modifier) {}
	public:
		//! transform a value into another value which could be of different types.
		//! @return the output value
		//! @param old_value the input value
		template <typename renew_type, typename any_internal_type>
		Modifier<old_type, renew_type, any_internal_type> link(const Modifier<new_type, renew_type, any_internal_type>& modifier) const { 
			typedef typename internal::ModifierWithLink<old_type, internal_type, any_internal_type> ModifierWithLink;
			typedef typename internal::ModifierAbstractBridge<internal_type, any_internal_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new ModifierWithLink(*this, abstract_modifier); 
		}
	protected:
		Modifier(const Generic& generic) : Generic(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename internal_type>
	class Modifier<void, void, internal_type> :
	public Generic,
	protected virtual internal::ModifierAbstractBridge<void, internal_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void old_type;
		typedef void new_type;
	public:
		Modifier() {}
		template<typename any_old_type, typename any_internal_type>
		Modifier(const internal::IModifier<any_old_type, any_internal_type>* modifier)
		: Generic(modifier) {}
		template<typename any_old_type, typename any_new_type, typename any_internal_type>
		Modifier(const Modifier<any_old_type, any_new_type, any_internal_type>& modifier)
		: Generic(modifier) {}
	protected:
		Modifier(const Generic& generic) : Generic(generic) {}
	};

	
} // namespace lazy3