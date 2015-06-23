/*
 *  lazy_internal_ValueTraits.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate>
		struct ValueTraits
		{
			typedef ValueTemplate PrimeType;
			typedef ValueTemplate& ReferenceType;
			typedef const ValueTemplate& ConstRefType;
		};
		
		template<typename ValueTemplate>
		struct ValueTraits<ValueTemplate&>
		{
			typedef ValueTemplate PrimeType;
			typedef ValueTemplate& ReferenceType;
			typedef const ValueTemplate& ConstRefType;
		};
		
		template<typename ValueTemplate>
		struct ValueTraits<const ValueTemplate>
		{
			typedef ValueTemplate PrimeType;
			typedef const ValueTemplate& ReferenceType;
			typedef const ValueTemplate& ConstRefType;
		};
		
		template<typename ValueTemplate>
		struct ValueTraits<const ValueTemplate&>
		{
			typedef ValueTemplate PrimeType;
			typedef const ValueTemplate& ReferenceType;
			typedef const ValueTemplate& ConstRefType;
		};
		
		template<typename ValueTemplate> 
		inline ValueTemplate& getPointerToReference(ValueTemplate& value)
		{
			return value;
		}
		
		template<typename ValueTemplate> 
		inline ValueTemplate& getPointerToReference(ValueTemplate* value)
		{
			return *value;
		}
		
	} // namespace internal
	
} // namespace lazy
