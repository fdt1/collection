/*
 *  variety_concatenation_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_static_types.h"
#include "variety_collection_implementation.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class concatenation_implementation : public virtual collection_implementation<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef static_types_template static_types;
			typedef collection_implementation<static_types> implementation_type;
		private:
			implementation_type* _implementation_0;
			implementation_type* _implementation_1;
		public:
			concatenation_implementation(implementation_type* implementation_0, implementation_type* implementation_1) : _implementation_0(implementation_0), _implementation_1(implementation_1) {}
			virtual ~concatenation_implementation() { delete _implementation_0; delete _implementation_1; }
			virtual concatenation_implementation* duplicate() const { return new concatenation_implementation(_implementation_0->duplicate(), _implementation_1->duplicate()); }
		public: 
			// const_associative_interface methods
			virtual bool exist(const key_type& key) const { return _implementation_0->exist(key) || _implementation_1->exist(key); }
			virtual bool exist(const key_type& key, const value_type& value) const { return _implementation_0->exist(key, value) || _implementation_1->exist(key, value); }
		public:
			// const_random_interface methods
			virtual const value_type& at(int index) const { /* FIXME: return get_container().at(index);*/ }
		};		
		
	} // namespace internal
	
	
} // namespace variety