/*
 *  variety_collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_collection_bridge.h"
#include "variety_empty_collection_implementation.h"
#include "variety_mutable_instance_implementation.h"
#include "variety_static_types.h"
#include "variety_cast_collection_implementation.h"


namespace variety {
	
	template <typename value_template>
	class collection : 
	public virtual internal::collection_bridge<internal::static_types<value_template, value_template, iterator<value_template> > >
	{
	public:
		typedef collection<value_template> collection_type;
		typedef internal::static_types<value_template, value_template, iterator<value_template> > static_types;
		typedef internal::collection_bridge<static_types> bridge_type;
	public:
		collection() { internal::bridge::set_implementation(new internal::empty_collection_implementation<static_types>); }
		template <typename base_template>
		collection(const base_template& base) { 
			internal::implementation* impl = new internal::mutable_instance_implementation<static_types, base_template> (base);
			internal::bridge::set_implementation(impl); }
		collection(const collection_type& iter) { set_implementation(iter.get_implementation()->duplicate()); }
		collection& operator=(const collection_type& iter) { set_implementation(iter.get_implementation()->duplicate()); }
		template <typename value_template2>
		collection& operator=(const collection<value_template2>& iter) { set_implementation(new internal::cast_collection_implementation<static_types, typename collection<value_template2>::static_types>(iter.get_implementation()->duplicate())); }
		template <typename value_template2>
		collection(const collection<value_template2>& iter) { internal::implementation* impl = new internal::cast_collection_implementation<static_types, typename collection<value_template2>::static_types>(iter.get_implementation()->duplicate()); internal::bridge::set_implementation(impl); }
	};
	
} // namespace variety