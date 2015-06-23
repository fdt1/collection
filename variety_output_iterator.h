/*
 *  variety_output.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_iterator_bridge.h"
#include "variety_output_bridge.h"
#include "variety_empty_iterator_implementation.h"
#include "variety_static_types.h"


namespace variety {
	
	template <typename iterator_template>
	class output : 
	public virtual internal::output_bridge<typename iterator_template::static_types>,
	public virtual iterator_template
	{
	public:
		typedef output<iterator_template> iterator_type;
		typedef iterator_template inherited_type;
		typedef typename iterator_template::static_types static_types;
		typedef internal::output_interface<static_types> interface_type;
	public:
		output() {}
		output(const iterator_type& iter) { set_implementation(iter.get_implementation()->duplicate()); }
		output& operator=(const iterator_type& iter) { set_implementation(iter.get_implementation()->duplicate()); }
		output(const inherited_type& iter) { iter.internal::bridge::find_implementation_interface<interface_type>(true); set_implementation(iter.get_implementation()->duplicate()); }
		output& operator=(const inherited_type& iter) { iter.internal::bridge::find_implementation_interface<interface_type>(true); set_implementation(iter.get_implementation()->duplicate()); }
	};
	
} // namespace variety