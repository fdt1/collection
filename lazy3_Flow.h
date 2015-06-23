/*
 *  lazy3_Flow.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_Modifier.h"
#include "lazy3_Accessor.h"
#include "lazy3_internal_FlowAbstractBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_FlowWithModifierOnFirst.h"
#include "lazy3_internal_FlowWithFilterOnFirst.h"
#include "lazy3_internal_FlowWithStaticCast.h"
#include "lazy3_internal_FlowElement.h"

namespace lazy3 {
	
		
	
	
	//--------------------------------------------------------------------------------
	//! @class Flow is a forward iterator.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename first_type = void, typename second_type = void, typename container_type = void>
	class Flow :
	public Modifier<container_type, Flow<first_type, second_type, container_type>, internal::IFlow<first_type, second_type, container_type>* >,
	protected virtual internal::FlowAbstractBridge<first_type, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef internal::FlowElement<first_type, second_type, container_type> FlowElement;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Flow() : InheritModifier(new FlowElement()) {}
		Flow(parameter_container_type container) : InheritModifier(new FlowElement(container)) {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		Flow(const Flow& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return FlowAbstractBridge::getFirst(); }
		//! @return the second_type value
		second_type second() { return FlowAbstractBridge::getSecond(); }
		//! @return the prime container
		const prime_container_type& container() const { return FlowAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return FlowAbstractBridge::setContent(container); }
		//! @return a new flow modified on the first value.
		//! @param modifier the modifier will change the first typed values of the flow.
		template<typename new_first_type>
		Flow<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::FlowWithModifierOnFirst<first_type, new_first_type, second_type, container_type> FlowWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new flow filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the flow.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Flow 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::FlowWithFilterOnFirst<first_type, filter_type, second_type, container_type> FlowWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
#if 1
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename second_type>
	class Flow<first_type, second_type, void> :
	public Modifier<void, Flow<first_type, second_type, void>, internal::IFlow<first_type, second_type, void>* >,
	protected virtual internal::FlowAbstractBridge<first_type, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
	public:
		Flow() {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_container_type>
		Flow(const Flow<first_type, second_type, any_container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return FlowAbstractBridge::getFirst(); }
		//! @return the second_type value
		second_type second() { return FlowAbstractBridge::getSecond(); }
		//! @return a new flow modified on the first value.
		//! @param modifier the modifier will change the first typed values of the flow.
		template<typename new_first_type>
		Flow<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::FlowWithModifierOnFirst<first_type, new_first_type, second_type, container_type> FlowWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new flow filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the flow.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Flow 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::FlowWithFilterOnFirst<first_type, filter_type, second_type, container_type> FlowWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type, typename container_type>
	class Flow<first_type, void, container_type> :
	public Modifier<container_type, Flow<first_type, void, container_type>, internal::IFlow<first_type, void, container_type>* >,
	protected virtual internal::FlowAbstractBridge<first_type, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef internal::FlowElement<first_type, second_type, container_type> FlowElement;
		typedef Modifier<container_type, Flow, IFlow* > InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Flow() : InheritModifier(new FlowElement()) {}
		Flow(parameter_container_type container) : InheritModifier(new FlowElement(container)) {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_second_type>
		Flow(const Flow<first_type, any_second_type, container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return FlowAbstractBridge::getFirst(); }
		//! @return the prime container
		const prime_container_type& container() const { return FlowAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return FlowAbstractBridge::setContent(container); }
		//! @return a new flow modified on the first value.
		template<typename new_first_type>
		Flow<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::FlowWithModifierOnFirst<first_type, new_first_type, second_type, container_type> FlowWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithModifierOnFirst(*this, abstract_modifier); 
		}
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type, typename container_type>
	class Flow<void, second_type, container_type> :
	public Modifier<container_type, Flow<void, second_type, container_type>, internal::IFlow<void, second_type, container_type>* >,
	protected virtual internal::FlowAbstractBridge<void, second_type, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void first_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef internal::FlowElement<first_type, second_type, container_type> FlowElement;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Flow() : InheritModifier(new FlowElement()) {}
		Flow(parameter_container_type container) : InheritModifier(new FlowElement(container)) {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_first_type>
		Flow(const Flow<any_first_type, second_type, container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the second_type value
		second_type second() { return FlowAbstractBridge::getSecond(); }
		//! @return the prime container
		const prime_container_type& container() const { return FlowAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return FlowAbstractBridge::setContent(container); }
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename first_type>
	class Flow<first_type, void, void> :
	public Modifier<void, Flow<first_type, void, void>, internal::IFlow<first_type, void, void>* >,
	protected virtual internal::FlowAbstractBridge<first_type, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
		typedef typename internal::Value<first_type>::parameter_type parameter_first_type;
	public:
		Flow() {}
		// FIXME: duplicate this constructor in all Flow without container ..
		//template<typename any_container_type>
		//Flow(const any_container_type& container) : InheritModifier(new internal::FlowElement<first_type, second_type, any_container_type, Flow<first_type, second_type, any_container_type> >(container)) {}
		
		//FIXME: shall we distribute	this constructor in all classes ?
		Flow(parameter_first_type container) : InheritModifier(new internal::FlowElement<first_type, second_type, first_type>(container)) {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_second_type, typename any_container_type>
		Flow(const Flow<first_type, any_second_type, any_container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the first_type value
		first_type first()  { return FlowAbstractBridge::getFirst(); }
		//! @return a new flow modified on the first value.
		//! @param modifier the modifier will change the first typed values of the flow.
		template<typename new_first_type>
		Flow<new_first_type, second_type, container_type> 
		modifyFirst(const Modifier<first_type, new_first_type>& modifier) const { 
			typedef typename internal::FlowWithModifierOnFirst<first_type, new_first_type, second_type, container_type> FlowWithModifierOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, new_first_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithModifierOnFirst(*this, abstract_modifier); 
		}
		//! @return a new flow filtered by the given predicate.
		//! @param modifier predicate to filter on the first typed values of the flow.
		//! the predicate can return any value that could statically converted into a boolean.
		template<typename filter_type>
		Flow 
		filterFirst(const Modifier<first_type, filter_type>& modifier) const { 
			typedef typename internal::FlowWithFilterOnFirst<first_type, filter_type, second_type, container_type> FlowWithFilterOnFirst;
			typedef typename internal::ModifierAbstractBridge<first_type, filter_type> ModifierAbstractBridge;
			const ModifierAbstractBridge& abstract_modifier = internal::GenericAbstractBridge::staticCast<const ModifierAbstractBridge&>(modifier);
			return new FlowWithFilterOnFirst(*this, abstract_modifier); 
		}
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename second_type>
	class Flow<void, second_type, void> :
	public Modifier<void, Flow<void, second_type, void>, internal::IFlow<void, second_type, void>* >,
	protected virtual internal::FlowAbstractBridge<void, second_type, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void first_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
	public:
		Flow() {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template<typename any_first_type, typename any_container_type>
		Flow(const Flow<any_first_type, second_type, any_container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the second_type value
		second_type second() { return FlowAbstractBridge::getSecond(); }
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <typename container_type>
	class Flow<void, void, container_type> :
	public Modifier<container_type, Flow<void, void, container_type>, internal::IFlow<void, void, container_type>* >,
	protected virtual internal::FlowAbstractBridge<void, void, container_type>
	{
		friend class internal::GenericAbstractBridge;
		typedef void second_type;
		typedef void first_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef internal::FlowElement<first_type, second_type, container_type> FlowElement;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
		typedef typename internal::Value<container_type>::prime_type prime_container_type;
		typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
	public:
		Flow() : InheritModifier(new FlowElement()) {}
		Flow(parameter_container_type container) : InheritModifier(new FlowElement(container)) {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type>
		Flow(const Flow<any_first_type, any_second_type, container_type>& flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow)
		: InheritModifier(new internal::FlowWithStaticCast<any_first_type, any_second_type, any_container_type, first_type, second_type, container_type>(internal::GenericAbstractBridge::staticCast<const internal::FlowAbstractBridge<any_first_type, any_second_type, any_container_type>&> (flow))) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() {  FlowAbstractBridge::flush(); }
		//! @return the prime container
		const prime_container_type& container() const { return FlowAbstractBridge::getConstContent(); }
		//! set the content.
		//! @param container the new content.
		//! @return the prime container
		const prime_container_type& container(const prime_container_type& container) { return FlowAbstractBridge::setContent(container); }
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
	
	//--------------------------------------------------------------------------------
	//! @class Flow specialization.
	//--------------------------------------------------------------------------------
	template <>
	class Flow<void, void, void> :
	public Modifier<void, Flow<void, void, void>, internal::IFlow<void, void, void>* >,
	protected virtual internal::FlowAbstractBridge<void, void, void>
	{
		friend class internal::GenericAbstractBridge;
		typedef void container_type;
		typedef void second_type;
		typedef void first_type;
		typedef internal::FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
		typedef internal::IFlow<first_type, second_type, container_type> IFlow;
		typedef Modifier<container_type, Flow, IFlow*> InheritModifier;
	public:
		Flow() {}
		Flow(const IFlow* flow) : InheritModifier(flow) {}
		template <typename any_first_type, typename any_second_type, typename any_container_type>
		Flow(const Flow<any_first_type, any_second_type, any_container_type>& flow) : InheritModifier(flow) {}
	public:
		//! remove the front element of the flow
		//! @return true if forward succeed
		bool forward() { return FlowAbstractBridge::forward(1); }
		//! make the flow empty
		//! @return the number of elements 
		//! that have been removed from the flow
		void flush() { FlowAbstractBridge::flush(); }
	protected:
		Flow(const Generic& generic) : InheritModifier(generic) {}
	};
#endif
	
	
} // namespace lazy2


