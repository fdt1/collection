//                                                                                                //
//  File: misc_collection_iterator.h                                                                              //
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

#include <misc/misc_collection_accessor.h>
#include <misc/misc_collection_predicate.h>
#include <xut/xtree.h>
#include <set>

namespace misc {

template<typename E> class alCollection;
/*}}}*/



//                                                                                                //
//  alIterator declaration                                                                          //
//                                                                                                //

//class alIterator<E>/*{{{*/
template<typename E>
class alIterator {

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
    //!\name Predicates:
    //@{
    virtual bool                is_valid() const PURE;
    virtual bool                is_mutable_access() const PURE;
    virtual bool                is_dynamic_access() const PURE;
    //@}

      public:
    //!\name alAccessors:
    //@{
    virtual Driver*                create_clone() const PURE;
    virtual E                get_current() const PURE;
    //@}

      public:
    //!\name Updators:
    //@{
    virtual void                progress() PURE;
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

  public:
    //!\name Destructor:
    //@{
                    ~alIterator();
    //@}

  public:
    //!\name Default Constructor:
    //@{
                    alIterator(Driver* driver = NULL);
    //@}

  public:
    //!\name Copy Constructor:
    //@{
                    alIterator(const alIterator<E>& iterator);
    //@}

  public:
    //! alCollection Constructor (OpenAccess like):
    //@{
                    alIterator(const alCollection<E>& collection);
    //@}

  public:
    //!\name Assignment Operators:
    //@{
        alIterator<E>&        operator=(Driver* driver);
        alIterator<E>&        operator=(const alIterator<E>& iterator);
    //@}

  public:
    //!\name Functional Operators:
    //@{
        bool            operator()() const;
    //@}

  public:
    //!\name Dereferencing Operators:
    //@{
        E                operator*() const;
    //@}

  public:
    //!\name Incrementation Operators:
    //@{
        alIterator<E>&        operator++();    // ++iterator
        alIterator<E>            operator++(int); // iterator++
    //@}

  public:
    //!\name alPredicates:
    //@{
        bool            is_valid() const;
        bool            is_driven() const;
        //! return true if we can modified the data of the iterator
        bool            is_mutable_access() const;
        //! return true if iterator supports dynamic modifications on datas
        bool            is_dynamic_access() const;
    //@}

  public:
    //!\name alAccessors:
    //@{
        Driver*            get_driver() const;
        E                get_current() const;
    //@}

  public:
    //!\name Updators:
    //@{
        E                get_next(); //Caution: OpenAccess style
        alIterator<E>&        progress();
    //@}

  #ifndef DOXYGEN
  private:
        Driver*            _driver;
  #endif // DOXYGEN

};
/*}}}*/



//                                                                                                //
//  Specialized iterators                                                                         //
//                                                                                                //

#ifndef DOXYGEN
//class alTypeIterator<O, E>/*{{{*/
template<typename O, typename E>
class alTypeIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<O>& alobjectIterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<O>                _object_iterator;

      public:
                            Driver(const alIterator<O>& alobjectIterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alListIterator<E>/*{{{*/
template<typename E>
class alListIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::list<E>& elementList);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::list<E>&                _element_list;
        typename std::list<E>::const_iterator    _iterator;

      public:
                            Driver(const std::list<E>& elementList);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alListReverseIterator<E>/*{{{*/
template<typename E>
class alListReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::list<E>& elementList);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::list<E>&                _element_list;
        typename
        std::list<E>::const_reverse_iterator        _iterator;

      public:
                            Driver(const std::list<E>& elementList);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alSetIterator<E, C>/*{{{*/
template<typename E, typename C>
class alSetIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::set<E, C>& elementSet);
    static  typename alIterator<E>::Driver*    create_driver(const std::set<E, C>& elementSet, const typename std::set<E, C>::const_iterator& iterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::set<E, C>&            _element_set;
        typename std::set<E, C>::const_iterator  _iterator;

      public:
                            Driver(const std::set<E, C>& elementSet);
                            Driver(const std::set<E, C>& elementSet, const typename std::set<E, C>::const_iterator& iterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alSetReverseIterator<E, C>/*{{{*/
template<typename E, typename C>
class alSetReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::set<E, C>& elementSet);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::set<E, C>&            _element_set;
        typename
        std::set<E, C>::const_reverse_iterator   _iterator;

      public:
                            Driver(const std::set<E, C>& elementSet);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alXtreeIterator<K, E, A, C>/*{{{*/
// xtree<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Value> >
template<typename K, typename E, typename A, typename C>
class alXtreeIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const xtree<K, E, A, C>& elementXtree);
    static  typename alIterator<E>::Driver*    create_driver(const xtree<K, E, A, C>& elementXtree, const typename xtree<K, E, A, C>::const_iterator& iterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const xtree<K, E, A, C>&            _element_tree;
        typename xtree<K, E, A, C>::const_iterator  _iterator;

      public:
                            Driver(const xtree<K, E, A, C>& elementXtree);
                            Driver(const xtree<K, E, A, C>& elementXtree, const typename xtree<K, E, A, C>::const_iterator& iterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alXtreeReverseIterator<E, C>/*{{{*/
template<typename K, typename E, typename A, typename C>
class alXtreeReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const xtree<K, E, A, C>& elementXtree);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const xtree<K, E, A, C>&            _element_tree;
        typename
        xtree<K, E, A, C>::const_reverse_iterator   _iterator;

      public:
                            Driver(const xtree<K, E, A, C>& elementXtree);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alVectorIterator<E>/*{{{*/
template<typename E>
class alVectorIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::vector<E>& elementVector, size_t index);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::vector<E>&            _element_vector;
        typename std::vector<E>::const_iterator  _iterator;

      public:
                            Driver(const std::vector<E>& elementVector, size_t index);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alVectorReverseIterator<E>/*{{{*/
template<typename E>
class alVectorReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::vector<E>& elementVector, size_t index);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::vector<E>&            _element_vector;
        typename
        std::vector<E>::const_reverse_iterator   _iterator;

      public:
                            Driver(const std::vector<E>& elementVector, size_t index);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alMapIterator<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alMapIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::map<K, E, C>& elementMap);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;
        typename std::map<K,E,C>::const_iterator _iterator;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alMapReverseIterator<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alMapReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const std::map<K, E, C>& elementMap);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;
        typename
        std::map<K,E,C>::const_reverse_iterator  _iterator;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alKeyIterator<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alKeyIterator : public alIterator<K> {

  public:
    static  typename alIterator<K>::Driver*    create_driver(const std::map<K, E, C>& elementMap);
    static  typename alIterator<K>::Driver*    create_driver(const std::map<K, E, C>& elementMap, const typename std::map<K, E, C>::const_iterator& iterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<K>::Driver {

      public:
    typedef typename alIterator<K>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;
        typename
        std::map<K, E, C>::const_iterator        _iterator;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const std::map<K, E, C>& elementMap, const typename std::map<K, E, C>::const_iterator& iterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<K>::Driver*        create_clone() const;
    virtual K                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alKeyReverseIterator<K, E, C>/*{{{*/
template<typename K, typename E, typename C>
class alKeyReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<K>::Driver*    create_driver(const std::map<K, E, C>& elementMap);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<K>::Driver {

      public:
    typedef typename alIterator<K>::Driver        Inherit;

      private:
        const std::map<K, E, C>&            _element_map;
        typename
        std::map<K,E,C>::const_reverse_iterator  _iterator;

      public:
                            Driver(const std::map<K, E, C>& elementMap);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<K>::Driver*        create_clone() const;
    virtual K                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alOpenAccessIterator<O, C, E>/*{{{*/
template<typename O, typename C, typename E>
class alOpenAccessIterator;
/*}}}*/

//class alRandomAccessIterator<E>/*{{{*/
template<typename E>
class alRandomAccessIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const alRefCounter<std::vector<E> >      _element_vector_ref;
        typename std::vector<E>::const_iterator  _iterator;

      public:
                            Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alRandomAccessReverseIterator<E>/*{{{*/
template<typename E>
class alRandomAccessReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        const alRefCounter<std::vector<E> >            _element_vector_ref;
        typename
        std::vector<E>::const_reverse_iterator   _iterator;

      public:
                            Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alHeadIterator<E>/*{{{*/
template<typename E>
class alHeadIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 size_t             count);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        size_t                    _count;

      public:
                            Driver(const alIterator<E>& iterator,
                               size_t             count);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alTailIterator<E>/*{{{*/
template<typename E>
class alTailIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 size_t             startIndex);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        size_t                    _start_index;

      public:
                            Driver(const alIterator<E>& iterator,
                               size_t             startIndex);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alToIterator<E>/*{{{*/
template<typename E>
class alToIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 const E&           last);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        E                    _last;

      public:
                            Driver(const alIterator<E>& iterator,
                               const E&           last);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alFromIterator<E>/*{{{*/
template<typename E>
class alFromIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 const E&           first);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        E                    _first;

      public:
                            Driver(const alIterator<E>& iterator,
                               const E&           first);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alBeforeIterator<E>/*{{{*/
template<typename E>
class alBeforeIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 const E&           next);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        E                    _next;

      public:
                            Driver(const alIterator<E>& iterator,
                               const E&           next);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alAfterIterator<E>/*{{{*/
template<typename E>
class alAfterIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 const E&           previous);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        E                    _previous;

      public:
                            Driver(const alIterator<E>& iterator,
                               const E&           previous);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alNotIterator<E>/*{{{*/
template<typename E>
class alNotIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator,
                                 const E&           rejected);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        E                    _rejected;

      public:
                            Driver(const alIterator<E>& iterator,
                               const E&           rejected);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alSubsetIterator<E, D>/*{{{*/
template<typename E, typename D = bool>
class alSubsetIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>&     iterator,
                                 const alPredicate<E, D>& predicate);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        alPredicate<E, D>            _predicate;

      public:
                            Driver(const alIterator<E>&     iterator,
                               const alPredicate<E, D>& predicate);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alAssociatesIterator<E, A, D>/*{{{*/
template<typename E, typename A, typename D = bool>
class alAssociatesIterator : public alIterator<A> {

  public:
    static  typename alIterator<A>::Driver*    create_driver(const alIterator<E>&       iterator,
                                 const alAccessor<E, A, D>& accessor);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<A>::Driver {

      public:
    typedef typename alIterator<A>::Driver        Inherit;

      private:
        alIterator<E>                _iterator;
        alAccessor<E, A, D>            _accessor;

      public:
                            Driver(const alIterator<E>&       iterator,
                               const alAccessor<E, A, D>& accessor);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<A>::Driver*        create_clone() const;
    virtual A                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alReverseIterator<E>/*{{{*/
template<typename E>
class alReverseIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        std::list<E>                     _element_list;

      public:
                            Driver(const alIterator<E>& iterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCollect1Iterator<E>/*{{{*/
template<typename E>
class alCollect1Iterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E& first);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _first;
        size_t                    _index;

      public:
                            Driver(const E& first);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCollect2Iterator<E>/*{{{*/
template<typename E>
class alCollect2Iterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E& first, const E& second);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        size_t                    _index;

      public:
                            Driver(const E& first, const E& second);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCollect3Iterator<E>/*{{{*/
template<typename E>
class alCollect3Iterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;
        size_t                    _index;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCollect4Iterator<E>/*{{{*/
template<typename E>
class alCollect4Iterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third,
                                 const E& fourth);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;
        E                    _fourth;
        size_t                    _index;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third,
                               const E& fourth);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCollect5Iterator<E>/*{{{*/
template<typename E>
class alCollect5Iterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E& first,
                                 const E& second,
                                 const E& third,
                                 const E& fourth,
                                 const E& fifth);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _first;
        E                    _second;
        E                    _third;
        E                    _fourth;
        E                    _fifth;
        size_t                    _index;

      public:
                            Driver(const E& first,
                               const E& second,
                               const E& third,
                               const E& fourth,
                               const E& fifth);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alReduceIterator<E>/*{{{*/
template<typename E>
class alReduceIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& iterator);
    template<typename A, typename D>
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>&       iterator,
                                 const alAccessor<E, A, D>& accessor);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        std::set<E>                    _set;
        alIterator<E>                _iterator;

      public:
                            Driver(const alIterator<E>& iterator);
                            Driver(const Driver& driver);

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

    //class AssociateDriver/*{{{*/
    template<typename A, typename D>
    class AssociateDriver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        std::set<A>                    _set;
        alIterator<E>                _iterator;
        alAccessor<E, A, D>            _accessor;

      public:
                            AssociateDriver(
                            const alIterator<E>&       iterator,
                            const alAccessor<E, A, D>& accessor);
                            AssociateDriver(const AssociateDriver& driver);

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alAppendIterator<E>/*{{{*/
template<typename E>
class alAppendIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const alIterator<E>& alheadIterator,
                                 const alIterator<E>& altailIterator);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<E>                _head_iterator;
        alIterator<E>                _tail_iterator;

      public:
                            Driver(const alIterator<E>& alheadIterator,
                               const alIterator<E>& altailIterator);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alFlattenIterator<Es>/*{{{*/
template<typename Es>
class alFlattenIterator : public alIterator<typename Es::ElementType> {

  public:
    typedef typename Es::ElementType        E;

    static  typename alIterator<E>::Driver*    create_driver(const alCollection<Es>& collections);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<Es>                _primary_iterator;
        alIterator<E>                _secondary_iterator;

      public:
                            Driver(const alCollection<Es>& collections);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alFlattenReverseIterator<Es>/*{{{*/
template<typename Es>
class alFlattenReverseIterator : public alIterator<typename Es::ElementType> {

  public:
    typedef typename Es::ElementType        E;

    static  typename alIterator<E>::Driver*    create_driver(const alCollection<Es>& collections);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        alIterator<Es>                _primary_iterator;
        alIterator<E>                _secondary_iterator;

      public:
                            Driver(const alCollection<Es>& collections);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/

//class alCustomIterator<E>/*{{{*/
template<typename E>
class alCustomIterator : public alIterator<E> {

  public:
    static  typename alIterator<E>::Driver*    create_driver(const E&                      first,
                                 const alAccessor<E, E>& get_next,
                                 const E&                      before);

  public:
    //class Driver/*{{{*/
    class Driver : public alIterator<E>::Driver {

      public:
    typedef typename alIterator<E>::Driver        Inherit;

      private:
        E                    _current;
        E                    _before;
        alAccessor<E, E>     _next;

      public:
                            Driver(const E&                      first,
                               const alAccessor<E, E>& get_next,
                                 const E&                      before);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_valid() const;
    virtual bool                    is_mutable_access() const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alIterator<E>::Driver*        create_clone() const;
    virtual E                    get_current() const;

      public:
    virtual void                    progress();

    };
    /*}}}*/

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alIterator<E> implementation                                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alIterator<E>::~alIterator()/*{{{*/
template<typename E>
inline
alIterator<E>::~alIterator()
{
    if (is_driven()) {
        delete get_driver();
    }
}
/*}}}*/

//alIterator<E>::alIterator(Driver* driver)/*{{{*/
template<typename E>
inline
alIterator<E>::alIterator(Driver* driver)
  : _driver(driver)
{
}
/*}}}*/

//alIterator<E>::alIterator(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline
alIterator<E>::alIterator(const alIterator<E>& iterator)
  : _driver(iterator.is_driven() ? iterator.get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alCollection<E>::alCollection(const alCollection<E>& collection)/*{{{*/
template<typename E>
inline
alIterator<E>::alIterator(const alCollection<E>& collection)
  : _driver(collection.get_iterator().is_driven() ? collection.get_iterator().get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alIterator<E>::operator=(Driver* driver)/*{{{*/
template<typename E>
inline alIterator<E>&
alIterator<E>::operator=(Driver* driver)
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

//alIterator<E>::operator=(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline alIterator<E>&
alIterator<E>::operator=(const alIterator<E>& iterator)
{
    return operator=((iterator.is_driven()) ? iterator.get_driver()->create_clone() : NULL);
}
/*}}}*/

//alIterator<E>::operator()() const/*{{{*/
template<typename E>
inline bool
alIterator<E>::operator()() const
{
    return is_valid();
}
/*}}}*/

//alIterator<E>::operator*() const/*{{{*/
template<typename E>
inline E
alIterator<E>::operator*() const
{
    return get_current();
}
/*}}}*/

//alIterator<E>::operator++()/*{{{*/
template<typename E>
inline alIterator<E>&
alIterator<E>::operator++()
{
    return progress();
}
/*}}}*/

//alIterator<E>::operator++(int)/*{{{*/
template<typename E>
inline alIterator<E>
alIterator<E>::operator++(int)
{
    alIterator<E> iterator(*this);

    progress();

    return iterator;
}
/*}}}*/

//alIterator<E>::is_valid() const/*{{{*/
template<typename E>
inline bool
alIterator<E>::is_valid() const
{
    return is_driven() && get_driver()->is_valid();
}
/*}}}*/

//alIterator<E>::is_driven() const/*{{{*/
template<typename E>
inline bool
alIterator<E>::is_driven() const
{
    return (get_driver() != NULL);
}
/*}}}*/

//alIterator<E>::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alIterator<E>::is_mutable_access() const
{
    return is_driven() && get_driver()->is_mutable_access();
}
/*}}}*/

//alIterator<E>::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alIterator<E>::is_dynamic_access() const
{
    return is_driven() && get_driver()->is_dynamic_access();
}
/*}}}*/

//alIterator<E>::get_driver() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alIterator<E>::get_driver() const
{
    return _driver;
}
/*}}}*/

//alIterator<E>::get_current() const/*{{{*/
template<typename E>
inline E
alIterator<E>::get_current() const
{
    return (is_driven()) ? get_driver()->get_current() : E();
}
/*}}}*/

//alIterator<E>::get_next()/*{{{*/
template<typename E>
inline E
alIterator<E>::get_next()
{
    if (!is_valid()) {
        return E();
    }

    E current = get_current();

    progress();

    return current;
}
/*}}}*/

//alIterator<E>::progress()/*{{{*/
template<typename E>
inline alIterator<E>&
alIterator<E>::progress()
{
    if (is_driven()) {
        get_driver()->progress();
    }

    return *this;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alIterator<E>::Driver implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alIterator<E>::Driver::~Driver()/*{{{*/
template<typename E>
inline
alIterator<E>::Driver::~Driver()
{
}
/*}}}*/

//alIterator<E>::Driver::Driver()/*{{{*/
template<typename E>
inline
alIterator<E>::Driver::Driver()
{
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTypeIterator<O, E> implementation                                                             //
//                                                                                                //

#ifndef DOXYGEN
//alTypeIterator<O, E>::create_driver(const alIterator<O>& alobjectIterator)/*{{{*/
template<typename O, typename E>
inline typename alIterator<E>::Driver*
alTypeIterator<O, E>::create_driver(const alIterator<O>& alobjectIterator)
{
    return new Driver(alobjectIterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTypeIterator<O, E>::Driver implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alTypeIterator<O, E>::Driver::Driver(const alIterator<O>& alobjectIterator)/*{{{*/
template<typename O, typename E>
inline
alTypeIterator<O, E>::Driver::Driver(const alIterator<O>& alobjectIterator)
  : Inherit()
  , _object_iterator(alobjectIterator)
{
    while (_object_iterator.is_valid() && !dynamic_cast<E>(_object_iterator.get_current())) {
        _object_iterator.progress();
    }
}
/*}}}*/

//alTypeIterator<O, E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename O, typename E>
inline
alTypeIterator<O, E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _object_iterator(driver._object_iterator)
{
}
/*}}}*/

//alTypeIterator<O, E>::Driver::is_valid() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeIterator<O, E>::Driver::is_valid() const
{
    return _object_iterator.is_valid();
}
/*}}}*/

//alTypeIterator<O, E>::Driver::is_mutable_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeIterator<O, E>::Driver::is_mutable_access() const
{
    return _object_iterator.is_mutable_access();
}
/*}}}*/

//alTypeIterator<O, E>::Driver::is_dynamic_access() const/*{{{*/
template<typename O, typename E>
inline bool
alTypeIterator<O, E>::Driver::is_dynamic_access() const
{
    return _object_iterator.is_dynamic_access();
}
/*}}}*/

//alTypeIterator<O, E>::Driver::create_clone() const/*{{{*/
template<typename O, typename E>
inline typename alIterator<E>::Driver*
alTypeIterator<O, E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alTypeIterator<O, E>::Driver::get_current() const/*{{{*/
template<typename O, typename E>
inline E
alTypeIterator<O, E>::Driver::get_current() const
{
    return (_object_iterator.is_valid()) ? dynamic_cast<E>(_object_iterator.get_current()) : E();
}
/*}}}*/

//alTypeIterator<O, E>::Driver::progress()/*{{{*/
template<typename O, typename E>
inline void
alTypeIterator<O, E>::Driver::progress()
{
    if (_object_iterator.is_valid()) {
        do {
            _object_iterator.progress();
        } while (_object_iterator.is_valid() && !dynamic_cast<E>(_object_iterator.get_current()));
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alListIterator<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alListIterator<E>::create_driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alListIterator<E>::create_driver(const std::list<E>& elementList)
{
    return new Driver(elementList);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alListIterator<E>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alListIterator<E>::Driver::Driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline
alListIterator<E>::Driver::Driver(const std::list<E>& elementList)
  : Inherit()
  , _element_list(elementList)
  , _iterator(elementList.begin())
{
}
/*}}}*/

//alListIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alListIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_list(driver._element_list)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alListIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alListIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_list.end());
}
/*}}}*/

//alListIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alListIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alListIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alListIterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alListIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alListIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alListIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alListIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_list.end()) ? *_iterator : E();
}
/*}}}*/

//alListIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alListIterator<E>::Driver::progress()
{
    if (_iterator != _element_list.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alListReverseIterator<E> implementation                                                         //
//                                                                                                //

#ifndef DOXYGEN
//alListReverseIterator<E>::create_driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alListReverseIterator<E>::create_driver(const std::list<E>& elementList)
{
    return new Driver(elementList);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alListReverseIterator<E>::Driver implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alListReverseIterator<E>::Driver::Driver(const std::list<E>& elementList)/*{{{*/
template<typename E>
inline
alListReverseIterator<E>::Driver::Driver(const std::list<E>& elementList)
  : Inherit()
  , _element_list(elementList)
  , _iterator(elementList.rbegin())
{
}
/*}}}*/

//alListReverseIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alListReverseIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_list(driver._element_list)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alListReverseIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alListReverseIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_list.rend());
}
/*}}}*/

//alListReverseIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alListReverseIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alListReverseIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alListReverseIterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alListReverseIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alListReverseIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alListReverseIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alListReverseIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_list.rend()) ? *_iterator : E();
}
/*}}}*/

//alListReverseIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alListReverseIterator<E>::Driver::progress()
{
    if (_iterator != _element_list.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSetIterator<E, C> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alSetIterator<E, C>::create_driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline typename alIterator<E>::Driver*
alSetIterator<E, C>::create_driver(const std::set<E, C>& elementSet)
{
    return new Driver(elementSet);
}
/*}}}*/

//alSetIterator<E, C>::create_driver(const std::set<E, C>& elementSet, const typename std::set<E, C>::const_iterator& iterator)/*{{{*/
template<typename E, typename C>
inline typename alIterator<E>::Driver*
alSetIterator<E, C>::create_driver(const std::set<E, C>& elementSet, const typename std::set<E, C>::const_iterator& iterator)
{
    return new Driver(elementSet, iterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSetIterator<E, C>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alSetIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline
alSetIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet)
  : Inherit()
  , _element_set(elementSet)
  , _iterator(elementSet.begin())
{
}
/*}}}*/

//alSetIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet, typename std::set<E, C>::const_iterator iterator)/*{{{*/
template<typename E, typename C>
inline
alSetIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet, const typename std::set<E, C>::const_iterator& iterator)
  : Inherit()
  , _element_set(elementSet)
  , _iterator(iterator)
{
}
/*}}}*/

//alSetIterator<E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename C>
inline
alSetIterator<E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_set(driver._element_set)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alSetIterator<E, C>::Driver::is_valid() const/*{{{*/
template<typename E, typename C>
inline bool
alSetIterator<E, C>::Driver::is_valid() const
{
    return (_iterator != _element_set.end());
}
/*}}}*/

//alSetIterator<E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetIterator<E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alSetIterator<E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetIterator<E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSetIterator<E, C>::Driver::create_clone() const/*{{{*/
template<typename E, typename C>
inline typename alIterator<E>::Driver*
alSetIterator<E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alSetIterator<E, C>::Driver::get_current() const/*{{{*/
template<typename E, typename C>
inline E
alSetIterator<E, C>::Driver::get_current() const
{
    return (_iterator != _element_set.end()) ? *_iterator : E();
}
/*}}}*/

//alSetIterator<E, C>::Driver::progress()/*{{{*/
template<typename E, typename C>
inline void
alSetIterator<E, C>::Driver::progress()
{
    if (_iterator != _element_set.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSetReverseIterator<E, C> implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alSetReverseIterator<E, C>::create_driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline typename alIterator<E>::Driver*
alSetReverseIterator<E, C>::create_driver(const std::set<E, C>& elementSet)
{
    return new Driver(elementSet);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSetReverseIterator<E, C>::Driver implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alSetReverseIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet)/*{{{*/
template<typename E, typename C>
inline
alSetReverseIterator<E, C>::Driver::Driver(const std::set<E, C>& elementSet)
  : Inherit()
  , _element_set(elementSet)
  , _iterator(elementSet.rbegin())
{
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename C>
inline
alSetReverseIterator<E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_set(driver._element_set)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::is_valid() const/*{{{*/
template<typename E, typename C>
inline bool
alSetReverseIterator<E, C>::Driver::is_valid() const
{
    return (_iterator != _element_set.rend());
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetReverseIterator<E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename C>
inline bool
alSetReverseIterator<E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::create_clone() const/*{{{*/
template<typename E, typename C>
inline typename alIterator<E>::Driver*
alSetReverseIterator<E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::get_current() const/*{{{*/
template<typename E, typename C>
inline E
alSetReverseIterator<E, C>::Driver::get_current() const
{
    return (_iterator != _element_set.rend()) ? *_iterator : E();
}
/*}}}*/

//alSetReverseIterator<E, C>::Driver::progress()/*{{{*/
template<typename E, typename C>
inline void
alSetReverseIterator<E, C>::Driver::progress()
{
    if (_iterator != _element_set.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alXtreeIterator<E, C> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alIterator<E>::Driver*
alXtreeIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree)
{
    return new Driver(elementXtree);
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree, const typename xtree<K, E, A, C>::const_iterator& iterator)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alIterator<E>::Driver*
alXtreeIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree, const typename xtree<K, E, A, C>::const_iterator& iterator)
{
    return new Driver(elementXtree, iterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alXtreeIterator<K, E, A, C>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)
  : Inherit()
  , _element_tree(elementXtree)
  , _iterator(elementXtree.begin())
{
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree, typename xtree<K, E, A, C>::const_iterator iterator)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree, const typename xtree<K, E, A, C>::const_iterator& iterator)
  : Inherit()
  , _element_tree(elementXtree)
  , _iterator(iterator)
{
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeIterator<K, E, A, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_tree(driver._element_tree)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeIterator<K, E, A, C>::Driver::is_valid() const
{
    return (_iterator != _element_tree.end());
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeIterator<K, E, A, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeIterator<K, E, A, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alIterator<E>::Driver*
alXtreeIterator<K, E, A, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline E
alXtreeIterator<K, E, A, C>::Driver::get_current() const
{
    return (_iterator != _element_tree.end()) ? *_iterator : E();
}
/*}}}*/

//alXtreeIterator<K, E, A, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename A, typename C>
inline void
alXtreeIterator<K, E, A, C>::Driver::progress()
{
    if (_iterator != _element_tree.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alXtreeReverseIterator<K, E, A, C> implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeReverseIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alIterator<E>::Driver*
alXtreeReverseIterator<K, E, A, C>::create_driver(const xtree<K, E, A, C>& elementXtree)
{
    return new Driver(elementXtree);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alXtreeReverseIterator<K, E, A, C>::Driver implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alXtreeReverseIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeReverseIterator<K, E, A, C>::Driver::Driver(const xtree<K, E, A, C>& elementXtree)
  : Inherit()
  , _element_tree(elementXtree)
  , _iterator(elementXtree.rbegin())
{
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename A, typename C>
inline
alXtreeReverseIterator<K, E, A, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_tree(driver._element_tree)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeReverseIterator<K, E, A, C>::Driver::is_valid() const
{
    return (_iterator != _element_tree.rend());
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeReverseIterator<K, E, A, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline bool
alXtreeReverseIterator<K, E, A, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline typename alIterator<E>::Driver*
alXtreeReverseIterator<K, E, A, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename A, typename C>
inline E
alXtreeReverseIterator<K, E, A, C>::Driver::get_current() const
{
    return (_iterator != _element_tree.rend()) ? *_iterator : E();
}
/*}}}*/

//alXtreeReverseIterator<K, E, A, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename A, typename C>
inline void
alXtreeReverseIterator<K, E, A, C>::Driver::progress()
{
    if (_iterator != _element_tree.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alVectorIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alVectorIterator<E>::create_driver(const std::vector<E>& elementVector, size_t index)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alVectorIterator<E>::create_driver(const std::vector<E>& elementVector, size_t index)
{
    return new Driver(elementVector, index);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alVectorIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alVectorIterator<E>::Driver::Driver(const std::vector<E>& elementVector, size_t index)/*{{{*/
template<typename E>
inline
alVectorIterator<E>::Driver::Driver(const std::vector<E>& elementVector, size_t index)
  : Inherit()
  , _element_vector(elementVector)
  , _iterator()
{
    if (index < elementVector.size())
        _iterator = elementVector.begin() + index;
    else
        _iterator = elementVector.end();
}
/*}}}*/

//alVectorIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alVectorIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_vector(driver._element_vector)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alVectorIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alVectorIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_vector.end());
}
/*}}}*/

//alVectorIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alVectorIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alVectorIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alVectorIterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alVectorIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alVectorIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alVectorIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alVectorIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_vector.end()) ? *_iterator : E();
}
/*}}}*/

//alVectorIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alVectorIterator<E>::Driver::progress()
{
    if (_iterator != _element_vector.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alVectorReverseIterator<E> implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alVectorReverseIterator<E>::create_driver(const std::vector<E>& elementVector, size_t index)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alVectorReverseIterator<E>::create_driver(const std::vector<E>& elementVector, size_t index)
{
    return new Driver(elementVector, index);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alVectorReverseIterator<E>::Driver implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alVectorReverseIterator<E>::Driver::Driver(const std::vector<E>& elementVector, size_t index)/*{{{*/
template<typename E>
inline
alVectorReverseIterator<E>::Driver::Driver(const std::vector<E>& elementVector, size_t index)
  : Inherit()
  , _element_vector(elementVector)
  , _iterator()
{
    if (index < elementVector.size())
        _iterator = elementVector.rbegin() + index;
    else
        _iterator = elementVector.rend();
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alVectorReverseIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_vector(driver._element_vector)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alVectorReverseIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_vector.rend());
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alVectorReverseIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alVectorReverseIterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alVectorReverseIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alVectorReverseIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_vector.rend()) ? *_iterator : E();
}
/*}}}*/

//alVectorReverseIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alVectorReverseIterator<E>::Driver::progress()
{
    if (_iterator != _element_vector.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapIterator<K, E, C> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alMapIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<E>::Driver*
alMapIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapIterator<K, E, C>::Driver implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alMapIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
  , _iterator(elementMap.begin())
{
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapIterator<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapIterator<K, E, C>::Driver::is_valid() const
{
    return (_iterator != _element_map.end());
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapIterator<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapIterator<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<E>::Driver*
alMapIterator<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename C>
inline E
alMapIterator<K, E, C>::Driver::get_current() const
{
    return (_iterator != _element_map.end()) ? (*_iterator).second : E();
}
/*}}}*/

//alMapIterator<K, E, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename C>
inline void
alMapIterator<K, E, C>::Driver::progress()
{
    if (_iterator != _element_map.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapReverseIterator<K, E, C> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alMapReverseIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<E>::Driver*
alMapReverseIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMapReverseIterator<K, E, C>::Driver implementation                                            //
//                                                                                                //

#ifndef DOXYGEN
//alMapReverseIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapReverseIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
  , _iterator(elementMap.rbegin())
{
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alMapReverseIterator<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapReverseIterator<K, E, C>::Driver::is_valid() const
{
    return (_iterator != _element_map.rend());
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapReverseIterator<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alMapReverseIterator<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<E>::Driver*
alMapReverseIterator<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename C>
inline E
alMapReverseIterator<K, E, C>::Driver::get_current() const
{
    return (_iterator != _element_map.rend()) ? (*_iterator).second : E();
}
/*}}}*/

//alMapReverseIterator<K, E, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename C>
inline void
alMapReverseIterator<K, E, C>::Driver::progress()
{
    if (_iterator != _element_map.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alKeyIterator<K, E, C> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alKeyIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<K>::Driver*
alKeyIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/

//alKeyIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<K>::Driver*
alKeyIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap, const typename std::map<K, E, C>::const_iterator& iterator)
{
    return new Driver(elementMap, iterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alKeyIterator<K, E, C>::Driver implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alKeyIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
  , _iterator(elementMap.begin())
{
}

template<typename K, typename E, typename C>
inline
alKeyIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap, const typename std::map<K, E, C>::const_iterator& iterator)
  : Inherit()
  , _element_map(elementMap)
  , _iterator(iterator)
{
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyIterator<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyIterator<K, E, C>::Driver::is_valid() const
{
    return (_iterator != _element_map.end());
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyIterator<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyIterator<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<K>::Driver*
alKeyIterator<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename C>
inline K
alKeyIterator<K, E, C>::Driver::get_current() const
{
    return (_iterator != _element_map.end()) ? (*_iterator).first : K();
}
/*}}}*/

//alKeyIterator<K, E, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename C>
inline void
alKeyIterator<K, E, C>::Driver::progress()
{
    if (_iterator != _element_map.end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alKeyReverseIterator<K, E, C> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alKeyReverseIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<K>::Driver*
alKeyReverseIterator<K, E, C>::create_driver(const std::map<K, E, C>& elementMap)
{
    return new Driver(elementMap);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alKeyReverseIterator<K, E, C>::Driver implementation                                            //
//                                                                                                //

#ifndef DOXYGEN
//alKeyReverseIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyReverseIterator<K, E, C>::Driver::Driver(const std::map<K, E, C>& elementMap)
  : Inherit()
  , _element_map(elementMap)
  , _iterator(elementMap.rbegin())
{
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename K, typename E, typename C>
inline
alKeyReverseIterator<K, E, C>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_map(driver._element_map)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::is_valid() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyReverseIterator<K, E, C>::Driver::is_valid() const
{
    return (_iterator != _element_map.rend());
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::is_mutable_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyReverseIterator<K, E, C>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::is_dynamic_access() const/*{{{*/
template<typename K, typename E, typename C>
inline bool
alKeyReverseIterator<K, E, C>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::create_clone() const/*{{{*/
template<typename K, typename E, typename C>
inline typename alIterator<K>::Driver*
alKeyReverseIterator<K, E, C>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::get_current() const/*{{{*/
template<typename K, typename E, typename C>
inline K
alKeyReverseIterator<K, E, C>::Driver::get_current() const
{
    return (_iterator != _element_map.rend()) ? (*_iterator).first : K();
}
/*}}}*/

//alKeyReverseIterator<K, E, C>::Driver::progress()/*{{{*/
template<typename K, typename E, typename C>
inline void
alKeyReverseIterator<K, E, C>::Driver::progress()
{
    if (_iterator != _element_map.rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN

/*}}}*/


//                                                                                                //
//  alRandomAccessIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessIterator<E>::create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alRandomAccessIterator<E>::create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)
{
    return new Driver(element_vector_ref, index);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alRandomAccessIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessIterator<E>::Driver::Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)/*{{{*/
template<typename E>
inline
alRandomAccessIterator<E>::Driver::Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)
  : Inherit()
  , _element_vector_ref(element_vector_ref)
  , _iterator()
{
    if (index < element_vector_ref.get_elements().size())
        _iterator = element_vector_ref.get_elements().begin() + index;
    else
        _iterator = element_vector_ref.get_elements().end();
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alRandomAccessIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_vector_ref(driver._element_vector_ref)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alRandomAccessIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_vector_ref.get_elements().end());
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessIterator<E>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alRandomAccessIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alRandomAccessIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_vector_ref.get_elements().end()) ? *_iterator : E();
}
/*}}}*/

//alRandomAccessIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alRandomAccessIterator<E>::Driver::progress()
{
    if (_iterator != _element_vector_ref.get_elements().end()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alRandomAccessReverseIterator<E> implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessReverseIterator<E>::create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alRandomAccessReverseIterator<E>::create_driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)
{
    return new Driver(element_vector_ref, index);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alRandomAccessReverseIterator<E>::Driver implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alRandomAccessReverseIterator<E>::Driver::Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)/*{{{*/
template<typename E>
inline
alRandomAccessReverseIterator<E>::Driver::Driver(const alRefCounter<std::vector<E> >& element_vector_ref, size_t index)
  : Inherit()
  , _element_vector_ref(element_vector_ref)
  , _iterator()
{
    if (index < element_vector_ref.get_elements().size())
        _iterator = element_vector_ref.get_elements().rbegin() + index;
    else
        _iterator = element_vector_ref.get_elements().rend();
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alRandomAccessReverseIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_vector_ref(driver._element_vector_ref)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alRandomAccessReverseIterator<E>::Driver::is_valid() const
{
    return (_iterator != _element_vector_ref.get_elements().rend());
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessReverseIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alRandomAccessReverseIterator<E>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alRandomAccessReverseIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alRandomAccessReverseIterator<E>::Driver::get_current() const
{
    return (_iterator != _element_vector_ref.get_elements().rend()) ? *_iterator : E();
}
/*}}}*/

//alRandomAccessReverseIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alRandomAccessReverseIterator<E>::Driver::progress()
{
    if (_iterator != _element_vector_ref.get_elements().rend()) {
        ++_iterator;
    }
}
/*}}}*/
#endif // DOXYGEN


//                                                                                                //
//  alHeadIterator<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alHeadIterator<E>::create_driver(const alIterator<E>& iterator, size_t count)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alHeadIterator<E>::create_driver(const alIterator<E>& iterator, size_t count)
{
    return new Driver(iterator, count);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alHeadIterator<E>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alHeadIterator<E>::Driver::Driver(const alIterator<E>& iterator, size_t count)/*{{{*/
template<typename E>
inline
alHeadIterator<E>::Driver::Driver(const alIterator<E>& iterator, size_t count)
  : Inherit()
  , _iterator()
  , _count(count)
{
    if (_count) {
        _iterator = iterator;
    }
}
/*}}}*/

//alHeadIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alHeadIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _count(driver._count)
{
}
/*}}}*/

//alHeadIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alHeadIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alHeadIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alHeadIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alHeadIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alHeadIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alHeadIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alHeadIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alHeadIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alHeadIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alHeadIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alHeadIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();

        if (!--_count) {
            _iterator = NULL;
        }
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTailIterator<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alTailIterator<E>::create_driver(const alIterator<E>& iterator, size_t startIndex)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alTailIterator<E>::create_driver(const alIterator<E>& iterator, size_t startIndex)
{
    return new Driver(iterator, startIndex);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alTailIterator<E>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alTailIterator<E>::Driver::Driver(const alIterator<E>& iterator, size_t startIndex)/*{{{*/
template<typename E>
inline
alTailIterator<E>::Driver::Driver(const alIterator<E>& iterator, size_t startIndex)
  : Inherit()
  , _iterator(iterator)
  , _start_index(startIndex)
{
    while (_start_index-- && _iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/

//alTailIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alTailIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _start_index(driver._start_index)
{
}
/*}}}*/

//alTailIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alTailIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alTailIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alTailIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alTailIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alTailIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alTailIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alTailIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alTailIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alTailIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alTailIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alTailIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alToIterator<E> implementation                                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alToIterator<E>::create_driver(const alIterator<E>& iterator, const E& last)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alToIterator<E>::create_driver(const alIterator<E>& iterator, const E& last)
{
    return new Driver(iterator, last);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alToIterator<E>::Driver implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alToIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& last)/*{{{*/
template<typename E>
inline
alToIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& last)
  : Inherit()
  , _iterator(iterator)
  , _last(last)
{
}
/*}}}*/

//alToIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alToIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _last(driver._last)
{
}
/*}}}*/

//alToIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alToIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alToIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alToIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alToIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alToIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alToIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alToIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alToIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alToIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alToIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alToIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        if (_iterator.get_current() == _last) {
            _iterator = NULL;
        }
        else {
            _iterator.progress();
        }
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFromIterator<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alFromIterator<E>::create_driver(const alIterator<E>& iterator, const E& first)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alFromIterator<E>::create_driver(const alIterator<E>& iterator, const E& first)
{
    return new Driver(iterator, first);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFromIterator<E>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alFromIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& first)/*{{{*/
template<typename E>
inline
alFromIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& first)
  : Inherit()
  , _iterator(iterator)
  , _first(first)
{
    while (_iterator.is_valid() && (_iterator.get_current() != _first)) {
        _iterator.progress();
    }
}
/*}}}*/

//alFromIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alFromIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _first(driver._first)
{
}
/*}}}*/

//alFromIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alFromIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alFromIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alFromIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alFromIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alFromIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alFromIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alFromIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alFromIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alFromIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alFromIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alFromIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alBeforeIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alBeforeIterator<E>::create_driver(const alIterator<E>& iterator, const E& next)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alBeforeIterator<E>::create_driver(const alIterator<E>& iterator, const E& next)
{
    return new Driver(iterator, next);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alBeforeIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alBeforeIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& next)/*{{{*/
template<typename E>
inline
alBeforeIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& next)
  : Inherit()
  , _iterator(iterator)
  , _next(next)
{
    if (iterator.is_valid() && (iterator.get_current() == _next)) {
        _iterator = NULL;
    }
}
/*}}}*/

//alBeforeIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alBeforeIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _next(driver._next)
{
}
/*}}}*/

//alBeforeIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alBeforeIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alBeforeIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alBeforeIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alBeforeIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alBeforeIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alBeforeIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alBeforeIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alBeforeIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alBeforeIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alBeforeIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alBeforeIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();

        if (_iterator.is_valid() && (_iterator.get_current() == _next)) {
            _iterator = NULL;
        }
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAfterIterator<E> implementation                                                               //
//                                                                                                //

#ifndef DOXYGEN
//alAfterIterator<E>::create_driver(const alIterator<E>& iterator, const E& previous)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alAfterIterator<E>::create_driver(const alIterator<E>& iterator, const E& previous)
{
    return new Driver(iterator, previous);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAfterIterator<E>::Driver implementation                                                       //
//                                                                                                //

#ifndef DOXYGEN
//alAfterIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& previous)/*{{{*/
template<typename E>
inline
alAfterIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& previous)
  : Inherit()
  , _iterator(iterator)
  , _previous(previous)
{
    while (_iterator.is_valid() && (_iterator.get_current() != _previous)) {
        _iterator.progress();
    }

    if (_iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/

//alAfterIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alAfterIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _previous(driver._previous)
{
}
/*}}}*/

//alAfterIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alAfterIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alAfterIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alAfterIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alAfterIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alAfterIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alAfterIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alAfterIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAfterIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alAfterIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alAfterIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alAfterIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alNotIterator<E> implementation                                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alNotIterator<E>::create_driver(const alIterator<E>& iterator, const E& rejected)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alNotIterator<E>::create_driver(const alIterator<E>& iterator, const E& rejected)
{
    return new Driver(iterator, rejected);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alNotIterator<E>::Driver implementation                                                         //
//                                                                                                //

#ifndef DOXYGEN
//alNotIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& rejected)/*{{{*/
template<typename E>
inline
alNotIterator<E>::Driver::Driver(const alIterator<E>& iterator, const E& rejected)
  : Inherit()
  , _iterator(iterator)
  , _rejected(rejected)
{
    while (_iterator.is_valid() && (_iterator.get_current() == _rejected)) {
        _iterator.progress();
    }
}
/*}}}*/

//alNotIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alNotIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _rejected(driver._rejected)
{
}
/*}}}*/

//alNotIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alNotIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alNotIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alNotIterator<E>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alNotIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alNotIterator<E>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access();
}
/*}}}*/

//alNotIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alNotIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alNotIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alNotIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alNotIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alNotIterator<E>::Driver::progress()
{
    if (_iterator.is_valid()) {
        do {
            _iterator.progress();
        } while (_iterator.is_valid() && (_iterator.get_current() == _rejected));
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSubsetIterator<E, D> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alSubsetIterator<E, D>::create_driver(const alIterator<E>& iterator, const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline typename alIterator<E>::Driver*
alSubsetIterator<E, D>::create_driver(const alIterator<E>& iterator, const alPredicate<E, D>& predicate)
{
    return new Driver(iterator, predicate);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSubsetIterator<E, D>::Driver implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alSubsetIterator<E, D>::Driver::Driver(const alIterator<E>& iterator, const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline
alSubsetIterator<E, D>::Driver::Driver(const alIterator<E>& iterator, const alPredicate<E, D>& predicate)
  : Inherit()
  , _iterator(iterator)
  , _predicate(predicate)
{
    while (_iterator.is_valid() && _predicate.is_rejected(_iterator.get_current())) {
        _iterator.progress();
    }
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename D>
inline
alSubsetIterator<E, D>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _predicate(driver._predicate)
{
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::is_valid() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetIterator<E, D>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetIterator<E, D>::Driver::is_mutable_access() const
{
    return _iterator.is_mutable_access();
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
inline bool
alSubsetIterator<E, D>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access() && _predicate.is_dynamic_access();
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::create_clone() const/*{{{*/
template<typename E, typename D>
inline typename alIterator<E>::Driver*
alSubsetIterator<E, D>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::get_current() const/*{{{*/
template<typename E, typename D>
inline E
alSubsetIterator<E, D>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alSubsetIterator<E, D>::Driver::progress()/*{{{*/
template<typename E, typename D>
inline void
alSubsetIterator<E, D>::Driver::progress()
{
    if (_iterator.is_valid()) {
        do {
            _iterator.progress();
        } while (_iterator.is_valid() && _predicate.is_rejected(_iterator.get_current()));
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAssociatesIterator<E, A, D> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alAssociatesIterator<E, A, D>::create_driver(const alIterator<E>& iterator, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline typename alIterator<A>::Driver*
alAssociatesIterator<E, A, D>::create_driver(const alIterator<E>&       iterator,
                      const alAccessor<E, A, D>& accessor)
{
    return new Driver(iterator, accessor);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAssociatesIterator<E, A, D>::Driver implementation                                            //
//                                                                                                //

#ifndef DOXYGEN
//alAssociatesIterator<E, A, D>::Driver::Driver(const alIterator<E>& iterator, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline
alAssociatesIterator<E, A, D>::Driver::Driver(const alIterator<E>&       iterator,
                        const alAccessor<E, A, D>& accessor)
  : Inherit()
  , _iterator(iterator)
  , _accessor(accessor)
{
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E, typename A, typename D>
inline
alAssociatesIterator<E, A, D>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _iterator(driver._iterator)
  , _accessor(driver._accessor)
{
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::is_valid() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesIterator<E, A, D>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::is_mutable_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesIterator<E, A, D>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAssociatesIterator<E, A, D>::Driver::is_dynamic_access() const
{
    return _iterator.is_dynamic_access() && _accessor.is_dynamic_access();
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
inline typename alIterator<A>::Driver*
alAssociatesIterator<E, A, D>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::get_current() const/*{{{*/
template<typename E, typename A, typename D>
inline A
alAssociatesIterator<E, A, D>::Driver::get_current() const
{
    return (_iterator.is_valid()) ? _accessor.get_associate(_iterator.get_current()) : A();
}
/*}}}*/

//alAssociatesIterator<E, A, D>::Driver::progress()/*{{{*/
template<typename E, typename A, typename D>
inline void
alAssociatesIterator<E, A, D>::Driver::progress()
{
    if (_iterator.is_valid()) {
        _iterator.progress();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReverseIterator<E> implementation                                                             //
//                                                                                                //

#ifndef DOXYGEN
//alReverseIterator<E>::create_driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alReverseIterator<E>::create_driver(const alIterator<E>& iterator)
{
    return new Driver(iterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReverseIterator<E>::Driver implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alReverseIterator<E>::Driver::Driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline
alReverseIterator<E>::Driver::Driver(const alIterator<E>& iterator)
  : Inherit()
  , _element_list()
{
    alIterator<E> iteratorCopy = iterator;

    while (iteratorCopy.is_valid()) {
        _element_list.push_front(iteratorCopy.get_current());
        iteratorCopy.progress();
    }
}
/*}}}*/

//alReverseIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alReverseIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _element_list(driver._element_list)
{
}
/*}}}*/

//alReverseIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alReverseIterator<E>::Driver::is_valid() const
{
    return !_element_list.empty();
}
/*}}}*/

//alReverseIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alReverseIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alReverseIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alReverseIterator<E>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alReverseIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alReverseIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alReverseIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alReverseIterator<E>::Driver::get_current() const
{
    return (!_element_list.empty()) ? _element_list.front() : E();
}
/*}}}*/

//alReverseIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alReverseIterator<E>::Driver::progress()
{
    if (!_element_list.empty()) {
        _element_list.pop_front();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect1Iterator<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCollect1Iterator<E>::create_driver(const E& first)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect1Iterator<E>::create_driver(const E& first)
{
    return new Driver(first);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect1Iterator<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCollect1Iterator<E>::Driver::Driver(const E& first)/*{{{*/
template<typename E>
inline
alCollect1Iterator<E>::Driver::Driver(const E& first)
  : Inherit()
  , _first(first)
  , _index(0)
{
}
/*}}}*/

//alCollect1Iterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect1Iterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _index(driver._index)
{
}
/*}}}*/

//alCollect1Iterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCollect1Iterator<E>::Driver::is_valid() const
{
    return !_index;
}
/*}}}*/

//alCollect1Iterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Iterator<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect1Iterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect1Iterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect1Iterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect1Iterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect1Iterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCollect1Iterator<E>::Driver::get_current() const
{
    return (!_index) ? _first : E();
}
/*}}}*/

//alCollect1Iterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCollect1Iterator<E>::Driver::progress()
{
    if (!_index) {
        ++_index;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect2Iterator<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCollect2Iterator<E>::create_driver(const E& first, const E& second)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect2Iterator<E>::create_driver(const E& first, const E& second)
{
    return new Driver(first, second);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect2Iterator<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCollect2Iterator<E>::Driver::Driver(const E& first, const E& second)/*{{{*/
template<typename E>
inline
alCollect2Iterator<E>::Driver::Driver(const E& first, const E& second)
  : Inherit()
  , _first(first)
  , _second(second)
  , _index(0)
{
}
/*}}}*/

//alCollect2Iterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect2Iterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _index(driver._index)
{
}
/*}}}*/

//alCollect2Iterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCollect2Iterator<E>::Driver::is_valid() const
{
    return (_index < 2);
}
/*}}}*/

//alCollect2Iterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Iterator<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect2Iterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect2Iterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect2Iterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect2Iterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect2Iterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCollect2Iterator<E>::Driver::get_current() const
{
    switch (_index) {
    case 0: return _first;
    case 1: return _second;
    }

    return E();
}
/*}}}*/

//alCollect2Iterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCollect2Iterator<E>::Driver::progress()
{
    if (_index < 2) {
        ++_index;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect3Iterator<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCollect3Iterator<E>::create_driver(const E& first, const E& second, const E& third)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect3Iterator<E>::create_driver(const E& first, const E& second, const E& third)
{
    return new Driver(first, second, third);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect3Iterator<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCollect3Iterator<E>::Driver::Driver(const E& first, const E& second, const E& third)/*{{{*/
template<typename E>
inline
alCollect3Iterator<E>::Driver::Driver(const E& first, const E& second, const E& third)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
  , _index(0)
{
}
/*}}}*/

//alCollect3Iterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect3Iterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
  , _index(driver._index)
{
}
/*}}}*/

//alCollect3Iterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCollect3Iterator<E>::Driver::is_valid() const
{
    return (_index < 3);
}
/*}}}*/

//alCollect3Iterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Iterator<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect3Iterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect3Iterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect3Iterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect3Iterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect3Iterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCollect3Iterator<E>::Driver::get_current() const
{
    switch (_index) {
    case 0: return _first;
    case 1: return _second;
    case 2: return _third;
    }

    return E();
}
/*}}}*/

//alCollect3Iterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCollect3Iterator<E>::Driver::progress()
{
    if (_index < 3) {
        ++_index;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect4Iterator<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCollect4Iterator<E>::create_driver(const E& first, const E& second, const E& third, const E& fourth)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect4Iterator<E>::create_driver(const E& first, const E& second, const E& third, const E& fourth)
{
    return new Driver(first, second, third, fourth);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect4Iterator<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCollect4Iterator<E>::Driver::Driver(const E& first, const E& second, const E& third, const E& fourth)/*{{{*/
template<typename E>
inline
alCollect4Iterator<E>::Driver::Driver(const E& first,
                    const E& second,
                    const E& third,
                    const E& fourth)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
  , _fourth(fourth)
  , _index(0)
{
}
/*}}}*/

//alCollect4Iterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect4Iterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
  , _fourth(driver._fourth)
  , _index(driver._index)
{
}
/*}}}*/

//alCollect4Iterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCollect4Iterator<E>::Driver::is_valid() const
{
    return (_index < 4);
}
/*}}}*/

//alCollect4Iterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Iterator<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect4Iterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect4Iterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect4Iterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect4Iterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect4Iterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCollect4Iterator<E>::Driver::get_current() const
{
    switch (_index) {
    case 0: return _first;
    case 1: return _second;
    case 2: return _third;
    case 3: return _fourth;
    }

    return E();
}
/*}}}*/

//alCollect4Iterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCollect4Iterator<E>::Driver::progress()
{
    if (_index < 4) {
        ++_index;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect5Iterator<E> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alCollect5Iterator<E>::create_driver(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect5Iterator<E>::create_driver(const E& first,
                  const E& second,
                  const E& third,
                  const E& fourth,
                  const E& fifth)
{
    return new Driver(first, second, third, fourth, fifth);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCollect5Iterator<E>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alCollect5Iterator<E>::Driver::Driver(const E& first, const E& second, const E& third, const E& fourth, const E& fifth)/*{{{*/
template<typename E>
inline
alCollect5Iterator<E>::Driver::Driver(const E& first,
                    const E& second,
                    const E& third,
                    const E& fourth,
                    const E& fifth)
  : Inherit()
  , _first(first)
  , _second(second)
  , _third(third)
  , _fourth(fourth)
  , _fifth(fifth)
  , _index(0)
{
}
/*}}}*/

//alCollect5Iterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCollect5Iterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _first(driver._first)
  , _second(driver._second)
  , _third(driver._third)
  , _fourth(driver._fourth)
  , _fifth(driver._fifth)
  , _index(driver._index)
{
}
/*}}}*/

//alCollect5Iterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCollect5Iterator<E>::Driver::is_valid() const
{
    return (_index < 5);
}
/*}}}*/

//alCollect5Iterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Iterator<E>::Driver::is_mutable_access() const
{
    return true;
}
/*}}}*/

//alCollect5Iterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCollect5Iterator<E>::Driver::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alCollect5Iterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCollect5Iterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCollect5Iterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCollect5Iterator<E>::Driver::get_current() const
{
    switch (_index) {
    case 0: return _first;
    case 1: return _second;
    case 2: return _third;
    case 3: return _fourth;
    case 4: return _fifth;
    }

    return E();
}
/*}}}*/

//alCollect5Iterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCollect5Iterator<E>::Driver::progress()
{
    if (_index < 5) {
        ++_index;
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReduceIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alReduceIterator<E>::create_driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alReduceIterator<E>::create_driver(const alIterator<E>& iterator)
{
    return new Driver(iterator);
}
/*}}}*/

//alReduceIterator<E>::create_driver(const alIterator<E>& iterator, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E>
template<typename A, typename D>
inline typename alIterator<E>::Driver*
alReduceIterator<E>::create_driver(const alIterator<E>& iterator, const alAccessor<E, A, D>& accessor)
{
    return new AssociateDriver<A, D>(iterator, accessor);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReduceIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alReduceIterator<E>::Driver::Driver(const alIterator<E>& iterator)/*{{{*/
template<typename E>
inline
alReduceIterator<E>::Driver::Driver(const alIterator<E>& iterator)
  : Inherit()
  , _set()
  , _iterator(iterator)
{
}
/*}}}*/

//alReduceIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alReduceIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _set(driver._set)
  , _iterator(driver._iterator)
{
}
/*}}}*/

//alReduceIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alReduceIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alReduceIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alReduceIterator<E>::Driver::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alReduceIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alReduceIterator<E>::Driver::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alReduceIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alReduceIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alReduceIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alReduceIterator<E>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alReduceIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alReduceIterator<E>::Driver::progress()
{
    if (is_valid()) {
        _set.insert(get_current());
        do {
            _iterator.progress();
        } while (_iterator.is_valid() && (_set.find(_iterator.get_current()) != _set.end()));
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alReduceIterator<E>::AssociateDriver<A, D> implementation                                       //
//                                                                                                //

#ifndef DOXYGEN
//alReduceIterator<E>::AssociateDriver<A, D>::AssociateDriver(const alIterator<E>& iterator, const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E>
template<typename A, typename D>
inline
alReduceIterator<E>::AssociateDriver<A, D>::AssociateDriver(const alIterator<E>&       iterator,
                              const alAccessor<E, A, D>& accessor)
  : Inherit()
  , _set()
  , _iterator(iterator)
  , _accessor(accessor)
{
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::AssociateDriver(const AssociateDriver& driver)/*{{{*/
template<typename E>
template<typename A, typename D>
inline
alReduceIterator<E>::AssociateDriver<A, D>::AssociateDriver(const AssociateDriver& driver)
  : Inherit()
  , _set(driver._set)
  , _iterator(driver._iterator)
  , _accessor(driver._accessor)
{
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::create_clone() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline typename alIterator<E>::Driver*
alReduceIterator<E>::AssociateDriver<A, D>::create_clone() const
{
    return new AssociateDriver<A, D>(*this);
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::get_current() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline E
alReduceIterator<E>::AssociateDriver<A, D>::get_current() const
{
    return _iterator.get_current();
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::is_valid() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceIterator<E>::AssociateDriver<A, D>::is_valid() const
{
    return _iterator.is_valid();
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::is_mutable_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceIterator<E>::AssociateDriver<A, D>::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::is_dynamic_access() const/*{{{*/
template<typename E>
template<typename A, typename D>
inline bool
alReduceIterator<E>::AssociateDriver<A, D>::is_dynamic_access() const
{
    return false;
}
/*}}}*/

//alReduceIterator<E>::AssociateDriver<A, D>::progress()/*{{{*/
template<typename E>
template<typename A, typename D>
inline void
alReduceIterator<E>::AssociateDriver<A, D>::progress()
{
    if (is_valid()) {
        _set.insert(_accessor.get_associate(get_current()));
        do {
            _iterator.progress();
        } while (_iterator.is_valid() &&
             (_set.find(_accessor.get_associate(_iterator.get_current())) != _set.end()));
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAppendIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alAppendIterator<E>::create_driver(const alIterator<E>& alheadIterator, const alIterator<E>& altailIterator)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alAppendIterator<E>::create_driver(const alIterator<E>& alheadIterator, const alIterator<E>& altailIterator)
{
    return new Driver(alheadIterator, altailIterator);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAppendIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alAppendIterator<E>::Driver::Driver(const alIterator<E>& alheadIterator, const alIterator<E>& altailIterator)/*{{{*/
template<typename E>
inline
alAppendIterator<E>::Driver::Driver(const alIterator<E>& alheadIterator, const alIterator<E>& altailIterator)
  : Inherit()
  , _head_iterator(alheadIterator)
  , _tail_iterator(altailIterator)
{
}
/*}}}*/

//alAppendIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alAppendIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _head_iterator(driver._head_iterator)
  , _tail_iterator(driver._tail_iterator)
{
}
/*}}}*/

//alAppendIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alAppendIterator<E>::Driver::is_valid() const
{
    return _head_iterator.is_valid() || _tail_iterator.is_valid();
}
/*}}}*/

//alAppendIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alAppendIterator<E>::Driver::is_mutable_access() const
{
    return _head_iterator.is_mutable_access() && _tail_iterator.is_mutable_access();
}
/*}}}*/

//alAppendIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alAppendIterator<E>::Driver::is_dynamic_access() const
{
    return _head_iterator.is_dynamic_access() && _tail_iterator.is_dynamic_access();
}
/*}}}*/

//alAppendIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alAppendIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alAppendIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alAppendIterator<E>::Driver::get_current() const
{
    return (_head_iterator.is_valid()) ? _head_iterator.get_current() : _tail_iterator.get_current();
}
/*}}}*/

//alAppendIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alAppendIterator<E>::Driver::progress()
{
    if (_head_iterator.is_valid()) {
        _head_iterator.progress();
    } else {
        _tail_iterator.progress();
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenIterator<Es> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenIterator<Es>::create_driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline typename alIterator<typename Es::ElementType>::Driver*
alFlattenIterator<Es>::create_driver(const alCollection<Es>& collections)
{
    return new Driver(collections);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenIterator<Es>::Driver implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenIterator<Es>::Driver::Driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline
alFlattenIterator<Es>::Driver::Driver(const alCollection<Es>& collections)
  : Inherit()
  , _primary_iterator(collections.get_iterator())
  , _secondary_iterator()
{
    while (_primary_iterator.is_valid() && !_secondary_iterator.is_valid()) {
        _secondary_iterator = _primary_iterator.get_current().get_iterator();
        _primary_iterator.progress();
    }
}
/*}}}*/

//alFlattenIterator<Es>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename Es>
inline
alFlattenIterator<Es>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _primary_iterator(driver._primary_iterator)
  , _secondary_iterator(driver._secondary_iterator)
{
}
/*}}}*/

//alFlattenIterator<Es>::Driver::is_valid() const/*{{{*/
template<typename Es>
inline bool
alFlattenIterator<Es>::Driver::is_valid() const
{
    return _secondary_iterator.is_valid();
}
/*}}}*/

//alFlattenIterator<Es>::Driver::is_mutable_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenIterator<Es>::Driver::is_mutable_access() const
{
    return _primary_iterator.is_mutable_access() && _secondary_iterator.is_mutable_access();
}
/*}}}*/

//alFlattenIterator<Es>::Driver::is_dynamic_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenIterator<Es>::Driver::is_dynamic_access() const
{
    return _primary_iterator.is_dynamic_access() && _secondary_iterator.is_dynamic_access();
}
/*}}}*/

//alFlattenIterator<Es>::Driver::create_clone() const/*{{{*/
template<typename Es>
inline typename alIterator<typename Es::ElementType>::Driver*
alFlattenIterator<Es>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alFlattenIterator<Es>::Driver::get_current() const/*{{{*/
template<typename Es>
inline typename Es::ElementType
alFlattenIterator<Es>::Driver::get_current() const
{
    return _secondary_iterator.get_current();
}
/*}}}*/

//alFlattenIterator<Es>::Driver::progress()/*{{{*/
template<typename Es>
inline void
alFlattenIterator<Es>::Driver::progress()
{
    if (_secondary_iterator.is_valid()) {
        _secondary_iterator.progress();

        while (_primary_iterator.is_valid() && !_secondary_iterator.is_valid()) {
            _secondary_iterator = _primary_iterator.get_current().get_iterator();
            _primary_iterator.progress();
        }
        
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenReverseIterator<Es> implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenReverseIterator<Es>::create_driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline typename alIterator<typename Es::ElementType>::Driver*
alFlattenReverseIterator<Es>::create_driver(const alCollection<Es>& collections)
{
    return new Driver(collections);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFlattenReverseIterator<Es>::Driver implementation                                             //
//                                                                                                //

#ifndef DOXYGEN
//alFlattenReverseIterator<Es>::Driver::Driver(const alCollection<Es>& collections)/*{{{*/
template<typename Es>
inline
alFlattenReverseIterator<Es>::Driver::Driver(const alCollection<Es>& collections)
  : Inherit()
  , _primary_iterator(collections.get_reverse_iterator())
  , _secondary_iterator()
{
    while (_primary_iterator.is_valid() && !_secondary_iterator.is_valid()) {
        _secondary_iterator = _primary_iterator.get_current().get_reverse_iterator();
        _primary_iterator.progress();
    }
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename Es>
inline
alFlattenReverseIterator<Es>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _primary_iterator(driver._primary_iterator)
  , _secondary_iterator(driver._secondary_iterator)
{
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::is_valid() const/*{{{*/
template<typename Es>
inline bool
alFlattenReverseIterator<Es>::Driver::is_valid() const
{
    return _secondary_iterator.is_valid();
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::is_mutable_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenReverseIterator<Es>::Driver::is_mutable_access() const
{
    return _primary_iterator.is_mutable_access() && _secondary_iterator.is_mutable_access();
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::is_dynamic_access() const/*{{{*/
template<typename Es>
inline bool
alFlattenReverseIterator<Es>::Driver::is_dynamic_access() const
{
    return _primary_iterator.is_dynamic_access() && _secondary_iterator.is_dynamic_access();
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::create_clone() const/*{{{*/
template<typename Es>
inline typename alIterator<typename Es::ElementType>::Driver*
alFlattenReverseIterator<Es>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::get_current() const/*{{{*/
template<typename Es>
inline typename Es::ElementType
alFlattenReverseIterator<Es>::Driver::get_current() const
{
    return _secondary_iterator.get_current();
}
/*}}}*/

//alFlattenReverseIterator<Es>::Driver::progress()/*{{{*/
template<typename Es>
inline void
alFlattenReverseIterator<Es>::Driver::progress()
{
    if (_secondary_iterator.is_valid()) {
        _secondary_iterator.progress();

        while (_primary_iterator.is_valid() && !_secondary_iterator.is_valid()) {
            _secondary_iterator = _primary_iterator.get_current().get_reverse_iterator();
            _primary_iterator.progress();
        }
        
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCustomIterator<E> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alCustomIterator<E>::create_driver(const E& first, const alAccessor<E, E>& get_next, const E& before)/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCustomIterator<E>::create_driver(const E& first, const alAccessor<E, E>& get_next, const E& before)
{
    return new Driver(first, get_next, before);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alCustomIterator<E>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alCustomIterator<E>::Driver::Driver(const E& first, const alAccessor<E, E>& get_next, const E& before)/*{{{*/
template<typename E>
inline
alCustomIterator<E>::Driver::Driver(const E& first, const alAccessor<E, E>& get_next, const E& before)
  : Inherit()
  , _current(first)
  , _before(before)
  , _next(get_next)
{
}
/*}}}*/

//alCustomIterator<E>::Driver::Driver(const Driver& driver)/*{{{*/
template<typename E>
inline
alCustomIterator<E>::Driver::Driver(const Driver& driver)
  : Inherit()
  , _current(driver._current)
  , _before(driver._before)
  , _next(driver._next)
{
}
/*}}}*/

//alCustomIterator<E>::Driver::is_valid() const/*{{{*/
template<typename E>
inline bool
alCustomIterator<E>::Driver::is_valid() const
{
    return _current != _before;
}
/*}}}*/

//alCustomIterator<E>::Driver::is_mutable_access() const/*{{{*/
template<typename E>
inline bool
alCustomIterator<E>::Driver::is_mutable_access() const
{
    return false;
}
/*}}}*/

//alCustomIterator<E>::Driver::is_dynamic_access() const/*{{{*/
template<typename E>
inline bool
alCustomIterator<E>::Driver::is_dynamic_access() const
{
    return _next.is_dynamic_access();
}
/*}}}*/

//alCustomIterator<E>::Driver::create_clone() const/*{{{*/
template<typename E>
inline typename alIterator<E>::Driver*
alCustomIterator<E>::Driver::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/

//alCustomIterator<E>::Driver::get_current() const/*{{{*/
template<typename E>
inline E
alCustomIterator<E>::Driver::get_current() const
{
    return _current;
}
/*}}}*/

//alCustomIterator<E>::Driver::progress()/*{{{*/
template<typename E>
inline void
alCustomIterator<E>::Driver::progress()
{
    if (is_valid()) {
        _current = _next.get_associate(_current);
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the definitions of the alIterator and alIterator::Driver classes.
    */
/*}}}*/

//class alIterator<E>/*{{{*/
/*!\class    alIterator
    \brief    This concrete class implements the concept of \em "iterator".
    */

/*!\member    E alIterator::get_next()
    \paragraph    Behaviour:
    \m    This function returns the current element and moves this iterator forward.
    \paragraph    Usage:
    \code
        * alIterator<Shape*> iterator(net->get_shapes());
        *
        * Shape* shape;
        *
        * while ((shape = iterator.get_next())) {
        *     // use shape here...
        * }
        \endcode
    \paragraph    Restriction:
    \m    This function returns \em "E()" when this iterator has exhausted all its elements
        (NULL is in case of pointer but something else in other cases).
    \n    In consequence, this approach works properly only for iterator of pointer objects:
    \li    So, whats append for a collection of Point ? (probably a compilation error, or a
        possible infinite loop).
    \li    Worst, whats append for a collection of integer containing a null value ? (a
        prematured loop exit).
    \paragraph    Recommendations:
    \m    So, I suggest to use the following form:
    \code
        * forEach (Shape*, shape, net->get_shapes()) {
        *     // use shape here...
        * }
        \endcode
    \n    This works in all cases and furthermore is more simpler.
    */
/*}}}*/

//class alIterator<E>::Driver/*{{{*/
/*!\class    alIterator::Driver
    \brief    This abstract class implements the concept of \em "iterator driver".
    */
/*}}}*/



//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
