/*
 *  lazy5_content.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include <memory> // for shared_ptr
#include <tuple>
#include <type_traits>
#include <functional>

namespace lazy5 {

	
///////////////////////////////////////

	template<typename __HiddenInterface, typename __Interface = __HiddenInterface, typename __Inheritance = __Interface>
	class bridge : public bridge<__HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : bridge<__HiddenInterface, __Interface, typename __Inheritance::super_type>(std::forward<AnyContent>(content)) { /*std::cout<<"+++"<<std::endl;*/	}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : bridge<__HiddenInterface, __Interface, typename __Inheritance::super_type>(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	};


///////////////////////////////////////

	class Igeneric {
	public:
		typedef Igeneric type;
		typedef std::_Nil super_type;
		typedef std::_Nil key_type;
		typedef std::_Nil value_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Igeneric type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : std::integral_constant<bool, false> {	
		};

		template <>
		struct has_all_methods_of<Igeneric> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual bool good() const = 0;
		//virtual void content(Igeneric* interface) = 0;
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Itemplate_generic : public Igeneric {
	public:
		typedef Itemplate_generic type;
		typedef Igeneric super_type;
		typedef KeyOrValue key_or_value_template;
		typedef OptionalValue optional_value_template;
		typedef typename std::conditional<std::is_same<OptionalValue, std::_Nil>::value, KeyOrValue, OptionalValue>::type value_type;
		typedef typename std::conditional<std::is_same<OptionalValue, std::_Nil>::value, size_t, KeyOrValue>::type key_type;
		typedef typename std::conditional<std::is_same<OptionalValue, std::_Nil>::value, KeyOrValue, OptionalValue>::type value_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Itemplate_generic<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface> {	
		};

		template <>
		struct has_all_methods_of<Itemplate_generic> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Ielement : public Itemplate_generic<KeyOrValue, OptionalValue> {
	public:
		typedef Ielement type;
		typedef Itemplate_generic super_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Ielement<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Ielement<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual typename std::add_const<value_type>::type value() const = 0;
		virtual typename std::add_const<key_type>::type key() const = 0;
		virtual type* __clone() const = 0;
	};
	

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Icontent : public Ielement<KeyOrValue, OptionalValue> {
	public:
		typedef Icontent type;
		typedef Ielement super_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Icontent<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Icontent<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<value_type>::type&& value) = 0;
		virtual type* __clone() const = 0;
	};
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Ireference : public Icontent<KeyOrValue, OptionalValue> {
	public:
		typedef Ireference type;
		typedef Icontent super_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Ireference<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Ireference<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
	};
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Iflow : public Ielement<KeyOrValue, OptionalValue> {
	public:
		typedef Iflow type;
		typedef Ielement super_type;
	public:
		typedef typename std::forward_iterator_tag iterator_category;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename std::ptrdiff_t distance_type;	// retained
		typedef typename std::add_pointer<value_type>::type pointer;
		typedef typename std::add_reference<typename std::add_const<value_type>::type>::type reference;

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Iflow<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Iflow<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

	public:
/*		
		virtual size_t distance() const = 0;
*/	
		virtual void flush() = 0;	
		virtual bool eof() const = 0;
		virtual size_t forward(size_t count = 1) = 0;
		virtual bool seek(typename std::decay<key_type>::type const& key) = 0;
		virtual const void* where() const = 0;
		virtual type* __clone() const = 0;
	};
	
	template<typename KeyOrValue, typename OptionalValue>
	class Icollection;
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Iiterator : public Iflow<KeyOrValue, OptionalValue> {
	public:
		typedef Iiterator type;
		typedef Iflow super_type;
		typedef Icollection<KeyOrValue, OptionalValue> collection_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Iiterator<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Iiterator<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual collection_type* __clone_collection() const = 0;
		virtual size_t backward(size_t count = 1) = 0;
	};
	
	template<typename KeyOrValue, typename OptionalValue>
	class Imap;
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Imap_iterator : public Iiterator<KeyOrValue, OptionalValue> {
	public:
		typedef Imap_iterator type;
		typedef Iiterator super_type;
		typedef Imap<KeyOrValue, OptionalValue> collection_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Imap_iterator<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Imap_iterator<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Icontent<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Ireference<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<value_type>::type&& value) = 0;
		virtual void erase() = 0;
		virtual type* __clone() const = 0;
		virtual collection_type* __clone_collection() const = 0;
	};

	template<typename KeyOrValue, typename OptionalValue>
	class Ilist;
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Ilist_iterator : public Imap_iterator<KeyOrValue, OptionalValue> {
	public:
		typedef Ilist_iterator type;
		typedef Imap_iterator super_type;
		typedef Ilist<KeyOrValue, OptionalValue> collection_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Ilist_iterator<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface> {	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Ilist_iterator<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual collection_type* __clone_collection() const = 0;
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Iquery : public Itemplate_generic<KeyOrValue, OptionalValue> {
	public:
		typedef Iquery type;
		typedef Itemplate_generic super_type;
		typedef Iflow<KeyOrValue, OptionalValue> iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Iquery<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Iquery<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual Iquery* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const = 0;
	};
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Icollection : public Iquery<KeyOrValue, OptionalValue> {
	public:
		typedef Icollection type;
		typedef Iquery super_type;
		typedef Iiterator<KeyOrValue, OptionalValue> iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Icollection<AnyKey, AnyValue> type;
			typedef type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Icollection<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
	};
	
	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Imap : public Icollection<KeyOrValue, OptionalValue> {
	public:
		typedef Imap type;
		typedef Icollection super_type;
		typedef typename Imap_iterator<KeyOrValue, OptionalValue> iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Imap<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface> {	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Imap<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<key_type>::type const& key) = 0;
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Ilist : public Imap<KeyOrValue, OptionalValue> {
	public:
		typedef Ilist type;
		typedef Imap super_type;
		typedef typename Ilist_iterator<KeyOrValue, OptionalValue> iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Ilist<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface> {	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Ilist<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
	};



	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Imatrix : public Icollection<KeyOrValue, bridge<Icollection<KeyOrValue, OptionalValue>>> {
	public:
		typedef Imatrix type;
		typedef Icollection super_type;
		typedef typename super_type::iterator_type iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Imatrix<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Imatrix<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class Irange : public Ilist<KeyOrValue, bridge<Ilist<KeyOrValue, OptionalValue>>> {
	public:
		typedef Irange type;
		typedef Ilist super_type;
		typedef typename super_type::iterator_type iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Irange<AnyKey, AnyValue> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey, typename AnyValue>
		struct has_all_methods_of<Irange<AnyKey, AnyValue>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
	};

	//////////////////////////////
	//////////////////////////////



	template<typename __Interface, typename __Inheritance = __Interface>
	class concatenator : public concatenator<__Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename __Inheritance::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename __Interface>
	class concatenator<__Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface super_type;
	public:
		bridge<__Interface> _left_content;
		bridge<__Interface> _right_content;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : _left_content(std::forward<AnyLeftContent> (left_content)), _right_content(std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new concatenator<__Interface>(const_cast<concatenator*>(this)->_left_content, const_cast<concatenator*>(this)->_right_content); }
		virtual bool good() const { return _left_content.good() && _right_content.good(); }
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Ielement<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename Ielement::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual typename std::add_const<value_type>::type value() const { return !_left_content.eof() ? _left_content.value() : _right_content.value(); }
		virtual typename std::add_const<key_type>::type key() const { return !_left_content.eof() ? _left_content.key() : _right_content.key(); }
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Iflow<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename Iflow::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void flush() { _left_content.flush(); _right_content.flush(); }	
		virtual bool eof() const { return _left_content.eof() && _right_content.eof(); }
		virtual const void* where() const { return !_left_content.eof() ? _left_content.where() : _right_content.where();; }
		virtual size_t forward(size_t count = 1) { size_t jump = count == 0 ? 0 : _left_content.forward(count); return jump == count ? count  : jump + _right_content.forward(count - jump); }
		virtual bool seek(typename std::decay<key_type>::type const& key) { return _left_content.seek(key) || _right_content.seek(key); }
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Iiterator<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename concatenator<__Interface, typename Iiterator::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new concatenator<collection_type>(_left_content.collection(), _right_content.collection()); }
		virtual size_t backward(size_t count = 1) { size_t jump = count == 0 ? 0 : _right_content.backward(count); return jump == count ? count : jump + _left_content.backward(count - jump); }
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename concatenator<__Interface, typename Imap_iterator::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { if (!_left_content.eof()) { _left_content.set(value); } else { _right_content.set(value); } }
		virtual void set(typename std::decay<value_type>::type&& value) { if (!_left_content.eof()) { _left_content.set(value); } else { _right_content.set(value); } }
		virtual void erase() { if (!_left_content.eof()) { _left_content.erase(); } else { _right_content.erase(); } }
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename Ilist_iterator::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Iquery<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename concatenator<__Interface, typename Iquery::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new concatenator<typename __HiddenLeftInterface::iterator_type, typename __HiddenRightInterface::iterator_type, typename __Interface::iterator_type>(_left_content.begin(), _right_content.begin()); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto left_iterator = _left_content.find(key); 
			return new concatenator<typename __Interface::iterator_type>(left_iterator, !left_iterator.eof() ? _right_content.begin() : _right_content.find(key));
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto left_iterator = _left_content.find(key); 
			return !left_iterator.eof() ? left_iterator.get() : _right_content.value(key);
		}
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Imap<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename Imap::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<key_type>::type const& key) { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));			
			if (iterator && !iterator->eof()) {
				iterator->erase();
			}
		}
	};
	
	template<typename __Interface, typename KeyOrValue, typename OptionalValue>
	class concatenator<__Interface, Ilist<KeyOrValue, OptionalValue>> : public concatenator<__Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename concatenator<__Interface, typename Ilist::super_type> super_type;
	public:
		concatenator() {}
		template <typename AnyLeftContent, typename AnyRightContent>
		concatenator(AnyLeftContent&& left_content, AnyRightContent&& right_content) : super_type(std::forward<AnyLeftContent> (left_content), std::forward<AnyRightContent> (right_content)) {std::cout<<__LINE__<<"  "<< typeid(left_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
	};
	
	//////////////////////////////
	//////////////////////////////////////////
	

	
	template<typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class flatten_value : public flatten_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename __HiddenInterface, typename __Interface>
	class flatten_value<__HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : _content(std::forward<AnyContent> (content)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new flatten_value<__HiddenInterface, __Interface>(const_cast<flatten_value*>(this)->_content); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		template < bool Compatible>
		class xx {
		public:
			template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
			static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& content) { return content; }
		};

		template < >
		class xx<false> {
		public:
			template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
			static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& content) { return content.begin(); }
		};
		template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
		static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& bridge) { return xx<std::is_base_of<Ielement<typename AnyInterface::key_or_value_template, typename AnyInterface::optional_value_template>, AnyInterface>::value>::get_nested_element( (bridge)); }

	public:
		virtual typename std::add_const<value_type>::type value() const { return get_nested_element(_content.value()).value(); }
		virtual typename std::add_const<key_type>::type key() const { return get_nested_element(_content.value()).key(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		bridge<__Interface> _nested_iterator;
	public:
		bridge<__Interface> get_nested_valid_element_forward() {
			if (!_content.eof()) {
				do {
					auto iterator = get_nested_element(_content.value()); 
					if (!iterator.eof()) {
						return iterator;
					}
				} while (_content.forward());
			}
			// invalid nested iterator
			return bridge<__Interface>();
		}

		bridge<__Interface> get_nested_valid_element_backward() { 
			do {
				auto iterator = get_nested_element(_content.value()); 
				if (!iterator.eof()) {
					return iterator;
				}
			} while (_content.backward());
			// invalid nested iterator
			return bridge<__Interface>();
		}

	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)), _nested_iterator(get_nested_valid_element_forward()) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content)), _nested_iterator(std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new flatten_value<__HiddenInterface, __Interface>(const_cast<flatten_value*>(this)->_content, const_cast<flatten_value*>(this)->_nested_iterator); }
		virtual bool good() const { return _nested_iterator.good(); }
		virtual typename std::add_const<value_type>::type value() const { return _nested_iterator.value(); }
		virtual typename std::add_const<key_type>::type key() const { return _nested_iterator.key(); }
	public:
		virtual void flush() { _content.flush(); _nested_iterator = bridge<__Interface>(); }
		virtual bool eof() const { return _content.eof() || _nested_iterator.eof(); }
		virtual const void* where() const { return _nested_iterator.where(); }
		virtual size_t forward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0 && !_nested_iterator.eof()) {
				size_t jump = _nested_iterator.forward(count);
				all_jumps += jump;
				if (jump == count) {
					if (_nested_iterator.eof()) {
						_content.forward();
						_nested_iterator = get_nested_valid_element_forward();
					}
					break;
				} else {
					count -= jump;
					_content.forward();
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return all_jumps;
		}
		virtual bool seek(typename std::decay<key_type>::type const& key) { 
			while (!_nested_iterator.seek(key)) {
				if (!_content.forward()) {
					_nested_iterator = bridge<__Interface>();
					return false;
				} else {
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return true;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new flatten_value<typename __HiddenInterface::collection_type, collection_type>(_content.collection()); }
		virtual size_t backward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0) {
				size_t jump = _nested_iterator.backward(count);
				all_jumps += jump;
				if (jump == count) {
					break;
				}
					
				if (!_content.backward()) {
					break;
				}
				_nested_iterator = get_nested_valid_element_backward();
			}
			return all_jumps;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _nested_iterator.set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _nested_iterator.set(value); }
		virtual void erase() { _nested_iterator.erase(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new flatten_value<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin()); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto iterator = __clone_iterator();
			if (iterator) {
				iterator->seek(key);
			}
			return iterator;
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));
			return iterator->value();
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<key_type>::type const& key) { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));			
			if (iterator && !iterator->eof()) {
				iterator->erase();
			}
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class flatten_value<__HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public flatten_value<__HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename flatten_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		flatten_value() {}
		template <typename AnyContent>
		flatten_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyNestedContent>
		flatten_value(AnyContent&& content, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
	};

	
	//////////////////////////////
	//////////////////////////////////////////

	
	template<typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class isolate_value : public isolate_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename __HiddenInterface, typename __Interface>
	class isolate_value<__HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
		size_t _rank;
	public:
		isolate_value() : _rank(0) {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : _content(std::forward<AnyContent> (content)), _rank(std::forward<AnyRank> (rank)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : _content(std::forward<AnyContent> (content)), _rank(std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new isolate_value<__HiddenInterface, __Interface>(const_cast<isolate_value*>(this)->_content, _rank); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		template < bool Compatible>
		class xx {
		public:
			template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
			static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& content) { return content; }
		};

		template < >
		class xx<false> {
		public:
			template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
			static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& content) { return content.begin(); }
		};
		template <typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
		static bridge<__Interface> get_nested_element(const bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& bridge) { return xx<std::is_base_of<Ielement<typename AnyInterface::key_or_value_template, typename AnyInterface::optional_value_template>, AnyInterface>::value>::get_nested_element( (bridge)); }

	public:
		virtual typename std::add_const<value_type>::type value() const { return get_nested_element(_content.value()).value(); }
		virtual typename std::add_const<key_type>::type key() const { return get_nested_element(_content.value()).key(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		bridge<__Interface> _nested_iterator;

	public:
		bridge<__Interface> get_nested_valid_element_forward() {
			if (!_content.eof()) {
				do {
					auto iterator = get_nested_element(_content.value()); 
					if (iterator.forward(_rank) == _rank) {
						return iterator;
					}
				} while (_content.forward());
			}
			// invalid nested iterator
			return bridge<__Interface>();
		}

		bridge<__Interface> get_nested_valid_element_backward() { 
			do {
				auto iterator = get_nested_element(_content.value()); 
				if (iterator.forward(_rank) == _rank) {
					return iterator;
				}
			} while (_content.backward());
			// invalid nested iterator
			return bridge<__Interface>();
		}

	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)), _nested_iterator(get_nested_valid_element_forward()) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)), _nested_iterator(std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new isolate_value<__HiddenInterface, __Interface>(const_cast<isolate_value*>(this)->_content, _rank, const_cast<isolate_value*>(this)->_nested_iterator); }
		virtual bool good() const { return _nested_iterator.good(); }
		virtual typename std::add_const<value_type>::type value() const { return _nested_iterator.value(); }
		virtual typename std::add_const<key_type>::type key() const { return _nested_iterator.key(); }
	public:
		virtual void flush() { _content.flush(); _nested_iterator = bridge<__Interface>(); }
		virtual bool eof() const { return _content.eof(); }
		virtual const void* where() const { return _nested_iterator.where(); }
		virtual size_t forward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0 && !_nested_iterator.eof()) {
				size_t jump = _nested_iterator.forward(count);
				all_jumps += jump;
				if (jump == count) {
					if (_nested_iterator.eof()) {
						_content.forward();
						_nested_iterator = get_nested_valid_element_forward();
					}
					break;
				} else {
					count -= jump;
					_content.forward();
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return all_jumps;
		}
		virtual bool seek(typename std::decay<key_type>::type const& key) { 
			while (!_nested_iterator.seek(key)) {
				if (!_content.forward()) {
					_nested_iterator = bridge<__Interface>();
					return false;
				} else {
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return true;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new isolate_value<typename __HiddenInterface::collection_type, collection_type>(_content.collection(), _rank); }
		virtual size_t backward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0) {
				size_t jump = _nested_iterator.backward(count);
				all_jumps += jump;
				if (jump == count) {
					break;
				}
					
				if (!_content.backward()) {
					break;
				}
				_nested_iterator = get_nested_valid_element_backward();
			}
			return all_jumps;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _nested_iterator.set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _nested_iterator.set(value); }
		virtual void erase() { _nested_iterator.erase(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new isolate_value<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin(), _rank); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto iterator = __clone_iterator();
			if (iterator) {
				iterator->seek(key);
			}
			return iterator;
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));
			return iterator->value();
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<key_type>::type const& key) { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));			
			if (iterator && !iterator->eof()) {
				iterator->erase();
			}
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class isolate_value<__HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public isolate_value<__HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename isolate_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		isolate_value() {}
		template <typename AnyContent, typename AnyRank>
		isolate_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		isolate_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
	};


	//////////////////////////////
	//////////////////////////////////////////
	
#if 0 // TODO
	
	template<typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class transpose_value : public transpose_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename __HiddenInterface, typename __Interface>
	class transpose_value<__HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
	public:
		transpose_value() : _rank(0) {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : _content(std::forward<AnyContent> (content)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new transpose_value<__HiddenInterface, __Interface>(const_cast<transpose_value*>(this)->_content); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		size_t _rank;
	public:
		transpose_value() : _rank(0) {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content)), _rank(std::forward<AnyRank> (rank)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyNestedContent> (nested_content)), _rank(std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new transpose_value<__HiddenInterface, __Interface>(const_cast<transpose_value*>(this)->_content, _rank); }
		virtual typename std::add_const<value_type>::type value() const { return get_nested_element(_content.value()).value(); }
		virtual typename std::add_const<key_type>::type key() const { return get_nested_element(_content.value()).key(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) { std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl; }
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), _rank(std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void flush() { _content.flush(); fixme; }
		virtual bool eof() const { return _content.eof(); }
		virtual const void* where() const { return _content.where(); }
		virtual size_t forward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0 && !_nested_iterator.eof()) {
				size_t jump = _nested_iterator.forward(count);
				all_jumps += jump;
				if (jump == count) {
					if (_nested_iterator.eof()) {
						_content.forward();
						_nested_iterator = get_nested_valid_element_forward();
					}
					break;
				} else {
					count -= jump;
					_content.forward();
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return all_jumps;
		}
		virtual bool seek(typename std::decay<key_type>::type const& key) { 
			while (!_nested_iterator.seek(key)) {
				if (!_content.forward()) {
					_nested_iterator = bridge<__Interface>();
					return false;
				} else {
					_nested_iterator = get_nested_valid_element_forward();
				}
			}
			return true;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new transpose_value<typename __HiddenInterface::collection_type, collection_type>(_content.collection(), _rank); }
		virtual size_t backward(size_t count = 1) {
			size_t all_jumps = 0;
			while (count != 0) {
				size_t jump = _nested_iterator.backward(count);
				all_jumps += jump;
				if (jump == count) {
					break;
				}
					
				if (!_content.backward()) {
					break;
				}
				_nested_iterator = get_nested_valid_element_backward();
			}
			return all_jumps;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _nested_iterator.set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _nested_iterator.set(value); }
		virtual void erase() { _nested_iterator.erase(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new transpose_value<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin(), _rank); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto iterator = __clone_iterator();
			if (iterator) {
				iterator->seek(key);
			}
			return iterator;
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));
			return iterator->value();
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<key_type>::type const& key) { 
			auto iterator = std::shared_ptr<iterator_type> (__find_iterator(key));			
			if (iterator && !iterator->eof()) {
				iterator->erase();
			}
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class transpose_value<__HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public transpose_value<__HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename transpose_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		transpose_value() {}
		template <typename AnyContent, typename AnyRank>
		transpose_value(AnyContent&& content, AnyRank&& rank) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyRank, typename AnyNestedContent>
		transpose_value(AnyContent&& content, AnyRank&& rank, AnyNestedContent&& nested_content) : super_type(std::forward<AnyContent> (content), std::forward<AnyRank> (rank), std::forward<AnyNestedContent> (nested_content)) {std::cout<<__LINE__<<"  "<< typeid(nested_content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) = 0;
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) = 0;
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) = 0;
	};
#endif

	//////////////////////////////
	//////////////////////////////////////////
	


	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class apply_value : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
		Function _function;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : _content(std::forward<AnyContent> (content)), _function(std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : _content(std::forward<AnyContent> (content)), _function(std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new apply_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<apply_value*>(this)->_content, const_cast<apply_value*>(this)->_function); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual typename std::add_const<value_type>::type value() const { return _function(key(), _content.value()); }
		virtual typename std::add_const<key_type>::type key() const { return _content.key(); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void flush() { _content.flush(); }
		virtual bool eof() const { return _content.eof(); }
		virtual const void* where() const { return _content.where(); }
		virtual size_t forward(size_t count = 1) { return _content.forward(count); }
		virtual bool seek(typename std::decay<key_type>::type const& key) { return _content.seek(key); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::collection_type, collection_type>(_content.collection(), _function); }
		virtual size_t backward(size_t count = 1) { return _content.backward(count); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	protected:
		ReverseFunction _reverse_function;

	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)), _reverse_function(std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new apply_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<apply_value*>(this)->_content, const_cast<apply_value*>(this)->_function, const_cast<apply_value*>(this)->_reverse_function); }
		virtual collection_type* __clone_collection() const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::collection_type, collection_type>(_content.collection(), _function, _reverse_function); }
		virtual void set(typename std::decay<value_type>::type const&  value) { _content.set(_reverse_function(key(), value)); }
		virtual void set(typename std::decay<value_type>::type&& value) { _content.set(_reverse_function(key(), value)); }
		virtual void erase() { _content.erase(); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin(), _function); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.find(key), _function); }
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { return _function(key, _content.value(key)); }
	};

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap::super_type> super_type;
	protected:
		ReverseFunction _reverse_function;

	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)), _reverse_function(std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new apply_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<apply_value*>(this)->_content, const_cast<apply_value*>(this)->_function, const_cast<apply_value*>(this)->_reverse_function); }
		virtual iterator_type* __clone_iterator() const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin(), _function, _reverse_function); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new apply_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.find(key), _function, _reverse_function); }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content.set(key, _reverse_function(key, value)); }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content.set(key, _reverse_function(key, value)); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content.set(key, _reverse_function(key, value)); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content.set(key, _reverse_function(key, value)); }
		virtual void erase(typename std::decay<key_type>::type const& key) { _content.erase(key); }
	};

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename apply_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist::super_type> super_type;
	public:
		apply_value() {}
		template <typename AnyContent, typename AnyFunction>
		apply_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		apply_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content.insert(key, _reverse_function(key, value)); }
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content.insert(key, _reverse_function(key, value)); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content.insert(key, _reverse_function(key,value)); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content.insert(key, _reverse_function(key, value)); }
	};

	

	//////////////////////////////
	//////////////////////////////////////////
	


	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class filter_value : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
		Function _function;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : _content(std::forward<AnyContent> (content)), _function(std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : _content(std::forward<AnyContent> (content)), _function(std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new filter_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<filter_value*>(this)->_content, const_cast<filter_value*>(this)->_function); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual typename std::add_const<value_type>::type value() const { return _content.value(); }
		virtual typename std::add_const<key_type>::type key() const { return _content.key(); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void flush() { _content.flush(); }
		virtual bool eof() const { return _content.eof(); }
		virtual const void* where() const { return _content.where(); }
		virtual size_t forward(size_t count = 1) { 
			size_t jump = count;
			while (count != 0) {
				if (!_content.forward(1)) {
					break;
				}
				if (_function(key(), value()) == true) {
					--count;
				}
			}
			return jump - count;
		}
		virtual bool seek(typename std::decay<key_type>::type const& key) {
			if (_content.seek(key)) {
				if (_function(key(), value()) == true) {
					return true;
				} else {
					_content.flush();
				}
			} 
			return false; 
		}
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	protected:
		ReverseFunction _reverse_function;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)), _reverse_function(std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new filter_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<filter_value*>(this)->_content, const_cast<filter_value*>(this)->_function, const_cast<filter_value*>(this)->_reverse_function); }
		virtual collection_type* __clone_collection() const { return new filter_value<Function, ReverseFunction, typename __HiddenInterface::collection_type, collection_type>(_content.collection(), _function, _reverse_function); }
		virtual size_t backward(size_t count = 1) { 
			size_t jump = count;
			while (count != 0) {
				if (!_content.backward(1)) {
					break;
				}
				if (_reverse_function(key(), value()) == true) {
					--count;
				}
			}
			return jump - count;
		}
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _content.set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _content.set(value); }
		virtual void erase() { _content.erase(); }
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const {
			return new filter_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin() FIXME: shall start to a valid iterator !, _function); 
		}
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto it = _content.find(key);
			if (_function(it.key(), it.value()) != true) {
				it.flush();
			}  
			return new filter_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(it, _function); 
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto it = std::shared_ptr<iterator_type> (__find_iterator(key));
			return it.value();
		}
	};

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Imap::super_type> super_type;
	protected:
		ReverseFunction _reverse_function;

	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)), _reverse_function(std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new filter_value<Function, ReverseFunction, __HiddenInterface, __Interface>(const_cast<filter_value*>(this)->_content, const_cast<filter_value*>(this)->_function, const_cast<filter_value*>(this)->_reverse_function); }
		virtual iterator_type* __clone_iterator() const { 
			return new filter_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin() FIXME: shall start to a valid iterator !, _function, _reverse_function); 
		}
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new filter_value<Function, ReverseFunction, typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.find(key), _function, _reverse_function); }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { if (_function(key, value) == true) { _content.set(key, value); } }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { if (_function(key, value) == true) { _content.set(key, value); } }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { if (_function(key, value) == true) { _content.set(key, value); } }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { if (_function(key, value) == true) { _content.set(key, value); } }
		virtual void erase(typename std::decay<key_type>::type const& key) { _content.erase(key); }
	};

	template<typename Function, typename ReverseFunction, typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename filter_value<Function, ReverseFunction, __HiddenInterface, __Interface, typename Ilist::super_type> super_type;
	public:
		filter_value() {}
		template <typename AnyContent, typename AnyFunction>
		filter_value(AnyContent&& content, AnyFunction&& function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyFunction, typename AnyReverseFunction>
		filter_value(AnyContent&& content, AnyFunction&& function, AnyReverseFunction&& reverse_function) : super_type(std::forward<AnyContent> (content), std::forward<AnyFunction> (function), std::forward<AnyReverseFunction> (reverse_function)) {std::cout<<__LINE__<<"  "<< typeid(function).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { if (_function(key, value) == true) { _content.insert(key, value); } }
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { if (_function(key, value) == true) { _content.insert(key, value); } }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { if (_function(key, value) == true) { _content.insert(key, value); } }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { if (_function(key, value) == true) { _content.insert(key, value); } }
	};

	

	//////////////////////////////////////////
	//////////////////////////////////////////
	
	


	template<typename __HiddenInterface, typename __Interface, typename __Inheritance = __Interface>
	class swap_value : public swap_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename __Inheritance::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename __HiddenInterface, typename __Interface>
	class swap_value<__HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef __Interface super_type;
	public:
		bridge<__HiddenInterface> _content;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual __Interface* __clone() const { return new swap_value<__HiddenInterface, __Interface>(const_cast<swap_value*>(this)->_content); }
		virtual bool good() const { return _content.good(); }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Ielement::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual typename std::add_const<value_type>::type value() const { return _content.key(); }
		virtual typename std::add_const<key_type>::type key() const { return _content.value(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void flush() { _content.flush(); }
		virtual bool eof() const { return _content.eof(); }
		virtual const void* where() const { return _content.where(); }
		virtual size_t forward(size_t count = 1) { return _content.forward(count); }
		virtual bool seek(typename std::decay<key_type>::type const& key) { 
			while (!_content.eof()) {
				if (_content.value() == key) {
					return true;
				}
				_content.forward();
			}
			return false;
		}
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual collection_type* __clone_collection() const { return new swap_value<typename __HiddenInterface::collection_type, collection_type>(_content.collection()); }
		virtual size_t backward(size_t count = 1) { return _content.backward(count); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<value_type>::type const&  value) = 0;
		virtual void set(typename std::decay<value_type>::type&& value) = 0;
		virtual void erase() { _content.erase(); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual iterator_type* __clone_iterator() const { return new swap_value<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(_content.begin()); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { 
			auto iterator = _content.begin();
			while (!iterator.eof() && iterator.value() != key) {
				iterator.forward();
			}
			return new swap_value<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type>(iterator); 
		}
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { 
			auto iterator = _content.begin();
			while (!iterator.eof() && iterator.value() != key) {
				iterator.forward();
			}
			return iterator.key();
		}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content.set(value, key); }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content.set(value, key); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content.set(value, key); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content.set(value, key); }
		virtual void erase(typename std::decay<key_type>::type const& key) = 0;
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class swap_value<__HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public swap_value<__HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename swap_value<__HiddenInterface, __Interface, typename Ilist::super_type> super_type;
	public:
		swap_value() {}
		template <typename AnyContent>
		swap_value(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}

	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content.insert(value, key); }
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content.insert(value, key); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content.insert(value, key); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content.insert(value, key); }
	};

	
	//////////////////////////////////////////
	//////////////////////////////////////////
	
	template<typename Content, typename __Interface = Iunknown, typename __Inheritance = __Interface>
	class prime_content : public prime_content<Content, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface, typename __Inheritance::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename Content, typename __Interface>
	class prime_content<Content, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface super_type;
	protected:
		Content _content;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new prime_content<Content, __Interface> (const_cast<prime_content*>(this)->_content); }
		virtual bool good() const { return true; }
	public:
		static typename std::add_const<value_type>::type convert(const __Interface& interface) { return interface.value(); }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Ielement<KeyOrValue>> : public prime_content<Content, __Interface, typename Ielement<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface, typename Ielement::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual typename std::add_const<value_type>::type value() const { return _content; }
		virtual typename std::add_const<key_type>::type key() const { return 0; }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Icontent<KeyOrValue>> : public prime_content<Content, __Interface, typename Icontent<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface, typename Icontent::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _content = value; }
		virtual void set(typename std::decay<value_type>::type&& value) { _content = value; }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Iflow<KeyOrValue>> : public prime_content<Content, __Interface, typename Iflow<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface, typename Iflow::super_type> super_type;
	protected:
		bool _eof;
	public:
		prime_content() : _eof(false) {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)), _eof(false) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new prime_content<Content, __Interface> (const_cast<prime_content*>(this)->_content, _eof); }
		virtual void flush() { _eof = true; }
		virtual bool eof() const { return _eof; }
		virtual size_t forward(size_t count = 1) { if (!_eof && count) { _eof = true; return 1; } else { return 0; } }
		virtual const void* where() const { return !_eof ? &_content : NULL; }
		virtual bool seek(typename std::decay<key_type>::type const& key) { return !_eof && key == 0; }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Iiterator<KeyOrValue>> : public prime_content<Content, __Interface, typename Iiterator<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename prime_content<Content, __Interface, typename Iiterator::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content), eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual collection_type* __clone_collection() const { return new prime_content<Content, collection_type> (_content); }
		virtual size_t backward(size_t count = 1) { if (_eof && count) { _eof = false; return 1; } else { return 0; } }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Iquery<KeyOrValue>> : public prime_content<Content, __Interface, typename Iquery<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename prime_content<Content, __Interface, typename Iquery::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual iterator_type* __clone_iterator() const { return new lazy5::prime_content<Content, __Interface::iterator_type>(_content); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new lazy5::prime_content<Content, __Interface::iterator_type>(_content, key == 0); }
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { if (key != 0) { throw std::out_of_range("key != 0"); } else { return _content; } }
	};
	
	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_content<Content, __Interface, Icollection<KeyOrValue>> : public prime_content<Content, __Interface, typename Icollection<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface, typename Icollection::super_type> super_type;
	public:
		prime_content() {}
		template <typename AnyContent>
		prime_content(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent>
		prime_content(AnyContent&& content, bool eof) : super_type(std::forward<AnyContent> (content)), _eof(eof) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	////////////////////////////////////////
	////////////////////////////////////////

	template<typename Content, typename __Interface = Iunknown>
	class prime : public prime_content<Content, __Interface> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_content<Content, __Interface> super_type;
	public:
		prime() {}
		template <typename AnyContent>
		prime(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	template<typename Content, typename __Interface>
	class prime<const Content, __Interface> : public prime<Content, __Interface> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime<Content, __Interface> super_type;
	public:
		prime() {}
		template <typename AnyContent>
		prime(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
	
	
	////////////////////////////////////////
	////////////////////////////////////////

	template<typename Content, typename __Interface, typename __Inheritance = __Interface>
	class prime_std_vector : public prime_std_vector<Content, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename __Inheritance::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};


	template<typename Content, typename __Interface>
	class prime_std_vector<Content, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface super_type;
	protected:
		Content _content;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : _content(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new typename lazy5::prime_std_vector<Content, __Interface>(const_cast<prime_std_vector*>(this)->_content); }
		virtual bool good() const { return true; }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Ielement<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Ielement<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Ielement::super_type> super_type;
	public:
		typedef typename std::conditional<std::is_const<Content>::value, typename std::decay<Content>::type::const_iterator, typename std::decay<Content>::type::iterator>::type iterator_type;

	public:
		iterator_type _iterator;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)), _iterator(_content.begin() + std::distance(content.begin(), iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual typename std::add_const<value_type>::type value() const { return *_iterator; }
		virtual typename std::add_const<key_type>::type key() const { return distance(); }
		virtual __Interface* __clone() const { return new lazy5::prime_std_vector<Content, __Interface>(const_cast<prime_std_vector*>(this)->_content, const_cast<prime_std_vector*>(this)->_iterator); }
		virtual size_t distance() const { return std::distance(static_cast<const iterator_type&> (_content.begin()), _iterator); }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Icontent<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Icontent<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Icontent::super_type> super_type;
	public:
		typedef typename std::conditional<std::is_const<Content>::value, typename std::decay<Content>::type::const_iterator, typename std::decay<Content>::type::iterator>::type iterator_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)), _iterator(_content.begin() + std::distance(content.begin(), iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { *_iterator = value; }
		virtual void set(typename std::decay<value_type>::type&& value) { *_iterator = value; }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Iflow<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Iflow<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Iflow::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		static Content convert(const __Interface& interface) {  return Content(interface, (const __Interface&) bridge<__Interface>()); }
	public:
		virtual void flush() { _iterator = static_cast<const iterator_type&> (_content.end()); }
		virtual bool eof() const { return static_cast<const iterator_type&> (_content.end()) == _iterator; }
		virtual const void* where() const { return !eof() ? &*_iterator : NULL; }
		virtual size_t forward(size_t count = 1) { 
			size_t jump = std::min(count, static_cast<size_t> (std::distance(_iterator, static_cast<const iterator_type&> (_content.end()))));
			_iterator += jump; 
			return jump; 
		}
		virtual bool seek(typename std::decay<key_type>::type const& key) { return forward(key) == key; }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Iiterator<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Iiterator<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename prime_std_vector<Content, __Interface, typename Iiterator::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual collection_type* __clone_collection() const { return new prime_std_vector<Content, collection_type> (_content); }
		virtual size_t backward(size_t count = 1) { 
			size_t jump = std::min(count, static_cast<size_t> (std::distance(static_cast<const iterator_type&> (_content.begin()), _iterator)));
			_iterator -= jump; 
			return jump; 
		}
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Imap_iterator<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Imap_iterator<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Imap_iterator::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { *_iterator = value; }
		virtual void set(typename std::decay<value_type>::type&& value) { *_iterator = value; }
		virtual void erase() { _content.erase(_iterator); }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Ilist_iterator<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Ilist_iterator<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Ilist_iterator::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Iquery<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Iquery<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename prime_std_vector<Content, __Interface, typename Iquery::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual iterator_type* __clone_iterator() const { return new prime_std_vector<Content, typename __Interface::iterator_type> (_content); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new prime_std_vector<Content, typename __Interface::iterator_type> (_content, _content.begin() + key); }
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { return _content[key]; }
	public:
		static Content convert(const __Interface& interface) { return Content(bridge<iterator_type>(interface.__clone_iterator()), bridge<iterator_type>()); }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Imap<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Imap<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Imap::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content[key] = value; }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content[key] = value; }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content[key] = value; }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content[key] = value; }
		virtual void erase(typename std::decay<key_type>::type const& key) { _content.erase(_content.begin() + key); }
	};

	template<typename Content, typename __Interface, typename KeyOrValue>
	class prime_std_vector<Content, __Interface, Ilist<KeyOrValue>> : public prime_std_vector<Content, __Interface, typename Ilist<KeyOrValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename prime_std_vector<Content, __Interface, typename Ilist::super_type> super_type;

	public:
		prime_std_vector() {}
		template <typename AnyContent>
		prime_std_vector(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime_std_vector(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content.insert(_content.begin() + key, value); }
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content.insert(_content.begin() + key, value); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content.insert(_content.begin() + key, value); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content.insert(_content.begin() + key, value); }
	};

	template<typename AnyValue, typename AnyAlloc, typename __Interface>
	class prime<std::vector<AnyValue, AnyAlloc>, __Interface> : public prime_std_vector<std::vector<AnyValue, AnyAlloc>, __Interface> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef prime_std_vector<std::vector<AnyValue, AnyAlloc>, __Interface> super_type;
	public:
		prime() {}
		template <typename AnyContent>
		prime(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};

	template<typename AnyValue, typename AnyAlloc, typename __Interface>
	class prime<std::vector<AnyValue, AnyAlloc>&, __Interface> : public prime_std_vector<std::vector<AnyValue, AnyAlloc>&, __Interface> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef prime_std_vector<std::vector<AnyValue, AnyAlloc>&, __Interface> super_type;
	public:
		prime() {}
		template <typename AnyContent>
		prime(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};

	template<typename AnyValue, typename AnyAlloc, typename __Interface>
	class prime<const std::vector<AnyValue, AnyAlloc>&, __Interface> : public prime_std_vector<const std::vector<AnyValue, AnyAlloc>&, __Interface> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef prime_std_vector<const std::vector<AnyValue, AnyAlloc>&, __Interface> super_type;
	public:
		prime() {}
		template <typename AnyContent>
		prime(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent, typename AnyIterator>
		prime(AnyContent&& content, AnyIterator&& iterator) : super_type(std::forward<AnyContent> (content), std::forward<AnyIterator> (iterator)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	};

		


	//////////////////////////////


	template<typename __HiddenInterface, typename __Interface>
	class bridge<__HiddenInterface, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface super_type;

	protected:
		std::shared_ptr<__HiddenInterface> _content;

	public:
				template < bool Compatible>
	class xx {
	public:
		template<typename AnyContent>
		static std::shared_ptr<__HiddenInterface> zozo(AnyContent&& content) {
					std::cout<<__LINE__<<"  "<< "Content& iflow"<<std::endl; 
			__Interface* v = new prime<AnyContent, __HiddenInterface>(std::forward<AnyContent>(content));
			return std::shared_ptr<__HiddenInterface>(v);
		}
	};

		template <>
class xx< true> {
public:

	template<typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
				static std::shared_ptr<__HiddenInterface> zozo(const lazy5::bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& bridge) { 
					std::cout<<__LINE__<<"  "<< "flow<__Interface>& iflow"<<std::endl; 
				return std::shared_ptr<__HiddenInterface>(new lazy5::bridge<AnyHiddenInterface, __HiddenInterface> (bridge.content())); }
};

		
		
		template < bool Compatible>
	class tt {
	public:
		template<typename AnyContent>
		static std::shared_ptr<__HiddenInterface> zozo(AnyContent&& content) {
					std::cout<<__LINE__<<"  "<< "Content& iflow"<<std::endl; 
			__Interface* v = new prime<AnyContent, __HiddenInterface>(std::forward<AnyContent>(content));
			return std::shared_ptr<__HiddenInterface>(v);
		}
	};

		template <>
class tt< true> {
public:

	template<typename AnyHiddenInterface, typename AnyInterface, typename AnyInheritance>
				static std::shared_ptr<__HiddenInterface> zozo(const lazy5::bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>& bridge) { 
					std::cout<<__LINE__<<"  "<< "flow<__Interface>& iflow"<<std::endl; 
				return xx<lazy5::bridge<AnyHiddenInterface, AnyInterface, AnyInheritance>::has_all_methods_of<__HiddenInterface>::value>::zozo (bridge); }

	template<typename AnyInterface, typename AnyInheritance>
				static std::shared_ptr<__HiddenInterface> zozo(const lazy5::bridge<__HiddenInterface, AnyInterface, AnyInheritance>& bridge) { std::cout<<__LINE__<<"  "<< "flow<__Interface>& iflow"<<std::endl; 
				return bridge._content; }
				static std::shared_ptr<__HiddenInterface> zozo(const __HiddenInterface& interface) { std::cout<<__LINE__<<"  "<< "flow<__Interface>& iflow"<<std::endl; return std::shared_ptr<__HiddenInterface>(interface.__clone()); }
				static std::shared_ptr<__HiddenInterface> zozo(const __HiddenInterface* interface) { std::cout<<__LINE__<<"  "<< "flow<__Interface>& iflow"<<std::endl; return std::shared_ptr<__HiddenInterface>(interface ? interface->__clone() : NULL); }


};


	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : _content(tt<std::is_base_of<Igeneric, typename std::decay<std::remove_pointer<AnyContent>::type>::type>::value>::zozo(std::forward<AnyContent>(content))) { /*std::cout<<"+++"<<std::endl;*/	}
		bridge(__HiddenInterface* iflow) : _content(iflow) {std::cout<<__LINE__<<"  "<< "Iflow* iflow"<<std::endl;	}
		bridge(const __HiddenInterface* iflow) : _content(const_cast<__HiddenInterface*> (iflow)) {std::cout<<__LINE__<<"  "<< "const Iflow* iflow"<<std::endl;	}
		bridge(std::shared_ptr<__HiddenInterface>& iflow) : _content(iflow) {std::cout<<__LINE__<<"  "<< "std::shared_ptr<Iflow>& iflow"<<std::endl;	}
		bridge(const std::shared_ptr<__HiddenInterface>& iflow) : _content(iflow) {std::cout<<__LINE__<<"  "<< "const std::shared_ptr<Iflow>& iflow"<<std::endl;	}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : _content(std::forward<AnyContent0>(content0)) { /*std::cout<<"+++"<<std::endl;*/	}
	protected:
		virtual __Interface* __clone() const { return new bridge<__HiddenInterface, __Interface> (_content); }
	public:
		virtual bool good() const { return _content && _content->good(); }
	public:
		std::shared_ptr<__HiddenInterface>& content() { return _content; }
		const std::shared_ptr<__HiddenInterface>& content() const { return _content; }
		bridge<__Interface> clone() const { return __clone(); }
		template <typename AnyValue>
		operator AnyValue () const { return prime<AnyValue, __Interface>::convert(*this); }
	};



	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Itemplate_generic<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Itemplate_generic<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Itemplate_generic::super_type> super_type;
	
	protected:
		template <typename Output, typename InputKey, typename InputValue, bool KeyInheritance = std::is_base_of<typename std::decay<InputKey>::type, typename std::decay<key_type>::type>::value>
		struct caller_on_key {
			typedef std::function<Output (InputKey, InputValue)> type;
		};

		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_key<Output, InputKey&, InputValue, true> {
			typedef caller_on_key type;
			std::function<Output (InputKey&, InputValue)> _function;
			caller_on_key() {}
			template<typename AnyFunction>
			caller_on_key(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyValue>
			Output operator() (typename std::decay<key_type>::type const& key, AnyValue&& value) const { typename std::decay<InputKey>::type lkey = key; return _function( std::move(lkey), std::forward<AnyValue> (value)); }
			template <typename AnyValue>
			Output operator() (typename std::decay<key_type>::type&& key, AnyValue&& value) const { return _function( (key), std::forward<AnyValue> (value)); }
		};

		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_key<Output, InputKey&&, InputValue, true> {
			typedef caller_on_key type;
			std::function<Output (InputKey&&, InputValue)> _function;
			caller_on_key() {}
			template<typename AnyFunction>
			caller_on_key(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyValue>
			Output operator() (typename std::decay<key_type>::type const& key, AnyValue&& value) const { typename std::decay<InputKey>::type lkey = key; return _function( std::move(lkey), std::forward<AnyValue> (value)); }
			template <typename AnyValue>
			Output operator() (typename std::decay<key_type>::type&& key, AnyValue&& value) const { return _function( (key), std::forward<AnyValue> (value)); }
		};

		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_key<Output, InputKey, InputValue, false> {
			typedef caller_on_key type;
			std::function<Output (InputKey, InputValue)> _function;
			caller_on_key() {}
			template<typename AnyFunction>
			caller_on_key(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyKey, typename AnyValue>
			Output operator() (AnyKey&& key, AnyValue&& value) const { typename std::decay<InputKey>::type lkey = key; return _function( std::forward<InputKey> (lkey), std::forward<AnyValue> (value)); }
		};

		template <typename Output, typename InputKey, typename InputValue, bool ValueInheritance = std::is_base_of<typename std::decay<InputValue>::type, typename std::decay<value_type>::type>::value>
		struct caller_on_value {
			typedef typename caller_on_key<Output, InputKey, InputValue>::type type;
		};

		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_value<Output, InputKey, InputValue&, true> {
			typedef caller_on_value type;
			typename caller_on_key<Output, InputKey, InputValue&>::type _function;
			caller_on_value() {}
			template<typename AnyFunction>
			caller_on_value(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyKey>
			Output operator() (AnyKey&& key, typename std::decay<value_type>::type const& value) const { typename std::decay<InputValue>::type lvalue = value; return _function(std::forward<AnyKey> (key), std::move(lvalue)); }
			template <typename AnyKey>
			Output operator() (AnyKey&& key, typename std::decay<value_type>::type&& value) const { return _function(std::forward<AnyKey> (key), (value)); }
		};


		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_value<Output, InputKey, InputValue&&, true> {
			typedef caller_on_value type;
			typename caller_on_key<Output, InputKey, InputValue&&>::type _function;
			caller_on_value() {}
			template<typename AnyFunction>
			caller_on_value(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyKey>
			Output operator() (AnyKey&& key, typename std::decay<value_type>::type const& value) const { typename std::decay<InputValue>::type lvalue = value; return _function(std::forward<AnyKey> (key), std::move(lvalue)); }
			template <typename AnyKey>
			Output operator() (AnyKey&& key, typename std::decay<value_type>::type&& value) const { return _function(std::forward<AnyKey> (key), (value)); }
		};

		template <typename Output, typename InputKey, typename InputValue>
		struct caller_on_value<Output, InputKey, InputValue, false> {
			typedef caller_on_value type;
			typename caller_on_key<Output, InputKey, InputValue>::type _function;
			caller_on_value() {}
			template<typename AnyFunction>
			caller_on_value(AnyFunction&& function) : _function(std::forward<AnyFunction> (function)) {}
			template <typename AnyKey, typename AnyValue>
			Output operator() (AnyKey&& key, AnyValue&& value) const { typename std::decay<InputValue>::type lvalue = value; return _function(std::forward<AnyKey> (key), std::forward<InputValue> (lvalue)); }
		};


	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		bridge<typename __Interface::template change<value_type, key_type>::downgraded_type> swap() const { return new swap_value<__Interface, typename __Interface::template change<value_type, key_type>::downgraded_type>(*this); }

		template <typename AnyOutput, typename AnyInputValue>
		bridge<typename __Interface::template change<key_type, AnyOutput>::downgraded_type> apply(const std::function<AnyOutput (AnyInputValue)>& function) const { 
			return new apply_value<
				caller_on_value<AnyOutput, typename std::decay<key_type>::type const&, AnyInputValue>::type,
				std::_Nil,
				__Interface, 
				typename __Interface::template change<key_type, AnyOutput>::downgraded_type>
				(
					*this, 
					[function] (typename std::decay<key_type>::type const&, AnyInputValue&& value) -> AnyOutput { return function(std::forward<AnyInputValue> (value)); }
				); 
		}

		// FIXME : rename apply2 en autre chose...
		template <typename AnyOutput, typename AnyInputKey, typename AnyInputValue>
		bridge<typename __Interface::template change<key_type, AnyOutput>::downgraded_type> apply_on_two(const std::function<AnyOutput (AnyInputKey, AnyInputValue)>& function) const { 
			return new apply_value<
				caller_on_value<AnyOutput, AnyInputKey, AnyInputValue>::type,
				std::_Nil,
				__Interface, 
				typename __Interface::template change<key_type, AnyOutput>::downgraded_type>
				(
					*this, 
					[function] (AnyInputKey&& key, AnyInputValue&& value) -> AnyOutput { return function(std::forward<AnyInputKey> (key), std::forward<AnyInputValue> (value)); }
				); 
		}

		// FIXME : rename apply2 en autre chose...
		template <typename AnyOutput0, typename AnyInputValue0, typename AnyOutput1, typename AnyInputValue1>
		bridge<typename __Interface::template change<key_type, AnyOutput0>::type> apply2(const std::function<AnyOutput0 (AnyInputValue0)>& function, const std::function<AnyOutput1 (AnyInputValue1)>& reverse_function) const { 
			return new apply_value<
				caller_on_value<AnyOutput0, typename std::decay<key_type>::type const&, AnyInputValue0>::type,
				caller_on_value<AnyOutput1, typename std::decay<key_type>::type const&, AnyInputValue1>::type,
				__Interface, 
				typename __Interface::template change<key_type, AnyOutput0>::type>
				(
					*this,
					[function] (typename std::decay<key_type>::type const&, AnyInputValue0&& value) -> AnyOutput0 { return function(std::forward<AnyInputValue0> (value)); },
					[reverse_function] (typename std::decay<key_type>::type const&, AnyInputValue1&& value) -> AnyOutput1 { return reverse_function(std::forward<AnyInputValue1> (value)); }
				); 
		}

		// FIXME : rename apply2 en autre chose...
		template <typename AnyOutput0, typename AnyInputKey0, typename AnyInputValue0, typename AnyOutput1, typename AnyInputKey1, typename AnyInputValue1>
		bridge<typename __Interface::template change<key_type, AnyOutput0>::type> apply2_on_two(const std::function<AnyOutput0 (AnyInputKey0, AnyInputValue0)>& function, const std::function<AnyOutput1 (AnyInputKey1, AnyInputValue1)>& reverse_function) const { 
			return new apply_value<
				caller_on_value<AnyOutput0, AnyInputKey0, AnyInputValue0>::type,
				caller_on_value<AnyOutput1, AnyInputKey1, AnyInputValue1>::type,
				__Interface, 
				typename __Interface::template change<key_type, AnyOutput0>::type>
				(
					*this,
					[function] (AnyInputKey0&& key, AnyInputValue0&& value) -> AnyOutput0 { return function(std::forward<AnyInputKey0> (key), std::forward<AnyInputValue0> (value)); },
					[reverse_function] (AnyInputKey1&& key, AnyInputValue1&& value) -> AnyOutput1 { return reverse_function(std::forward<AnyInputKey1> (key), std::forward<AnyInputValue1> (value)); }
				); 
		}


	};
	
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Ielement<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Ielement<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Ielement::super_type> super_type;

	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		value_type flatten() const { return value(); }
		value_type isolate(size_t rank) const { return rank == 0 ? value_type() : value(); }

	public:
		virtual typename std::add_const<value_type>::type value() const { return _content->value(); }
		virtual typename std::add_const<key_type>::type key() const { return _content->key(); }
	};
	
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Icontent<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Icontent<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Icontent::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _content->set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _content->set(value); }
	};
	
	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Ireference<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Ireference<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Ireference::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		template <typename AnyValue>
		bridge& operator=(AnyValue&& value) { this->set(std::forward<AnyValue>(value)); return *this; }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Iflow<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Iflow::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		value_type flatten() const { return new flatten_value<__Interface, typename value_type::type /* we use type to take the interface! */>(*this); }
		value_type isolate(size_t rank) const { return new isolate_value<__Interface, typename value_type::type /* we use type to take the interface! */>(*this, rank); }


	public:
		bridge operator+ (size_t count) const { bridge copy = this->copy(); copy.forward(count); return copy; }
		bridge& operator++ () { this->forward(); return *this; }
		bridge operator++ (int) { bridge copy = this->copy(); this->forward(); return copy; }
		bool operator== (const Iflow<KeyOrValue, OptionalValue>& flow) const { return this->where() == flow.where(); }
		bool operator!= (const Iflow<KeyOrValue, OptionalValue>& flow) const { return this->where() != flow.where(); }
		typename std::add_const<value_type>::type operator* () const { return value(); }
		bridge& operator<< (const lazy5::bridge<__HiddenInterface>& any_flow) { return (*this = new concatenator<__HiddenInterface>(*this, any_flow)); }
	public:
		virtual void flush() { if (_content) { _content->flush(); } }
		virtual bool eof() const { return !_content || _content->eof(); }
		virtual const void* where() const { return _content ? _content->where() : NULL; }
		virtual size_t forward(size_t count = 1) { return _content ? _content->forward(count) : 0; }
		virtual bool seek(typename std::decay<key_type>::type const& key) { return _content ? _content->seek(key) : false; }
	};
	

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Iiterator<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Iiterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::collection_type collection_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Iiterator::super_type> super_type;
	protected:
		template <bool Compatible>
		struct ff {
			static typename value_type flatten(const bridge& b) { return new flatten_value<__Interface, typename value_type::type>(b); }
			static typename value_type isolate(const bridge& b, size_t rank) { return new isolate_value<__Interface, typename value_type::type>(b, rank); }
			//static typename bridge<typename __Interface::change<key_type, typename value_type::value_type>::type> isolate(const bridge& b, size_t rank) { return new isolate_value<typename __Interface::change<key_type, typename value_type::value_type>::type, typename value_type::type>(b, rank); }
		};
		template <>
		struct ff<false> {
			static typename value_type flatten(const bridge& b) { return new flatten_value<typename __Interface::collection_type, typename value_type::type>(b.collection()); }
			static typename value_type isolate(const bridge& b, size_t rank) { return new isolate_value<typename __Interface::collection_type, typename value_type::type>(b.collection(), rank); }
		};
	public:
		value_type flatten() const { return ff<std::is_base_of<lazy5::Ielement<typename value_type::key_type, typename value_type::value_type>, value_type>::value>::flatten(*this); }

		value_type isolate(size_t rank) const { return ff<std::is_base_of<lazy5::Ielement<typename value_type::key_type, typename value_type::value_type>, value_type>::value>::isolate(*this, rank); }

	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		virtual bridge<collection_type> collection() const { return __clone_collection(); }
	protected:
		virtual collection_type* __clone_collection() const { return new bridge<typename __HiddenInterface::collection_type, collection_type> (_content ? _content->__clone_collection() : NULL); }
	public:
		virtual size_t backward(size_t count = 1) { return _content ? _content->backward(count) : 0; }
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Imap_iterator<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Imap_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Imap_iterator::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		virtual void set(typename std::decay<value_type>::type const&  value) { _content->set(value); }
		virtual void set(typename std::decay<value_type>::type&& value) { _content->set(value); }
		virtual void erase() { _content->erase(); }
	public:
		typename std::add_const<value_type>::type operator* () const { return value(); }
		typename bridge<Ireference<value_type>> operator* () { return *this; }
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Ilist_iterator<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Ilist_iterator<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Ilist_iterator::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Iquery<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Iquery<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename __Interface::iterator_type iterator_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Iquery::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		bridge<typename __Interface::iterator_type> begin() const { return __clone_iterator(); }
		bridge<typename __Interface::iterator_type> end() const { bridge<typename __Interface::iterator_type> iterator = begin(); iterator.flush(); return iterator; }
		bridge<typename __Interface::iterator_type> find(typename std::decay<key_type>::type const& key) const { return __find_iterator(key); }
	protected:
		template <bool Compatible>
		struct ff {
			static typename value_type flatten(const bridge& b) { return new flatten_value<typename __Interface::iterator_type, typename value_type::type>(b.begin()); }
			static typename value_type isolate(const bridge& b, size_t rank) { return new isolate_value<typename __Interface::iterator_type, typename value_type::type>(b.begin(), rank); }
		};
		template <>
		struct ff<false> {
			static typename value_type flatten(const bridge& b) { return new flatten_value<__Interface, typename value_type::type>(b); }
			static typename value_type isolate(const bridge& b, size_t rank) { return new isolate_value<__Interface, typename value_type::type>(b, rank); }
		};
	public:
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { return _content->value(key); }
		
	public:
		value_type flatten() const { return ff<std::is_base_of<Ielement<typename value_type::key_type, typename value_type::value_type>, value_type>::value>::flatten(*this); }

		value_type isolate(size_t rank) const {	return ff<std::is_base_of<Ielement<typename value_type::key_type, typename value_type::value_type>, value_type>::value>::isolate(*this, rank); }

	protected:
		virtual iterator_type* __clone_iterator() const { return new bridge<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type> (_content ? _content->__clone_iterator() : NULL); }
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const { return new bridge<typename __HiddenInterface::iterator_type, typename __Interface::iterator_type> (_content ? _content->__find_iterator(key) : NULL); }
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Icollection<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Icollection<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Icollection::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Imap<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Imap<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Imap::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content->set(key, value); }
		virtual void set(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content->set(key, value); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content->set(key, value); }
		virtual void set(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content->set(key, value); }
		virtual void erase(typename std::decay<key_type>::type const& key) { if (_content) { _content->erase(key); } }
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Ilist<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Ilist<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Ilist::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	public:
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type const&  value) { _content->insert(key, value); }
		virtual void insert(typename std::decay<key_type>::type const& key, typename std::decay<value_type>::type&& value) { _content->insert(key, value); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type const& value) { _content->insert(key, value); }
		virtual void insert(typename std::decay<key_type>::type&& key, typename std::decay<value_type>::type&& value) { _content->insert(key, value); }
	};

	template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bridge<__HiddenInterface, __Interface, Imatrix<KeyOrValue, OptionalValue>> : public bridge<__HiddenInterface, __Interface, typename Imatrix<KeyOrValue, OptionalValue>::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
		typedef typename bridge<__HiddenInterface, __Interface, typename Imatrix::super_type> super_type;
	public:
		bridge() {}
		template <typename AnyContent>
		bridge(AnyContent&& content) : super_type(std::forward<AnyContent> (content)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
		template <typename AnyContent0, typename AnyContent1>
		bridge(AnyContent0&& content0, AnyContent1&& content1) : super_type(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) { /*std::cout<<"+++"<<std::endl;*/	}
	};


	//////////////////////////////////////////
	///////////////////////////////////////////////

	class generic : public bridge<Igeneric> {
		friend class Iunknown;
	public:
		typedef Igeneric::key_type key_type;
		typedef Igeneric::value_type value_type;
	public:
		generic() { }
		template <typename AnyContent>
		generic(AnyContent&& content) : bridge(std::forward<AnyContent> (content)) {}
		template <typename AnyContent0, typename AnyContent1>
		generic(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};


	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class element : public bridge<Ielement<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Ielement::key_type key_type;
		typedef typename Ielement::value_type value_type;
	public:
		element() { }
		template <typename AnyContent>
		element(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		element(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class content : public bridge<Icontent<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Icontent::key_type key_type;
		typedef typename Icontent::value_type value_type;
	public:
		content() { }
		template <typename AnyContent>
		content(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		content(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class reference : public bridge<Ireference<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Ireference::key_type key_type;
		typedef typename Ireference::value_type value_type;
	public:
		reference() { }
		template <typename AnyContent>
		reference(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		reference(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	public:
		template <typename AnyValue>
		reference& operator=(AnyValue&& value) { this->set(std::forward<AnyValue>(value)); return *this; }
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class flow : public bridge<Iflow<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Iflow::key_type key_type;
		typedef typename Iflow::value_type value_type;
	public:
		flow() { }
		template <typename AnyContent>
		flow(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		flow(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class iterator : public bridge<Iiterator<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Iiterator::key_type key_type;
		typedef typename Iiterator::value_type value_type;
		typedef bridge super_type;
	public:
		iterator() { }
		template <typename AnyContent>
		iterator(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		iterator(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};


	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class map_iterator : public bridge<Imap_iterator<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Imap_iterator::key_type key_type;
		typedef typename Imap_iterator::value_type value_type;
		typedef bridge super_type;
	public:
		map_iterator() { }
		template <typename AnyContent>
		map_iterator(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		map_iterator(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class list_iterator : public bridge<Ilist_iterator<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Ilist_iterator::key_type key_type;
		typedef typename Ilist_iterator::value_type value_type;
		typedef bridge super_type;
	public:
		list_iterator() { }
		template <typename AnyContent>
		list_iterator(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		list_iterator(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};


	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class query : public bridge<Iquery<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Iquery::key_type key_type;
		typedef typename Iquery::value_type value_type;
	public:
		query() { }
		template <typename AnyContent>
		query(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		query(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};


	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class collection : public bridge<Icollection<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Icollection::key_type key_type;
		typedef typename Icollection::value_type value_type;
	public:
		collection() { }
		template <typename AnyContent>
		collection(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		collection(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class map : public bridge<Imap<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Imap::key_type key_type;
		typedef typename Imap::value_type value_type;
	public:
		map() { }
		template <typename AnyContent>
		map(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		map(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class list : public bridge<Ilist<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Ilist::key_type key_type;
		typedef typename Ilist::value_type value_type;
	public:
		list() { }
		template <typename AnyContent>
		list(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		list(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};

	template<typename KeyOrValue = std::_Nil, typename OptionalValue = std::_Nil>
	class matrix : public bridge<Imatrix<KeyOrValue, OptionalValue>> {
		friend class Iunknown;
	public:
		typedef typename Imatrix::key_type key_type;
		typedef typename Imatrix::value_type value_type;
	public:
		matrix() { }
		template <typename AnyContent>
		matrix(AnyContent&& content) : bridge (std::forward<AnyContent>(content)) { 	}
		template <typename AnyContent0, typename AnyContent1>
		matrix(AnyContent0&& content0, AnyContent1&& content1) : bridge(std::forward<AnyContent0>(content0), std::forward<AnyContent1>(content1)) {	}
	};



	//////////////////////////////////////////
	//////////////////////////////////////////
#if 0 //  TODO
	template<typename ValueContent, typename IndexContent, typename __Interface = Igeneric>
	class adjacent_list : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
	public:
		typedef typename prime<ValueContent>::type::attribute0_type input_value_type;
		typedef typename __Interface::attribute1_type output_value_type;
		typedef typename __Interface::attribute0_type input_index_type;
		typedef typename prime<IndexContent>::type::attribute1_type output_index_type;
		typedef typename __Interface::change<input_value_type, output_value_type> interface_value_type;
		typedef typename __Interface::change<input_index_type, output_index_type> interface_index_type;
	public:
		prime<ValueContent, interface_value_type> _value_content;
		prime<IndexContent, interface_index_type> _index_content;
	public:
		adjacent_list() {}
		template <typename AnyContent0, typename AnyContent1>
		adjacent_list(AnyContent0&& content0, AnyContent1&& content1) : _value_content(std::forward<AnyContent0> (content0)), _index_content(std::forward<AnyContent1> (content1)) {std::cout<<__LINE__<<"  "<< typeid(content).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new adjacent_list(const_cast<adjacent_list*>(this)->_value_content, const_cast<adjacent_list*>(this)->_index_content); }
	public:
					

		index_type get_begin_index(const I& objectID) {
			if (const Index* pt_begin_index = (*_index_storage).find(objectID)) {
				return (*pt_begin_index);
			} else {
				index_type begin_index = _value_content.size();
				// create all the missing elements
				for (size_t begin_objectID = (*_index_storage).all().size(); begin_objectID <= objectID; ++begin_objectID) {
					(*_index_storage).set(static_cast<I> (begin_objectID), begin_index);
				}
				return begin_index;
			}
		}
			
		index_type get_end_index(const I& objectID) {
			if (const Index* end_index = (*_index_storage).find(objectID + 1)) {
				return (*end_index);
			} else {
				return _value_vector.size();
			}
		}
	

	};
#endif		
		
	//////////////////////////////////////////
	//////////////////////////////////////////
	
	// FIXME : je ne suis pas sur que cela soit une bonne idéee de réduire le nbr de template
	template<typename KeyOrValue = std::_Nil>
	class Iset : public Icollection<KeyOrValue, KeyOrValue> {
	public:
		typedef Iset type;
		typedef Icollection super_type;
		typedef typename super_type::iterator_type iterator_type;
	public:
		template <typename AnyKey, typename AnyValue>
		struct change {
			typedef lazy5::Iset<AnyKey> type;
			typedef typename super_type::change<AnyKey, AnyValue>::downgraded_type downgraded_type;
		};

		template <typename AnyInterface>
		struct has_all_methods_of : super_type::has_all_methods_of<AnyInterface>{	
		};

		template <typename AnyKey>
		struct has_all_methods_of<Iset<AnyKey>> : std::integral_constant<bool, true> {
		};

	public:
		virtual type* __clone() const = 0;
		virtual iterator_type* __clone_iterator() const = 0;
		virtual iterator_type* __find_iterator(typename std::decay<key_type>::type const& key) const = 0;
		virtual typename std::add_const<value_type>::type set(typename std::decay<value_type>::type const&  value) = 0;
		virtual typename std::add_const<value_type>::type set(typename std::decay<value_type>::type&& value) = 0;
		virtual void erase(typename std::decay<value_type>::type const& value) = 0;
	};

	//TODO ...
	template<typename __HiddenInterface0, typename __HiddenInterface1, typename __Interface, typename __Inheritance = __Interface>
	class bounds : public bounds<__HiddenInterface0, __HiddenInterface1, __Interface, typename __Inheritance::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
	public:
		bounds() {}
		template <typename AnyContent0, typename AnyContent1>
		bounds(AnyContent0&& begin, AnyContent1&& end) : bounds<__HiddenInterface0, __HiddenInterface1, __Interface, typename __Inheritance::super_type>(std::forward<AnyContent0> (begin), std::forward<AnyContent1> (end)) {std::cout<<__LINE__<<"  "<< typeid(begin).name()<<"  "<< "AnyContent content"<<std::endl;}
	};
		
	template<typename __HiddenInterface0, typename __HiddenInterface1, typename __Interface>
	class bounds<__HiddenInterface0, __HiddenInterface1, __Interface, Igeneric> : public __Interface {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
	public:
		bridge<__HiddenInterface0, __Interface> _begin;
		bridge<__HiddenInterface1, __Interface> _end;
	public:
		bounds() {}
		template <typename AnyContent0, typename AnyContent1>
		bounds(AnyContent0&& begin, AnyContent1&& end) : _begin(std::forward<AnyContent0> (begin)), _end(std::forward<AnyContent1> (end)) {std::cout<<__LINE__<<"  "<< typeid(begin).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual __Interface* __clone() const { return new bounds(const_cast<bounds*>(this)->_begin, const_cast<bounds*>(this)->_end); }
	};
		
	template<typename __HiddenInterface0, typename __HiddenInterface1, typename __Interface, typename KeyOrValue, typename OptionalValue>
	class bounds<__HiddenInterface0, __HiddenInterface1, __Interface, Iquery<KeyOrValue, OptionalValue>> : public bounds<__HiddenInterface0, __HiddenInterface1, __Interface, typename Iquery::super_type> {
		friend class Iunknown;
	public:
		typedef typename __Interface::key_type key_type;
		typedef typename __Interface::value_type value_type;
	public:
		bounds() {}
		template <typename AnyContent0, typename AnyContent1>
		bounds(AnyContent0&& begin, AnyContent1&& end) : bounds<__HiddenInterface0, __HiddenInterface1, __Interface, typename Iquery::super_type>(std::forward<AnyContent0> (begin), std::forward<AnyContent1> (end)) {std::cout<<__LINE__<<"  "<< typeid(begin).name()<<"  "<< "AnyContent content"<<std::endl;}
	public:
		virtual typename std::add_const<value_type>::type value(typename std::decay<key_type>::type const& key) const { return (_begin + key).value(); }
	};
		

} // namespace lazy5

#if 0
template<typename __HiddenInterface, typename __Interface, typename KeyOrValue, typename OptionalValue>
bridge<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>> operator+( const bridge<__HiddenInterface, __Interface, Iflow<KeyOrValue, OptionalValue>>& lhs, const T& rhs )
{
  T nrv( lhs );
  nrv += rhs;
  return nrv;
}

T&& operator+( T&& lhs, const T& rhs )
{
  lhs += rhs;
  return lhs;
}

T&& operator+( const T& lhs, T&& rhs )
{
  rhs += lhs;
  return rhs;
}

T&& operator+( T&& lhs, T&& rhs )
{
  lhs += rhs;
  return lhs;
}


///////////////////
T   operator+( const T& lhs, const T& rhs )
{
  T nrv( lhs );
  nrv += rhs;
  return nrv;
}

T&& operator+( T&& lhs, const T& rhs )
{
  lhs += rhs;
  return lhs;
}

T&& operator+( const T& lhs, T&& rhs )
{
  rhs += lhs;
  return rhs;
}

T&& operator+( T&& lhs, T&& rhs )
{
  lhs += rhs;
  return lhs;
}
#endif
