/*
 *  variety_Generic.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#if 0
#include "variety_internal_SharedImplementation.h"


namespace variety {
	
	class Generic :
	public virtual internal::SharedImplementation<internal::Implementation>
	{
	public:
		//Generic(const Generic& generic) : internal::SharedImplementation<internal::Implementation>(generic) {}
		//Generic() {}
	};

} // namespace variety

#elif 1
#include "variety_internal_SharedImplementation.h"


namespace variety {
	
	class Generic :
	protected virtual internal::Bridge
	{
	protected:
		internal::SharedImplementation<internal::Implementation> _shared_implementation;
	public:
		//Generic(const Generic& generic) : internal::SharedImplementation<internal::Implementation>(generic) {}
		//Generic() {}
	public:
		virtual const internal::Implementation* get_implementation() const { return _shared_implementation.get_implementation(); }
		virtual internal::Implementation* get_implementation() { return _shared_implementation.get_implementation(); }		
		virtual internal::Implementation* get_unique_implementation() { return _shared_implementation.get_unique_implementation(); }		
		bool is_shared_implementation() const { return _shared_implementation.is_shared_implementation(); }
		size_t count_implementation_use() const { return _shared_implementation.count_implementation_use(); }
		void set_implementation(internal::Implementation* implementation) { _shared_implementation.set_implementation(implementation); }
		void set_shared_implementation(const internal::SharedImplementation<internal::Implementation>& shared_implementation) { _shared_implementation = shared_implementation; }
		const internal::SharedImplementation<internal::Implementation>& get_shared_implementation() const { return _shared_implementation; }
	};
	
} // namespace variety



#else
#include "variety_internal_Implementation.h"
#include "variety_internal_Bridge.h"
// for shared_ptr
#include <tr1/memory> 


namespace variety {
	
	class Generic :
	public virtual internal::Bridge
	{
	public:
		// FIXME: mettre ici tous les types obligatoires de Iterator, etc...
	private:
		std::tr1::shared_ptr<internal::Implementation> _shared_implementation;
	protected:
		Generic(internal::Implementation* implementation) : _shared_implementation(implementation) {}
		Generic() {}
		virtual ~Generic() {}
	public: //FIXME : must be protected
		// Bridge
		virtual void set_implementation(internal::Implementation* implementation) { _shared_implementation = std::tr1::shared_ptr<internal::Implementation>(implementation); }
	public:
		// Bridge
		virtual internal::Implementation* get_implementation() { return _shared_implementation.get(); }
		virtual const internal::Implementation* get_implementation() const { return _shared_implementation.get(); }
	protected:
		internal::Implementation* get_unique_implementation() { if (is_shared_implementation()) { set_implementation(get_implementation()->duplicate()); } return get_implementation(); }
	public:
		bool is_shared_implementation() const { return count_use_implementation() > 1; }
		size_t count_use_implementation() const { return _shared_implementation.use_count(); }
		void set_shared_implementation(const internal::SharedImplementation<internal::Implementation>& shared_implementation) { _shared_implementation = shared_implementation; }
		const internal::SharedImplementation<internal::Implementation>& get_shared_implementation() const { return _shared_implementation; }
	};
	
} // namespace variety

#endif