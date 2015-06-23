/*
 *  variety_generic_traits.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


namespace variety {
	
		
		template<typename GenericTemplate>
		struct GenericTraits
		{
			typedef GenericTemplate BaseType;
			typedef GenericTemplate& RefType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<GenericTemplate&>
		{
			typedef GenericTemplate BaseType;
			typedef GenericTemplate& RefType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<const GenericTemplate>
		{
			typedef GenericTemplate BaseType;
			typedef GenericTemplate& RefType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<const GenericTemplate&>
		{
			typedef GenericTemplate BaseType;
			typedef GenericTemplate& RefType;
			typedef const GenericTemplate& ConstRefType;
		};
		
	
} // namespace variety
