//                                                                                                //
//  File: misc_collection.h                                                                            //
//  Creator: remye                                                                                //
//                                                                                                //
//  Copyright (C) 2006-2009 Abound Logic. All rights reserved                                     //
//                                                                                                //
//  These coded statements, instructions, and computer programs contain unpublished proprietary   //
//  informations and are protected by copyright law. They may not be disclosed to third parties   //
//  or copied or duplicated in any form without the written consent of Abound Logic.              //
//                                                                                                //

//header/*{{{*/

// include only once...
#pragma once



//#include "misc_collection_action.h"
//#include "misc_collection_iterator.h"
//#include <xut/xassert.h>
//#include <xut/xtree.h>
//#include <oa/oaCommon.h>
//#include <oa/oaBaseTypes.h>
#include <vector>
#include <set>
#include <list>
#include <map>


#define PURE = 0

#if 0

// external link to Open Access
BEGIN_OA_NAMESPACE
    template <class obj, class container>
    class OA_BASE_DLL_API oaCollection;
END_OA_NAMESPACE
#endif

//using namespace misc;

namespace misc {
/*}}}*/



//                                                                                                //
//  alCollection declaration                                                                        //
//                                                                                                //

//class alCollection<E>/*{{{*/
template<typename E>
class alCollection {

  public:
    //class Driver/*{{{*/
    class Driver {

      public:
    //!\name Destructor:
    //@{
    virtual                    ~Driver();
    //@}

      protected:
    //!\name Default Constructor:
    //@{
                         Driver();
    //@}

      public:
    //!\name alPredicates:
    
    virtual bool              is_random_access() const PURE;
    virtual bool              is_associative_access() const PURE;
    virtual bool              is_unique_access() const PURE;
    virtual bool              is_reversible_access() const PURE;
    virtual bool              is_mutable_access() const PURE;
    virtual bool              is_dynamic_access() const PURE;
    virtual bool              is_sized() const PURE;
    //@}

      public:
    //! standard O(n) functions
    //@{
#if 0
    alIterator<E>     eval_iterator(alIterator<E> iterator, size_t index) const;
    alIterator<E>     eval_reverse_iterator(size_t index) const;
    alIterator<E>     eval_find(const E& element) const;
    size_t            eval_count() const;
#endif
    //@}

      public:
    //!\name alAccessors:
    //@{
    virtual Driver*           create_clone() const PURE;
#if 0
    virtual alIterator<E>     get_iterator(size_t index) const PURE;
    virtual alIterator<E>     get_reverse_iterator(size_t index) const PURE;
    virtual alIterator<E>     find(const E& element) const PURE;
    virtual size_t            get_count() const PURE;
#endif
    //@}

      #ifndef DOXYGEN
      private:
                        Driver(const Driver& driver);
                        // not implemented to forbid copy

      private:
        Driver&                operator=(const Driver& driver);
                        // not implemented to forbid assignment
      #endif // DOXYGEN

    };
    /*}}}*/

    //type ElementType/*{{{*/
    typedef E                ElementType;
    /*}}}*/

  public:
    //!\name Destructor:
    //@{
                    ~alCollection();
    //@}

  public:
    //!\name Default Constructor:
    //@{
                    alCollection(Driver* driver = NULL);
    //@}

  public:
    //!\name Generalized Copy Constructor:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O>
                    alCollection(const alCollection<O>& objects);
    //@}

  public:
#if 0
    //!\name Generalized alIterator Based Constructor:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O>
                    alCollection(const alIterator<O>& alobjectIterator);
    //@}
#endif
	
  public:
    //!\name Generalized STL Based Constructors:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O>
                    alCollection(const std::list<O>& objectList);
        template<typename O, typename C>
                    alCollection(const std::set<O, C>& objectSet);
        // xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
//        template<typename K, typename O, typename A, typename C>
//                    alCollection(const xtree<K, O, A, C>& elementXtree);
        template<typename O>
                    alCollection(const std::vector<O>& objectVector);
        template<typename K, typename O, typename C>
                    alCollection(const std::map<K, O, C>& objectMap);
    //@}

  public:
    //!\name Generalized OpenAccess Based Constructor:
    //! elements of type 'O' inherits of type 'E'                
    //@{
#if 0
        template<typename O, typename C>
                    alCollection(const oa::oaCollection<O, C>& objectCollection);
#endif
	//@}

  public:
    //!\name Assignment Operators:
    //@{
        alCollection<E>&        operator=(Driver* driver);
        alCollection<E>&        operator=(const alCollection<E>& elements);
    //@}

  public:
    //!\name Random Access Operator:
    //! the complexity of the function relies on the containers hidden in the collection
    //! -e.g : size of vector is in O(1) but list, set, map is in O(n)
        E                operator[](size_t index) const;
    //@}

  public:
    //!\name Predicates:
    //@{
        bool            is_empty() const;
        bool            is_driven() const;
    //@}

  public:
    //!\name Predicate related to the traits of the collection
    //@{
        /*! return true if the following methods have a complexity lower than O(n) :
                - operator[]
                - at()
        */
        bool    is_random_access() const;
        /*! return true if the each elements of the collection is listed once
        */
        bool    is_unique_access() const;
        /*! return true if the following methods have a complexity lower than O(n) :
                - find()
        */
        bool    is_associative_access() const;
        /*! return true if the following methods have a complexity lower than O(n) (or its iterator) :
                - get_reverse_iterator(size_t index)
                - get_last()
                - create_reverse()
        */
        bool    is_reversible_access() const;
        /*! return true if the following methods have a complexity lower than O(n) :
                - insert()  // TODO : method to be implemented
        */
        bool    is_mutable_access() const;
        /*! return true if the collection supports dynamic changes in the referenced datas
        */
        bool    is_dynamic_access() const;
        /*! return true if the following methods have a complexity lower than O(n) :
                - get_count()
        */
        bool    is_sized() const;
    //@}

  public:
    //!\name Standard alAccessors:
    //@{
        Driver*            get_driver() const;
#if 0
        alIterator<E>      get_iterator(size_t index = 0) const;
        alIterator<E>      get_reverse_iterator(size_t index = 0) const;
	
        //! @return iterator on the first 'element' met in the collection. 
        //! @param element wanted element of the collection
        //! If the 'element' doesn't exist then iterator on the end of the collection.
        alIterator<E>      find(const E& element) const;
        //! @return the iterator ot the first occurrence that match the predicate in the collection
        //! If the 'element' doesn't exist then iterator on the end of the collection.
        //! @param predicate criteria to match
        template<typename D>
        alIterator<E>      find(const alPredicate<E, D>& predicate) const;
        bool               is_exist(const E& element) const;
        //! the complexity of the function relies on the containers hidden in the collection
        //! -e.g : size of vector, set, map is in O(1) but list is in O(n)
        size_t             get_count() const;
        //! @return true if the collection has 'size' elements
        //! the method is quicker than 'get_count() == size'
        bool               is_count_equal(size_t size) const;
        //! @return true if the collection has less than 'size' elements
        //! the method is quicker than 'get_count() < size'
        bool               is_count_less(size_t size) const;
        //! @return true if the collection has less or equal than 'size' elements
        //! the method is quicker than 'get_count() <= size'
        bool               is_count_less_or_equal(size_t size) const;
        //! @return true if the collection has greater than 'size' elements
        //! the method is quicker than 'get_count() > size'
        bool               is_count_greater(size_t size) const;
        //! @return true if the collection has greater or equal than 'size' elements
        //! the method is quicker than 'get_count() >= size'
        bool               is_count_greater_or_equal(size_t size) const;
        E                  get_first() const;
        E                  get_last() const;
        //! the complexity of the function relies on the containers hidden in the collection
        //! -e.g : size of vector is in O(1) but list, set, map is in O(n)
        E                  at(size_t index) const;
#endif
    //@}

  public:
#if 0
    //!\name Generalized Subset alAccessor:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O, typename D>
        alCollection<E>        create_with(const alPredicate<O, D>& predicate) const;
    //@}

  public:
    //!\name Generalized Associates alAccessor:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O, typename A, typename D>
        alCollection<A>        create_member_access(const alAccessor<O, A, D>& accessor) const;
    //@}

  public:
    //!\name Generalized alAction Invoker:
    //! elements of type 'O' inherits of type 'E'                
    //@{
        template<typename O, typename D>
        void            apply(const alAction<O, D>& action) const;
    //@}
#endif
	
  public:
    //!\name Generalized STL Container Fillers:
    //! elements of type 'O' inherits of type 'E'                
    //@{
#if 0
        template<typename O>
        std::list<O>&            save(std::list<O>& objectList) const;
        template<typename O, typename C>
        std::set<O, C>&            save(std::set<O, C>& objectSet) const;
        // xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
        template<typename K, typename O, typename A, typename C>
        xtree<K, O, A, C>&            save(xtree<K, O, A, C>& objectSet) const;
        template<typename O>
        std::vector<O>&            save(std::vector<O>& objectVector) const;
        template<typename O, typename K, typename C>
        std::map<K, O, C>&        save(std::map<K, O, C>&         objectMap,
                         const alAccessor<O, K>& keyAccessor) const;
#endif
	//@}

  #ifndef DOXYGEN
  private:
        Driver*            _driver;

  public:
#if 0
                    alCollection(const alCollection<E>& elements);
                    alCollection(const alIterator<E>& iterator);
    //Composition Functions/*{{{*/
    //@{
                    alCollection(const E& first);
                    alCollection(const E& first, const E& second);
                    alCollection(const E& first, const E& second, const E& third);
                    alCollection(const E& first, const E& second, const E& third, const E& fourth);
                    alCollection(const E& first, const E& second, const E& third, const E& fourth, const E& fifth);
                    //! @return  a collection from the current collection that contains [element, before[
                    template<typename D>
                    alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before, const alAccessor<E, E, D>&  get_previous_accessor);
                    template<typename D>
                    alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before = E());
    //@}
                    alCollection(const std::list<E>& elementList);
        template<typename C>
                    alCollection(const std::set<E, C>& elementSet);
        // xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
        template<typename K, typename A, typename C>
                    alCollection(const xtree<K, E, A, C>& elementXtree);
                    alCollection(const std::vector<E>& elementVector);
        //! insert data field of the map
        template<typename K, typename C>
                    alCollection(const std::map<K, E, C>& elementMap);
        //! insert key of the map
        template<typename D, typename C>
                    explicit alCollection(const std::map<E, D, C>& elementMap);

  public:   
        //! @return  a collection from the current collection that contains [0, count[ elements
        //! if 'count' is greater than the number of elements in the current collection it returns the entire collection
        //! if 'count' is equal to zero it returns an empty collection
        alCollection<E>        create_without_tail(size_t count = 1) const;
        //! @return  a collection from the current collection that contains [startIndex, size[ elements
        //! if 'startIndex' is equal to zero it returns the entire collection
        //! if 'startIndex' is greater than the number of elements in the current collection it returns an empty collection
        alCollection<E>        create_without_head(size_t startIndex = 1) const;
        //! @return  a collection from the current collection that contains [first, element]
        //! if the 'element' doesn't exist in the current collection it returns the entire collection
        alCollection<E>        create_to(const E& element) const;
        //! @return  a collection from the current collection that contains [element, last]
        //! if the 'element' doesn't exist in the current collection it returns the entire collection
        alCollection<E>        create_from(const E& element) const;
        //! @return  a collection from the current collection that contains [first, element[
        //! if the 'element' doesn't exist in the current collection it returns the entire collection
        alCollection<E>        create_before(const E& element) const;
        //! @return  a collection from the current collection that contains ]element, last]
        //! if the 'element' doesn't exist in the current collection it returns the entire collection
        alCollection<E>        create_after(const E& element) const;
        //! return a new collection without 'element'
        alCollection<E>        create_without(const E& element) const;
        //! only available if 'E' is a collection
        E                      create_flatten() const;
        //! reverse the order of the collection
        alCollection<E>        create_reverse() const;
        //! return a new collection with the current collection ending by the added collection
        alCollection<E>        create_concatenate(const alCollection<E>& tail) const;
        template<typename D>
        alCollection<E>        create_with(const alPredicate<E, D>& predicate) const;
        template<typename A, typename D>
        alCollection<A>        create_member_access(const alAccessor<E, A, D>& accessor) const;
        //! @return a collection with elements that associated members are equal to 'element'.
        template<typename A, typename D>
        alCollection<E>        create_with_member(const alAccessor<E, A, D>& accessor, const A& member) const;
        //! @return a collection with elements that associated members aren't equal to 'member'.
        template<typename A, typename D>
        alCollection<E>        create_without_member(const alAccessor<E, A, D>& accessor, const A& member) const;
        //! @return a collection with elements that associated members are unique, next duplicated members are ignored.
        template<typename A, typename D>
        alCollection<E>        create_unique_access(const alAccessor<E, A, D>& accessor) const;
        //! @return a collection with a random access.
        /*! if the current collection is already random access, the collection is unchanged.
            Elsewhere the returned collection has the following traits :
               - random access in O(1) . the first random access call costs O(n)
               - sized
               - reversible access
               - NO dynamic access
          */
        alCollection<E>        create_random_access() const;
        //! @return a collection with an associative access.
        /*! if the current collection is already associative access, the collection is unchanged.
            Elsewhere the returned collection has the following traits :
               - associative access lower than in O(n) . the first associative access call costs O(n)
               - NO dynamic access
          */
        alCollection<E>        create_associative_access() const;
        //! @return a collection with a unique access.
        //! guaranty the unicity of the elements, next duplicated elements are ignored.
        /*! if the current collection is already unique access, the collection is unchanged.
            Elsewhere the returned collection has the following traits :
               - unique access
          */
        alCollection<E>        create_unique_access() const;

  public:
        template<typename D>
        void            apply(const alAction<E, D>& action) const;

  public:
        bool operator ==(const alCollection<E>& collection) const;
        bool operator !=(const alCollection<E>& collection) const;

  public:
        std::list<E>&            save(std::list<E>& elementList) const;
        template<typename C>
        std::set<E, C>&            save(std::set<E, C>& elementSet) const;
        // xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
        template<typename K, typename A, typename C>
        xtree<K, E, A, C>&            save(xtree<K, E, A, C>& elementSet) const;
        std::vector<E>&            save(std::vector<E>& elementVector) const;
        template<typename K, typename C>
        std::map<K, E, C>&        save(std::map<K, E, C>&         elementMap,
                         const alAccessor<E, K>& keyAccessor) const;
  #endif // DOXYGEN
#endif
};
/*}}}*/
	
#if 0

	
	
//                                                                                                //
//  Crossing Controlers                                                                           //
//                                                                                                //

#ifndef DOXYGEN
//class alForEachControler<E>/*{{{*/
template<typename E>
class alForEachControler {

  private:
        E&            _current;
        alIterator<E>        _iterator;

  public:
                template<typename D>
                alForEachControler(E& current, const D& data);

  public:
        bool        is_alive();

  public:
    static  bool&        _continue();

};
/*}}}*/

//class alForEachConsecutiveControler<E>/*{{{*/
template<typename E>
class alForEachConsecutiveControler {

  private:
        E&            _current;
        E&            _next;
        alIterator<E>        _iterator;

  public:
                template<typename D>
                alForEachConsecutiveControler(E& current, E& next, const D& data);

  public:
        bool        is_alive();

  public:
    static  bool&        _continue();

};
/*}}}*/

//class alForEachParallelControler<E1, E2>/*{{{*/
template<typename E1, typename E2>
class alForEachParallelControler {

  private:
        E1&            _current1;
        alIterator<E1>    _iterator1;
        E2&            _current2;
        alIterator<E2>    _iterator2;

  public:
                template<typename D1, typename D2>
                alForEachParallelControler(E1& current1, const D1& data1,
                             E2& current2, const D2& data2);

  public:
        bool        is_alive();

  public:
    static  bool&        _continue();

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Macros                                                                                        //
//                                                                                                //

//Coding Macros/*{{{*/
#ifdef DOXYGEN
//!\name Coding Macros
//@{
#define COLLECTION(alCollectionType, ElementType)
//@}
#else
#define COLLECTION(Es, E)\
\
  private:\
    typedef alCollection<E>        Inherit;\
\
  public:\
                    Es() : Inherit() {}\
\
        template<typename Os>    Es(const Os& objects) : Inherit(objects) {}\
\
  public:\
        template<typename Os>\
        Es&                operator=(const Os& objects)\
                    {\
                        return (Es&)Inherit::operator=(objects);\
                    }
#endif // DOXYGEN
/*}}}*/

//Crossing Macros/*{{{*/
#ifdef DOXYGEN
//!\name Coding Macros
//@{
#define for_each(Type, current, data)
#define for_each_consecutive(Type, current, next, data)
#define for_each_parallel(Type1, current1, data1, Type2, current2, data2)
//@}
#else
#define for_each(Type, current, data)\
    if ((alForEachControler<Type>::_continue() = true))\
    for (Type current;\
         alForEachControler<Type>::_continue();\
         alForEachControler<Type>::_continue() = false)\
        for (alForEachControler<Type> controler(current, data);\
         controler.is_alive();\
        )

#define for_each_consecutive(Type, current, next, data)\
    if ((alForEachConsecutiveControler<Type>::_continue() = true))\
        for (Type current;\
             alForEachConsecutiveControler<Type>::_continue();\
             alForEachConsecutiveControler<Type>::_continue() = false)\
            for (Type next;\
             alForEachConsecutiveControler<Type>::_continue();\
             alForEachConsecutiveControler<Type>::_continue() = false)\
            for (alForEachConsecutiveControler<Type> controler(current, next, data);\
                 controler.is_alive();\
                )

#define for_each_parallel(Type1, current1, data1, Type2, current2, data2)\
    if ((alForEachParallelControler<Type1, Type2>::_continue() = true))\
        for (Type1 current1;\
             alForEachParallelControler<Type1, Type2>::_continue();\
             alForEachParallelControler<Type1, Type2>::_continue() = false)\
            for (Type2 current2;\
             alForEachParallelControler<Type1, Type2>::_continue();\
             alForEachParallelControler<Type1, Type2>::_continue() = false)\
            for (alForEachParallelControler<Type1, Type2> controler(current1, data1,\
                                          current2, data2);\
                 controler.is_alive();\
                )
#endif // DOXYGEN
/*}}}*/



//                                                                                                //
//  Specialized collections                                                                       //
//                                                                                                //

#ifndef DOXYGEN
//class alTypeCollection<O, E>/*{{{*/
template<typename O, typename E>
class alTypeCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<O>& objects);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<O>                _elements;

      public:
                            Driver(const alCollection<O>& objects);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alIteratorCollection<E>/*{{{*/
template<typename E>
class alIteratorCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alIterator<E>& iterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;

      public:
                            Driver(const alIterator<E>& iterator);
                            Driver(const Driver& driver);
      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alListCollection<E>/*{{{*/
template<typename E>
class alListCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const std::list<E>& elementList);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        const std::list<E>&                _element_list;

      public:
                            Driver(const std::list<E>& elementList);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alSetCollection<E, C>/*{{{*/
template<typename E, typename C>
class alSetCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const std::set<E, C>& elementSet);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        const std::set<E, C>&            _element_set;

      public:
                            Driver(const std::set<E, C>& elementSet);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alXtreeCollection<K, E, A, C>/*{{{*/
// xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
template<typename K, typename E, typename A, typename C>
class alXtreeCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const xtree<K, E, A, C>& elementXtree);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        const xtree<K, E, A, C>&            _element_tree;

      public:
                            Driver(const xtree<K, E, A, C>& elementXtree);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alVectorCollection<E>/*{{{*/
template<typename E>
class alVectorCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const std::vector<E>& elementVector);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        const std::vector<E>&            _element_vector;

      public:
                            Driver(const std::vector<E>& elementVector);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alMapCollection<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alMapCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const std::map<K, E, C>& elementMap);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alKeyCollection<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alKeyCollection : public alCollection<K> {

  public:
    static  typename alCollection<K>::Driver*    create_driver(const std::map<K, E, C>& elementMap);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<K>::Driver {

      private:
    typedef typename alCollection<K>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<K>::Driver* create_clone() const;
    virtual alIterator<K>            get_iterator(size_t index) const;
    virtual alIterator<K>            get_reverse_iterator(size_t index) const;
    virtual alIterator<K>            find(const K& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alOpenAccessCollection<O, C, E>/*{{{*/
template<typename O, typename C, typename E>
class alOpenAccessCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver* create_driver
                        (const oa::oaCollection<O, C>& objectCollection);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver    Inherit;

      private:
        const oa::oaCollection<O, C>    _object_collection;

      public:
                        Driver(const oa::oaCollection<O, C>& objectCollection);
                        Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alRandomAccessCollection<E>/*{{{*/
template<typename E>
class alRandomAccessCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& objects);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>           _elements;
        mutable alRefCounter<std::vector<E> >   _element_vector_ref;

      public:
                            Driver(const alCollection<E>& objects);
                            Driver(const Driver& driver);

      public:
                            std::vector<E>& save_element_vector_ref() const;

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/


//class alAssociativeAccessCollection<E, C>/*{{{*/
template<typename E, typename C>
class alAssociativeAccessCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& objects);

  public:
    //class IteratorToValue/*{{{*/
    //! dedicated functors
    class IteratorToValue {
      public:
        E operator() (const alIterator<E>& iterator) const;
    };
    /*}}}*/

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      public:
    typedef typename alCollection<E>::Driver        Inherit;
    // xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
    typedef xtree<E, alIterator<E>, IteratorToValue, C>  Xtree;

      private:
        alCollection<E>                          _elements;
        mutable alRefCounter<Xtree>              _element_tree_ref;

      public:
                            Driver(const alCollection<E>& objects);
                            Driver(const Driver& driver);

      public:
                            Xtree& save_element_tree_ref() const;

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/


//class alHeadCollection<E>/*{{{*/
template<typename E>
class alHeadCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 size_t               count);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        size_t                    _count;

      public:
                            Driver(const alCollection<E>& elements,
                               size_t               count);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alTailCollection<E>/*{{{*/
template<typename E>
class alTailCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 size_t               startIndex);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        size_t                    _start_index;

      public:
                            Driver(const alCollection<E>& elements,
                               size_t               startIndex);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alToCollection<E>/*{{{*/
template<typename E>
class alToCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 const E&             last);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        E                    _last;

      public:
                            Driver(const alCollection<E>& elements,
                               const E&             last);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alFromCollection<E>/*{{{*/
template<typename E>
class alFromCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 const E&             first);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        E                    _first;

      public:
                            Driver(const alCollection<E>& elements,
                               const E&             first);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alBeforeCollection<E>/*{{{*/
template<typename E>
class alBeforeCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 const E&             next);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        E                    _next;

      public:
                            Driver(const alCollection<E>& elements,
                               const E&             next);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alAfterCollection<E>/*{{{*/
template<typename E>
class alAfterCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 const E&             previous);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        E                    _previous;

      public:
                            Driver(const alCollection<E>& elements,
                               const E&             previous);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alNotCollection<E>/*{{{*/
template<typename E>
class alNotCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements,
                                 const E&             rejected);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        E                    _rejected;

      public:
                            Driver(const alCollection<E>& elements,
                               const E&             rejected);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alSubsetCollection<E, D>/*{{{*/
template<typename E, typename D = bool>
class alSubsetCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>&   elements,
                                 const alPredicate<E, D>& predicate);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        alPredicate<E, D>                _predicate;

      public:
                            Driver(const alCollection<E>&   elements,
                               const alPredicate<E, D>& predicate);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alAssociatesCollection<E, A, D>/*{{{*/
template<typename E, typename A, typename D = bool>
class alAssociatesCollection : public alCollection<A> {

  public:
    static  typename alCollection<A>::Driver*    create_driver(const alCollection<E>&     elements,
                                 const alAccessor<E, A, D>& accessor);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<A>::Driver {

      private:
    typedef typename alCollection<A>::Driver        Inherit;

      private:
        alCollection<E>                _elements;
        alAccessor<E, A, D>            _accessor;

      public:
                            Driver(const alCollection<E>&     elements,
                               const alAccessor<E, A, D>& accessor);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<A>::Driver* create_clone() const;
    virtual alIterator<A>            get_iterator(size_t index) const;
    virtual alIterator<A>            get_reverse_iterator(size_t index) const;
    virtual alIterator<A>            find(const A& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCollect1Collection<E>/*{{{*/
template<typename E>
class alCollect1Collection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E& first);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;

      public:
                            Driver(const E& first);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCollect2Collection<E>/*{{{*/
template<typename E>
class alCollect2Collection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E& first,
                                 const E& second);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;

      public:
                            Driver(const E& first,
                               const E& second);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCollect3Collection<E>/*{{{*/
template<typename E>
class alCollect3Collection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCollect4Collection<E>/*{{{*/
template<typename E>
class alCollect4Collection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third,
                                 const E& fourth);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;
        E                    _fourth;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third,
                               const E& fourth);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCollect5Collection<E>/*{{{*/
template<typename E>
class alCollect5Collection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third,
                                 const E& fourth,
                                 const E& fifth);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;
        E                    _fourth;
        E                    _fifth;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third,
                               const E& fourth,
                               const E& fifth);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alReverseCollection<E>/*{{{*/
template<typename E>
class alReverseCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& elements);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _elements;

      public:
                            Driver(const alCollection<E>& elements);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alReduceCollection<E>/*{{{*/
template<typename E>
class alReduceCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>&  collection);
    template<typename A, typename D>
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>&     collection,
                                 const alAccessor<E, A, D>& accessor);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _collection;

      public:
                            Driver(const alCollection<E>& collection);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

    //class AssociateDriver/*{{{*/
    template<typename A, typename D>
    class AssociateDriver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _collection;
        alAccessor<E, A, D>            _accessor;

      public:
                            AssociateDriver(
                            const alCollection<E>&     collection,
                            const alAccessor<E, A, D>& accessor);
                            AssociateDriver(const AssociateDriver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alAppendCollection<E>/*{{{*/
template<typename E>
class alAppendCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<E>& head,
                                 const alCollection<E>& tail);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<E>                _head;
        alCollection<E>                _tail;

      public:
                            Driver(const alCollection<E>& head,
                               const alCollection<E>& tail);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alFlattenCollection<E>/*{{{*/
template<typename Es>
class alFlattenCollection : public alCollection<typename Es::ElementType> {

  public:
    typedef typename Es::ElementType        E;

  public:
    static  typename alCollection<E>::Driver*    create_driver(const alCollection<Es>& collections);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        alCollection<Es>                _collections;

      public:
                            Driver(const alCollection<Es>& collections);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/

//class alCustomCollection<E>/*{{{*/
template<typename E>
class alCustomCollection : public alCollection<E> {

  public:
    static  typename alCollection<E>::Driver*    create_driver(const E&                      first,
                                 const alAccessor<E, E>& get_next,
                                 const E&                      before,
                                 const alAccessor<E, E>& get_previous);

  public:
    //class Driver/*{{{*/
    class Driver : public alCollection<E>::Driver {

      private:
    typedef typename alCollection<E>::Driver        Inherit;

      private:
        E                    _first;
        alAccessor<E, E>            _next;
        E                    _before;
        alAccessor<E, E>            _previous;

      public:
                            Driver(const E&                      first,
                               const alAccessor<E, E>& get_next, 
                               const E&                      before);
                            Driver(const E&                      first,
                               const alAccessor<E, E>& get_next,
                               const E&                      before,
                               const alAccessor<E, E>& get_previous);
                            Driver(const Driver& driver);

      public:
    virtual bool              is_random_access() const;
    virtual bool              is_unique_access() const;
    virtual bool              is_associative_access() const;
    virtual bool              is_reversible_access() const;
    virtual bool              is_mutable_access() const;
    virtual bool              is_dynamic_access() const;
    virtual bool              is_sized() const;

      public:
    virtual typename alCollection<E>::Driver* create_clone() const;
    virtual alIterator<E>            get_iterator(size_t index) const;
    virtual alIterator<E>            get_reverse_iterator(size_t index) const;
    virtual alIterator<E>            find(const E& element) const;
    virtual size_t                   get_count() const;
    };
    /*}}}*/

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Generic functions                                                                             //
//                                                                                                //

//Printing operators/*{{{*/
//!\name Printing Operators
//@{
template<typename E>
inline std::ostream&
operator<<(std::ostream& stream, const alCollection<E>& elements)
{
    stream << "{";

    size_t count = 200; //HOOPS
    std::string separator = "";

    for_each (E, element, elements) {
        stream << separator << element;
        if (--count) {
            separator = ", ";
        } else {
            stream << "...";
            break;
        }
    }

    stream << "}";

    return stream;
}
//@}
/*}}}*/

//                                                                                                //
//  alForEachControler<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alForEachControler<E>::alForEachControler(E& current, const D& data)/*{{{*/
template<typename E>
template<typename D>
inline
alForEachControler<E>::alForEachControler(E& current, const D& data)
  : _current(current)
  , _iterator(alCollection<E>(data).get_iterator(0))
{
}
/*}}}*/

//alForEachControler<E>::is_alive()/*{{{*/
template<typename E>
inline bool
alForEachControler<E>::is_alive()
{
    bool alive = _iterator.is_valid();

    if (alive) {
        _current = _iterator.get_current();
        _iterator.progress();
    }

    return alive;
}
/*}}}*/

//alForEachControler<E>::_continue()/*{{{*/
template<typename E>
inline bool&
alForEachControler<E>::_continue()
{
    static bool value = false;

    return value;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alForEachConsecutiveControler<E> implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alForEachConsecutiveControler<E>::alForEachConsecutiveControler(E& current, E& next, const D& data)/*{{{*/
template<typename E>
template<typename D>
inline
alForEachConsecutiveControler<E>::alForEachConsecutiveControler(E& current, E& next, const D& data)
  : _current(current)
  , _next(next)
  , _iterator(alCollection<E>(data).get_iterator(0))
{
}
/*}}}*/

//alForEachConsecutiveControler<E>::is_alive()/*{{{*/
template<typename E>
inline bool
alForEachConsecutiveControler<E>::is_alive()
{
    bool alive = _iterator.is_valid();

    if (alive) {
        _current = _iterator.get_current();

        _iterator.progress();

        alive = _iterator.is_valid();

        if (alive) {
            _next = _iterator.get_current();
        }
    }

    return alive;
}
/*}}}*/

//alForEachConsecutiveControler<E>::_continue()/*{{{*/
template<typename E>
inline bool&
alForEachConsecutiveControler<E>::_continue()
{
    static bool value = false;

    return value;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alForEachParallelControler<E1, E2> implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alForEachParallelControler<E1, E2>::alForEachParallelControler(E1& current1, const D1& data1, E2& current2, const D2& data2)/*{{{*/
template<typename E1, typename E2>
template<typename D1, typename D2>
inline
alForEachParallelControler<E1, E2>::alForEachParallelControler(E1&       current1,
                               const D1& data1,
                               E2&       current2,
                               const D2& data2)
  : _current1(current1)
  , _iterator1(alCollection<E1>(data1).get_iterator(0))
  , _current2(current2)
  , _iterator2(alCollection<E2>(data2).get_iterator(0))
{
}
/*}}}*/

//alForEachParallelControler<E1, E2>::is_alive()/*{{{*/
template<typename E1, typename E2>
inline bool
alForEachParallelControler<E1, E2>::is_alive()
{
    bool alive = _iterator1.is_valid() && _iterator2.is_valid();

    if (alive) {
        _current1 = _iterator1.get_current();
        _current2 = _iterator2.get_current();

        _iterator1.progress();
        _iterator2.progress();
    }

    return alive;
}
/*}}}*/

//alForEachParallelControler<E1, E2>::_continue()/*{{{*/
template<typename E1, typename E2>
inline bool&
alForEachParallelControler<E1, E2>::_continue()
{
    static bool value = false;

    return value;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollection<E> implementation                                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollection<E>::~alCollection()/*{{{*/
template<typename E>
inline
alCollection<E>::~alCollection()
{
    if (is_driven()) {
        delete get_driver();
    }
}
/*}}}*/

//alCollection<E>::alCollection(Driver* driver)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(Driver* driver)
  : _driver(driver)
{
}
/*}}}*/

//alCollection<E>::alCollection(const alCollection<E>& elements)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const alCollection<E>& elements)
  : _driver(elements.is_driven() ? elements.get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alCollection<E>::alCollection(const alCollection<O>& objects)/*{{{*/
template<typename E>
template<typename O>
inline
alCollection<E>::alCollection(const alCollection<O>& objects)
  : _driver(alTypeCollection<O, E>::create_driver(objects))
{
}
/*}}}*/

//alCollection<E>::alCollection(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const alIterator<E>& iterator)
  : _driver(alIteratorCollection<E>::create_driver(iterator))
{
}
/*}}}*/

//alCollection<E>::alCollection(const alIterator<O>& alobjectIterator)/*{{{*/
template<typename E>
template<typename O>
inline
alCollection<E>::alCollection(const alIterator<O>& alobjectIterator)
  : _driver(alTypeCollection<O, E>::create_driver(alobjectIterator))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first)/*{{{*/
template<typename E>
inline 
alCollection<E>::alCollection(const E& first)
  : _driver(alCollect1Collection<E>::create_driver(first))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const E& second)/*{{{*/
template<typename E>
inline 
alCollection<E>::alCollection(const E& first, const E& second)
  : _driver(alCollect2Collection<E>::create_driver(first, second))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const E& second, const E& third)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const E& first, const E& second, const E& third)
  : _driver(alCollect3Collection<E>::create_driver(first, second, third))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const E& second, const E& third, const E& fourth)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const E& first, const E& second, const E& third, const E& fourth)
  : _driver(alCollect4Collection<E>::create_driver(first, second, third, fourth))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)/*{{{*/
template<typename E>
inline 
alCollection<E>::alCollection(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)
  : _driver(alCollect5Collection<E>::create_driver(first, second, third, fourth, fifth))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before, const alAccessor<E, E, D>&  get_previous_accessor)/*{{{*/
template<typename E>
template<typename D>
inline 
alCollection<E>::alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before, const alAccessor<E, E, D>&  get_previous_accessor)
  : _driver(alCustomCollection<E>::create_driver(first,
                         get_next_accessor,
                         before,
                         get_previous_accessor))
{
}
/*}}}*/

//alCollection<E>::alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before)/*{{{*/
template<typename E>
template<typename D>
inline 
alCollection<E>::alCollection(const E& first, const alAccessor<E, E, D>& get_next_accessor, const E& before)
  : _driver(alCustomCollection<E>::create_driver(first,
                         get_next_accessor,
                         before,
                         alAccessor<E, E, D>()))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const std::list<E>& elementList)
  : _driver(alListCollection<E>::create_driver(elementList))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::list<O>& objectList)/*{{{*/
template<typename E>
template<typename O>
inline
alCollection<E>::alCollection(const std::list<O>& objectList)
  : _driver(alTypeCollection<O, E>::create_driver(objectList))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::set<E, C>& elementSet)/*{{{*/
template<typename E>
template<typename C>
inline
alCollection<E>::alCollection(const std::set<E, C>& elementSet)
  : _driver(alSetCollection<E, C>::create_driver(elementSet))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::set<O, C>& objectSet)/*{{{*/
template<typename E>
template<typename O, typename C>
inline
alCollection<E>::alCollection(const std::set<O, C>& objectSet)
  : _driver(alTypeCollection<O, E>::create_driver(objectSet))
{
}
/*}}}*/

//alCollection<E>::alCollection(const xtree<E, C>& elementSet)/*{{{*/
template<typename E>
template<typename K, typename A, typename C>
inline
alCollection<E>::alCollection(const xtree<K, E, A, C>& elementSet)
  : _driver(alXtreeCollection<K, E, A, C>::create_driver(elementSet))
{
}
/*}}}*/

//alCollection<E>::alCollection(const xtree<O, C>& objectSet)/*{{{*/
template<typename E>
template<typename K, typename O, typename A, typename C>
inline
alCollection<E>::alCollection(const xtree<K, O, A, C>& objectSet)
  : _driver(alTypeCollection<O, E>::create_driver(objectSet))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::vector<E>& elementVector)/*{{{*/
template<typename E>
inline
alCollection<E>::alCollection(const std::vector<E>& elementVector)
  : _driver(alVectorCollection<E>::create_driver(elementVector))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::vector<O>& objectVector)/*{{{*/
template<typename E>
template<typename O>
inline
alCollection<E>::alCollection(const std::vector<O>& objectVector)
  : _driver(alTypeCollection<O, E>::create_driver(objectVector))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename E>
template<typename K, typename C>
inline
alCollection<E>::alCollection(const std::map<K, E, C>& elementMap)
  : _driver(alMapCollection<K, E, C>::create_driver(elementMap))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::map<E, D, C>& elementMap)/*{{{*/
template<typename E>
template<typename D, typename C>
inline
alCollection<E>::alCollection(const std::map<E, D, C>& elementMap)
  : _driver(alKeyCollection<E, D, C>::create_driver(elementMap))
{
}
/*}}}*/

//alCollection<E>::alCollection(const std::map<K, O, C>& objectMap)/*{{{*/
template<typename E>
template<typename K, typename O, typename C>
inline
alCollection<E>::alCollection(const std::map<K, O, C>& objectMap)
  : _driver(alTypeCollection<O, E>::create_driver(objectMap))
{
}
/*}}}*/


//alCollection<E>::alCollection(const oa::oaCollection<O, C>& objectCollection)/*{{{*/
template<typename E>
template<typename O, typename C>
inline
alCollection<E>::alCollection(const oa::oaCollection<O, C>& objectCollection)
  : _driver(alOpenAccessCollection<O, C, E>::create_driver(objectCollection))
{
}
/*}}}*/

//alCollection<E>::operator=(Driver* driver)/*{{{*/
template<typename E>
inline alCollection<E>&
alCollection<E>::operator=(Driver* driver)
{
    if (driver != _driver) {
        if (_driver) {
            delete _driver;
        }

        _driver = driver;
    }

    return *this;
}
/*}}}*/

//alCollection<E>::operator=(const alCollection<E>& elements)/*{{{*/
template<typename E>
inline alCollection<E>&
alCollection<E>::operator=(const alCollection<E>& elements)
{
    return operator=((elements.is_driven()) ? elements.get_driver()->create_clone() : NULL);
}
/*}}}*/

//alCollection<E>::operator[](size_t index) const/*{{{*/
template<typename E>
inline E
alCollection<E>::operator[](size_t index) const
{
    return at(index);
}
/*}}}*/

//alCollection<E>::is_empty() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_empty() const
{
    return !get_iterator(0).is_valid();
}
/*}}}*/

//alCollection<E>::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_random_access() const
{
    return is_driven() && get_driver()->is_random_access();
}
/*}}}*/

//alCollection<E>::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_unique_access() const
{
    return is_driven() && get_driver()->is_unique_access();
}
/*}}}*/

//alCollection<E>::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_associative_access() const
{
    return is_driven() && get_driver()->is_associative_access();
}
/*}}}*/

//alCollection<E>::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_reversible_access() const
{
    return is_driven() && get_driver()->is_reversible_access();
}
/*}}}*/

//alCollection<E>::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_mutable_access() const
{
    return is_driven() && get_driver()->is_mutable_access();
}
/*}}}*/

//alCollection<E>::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_dynamic_access() const
{
    return is_driven() && get_driver()->is_dynamic_access();
}
/*}}}*/

//alCollection<E>::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_sized() const
{
    return is_driven() && get_driver()->is_sized();
}
/*}}}*/

//alCollection<E>::is_driven() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_driven() const
{
    return (get_driver() != NULL);
}
/*}}}*/

//alCollection<E>::get_driver() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollection<E>::get_driver() const
{
    return _driver;
}
/*}}}*/

//alCollection<E>::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::get_iterator(size_t index) const
{
    return (is_driven()) ? get_driver()->get_iterator(index) : NULL;
}
/*}}}*/

//alCollection<E>::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::get_reverse_iterator(size_t index) const
{
    return (is_driven()) ? get_driver()->get_reverse_iterator(index) : NULL;
}
/*}}}*/

//alCollection<E>::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::find(const E& element) const
{
    return (is_driven()) ? get_driver()->find(element) : NULL;
}
/*}}}*/

//alCollection<E>::find(const alPredicate<E, D>& predicate) const/*{{{*/
template<typename E>
template<typename D>
inline alIterator<E>
alCollection<E>::find(const alPredicate<E, D>& predicate) const
{
    return create_with(predicate()).begin();
}
/*}}}*/

//alCollection<E>::is_exist(const E& element) const/*{{{*/
template<typename E>
inline bool
alCollection<E>::is_exist(const E& element) const
{
    return find(element).is_valid();
}
/*}}}*/

//alCollection<E>::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollection<E>::get_count() const
{
    return (is_driven()) ? get_driver()->get_count() : 0;
}
/*}}}*/

//alCollection<E>::is_count_equal(size_t size) const/*{{{*/
template<typename E>
bool
alCollection<E>::is_count_equal(size_t size) const
{
    if (size == 0) {
        return is_empty();
    } else {
        alCollection tail = create_without_head(size - 1);
        return tail.is_empty() ? false : tail.create_without_head(1).is_empty();
    }
}
/*}}}*/

//alCollection<E>::is_count_less(size_t size) const/*{{{*/
template<typename E>
bool
alCollection<E>::is_count_less(size_t size) const
{
    return !is_count_greater_or_equal(size);
}
/*}}}*/

//alCollection<E>::is_count_less_or_equal(size_t size) const/*{{{*/
template<typename E>
bool
alCollection<E>::is_count_less_or_equal(size_t size) const
{
    return is_count_less(size + 1);
}
/*}}}*/

//alCollection<E>::is_count_greater(size_t size) const/*{{{*/
template<typename E>
bool
alCollection<E>::is_count_greater(size_t size) const
{
    return is_count_greater_or_equal(size + 1);
}
/*}}}*/

//alCollection<E>::is_count_greater_equal(size_t size) const/*{{{*/
template<typename E>
bool
alCollection<E>::is_count_greater_or_equal(size_t size) const
{
    return size == 0 ? true : !create_without_head(size - 1).is_empty();
}
/*}}}*/

//alCollection<E>::get_first() const/*{{{*/
template<typename E>
inline E
alCollection<E>::get_first() const
{
    return get_iterator(0).get_current();
}
/*}}}*/

//alCollection<E>::get_last() const/*{{{*/
template<typename E>
inline E
alCollection<E>::get_last() const
{
    return get_reverse_iterator(0).get_current();
}
/*}}}*/

//alCollection<E>::at(size_t index) const/*{{{*/
template<typename E>
inline E
alCollection<E>::at(size_t index) const
{
    return get_iterator(index).get_current();
}
/*}}}*/

//alCollection<E>::create_without_tail(size_t count) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_without_tail(size_t count) const
{
    return alHeadCollection<E>::create_driver(*this, count);
}
/*}}}*/

//alCollection<E>::create_without_head(size_t startIndex) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_without_head(size_t startIndex) const
{
    return alTailCollection<E>::create_driver(*this, startIndex);
}
/*}}}*/

//alCollection<E>::create_to(const E& element) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_to(const E& element) const
{
    return alToCollection<E>::create_driver(*this, element);
}
/*}}}*/

//alCollection<E>::create_from(const E& element) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_from(const E& element) const
{
    return alFromCollection<E>::create_driver(*this, element);
}
/*}}}*/

//alCollection<E>::create_before(const E& element) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_before(const E& element) const
{
    return alBeforeCollection<E>::create_driver(*this, element);
}
/*}}}*/

//alCollection<E>::create_after(const E& element) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_after(const E& element) const
{
    return alAfterCollection<E>::create_driver(*this, element);
}
/*}}}*/

//alCollection<E>::create_without(const E& element) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_without(const E& element) const
{
    return alNotCollection<E>::create_driver(*this, element);
}
/*}}}*/

//alCollection<E>::create_flatten() const/*{{{*/
template<typename E>
inline E
alCollection<E>::create_flatten() const
{
    return alFlattenCollection<E>::create_driver(*this);
}
/*}}}*/


//alCollection<E>::create_concatenate(const alCollection<E>& tail) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_concatenate(const alCollection<E>& tail) const
{
    return alAppendCollection<E>::create_driver(*this, tail);
}
/*}}}*/

//alCollection<E>::create_concatenate(const alCollection<E>& tail) const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_reverse() const
{
    return alReverseCollection<E>::create_driver(*this);
}
/*}}}*/

//alCollection<E>::create_unique_access() const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_unique_access() const
{
    return is_unique_access() ? *this : alReduceCollection<E>::create_driver(*this);
}
/*}}}*/

//alCollection<E>::create_with_member(const alAccessor<E, A, D>& accessor, const A& member) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alCollection<E>
alCollection<E>::create_with_member(const alAccessor<E, A, D>& accessor, const A& member) const
{
    return alSubsetCollection<E, A>::create_driver(*this, alPredicate<E, A>(accessor, &alEqual<A>::is)(member));
}
/*}}}*/

//alCollection<E>::create_without_member(const alAccessor<E, A, D>& accessor, const A& member) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alCollection<E>
alCollection<E>::create_without_member(const alAccessor<E, A, D>& accessor, const A& member) const
{
    return alSubsetCollection<E>::create_driver(*this, !alPredicate<E, A>(accessor, &alEqual<A>::is)(member));
}
/*}}}*/

//alCollection<E>::create_unique_access(const alAccessor<E, A, D>& accessor) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alCollection<E>
alCollection<E>::create_unique_access(const alAccessor<E, A, D>& accessor) const
{
    return alReduceCollection<E>::create_driver(*this, accessor);
}
/*}}}*/

//alCollection<E>::create_with(const alPredicate<E, D>& predicate) const/*{{{*/
template<typename E>
template<typename D>
inline alCollection<E>
alCollection<E>::create_with(const alPredicate<E, D>& predicate) const
{
    return alSubsetCollection<E, D>::create_driver(*this, predicate);
}
/*}}}*/

//alCollection<E>::create_with(const alPredicate<O, D>& predicate) const/*{{{*/
template<typename E>
template<typename O, typename D>
inline alCollection<E>
alCollection<E>::create_with(const alPredicate<O, D>& predicate) const
{
    return alCollection<O>(*this).create_with(predicate);
}
/*}}}*/

//alCollection<E>::create_member_access(const alAccessor<E, A, D>& accessor) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alCollection<A>
alCollection<E>::create_member_access(const alAccessor<E, A, D>& accessor) const
{
    return alAssociatesCollection<E, A, D>::create_driver(*this, accessor);
}
/*}}}*/

//alCollection<E>::create_member_access(const alAccessor<O, A, D>& accessor) const/*{{{*/
template<typename E>
template<typename O, typename A, typename D>
inline alCollection<A>
alCollection<E>::create_member_access(const alAccessor<O, A, D>& accessor) const
{
    return alCollection<O>(*this).create_member_access(accessor);
}
/*}}}*/

//alCollection<E>::apply(const alAction<E, D>& action) const/*{{{*/
template<typename E>
template<typename D>
inline void
alCollection<E>::apply(const alAction<E, D>& action) const
{
    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        E element = iterator.get_current();
        iterator.progress();
        action.apply(element);
    }
}
/*}}}*/

//alCollection<E>::apply(const alAction<O, D>& action) const/*{{{*/
template<typename E>
template<typename O, typename D>
inline void
alCollection<E>::apply(const alAction<O, D>& action) const
{
    return alCollection<O>(*this).apply(action);
}
/*}}}*/

//alCollection<E>::operator ==() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::operator ==(const alCollection<E>& collection) const
{
    alIterator<E> iterator = get_iterator();
    alIterator<E> iterator2 = collection.get_iterator();
    
    while (iterator.is_valid() && iterator2.is_valid()) {
        if (iterator.get_current() != iterator2.get_current()) 
            return false;
        iterator.progress();
        iterator2.progress();
    }

    return !iterator.is_valid() && !iterator2.is_valid();
}
/*}}}*/

//alCollection<E>::operator !=() const/*{{{*/
template<typename E>
inline bool
alCollection<E>::operator !=(const alCollection<E>& collection) const
{
    return ! alCollection<E>::operator ==(collection);
}
/*}}}*/

//alCollection<E>::create_random_access() const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_random_access() const
{
    return is_random_access() ? *this : alRandomAccessCollection<E>::create_driver(*this);
}
/*}}}*/

//alCollection<E>::create_associative_access() const/*{{{*/
template<typename E>
inline alCollection<E>
alCollection<E>::create_associative_access() const
{
    return is_associative_access() ? *this : alAssociativeAccessCollection<E, std::less<E> >::create_driver(*this);
}
/*}}}*/

//alCollection<E>::save(std::list<E>& elementList) const/*{{{*/
template<typename E>
inline std::list<E>&
alCollection<E>::save(std::list<E>& elementList) const
{
    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        elementList.push_back(iterator.get_current());
        iterator.progress();
    }

    return elementList;
}
/*}}}*/

//alCollection<E>::save(std::set<E, C>& elementSet) const/*{{{*/
template<typename E>
template<typename C>
inline std::set<E, C>&
alCollection<E>::save(std::set<E, C>& elementSet) const
{
    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        elementSet.insert(iterator.get_current());
        iterator.progress();
    }

    return elementSet;
}
/*}}}*/

//alCollection<E>::save(xtree<K, E, A, C>& elementXtree) const/*{{{*/
template<typename E>
template<typename K, typename A, typename C>
inline xtree<K, E, A, C>&
alCollection<E>::save(xtree<K, E, A, C>& elementXtree) const
{
    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        elementXtree.insert_unique(iterator.get_current());
        iterator.progress();
    }

    return elementXtree;
}
/*}}}*/

//alCollection<E>::save(std::vector<E>& elementVector) const/*{{{*/
template<typename E>
inline std::vector<E>&
alCollection<E>::save(std::vector<E>& elementVector) const
{
    elementVector.reserve(elementVector.size() + get_count());

    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        elementVector.push_back(iterator.get_current());
        iterator.progress();
    }

    return elementVector;
}
/*}}}*/

//alCollection<E>::save(std::map<K, E, C>& elementMap, const alAccessor<E, K>& keyAccessor) const/*{{{*/
template<typename E>
template<typename K, typename C>
inline std::map<K, E, C>&
alCollection<E>::save(std::map<K, E, C>& elementMap, const alAccessor<E, K>& keyAccessor) const
{
    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        E current = iterator.get_current();
        elementMap[keyAccessor.get_associate(current)] = current;
        iterator.progress();
    }

    return elementMap;
}
/*}}}*/

//alCollection<E>::save(std::list<O>& objectList) const/*{{{*/
template<typename E>
template<typename O>
inline std::list<O>&
alCollection<E>::save(std::list<O>& objectList) const
{
    return alCollection<O>(*this).save(objectList);
}
/*}}}*/

//alCollection<E>::save(std::set<O, C>& objectSet) const/*{{{*/
template<typename E>
template<typename O, typename C>
inline std::set<O, C>&
alCollection<E>::save(std::set<O, C>& objectSet) const
{
    return alCollection<O>(*this).save(objectSet);
}
/*}}}*/

//alCollection<E>::save(xtree<K, O, A, C>& objectSet) const/*{{{*/
template<typename E>
template<typename K, typename O, typename A, typename C>
inline xtree<K, O, A, C>&
alCollection<E>::save(xtree<K, O, A, C>& objectSet) const
{
    return alCollection<O>(*this).save(objectSet);
}
/*}}}*/

//alCollection<E>::save(std::vector<O>& objectVector) const/*{{{*/
template<typename E>
template<typename O>
inline std::vector<O>&
alCollection<E>::save(std::vector<O>& objectVector) const
{
    return alCollection<O>(*this).save(objectVector);
}
/*}}}*/

//alCollection<E>::save(std::map<K, O, C>& objectMap, const alAccessor<O, K>& keyAccessor) const/*{{{*/
template<typename E>
template<typename O, typename K, typename C>
inline std::map<K, O, C>&
alCollection<E>::save(std::map<K, O, C>& objectMap, const alAccessor<O, K>& keyAccessor) const
{
    return alCollection<O>(*this).save(objectMap, keyAccessor);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollection<E>::Driver implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollection<E>::Driver::~Driver()/*{{{*/
template<typename E>
inline
alCollection<E>::Driver::~Driver()
{
}
/*}}}*/

//alCollection<E>::Driver::Driver()/*{{{*/
template<typename E>
inline
alCollection<E>::Driver::Driver()
{
}
/*}}}*/

//alCollection<E>::Driver::eval_iterator(alIterator<E> iterator, size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::Driver::eval_iterator(alIterator<E> iterator, size_t index) const
{
    size_t count = 0;

    while (iterator.is_valid()) {
        if (count++ == index) {
            return iterator;
        }

        iterator.progress();
    }

    return iterator;
}
/*}}}*/

//alCollection<E>::Driver::eval_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::Driver::eval_reverse_iterator(size_t index) const
{
    return eval_iterator(alReverseIterator<E>::create_driver(get_iterator(0)), index);
}
/*}}}*/

//alCollection<E>::Driver::eval_find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollection<E>::Driver::eval_find(const E& element) const
{
    return alFromIterator<E>::create_driver(get_iterator(0), element);
}

//alCollection<E>::Driver::eval_count(alIterator<E>& iterator) const/*{{{*/
template<typename E>
inline size_t
alCollection<E>::Driver::eval_count() const
{
    size_t count = 0;

    alIterator<E> iterator = get_iterator(0);

    while (iterator.is_valid()) {
        ++count;
        iterator.progress();
    }

    return count;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alTypeCollection<O, E> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alTypeCollection<O, E>::create_driver(const alCollection<O>& objects)/*{{{*/
template<typename O, typename E>
inline typename alCollection<E>::Driver*
alTypeCollection<O, E>::create_driver(const alCollection<O>& objects)
{
    return new Driver(objects);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTypeCollection<O, E>::Driver implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alTypeCollection<O, E>::Driver::Driver(const alCollection<O>& objects)/*{{{*/
template<typename O, typename E>
inline
alTypeCollection<O, E>::Driver::Driver(const alCollection<O>& objects)
  : Inherit()
  , _elements(objects)
{
}
/*}}}*/

//alTypeCollection<O, E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename O, typename E>
inline
alTypeCollection<O, E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
{
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_random_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_unique_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_associative_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_associative_access() const
{
    return _elements.is_associative_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_reversible_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_mutable_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_dynamic_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::is_sized() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeCollection<O, E>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/

//alTypeCollection<O, E>::Driver::create_clone() const/*{{{*/
template<typename O, typename E>
inline typename alCollection<E>::Driver*
alTypeCollection<O, E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alTypeCollection<O, E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename O, typename E>
inline alIterator<E>
alTypeCollection<O, E>::Driver::get_iterator(size_t index) const
{
    return alTypeIterator<O, E>::create_driver(_elements.get_iterator(index));
}
/*}}}*/

//alTypeCollection<O, E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename O, typename E>
inline alIterator<E>
alTypeCollection<O, E>::Driver::get_reverse_iterator(size_t index) const
{
    return alTypeIterator<O, E>::create_driver(_elements.get_reverse_iterator(index));
}
/*}}}*/

//alTypeCollection<O, E>::Driver::find(const E& element) const/*{{{*/
template<typename O, typename E>
inline alIterator<E>
alTypeCollection<O, E>::Driver::find(const E& element) const
{
    return alTypeIterator<O, E>::create_driver(_elements.find((O&) element));
}
/*}}}*/

//alTypeCollection<O, E>::Driver::get_count() const/*{{{*/
template<typename O, typename E>
inline size_t
alTypeCollection<O, E>::Driver::get_count() const
{
    return _elements.get_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alIteratorCollection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alIteratorCollection<E>::create_driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alIteratorCollection<E>::create_driver(const alIterator<E>& iterator)
{
    return new Driver(iterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alIteratorCollection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alIteratorCollection<E>::Driver::Driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline
alIteratorCollection<E>::Driver::Driver(const alIterator<E>& iterator)
  : Inherit()
  , _iterator(iterator)
{
}
/*}}}*/

//alIteratorCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alIteratorCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alIteratorCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alIteratorCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alIteratorCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alIteratorCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alIteratorCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alIteratorCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(_iterator, index);
}
/*}}}*/

//alIteratorCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alIteratorCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alIteratorCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alIteratorCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alIteratorCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alIteratorCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alListCollection<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alListCollection<E>::create_driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alListCollection<E>::create_driver(const std::list<E>& elementList)
{
    return new Driver(elementList);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alListCollection<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alListCollection<E>::Driver::Driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline
alListCollection<E>::Driver::Driver(const std::list<E>& elementList)
  : Inherit()
  , _element_list(elementList)
{
}
/*}}}*/

//alListCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alListCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_list(driver._element_list)
{
}
/*}}}*/

//alListCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alListCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alListCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alListCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alListCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alListCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alListCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alListCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alListCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alListCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alListCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alListCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alListIterator<E>::create_driver(_element_list), index);
}
/*}}}*/

//alListCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alListCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alListReverseIterator<E>::create_driver(_element_list), index);
}
/*}}}*/

//alListCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alListCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alListCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alListCollection<E>::Driver::get_count() const
{
    return _element_list.size();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alSetCollection<E, C> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alSetCollection<E>::create_driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline typename alCollection<E>::Driver*
alSetCollection<E, C>::create_driver(const std::set<E, C>& elementSet)
{
    return new Driver(elementSet);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSetCollection<E, C>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alSetCollection<E, C>::Driver::Driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline
alSetCollection<E, C>::Driver::Driver(const std::set<E, C>& elementSet)
  : Inherit()
  , _element_set(elementSet)
{
}
/*}}}*/

//alSetCollection<E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename C>
inline
alSetCollection<E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_set(driver._element_set)
{
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_random_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_unique_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_unique_access() const
{
    return true;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_associative_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_associative_access() const
{
    return true;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_reversible_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSetCollection<E, C>::Driver::is_sized() const/*{{{*/
template<typename E, typename C>
inline bool
alSetCollection<E, C>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alSetCollection<E, C>::Driver::create_clone() const/*{{{*/
template<typename E, typename C>
inline typename alCollection<E>::Driver*
alSetCollection<E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alSetCollection<E, C>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alSetCollection<E, C>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alSetIterator<E, C>::create_driver(_element_set), index);
}
/*}}}*/

//alSetCollection<E, C>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alSetCollection<E, C>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alSetReverseIterator<E, C>::create_driver(_element_set), index);
}
/*}}}*/

//alSetCollection<E, C>::Driver::find(const E& element) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alSetCollection<E, C>::Driver::find(const E& element) const
{
    return alSetIterator<E, C>::create_driver(_element_set, _element_set.find(element));
}
/*}}}*/

//alSetCollection<E, C>::Driver::get_count() const/*{{{*/
template<typename E, typename C>
inline size_t
alSetCollection<E, C>::Driver::get_count() const
{
    return _element_set.size();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alXtreeCollection<K, E, A, C> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeCollection<E>::create_driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alCollection<E>::Driver*
alXtreeCollection<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree)
{
    return new Driver(elementXtree);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alXtreeCollection<K, E, A, C>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeCollection<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeCollection<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)
  : Inherit()
  , _element_tree(elementXtree)
{
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeCollection<K, E, A, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_tree(driver._element_tree)
{
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_random_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_unique_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_associative_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_associative_access() const
{
    return true;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_reversible_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::is_sized() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeCollection<K, E, A, C>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alCollection<E>::Driver*
alXtreeCollection<K, E, A, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline alIterator<E>
alXtreeCollection<K, E, A, C>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alXtreeIterator<K, E, A, C>::create_driver(_element_tree), index);
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline alIterator<E>
alXtreeCollection<K, E, A, C>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alXtreeReverseIterator<K, E, A, C>::create_driver(_element_tree), index);
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::find(const E& element) const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline alIterator<E>
alXtreeCollection<K, E, A, C>::Driver::find(const E& element) const
{
    return alXtreeIterator<K, E, A, C>::create_driver(_element_tree, _element_tree.find(A() (element)));
}
/*}}}*/

//alXtreeCollection<K, E, A, C>::Driver::get_count() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline size_t
alXtreeCollection<K, E, A, C>::Driver::get_count() const
{
    return _element_tree.size();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alVectorCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alVectorCollection<E>::create_driver(const std::vector<E>& elementVector)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alVectorCollection<E>::create_driver(const std::vector<E>& elementVector)
{
    return new Driver(elementVector);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alVectorCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alVectorCollection<E>::Driver::Driver(const std::vector<E>& elementVector)/*{{{*/
template<typename E>
inline
alVectorCollection<E>::Driver::Driver(const std::vector<E>& elementVector)
  : Inherit()
  , _element_vector(elementVector)
{
}
/*}}}*/

//alVectorCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alVectorCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_vector(driver._element_vector)
{
}
/*}}}*/

//alVectorCollection<O, E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alVectorCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alVectorCollection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alVectorCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alVectorCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alVectorCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alVectorCollection<E>::Driver::get_iterator(size_t index) const
{
    return alVectorIterator<E>::create_driver(_element_vector, index);
}
/*}}}*/

//alVectorCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alVectorCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return alVectorReverseIterator<E>::create_driver(_element_vector, index);
}
/*}}}*/

//alVectorCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alVectorCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alVectorCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alVectorCollection<E>::Driver::get_count() const
{
    return _element_vector.size();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapCollection<K, E, C> implementation                                                         //
//                                                                                                //

#ifndef DOXYGEN
//alMapCollection<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alCollection<E>::Driver*
alMapCollection<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapCollection<K, E, C>::Driver implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alMapCollection<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapCollection<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
{
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapCollection<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
{
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_random_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_unique_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_associative_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_reversible_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::is_sized() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapCollection<K, E, C>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alCollection<E>::Driver*
alMapCollection<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<E>
alMapCollection<K, E, C>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alMapIterator<K, E, C>::create_driver(_element_map), index);
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<E>
alMapCollection<K, E, C>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alMapReverseIterator<K, E, C>::create_driver(_element_map), index);
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::find(const E& element) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<E>
alMapCollection<K, E, C>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alMapCollection<K, E, C>::Driver::get_count() const/*{{{*/
template<typename K, typename E, typename C>
inline size_t
alMapCollection<K, E, C>::Driver::get_count() const
{
    return _element_map.size();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alKeyCollection<K, E, C> implementation                                                         //
//                                                                                                //

#ifndef DOXYGEN
//alKeyCollection<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alCollection<K>::Driver*
alKeyCollection<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alKeyCollection<K, E, C>::Driver implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alKeyCollection<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyCollection<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
{
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyCollection<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
{
}
/*}}}*/

//alKeyCollection<O, E>::Driver::is_random_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_unique_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_unique_access() const
{
    return true;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_associative_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_associative_access() const
{
    return true;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_reversible_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::is_sized() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyCollection<K, E, C>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alCollection<K>::Driver*
alKeyCollection<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<K>
alKeyCollection<K, E, C>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alKeyIterator<K, E, C>::create_driver(_element_map), index);
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<K>
alKeyCollection<K, E, C>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alKeyReverseIterator<K, E, C>::create_driver(_element_map), index);
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::find(const E& element) const/*{{{*/
template<typename K, typename E, typename C>
inline alIterator<K>
alKeyCollection<K, E, C>::Driver::find(const K& element) const
{
    return alKeyIterator<K, E, C>::create_driver(_element_map, _element_map.find(element));
}
/*}}}*/

//alKeyCollection<K, E, C>::Driver::get_count() const/*{{{*/
template<typename K, typename E, typename C>
inline size_t
alKeyCollection<K, E, C>::Driver::get_count() const
{
    return _element_map.size();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alOpenAccessCollection<O, C, E> implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alOpenAccessCollection<O, C, E>::create_driver(const oa::oaCollection<O, C>& objectCollection)/*{{{*/
template<typename O, typename C, typename E>
inline typename alCollection<E>::Driver*
alOpenAccessCollection<O, C, E>::create_driver(const oa::oaCollection<O, C>& objectCollection)
{
    return new Driver(objectCollection);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alOpenAccessCollection<O, C, E>::Driver implementation                                          //
//                                                                                                //

#ifndef DOXYGEN
//alOpenAccessCollection<O, C, E>::Driver::Driver(const oa::oaCollection<O, C>& objectCollection)/*{{{*/
template<typename O, typename C, typename E>
inline
alOpenAccessCollection<O, C, E>::Driver::Driver(const oa::oaCollection<O, C>& objectCollection)
  : Inherit()
  , _object_collection(objectCollection)
{
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename O, typename C, typename E>
inline
alOpenAccessCollection<O, C, E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _object_collection(driver._object_collection)
{
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_random_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_unique_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_unique_access() const
{
    return true;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_associative_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_reversible_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_mutable_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_dynamic_access() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::is_sized() const/*{{{*/
template<typename O, typename C, typename E>
inline bool
alOpenAccessCollection<O, C, E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::create_clone() const/*{{{*/
template<typename O, typename C, typename E>
inline typename alCollection<E>::Driver*
alOpenAccessCollection<O, C, E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename O, typename C, typename E>
inline alIterator<E>
alOpenAccessCollection<O, C, E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alOpenAccessIterator<O, C, E>::create_driver(_object_collection), index);
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename O, typename C, typename E>
inline alIterator<E>
alOpenAccessCollection<O, C, E>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::find(const E& element) const/*{{{*/
template<typename O, typename C, typename E>
inline alIterator<E>
alOpenAccessCollection<O, C, E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alOpenAccessCollection<O, C, E>::Driver::get_count() const/*{{{*/
template<typename O, typename C, typename E>
inline size_t
alOpenAccessCollection<O, C, E>::Driver::get_count() const
{
    return _object_collection.getCount();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alRandomAccessCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessCollection<E>::create_driver(const std::vector<E>& elementVector)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alRandomAccessCollection<E>::create_driver(const alCollection<E>& objects)
{
    return new Driver(objects);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alRandomAccessCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessCollection<E>::Driver::Driver(const std::vector<E>& elementVector)/*{{{*/
template<typename E>
inline
alRandomAccessCollection<E>::Driver::Driver(const alCollection<E>& objects)
  : Inherit()
  , _elements(objects)
  , _element_vector_ref()
{
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alRandomAccessCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _element_vector_ref()
{
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::save_element_vector_ref() const/*{{{*/
template<typename E>
inline std::vector<E>&
alRandomAccessCollection<E>::Driver::save_element_vector_ref() const
{
    if (_elements.is_empty() || !_element_vector_ref.get_elements().empty())
        return _element_vector_ref.get_elements();

    if (_elements.is_sized()) {
        _element_vector_ref.get_elements().reserve(_elements.get_count());
    }

    for_each (E, object, _elements) {
        _element_vector_ref.get_elements().push_back(object);
    }
   
    return _element_vector_ref.get_elements();
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_associative_access() const
{
    return _elements.is_associative_access();
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alRandomAccessCollection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alRandomAccessCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alRandomAccessCollection<E>::Driver::get_iterator(size_t index) const
{
    save_element_vector_ref();
    return alRandomAccessIterator<E>::create_driver(_element_vector_ref, index);
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alRandomAccessCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    save_element_vector_ref();
    return alRandomAccessReverseIterator<E>::create_driver(_element_vector_ref, index);
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alRandomAccessCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alRandomAccessCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alRandomAccessCollection<E>::Driver::get_count() const
{
    if (is_sized()) {
        return _elements.get_count();
    } else {
        save_element_vector_ref();
        return _element_vector_ref.get_elements().size();
    }
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alAssociativeAccessCollection<E, C> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alAssociativeAccessCollection<E>::create_driver(const alCollection<E>& objects)/*{{{*/
template<typename E, typename C>
inline typename alCollection<E>::Driver*
alAssociativeAccessCollection<E, C>::create_driver(const alCollection<E>& objects)
{
    return new Driver(objects);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAssociativeAccessCollection<E, C>::IteratorToValue implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alAssociativeAccessCollection<E, C>::IteratorToValue::operator() (const alIterator<E>& iterator) const/*{{{*/
template<typename E, typename C>
inline E
alAssociativeAccessCollection<E, C>::IteratorToValue::operator() (const alIterator<E>& iterator) const
{
    return iterator.get_current();
}
/*}}}*/
#endif // DOXYGEN


//                                                                                                //
//  alAssociativeAccessCollection<E, C>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alAssociativeAccessCollection<E, C>::Driver::Driver(const alCollection<E>& objects)/*{{{*/
template<typename E, typename C>
inline
alAssociativeAccessCollection<E, C>::Driver::Driver(const alCollection<E>& objects)
  : Inherit()
  , _elements(objects)
  , _element_tree_ref()
{
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename C>
inline
alAssociativeAccessCollection<E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _element_tree_ref()
{
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::save_element_tree_ref() const/*{{{*/
template<typename E, typename C>
inline typename alAssociativeAccessCollection<E, C>::Driver::Xtree&
alAssociativeAccessCollection<E, C>::Driver::save_element_tree_ref() const
{
    if (_elements.is_empty() || !_element_tree_ref.get_elements().empty())
        return _element_tree_ref.get_elements();

    alIterator<E> iterator = _elements.get_iterator(0);

    while (iterator.is_valid()) {
        // insert once each element !
        if (_element_tree_ref.get_elements().find(iterator.get_current()) == _element_tree_ref.get_elements().end())
            _element_tree_ref.get_elements().insert_unique(iterator);
        iterator.progress();
    }

    return _element_tree_ref.get_elements();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_random_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_unique_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_associative_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_associative_access() const
{
    return true;
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_reversible_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::is_sized() const/*{{{*/
template<typename E, typename C>
inline bool
alAssociativeAccessCollection<E, C>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::create_clone() const/*{{{*/
template<typename E, typename C>
inline typename alCollection<E>::Driver*
alAssociativeAccessCollection<E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alAssociativeAccessCollection<E, C>::Driver::get_iterator(size_t index) const
{
    return _elements.get_iterator(index);
}
/*}}}*/

//alAssociateAccessCollection<E, C>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alAssociativeAccessCollection<E, C>::Driver::get_reverse_iterator(size_t index) const
{
    return _elements.get_reverse_iterator(index);
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::find(const E& element) const/*{{{*/
template<typename E, typename C>
inline alIterator<E>
alAssociativeAccessCollection<E, C>::Driver::find(const E& element) const
{
    save_element_tree_ref();
    typename Driver::Xtree::const_iterator iterator = _element_tree_ref.get_elements().find(element);

    if (iterator != _element_tree_ref.get_elements().end()) {
        return *iterator;
    } else {
        return alIterator<E>();
    }
}
/*}}}*/

//alAssociativeAccessCollection<E, C>::Driver::get_count() const/*{{{*/
template<typename E, typename C>
inline size_t
alAssociativeAccessCollection<E, C>::Driver::get_count() const
{
    return _elements.get_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alHeadCollection<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alHeadCollection<E>::create_driver(const alCollection<E>& elements, size_t count)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alHeadCollection<E>::create_driver(const alCollection<E>& elements, size_t count)
{
    return new Driver(elements, count);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alHeadCollection<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alHeadCollection<E>::Driver::Driver(const alCollection<E>& elements, size_t count)/*{{{*/
template<typename E>
inline
alHeadCollection<E>::Driver::Driver(const alCollection<E>& elements, size_t count)
  : Inherit()
  , _elements(elements)
  , _count(count)
{
}
/*}}}*/

//alHeadCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alHeadCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _count(driver._count)
{
}
/*}}}*/

//alHeadCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alHeadCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alHeadCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alHeadCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alHeadCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alHeadCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alHeadCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alHeadCollection<E>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/

//alHeadCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alHeadCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alHeadCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alHeadCollection<E>::Driver::get_iterator(size_t index) const
{
    size_t count = get_count();
    if (index < count) {
        return alHeadIterator<E>::create_driver(_elements.get_iterator(index), count - index);
     } else {
         return alIterator<E> ();
     }
}
/*}}}*/

//alHeadCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alHeadCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    size_t count = get_count();
    if (index < count) {
        size_t original_size = _elements.get_count();
        return alTailIterator<E>::create_driver(_elements.get_reverse_iterator(original_size - count + index), 0);
    } else {
         return alIterator<E> ();
     }
}
/*}}}*/

//alHeadCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alHeadCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alHeadCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alHeadCollection<E>::Driver::get_count() const
{
    size_t count = _elements.get_count();

    return std::min(_count, count);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTailCollection<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alTailCollection<E>::create_driver(const alCollection<E>& elements, size_t startIndex)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alTailCollection<E>::create_driver(const alCollection<E>& elements, size_t startIndex)
{
    return new Driver(elements, startIndex);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTailCollection<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alTailCollection<E>::Driver::Driver(const alCollection<E>& elements, size_t startIndex)/*{{{*/
template<typename E>
inline
alTailCollection<E>::Driver::Driver(const alCollection<E>& elements, size_t startIndex)
  : Inherit()
  , _elements(elements)
  , _start_index(startIndex)
{
}
/*}}}*/

//alTailCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alTailCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _start_index(driver._start_index)
{
}
/*}}}*/

//alTailCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alTailCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alTailCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alTailCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alTailCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alTailCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alTailCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alTailCollection<E>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/

//alTailCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alTailCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alTailCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alTailCollection<E>::Driver::get_iterator(size_t index) const
{
    return alTailIterator<E>::create_driver(_elements.get_iterator(_start_index + index), 0);
}
/*}}}*/

//alTailCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alTailCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    size_t count = get_count();
    if (index < count) {
        return alHeadIterator<E>::create_driver(_elements.get_reverse_iterator(index), count - index);
     } else {
         return alIterator<E> ();
     }
}
/*}}}*/

//alTailCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alTailCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alTailCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alTailCollection<E>::Driver::get_count() const
{
    size_t count = _elements.get_count();

    return (_start_index < count) ? (count - _start_index) : 0;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alToCollection<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alToCollection<E>::create_driver(const alCollection<E>& elements, const E& last)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alToCollection<E>::create_driver(const alCollection<E>& elements, const E& last)
{
    return new Driver(elements, last);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alToCollection<E>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alToCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& last)/*{{{*/
template<typename E>
inline
alToCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& last)
  : Inherit()
  , _elements(elements)
  , _last(last)
{
}
/*}}}*/

//alToCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alToCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _last(driver._last)
{
}
/*}}}*/

//alToCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alToCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alToCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alToCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alToCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alToCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alToCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alToCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alToCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alToCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alToCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alToCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alToIterator<E>::create_driver(_elements.get_iterator(0), _last), index);
}
/*}}}*/

//alToCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alToCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    // TODO : create a ToReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alToCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alToCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alToCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alToCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alFromCollection<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alFromCollection<E>::create_driver(const alCollection<E>& elements, const E& first)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alFromCollection<E>::create_driver(const alCollection<E>& elements, const E& first)
{
    return new Driver(elements, first);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFromCollection<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alFromCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& first)/*{{{*/
template<typename E>
inline
alFromCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& first)
  : Inherit()
  , _elements(elements)
  , _first(first)
{
}
/*}}}*/

//alFromCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alFromCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _first(driver._first)
{
}
/*}}}*/

//alFromCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alFromCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alFromCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alFromCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alFromCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alFromCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alFromCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alFromCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alFromCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alFromCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alFromCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alFromCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alFromIterator<E>::create_driver(_elements.find(_first), _first), index);
}
/*}}}*/

//alFromCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alFromCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    // TODO : create a FromReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alFromCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alFromCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alFromCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alFromCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alBeforeCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alBeforeCollection<E>::create_driver(const alCollection<E>& elements, const E& next)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alBeforeCollection<E>::create_driver(const alCollection<E>& elements, const E& next)
{
    return new Driver(elements, next);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alBeforeCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alBeforeCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& next)/*{{{*/
template<typename E>
inline
alBeforeCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& next)
  : Inherit()
  , _elements(elements)
  , _next(next)
{
}
/*}}}*/

//alBeforeCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alBeforeCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _next(driver._next)
{
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alBeforeCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alBeforeCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alBeforeCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alBeforeCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alBeforeCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alBeforeCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alBeforeIterator<E>::create_driver(_elements.get_iterator(0), _next), index);
}
/*}}}*/

//alBeforeCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alBeforeCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    // TODO : create a BeforeReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alBeforeCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alBeforeCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alBeforeCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alBeforeCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alAfterCollection<E> implementation                                                             //
//                                                                                                //

#ifndef DOXYGEN
//alAfterCollection<E>::create_driver(const alCollection<E>& elements, const E& previous)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alAfterCollection<E>::create_driver(const alCollection<E>& elements, const E& previous)
{
    return new Driver(elements, previous);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAfterCollection<E>::Driver implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alAfterCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& previous)/*{{{*/
template<typename E>
inline
alAfterCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& previous)
  : Inherit()
  , _elements(elements)
  , _previous(previous)
{
}
/*}}}*/

//alAfterCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alAfterCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _previous(driver._previous)
{
}
/*}}}*/

//alAfterCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alAfterCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alAfterCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alAfterCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alAfterCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alAfterCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alAfterCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alAfterCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alAfterCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alAfterCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAfterCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alAfterCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alAfterIterator<E>::create_driver(_elements.find(_previous), _previous), index);
}
/*}}}*/

//alAfterCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alAfterCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    // TODO : create a AfterReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alAfterCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alAfterCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alAfterCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alAfterCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alNotCollection<E> implementation                                                               //
//                                                                                                //

#ifndef DOXYGEN
//alNotCollection<E>::create_driver(const alCollection<E>& elements, const E& rejected)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alNotCollection<E>::create_driver(const alCollection<E>& elements, const E& rejected)
{
    return new Driver(elements, rejected);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alNotCollection<E>::Driver implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alNotCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& rejected)/*{{{*/
template<typename E>
inline
alNotCollection<E>::Driver::Driver(const alCollection<E>& elements, const E& rejected)
  : Inherit()
  , _elements(elements)
  , _rejected(rejected)
{
}
/*}}}*/

//alNotCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alNotCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _rejected(driver._rejected)
{
}
/*}}}*/

//alNotCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alNotCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alNotCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_associative_access() const
{
    return _elements.is_associative_access();
}
/*}}}*/

//alNotCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alNotCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alNotCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alNotCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alNotCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alNotCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alNotCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alNotCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alNotCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alNotIterator<E>::create_driver(_elements.get_iterator(0), _rejected), index);
}
/*}}}*/

//alNotCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alNotCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alNotCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alNotCollection<E>::Driver::find(const E& element) const
{
    if (element == _rejected)
        return alIterator<E> ();
    else 
        return _elements.find(element);
}
/*}}}*/

//alNotCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alNotCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alSubsetCollection<E, D> implementation                                                         //
//                                                                                                //

#ifndef DOXYGEN
//alSubsetCollection<E, D>::create_driver(const alCollection<E>& elements, const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline typename alCollection<E>::Driver*
alSubsetCollection<E, D>::create_driver(const alCollection<E>& elements, const alPredicate<E, D>& predicate)
{
    return new Driver(elements, predicate);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSubsetCollection<E, D>::Driver implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alSubsetCollection<E, D>::Driver::Driver(const alCollection<E>& elements, const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline
alSubsetCollection<E, D>::Driver::Driver(const alCollection<E>& elements, const alPredicate<E, D>& predicate)
  : Inherit()
  , _elements(elements)
  , _predicate(predicate)
{
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename D>
inline
alSubsetCollection<E, D>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _predicate(driver._predicate)
{
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_random_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_unique_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_associative_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_reversible_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access() && _predicate.is_dynamic_access();
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::is_sized() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetCollection<E, D>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::create_clone() const/*{{{*/
template<typename E, typename D>
inline typename alCollection<E>::Driver*
alSubsetCollection<E, D>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E, typename D>
inline alIterator<E>
alSubsetCollection<E, D>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alSubsetIterator<E, D>::create_driver(_elements.get_iterator(0), _predicate), index);
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E, typename D>
inline alIterator<E>
alSubsetCollection<E, D>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alSubsetCollection<E, D>::Driver::find(const E& element) const/*{{{*/
template<typename E, typename D>
inline alIterator<E>
alSubsetCollection<E, D>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alSubsetCollection<E>::Driver::get_count() const/*{{{*/
template<typename E, typename D>
inline size_t
alSubsetCollection<E, D>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alAssociatesCollection<E, A, D> implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alAssociatesCollection<E, A, D>::create_driver(const alCollection<E>& elements, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline typename alCollection<A>::Driver*
alAssociatesCollection<E, A, D>::create_driver(const alCollection<E>&     elements,
                        const alAccessor<E, A, D>& accessor)
{
    return new Driver(elements, accessor);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAssociatesCollection<E, A, D>::Driver implementation                                          //
//                                                                                                //

#ifndef DOXYGEN
//alAssociatesCollection<E, A, D>::Driver::Driver(const alCollection<E>& elements, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline
alAssociatesCollection<E, A, D>::Driver::Driver(const alCollection<E>&     elements,
                          const alAccessor<E, A, D>& accessor)
  : Inherit()
  , _elements(elements)
  , _accessor(accessor)
{
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename A, typename D>
inline
alAssociatesCollection<E, A, D>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
  , _accessor(driver._accessor)
{
}
/*}}}*/

//alAssociatesCollection<O, E>::Driver::is_random_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_unique_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_associative_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_reversible_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access() && _accessor.is_dynamic_access();
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::is_sized() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesCollection<E, A, D>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
inline typename alCollection<A>::Driver*
alAssociatesCollection<E, A, D>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E, typename A, typename D>
inline alIterator<A>
alAssociatesCollection<E, A, D>::Driver::get_iterator(size_t index) const
{
    return alAssociatesIterator<E, A, D>::create_driver(_elements.get_iterator(index), _accessor);
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E, typename A, typename D>
inline alIterator<A>
alAssociatesCollection<E, A, D>::Driver::get_reverse_iterator(size_t index) const
{
    return alAssociatesIterator<E, A, D>::create_driver(_elements.get_reverse_iterator(index), _accessor);
}
/*}}}*/

//alAssociateCollection<E, A, D>::Driver::find(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
inline alIterator<A>
alAssociatesCollection<E, A, D>::Driver::find(const A& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alAssociatesCollection<E, A, D>::Driver::get_count() const/*{{{*/
template<typename E, typename A, typename D>
inline size_t
alAssociatesCollection<E, A, D>::Driver::get_count() const
{
    return _elements.get_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alCollect1Collection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollect1Collection<E>::create_driver(const E& first)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect1Collection<E>::create_driver(const E& first)
{
    return new Driver(first);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect1Collection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollect1Collection<E>::Driver::Driver(const E& first)/*{{{*/
template<typename E>
inline
alCollect1Collection<E>::Driver::Driver(const E& first)
  : Inherit()
  , _first(first)
{
}
/*}}}*/

//alCollect1Collection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect1Collection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
{
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_unique_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_associative_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollect1Collection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alCollect1Collection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect1Collection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect1Collection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect1Collection<E>::Driver::get_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect1Collection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect1Collection<E>::Driver::get_reverse_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect1Collection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect1Collection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCollect1Collection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollect1Collection<E>::Driver::get_count() const
{
    return 1;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alCollect2Collection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollect2Collection<E>::create_driver(const E& first, const E& second)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect2Collection<E>::create_driver(const E& first, const E& second)
{
    return new Driver(first, second);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect2Collection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollect2Collection<E>::Driver::Driver(const E& first, const E& second)/*{{{*/
template<typename E>
inline
alCollect2Collection<E>::Driver::Driver(const E& first, const E& second)
  : Inherit()
  , _first(first)
  , _second(second)
{
}
/*}}}*/

//alCollect2Collection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect2Collection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
{
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect2Collection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollect2Collection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alCollect2Collection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect2Collection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect2Collection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect2Collection<E>::Driver::get_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect2Iterator<E>::create_driver(_first, _second);
        case 1: return alCollect1Iterator<E>::create_driver(_second);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect2Collection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect2Collection<E>::Driver::get_reverse_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect2Iterator<E>::create_driver(_second, _first);
        case 1: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect2Collection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect2Collection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCollect2Collection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollect2Collection<E>::Driver::get_count() const
{
    return 2;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alCollect3Collection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollect3Collection<E>::create_driver(const E& first, const E& second, const E& third)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect3Collection<E>::create_driver(const E& first, const E& second, const E& third)
{
    return new Driver(first, second, third);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect3Collection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollect3Collection<E>::Driver::Driver(const E& first, const E& second, const E& third)/*{{{*/
template<typename E>
inline
alCollect3Collection<E>::Driver::Driver(const E& first, const E& second, const E& third)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
{
}
/*}}}*/

//alCollect3Collection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect3Collection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
{
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect3Collection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollect3Collection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alCollect3Collection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect3Collection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect3Collection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect3Collection<E>::Driver::get_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect3Iterator<E>::create_driver(_first, _second, _third);
        case 1: return alCollect2Iterator<E>::create_driver(_second, _third);
        case 2: return alCollect1Iterator<E>::create_driver(_third);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect3Collection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect3Collection<E>::Driver::get_reverse_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect3Iterator<E>::create_driver(_third, _second, _first);
        case 1: return alCollect2Iterator<E>::create_driver(_second, _first);
        case 2: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect3Collection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect3Collection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCollect3Collection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollect3Collection<E>::Driver::get_count() const
{
    return 3;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alCollect4Collection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollect4Collection<E>::create_driver(const E& first, const E& second, const E& third, const E& fourth)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect4Collection<E>::create_driver
        (const E& first, const E& second, const E& third, const E& fourth)
{
    return new Driver(first, second, third, fourth);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect4Collection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollect4Collection<E>::Driver::Driver(const E& first, const E& second, const E& third, const E& fourth)/*{{{*/
template<typename E>
inline
alCollect4Collection<E>::Driver::Driver
        (const E& first, const E& second, const E& third, const E& fourth)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
  , _fourth(fourth)
{
}
/*}}}*/

//alCollect4Collection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect4Collection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
  , _fourth(driver._fourth)
{
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect4Collection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollect4Collection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alCollect4Collection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect4Collection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect4Collection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect4Collection<E>::Driver::get_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect4Iterator<E>::create_driver(_first, _second, _third, _fourth);
        case 1: return alCollect3Iterator<E>::create_driver(_second, _third, _fourth);
        case 2: return alCollect2Iterator<E>::create_driver(_third, _fourth);
        case 3: return alCollect1Iterator<E>::create_driver(_fourth);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect4Collection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect4Collection<E>::Driver::get_reverse_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect4Iterator<E>::create_driver(_fourth, _third, _second, _first);
        case 1: return alCollect3Iterator<E>::create_driver(_third, _second, _first);
        case 2: return alCollect2Iterator<E>::create_driver(_second, _first);
        case 3: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect4Collection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect4Collection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCollect4Collection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollect4Collection<E>::Driver::get_count() const
{
    return 4;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alCollect5Collection<E> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alCollect5Collection<E>::create_driver(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect5Collection<E>::create_driver
        (const E& first, const E& second, const E& third, const E& fourth, const E& fifth)
{
    return new Driver(first, second, third, fourth, fifth);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect5Collection<E>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alCollect5Collection<E>::Driver::Driver(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)/*{{{*/
template<typename E>
inline
alCollect5Collection<E>::Driver::Driver
        (const E& first, const E& second, const E& third, const E& fourth, const E& fifth)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
  , _fourth(fourth)
  , _fifth(fifth)
{
}
/*}}}*/

//alCollect5Collection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect5Collection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
  , _fourth(driver._fourth)
  , _fifth(driver._fifth)
{
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_random_access() const
{
    return true;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_reversible_access() const
{
    return true;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect5Collection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCollect5Collection<E>::Driver::is_sized() const
{
    return true;
}
/*}}}*/

//alCollect5Collection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCollect5Collection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect5Collection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect5Collection<E>::Driver::get_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect5Iterator<E>::create_driver(_first, _second, _third, _fourth, _fifth);
        case 1: return alCollect4Iterator<E>::create_driver(_first, _second, _third, _fourth);
        case 2: return alCollect3Iterator<E>::create_driver(_second, _third, _fourth);
        case 3: return alCollect2Iterator<E>::create_driver(_third, _fourth);
        case 4: return alCollect1Iterator<E>::create_driver(_fourth);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect5Collection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect5Collection<E>::Driver::get_reverse_iterator(size_t index) const
{
    switch (index) {
        case 0: return alCollect5Iterator<E>::create_driver(_fifth, _fourth, _third, _second, _first);
        case 1: return alCollect4Iterator<E>::create_driver(_fourth, _third, _second, _first);
        case 2: return alCollect3Iterator<E>::create_driver(_third, _second, _first);
        case 3: return alCollect2Iterator<E>::create_driver(_second, _first);
        case 4: return alCollect1Iterator<E>::create_driver(_first);
        default: return alIterator<E> ();
    }
}
/*}}}*/

//alCollect5Collection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCollect5Collection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCollect5Collection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCollect5Collection<E>::Driver::get_count() const
{
    return 5;
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alReverseCollection<E> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alReverseCollection<E>::create_driver(const alCollection<E>& elements)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alReverseCollection<E>::create_driver(const alCollection<E>& elements)
{
    return new Driver(elements);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReverseCollection<E>::Driver implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alReverseCollection<E>::Driver::Driver(const alCollection<E>& elements)/*{{{*/
template<typename E>
inline
alReverseCollection<E>::Driver::Driver(const alCollection<E>& elements)
  : Inherit()
  , _elements(elements)
{
}
/*}}}*/

//alReverseCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alReverseCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _elements(driver._elements)
{
}
/*}}}*/

//alReverseCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_random_access() const
{
    return _elements.is_random_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_unique_access() const
{
    return _elements.is_unique_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_associative_access() const
{
    return _elements.is_associative_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_reversible_access() const
{
    return _elements.is_reversible_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_dynamic_access() const
{
    return _elements.is_dynamic_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_mutable_access() const
{
    return _elements.is_mutable_access();
}
/*}}}*/

//alReverseCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alReverseCollection<E>::Driver::is_sized() const
{
    return _elements.is_sized();
}
/*}}}*/
//alReverseCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alReverseCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alReverseCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alReverseCollection<E>::Driver::get_iterator(size_t index) const
{
    return _elements.get_reverse_iterator(index);
}
/*}}}*/

//alReverseCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alReverseCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return _elements.get_iterator(index);
}
/*}}}*/

//alReverseCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alReverseCollection<E>::Driver::find(const E& element) const
{
    return alReverseIterator<E>::create_driver(_elements.find(element));
}
/*}}}*/

//alReverseCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alReverseCollection<E>::Driver::get_count() const
{
    return _elements.get_count();
}
/*}}}*/

#endif // DOXYGEN


//                                                                                                //
//  alReduceCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alReduceCollection<E>::create_driver(const alCollection<E>& collection)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alReduceCollection<E>::create_driver(const alCollection<E>& collection)
{
    return new Driver(collection);
}
/*}}}*/

//alReduceCollection<E>::create_driver(const alCollection<E>& collection, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E>
template<typename A, typename D>
inline typename alCollection<E>::Driver*
alReduceCollection<E>::create_driver(const alCollection<E>&     collection,
                  const alAccessor<E, A, D>& accessor)
{
    return new AssociateDriver<A, D>(collection, accessor);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReduceCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alReduceCollection<E>::Driver::Driver(const alCollection<E>& collection)/*{{{*/
template<typename E>
inline
alReduceCollection<E>::Driver::Driver(const alCollection<E>& collection)
  : Inherit()
  , _collection(collection)
{
}
/*}}}*/

//alReduceCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alReduceCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _collection(driver._collection)
{
}
/*}}}*/

//alReduceCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_unique_access() const
{
    return true;
}
/*}}}*/

//alReduceCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_associative_access() const
{
    return _collection.is_associative_access();
}
/*}}}*/

//alReduceCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_mutable_access() const
{
    return _collection.is_mutable_access();
}
/*}}}*/

//alReduceCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_dynamic_access() const
{
    return _collection.is_dynamic_access();
}
/*}}}*/

//alReduceCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alReduceCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alReduceCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alReduceCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alReduceCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alReduceIterator<E>::create_driver(_collection.get_iterator(0)), index);
}
/*}}}*/

//alReduceCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alReduceCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    // TODO : create a ReduceReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alReduceCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alReduceCollection<E>::Driver::find(const E& element) const
{
    return _collection.find(element);
}
/*}}}*/

//alReduceCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alReduceCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  alReduceCollection<E>::AssociateDriver<A, D> implementation                                     //
//                                                                                                //

#ifndef DOXYGEN
//alReduceCollection<E>::AssociateDriver<A, D>::AssociateDriver(const alCollection<E>& collection, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E>
template<typename A, typename D>
inline
alReduceCollection<E>::AssociateDriver<A, D>::AssociateDriver(const alCollection<E>&     collection,
                                const alAccessor<E, A, D>& accessor)
  : Inherit()
  , _collection(collection)
  , _accessor(accessor)
{
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::AssociateDriver(const AssociateDriver& driver)/*{{{*/
template<typename E>
template<typename A, typename D>
inline
alReduceCollection<E>::AssociateDriver<A, D>::AssociateDriver(const AssociateDriver& driver)
  : Inherit()
  , _collection(driver._collection)
  , _accessor(driver._accessor)
{
}
/*}}}*/


//alReduceCollection<E>::AssociateDriver<A, D>::is_random_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_random_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_unique_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_unique_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_associative_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_associative_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_reversible_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_reversible_access() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_mutable_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_mutable_access() const
{
    return _collection.is_mutable_access();
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_dynamic_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_dynamic_access() const
{
    return _collection.is_dynamic_access() && _accessor.is_dynamic_access();
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::is_sized() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceCollection<E>::AssociateDriver<A, D>::is_sized() const
{
    return false;
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::create_clone() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline typename alCollection<E>::Driver*
alReduceCollection<E>::AssociateDriver<A, D>::create_clone() const
{
    return new AssociateDriver(*this);
}
/*}}}*/

//alReduceCollection<E>::AssociateDriver<A, D>::get_iterator(size_t index) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alIterator<E>
alReduceCollection<E>::AssociateDriver<A, D>::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alReduceIterator<E>::create_driver(_collection.get_iterator(0), _accessor), index);
}
/*}}}*/

//alReduceCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alIterator<E>
alReduceCollection<E>::AssociateDriver<A, D>::get_reverse_iterator(size_t index) const
{
    // TODO : create a ReduceReverseIterator
    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alReduceCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
template<typename A, typename D>
inline alIterator<E>
alReduceCollection<E>::AssociateDriver<A, D>::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alReduceCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline size_t
alReduceCollection<E>::AssociateDriver<A, D>::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN


//                                                                                                //
//  alAppendCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alAppendCollection<E>::create_driver(const alCollection<E>& head, const alCollection<E>& tail)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alAppendCollection<E>::create_driver(const alCollection<E>& head, const alCollection<E>& tail)
{
    return new Driver(head, tail);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAppendCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alAppendCollection<E>::Driver::Driver(const alCollection<E>& head, const alCollection<E>& tail)/*{{{*/
template<typename E>
inline
alAppendCollection<E>::Driver::Driver(const alCollection<E>& head, const alCollection<E>& tail)
  : Inherit()
  , _head(head)
  , _tail(tail)
{
}
/*}}}*/

//alAppendCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alAppendCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _head(driver._head)
  , _tail(driver._tail)
{
}
/*}}}*/

//alAppendCollection<E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_random_access() const
{
    return _head.is_random_access() && _tail.is_random_access();
}
/*}}}*/

//alAppendCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alAppendCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_associative_access() const
{
    return  _head.is_associative_access() && _tail.is_associative_access();
}
/*}}}*/

//alAppendCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_reversible_access() const
{
    return _head.is_reversible_access() && _tail.is_reversible_access();
}
/*}}}*/

//alAppendCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_mutable_access() const
{
    return _head.is_mutable_access() && _tail.is_mutable_access();
}
/*}}}*/

//alAppendCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_dynamic_access() const
{
    return _head.is_dynamic_access() && _tail.is_dynamic_access();
}
/*}}}*/

//alAppendCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alAppendCollection<E>::Driver::is_sized() const
{
    return _head.is_sized() && _tail.is_sized();
}
/*}}}*/

//alAppendCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alAppendCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAppendCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alAppendCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alAppendIterator<E>::create_driver(_head.get_iterator(0), _tail.get_iterator(0)), index);
}
/*}}}*/

//alAppendCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alAppendCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alAppendIterator<E>::create_driver(_tail.get_reverse_iterator(0), _head.get_reverse_iterator(0)), index);
}
/*}}}*/

//alAppendCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alAppendCollection<E>::Driver::find(const E& element) const
{
    alIterator<E> iterator = _head.find(element);
    if (iterator.is_valid())
        return iterator;
    else
        return _tail.find(element);
}
/*}}}*/

//alAppendCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alAppendCollection<E>::Driver::get_count() const
{
    return _head.get_count() + _tail.get_count();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenCollection<Es> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenCollection<Es>::create_driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline typename alCollection<typename Es::ElementType>::Driver*
alFlattenCollection<Es>::create_driver(const alCollection<Es>& collections)
{
    return new Driver(collections);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenCollection<Es>::Driver implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenCollection<Es>::Driver::Driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline
alFlattenCollection<Es>::Driver::Driver(const alCollection<Es>& collections)
  : Inherit()
  , _collections(collections)
{
}
/*}}}*/

//alFlattenCollection<Es>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename Es>
inline
alFlattenCollection<Es>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _collections(driver._collections)
{
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_random_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_unique_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_associative_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_reversible_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_reversible_access() const
{
    return _collections.is_reversible_access();
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_mutable_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_mutable_access() const
{
    return _collections.is_mutable_access();
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_dynamic_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_dynamic_access() const
{
    return _collections.is_dynamic_access();
}
/*}}}*/

//alFlattenCollection<Es>::Driver::is_sized() const/*{{{*/
template<typename Es>
inline bool
alFlattenCollection<Es>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alFlattenCollection<Es>::Driver::create_clone() const/*{{{*/
template<typename Es>
inline typename alCollection<typename alFlattenCollection<Es>::E>::Driver*
alFlattenCollection<Es>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alFlattenCollection<Es>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename Es>
inline alIterator<typename alFlattenCollection<Es>::E>
alFlattenCollection<Es>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alFlattenIterator<Es>::create_driver(_collections), index);
}
/*}}}*/

//alFlattenCollection<Es>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename Es>
inline alIterator<typename alFlattenCollection<Es>::E>
alFlattenCollection<Es>::Driver::get_reverse_iterator(size_t index) const
{
    return Inherit::eval_iterator(alFlattenReverseIterator<Es>::create_driver(_collections), index);
}
/*}}}*/

//alFlattenCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename Es>
inline alIterator<typename alFlattenCollection<Es>::E>
alFlattenCollection<Es>::Driver::find(const E& element) const
{
    alIterator<Es> iterator = _collections.get_iterator(0);

    while (iterator.is_valid()) {
        alIterator<E> elem_iterator = iterator.get_current().find(element);
        if (elem_iterator.is_valid())
            return elem_iterator;
        iterator.progress();
    }

    return alIterator<E> ();
}
/*}}}*/

//alFlattenCollection<Es>::Driver::get_count() const/*{{{*/
template<typename Es>
inline size_t
alFlattenCollection<Es>::Driver::get_count() const
{
    size_t count = 0;

    alIterator<Es> iterator = _collections.get_iterator(0);

    while (iterator.is_valid()) {
        count += iterator.get_current().get_count();
        iterator.progress();
    }

    return count;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCustomCollection<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCustomCollection<E>::create_driver(const E& first, const alAccessor<E, E>& get_next, const E& before, const alAccessor<E, E>& get_previous)/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCustomCollection<E>::create_driver(const E&                      first,
                  const alAccessor<E, E>& get_next,
                  const E&                      before,
                  const alAccessor<E, E>& get_previous)
{
    return new Driver(first, get_next, before, get_previous);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCustomCollection<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCustomCollection<E>::Driver::Driver(const E& first, const alAccessor<E, E>& get_next, const E& before, const alAccessor<E, E>& get_previous)/*{{{*/
template<typename E>
inline
alCustomCollection<E>::Driver::Driver(const E&                      first,
                    const alAccessor<E, E>& get_next,
                    const E&                      before,
                    const alAccessor<E, E>& get_previous)
  : Inherit()
  , _first(first)
  , _next(get_next)
  , _before(before)
  , _previous(get_previous)
{
}
/*}}}*/

//alCustomCollection<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCustomCollection<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _next(driver._next)
  , _before(driver._before)
  , _previous(driver._previous)
{
}
/*}}}*/

//alCustomCollection<O, E>::Driver::is_random_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_random_access() const
{
    return false;
}
/*}}}*/

//alCustomCollection<E>::Driver::is_unique_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_unique_access() const
{
    return false;
}
/*}}}*/

//alCustomCollection<E>::Driver::is_associative_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_associative_access() const
{
    return false;
}
/*}}}*/

//alCustomCollection<E>::Driver::is_reversible_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_reversible_access() const
{
    return (_previous.is_driven()) ;
}
/*}}}*/

//alCustomCollection<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alCustomCollection<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_dynamic_access() const
{
    return _next.is_dynamic_access();
}
/*}}}*/

//alCustomCollection<E>::Driver::is_sized() const/*{{{*/
template<typename E>
inline bool
alCustomCollection<E>::Driver::is_sized() const
{
    return false;
}
/*}}}*/

//alCustomCollection<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alCollection<E>::Driver*
alCustomCollection<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCustomCollection<E>::Driver::get_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCustomCollection<E>::Driver::get_iterator(size_t index) const
{
    return Inherit::eval_iterator(alCustomIterator<E>::create_driver(_first, _next, _before), index);
}
/*}}}*/

//alCustomCollection<E>::Driver::get_reverse_iterator(size_t index) const/*{{{*/
template<typename E>
inline alIterator<E>
alCustomCollection<E>::Driver::get_reverse_iterator(size_t index) const
{
    if (_previous.is_driven()) {
        return Inherit::eval_iterator(alCustomIterator<E>::create_driver(_previous.get_associate(_before), _previous, _previous.get_associate(_first)), index);
    }

    return Inherit::eval_reverse_iterator(index);
}
/*}}}*/

//alCustomCollection<E>::Driver::find(const E& element) const/*{{{*/
template<typename E>
inline alIterator<E>
alCustomCollection<E>::Driver::find(const E& element) const
{
    return Inherit::eval_find(element);
}
/*}}}*/

//alCustomCollection<E>::Driver::get_count() const/*{{{*/
template<typename E>
inline size_t
alCustomCollection<E>::Driver::get_count() const
{
    return Inherit::eval_count();
}
/*}}}*/

#endif // DOXYGEN



//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the definitions of the alCollection and alCollection::Driver classes
        and the corresponding generic functions and macros.
    */

/*!\define    COLLECTION(alCollectionType, ElementType)
    \paragraph    Behaviour:
    \m    This macro should be used to declare a new type of collection.
    \p    The goal is to override some members in the declaration body to extend the
        automatic promotion or filtering for the new class.
    \param    alCollectionType    The type of the new collection.
    \param    ElementType    The type of the elements handled by the collection.
    \paragraph    Examples:
    \m    To declare a collection handling objects managed by pointers you need to write:
    \code
        * class Shapes : public alCollection<Shape*> {
        *
        *    COLLECTION(Shapes, Shape*);
        *
        * }
        \endcode
    \m    And to declare a collection handling objects managed by copy you need to write:
    \code
        * class Points : public alCollection<Point> {
        *
        *    COLLECTION(Points, Point);
        *
        * }
        \endcode
    \paragraph    Remark:
    \m    The simplest way to declare a new type of collection is to write:
    \code
        * typedef alCollection<Shape*> Shapes;
        \endcode
    \m    or:
    \code
        * typedef alCollection<Point> Points;
        \endcode
    \m    But a more powerfull way is to declare a new class. You can then declare additional
        members (constructors, accessors, ...) as illustrated in the following example:
    \code
        * class Points : public alCollection<Point> {
        *
        *    COLLECTION(Points, Point);
        *
        *    public:
        *                       Points(const Box& box);
        *                       Points(const Polygon* polygon);
        *
        *    public:
        *        Units          get_ordinates() const;
        *        Point          get_barycenter() const;
        *        Box            get_bounding_box() const;
        *        Points         get_insides(const Box& area) const;
        *
        * }
        \endcode
    */

/*!\define    for_each(Type, current, data)
    \paragraph    Behaviour:
    \m    This macro can be used to visit all the elements of a collection.
    \param    Type    The type of the elements to visit.
    \param    current    The name of the variable which is bound, in each step, to the current
            element.
    \param    data    Can be anything from which a collection of elements can be created.
    \paragraph    Usages:
    \code
        * for_each (Shape*, shape, get_shapes()) {
        *     // using shape here...
        * }
        \endcode
    \m    or:
    \code
        * for_each (Point, point, polygon->get_points()) {
        *     // using point here...
        * }
        \endcode
    \paragraph    Remark:
    \m    Depending to the specified type and the type of the elements of the specified
        collection, an automatic promotion or filtering is done.
    \code
        * for_each (Polygon*, polygon, get_shapes()) {
        *     // only the subset of polygons of the shapes will be visited
        * }
        \endcode
    */

/*!\define    for_each_consecutive(Type, current, next, data)
    \paragraph    Behaviour:
    \m    This macro can be used to visit all the consecutive elements of a collection.
    \param    Type    The type of the elements to visit.
    \param    current    The name of the variable which is bound, in each step, to the current
            element.
    \param    next    The name of the variable which is bound, in each step, to the element
            following the current element.
    \param    data    Can be anything from which a collection of elements can be created.
    \paragraph    Usage:
    \code
        * void View::drawPolyline(const Points& points)
        * {
        *     for_each_consecutive (Point, source, target, points) {
        *         drawLine(source, target);
        *     }
        * }
        \endcode
    \paragraph    Remark:
    \m    Depending to the specified type and the type of the elements of the specified
        collection, an automatic promotion or filtering is done.
    */

/*!\define    for_each_parallel(Type1, current1, data1, Type2, current2, data2)
    \paragraph    Behaviour:
    \m    This macro can be used to visit in parallel all the elements of the collections.
    \param    Type1        The type of the elements to visit in the first collection.
    \param    current1    The name of the variable which is bound, in each step, to the current
                element of the first collection.
    \param    data1        Can be anything from which the first collection can be created.
    \param    Type2        The type of the elements to visit in the second collection.
    \param    current2    The name of the variable which is bound, in each step, to the current
                element of the second collection.
    \param    data2        Can be anything from which the second collection can be created.
    \paragraph    Usage:
    \code
        * void Instance::connect(const Nets& nets)
        * {
        *     for_each_parallel (Pin*, pin, instance->get_pins(), Net*, net, nets) {
        *         pin->connect(net);
        *     }
        * }
        \endcode
    \paragraph    Note:
    \m    The visit stops when one of the two specified collections has exhausted all its
        elements.
    \paragraph    Remark:
    \m    Depending to the specified types and the types of the elements of the specified
        collections, an automatic promotion or filtering is done.
    */
/*}}}*/

//class alCollection<E>/*{{{*/
/*!\class    alCollection
    \brief    This concrete class implements the concept of \em "collection".
    */
/*}}}*/

//class alCollection<E>::Driver/*{{{*/
/*!\class    alCollection::Driver
    \brief    This abstract class introduces the concept of \em "collection driver".
    */
/*}}}*/

#endif

//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
