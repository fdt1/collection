/*
 *  lazy_internal_IteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_IGeneric.h"
#include "lazy_internal_Bridge.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator :
		public virtual IGeneric
		{
		public:
			ValueTemplate getValue() const { return getValuePrimeType(); }
			AssociateTemplate getAssociate() const { return getAssociatePrimeType(); }
		public:
			virtual size_t incrementAt(size_t index) = 0;			
			virtual size_t countToEnd() const = 0;			
			virtual Bridge getImmediate() const = 0;
			virtual Bridge getEnd() const = 0;
			virtual ValueTemplate getValuePrimeType() const = 0;
			virtual AssociateTemplate getAssociatePrimeType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<const ValueTemplate&, AssociateTemplate> :
		public virtual IIterator<ValueTemplate, AssociateTemplate>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			const ValueTemplate& getValue() const { return getValueConstRefType(); }
		public:
			virtual const ValueTemplate& getValueConstRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<ValueTemplate&, AssociateTemplate> :
		public virtual IIterator<const ValueTemplate&, AssociateTemplate>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			ValueTemplate& getValue() const { return getValueRefType(); }
		public:
			virtual ValueTemplate& getValueRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<ValueTemplate, const AssociateTemplate&> :
		public virtual IIterator<ValueTemplate, AssociateTemplate>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			const AssociateTemplate& getAssociate() const { return getAssociateConstRefType(); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<const ValueTemplate&, const AssociateTemplate&> :
		public virtual IIterator<const ValueTemplate&, AssociateTemplate>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			const AssociateTemplate& getAssociate() const { return getAssociateConstRefType(); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<ValueTemplate&, const AssociateTemplate&> :
		public virtual IIterator<ValueTemplate&, AssociateTemplate>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			const AssociateTemplate& getAssociate() const { return getAssociateConstRefType(); }
		public:
			virtual const AssociateTemplate& getAssociateConstRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<ValueTemplate, AssociateTemplate&> :
		public virtual IIterator<ValueTemplate, const AssociateTemplate&>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			AssociateTemplate& getAssociate() const { return getAssociateRefType(); }
		public:
			virtual AssociateTemplate& getAssociateRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<const ValueTemplate&, AssociateTemplate&> :
		public virtual IIterator<const ValueTemplate&, const AssociateTemplate&>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			AssociateTemplate& getAssociate() const { return getAssociateRefType(); }
		public:
			virtual AssociateTemplate& getAssociateRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IIterator<ValueTemplate&, AssociateTemplate&> :
		public virtual IIterator<ValueTemplate&, const AssociateTemplate&>
		{
		public:
			static const IIterator& cast(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
			static IIterator& cast(IGeneric& generic) {
				return dynamic_cast<IIterator&> (generic);
			}
		public:
			AssociateTemplate& getAssociate() const { return getAssociateRefType(); }
		public:
			virtual AssociateTemplate& getAssociateRefType() const = 0;
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IIterator&> (generic);
			}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy