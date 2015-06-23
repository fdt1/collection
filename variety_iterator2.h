/*
 *  variety_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_iterator_bridge.h"
#include "variety_empty_iterator_implementation.h"
#include "variety_mutable_instance_implementation.h"
#include "variety_static_types.h"
#include "variety_cast_iterator_implementation.h"


namespace variety {
		
	template <typename value_template>
	class iterator : 
	public virtual internal::iterator_bridge<internal::static_types<value_template, value_template, iterator<value_template> > >
	{
	public:
		typedef iterator<value_template> iterator_type;
		typedef internal::static_types<value_template, value_template, iterator<value_template> > static_types;
		typedef internal::iterator_bridge<static_types> bridge_type;
	public:
		iterator() { set_implementation(new internal::empty_iterator_implementation<static_types>); }
		template <typename base_template>
		iterator(const base_template& base) { 
			internal::implementation* impl = new internal::mutable_instance_implementation<static_types, base_template> (base); 
			internal::bridge::set_implementation(impl); }
		iterator(const iterator_type& iter) { internal::bridge::set_implementation(iter.get_implementation()->duplicate()); }
		iterator& operator=(const iterator_type& iter) { internal::bridge::set_implementation(iter.get_implementation()->duplicate()); }
		template <typename value_template2>
		iterator& operator=(const iterator<value_template2>& iter) { internal::bridge::set_implementation(new internal::cast_iterator_implementation<static_types, typename iterator<value_template2>::static_types>(iter.get_implementation()->duplicate())); }
		template <typename value_template2>
		iterator(const iterator<value_template2>& iter) { internal::implementation* impl = new internal::cast_iterator_implementation<static_types, typename iterator<value_template2>::static_types>(iter.get_implementation()->duplicate()); internal::bridge::set_implementation(impl); }
	};
	
} // namespace variety