/*
 *  variety_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

//#include "variety_unknown.h"
#include "variety_implementation_bis.h"
#include <assert.h>

namespace variety {

	namespace internal {
		
		class bridge  {
		private:
			implementation* _implementation;
		protected:
			bridge() : _implementation(NULL) {}
			bridge(implementation* impl) : _implementation(impl) {}
			virtual ~bridge() { if (_implementation) delete _implementation; }
		public:
			virtual implementation* get_implementation() const { return _implementation; }
			//virtual void set_implementation(implementation* impl) { if (_implementation) delete _implementation; _implementation = impl; }
			template <typename unknown_template>
			unknown_template* find_implementation_interface(bool abort = false) const { 
				if (unknown_template* casted_unknown = dynamic_cast<unknown_template*> (get_implementation()))
				{
					return casted_unknown;
				} else {
					assert(!abort);
					return NULL;
				}
			}
		};
	
	} // namespace internal
	
} // namespace variety