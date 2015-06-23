/*
 *  lazy2_internal_ValueTraits.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#define DEBUG


namespace lazy2 {
	
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
		
		template<>
		struct ValueTraits<void>
		{
			typedef void PrimeType;
			typedef void ReferenceType;
			typedef void ConstRefType;
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
	
} // namespace lazy2
