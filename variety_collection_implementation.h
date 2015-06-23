/*
 *  variety_collection_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_static_types.h"
#include "variety_implementation_bis.h"
#include "variety_collection_interface.h"


namespace variety {
	
	namespace internal {

		template <typename static_types_template>
		class collection_implementation : 
		public virtual implementation, 
		public virtual collection_interface<static_types_template>
		{
		public:
			typedef collection_implementation<static_types_template> implementation_type;
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
		public:
			virtual implementation_type* duplicate() const = 0;
			implementation_type* concatenate(implementation_type* impl) const;
		public:
			// default iterable_interface methods : unfortunately none for begin()
			virtual iterator_type begin() const = 0;
			virtual iterator_type end() const = 0;
			virtual size_t size() const { size_t count; for (iterator_type it = begin(); it.is_valid(); ++it) ++count; return count; }
		public: 
			// default const_associative_interface methods
			virtual bool exist(const key_type& key) const { for (iterator_type it = begin(); it.is_valid(); ++it) { if (*it == key) return true; } return false; }
			virtual bool exist(const key_type& key, const value_type& value) const { for (iterator_type it = begin(); it.is_valid(); ++it) { if (*it == key && *it == value) return true; } return false; }
		public:
			// default const_random_interface methods
			virtual const value_type& at(int index) const { iterator_type it = begin(); /*std::advance(it, index); FIXME */ return *it; }
		};		
			
	} // namespace internal
		
		
} // namespace variety


#include "variety_concatenation_implementation.h"
#include "variety_empty_collection_implementation.h"

namespace variety {
	
	namespace internal {

		template <typename static_types_template>
		class empty_collection_implementation;
		
		template <typename static_types_template>
		typename collection_implementation<static_types_template>::implementation_type* collection_implementation<static_types_template>::concatenate(implementation_type* impl) const
		{
			if (dynamic_cast<empty_collection_implementation<static_types_template>*> (impl)) {
				return duplicate();
			} else if (dynamic_cast<const empty_collection_implementation<static_types_template>*> (this)) {
				return impl->duplicate();
			} else {
				return new concatenation_implementation<static_types_template>(duplicate(), impl->duplicate());
			}
		}
		
		
	} // namespace internal
	
	
} // namespace variety

