//                                                                                                //
//  File: misc_collection_predicate.h                                                                             //
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

#include <misc/misc_collection_common.h>
#include <misc/misc_collection_accessor.h>

namespace misc {
/*}}}*/



//                                                                                                //
//  Declarations                                                                                  //
//                                                                                                //

//class alPredicate<E, D = bool>/*{{{*/
template<typename E, typename D = bool>
class alPredicate {

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
    //@{
    virtual bool                is_accepted(const E& element) const PURE;
    virtual bool                is_dynamic_access() const PURE;
    //@}

      public:
    //!\name Accessors:
    //@{
    virtual Driver*                create_clone() const PURE;
    virtual Driver*                create_clone(const D& datum) const;
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
                    ~alPredicate();
    //@}

  public:
    //!\name Default Constructor:
    //@{
                    alPredicate(Driver* driver = NULL);
    //@}

  public:
    //!\name Copy Constructor:
    //@{
                    alPredicate(const alPredicate<E, D>& predicate);
    //@}

  public:
    //!\name Member Based Constructors:
    //@{
        template<typename X>    alPredicate(bool (X::*member)());
        template<typename X>    alPredicate(bool (X::*member)() const);
        template<typename X>    alPredicate(bool (X::*member)(D));
        template<typename X>    alPredicate(bool (X::*member)(D) const);
        template<typename X>    alPredicate(bool (X::*member)(const D&));
        template<typename X>    alPredicate(bool (X::*member)(const D&) const);
    //@}

  public:
    //!\name Function Based Constructors:
    //@{
                    alPredicate(bool (*function)(E));
                    alPredicate(bool (*function)(const E&));
                    alPredicate(bool (*function)(E, D));
                    alPredicate(bool (*function)(const E&, D));
                    alPredicate(bool (*function)(E, const D&));
                    alPredicate(bool (*function)(const E&, const D&));
    //@}

  public:
    //!\name Accessor Based Constructors:
    //@{
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X));
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&));
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, D));
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, D));
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, const D&));
         template<typename X, typename Y> alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, const D&));
    //@}

  public:
    //!\name Assignment Operators:
    //@{
        alPredicate<E, D>&        operator=(Driver* driver);
        alPredicate<E, D>&        operator=(const alPredicate<E, D>& predicate);
    //@}

  public:
    //!\name Functional Operators:
    //@{
        alPredicate<E, D>        operator()() const;
        alPredicate<E, D>        operator()(const D& datum) const;
    //@}

  public:
    //!\name alPredicates:
    //@{
        bool            is_driven() const;
        bool            is_accepted(const E& element) const;
        bool            is_rejected(const E& element) const;
        //! return true if predicate supports dynamic modifications on datas
        bool            is_dynamic_access() const;
    //@}

  public:
    //!\name Accessors:
    //@{
        Driver*            get_driver() const;
    //@}

  #ifndef DOXYGEN
  private:
        Driver*            _driver;
  #endif // DOXYGEN

};
/*}}}*/

//class alSwapPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alSwapPredicate : public alPredicate<E, D> {

  public:
    //!\name Member Based Constructors:
    //@{
        template<typename X>    alSwapPredicate(bool (X::*member)(E));
        template<typename X>    alSwapPredicate(bool (X::*member)(E) const);
        template<typename X>    alSwapPredicate(bool (X::*member)(const E&));
        template<typename X>    alSwapPredicate(bool (X::*member)(const E&) const);
    //@}

    //!\name Function Based Constructors:
    //@{
                    alSwapPredicate(bool (*function)(D, E));
                    alSwapPredicate(bool (*function)(const D&, E));
                    alSwapPredicate(bool (*function)(D, const E&));
                    alSwapPredicate(bool (*function)(const D&, const E&));
    //@}

  #ifndef DOXYGEN
  private:
    typedef alPredicate<E, D>        Inherit;
  #endif // DOXYGEN

};
/*}}}*/

#ifndef DOXYGEN
//class alNotPredicate<E>/*{{{*/
template<typename E>
class alNotPredicate : public alPredicate<E> {

  public:
    //class Driver/*{{{*/
    template<typename D>
    class Driver : public alPredicate<E>::Driver {

      private:
    typedef typename alPredicate<E>::Driver        Inherit;

      private:
        alPredicate<E, D>                _predicate;

      public:
                            Driver(const alPredicate<E, D>& predicate);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E>::Driver*        create_clone() const;

    };
    /*}}}*/

  public:
    template<typename D>
    static  typename alPredicate<E>::Driver*    create_driver(const alPredicate<E, D>& predicate);

};
/*}}}*/

//class alOrPredicate<E>/*{{{*/
template<typename E>
class alOrPredicate : public alPredicate<E> {

  public:
    //class Driver/*{{{*/
    template<typename D1, typename D2>
    class Driver : public alPredicate<E>::Driver {

      private:
    typedef typename alPredicate<E>::Driver        Inherit;

      private:
        alPredicate<E, D1>            _predicate1;
        alPredicate<E, D2>            _predicate2;

      public:
                            Driver(const alPredicate<E, D1>& predicate1,
                               const alPredicate<E, D2>& predicate2);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E>::Driver*        create_clone() const;

    };
    /*}}}*/

  public:
    template<typename D1, typename D2>
    static  typename alPredicate<E>::Driver*    create_driver(const alPredicate<E, D1>& predicate1,
                                 const alPredicate<E, D2>& predicate2);

};
/*}}}*/

//class alAndPredicate<E>/*{{{*/
template<typename E>
class alAndPredicate : public alPredicate<E> {

  public:
    //class Driver/*{{{*/
    template<typename D1, typename D2>
    class Driver : public alPredicate<E>::Driver {

      private:
    typedef typename alPredicate<E>::Driver        Inherit;

      private:
        alPredicate<E, D1>            _predicate1;
        alPredicate<E, D2>            _predicate2;

      public:
                            Driver(const alPredicate<E, D1>& predicate1,
                               const alPredicate<E, D2>& predicate2);
                            Driver(const Driver& driver);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E>::Driver*        create_clone() const;

    };
    /*}}}*/

  public:
    template<typename D1, typename D2>
    static  typename alPredicate<E>::Driver*    create_driver(const alPredicate<E, D1>& predicate1,
                                 const alPredicate<E, D2>& predicate2);

};
/*}}}*/

//class alMemberPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alMemberPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        M                    _member;

      public:
                            Driver(M member);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alPredicate<E, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alMemberDatumPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alMemberDatumPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        M                    _member;
        D                    _datum;

      public:
                            Driver(M member);
                            Driver(M member, const D& datum);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;
    virtual typename alPredicate<E, D>::Driver*   create_clone(const D& datum) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alPredicate<E, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alSwapMemberPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alSwapMemberPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        M                    _member;
        D                    _datum;

      public:
                            Driver(M member);
                            Driver(M member, const D& datum);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;
    virtual typename alPredicate<E, D>::Driver*   create_clone(const D& datum) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alPredicate<E, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alFunctionPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alFunctionPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver  Inherit;

      private:
        F                    _function;

      public:
                            Driver(F function);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alPredicate<E, D>::Driver*    create_driver(F function);

};
/*}}}*/

//class alFunctionDatumPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alFunctionDatumPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        F                    _function;
        D                    _datum;

      public:
                            Driver(F function);
                            Driver(F function, const D& datum);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;
    virtual typename alPredicate<E, D>::Driver*   create_clone(const D& datum) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alPredicate<E, D>::Driver*    create_driver(F function);

};
/*}}}*/

//class alSwapFunctionPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alSwapFunctionPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        F                    _function;
        D                    _datum;

      public:
                            Driver(F function);
                            Driver(F function, const D& datum);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;
    virtual typename alPredicate<E, D>::Driver*   create_clone(const D& datum) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alPredicate<E, D>::Driver*    create_driver(F function);

};
/*}}}*/


//class alAccessorFunctionPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alAccessorFunctionPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename A, typename F>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        A                    _accessor;
        F                    _function;

      public:
                            Driver(const A& accessor, F function);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;

    };
    /*}}}*/

  public:
    template<typename A, typename F>
    static  typename alPredicate<E, D>::Driver*    create_driver(const A& accessor, F function);

};
/*}}}*/


//class alAccessorFunctionDatumPredicate<E, D>/*{{{*/
template<typename E, typename D>
class alAccessorFunctionDatumPredicate : public alPredicate<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename A, typename F>
    class Driver : public alPredicate<E, D>::Driver {

      private:
    typedef typename alPredicate<E, D>::Driver    Inherit;

      private:
        A                    _accessor;
        F                    _function;
        D                    _datum;

      public:
                            Driver(const A& accessor, F function);
                            Driver(const A& accessor, F function, const D& datum);

      public:
    virtual bool                    is_accepted(const E& element) const;
    virtual bool                    is_dynamic_access() const;

      public:
    virtual typename alPredicate<E, D>::Driver*   create_clone() const;
    virtual typename alPredicate<E, D>::Driver*   create_clone(const D& datum) const;

    };
    /*}}}*/

  public:
    template<typename A, typename F>
    static  typename alPredicate<E, D>::Driver*    create_driver(const A& accessor, F function);

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Operators                                                                                     //
//                                                                                                //

//operator!(const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline alPredicate<E>
operator!(const alPredicate<E, D>& predicate)
{
    return alNotPredicate<E>::create_driver(predicate);
}
/*}}}*/

//operator||(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E, typename D1, typename D2>
inline alPredicate<E>
operator||(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
{
    return alOrPredicate<E>::create_driver(predicate1, predicate2);
}
/*}}}*/

//operator&&(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E, typename D1, typename D2>
inline alPredicate<E>
operator&&(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
{
    return alAndPredicate<E>::create_driver(predicate1, predicate2);
}
/*}}}*/



//                                                                                                //
//  alPredicate<E, D> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alPredicate<E, D>::~alPredicate()/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::~alPredicate()
{
    if (is_driven()) {
        delete get_driver();
    }
}
/*}}}*/

//alPredicate<E, D>::alPredicate(Driver* driver)/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(Driver* driver)
  : _driver(driver)
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)())/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)())
  : _driver(alMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)() const)/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)() const)
  : _driver(alMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)(D))/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)(D))
  : _driver(alMemberDatumPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)(D) const)/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)(D) const)
  : _driver(alMemberDatumPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)(const D&))/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)(const D&))
  : _driver(alMemberDatumPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (X::*member)(const D&) const)/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alPredicate<E, D>::alPredicate(bool (X::*member)(const D&) const)
  : _driver(alMemberDatumPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(E))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(E))
  : _driver(alFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(const E&))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(const E&))
  : _driver(alFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(E, D))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(E, D))
  : _driver(alFunctionDatumPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(const E&, D))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(const E&, D))
  : _driver(alFunctionDatumPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(E, const D&))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(E, const D&))
  : _driver(alFunctionDatumPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(bool (*function)(const E&, const D&))/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(bool (*function)(const E&, const D&))
  : _driver(alFunctionDatumPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X))
  : _driver(alAccessorFunctionPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&))
  : _driver(alAccessorFunctionPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, D))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, D))
  : _driver(alAccessorFunctionDatumPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, D))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, D))
  : _driver(alAccessorFunctionDatumPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, const D&))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(X, const D&))
  : _driver(alAccessorFunctionDatumPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, const D&))/*{{{*/
template<typename E, typename D>
template<typename X, typename Y>
inline
alPredicate<E, D>::alPredicate(const alAccessor<E, X, Y>& accessor, bool (*function)(const X&, const D&))
  : _driver(alAccessorFunctionDatumPredicate<E, D>::create_driver(accessor, function))
{
}
/*}}}*/

//alPredicate<E, D>::alPredicate(const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::alPredicate(const alPredicate<E, D>& predicate)
  : _driver(predicate.is_driven() ? predicate.get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alPredicate<E, D>::operator=(Driver* driver)/*{{{*/
template<typename E, typename D>
inline alPredicate<E, D>&
alPredicate<E, D>::operator=(Driver* driver)
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

//alPredicate<E, D>::operator=(const alPredicate<E, D>& predicate)/*{{{*/
template<typename E, typename D>
inline alPredicate<E, D>&
alPredicate<E, D>::operator=(const alPredicate<E, D>& predicate)
{
    return operator=((predicate.is_driven()) ? predicate.get_driver()->create_clone() : NULL);
}
/*}}}*/

//alPredicate<E, D>::operator()() const/*{{{*/
template<typename E, typename D>
inline alPredicate<E, D>
alPredicate<E, D>::operator()() const
{
    return (is_driven()) ? get_driver()->create_clone() : NULL;
}
/*}}}*/

//alPredicate<E, D>::operator()(const D& datum) const/*{{{*/
template<typename E, typename D>
inline alPredicate<E, D>
alPredicate<E, D>::operator()(const D& datum) const
{
    return (is_driven()) ? get_driver()->create_clone(datum) : NULL;
}
/*}}}*/

//alPredicate<E, D>::is_driven() const/*{{{*/
template<typename E, typename D>
inline bool
alPredicate<E, D>::is_driven() const
{
    return (get_driver() != NULL);
}
/*}}}*/

//alPredicate<E, D>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
inline bool
alPredicate<E, D>::is_accepted(const E& element) const
{
    return is_driven() && get_driver()->is_accepted(element);
}
/*}}}*/

//alPredicate<E, D>::is_rejected(const E& element) const/*{{{*/
template<typename E, typename D>
inline bool
alPredicate<E, D>::is_rejected(const E& element) const
{
    return !is_accepted(element);
}
/*}}}*/

//alPredicate<E, D>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
inline bool
alPredicate<E, D>::is_dynamic_access() const
{
    return is_driven() && get_driver()->is_dynamic_access();
}
/*}}}*/

//alPredicate<E, D>::get_driver() const/*{{{*/
template<typename E, typename D>
inline typename alPredicate<E, D>::Driver*
alPredicate<E, D>::get_driver() const
{
    return _driver;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alPredicate<E, D>::Driver implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alPredicate<E, D>::Driver::~Driver()/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::Driver::~Driver()
{
}
/*}}}*/

//alPredicate<E, D>::Driver::Driver()/*{{{*/
template<typename E, typename D>
inline
alPredicate<E, D>::Driver::Driver()
{
}
/*}}}*/

//alPredicate<E, D>::Driver::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
inline typename alPredicate<E, D>::Driver*
alPredicate<E, D>::Driver::create_clone(const D& /*datum*/) const
{
    return create_clone();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapPredicate<E, D> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(E))/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(E))
  : Inherit(alSwapMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(E) const)/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(E) const)
  : Inherit(alSwapMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(const E&))/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(const E&))
  : Inherit(alSwapMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(const E&) const)/*{{{*/
template<typename E, typename D>
template<typename X>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (X::*member)(const E&) const)
  : Inherit(alSwapMemberPredicate<E, D>::create_driver(member))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(D, E))/*{{{*/
template<typename E, typename D>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(D, E))
  : Inherit(alSwapFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(const D&, E))/*{{{*/
template<typename E, typename D>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(const D&, E))
  : Inherit(alSwapFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(D, const E&))/*{{{*/
template<typename E, typename D>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(D, const E&))
  : Inherit(alSwapFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/

//alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(const D&, const E&))/*{{{*/
template<typename E, typename D>
inline
alSwapPredicate<E, D>::alSwapPredicate(bool (*function)(const D&, const E&))
  : Inherit(alSwapFunctionPredicate<E, D>::create_driver(function))
{
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alNotPredicate<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alNotPredicate<E>::create_driver(const alPredicate<E, D>& predicate)/*{{{*/
template<typename E>
template<typename D>
inline typename alPredicate<E>::Driver*
alNotPredicate<E>::create_driver(const alPredicate<E, D>& predicate)
{
    return new Driver<D>(predicate);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alNotPredicate<E>::Driver<D> implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alNotPredicate<E>::Driver<D>::Driver(const alPredicate<E, D>& predicate)/*{{{*/
template<typename E>
template<typename D>
inline
alNotPredicate<E>::Driver<D>::Driver(const alPredicate<E, D>& predicate)
  : Inherit()
  , _predicate(predicate)
{
}
/*}}}*/

//alNotPredicate<E>::Driver<D>::Driver(const Driver& driver)/*{{{*/
template<typename E>
template<typename D>
inline
alNotPredicate<E>::Driver<D>::Driver(const Driver& driver)
  : Inherit()
  , _predicate(driver._predicate)
{
}
/*}}}*/

//alNotPredicate<E>::Driver<D>::is_accepted(const E& element) const/*{{{*/
template<typename E>
template<typename D>
inline bool
alNotPredicate<E>::Driver<D>::is_accepted(const E& element) const
{
    return _predicate.is_rejected(element);
}
/*}}}*/

//alNotPredicate<E>::Driver<D>::is_dynamic_access() const/*{{{*/
template<typename E>
template<typename D>
inline bool
alNotPredicate<E>::Driver<D>::is_dynamic_access() const
{
    return _predicate.is_dynamic_access();
}
/*}}}*/

//alNotPredicate<E>::Driver<D>::create_clone() const/*{{{*/
template<typename E>
template<typename D>
inline typename alPredicate<E>::Driver*
alNotPredicate<E>::Driver<D>::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alOrPredicate<E> implementation                                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alOrPredicate<E>::create_driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline typename alPredicate<E>::Driver*
alOrPredicate<E>::create_driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
{
    return new Driver<D1, D2>(predicate1, predicate2);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alOrPredicate<E>::Driver<D1, D2> implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alOrPredicate<E>::Driver<D1, D2>::Driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline
alOrPredicate<E>::Driver<D1, D2>::Driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
  : Inherit()
  , _predicate1(predicate1)
  , _predicate2(predicate2)
{
}
/*}}}*/

//alOrPredicate<E>::Driver<D1, D2>::Driver(const Driver& driver)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline
alOrPredicate<E>::Driver<D1, D2>::Driver(const Driver& driver)
  : Inherit()
  , _predicate1(driver._predicate1)
  , _predicate2(driver._predicate2)
{
}
/*}}}*/

//alOrPredicate<E>::Driver<D1, D2>::is_accepted(const E& element) const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline bool
alOrPredicate<E>::Driver<D1, D2>::is_accepted(const E& element) const
{
    return _predicate1.is_accepted(element) || _predicate2.is_accepted(element);
}
/*}}}*/

//alOrPredicate<E>::Driver<D1, D2>::is_dynamic_access() const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline bool
alOrPredicate<E>::Driver<D1, D2>::is_dynamic_access() const
{
    return _predicate1.is_dynamic_access() && _predicate2.is_dynamic_access();
}
/*}}}*/

//alOrPredicate<E>::Driver<D1, D2>::create_clone() const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline typename alPredicate<E>::Driver*
alOrPredicate<E>::Driver<D1, D2>::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAndPredicate<E> implementation                                                                //
//                                                                                                //

#ifndef DOXYGEN
//alAndPredicate<E>::create_driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline typename alPredicate<E>::Driver*
alAndPredicate<E>::create_driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
{
    return new Driver<D1, D2>(predicate1, predicate2);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAndPredicate<E>::Driver<D1, D2> implementation                                                //
//                                                                                                //

#ifndef DOXYGEN
//alAndPredicate<E>::Driver<D1, D2>::Driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline
alAndPredicate<E>::Driver<D1, D2>::Driver(const alPredicate<E, D1>& predicate1, const alPredicate<E, D2>& predicate2)
  : Inherit()
  , _predicate1(predicate1)
  , _predicate2(predicate2)
{
}
/*}}}*/

//alAndPredicate<E>::Driver<D1, D2>::Driver(const Driver& driver)/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline
alAndPredicate<E>::Driver<D1, D2>::Driver(const Driver& driver)
  : Inherit()
  , _predicate1(driver._predicate1)
  , _predicate2(driver._predicate2)
{
}
/*}}}*/

//alAndPredicate<E>::Driver<D1, D2>::is_accepted(const E& element) const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline bool
alAndPredicate<E>::Driver<D1, D2>::is_accepted(const E& element) const
{
    return _predicate1.is_accepted(element) && _predicate2.is_accepted(element);
}
/*}}}*/

//alAndPredicate<E>::Driver<D1, D2>::is_dynamic_access() const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline bool
alAndPredicate<E>::Driver<D1, D2>::is_dynamic_access() const
{
    return _predicate1.is_dynamic_access() && _predicate2.is_dynamic_access();
}
/*}}}*/

//alAndPredicate<E>::Driver<D1, D2>::create_clone() const/*{{{*/
template<typename E>
template<typename D1, typename D2>
inline typename alPredicate<E>::Driver*
alAndPredicate<E>::Driver<D1, D2>::create_clone() const
{
    return new Driver(*this);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberPredicate<E, D> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alMemberPredicate<E, D>::create_driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alMemberPredicate<E, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberPredicate<E, D>::Driver<M> implementation                                               //
//                                                                                                //

#ifndef DOXYGEN
//alMemberPredicate<E, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
alMemberPredicate<E, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
{
}
/*}}}*/

//alMemberPredicate<E, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alMemberPredicate<E, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMemberPredicate<E, D>::Driver<M>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alMemberPredicate<E, D>::Driver<M>::is_accepted(const E& element) const
{
    return (get_reference(element).*_member)();
}
/*}}}*/

//alMemberPredicate<E, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alMemberPredicate<E, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberDatumPredicate<E, D> implementation                                                     //
//                                                                                                //

#ifndef DOXYGEN
//alMemberDatumPredicate<E, D>::create_driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alMemberDatumPredicate<E, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberDatumPredicate<E, D>::Driver<M> implementation                                          //
//                                                                                                //

#ifndef DOXYGEN
//alMemberDatumPredicate<E, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
alMemberDatumPredicate<E, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
  , _datum(D())
{
}
/*}}}*/

//alMemberDatumPredicate<E, D>::Driver<M>::Driver(M member, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
alMemberDatumPredicate<E, D>::Driver<M>::Driver(M member, const D& datum)
  : Inherit()
  , _member(member)
  , _datum(datum)
{
}
/*}}}*/

//alMemberDatumPredicate<E, D>::Driver<M>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alMemberDatumPredicate<E, D>::Driver<M>::is_accepted(const E& element) const
{
    return (get_reference(element).*_member)(_datum);
}
/*}}}*/

//alMemberDatumPredicate<E, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alMemberDatumPredicate<E, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMemberDatumPredicate<E, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alMemberDatumPredicate<E, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member, _datum);
}
/*}}}*/

//alMemberDatumPredicate<E, D>::Driver<M>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alMemberDatumPredicate<E, D>::Driver<M>::create_clone(const D& datum) const
{
    return new Driver<M>(_member, datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapMemberPredicate<E, D> implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alSwapMemberPredicate<E, D>::create_driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alSwapMemberPredicate<E, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapMemberPredicate<E, D>::Driver<M> implementation                                           //
//                                                                                                //

#ifndef DOXYGEN
//alSwapMemberPredicate<E, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
alSwapMemberPredicate<E, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
  , _datum(D())
{
}
/*}}}*/

//alSwapMemberPredicate<E, D>::Driver<M>::Driver(M member, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
alSwapMemberPredicate<E, D>::Driver<M>::Driver(M member, const D& datum)
  : Inherit()
  , _member(member)
  , _datum(datum)
{
}
/*}}}*/

//alSwapMemberPredicate<E, D>::Driver<M>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alSwapMemberPredicate<E, D>::Driver<M>::is_accepted(const E& element) const
{
    return (get_reference(_datum).*_member)(element);
}
/*}}}*/

//alSwapMemberPredicate<E, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline bool
alSwapMemberPredicate<E, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSwapMemberPredicate<E, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alSwapMemberPredicate<E, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member, _datum);
}
/*}}}*/

//alSwapMemberPredicate<E, D>::Driver<M>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alPredicate<E, D>::Driver*
alSwapMemberPredicate<E, D>::Driver<M>::create_clone(const D& datum) const
{
    return new Driver<M>(_member, datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionPredicate<E, D> implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionPredicate<E, D>::create_driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alFunctionPredicate<E, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionPredicate<E, D>::Driver<F> implementation                                             //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionPredicate<E, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
alFunctionPredicate<E, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
{
}
/*}}}*/

//alFunctionPredicate<E, D>::Driver<F>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alFunctionPredicate<E, D>::Driver<F>::is_accepted(const E& element) const
{
    return _function(element);
}
/*}}}*/

//alFunctionPredicate<E, D>::Driver<F>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alFunctionPredicate<E, D>::Driver<F>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alFunctionPredicate<E, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alFunctionPredicate<E, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionDatumPredicate<E, D> implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionDatumPredicate<E, D>::create_driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alFunctionDatumPredicate<E, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionDatumPredicate<E, D>::Driver<F> implementation                                        //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionDatumPredicate<E, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
alFunctionDatumPredicate<E, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//alFunctionDatumPredicate<E, D>::Driver<F>::Driver(F function, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
alFunctionDatumPredicate<E, D>::Driver<F>::Driver(F function, const D& datum)
  : Inherit()
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//alFunctionDatumPredicate<E, D>::Driver<F>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alFunctionDatumPredicate<E, D>::Driver<F>::is_accepted(const E& element) const
{
    return _function(element, _datum);
}
/*}}}*/

//alFunctionDatumPredicate<E, D>::Driver<F>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alFunctionDatumPredicate<E, D>::Driver<F>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alFunctionDatumPredicate<E, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alFunctionDatumPredicate<E, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function, _datum);
}
/*}}}*/

//alFunctionDatumPredicate<E, D>::Driver<F>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alFunctionDatumPredicate<E, D>::Driver<F>::create_clone(const D& datum) const
{
    return new Driver<F>(_function, datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapFunctionPredicate<E, D> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alSwapFunctionPredicate<E, D>::create_driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alSwapFunctionPredicate<E, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapFunctionPredicate<E, D>::Driver<F> implementation                                         //
//                                                                                                //

#ifndef DOXYGEN
//alSwapFunctionPredicate<E, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
alSwapFunctionPredicate<E, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//alSwapFunctionPredicate<E, D>::Driver<F>::Driver(F function, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
alSwapFunctionPredicate<E, D>::Driver<F>::Driver(F function, const D& datum)
  : Inherit()
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//alSwapFunctionPredicate<E, D>::Driver<F>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alSwapFunctionPredicate<E, D>::Driver<F>::is_accepted(const E& element) const
{
    return _function(_datum, element);
}
/*}}}*/

//alSwapFunctionPredicate<E, D>::Driver<F>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline bool
alSwapFunctionPredicate<E, D>::Driver<F>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSwapFunctionPredicate<E, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alSwapFunctionPredicate<E, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function, _datum);
}
/*}}}*/

//alSwapFunctionPredicate<E, D>::Driver<F>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alPredicate<E, D>::Driver*
alSwapFunctionPredicate<E, D>::Driver<F>::create_clone(const D& datum) const
{
    return new Driver<F>(_function, datum);
}
/*}}}*/
#endif // DOXYGEN


//                                                                                                //
//  alAccessorFunctionPredicate<E, D> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alAccessorFunctionPredicate<E, D>::create_driver(const A& accessor, F function)/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline typename alPredicate<E, D>::Driver*
alAccessorFunctionPredicate<E, D>::create_driver(const A& accessor, F function)
{
    return new Driver<A, F>(accessor, function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAccessorFunctionPredicate<E, D>::Driver<X> implementation                                         //
//                                                                                                //

#ifndef DOXYGEN
//alAccessorFunctionPredicate<E, D>::Driver<X>::Driver(const A& accessor, F function)/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline
alAccessorFunctionPredicate<E, D>::Driver<A, F>::Driver(const A& accessor, F function)
  : Inherit()
  , _accessor(accessor)
  , _function(function)
{
}
/*}}}*/

//alAccessorFunctionPredicate<E, D>::Driver<X>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline bool
alAccessorFunctionPredicate<E, D>::Driver<A, F>::is_accepted(const E& element) const
{
    return _function(_accessor.get_associate(element));
}
/*}}}*/

//alAccessorFunctionPredicate<E, D>::Driver<X>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline bool
alAccessorFunctionPredicate<E, D>::Driver<A, F>::is_dynamic_access() const
{
    return _accessor.is_dynamic_access();
}
/*}}}*/

//alAccessorFunctionPredicate<E, D>::Driver<X>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline typename alPredicate<E, D>::Driver*
alAccessorFunctionPredicate<E, D>::Driver<A, F>::create_clone() const
{
    return new Driver<A, F>(_accessor, _function);
}
/*}}}*/
#endif // DOXYGEN


//                                                                                                //
//  alAccessorFunctionPredicate<E, D> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alAccessorFunctionDatumPredicate<E, D>::create_driver(const A& accessor, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline typename alPredicate<E, D>::Driver*
alAccessorFunctionDatumPredicate<E, D>::create_driver(const A& accessor, F function)
{
    return new Driver<A, F>(accessor, function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAccessorFunctionDatumPredicate<E, D>::Driver<X> implementation                                         //
//                                                                                                //

#ifndef DOXYGEN
//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::Driver(const A& accessor, F function)/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::Driver(const A& accessor, F function)
  : Inherit()
  , _accessor(accessor)
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::Driver(const A& accessor, F function, const D& datum)/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::Driver(const A& accessor, F function, const D& datum)
  : Inherit()
  , _accessor(accessor)
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::is_accepted(const E& element) const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline bool
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::is_accepted(const E& element) const
{
    return _function(_accessor.get_associate(element), _datum);
}
/*}}}*/

//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::is_dynamic_access() const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline bool
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::is_dynamic_access() const
{
    return _accessor.is_dynamic_access();
}
/*}}}*/

//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline typename alPredicate<E, D>::Driver*
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::create_clone() const
{
    return new Driver<A, F>(_accessor, _function, _datum);
}
/*}}}*/

//alAccessorFunctionDatumPredicate<E, D>::Driver<X>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename D>
template<typename A, typename F>
inline typename alPredicate<E, D>::Driver*
alAccessorFunctionDatumPredicate<E, D>::Driver<A, F>::create_clone(const D& datum) const
{
    return new Driver<A, F>(_accessor, _function, datum);
}
/*}}}*/
#endif // DOXYGEN

//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the definitions of the alPredicate, alPredicate::Driver and
        alSwapPredicate classes and the corresponding logical operators.
    */
/*}}}*/

//class alPredicate<E, D>/*{{{*/
/*!\class    Predicate
    \brief    This concrete class implements the concept of \em "predicate".
    */
/*}}}*/

//class alPredicate<E, D>::Driver/*{{{*/
/*!\class    alPredicate::Driver
    \brief    This abstract class introduces the concept of \em "predicate driver".
    */
/*}}}*/

//class alSwapPredicate<E, D>/*{{{*/
/*!\class    SwapPredicate
    \brief    This concrete class implements the concept of \em "swap predicate".
    */
/*}}}*/



//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  transform alAccessor into alPredicate                                                         //
//                                                                                                //

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator==(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return misc::alPredicate<E, A>(accessor, &misc::alEqual<A>::is)(datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator<(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return misc::alPredicate<E, A>(accessor, &misc::alLess<A>::is)(datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator>(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return misc::alPredicate<E, A>(accessor, &misc::alGreater<A>::is)(datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator!=(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return !(accessor == datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator<=(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return !(accessor > datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator>=(const misc::alAccessor<E, A, X>& accessor, const A& datum)
{
  return !(accessor < datum);
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator==(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor == datum;
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator<(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor > datum;
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator>(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor < datum;
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator!=(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor != datum;
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator<=(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor >= datum;
}

template<typename E, typename A, typename X>
inline
misc::alPredicate<E, A> operator>=(const A& datum, const misc::alAccessor<E, A, X>& accessor)
{
  return accessor <= datum;
}

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
