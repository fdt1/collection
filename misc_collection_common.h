//                                                                                                //
//  File: misc_collection_common.h                                                                                //
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

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#ifndef DOXYGEN
#define PURE = 0
#endif // DOXYGEN

namespace misc {
/*}}}*/

//                                                                                                //
//  Unary Operator Functor                                                                     //
//                                                                                                //

template<typename T>
struct alIncr {
  static T get(T t) { return ++t; }
};

template<typename T>
struct alDecr {
  static T get(T t) { return --t; }
};

//                                                                                                //
//  Binary Comparator Functor                                                                     //
//                                                                                                //

template<typename T>
struct alEqual {
  static bool is(const T& t1, const T& t2) { return t1 == t2; }
};

template<typename T>
struct alGreater {
  static bool is(const T& t1, const T& t2) { return t1 > t2; }
};

template<typename T>
struct alLess {
  static bool is(const T& t1, const T& t2) { return t1 < t2; }
};

//                                                                                                //
//  Reference counter                                                                             //
//                                                                                                //


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
        const E& get_elements() const;
        E& get_elements();
};


//                                                                                                //
//  Reference counter  implementation                                                             //
//                                                                                                //

template<typename E>
inline
alRefCounter<E>::alRefCounter()
    : _elements(new std::pair<E, int>(E(), 0))
{
}

template<typename E>
inline
alRefCounter<E>::alRefCounter(const alRefCounter<E>& refcounter)
    : _elements(refcounter._elements)
{
    ++_elements->second;
}

template<typename E>
inline
alRefCounter<E>::alRefCounter(const E& elements)
    : _elements(new std::pair<E, int>(elements, 0))
{
}

template<typename E>
inline
alRefCounter<E>::~alRefCounter()
{
    if (_elements->second == 0)
        delete _elements;
    else
        --_elements->second;
}

template<typename E>
inline alRefCounter<E>& 
alRefCounter<E>::operator=(const alRefCounter<E>& refcounter)
{
    if (_elements->second == 0)
        delete _elements;
    else
        --_elements->second;

    _elements = refcounter._elements;
    
    ++_elements->second;

    return *this;
}

template<typename E>
inline const E& 
alRefCounter<E>::get_elements() const
{
    return _elements->first;    
}

template<typename E>
inline E& 
alRefCounter<E>::get_elements()
{
    return _elements->first;    
}


//                                                                                                //
//  Generic accessors                                                                             //
//                                                                                                //

//get_reference(O* object)/*{{{*/
#ifdef DOXYGEN
template<typename O> O& get_reference(O* object);
#else
template<typename O> inline O& get_reference(O* object)
{
    return *object;
}
#endif // DOXYGEN
/*}}}*/

//get_reference(O& object)/*{{{*/
#ifdef DOXYGEN
template<typename O> O& get_reference(O& object);
#else
template<typename O> inline O& get_reference(O& object)
{
    return object;
}
#endif // DOXYGEN
/*}}}*/

//get_typename(const O& object)/*{{{*/
#ifdef DOXYGEN
template<typename O> const string& get_typename(const O& object);
#else
const std::string& get_externalname(const std::string& internalName);

#define get_typename(object) get_externalname(typeid(object).name())
#endif // DOXYGEN
/*}}}*/



//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the common declarations and the corresponding generic functions.
    */
/*}}}*/

//mainpage/*{{{*/
/*! Home Page
    \paragraph    Introduction:
    \m    The purpose of this package is to provide to the developpers a set of classes and
        functions implementing some powerfull concepts and constituing a good start point
        for a new sofware development.
    \paragraph    Documentation:
    \m    This documentation comprises a large set of HTML pages that are hyperlinked
        together for fast information retrieval.
    \p    You can access the main pages of this documentation from the links availables in
        the banner located on top of each page.
    \paragraph    Copyright:
    \m    These coded concepts, statements, instructions, and computer programs contain
        unpublished proprietary informations and are protected by copyright law. They may
        not be disclosed to third parties or copied or duplicated in any form without the
        written consent of Abound Logic.
    */
/*}}}*/



//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
