/*
 *  variety_empty_collection_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_static_types.h"
#include "variety_collection_implementation.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class empty_collection_implementation : public virtual collection_implementation<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
		public:
			empty_collection_implementation() {}
			virtual ~empty_collection_implementation() {}
			virtual empty_collection_implementation* duplicate() const { return new empty_collection_implementation(); }
		public: 
			virtual iterator_type begin() const { assert(false); };
		public: 
			// const_associative_interface methods
			virtual bool exist(const key_type& key) const { return false; }
			virtual bool exist(const key_type& key, const value_type&) const { return false; }
		public:
			// const_random_interface methods
			virtual const value_type& at(int index) const { assert(false); }
		};		
		
	} // namespace internal
	
	
} // namespace variety