/*
 *  lazy2_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_Generic.h"
#include "lazy2_Iterator.h"
#include "lazy2_Accessor.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionImplementation.h"
#include "lazy2_internal_CollectionImplementation_std_pair.h"
#include "lazy2_internal_CollectionImplementation_std_vector.h"
#include "lazy2_internal_CollectionImplementation_std_vector_std_pair.h"
#include "lazy2_internal_InstanceCallback.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_AssociateCollectionCallback.h"
#include "lazy2_internal_InstanceImplementation.h"
#include "lazy2_internal_FlattenCollectionImplementation.h"
#include "lazy2_internal_FlattenCollection.h"
#include "lazy2_internal_AssociateCollection.h"
#include "lazy2_internal_AccessorCollectionImplementation.h"
//FIXME: to include...
//#include "lazy2_internal_ConcatenateCollectionImplementation.h"
#include "lazy2_internal_InheritCollection.h"
#include "lazy2_internal_ConstructorCollection.h"
#include "lazy2_internal_ContainerCollection.h"
#include "lazy2_internal_ValueTraits.h"



namespace lazy2 {

	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Iterator; 
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate>
	class Accessor; 
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate = void, typename ContainerTemplate = void, bool __ForInternalUseOnly_InheritanceTemplate__ = true>
	class Collection : 
	public internal::InheritCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__>,
	public internal::FlattenCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__>,
	public internal::ContainerCollection<ValueTemplate, AssociateTemplate, ContainerTemplate>,
	public internal::AssociateCollection<ValueTemplate, AssociateTemplate, ContainerTemplate>
	{
		template <typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate>
		friend class internal::FlattenCollection;
		template <typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		friend class Collection;
		template <typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		friend class internal::InheritCollection;
		typedef internal::CollectionCallback<ValueTemplate> CollectionCallback;
		typedef internal::AssociateCollectionCallback<AssociateTemplate> AssociateCollectionCallback;
		typedef internal::InheritCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> InheritCollection;
		typedef typename internal::ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		typedef typename internal::ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		typedef Collection<ValueTemplate, AssociateTemplate, ContainerTemplate, true> SelfType;
	public:
		typedef ValueTemplate ValueType;
		typedef AssociateTemplate AssociateType;
		typedef ContainerTemplate ContainerType;
		typedef Iterator<ValueTemplate, AssociateTemplate, ContainerTemplate, true> Iterator;
	protected:
		explicit Collection(internal::Implementation* implementation) : InheritCollection(implementation) {}
		explicit Collection(const internal::Bridge& bridge) : InheritCollection(bridge) {}
		explicit Collection(const Generic& generic) : InheritCollection(generic) {}
	public:
		Collection() : InheritCollection(internal::ConstructorCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, ContainerTemplate>()) {}
		template <typename AnyContainerTemplate>
		explicit Collection(const AnyContainerTemplate& container) : InheritCollection(internal::ConstructorCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, AnyContainerTemplate>(container)) {}
		// FIXME: add cast operator
	public:
		// FIXME: plutôt que size return object cardinality
		size_t size() const { return CollectionCallback::count(-1); }
		
		ValueTemplate operator[](int index) const { size_t count; return CollectionCallback::getPrimeValue(index, count); }
		Iterator begin() const { return Generic::fabric<Iterator>(CollectionCallback::createBeginIterator()); }
		Iterator end() const { return Generic::fabric<Iterator>(CollectionCallback::createEndIterator()); }
	public:
		template<typename AccessorValueTemplate>
		Collection<AccessorValueTemplate, ValueTemplate, SelfType, true> associate(const Accessor<AccessorValueTemplate, ValueTemplate>& accessor) 
		{
			internal::Implementation* implementation = new typename internal::AccessorCollectionImplementation<AccessorValueTemplate, ValueTemplate, Collection>(*this, accessor);
			return Collection<AccessorValueTemplate, ValueTemplate, SelfType, true>(implementation);
		}
	public:
		// concatenate
		template <typename AnyAssociateTemplate, typename AnyContainerTemplate, bool __AnyInheritanceTemplate__>
		Collection<ValueTemplate, 
		void, 
		std::pair<Collection,
		Collection<ValueTemplate, void, AnyContainerTemplate, __AnyInheritanceTemplate__> >,
		true>		
		operator+ (const Collection<ValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, __AnyInheritanceTemplate__>& collection) const
		{
			typedef Collection<ValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, __AnyInheritanceTemplate__> CollectionType;
			// FIXME: to use ...
			//internal::Implementation* implementation = new internal::ConcatenateCollectionImplementation<ValueTemplate, void, Collection, CollectionType>(*this, collection);
			internal::Implementation* implementation = NULL;
			return Collection<ValueTemplate, void, std::pair<Collection, CollectionType>, true>(implementation);
		}
		// concatenate
		template <typename AnyContainerTemplate, bool __AnyInheritanceTemplate__>
		Collection<ValueTemplate, 
		AssociateTemplate, 
		std::pair<Collection,
		Collection<ValueTemplate, AssociateTemplate, AnyContainerTemplate, __AnyInheritanceTemplate__> >,
		true>		
		operator+ (const Collection<ValueTemplate, AssociateTemplate, AnyContainerTemplate, __AnyInheritanceTemplate__>& collection) const
		{
			typedef Collection<ValueTemplate, AssociateTemplate, AnyContainerTemplate, __AnyInheritanceTemplate__> CollectionType;
			// FIXME: to use ...
			//internal::Implementation* implementation = new internal::ConcatenateCollectionImplementation<ValueTemplate, AssociateTemplate, Collection, CollectionType>(*this, collection);
			internal::Implementation* implementation = NULL;
			return Collection<ValueTemplate, AssociateTemplate, std::pair<Collection, CollectionType>, true>(implementation);
		}
	};
	
} // namespace lazy2




