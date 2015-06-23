/*
 *  lazy4_internal_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Query.h"
#include <stdexcept>


namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Collection;
	
	namespace internal {
		
		template<typename first_template, typename second_template, typename content_template>
		class IIterator;
		
		template<typename first_template, typename second_template, typename content_template>
		class Iterator;
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class ICollection :
		public IQuery<first_template, second_template, content_template>
		{
		public:
			typedef content_template input_template;
			typedef ICollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			
		public:
			//! @return duplicate of the current implementation
			virtual ICollection* clone() const = 0;
			
			//! @return the corresponding Iterator set at the beginning.
			virtual IIterator* cloneIterator() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Collection wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionBridge :
		public Bridge<ICollection<first_template, second_template, content_template> >
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::IIterator<first_template, second_template, content_template> IIterator;
			typedef typename internal::Bridge<IEmbeddedCollection> Bridge;
		public:
			typedef IEmbeddedCollection interface_type;
			
		public:
			CollectionBridge() {}
			
			CollectionBridge(const IEmbeddedCollection* implementation) : Bridge(implementation) {}
			
			CollectionBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline CollectionBridge& operator= (const IEmbeddedCollection* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const CollectionBridge& cast(const lazy4::Collection<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline CollectionBridge& cast(lazy4::Collection<first_template, second_template, content_template>& collection) { return collection; }
			
			//! for compatibility
			static inline const CollectionBridge& cast(const CollectionBridge& collection) { return collection; }
			
			//! for compatibility
			static inline CollectionBridge& cast(CollectionBridge& collection) { return collection; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedCollection* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedCollection* clone() const { if (const IEmbeddedCollection* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
			//! @return build the corresponding iterator
			inline IIterator* cloneIterator() const { if (const IEmbeddedCollection* Collection = const_cast<CollectionBridge*> (this)->Bridge::getUniqueImplementation()) return Collection->cloneIterator(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t size() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->size(); else return 0; }
			
			//! @href lazy3::internal::ICollectionOnBase::pop
			inline bool empty() const { if (const IEmbeddedCollection* Collection = Bridge::getImplementation()) return Collection->empty(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst(size_t steps) { return FirstUtility::getFirst(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirstWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(*this, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(*this, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond(size_t steps) { return SecondUtility::getSecond(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(*this, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(*this, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			inline bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(*this, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			inline bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(*this, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			inline bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(*this, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class IteratorWithBounds;
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorBridge;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithBounds is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class CollectionWithBounds : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithBounds<first_template, second_template, content_template> IteratorWithBounds;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			
		public:
			IteratorBridge _begin;
			IteratorBridge _end;
			
		public:
			CollectionWithBounds(const IteratorBridge& begin, const IteratorBridge& end) : _begin(begin), _end(end) {}
			
			CollectionWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _begin.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _begin.good() && _end.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithBounds* clone() const { return new CollectionWithBounds(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithBounds* cloneIterator() const { return new IteratorWithBounds(_begin, _end); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _begin.remains() - _end.remains(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return _begin.where() == _end.where(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps)  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				return current.getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps)  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const  { 
				IteratorBridge current = _begin;
				current.forward(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				IteratorBridge current = _begin;
				return current.find_first(first);
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				IteratorBridge current = _begin;
				return current.find_second(second);
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				IteratorBridge current = _begin;
				return current.find(first, second);
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_begin); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_begin); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template>
		class IteratorWithPermutation;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithPermutation is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class CollectionWithPermutation : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<second_template> FirstUtility;
			typedef typename internal::SecondUtility<first_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<second_template, first_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithPermutation<first_template, second_template, content_template> IteratorWithPermutation;
			typedef typename internal::CollectionBridge<second_template, first_template, content_template> CollectionBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithPermutation(const CollectionBridge& bridge) : _bridge(bridge) {}
			
			CollectionWithPermutation() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithPermutation* clone() const { return new CollectionWithPermutation(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPermutation* cloneIterator() const { return new IteratorWithPermutation(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithPermutation(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithPermutation(_bridge.getConstOutput(input)); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return SecondUtility::exist_second(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return FirstUtility::exist_first(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, second, first); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class IteratorWithStaticCast;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template, typename old_second_template, typename old_content_template>
		class CollectionWithStaticCast : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::ICollection<old_first_template, old_second_template, old_content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithStaticCast<first_template, second_template, content_template, old_first_template, old_second_template, old_content_template> IteratorWithStaticCast;
			typedef typename internal::CollectionBridge<old_first_template, old_second_template, old_content_template> CollectionBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithStaticCast(const CollectionBridge& bridge) : _bridge(bridge) {}
			
			CollectionWithStaticCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithStaticCast* clone() const { return new CollectionWithStaticCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithStaticCast* cloneIterator() const { return new IteratorWithStaticCast(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithStaticCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithStaticCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _bridge.size(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class IteratorWithFirstDynamicCast;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class CollectionWithFirstDynamicCast : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::ICollection<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithFirstDynamicCast<first_template, second_template, content_template, old_first_template> IteratorWithFirstDynamicCast;
			typedef typename internal::CollectionBridge<old_first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithFirstDynamicCast(const CollectionBridge& bridge) : _bridge(bridge) {}
			
			CollectionWithFirstDynamicCast() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstDynamicCast* clone() const { return new CollectionWithFirstDynamicCast(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstDynamicCast* cloneIterator() const { return new IteratorWithFirstDynamicCast(_bridge.cloneIterator()); }
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithFirstDynamicCast* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithFirstDynamicCast* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithFirstDynamicCast* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class IteratorWithFirstAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class CollectionWithFirstAccessor :
		public ICollection<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithFirstAccessor<first_template, second_template, content_template, old_first_template, closure_template> IteratorWithFirstAccessor;
			typedef typename internal::CollectionBridge<old_first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithFirstAccessor(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstAccessor* clone() const { return new CollectionWithFirstAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstAccessor* cloneIterator() const { return new IteratorWithFirstAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirstWithThrow(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirstWithThrow(_bridge, steps)); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_bridge, steps); }
			
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithFirstAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _bridge.exist_second(second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithFirstAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class IteratorWithSecondAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_second_template, typename closure_template>
		class CollectionWithSecondAccessor :
		public ICollection<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<old_second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<second_template, old_second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithSecondAccessor<first_template, second_template, content_template, old_second_template, closure_template> IteratorWithSecondAccessor;
			typedef typename internal::CollectionBridge<first_template, old_second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<second_template, old_second_template, closure_template> ModifierBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithSecondAccessor(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithSecondAccessor* clone() const { return new CollectionWithSecondAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithSecondAccessor* cloneIterator() const { return new IteratorWithSecondAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithSecondAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithSecondAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirst(size_t steps) { return FirstUtility::getFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual first_type getFirstWithThrow(size_t steps) { return FirstUtility::getFirstWithThrow(_bridge, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_bridge, steps); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_first(const_ref_first_type first) const { return _bridge.exist_first(first); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecond(size_t steps) { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecond(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecond(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecond(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual second_type getSecondWithThrow(size_t steps) { return FunctorUtility::getOutput(_modifier, SecondUtility::getConstSecondWithThrow(_bridge, steps)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return FunctorUtility::getConstOutput(_modifier, SecondUtility::getConstSecondWithThrow(_bridge, steps)); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithSecondAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithSecondAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
#if 1
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class IteratorWithPairAccessor;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename old_second_template, typename closure_template>
		class CollectionWithPairAccessor :
		public ICollection<first_template, second_template, content_template>	
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename lazy4::Pair<old_first_template, old_second_template> OldPair;
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<old_second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<Pair, OldPair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::IteratorWithPairAccessor<first_template, second_template, content_template, old_first_template, old_second_template, closure_template> IteratorWithPairAccessor;
			typedef typename internal::CollectionBridge<old_first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<Pair, OldPair, closure_template> ModifierBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithPairAccessor(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithPairAccessor* clone() const { return new CollectionWithPairAccessor(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPairAccessor* cloneIterator() const { return new IteratorWithPairAccessor(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithPairAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithPairAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { IteratorWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { IteratorWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { IteratorWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.first(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { IteratorWithPairAccessor* it = cloneIterator(); if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.first(); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { IteratorWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { IteratorWithPairAccessor* it = cloneIterator(); it->forward(steps); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { IteratorWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getOutput(_modifier, OldPair(it->getFirst(), it->getSecond())); delete it; return ret.second(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { IteratorWithPairAccessor* it = cloneIterator();  if (it->forward(steps) != steps) throw std::out_of_bounds("index too high"); Pair ret = FunctorUtility::getConstOutput(_modifier, OldPair(it->getConstFirst(), it->getConstSecond())); delete it; return ret.second(); }
			
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const {
				if (IteratorWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithPairAccessor* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
#endif
		
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithFirstFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithFirstFilter :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<filter_template, first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithFirstFilter<first_template, second_template, content_template, filter_template, closure_template> IteratorWithFirstFilter;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<filter_template, first_template, closure_template> ModifierBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithFirstFilter(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithFirstFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstFilter* clone() const { return new CollectionWithFirstFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithFirstFilter* cloneIterator() const { return new IteratorWithFirstFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithFirstFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithFirstFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithFirstFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
				
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithSecondFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithSecondFilter :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<filter_template, second_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithSecondFilter<first_template, second_template, content_template, filter_template, closure_template> IteratorWithSecondFilter;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<filter_template, second_template, closure_template> ModifierBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithSecondFilter(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithSecondFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithSecondFilter* clone() const { return new CollectionWithSecondFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithSecondFilter* cloneIterator() const { return new IteratorWithSecondFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithSecondFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithSecondFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithSecondFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithSecondFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithSecondFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class IteratorWithPairFilter;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename filter_template, typename closure_template>
		class CollectionWithPairFilter :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename lazy4::Pair<first_template, second_template> Pair;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<filter_template, Pair> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			//typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithPairFilter<first_template, second_template, content_template, filter_template, closure_template> IteratorWithPairFilter;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::ModifierBridge<filter_template, Pair, closure_template> ModifierBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			CollectionWithPairFilter(const CollectionBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public:
			//! @return duplicate of the nested implementation
			//! @param steps increment for the clone
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithPairFilter* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithPairFilter* clone() const { return new CollectionWithPairFilter(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithPairFilter* cloneIterator() const { return new IteratorWithPairFilter(_bridge.cloneIterator(), _modifier); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithPairFilter(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithPairFilter(_bridge.getConstOutput(input), _modifier); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithPairFilter* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithPairFilter* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithPairFilter* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
				
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithFirstUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithFirstUnique :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithFirstUnique<first_template, second_template, content_template> IteratorWithFirstUnique;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithFirstUnique(const CollectionBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithFirstUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstUnique* clone() const { return new CollectionWithFirstUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithFirstUnique* cloneIterator() const { return new IteratorWithFirstUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstUnique(_bridge.getConstOutput(input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithFirstUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithFirstUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithSecondUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithSecondUnique :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithSecondUnique<first_template, second_template, content_template> IteratorWithSecondUnique;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithSecondUnique(const CollectionBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithSecondUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithSecondUnique* clone() const { return new CollectionWithSecondUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithSecondUnique* cloneIterator() const { return new IteratorWithSecondUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithSecondUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithSecondUnique(_bridge.getConstOutput(input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithSecondUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithSecondUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithPairUnique;
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithPairUnique :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithPairUnique<first_template, second_template, content_template> IteratorWithPairUnique;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithPairUnique(const CollectionBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithPairUnique* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithPairUnique* clone() const { return new CollectionWithPairUnique(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithPairUnique* cloneIterator() const { return new IteratorWithPairUnique(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithPairUnique(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithPairUnique(_bridge.getConstOutput(input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithPairUnique* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithPairUnique* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_bridge, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename content_template>
		class IteratorWithReverse;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class CollectionWithReverse :
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithReverse<first_template, second_template, content_template> IteratorWithReverse;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithReverse(const CollectionBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline IteratorBridge cloneIterator(size_t steps) const { IteratorWithReverse* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithReverse* clone() const { return new CollectionWithReverse(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithReverse* cloneIterator() const { return new IteratorWithReverse(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithReverse(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithReverse(_bridge.getConstOutput(input)); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _bridge.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _bridge.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst();	}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps);	
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const {
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return _bridge.exist_first(first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _bridge.exist_second(second); } 
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_bridge, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class IteratorWithConcatenation;
		
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithStaticCast is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename prev_content_template, typename next_content_template>
		class CollectionWithConcatenation :
		public ICollection<first_template, second_template, 
		lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> >	
		{
		public:
			typedef typename lazy4::Pair<typename internal::Type<prev_content_template>::ref_type, typename internal::Type<next_content_template>::ref_type> content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithConcatenation<first_template, second_template, prev_content_template, next_content_template> IteratorWithConcatenation;
			typedef typename internal::CollectionBridge<first_template, second_template, prev_content_template> PrevCollectionBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, next_content_template> NextCollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			PrevCollectionBridge _prev;
			NextCollectionBridge _next;
			content_template _content;
			
		public:
			CollectionWithConcatenation(const PrevCollectionBridge& prev, const NextCollectionBridge& next) : _prev(prev), _next(next), _content(_prev.getContent(), _next.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return content_template::Bridge::cast(_content).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _prev.good() && _next.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithConcatenation* clone() const { return new CollectionWithConcatenation(*this); }
			
			//! @return the corresponding iterator
			virtual IteratorWithConcatenation* cloneIterator() const { return new IteratorWithConcatenation(_prev.cloneIterator(), _next.cloneIterator()); }
			
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			IteratorBridge cloneIterator(size_t steps) const { IteratorWithConcatenation* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithConcatenation(_prev.getOutput(input.first()), _next.getOutput(input.second())); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithConcatenation(_prev.getConstOutput(input.first()), _next.getConstOutput(input.second())); }
			
		public: // ICollection			
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { return _prev.size() + _next.size(); }			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { return _prev.empty() && _next.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { return cloneIterator(steps).getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return cloneIterator(steps).getConstFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return cloneIterator(steps).getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return cloneIterator(steps).getConstSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				IteratorBridge current = cloneIterator(steps); 
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return _prev.exist_first(first) || _next.exist_first(first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return _prev.exist_second(second) || _next.exist_second(second); } 
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return _prev.exist(first, second) || _next.exist(first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
		};
		
		
		template<typename container_first_template, typename other_second_template, typename content_template>
		class IteratorWithFirstFlatten;
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithFirstFlatten is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class CollectionWithFirstFlatten :
		public ICollection<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithFirstFlatten<container_first_template, other_second_template, content_template> IteratorWithFirstFlatten;
			typedef typename internal::IteratorBridge<container_first_template, other_second_template, content_template> IteratorBridge;
			typedef typename internal::CollectionBridge<container_first_template, other_second_template, content_template> CollectionBridge;
			typedef typename internal::IteratorBridge<first_template, second_template, other_content_template> NestedIteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, other_content_template> NestedCollectionBridge;			
			
		public:
			CollectionBridge _bridge;
			
		public:
			CollectionWithFirstFlatten(const CollectionBridge& bridge) : _bridge(bridge) {}
			
		public:
			//! @return the corresponding iterator incremented
			//! param steps number of increments
			inline NestedIteratorBridge cloneIterator(size_t steps) const { IteratorWithFirstFlatten* iterator = cloneIterator(); iterator->forward(steps); return iterator; }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithFirstFlatten* clone() const { return new CollectionWithFirstFlatten(*this); }
			
			//! @return build the corresponding collection
			virtual IteratorWithFirstFlatten* cloneIterator() const { return new IteratorWithFirstFlatten(_bridge.cloneIterator()); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new CollectionWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new CollectionWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // ICollection		
			//! @href lazy3::internal::ICollectionOnBase::remains
			virtual size_t size() const { 
				size_t count = 0;
				if (const IteratorWithFirstFlatten* iterator = cloneIterator()) {
					count = iterator->remains();
					delete iterator;
				}
				return count;
			}			
			
			//! @return true if the Collection is at the end.
			virtual bool empty() const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isEnd = iterator->eof();
					delete iterator;
					return isEnd;
				} 
				return true; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps) { 
				return cloneIterator(steps).getFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { 
				return cloneIterator(steps).getConstFirst();
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps) { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstFirst();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { 
				return cloneIterator(steps).getSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { 
				return cloneIterator(steps).getConstSecond();
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { 
				NestedIteratorBridge current = cloneIterator(steps);
				if (!current.eof()) {
					return current.getConstSecond();
				} else {
					throw std::out_of_range("Collection::out of range");
				}
			}
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find_first(first);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find_second(second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { 
				if (IteratorWithFirstFlatten* iterator = cloneIterator()) {
					bool isFound = iterator->find(first, second);
					delete iterator;
					return isFound;
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class IteratorWithInheritance;
		
		//--------------------------------------------------------------------------------
		//! @class CollectionWithBounds is an implementation of a Collection to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, typename     inheritance_template>
		class CollectionWithInheritance : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
			typedef inheritance_template InheritCollection;
			typedef IEmbeddedCollection interface_type;			
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::FirstUtility<first_template, false> FirstUtility;
			typedef typename internal::SecondUtility<second_template, false> SecondUtility;
			typedef typename internal::PairUtility<first_template, second_template, false> PairUtility;
			typedef typename internal::ContentUtility<content_template, false> ContentUtility;
			typedef typename internal::FunctorUtility<output_template, input_template, false> FunctorUtility;
			
		public:
			typedef typename internal::IteratorWithInheritance<first_template, second_template, content_template, typename InheritCollection::Iterator> IteratorWithInheritance;
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			typedef typename internal::CollectionBridge<first_template, second_template, content_template> CollectionBridge;
			
		public:
			InheritCollection _collection;
			
		public:
			CollectionWithInheritance(const InheritCollection& collection) : _collection(collection) {}
			
			CollectionWithInheritance(parameter_input_type input) : _collection(input) {}
			
			CollectionWithInheritance() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return InheritCollection::Bridge::cast(_collection).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _collection.good(); }
			
			//! @return duplicate of the nested implementation
			virtual CollectionWithInheritance* clone() const { return new CollectionWithInheritance(*this); }
			
			//! @return duplicate of the nested implementation
			virtual IteratorWithInheritance* cloneIterator() const { return new IteratorWithInheritance(_collection.begin()); }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t size() const { return _collection.size(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return _collection.empty(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst(size_t steps)  { return FirstUtility::getFirst(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst(size_t steps) const { return FirstUtility::getConstFirst(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirstWithThrow(size_t steps)  { return FirstUtility::getFirstWithThrow(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return FirstUtility::getConstFirstWithThrow(_collection, steps); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond(size_t steps) { return SecondUtility::getSecond(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond(size_t steps) const { return SecondUtility::getConstSecond(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecondWithThrow(size_t steps) { return SecondUtility::getSecondWithThrow(_collection, steps); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return SecondUtility::getConstSecondWithThrow(_collection, steps); }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return FirstUtility::exist_first(_collection, first); }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return SecondUtility::exist_second(_collection, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return PairUtility::exist(_collection, first, second); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_collection); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_collection); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Collection to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class Collection : 
		public ICollection<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;			
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::prime_type prime_first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::prime_type prime_second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator;		
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Collection specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class Collection<first_template, second_template, void > : 
		public ICollection<first_template, second_template, void >
		{
		public:
			typedef void content_template;
			typedef typename internal::ICollection<first_template, second_template, content_template> IEmbeddedCollection;
			typedef content_template input_template;
			typedef IEmbeddedCollection* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			typedef typename internal::Iterator<first_template, second_template, content_template> Iterator;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			
		public:
			Collection() {}
			
			Collection(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second) {}
			
			Collection(parameter_first_type first) : _firstContent(first) {}
			
			Collection(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual Collection* clone() const { return new Collection(*this); }			
			
			//! @href lazy3::internal::ICommon::clone
			virtual Iterator* cloneIterator() const { return new Iterator(_firstContent, _secondContent); }			
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return good() ? _firstContent.where() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirstWithThrow(size_t steps) { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirstWithThrow(size_t steps) const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecondWithThrow(size_t steps) { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecondWithThrow(size_t steps) const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool good() const { return _firstContent.good() && _secondContent.good(); }
			
			//! @return true if the Collection is at the beginning.
			virtual bool empty() const { return !good(); }
			
			//! @return true if the Collection is at the end.
			virtual size_t size() const { return good(); }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { static content_type content; return content; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { static content_type content; return content; }
			
			//! @return true if an occurence of first exists.
			//! @param first element to search
			virtual bool exist_first(const_ref_first_type first) const { return good() && _firstContent.getConstContent() == first; }
			
			//! @return true if an occurence of second exists.
			//! @param second element to search
			virtual bool exist_second(const_ref_second_type second) const { return good() && _secondContent.getConstContent() == second; }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool exist(const_ref_first_type first, const_ref_second_type second) const { return good() && _firstContent.getConstContent() == first && _secondContent.getConstContent() == second; }
		};
		
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
