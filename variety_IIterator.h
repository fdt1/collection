/*
 *  variety_IIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


namespace variety {
	
	template <typename PrimeTemplate, typename AssociateTemplate = PrimeTemplate>
	class IIterator : 
	public virtual IGeneric {
	public:
		typedef typename internal::IIterator<PrimeTemplate, AssociateTemplate>::InheritedType InheritedType;
	public:
		typedef typename GenericTraits<PrimeTemplate>::BaseType PrimeBaseType;
		typedef PrimeTemplate PrimeType;
		typedef typename GenericTraits<AssociateTemplate>::BaseType AssociateType;
		typedef internal::IIterator<PrimeTemplate, AssociateTemplate> InterfaceType;
		typedef IIterator<PrimeTemplate, AssociateTemplate> SelfType;
	public:
		// cast
		//template <typename OtherPrimeTemplate, typename OtherAssociateTemplate>
		//IList(const IList<OtherPrimeTemplate, OtherAssociateTemplate>& ilist) : IGeneric(NULL) { /* FIXME: cast */ }
		template <typename OtherPrimeTemplate, typename OtherAssociateTemplate>
		SelfType& operator= (const IIterator<OtherPrimeTemplate, OtherAssociateTemplate>& ilist) { /* FIXME: cast */ }
		// ref copy
		//IList(const SelfType& ilist) : IGeneric(ilist) {}
		SelfType& operator= (const SelfType& ilist) { IGeneric::set_implementation(ilist.get_implementation()); return *this; }
	protected:
		InterfaceType& get_implementation() { return dynamic_cast<InterfaceType&> (IGeneric::get_implementation()); }
		const InterfaceType& get_implementation() const { return dynamic_cast<const InterfaceType&> (IGeneric::get_implementation()); }
		IIterator(Implementation* implementation) : IGeneric(implementation) {}
	public:
		SelfType& operator++() { get_implementation().increment(); return *this; }
		SelfType operator++(int) { IteratorType it = * this; get_implementation().increment(); return it; }
		PrimeType operator*() { return get_implementation().get_prime(); }
		//SwapIterator swap() const { return internal::SwapIterator
	};
	
	
} // namespace variety