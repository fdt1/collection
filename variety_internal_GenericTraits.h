/*
 *  variety_internal_GenericTraits.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


namespace variety {

	namespace internal {
	
		template<typename GenericTemplate>
		struct GenericTraits
		{
			typedef GenericTemplate ValueType;
			typedef GenericTemplate& ReferenceType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<GenericTemplate&>
		{
			typedef GenericTemplate ValueType;
			typedef GenericTemplate& ReferenceType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<const GenericTemplate>
		{
			typedef GenericTemplate ValueType;
			typedef const GenericTemplate& ReferenceType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename GenericTemplate>
		struct GenericTraits<const GenericTemplate&>
		{
			typedef GenericTemplate ValueType;
			typedef const GenericTemplate& ReferenceType;
			typedef const GenericTemplate& ConstRefType;
		};
		
		template<typename ValueType> 
		inline ValueType& get_pointer_to_reference(ValueType& value)
		{
			return value;
		}
		
		template<typename ValueType> 
		inline ValueType& get_pointer_to_reference(ValueType* value)
		{
			return *value;
		}
		
	} // namespace internal

} // namespace variety
