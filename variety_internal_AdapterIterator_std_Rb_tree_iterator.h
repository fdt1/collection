/*
 *  variety_internal_AdapterIterator_std_Rb_tree_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_AdapterIterator.h"
#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_BackwardIteratorInterface.h"
#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_GenericTraits.h"
#include "variety_internal_AdapterIteratorInterface.h"
#include <bits/stl_tree.h>


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename ContainerTemplate>
		class AdapterIterator<std::_Rb_tree_iterator<ValueTemplate>, ContainerTemplate > :
		public virtual AdapterIteratorInterface<std::_Rb_tree_iterator<ValueTemplate>, ContainerTemplate>,
		public virtual InputIteratorInterface<typename std::_Rb_tree_iterator<ValueTemplate>::reference>,
		public virtual BasicIteratorInterface,
		public virtual ForwardIteratorInterface,
		public virtual BackwardIteratorInterface
		{
		protected:
			typedef std::_Rb_tree_iterator<ValueTemplate> IteratorTemplate;
		public:
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ValueType ValueType;
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ReferenceType ReferenceType;
			typedef typename GenericTraits<typename IteratorTemplate::reference>::ConstRefType ConstRefType;
		protected:
			typedef AdapterIterator<IteratorTemplate, ContainerTemplate> SelfType;
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef typename GenericTraits<IteratorTemplate>::ValueType IteratorType;
		public:
			// AdapterIteratorInterface
			virtual ContainerType& get_container() = 0;
			virtual const ContainerType& get_container() const = 0;
			virtual IteratorType& get_iterator() = 0;
			virtual const IteratorType& get_iterator() const = 0;
		protected:
			void move(int offset) { 
				if (offset < 0) {
					for (int i = 0; i != offset; --i) --get_iterator(); 
				} else {
					for (int i = 0; i != offset; ++i) ++get_iterator(); 
				}
			}
			int move_if_possible(int offset) { 
				if (offset < 0) {
					for (; 0 != offset; ++offset) {
						if (--get_iterator() == get_container().begin())
							break;
					}
				} else {
					for (; 0 != offset; --offset) {
						if (++get_iterator() == get_container().begin())
							break;
					}
				}
				return offset;
			}
		public:	
			// BasicIteratorInterface
			virtual bool is_valid() const { return get_iterator() != get_container().end(); }
			virtual void restart() { get_iterator() = get_container().begin(); }
			virtual bool is_equal(const BasicIteratorInterface& other) const { return get_iterator() == (dynamic_cast<const SelfType&> (other)).get_iterator(); }
		public:
			// InputIteratorInterface
			virtual ValueType get_instance() const { return *get_iterator(); }
			virtual ReferenceType get_reference() const { return *get_iterator(); }
			virtual ConstRefType get_const_reference() const { return *get_iterator(); }
		public:
			// forward_interface
			virtual void increment() { ++get_iterator(); }
			virtual void increment(int offset) { move(offset); }
			virtual int increment_if_possible(int offset) { return move_if_possible(offset); }
		public:
			// BackwardInterface
			virtual void decrement() { --get_iterator(); }
			virtual void decrement(int offset) { move(-offset); }
			virtual int decrement_if_possible(int offset) { return move_if_possible(-offset); }
		};
		
	} // namespace internal
	
	
} // namespace variety