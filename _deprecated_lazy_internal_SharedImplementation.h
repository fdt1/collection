/*
 *  lazy_internal_SharedImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Implementation.h"
//#include "lazy_internal_Bridge.h"
// for shared_ptr
#include <tr1/memory> 
#include <iostream> 

#ifdef SHARED_DEBUG

extern std::set<variety::internal::Implementation*> _ff;
extern std::set<variety::internal::Implementation*> _gg;
#endif

namespace lazy {
	
	namespace internal {
		
		
		//! alRefCounter allocates once 'E' without duplication even if the alRefCounter is duplicated
		//! and unallocates when it isn't used anymore
		template<typename E>
		class alRefCounter {
			
		private:
			mutable std::pair<E, int>* _elements;
			
		public:
			alRefCounter();
			alRefCounter(const alRefCounter<E>& refcounter);
			alRefCounter(const E& elements);
			~alRefCounter();
			alRefCounter<E>& operator=(const alRefCounter<E>& refcounter);
			
		public:
			const E& get() const;
			E& get();
			size_t use_count() const {return _elements->second;}
		};
		
		
		//                                                                                                //
		//  Reference counter  implementation                                                             //
		//                                                                                                //
		
		template<typename E>
		alRefCounter<E>::alRefCounter()
		: _elements(new std::pair<E, int>(E(), 0))
		{
		}
		
		template<typename E>
		alRefCounter<E>::alRefCounter(const alRefCounter<E>& refcounter)
		: _elements(refcounter._elements)
		{
			++_elements->second;
			std::cout <<"          ++" << _elements->first <<" ("<<_elements->second<<")   " <<__LINE__<<std::endl;
		}
		
		template<typename E>
		alRefCounter<E>::alRefCounter(const E& elements)
		: _elements(new std::pair<E, int>(elements, 0))
		{
		}
		
		template<typename E>
		alRefCounter<E>::~alRefCounter()
		{
			if (_elements->second == 0)
				delete _elements;
			else
				--_elements->second;
		}
		
		template<typename E>
		alRefCounter<E>& 
		alRefCounter<E>::operator=(const alRefCounter<E>& refcounter)
		{
			if (_elements->second == 0)
				delete _elements;
			else
				--_elements->second;
			
			_elements = refcounter._elements;
			
			++_elements->second;
			
			std::cout <<"          ++" << _elements->first <<" ("<<_elements->second<<")   " <<__LINE__<<std::endl;
			
			return *this;
		}
		
		template<typename E>
		const E& 
		alRefCounter<E>::get() const
		{
			return _elements->first;    
		}
		
		template<typename E>
		E& 
		alRefCounter<E>::get()
		{
			return _elements->first;    
		}
		
		
		template<typename E>
		inline std::ostream& operator<<(std::ostream& os, const alRefCounter<E>& refcounter) {
			os<<refcounter.get();
			return os;
		}
		
		template <typename ImplementationTemplate>
		struct toto {
		private:
			std::tr1::shared_ptr<ImplementationTemplate> _implementation;
			//alRefCounter<ImplementationTemplate*> _implementation;
		public:
			// implementation should have be done with a new, don't bother about destroy. 
			// The destruction of the current object will destroy the implementation.
			
			toto(ImplementationTemplate* implementation) { 
				if (implementation) {
#ifdef SHARED_DEBUG
					std::cout <<"   +++  "<<implementation<< " ..."<<std::endl;
#endif
					_implementation = std::tr1::shared_ptr<ImplementationTemplate>(implementation); 		
					//_implementation = alRefCounter<ImplementationTemplate*>(implementation); 
#ifdef SHARED_DEBUG
					
					std::cout <<"       ... " << "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
					if (_gg.find(_implementation.get()) != _gg.end() && _implementation.get()) {
						std::cout <<"   ????????????  "<< " "<<__LINE__<<" "<<_implementation.get()<<std::endl;
					}
					
					_gg.insert(_implementation.get());
#endif
				}
				
			}
			
#ifdef SHARED_DEBUG
			
			toto(const toto& shared_implementation)   {
				
				std::cout <<"   *++  "<<shared_implementation._implementation << "  ..."<<std::endl;
				_implementation=shared_implementation._implementation;
				
				std::cout <<"       ... " << "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
				
			}
			
			toto& operator=(const toto& shared_implementation)   {
				std::cout <<"   *++  "<<shared_implementation._implementation << "  ..."<<std::endl;
				_implementation=shared_implementation._implementation;
				std::cout <<"       ... " << "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
				return *this;
				
			}
			template <typename OtherImplementationTemplate>
			toto(const toto<OtherImplementationTemplate>& shared_implementation) {
				std::cout <<"   *++  "<<shared_implementation._implementation << "  ..."<<std::endl;
				_implementation=shared_implementation._implementation;
				std::cout <<"       ... "<< "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
				
			}
#endif
			toto()  {
				//_implementation = std::tr1::shared_ptr<ImplementationTemplate>(); 
			}
#ifdef SHARED_DEBUG
			
			// destroy implementation
			virtual ~toto() { 
				
				std::cout <<"   *--  "<<_implementation.get()<< "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
				if (_implementation.use_count() <=1 && _implementation.get()) {
					std::cout <<"   ---  "<<_implementation.get()<< " "<<__LINE__<<std::endl;
					if (_ff.find(_implementation.get()) != _ff.end()) {
						std::cout <<"   !!!!!!!!!!!!!! "<< " "<<__LINE__<<" "<<_implementation.get()<<std::endl;
						
					}
					if (_gg.find(_implementation.get()) == _gg.end()) {
						std::cout <<"   ????????????  "<< " "<<__LINE__<<" "<<_implementation.get()<<std::endl;
					}
					_gg.erase(_implementation.get());
					
					_ff.insert(_implementation.get());
					
				}
			}
#endif
		public:
			// Bridge
			// implementation should have be done with a new, don't bother about destroy. It destroyes previous implementation
			virtual ImplementationTemplate* get_implementation() { return _implementation.get(); }
			virtual const ImplementationTemplate* get_implementation() const { return _implementation.get(); }
		public:
			void set_implementation(ImplementationTemplate* implementation) {
#ifdef SHARED_DEBUG
				
				//alRefCounter<ImplementationTemplate*> tmp =_implementation;
				std::cout <<"        ********** "<<implementation<<"    "<<__LINE__<<std::endl;
				
				std::cout <<"   *--  "<<_implementation.get()<< "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
				if (_implementation.use_count() <=1 && _implementation.get()) {
					std::cout<<"  ---  "<<_implementation.get()<< " "<<__LINE__<<std::endl;
					if (_ff.find(_implementation.get()) != _ff.end()) {
						std::cout <<"   !!!!!!!!!!!!!! "<< " "<<__LINE__<<std::endl;
						
					}
					if (_gg.find(_implementation.get()) == _gg.end()) {
						std::cout <<"   ????????????  "<< " "<<__LINE__<<std::endl;
					}
					_gg.erase(_implementation.get());
					_ff.insert(_implementation.get());
				}
				if (implementation) {
					std::cout <<"   +++  "<<implementation<< " ... " <<std::endl;
#endif
					_implementation = std::tr1::shared_ptr<ImplementationTemplate>(implementation); 
#ifdef SHARED_DEBUG
					
					//_implementation = alRefCounter<ImplementationTemplate*>(implementation); 
					std::cout <<"       ... " << "  ("<<_implementation.use_count()<< ") "<<__LINE__<<std::endl;
					if (_gg.find(_implementation.get()) != _gg.end() && _implementation.get()) {
						std::cout <<"   ????????????  "<< " "<<__LINE__<<std::endl;
					}
					_gg.insert(_implementation.get());
				} else {
					_implementation = std::tr1::shared_ptr<ImplementationTemplate>(); 
					//_implementation = alRefCounter<ImplementationTemplate*>(); 
				}
#endif
			}
			ImplementationTemplate* get_unique_implementation() { if (is_shared_implementation()&&_implementation.get()) { set_implementation(_implementation.get()->duplicate()); } return _implementation.get(); } 
			bool is_shared_implementation() const { return count_implementation_use() > 1; }
			size_t count_implementation_use() const { return _implementation.use_count(); }
			//template <typename OtherImplementationTemplate>			
			//void set_implementation(const SharedImplementation<OtherImplementationTemplate>& shared_implementation) { _implementation = shared_implementation._implementation; }
		};
		
		// bridge between an implementation and an interface
		template <typename ImplementationTemplate>
		class SharedImplementation :
		public virtual Bridge
		{
		public:
			toto<ImplementationTemplate> _implementation;
		public:
			// implementation should have be done with a new, don't bother about destroy. 
			// The destruction of the current object will destroy the implementation.
			
			SharedImplementation(ImplementationTemplate* implementation) : _implementation(implementation) {} 
			
			
			SharedImplementation(const SharedImplementation& shared_implementation) : _implementation(shared_implementation._implementation)  {}
			//SharedImplementation& operator=(const SharedImplementation& shared_implementation)  {  _implementation = shared_implementation._implementation;}
			//template <typename OtherImplementationTemplate>
			//SharedImplementation(const SharedImplementation<OtherImplementationTemplate>& shared_implementation) : _implementation(shared_implementation._implementation) {}
			SharedImplementation() : _implementation() {}
			// destroy implementation
			virtual ~SharedImplementation() { }
		public:
			// Bridge
			// implementation should have be done with a new, don't bother about destroy. It destroyes previous implementation
			virtual ImplementationTemplate* get_implementation() { return _implementation.get_implementation(); }
			virtual const ImplementationTemplate* get_implementation() const { return _implementation.get_implementation(); }
		public:
			void set_implementation(ImplementationTemplate* implementation) {_implementation.set_implementation(implementation); }
			ImplementationTemplate* get_unique_implementation() { return _implementation.get_unique_implementation(); }
			bool is_shared_implementation() const { return count_implementation_use() > 1; }
			size_t count_implementation_use() const { return _implementation.count_implementation_use(); }
			//template <typename OtherImplementationTemplate>			
			//void set_implementation(const SharedImplementation<OtherImplementationTemplate>& shared_implementation) { _implementation = shared_implementation._implementation; }
		};
		
	} // namespace internal
	
	
} // namespace lazy