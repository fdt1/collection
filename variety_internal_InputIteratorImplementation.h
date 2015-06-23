/*
 *  variety_internal_InputIteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_SharedImplementation.h"
// for std::pair
#include <list>
// for shared_ptr
#include <tr1/memory> 

namespace variety {
	
	
	namespace internal {
		
#if 0	
		template <typename BridgeTemplate>
		class TransformIteratorImplementation : 
		public virtual BridgeTemplate,
		public virtual SharedImplementation<Implementation>,
		public virtual Implementation
		{
		public:
		public:
			TransformIteratorImplementation(const SharedImplementation<Implementation>& shared_implementation) : SharedImplementation<Implementation>(shared_implementation) {}
			//TransformIteratorImplementation(const SharedImplementation<Implementation>& shared_implementation, const BridgeTemplate& bridge) : BridgeTemplate(bridge), SharedImplementation<Implementation>(shared_implementation) {}
			virtual ~TransformIteratorImplementation() {}
			virtual TransformIteratorImplementation* duplicate() const { return new TransformIteratorImplementation(*this); }
			virtual std::string get_name() const { return typeid(TransformIteratorImplementation).name(); }
		};		
		
#else
		template <typename BridgeTemplate>
		class TransformIteratorImplementation : 
		public virtual BridgeTemplate,
		public virtual Bridge,
		public virtual Implementation
		{
		public:
			typedef SharedImplementation<Implementation> SharedImplementation;
		protected:
			SharedImplementation _shared_implementation;
		public:
		public:
			TransformIteratorImplementation(const SharedImplementation& shared_implementation) : _shared_implementation(shared_implementation) {}
			//TransformIteratorImplementation(const SharedImplementation<Implementation>& shared_implementation, const BridgeTemplate& bridge) : BridgeTemplate(bridge), SharedImplementation<Implementation>(shared_implementation) {}
			virtual ~TransformIteratorImplementation() {}
			// Implementation
			virtual TransformIteratorImplementation* duplicate() const { return new TransformIteratorImplementation(_shared_implementation); }
			virtual std::string get_name() const { return typeid(TransformIteratorImplementation).name(); }
			// Bridge
			//virtual void set_implementation(internal::Implementation* implementation) = 0;
		public:
			virtual const internal::Implementation* get_implementation() const { return _shared_implementation.get_implementation(); }
			virtual internal::Implementation* get_implementation() { return _shared_implementation.get_implementation(); }
			
		};		
#endif
	} // namespace internal

	
	template <typename PairTemplate, typename BridgeType>
	class FirstPair : 
	public virtual BridgeType
	{
	public:
		typedef internal::InputIteratorInterface<PairTemplate> InputIteratorInterface;
		typedef typename internal::InputIteratorInterface<typename PairTemplate::first_type>::ValueType ValueType;
		
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_instance() const { return get_input_iterator_interface().get_instance().first; }
		virtual ~FirstPair() {}
	};

	template <typename PairTemplate, typename BridgeType>
	class FirstPair<const PairTemplate&, BridgeType> : 
	public virtual FirstPair<PairTemplate,BridgeType>
	{
	public:
		typedef internal::InputIteratorInterface<const PairTemplate &> InputIteratorInterface;
		typedef typename internal::InputIteratorInterface<const typename PairTemplate::first_type &>::ValueType ValueType;
		
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_const_reference() const { return get_input_iterator_interface().get_const_reference().first; }
		virtual ~FirstPair() {}
	};
	
	template <typename PairTemplate, typename BridgeType>
	class FirstPair< PairTemplate&, BridgeType> : 
	public virtual FirstPair<const PairTemplate&,BridgeType>
	{
	public:
		typedef internal::InputIteratorInterface< PairTemplate &> InputIteratorInterface;
		typedef typename internal::InputIteratorInterface<typename  PairTemplate::first_type &>::ValueType ValueType;
		
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_reference() const { return get_input_iterator_interface().get_reference().first; }
		virtual ~FirstPair() {}
	};

	class FirstPairFabric 
	
	{
		template <typename PairTemplate>
		struct PairTraits {
			typedef typename PairTemplate::first_type ValueType;
		};
		template <typename PairTemplate>
		struct PairTraits<const PairTemplate &> {
			typedef  const typename PairTemplate::first_type& ValueType;
		};
		template <typename PairTemplate>
		struct PairTraits<PairTemplate&> {
			typedef typename PairTemplate::first_type& ValueType;
		};
		
	public:
		template <typename StdPairIteratorTemplate>
		
		typename StdPairIteratorTemplate::template ChangeValue<typename PairTraits<typename StdPairIteratorTemplate::ValueType>::ValueType>::Type apply(const StdPairIteratorTemplate& iter) const { 
			typedef typename StdPairIteratorTemplate::template ChangeValue<typename PairTraits<typename StdPairIteratorTemplate::ValueType>::ValueType>::Type NewIteratorType;
			typedef FirstPair<typename StdPairIteratorTemplate::ValueType, typename NewIteratorType::BridgeType> MyBridgeType;
			typedef internal::TransformIteratorImplementation<MyBridgeType> MyImplementation;
			
			NewIteratorType x;
			//NewIteratorType y;
			// FIXME: pourquoi cela ne marche pas?
			//x.set_implementation(new Implementation(iter.get_implementation()->duplicate()));
			internal::Implementation* x_impl=iter.get_implementation()->duplicate();
			//internal::Implementation* y_impl=iter.get_implementation()->duplicate();
			//std::cout<<"x_impl="<<x_impl<<std::endl;
			MyImplementation* x_impl2=new MyImplementation(x_impl);
			//std::cout<<"y_impl="<<y_impl<<std::endl;
			//MyImplementation* y_impl2=new MyImplementation(y_impl);
			//std::cout<<"x_impl2="<<x_impl2<<std::endl;
			x.set_implementation(x_impl2); 
			//std::cout<<"y_impl2="<<y_impl2<<std::endl;
			//y.set_implementation(y_impl2); 
			//std::cout<<typeid(x.get_implementation()).name()<<std::endl;
			//std::cout<<typeid(iter.get_implementation()).name()<<std::endl;
			//std::cout<<(x.get_implementation())->get_name()<<std::endl;
			//std::cout<<y.get_implementation()->get_name()<<std::endl;
			//std::cout<<iter.get_implementation()->get_name()<<std::endl;
			//x.set_implementation(MyImplementation(NULL)); 
			//x.set_implementation(NULL); 
			return x;
		}
#if 0 //disabled for debug
		template <typename StdPairIteratorTemplate>
		void apply(const StdPairIteratorTemplate& iter, typename StdPairIteratorTemplate::template ChangeValue<typename PairTraits<typename StdPairIteratorTemplate::ValueType>::ValueType>::Type& x) const { 
			typedef typename StdPairIteratorTemplate::template ChangeValue<typename PairTraits<typename StdPairIteratorTemplate::ValueType>::ValueType>::Type NewIteratorType;
			typedef FirstPair<typename StdPairIteratorTemplate::ValueType, typename NewIteratorType::BridgeType> MyBridgeType;
			typedef internal::TransformIteratorImplementation<MyBridgeType> MyImplementation;
			
			//NewIteratorType x;
			x.set_implementation(new MyImplementation(iter.get_implementation()->duplicate())); 
			//return x;
		}
#endif
	};
	
//=============================================	
	
	template <typename ValueTemplate, typename BridgeType>
	class Reverse : 
	public virtual BridgeType
	{
	public:
		typedef ValueTemplate ValueType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		typedef internal::PtrDiffIteratorInterface PtrDiffIteratorInterface;
				
		template <typename InterfaceTemplate>
		struct CompatibilityCheck {
			static InputIteratorInterface* get_input_iterator_interface(InterfaceTemplate* interface) { return interface; }
		};
		
		const BasicIteratorInterface& get_basic_iterator_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*this->get_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*this->get_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*this->get_implementation()); }
		const PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() const { return dynamic_cast<const PtrDiffIteratorInterface&> (*this->get_implementation()); }
		BasicIteratorInterface& get_basic_iterator_interface()  { return dynamic_cast< BasicIteratorInterface&> (*this->get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface()  { return dynamic_cast< InputIteratorInterface&> (*this->get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface()  { return dynamic_cast< ForwardIteratorInterface&> (*this->get_implementation()); }
		BackwardIteratorInterface& get_backward_iterator_interface()  { return dynamic_cast< BackwardIteratorInterface&> (*this->get_implementation()); }
		PtrDiffIteratorInterface& get_ptr_diff_iterator_interface()  { return dynamic_cast< PtrDiffIteratorInterface&> (*this->get_implementation()); }
		
		// InputIteratorInterface
		virtual ValueType get_instance() const { ((BackwardIteratorInterface&) get_backward_iterator_interface()).decrement(); ValueType v = get_input_iterator_interface().get_instance(); ((ForwardIteratorInterface&) get_forward_iterator_interface()).increment(); return v; }
		
		// ForwardIteratorInterface
		virtual void increment() {  get_backward_iterator_interface().decrement(); }
		virtual void increment(int offset) {  get_backward_iterator_interface().decrement(offset); }
		
		// BackwardIteratorInterface
		virtual void decrement() {  get_forward_iterator_interface().increment(); }
		virtual void decrement(int offset) {  get_forward_iterator_interface().increment(offset); }
		
		//FIXME : is_equal et diff non - implémenté
		
		//FIXME: restart et is_valid aussi !!!
		
		
	};

	template <typename ValueTemplate, typename BridgeType>
	class Reverse<const ValueTemplate&, BridgeType> : 
	public virtual Reverse<ValueTemplate, BridgeType>
	{
	public:
		typedef const ValueTemplate& ValueType;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*this->get_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*this->get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface()  { return dynamic_cast< InputIteratorInterface&> (*this->get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface()  { return dynamic_cast< ForwardIteratorInterface&> (*this->get_implementation()); }
		BackwardIteratorInterface& get_backward_iterator_interface()  { return dynamic_cast< BackwardIteratorInterface&> (*this->get_implementation()); }
		
		// InputIteratorInterface
		virtual ValueType get_const_reference() const { ((BackwardIteratorInterface&) get_backward_iterator_interface()).decrement(); ValueType v = get_input_iterator_interface().get_const_reference(); ((ForwardIteratorInterface&) get_forward_iterator_interface()).increment(); return v; }
		
		
	};
	
	template <typename ValueTemplate, typename BridgeType>
	class Reverse< ValueTemplate&, BridgeType> : 
	public virtual Reverse<const ValueTemplate, BridgeType>
	{
	public:
		typedef  ValueTemplate& ValueType;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*this->get_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*this->get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface()  { return dynamic_cast< InputIteratorInterface&> (*this->get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface()  { return dynamic_cast< ForwardIteratorInterface&> (*this->get_implementation()); }
		BackwardIteratorInterface& get_backward_iterator_interface()  { return dynamic_cast< BackwardIteratorInterface&> (*this->get_implementation()); }
		
		// InputIteratorInterface
		virtual ValueType get_reference() const { ((BackwardIteratorInterface&) get_backward_iterator_interface()).decrement(); ValueType v = get_input_iterator_interface().get_reference(); ((ForwardIteratorInterface&) get_forward_iterator_interface()).increment(); return v; }
		
		
	};

	class ReverseFabric 
	
	{
		
	public:
		template <typename IteratorTemplate>		
		IteratorTemplate apply(const IteratorTemplate& iter) const { 
			typedef Reverse<typename IteratorTemplate::ValueType, typename IteratorTemplate::BridgeType> BridgeType;
			typedef internal::TransformIteratorImplementation<BridgeType> Implementation;

			
			//typename IteratorTemplate::BridgeType* z;
			//internal::BackwardIteratorInterface* y = z;
			
			IteratorTemplate x;
			x.set_implementation(new Implementation(iter.get_implementation()->duplicate())); 
			return x;
		}
	};
	
//==================
	
	template <typename ValueTemplate, typename BridgeType>
	class Unique : 
	public virtual BridgeType
	{
	public:
		typedef typename internal::GenericTraits<ValueTemplate>::ValueType ValueType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueTemplate> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
	private:
		// FIXME : rb_tree pour éviter de dupliquer la valeur !
		mutable std::set<ValueType> _visited;

	public:
		
		const BasicIteratorInterface& get_basic_iterator_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*this->get_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*this->get_implementation()); }
		BasicIteratorInterface& get_basic_iterator_interface()  { return dynamic_cast< BasicIteratorInterface&> (*this->get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface()  { return dynamic_cast< InputIteratorInterface&> (*this->get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface()  { return dynamic_cast< ForwardIteratorInterface&> (*this->get_implementation()); }
		
		bool is_visited() const {
			if (!get_basic_iterator_interface().is_valid()) {
				return false;
			} else {
				ValueTemplate v = get_input_iterator_interface().get_value();
				if (_visited.find(v) != _visited.end()) { 
					return true;
				} else {
					_visited.insert(v);
					return false;
				}
			}
		}
		
		
		// ForwardIteratorInterface
		virtual void increment() { 
			get_forward_iterator_interface().increment();
			while (is_visited()) {
				get_forward_iterator_interface().increment();
			}
		}
		virtual void increment(int offset) { 
				for (int i = offset; i != offset; ++i) {
					increment(); 
			}
		}
		
		
		
		virtual void restart() {
			_visited.clear();
			get_basic_iterator_interface().restart();
		}
	
		
	};

	
	
	class UniqueFabric 
	
	{
		
	public:
		template <typename IteratorTemplate>		
		typename RemoveInterface<IteratorTemplate, internal::BackwardIteratorInterface>::IteratorType apply(const IteratorTemplate& iter) const { 
			typedef Unique<typename IteratorTemplate::ValueType, typename RemoveInterface<IteratorTemplate, internal::BackwardIteratorInterface>::IteratorType::BridgeType> BridgeType;
			typedef internal::TransformIteratorImplementation<BridgeType> Implementation;
			
			
			//typename IteratorTemplate::BridgeType* z;
			//internal::BackwardIteratorInterface* y = z;
			
			IteratorTemplate x;
			x.set_implementation(new Implementation(iter.get_implementation()->duplicate())); 
			return x;
		}
	};

#if 0 // FIXME le flatten ...
	template <typename IteratorTemplate, typename BridgeType>
	class Flatten : 
	public virtual BridgeType
	{
	private:
		// FIXME : rb_tree pour éviter de dupliquer la valeur !
		std::set<ValueType> _visited;
		
	public:
		typedef ValueTemplate ValueType;
		typedef internal::BasicIteratorInterface BasicIteratorInterface;
		typedef internal::InputIteratorInterface<ValueType> InputIteratorInterface;
		typedef internal::ForwardIteratorInterface ForwardIteratorInterface;
		typedef internal::BackwardIteratorInterface BackwardIteratorInterface;
		typedef internal::PtrDiffIteratorInterface PtrDiffIteratorInterface;
				
		const BasicIteratorInterface& get_basic_iterator_interface() const { return dynamic_cast<const BasicIteratorInterface&> (*this->get_implementation()); }
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		const ForwardIteratorInterface& get_forward_iterator_interface() const { return dynamic_cast<const ForwardIteratorInterface&> (*this->get_implementation()); }
		const BackwardIteratorInterface& get_backward_iterator_interface() const { return dynamic_cast<const BackwardIteratorInterface&> (*this->get_implementation()); }
		const PtrDiffIteratorInterface& get_ptr_diff_iterator_interface() const { return dynamic_cast<const PtrDiffIteratorInterface&> (*this->get_implementation()); }
		BasicIteratorInterface& get_basic_iterator_interface()  { return dynamic_cast< BasicIteratorInterface&> (*this->get_implementation()); }
		InputIteratorInterface& get_input_iterator_interface()  { return dynamic_cast< InputIteratorInterface&> (*this->get_implementation()); }
		ForwardIteratorInterface& get_forward_iterator_interface()  { return dynamic_cast< ForwardIteratorInterface&> (*this->get_implementation()); }
		BackwardIteratorInterface& get_backward_iterator_interface()  { return dynamic_cast< BackwardIteratorInterface&> (*this->get_implementation()); }
		PtrDiffIteratorInterface& get_ptr_diff_iterator_interface()  { return dynamic_cast< PtrDiffIteratorInterface&> (*this->get_implementation()); }
		
		// InputIteratorInterface
		virtual ValueType get_instance() const { ((BackwardIteratorInterface&) get_backward_iterator_interface()).decrement(); ValueType v = get_input_iterator_interface().get_instance(); ((ForwardIteratorInterface&) get_forward_iterator_interface()).increment(); return v; }
		
		// ForwardIteratorInterface
		virtual void increment() {  get_backward_iterator_interface().decrement(); }
		virtual void increment(int offset) {  get_backward_iterator_interface().decrement(offset); }
		
		// BackwardIteratorInterface
		virtual void decrement() {  get_forward_iterator_interface().increment(); }
		virtual void decrement(int offset) {  get_forward_iterator_interface().increment(offset); }
		
		//FIXME : is_equal et diff non - implémenté
		
		//FIXME: restart et is_valid aussi !!!
		
		
	};
	
	
	class FlattenFabric 
	{		
	public:
		template <typename IteratorTemplate>		
		typename IteratorTemplate::ValueType apply(const IteratorTemplate& iter) const { 
			typedef Flatten<typename IteratorTemplate::ValueType::ValueType, typename IteratorTemplate::ValueType::BridgeType> BridgeType;
			typedef internal::TransformIteratorImplementation<BridgeType> Implementation;
			
			
			IteratorTemplate x;
			x.set_implementation(new Implementation(iter.get_implementation()->duplicate())); 
			return x;
		}
	};
#endif

	
#if 1 //FIXME : l'accessor ...
	
	
	template <typename ValueTemplate, typename BridgeType, typename AccessorTemplate>
	class AccessorBridge : 
	public virtual BridgeType
	{
		AccessorTemplate _accessor;
	public:
		typedef internal::InputIteratorInterface<ValueTemplate> InputIteratorInterface;
		typedef typename internal::GenericTraits<typename AccessorTemplate::ValueType>::ValueType ValueType;
		
		AccessorBridge(const AccessorTemplate& accessor) : _accessor(accessor) {}
		AccessorBridge() {}
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_instance() const { return _accessor.get_value(get_input_iterator_interface().get_instance()); }
	};
	
	template <typename ValueTemplate, typename BridgeType, typename AccessorTemplate>
	class AccessorBridge<const ValueTemplate&, BridgeType, AccessorTemplate> : 
	public virtual AccessorBridge<ValueTemplate, BridgeType, AccessorTemplate>
	{
		AccessorTemplate _accessor;
	public:
		typedef internal::InputIteratorInterface<const ValueTemplate&> InputIteratorInterface;
		typedef typename internal::GenericTraits<typename AccessorTemplate::ValueType>::ConstRefType ValueType;
		
		AccessorBridge(const AccessorTemplate& accessor) : _accessor(accessor) {}
		AccessorBridge() {}
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_const_reference() const { return _accessor.get_value(get_input_iterator_interface().get_const_reference()); }
	};
	
	template <typename ValueTemplate, typename BridgeType, typename AccessorTemplate>
	class AccessorBridge< ValueTemplate&, BridgeType, AccessorTemplate> : 
	public virtual AccessorBridge<const ValueTemplate&, BridgeType, AccessorTemplate>
	{
		AccessorTemplate _accessor;
	public:
		typedef internal::InputIteratorInterface<ValueTemplate &> InputIteratorInterface;
		typedef typename internal::GenericTraits<typename AccessorTemplate::ValueType>::ReferenceType ValueType;
		
		AccessorBridge(const AccessorTemplate& accessor) : _accessor(accessor) {}
		AccessorBridge() {}
		const InputIteratorInterface& get_input_iterator_interface() const { return dynamic_cast<const InputIteratorInterface&> (*this->get_implementation()); }
		virtual ValueType get_reference() const { return _accessor.get_value(get_input_iterator_interface().get_reference()); }
	};
		
	
	class AccessorFabric 
	{
	public:
		template <typename IteratorTemplate, typename AccessorTemplate>
		
		typename IteratorTemplate::template ChangeValue<typename AccessorTemplate::ValueType>::Type apply(const IteratorTemplate& iter, const AccessorTemplate& accessor) const { 
			typedef typename IteratorTemplate::template ChangeValue<typename AccessorTemplate::ValueType>::Type NewIteratorType;
			typedef AccessorBridge<typename IteratorTemplate::ValueType, typename NewIteratorType::BridgeType, AccessorTemplate> BridgeType;
			typedef internal::TransformIteratorImplementation<BridgeType> Implementation;
			
			NewIteratorType x;
			x.set_implementation(new Implementation(iter.get_implementation()->duplicate(), BridgeType(accessor))); 
			return x;
		}
	};
#endif

} // namespace variety