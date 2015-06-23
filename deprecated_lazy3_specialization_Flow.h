/*
 *  lazy3_specialization_Flow.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#if 0
#include "lazy3_Generic.h"
#include "lazy3_internal_Flow.h"

namespace lazy3 {
	
	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with container_type to void
	//--------------------------------------------------------------------------------
	template <typename first_type, typename second_type>
	class Flow<first_type, second_type, void> :
	public Generic,
	protected virtual internal::Flow<first_type, second_type, void>
	{
		typedef internal::Flow<first_type, second_type, void> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! @return pop and the first_type value
		first_type pop_first() { return InternalFlow::popFirst(); }
		//! @return pop and the second_type value
		second_type pop_second() { return InternalFlow::popSecond(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with second_type to void
	//--------------------------------------------------------------------------------
	template <typename first_type, typename container_type>
	class Flow<first_type, void, container_type> :
	public Generic,
	protected virtual internal::Flow<first_type, void, container_type>
	{
		typedef internal::Flow<first_type, void, container_type> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! @return pop and the first_type value
		first_type pop_first() { return InternalFlow::popFirst(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
		//! @return the prime container
		container_type container() const { return InternalFlow::container(); }
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with first_type to void
	//--------------------------------------------------------------------------------
	template <typename second_type, typename container_type>
	class Flow<void, second_type, container_type> :
	public Generic,
	protected virtual internal::Flow<void, second_type, container_type>
	{
		typedef internal::Flow<void, second_type, container_type> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! @return pop and the second_type value
		second_type pop_second() { return InternalFlow::popSecond(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
		//! @return the prime container
		container_type container() const { return InternalFlow::container(); }
	};
	


	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with container_type and second_type to void
	//--------------------------------------------------------------------------------
	template <typename first_type>
	class Flow<first_type, void, void> :
	public Generic,
	protected virtual internal::Flow<first_type, void, void>
	{
		typedef internal::Flow<first_type, second_type, void> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! @return pop and the first_type value
		first_type pop_first() { return InternalFlow::popFirst(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with second_type to void
	//--------------------------------------------------------------------------------
	template <typename container_type>
	class Flow<void, void, container_type> :
	public Generic,
	protected virtual internal::Flow<void, void, container_type>
	{
		typedef internal::Flow<void, void, container_type> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
		//! @return the prime container
		container_type container() const { return InternalFlow::container(); }
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow is specialization a forward iterator
	//! with first_type to void
	//--------------------------------------------------------------------------------
	template <typename second_type, typename container_type>
	class Flow<void, second_type, container_type> :
	public Generic,
	protected virtual internal::Flow<void, second_type, container_type>
	{
		typedef internal::Flow<void, second_type, container_type> InternalFlow;
	public:
		//! remove the front element of the flow
		void pop() { InternalFlow::pop(); }
		//! @return pop and the first_type value
		first_type pop_first() { return InternalFlow::popFirst(); }
		//! @return pop and the second_type value
		second_type pop_second() { return InternalFlow::popSecond(); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		size_t flush() { return InternalFlow::flush(); }
		//! @return the prime container
		container_type container() const { return InternalFlow::container(); }
	};
	
	


} // namespace lazy2

#endif
