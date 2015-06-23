/*
 *  lazy2_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_Collection.h"
#include "lazy2_Accessor.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_Generic.h"
#include "lazy2_internal_InheritIterator.h"
#include "lazy2_internal_IteratorImplementation_std_pair.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorCallback.h"
#include "lazy2_internal_AssociateIteratorCallback.h"
#include "lazy2_internal_InstanceImplementation.h"
#include "lazy2_internal_FlattenIteratorImplementation.h"
#include "lazy2_internal_AccessorIteratorImplementation.h"
#include <utility>
#include <vector>



namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate>
	class Accessor; 
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate = void, typename ContainerTemplate = void, bool __ForInternalUseOnly_InheritanceTemplate__ = true>
	class Iterator : 
	public internal::InheritIterator<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__>
	{
		friend class Generic;
		typedef internal::IteratorCallback<ValueTemplate> IteratorCallback;
		typedef internal::AssociateIteratorCallback<AssociateTemplate> AssociateIteratorCallback;
		typedef internal::InheritIterator<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> InheritIterator;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef typename internal::ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		typedef Iterator<ValueTemplate, AssociateTemplate, ContainerTemplate, true> SelfType;
	protected:
		Iterator(internal::Implementation* implementation) : InheritIterator(implementation) {}
	public:
		Iterator() : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
		template <typename AnyContainerTemplate>
		Iterator(const AnyContainerTemplate& container) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, AnyContainerTemplate>(new internal::InstanceImplementation<AnyContainerTemplate>((AnyContainerTemplate&) container))) {}
		Iterator(const Iterator& iterator) : InheritIterator(iterator) {}
		Iterator(const ValueTemplate& value) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
	public:
		// redefine ForwardIteratorInterface
		Iterator& operator++() { IteratorCallback::increment(1); return *this; }
		Iterator operator++(int) { Iterator it = *this; IteratorCallback::increment(1); return it; }
		Iterator& operator+=(int offset) { IteratorCallback::increment(offset); return *this; }
		Iterator operator+(int offset) const { Iterator it = *this; it.IteratorCallback::increment(offset); return it; }
	public:
		template<typename AccessorValueTemplate>
		Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> associate(const Accessor<AccessorValueTemplate, ValueTemplate>& accessor) 
		{
			internal::Implementation* implementation = new typename internal::AccessorIteratorImplementation<AccessorValueTemplate, ValueTemplate, Iterator>(*this, accessor);
			return Generic::fabric<Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> >(implementation);
		}		
	};

	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Iterator<ValueTemplate, AssociateTemplate, void, __ForInternalUseOnly_InheritanceTemplate__> : 
	public internal::InheritIterator<ValueTemplate, AssociateTemplate, void, __ForInternalUseOnly_InheritanceTemplate__>,
	protected internal::AssociateIteratorCallback<AssociateTemplate>
	{
		friend class Generic;
		typedef std::vector<std::pair<ValueTemplate, AssociateTemplate> > ContainerTemplate;
		typedef internal::AssociateIteratorCallback<AssociateTemplate> AssociateIteratorCallback;
		typedef internal::InheritIterator<ValueTemplate, AssociateTemplate, void, __ForInternalUseOnly_InheritanceTemplate__> InheritIterator;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef typename internal::ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		typedef internal::IteratorCallback<ValueTemplate> IteratorCallback;
		typedef Iterator<ValueTemplate, AssociateTemplate, void, true> SelfType;
	protected:
		Iterator(internal::Implementation* implementation) : InheritIterator(implementation) {}
	public:
		Iterator() : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
		template <typename AnyContainerTemplate>
		Iterator(const AnyContainerTemplate& container) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, AnyContainerTemplate>(new internal::InstanceImplementation<AnyContainerTemplate>((AnyContainerTemplate&) container))) {}
		Iterator(const Iterator& iterator) : InheritIterator(iterator) {}
		Iterator(const ValueTemplate& value) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
	public:
		// redefine ForwardIteratorInterface
		Iterator& operator++() { IteratorCallback::increment(1); return *this; }
		Iterator operator++(int) { Iterator it = *this; IteratorCallback::increment(1); return it; }
		Iterator& operator+=(int offset) { IteratorCallback::increment(offset); return *this; }
		Iterator operator+(int offset) const { Iterator it = *this; it.IteratorCallback::increment(offset); return it; }
	public:
		template<typename AccessorValueTemplate>
		Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> associate(const Accessor<AccessorValueTemplate, ValueTemplate>& accessor) 
		{
			internal::Implementation* implementation = new typename internal::AccessorIteratorImplementation<AccessorValueTemplate, ValueTemplate, Iterator>(*this, accessor);
			return Generic::fabric<Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> >(implementation);
		}		
	};
	
	//================================================================
	template <typename ValueTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Iterator<ValueTemplate, void, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> : 
	public internal::InheritIterator<ValueTemplate, void, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__>,
	protected internal::InstanceCallback<ContainerTemplate>
	{
		friend class Generic;
		typedef void AssociateTemplate;
		typedef internal::InheritIterator<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> InheritIterator;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef internal::IteratorCallback<ValueTemplate> IteratorCallback;
		typedef internal::InstanceCallback<ContainerTemplate> InstanceCallback;
		typedef typename internal::ValueTraits<ContainerTemplate>::PrimeType ContainerPrimeType;
		typedef Iterator<ValueTemplate, AssociateTemplate, ContainerTemplate, true> SelfType;
	protected:
		Iterator(internal::Implementation* implementation) : InheritIterator(implementation) {}
	public:
		Iterator() : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
		template <typename AnyContainerTemplate>
		Iterator(const AnyContainerTemplate& container) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, AnyContainerTemplate>(new internal::InstanceImplementation<AnyContainerTemplate>((AnyContainerTemplate&) container))) {}
		Iterator(const Iterator& iterator) : InheritIterator(iterator) {}
		Iterator(const ValueTemplate& value) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
	public:
		// redefine ForwardIteratorInterface
		Iterator& operator++() { IteratorCallback::increment(1); return *this; }
		Iterator operator++(int) { Iterator it = *this; IteratorCallback::increment(1); return it; }
		Iterator& operator+=(int offset) { IteratorCallback::increment(offset); return *this; }
		Iterator operator+(int offset) const { Iterator it = *this; it.IteratorCallback::increment(offset); return it; }
	public:
		template<typename AccessorValueTemplate>
		Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> associate(const Accessor<AccessorValueTemplate, ValueTemplate>& accessor) 
		{
			internal::Implementation* implementation = new typename internal::AccessorIteratorImplementation<AccessorValueTemplate, ValueTemplate, Iterator>(*this, accessor);
			return Generic::fabric<Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> >(implementation);
		}		
	public:
		const ContainerPrimeType& inner() const { return InstanceCallback::getInstance(); }
		ContainerPrimeType inner() { return InstanceCallback::getInstance(); }
	};
	
	
	//================================================================
	template <typename ValueTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Iterator<ValueTemplate, void, void, __ForInternalUseOnly_InheritanceTemplate__> : 
	public internal::InheritIterator<ValueTemplate, void, void, __ForInternalUseOnly_InheritanceTemplate__>,
	protected internal::IteratorCallback<ValueTemplate>
	{
		friend class Generic;
		typedef void AssociateTemplate;
		typedef std::vector<ValueTemplate> ContainerTemplate;
		typedef internal::IteratorCallback<ValueTemplate> IteratorCallback;
		typedef internal::InheritIterator<ValueTemplate, void, void, __ForInternalUseOnly_InheritanceTemplate__> InheritIterator;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef Iterator<ValueTemplate, AssociateTemplate, void, true> SelfType;
	protected:
		Iterator(internal::Implementation* implementation) : InheritIterator(implementation) {}
	public:
		Iterator() : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
		template <typename AnyContainerTemplate>
		Iterator(const AnyContainerTemplate& container) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, AnyContainerTemplate>(new internal::InstanceImplementation<AnyContainerTemplate>((AnyContainerTemplate&) container))) {}
		template <typename AnyAssociateTemplate>
		Iterator(const Iterator<ValueTemplate, AnyAssociateTemplate>& iterator) : InheritIterator(iterator) {}
		Iterator(const Iterator& iterator) : InheritIterator(iterator) {}
		Iterator(const ValueTemplate& value) : InheritIterator(new typename internal::IteratorImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
	public:
		ValueTemplate operator*() const { return IteratorCallback::getPrimeValue(); }		
		Iterator& operator++() { IteratorCallback::increment(1); return *this; }
		Iterator operator++(int) { Iterator it = *this; IteratorCallback::increment(1); return it; }
		Iterator& operator+=(int offset) { IteratorCallback::increment(offset); return *this; }
		Iterator operator+(int offset) const { Iterator it = *this; it.IteratorCallback::increment(offset); return it; }
		// FIXME: to optimize IteratorCallback::getPosition() :
		// 1. rather use count_to_end position is dedicated to bidir iterator
		// 2. comparison of the container first? -> the flattenImplementation and the concatenationImpl 
		// (also the reduceImplementation, accessorImpl and filterImpl) !!!
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator==(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return IteratorCallback::getPosition() == it1.IteratorCallback::getPosition(); }
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator!=(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return !operator==(it1); }
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator<(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return IteratorCallback::getPosition() < it1.IteratorCallback::getPosition(); }
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator>(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return IteratorCallback::getPosition() > it1.IteratorCallback::getPosition(); }
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator<=(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return !operator>(it1); }
		template <typename ValueTemplate1, typename AssociateTemplate1>		
		bool operator>=(const Iterator<ValueTemplate1, AssociateTemplate1>& it1) const { return !operator<(it1); }
	public:
		template<typename AccessorValueTemplate>
		Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> associate(const Accessor<AccessorValueTemplate, ValueTemplate>& accessor) 
		{
			internal::Implementation* implementation = new typename internal::AccessorIteratorImplementation<AccessorValueTemplate, ValueTemplate, Iterator>(*this, accessor);
			return Generic::fabric<Iterator<AccessorValueTemplate, ValueTemplate, SelfType, true> >(implementation);
		}		
	};
	
	
} // namespace lazy2


template <typename ValueTemplate, typename AssociateTemplate>
inline lazy2::Iterator<ValueTemplate, AssociateTemplate> operator+(int offset, const lazy2::Iterator<ValueTemplate, AssociateTemplate>& it) { return it + offset; }

