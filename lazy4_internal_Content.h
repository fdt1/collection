/*
 *  lazy4_internal_Content.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

// for shared_ptr
#if defined( _MSC_VER )
#include <memory> 
#else
#include <tr1/memory>
namespace std { namespace tr1 { using namespace std; } }
#endif


namespace lazy4 {

	template <typename content_template>
	class Content;
		
	template<typename first_template, typename second_template, typename content_template>
	class Iterator;
	
	template<typename first_template, typename second_template, typename content_template>
	class Flow;
	
	template<typename first_template, typename second_template>
	class Pair;
	
	template<typename first_template, typename second_template, typename content_template>
	class Collection;
	
	template<typename first_template, typename second_template, typename closure_template>
	class Modifier;
	
	namespace internal {
		
		template<typename T>
		static inline T& getReference(T* t) { return *t; }
		
		template<typename T>
		static inline const T& getReference(const T* t) { return *t; }
		
		template<typename T>
		static inline T& getReference(T& t) { return t; }
		
		template<typename T>
		static inline const T& getReference(const T& t) { return t; }
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type
		{
			typedef value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef value_template template_type;
			typedef value_template const_template_type;
			typedef const value_template const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<value_template&>
		{
			typedef value_template& type;
			typedef value_template prime_type;
			typedef value_template& parameter_type;
			typedef value_template& template_type;
			typedef const value_template& const_template_type;
			typedef const value_template& const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<const value_template&>
		{
			typedef const value_template& type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef const value_template& template_type;
			typedef const value_template& const_template_type;
			typedef const value_template& const_type;
			typedef const value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef const value_template* pointer_type;
			typedef const value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<const value_template>
		{
			typedef const value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef const value_template template_type;
			typedef const value_template const_template_type;
			typedef const value_template const_type;
			typedef const value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef const value_template* pointer_type;
			typedef const value_template* const const_pointer_type;
		};
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type<value_template*>
		{
			typedef value_template* type;
			typedef value_template* prime_type;
			typedef value_template* const& parameter_type;
			typedef value_template* template_type;
			typedef value_template* const_template_type;
			typedef value_template* const const_type;
			typedef value_template*& ref_type;
			typedef value_template* const& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type<value_template* const>
		{
			typedef value_template* const type;
			typedef value_template* prime_type;
			typedef value_template* const& parameter_type;
			typedef value_template* template_type;
			typedef value_template* const const_template_type;
			typedef value_template* const const_type;
			typedef value_template* const& ref_type;
			typedef value_template* const& const_ref_type;
			typedef value_template* const pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<>
		struct Type<void>
		{
			typedef void* value_template;
			typedef value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef void template_type;
			typedef void const_template_type;
			typedef const value_template const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template pointer_type;
			typedef value_template const const_pointer_type;
		};
		
		
		//! @class Value specialization
		template<typename value_template>
		struct NestedType
		{
			typedef void first_type;
			typedef void second_type;
			typedef void content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Collection<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Iterator<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Flow<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<lazy4::Modifier<first_template, second_template, closure_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<lazy4::Pair<first_template, second_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Collection<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Iterator<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Flow<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<lazy4::Modifier<first_template, second_template, closure_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<lazy4::Pair<first_template, second_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Collection<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Iterator<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Flow<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<const lazy4::Modifier<first_template, second_template, closure_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<const lazy4::Pair<first_template, second_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Collection<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Iterator<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Flow<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<const lazy4::Modifier<first_template, second_template, closure_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<const lazy4::Pair<first_template, second_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> (& ((ref_old_first) first)) != NULL; }
			static first_template convert(const_ref_old_first first) { return *(dynamic_cast<pointer_first> (& ((ref_old_first) first))); }
		};
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast<first_template, old_first_template*> {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template*>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template*>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> ((ref_old_first) first) != NULL; }
			static first_template convert(const_ref_old_first first) { return (dynamic_cast<pointer_first> ((ref_old_first) first)); }
		};
		
		template <typename first_template, typename old_first_template>
		struct DynamicCast<first_template, old_first_template* const> {
			typedef typename internal::Type<first_template>::const_pointer_type const_pointer_first;
			typedef typename internal::Type<first_template>::pointer_type pointer_first;
			typedef typename internal::Type<old_first_template* const>::ref_type ref_old_first;
			typedef typename internal::Type<old_first_template* const>::const_ref_type const_ref_old_first;
			static bool isMatch(const_ref_old_first first) { return dynamic_cast<const_pointer_first> ((ref_old_first) first) != NULL; }
			static first_template convert(const_ref_old_first first) { return (dynamic_cast<pointer_first> ((ref_old_first) first)); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Bridge hides an implementation and shared allocation
		//! strategy
		//--------------------------------------------------------------------------------
		template <typename interface_template>
		class Bridge
		{
		public:
			typedef interface_template interface_type;
			typedef std::shared_ptr<interface_template> shared_interface_type;
		
		protected:
			shared_interface_type _shared_implementation;
			
		public:
			Bridge() {}
			
			Bridge(const interface_template* implementation) : _shared_implementation(const_cast<interface_template*> (implementation)) {}
			
			~Bridge() {}
			
		public:
			Bridge& operator= (const interface_template* implementation) { _shared_implementation = shared_interface_type(implementation); return *this; }
			
		public:
			//! @href lazy3::internal::IBridge::getSharedImplementation
			inline const shared_interface_type& getSharedImplementation() const { return _shared_implementation; }
			
			//! @href lazy3::internal::IBridge::getImplementation
			inline const interface_template* getImplementation() const { return _shared_implementation.get(); }
			
			//! @href lazy3::internal::IBridge::duplicateImplementation
			inline interface_template* duplicateImplementation() const { return dynamic_cast<interface_template*> (getImplementation()->clone()); }
			
			//! @href lazy3::internal::IBridge::getUniqueImplementation
			inline interface_template* getUniqueImplementation() { return !isUniqueImplementation() ? setImplementation(duplicateImplementation()) : const_cast<interface_template*> (getImplementation()); }
			
			//! @href lazy3::internal::IBridge::setImplementation
			inline interface_template* setImplementation(interface_template* implementation) { _shared_implementation = shared_interface_type(implementation); return implementation; }
			
			//! @href lazy3::internal::IBridge::countUse
			inline size_t countUse() const { return _shared_implementation.use_count(); }
			
			//! @href lazy3::internal::IBridge::isUniqueImplementation
			inline bool isUniqueImplementation() const { return countUse() <= 1; }
		};
		

		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template, bool is_bridge_template = true>
		struct ContentUtility
		{
		public:
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { return (ref_content_type) (bridge.getUniqueImplementation()->getContent()); }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { return (const_ref_content_type) (bridge.getImplementation()->getConstContent()); }
			
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct ContentUtility<void, true>
		{
			typedef void content_template;
			typedef internal::Type<content_template>::ref_type ref_content_type;
			typedef internal::Type<content_template>::type content_type;
			typedef internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { static content_type content = NULL; return content; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { static content_type content = NULL; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ContentUtility<const content_template, true>
		{
			typedef typename internal::Type<const content_template>::ref_type ref_content_type;
			typedef typename internal::Type<const content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<const content_template>::parameter_type parameter_content_type;
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { return (ref_content_type) (bridge.getImplementation()->getConstContent()); }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { return (const_ref_content_type) (bridge.getImplementation()->getConstContent()); }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct ContentUtility<void, false>
		{
			typedef void content_template;
			typedef internal::Type<content_template>::ref_type ref_content_type;
			typedef internal::Type<content_template>::type content_type;
			typedef internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { static content_type content = NULL; return content; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { static content_type content = NULL; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ContentUtility<content_template, false>
		{
		public:
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { return (ref_content_type) (bridge.container()); }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { return (const_ref_content_type) (bridge.container()); }
			
		};
		
		
		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class IContent
		{
		public:
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return duplicate of the current implementation
			virtual IContent* clone() const = 0;
			
		public:
			//! @return the pointer ID
			virtual const void* where() const = 0;
			
			//! @return the content
			virtual ref_content_type getContent() = 0;
			
			//! @return the content
			virtual const_ref_content_type getConstContent() const = 0;
			
			//! @return true if initialized
			virtual bool good() const = 0;			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Content wraps an implementation of a forward Content.
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class ContentBridge :
		public Bridge<IContent<content_template> >
		{
		public:
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
		public:
			typedef typename internal::IContent<content_template> IEmbeddedContent;
			typedef typename internal::Bridge<IEmbeddedContent> Bridge;
		public:
			typedef IEmbeddedContent interface_type;
			
		public:
			ContentBridge() {}
			
			ContentBridge(const IEmbeddedContent* implementation) : Bridge(implementation) {}
			
			ContentBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline ContentBridge& operator= (const IEmbeddedContent* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const ContentBridge& cast(const lazy4::Content<content_template>& Content) { return Content; }
			
			//! for compatibility
			static inline ContentBridge& cast(lazy4::Content<content_template>& Content) { return Content; }
			
			//! for compatibility
			static inline const ContentBridge& cast(const ContentBridge& Content) { return Content; }
			
			//! for compatibility
			static inline ContentBridge& cast(ContentBridge& Content) { return Content; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* where() const { if (const IEmbeddedContent* Content = Bridge::getImplementation()) return Content->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedContent* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedContent* clone() const { if (const IEmbeddedContent* generic = Bridge::getImplementation()) return generic->clone(); else return NULL; }
			
		public:
			//! @href lazy3::internal::IContentOncontent::content
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContentOncontent::content
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
			
		};	
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is an implementation of IContent
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class Content : 
		public IContent<content_template>
		{
		public:
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
		
		public:
			prime_content_type _content;
		
		public:
			Content(parameter_content_type content) : _content(content) {}
		
			Content() : _content() {}
		
		public:
			//! @return the pointer ID
			virtual const void* where() const { return &_content; }
			
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return const_cast<ref_content_type> (_content); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _content; }
			
			//! @href lazy3::internal::IImplementation::duplicate
			virtual Content* clone() const { return new Content(*this); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return true; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is a specialization
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class Content<content_template&> : 
		public IContent<content_template&>
		{
		public:
			typedef typename internal::Type<content_template&>::prime_type prime_content_type;
			typedef typename internal::Type<content_template&>::parameter_type parameter_content_type;
			typedef typename internal::Type<content_template&>::ref_type ref_content_type;
			typedef typename internal::Type<content_template&>::const_ref_type const_ref_content_type;
		
		public:
			prime_content_type* _content;
		
		public:
			Content(parameter_content_type content) : _content(const_cast<prime_content_type*> (&content)) {}
		
			Content() : _content(NULL) {}
		
		public:
			//! @return the pointer ID
			virtual const void* where() const { return _content; }
			
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() const { return const_cast<ref_content_type> (*_content); }
		
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return (*_content); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return *_content; }
			
			//! @href lazy3::internal::IImplementation::duplicate
			virtual Content* clone() const { return new Content(*this); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _content != NULL; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class ContentElement is a specialization
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class Content<const content_template&> : 
		public IContent<const content_template&>
		{
		public:
			typedef typename internal::Type<const content_template&>::prime_type prime_content_type;
			typedef typename internal::Type<const content_template&>::parameter_type parameter_content_type;
			typedef typename internal::Type<const content_template&>::ref_type ref_content_type;
			typedef typename internal::Type<const content_template&>::const_ref_type const_ref_content_type;
			
		public:
			const prime_content_type* _content;
			
		public:
			Content(parameter_content_type content) : _content(const_cast<prime_content_type*> (&content)) {}
			
			Content() : _content(NULL) {}
			
		public:
			//! @return the pointer ID
			virtual const void* where() const { return _content; }
			
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() const { return (*_content); }
			
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return (*_content); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return *_content; }
			
			//! @href lazy3::internal::IImplementation::duplicate
			virtual Content* clone() const { return new Content(*this); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _content != NULL; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
