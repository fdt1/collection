/*
 *  output_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_forward_interface.h"
#include "variety_output_bridge.h"


namespace variety {
	
	template <typename value_template>
	class iterator : public virtual bridge {
	public:
		typedef iterator<value_template> iterator_type;
		typedef value_template value_type;
		typedef value_template key_type;
	private:
		implementation* _implementation;
	protected:
		virtual implementation* get_implementation() const { return _implementation; }
		virtual void set_implementation(implementation* impl) { _implementation = impl; }
	public:
		iterator() {}
		iterator(const iterator<value_type>& interf) {}
	};
	
	template <typename iterator_template>
	class output_iterator : public virtual iterator_template, public virtual output_bridge<iterator_template> {
	public:
		typedef output_iterator<iterator_template> iterator_type;
		typedef typename iterator_template::value_type value_type;
		typedef typename iterator_template::key_type key_type;
	public:	
#if 1
		output_iterator() {}
		output_iterator(const iterator<value_type>& interf) {}
#else
		bidirectional_interface(const iterator& interf) { set_interface<bidirectional_interface>(interf); }
		template <typename I>
		void set_interface(const implementation& interf) {
			if (I& itf = dynamic_cast<I&> (interf)) {
				set_implementation(itf->clone_implementation());
			} else {
				copy_implementation(interf ->implementation());
			}
		}
#endif
	};
	
	/*
	key<output<iterator<T> >, K>
	key_iterator<output_iterator<iterator<T> >, K>
	 
	access<iterator<T>, backward>
	 
	key<output_iterator<T>, K>
	*/
} // namespace variety