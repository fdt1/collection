/*
 *  lazy_internal_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_IIterator.h"
#include "lazy_internal_Generic.h"
#include "lazy_internal_Bridge.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator : 
		public virtual IIterator<ValueTemplate, AssociateTemplate>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate, AssociateTemplate> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			// --- interface of IIterator ---
			virtual size_t countToEnd() const { return getBridgeToIterator().countToEnd(); }			
			virtual size_t incrementAt(size_t index) { return getBridgeToIterator().incrementAt(index); }
			virtual Bridge getImmediate() const { return getBridgeToIterator().getImmediate(); }
			virtual Bridge getEnd() const { return getBridgeToIterator().getEnd(); }
			virtual ValueTemplate getValuePrimeType() const { return getBridgeToIterator().getValuePrimeType(); }
			virtual AssociateTemplate getAssociatePrimeType() const { return getBridgeToIterator().getAssociatePrimeType(); }
		};		
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<const ValueTemplate&, AssociateTemplate> : 
		public virtual Iterator<ValueTemplate, AssociateTemplate>,
		public virtual IIterator<const ValueTemplate&, AssociateTemplate>,
		public virtual Generic
		{
		protected:
			typedef IIterator<const ValueTemplate&, AssociateTemplate> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			// --- interface of IIterator ---
			virtual const ValueTemplate& getValueConstRefType() const { return getBridgeToIterator().getValueConstRefType(); }
		};		
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<ValueTemplate&, AssociateTemplate> : 
		public virtual Iterator<ValueTemplate, AssociateTemplate>,
		public virtual IIterator<ValueTemplate&, AssociateTemplate>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate&, AssociateTemplate> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			// --- interface of IIterator ---
			virtual ValueTemplate& getValueRefType() const { return getBridgeToIterator().getValueRefType(); }
		};		
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<ValueTemplate, const AssociateTemplate&> :
		public virtual Iterator<ValueTemplate, AssociateTemplate>,
		public virtual IIterator<ValueTemplate, const AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate, const AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<const ValueTemplate&, const AssociateTemplate&> :
		public virtual Iterator<const ValueTemplate&, AssociateTemplate>,
		public virtual IIterator<const ValueTemplate&, const AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<const ValueTemplate&, const AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<ValueTemplate&, const AssociateTemplate&> :
		public virtual Iterator<ValueTemplate&, AssociateTemplate>,
		public virtual IIterator<ValueTemplate&, const AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate&, const AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<ValueTemplate, AssociateTemplate&> :
		public virtual Iterator<ValueTemplate, const AssociateTemplate&>,
		public virtual IIterator<ValueTemplate, AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate, AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<const ValueTemplate&, AssociateTemplate&> :
		public virtual Iterator<const ValueTemplate&, const AssociateTemplate&>,
		public virtual IIterator<const ValueTemplate&, AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<const ValueTemplate&, AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class Iterator<ValueTemplate&, AssociateTemplate&> :
		public virtual Iterator<ValueTemplate&, const AssociateTemplate&>,
		public virtual IIterator<ValueTemplate&, AssociateTemplate&>,
		public virtual Generic
		{
		protected:
			typedef IIterator<ValueTemplate&, AssociateTemplate&> IIterator;
		public:
			const IIterator& getBridgeToIterator() const { return dynamic_cast<const IIterator&> (getBridgeToGeneric()); }
			IIterator& getBridgeToIterator() { return dynamic_cast<IIterator&> (getBridgeToGeneric()); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const { return getBridgeToIterator().getAssociateConstRefType(); }
		};
		
		
	} // namespace internal
	
	
	
} // namespace lazy