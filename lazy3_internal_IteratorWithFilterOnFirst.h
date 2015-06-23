/*
 *  lazy3_internal_IteratorWithFilterOnFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IteratorAbstractBridge.h"
#include "lazy3_internal_IteratorBridge.h"
#include "lazy3_internal_ModifierBridge.h"
#include "lazy3_internal_IIterator.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFilterOnFirst is an implementation of IIterator to filter 
		//! first typed values.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class IteratorWithFilterOnFirstOnBase : 
		public IteratorBridge<first_type, second_type, container_type>
		{
		public:
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef IteratorBridge<first_type, second_type, container_type> IteratorBridge;
			typedef IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
			typedef IIterator<first_type, second_type, container_type> IIterator;
		public:
			ModifierBridge _modifier;
			size_t _distance;
		public:
			IteratorWithFilterOnFirstOnBase(const IteratorAbstractBridge& Iterator, const ModifierAbstractBridge& modifier) 
			: IteratorBridge(Iterator), _modifier(modifier), _distance(Iterator.distance()) {}
		public:
			//! @href lazy3::internal::IIteratorOnBase::forward
			virtual size_t forward(size_t steps)  { 
				/* search the next element that match the predicate */
				IIterator* IteratorBase = this->getUniqueIIterator(); 
				size_t count = 0;
				while (steps != count && IteratorBase->isValid()) {
					if (_modifier.change(IteratorBase->getConstFirst())) ++count; 
					IteratorBase->forward(1);
				} 
				_distance += count;
				return count;
			}
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { 
				/* search the first element that match the predicate */
				IIterator* IteratorBase = const_cast<IteratorWithFilterOnFirstOnBase*> (this)->getUniqueIIterator(); 
				while (IteratorBase->isValid()) {
					if (const_cast<IteratorWithFilterOnFirstOnBase*> (this)->_modifier.change(IteratorBase->getConstFirst())) return true;
					IteratorBase->forward(1); 
				} 
				return false;
			}
			//! @href lazy3::internal::IPairOnFirst::getFirst
			virtual first_type getFirst() { 
				/* search the next element that match the predicate */
				IIterator* IteratorBase = this->getUniqueIIterator(); 
				while (IteratorBase->isValid()) {
					if (const_cast<IteratorWithFilterOnFirstOnBase*> (this)->_modifier.change(IteratorBase->getConstFirst())) break;
					IteratorBase->forward(1); 
				} 
				return IteratorBase->getFirst();
			}
			//! @href lazy3::internal::IPairOnFirst::getConstFirst
			virtual const_first_type getConstFirst() const { 
				/* search the next element that match the predicate */
				IIterator* IteratorBase = const_cast<IteratorWithFilterOnFirstOnBase*> (this)->getUniqueIIterator(); 
				while (IteratorBase->isValid()) {
					if (const_cast<IteratorWithFilterOnFirstOnBase*> (this)->_modifier.change(IteratorBase->getConstFirst())) break;
					IteratorBase->forward(1); 
				} 
				return IteratorBase->getConstFirst();
			}
			
			//! @href lazy3::internal::IIteratorOnBase::distance
			virtual size_t distance() const { return _distance; }
			//! @href lazy3::internal::IIteratorOnBase::backward
			virtual size_t backward(size_t steps)  { 
				/* search the next element that match the predicate */
				IIterator* iteratorBase = this->getUniqueIIterator(); 
				size_t count = 0;
				while (steps != count && iteratorBase->backward(1)) {
					if (_modifier.change(iteratorBase->getConstFirst())) ++count; 
				} 
				this->_distance -= count;
				return count;
			}
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { 
				/* search the next element that match the predicate */
				IIterator* iteratorBase = this->getIIterator(); 
				size_t count = 0;
				size_t steps = 0;
				while (iteratorBase->isValid()) {
					++steps;
					if (_modifier.change(iteratorBase->getConstFirst())) ++count; 
					iteratorBase->forward(1);
				} 
				// rewind to the previous point
				iteratorBase->backward(steps);
				return count;
			}
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFilterOnFirst is an implementation of IIterator to filter 
		//! first typed values.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class IteratorWithFilterOnFirst :
		public IteratorWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type>
		{
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef IteratorBridge<first_type, second_type, container_type> IteratorBridge;
			typedef IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
			typedef IteratorWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> IteratorWithFilterOnFirstOnBase;
			typedef IIterator<first_type, second_type, container_type> IIterator;
		public:
			IteratorWithFilterOnFirst(const IteratorAbstractBridge& Iterator, const ModifierAbstractBridge& modifier) 
			: IteratorWithFilterOnFirstOnBase(Iterator, modifier) {}
		public:
			//! @href lazy3::internal::IPairOnSecond::getSecond
			virtual second_type getSecond(size_t steps) { 
				/* search the next element that match the predicate */
				IIterator* IteratorBase = this->getUniqueIIterator(); 
				while (IteratorBase->isValid()) {
					if (const_cast<IteratorWithFilterOnFirstOnBase*> (this)->_modifier.change(IteratorBase->getConstFirst())) break;
					IteratorBase->forward(1); 
				} 
				return IteratorBase->getSecond();
			}
			//! @href lazy3::internal::IPairOnSecond::getConstSecond
			virtual const_second_type getConstSecond() const  { 
				/* search the next element that match the predicate */
				IIterator* IteratorBase = this->getUniqueIIterator(); 
				while (IteratorBase->isValid()) {
					if (const_cast<IteratorWithFilterOnFirstOnBase*> (this)->_modifier.change(IteratorBase->getConstFirst())) break;
					IteratorBase->forward(1); 
				} 
				return IteratorBase->getConstSecond();
			}
			
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFilterOnFirst<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename container_type>
		class IteratorWithFilterOnFirst<first_type, test_type, void, container_type> :
		public IteratorWithFilterOnFirstOnBase<first_type, test_type, void, container_type>
		{
			typedef void second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef IteratorBridge<first_type, second_type, container_type> IteratorBridge;
			typedef IteratorAbstractBridge<first_type, second_type, container_type> IteratorAbstractBridge;
			typedef IteratorWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> IteratorWithFilterOnFirstOnBase;
		public:
			IteratorWithFilterOnFirst(const IteratorAbstractBridge& Iterator, const ModifierAbstractBridge& modifier) 
			: IteratorWithFilterOnFirstOnBase(Iterator, modifier) {}
		};
		
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy3
