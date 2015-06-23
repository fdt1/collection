/*
 *  lazy4_internal_DynamicCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

namespace lazy4 {
	
	
	namespace internal {
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> (& ((ref_old_first) first)) != NULL; }
			static first_template convert(const_ref_old_first first) { return *(dynamic_cast<pointer_first> (& ((ref_old_first) first))); }
		};
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast<first_template, old_first_template*> {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template*>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template*>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> ((ref_old_first) first) != NULL; }
			static first_template convert(const_ref_old_first first) { return (dynamic_cast<pointer_first> ((ref_old_first) first)); }
		};
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast<first_template, old_first_template* const> {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template* const>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template* const>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> ((ref_old_first) first) != NULL; }
			static first_template convert(const_ref_old_first first) { return (dynamic_cast<pointer_first> ((ref_old_first) first)); }
		};
		
	}
}