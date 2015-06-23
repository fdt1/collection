/*
 *  lazy2_internal_InheritCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 18/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"


namespace lazy2 {
	
	//================================================================
	class Generic;
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Collection; 
	
		
	namespace internal {
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
		class InheritCollection : 
		public Collection<ValueTemplate, AssociateTemplate, void, true>,
		public Collection<ValueTemplate, void, ContainerTemplate, false>
		{
			typedef Collection<ValueTemplate, AssociateTemplate, void, true> Collection;
		public:
			typedef void InheritContainerType;
		protected:
			InheritCollection(Implementation* implementation) : Collection(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Collection(bridge) {}
		};
		
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		class InheritCollection<ValueTemplate, AssociateTemplate, Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, true> : 
		public Collection<ValueTemplate, AssociateTemplate, typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true>,
		public Collection<ValueTemplate, void, Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, false>
		{
		public:
			typedef typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType InheritContainerType;
		private:
			typedef Collection<ValueTemplate, AssociateTemplate, typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true> Collection;
		protected:
			InheritCollection(Implementation* implementation) : Collection(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Collection(bridge) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		class InheritCollection<ValueTemplate, void, Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, true> : 
		public Collection<ValueTemplate, void, typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true>
		{
		public:
			typedef typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType InheritContainerType;
		private:
			typedef Collection<ValueTemplate, void, typename Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true> Collection;
		protected:
			InheritCollection(Implementation* implementation) : Collection(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Collection(bridge) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename ContainerTemplate>
		class InheritCollection<ValueTemplate, void, ContainerTemplate, true> : 
		public Collection<ValueTemplate, void, void, true>
		{
			typedef Collection<ValueTemplate, void, void, true> Collection;
		public:
			typedef void InheritContainerType;
		protected:
			InheritCollection(Implementation* implementation) : Collection(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Collection(bridge) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class InheritCollection<ValueTemplate, AssociateTemplate, void, true> : 
		public Collection<ValueTemplate, void, void, true>
		{
			typedef Collection<ValueTemplate, void, void, true> Collection;
		public:
			typedef void InheritContainerType;
		protected:
			InheritCollection(Implementation* implementation) : Collection(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Collection(bridge) {}
		};
		
		//================================================================
		template <typename ValueTemplate>
		class InheritCollection<ValueTemplate, void, void, true> : 
		public Generic,
		public internal::CollectionCallback<ValueTemplate>
		{
		public:
			typedef void InheritContainerType;
		protected:
			InheritCollection(Implementation* implementation) : Generic(implementation) {}
			InheritCollection(const internal::Bridge& bridge) : Generic(bridge) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate>
		class InheritCollection<ValueTemplate, AssociateTemplate, ContainerTemplate, false>
		{
		public:
			typedef void InheritContainerType;
		protected:
			InheritCollection(Implementation* implementation) {}
			InheritCollection(const internal::Bridge& bridge) {}
		};
		
	} // namespace internal
	
	
} // namespace lazy2

