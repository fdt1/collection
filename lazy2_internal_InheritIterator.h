/*
 *  lazyé_internal_InheritIterator.h
 *  Iterator
 *
 *  Created by Francois et Fabienne on 26/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"


namespace lazy2 {
	
	//================================================================
	class Generic;
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Iterator; 
	
	
	namespace internal {
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
		class InheritIterator : 
		public Iterator<ValueTemplate, AssociateTemplate, void, true>,
		public Iterator<ValueTemplate, void, ContainerTemplate, false>
		{
			typedef Iterator<ValueTemplate, AssociateTemplate, void, true> Iterator;
		public:
			typedef void InheritContainerType;
		protected:
			explicit InheritIterator(Implementation* implementation) : Iterator(implementation) {}
			explicit InheritIterator(const Generic& generic) : Iterator(generic) {}
		};
		
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		class InheritIterator<ValueTemplate, AssociateTemplate, Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, true> : 
		public Iterator<ValueTemplate, AssociateTemplate, typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true>,
		public Iterator<ValueTemplate, void, Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, false>
		{
		public:
			typedef typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType InheritContainerType;
		private:
			typedef Iterator<ValueTemplate, AssociateTemplate, typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true> Iterator;
		protected:
			explicit InheritIterator(Implementation* implementation) : Iterator(implementation) {}
			explicit InheritIterator(const Generic& generic) : Iterator(generic) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool AnyInheritanceTemplate>
		class InheritIterator<ValueTemplate, void, Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>, true> : 
		public Iterator<ValueTemplate, void, typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true>
		{
		public:
			typedef typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType InheritContainerType;
		private:
			typedef Iterator<ValueTemplate, void, typename Iterator<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, AnyInheritanceTemplate>::InheritContainerType, true> Iterator;
		protected:
			explicit InheritIterator(Implementation* implementation) : Iterator(implementation) {}
			explicit InheritIterator(const Generic& generic) : Iterator(generic) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename ContainerTemplate>
		class InheritIterator<ValueTemplate, void, ContainerTemplate, true> : 
		public Iterator<ValueTemplate, void, void, true>
		{
			typedef Iterator<ValueTemplate, void, void, true> Iterator;
		public:
			typedef void InheritContainerType;
		protected:
			explicit InheritIterator(Implementation* implementation) : Iterator(implementation) {}
			explicit InheritIterator(const Generic& generic) : Iterator(generic) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class InheritIterator<ValueTemplate, AssociateTemplate, void, true> : 
		public Iterator<ValueTemplate, void, void, true>
		{
			typedef Iterator<ValueTemplate, void, void, true> Iterator;
		public:
			typedef void InheritContainerType;
		protected:
			explicit InheritIterator(Implementation* implementation) : Iterator(implementation) {}
			explicit InheritIterator(const Generic& generic) : Iterator(generic) {}
		};
		
		//================================================================
		template <typename ValueTemplate>
		class InheritIterator<ValueTemplate, void, void, true> : 
		public Generic
		{
		public:
			typedef void InheritContainerType;
		protected:
			explicit InheritIterator(Implementation* implementation) : Generic(implementation) {}
			explicit InheritIterator(const Generic& generic) : Generic(generic) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate>
		class InheritIterator<ValueTemplate, AssociateTemplate, ContainerTemplate, false>
		{
		public:
			typedef void InheritContainerType;
		protected:
			explicit InheritIterator(Implementation* implementation) {}
			explicit InheritIterator(const Generic& generic) {}
		};
		
	} // namespace internal
	
	
} // namespace lazy2

