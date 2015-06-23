//                                                                                                //
//  File: misc_collection_action.h                                                                                //
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

namespace misc {
/*}}}*/



//                                                                                                //
//  Declarations                                                                                  //
//                                                                                                //

//class alAction<E, D>/*{{{*/
template<typename E, typename D = bool>
class alAction {

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
    //!\name Accessors:
    //@{
    virtual Driver*                create_clone() const PURE;
    virtual Driver*                create_clone(D datum) const;
    //@}

      public:
    //!\name Managers:
    //@{
    virtual void                apply(E element) const PURE;
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
                    ~alAction();
    //@}

  public:
    //!\name Default Constructor:
    //@{
                    alAction(Driver* driver = NULL);
    //@}

  public:
    //!\name Copy Constructor:
    //@{
                    alAction(const alAction<E, D>& action);
    //@}

  public:
    //!\name Member Based Constructor:
    //@{
        template<typename R, typename X>
                    alAction(R (X::*member)());
        template<typename R, typename X>
                    alAction(R (X::*member)() const);
        template<typename R, typename X>
                    alAction(R (X::*member)(D));
        template<typename R, typename X>
                    alAction(R (X::*member)(D) const);
    //@}

  public:
    //!\name Function Based Constructor:
    //@{
        template<typename R>    alAction(R (*function)(E));
        template<typename R>    alAction(R (*function)(E, D));
    //@}

  public:
    //!\name Assignment Operators:
    //@{
        alAction<E, D>&        operator=(Driver* driver);
        alAction<E, D>&        operator=(const alAction<E, D>& action);
    //@}

  public:
    //!\name Functional Operators:
    //@{
        alAction<E, D>        operator()() const;
        alAction<E, D>        operator()(D datum) const;
    //@}

  public:
    //!\name Predicates:
    //@{
        bool            is_driven() const;
    //@}

  public:
    //!\name Accessors:
    //@{
        Driver*            get_driver() const;
    //@}

  public:
    //!\name Managers:
    //@{
        void            apply(E element) const;
    //@}

  #ifndef DOXYGEN
  private:
        Driver*            _driver;
  #endif // DOXYGEN

};
/*}}}*/

#ifndef DOXYGEN
//class UnaryMember<E, D>/*{{{*/
template<typename E, typename D>
class UnaryMember : public alAction<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alAction<E, D>::Driver {

      private:
    typedef typename alAction<E, D>::Driver        Inherit;

      private:
        M                    _member;

      public:
                            Driver(M member);

      public:
    virtual typename alAction<E, D>::Driver*        create_clone() const;

      public:
    virtual void                    apply(E element) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alAction<E, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class BinaryMember<E, D>/*{{{*/
template<typename E, typename D>
class BinaryMember : public alAction<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alAction<E, D>::Driver {

      private:
    typedef typename alAction<E, D>::Driver        Inherit;

      private:
        M                    _member;
        D                    _datum;

      public:
                            Driver(M member);
                            Driver(M member, D datum);

      public:
    virtual typename alAction<E, D>::Driver*        create_clone() const;
    virtual typename alAction<E, D>::Driver*        create_clone(D datum) const;

      public:
    virtual void                    apply(E element) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alAction<E, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class UnaryFunction<E, D>/*{{{*/
template<typename E, typename D>
class UnaryFunction : public alAction<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alAction<E, D>::Driver {

      private:
    typedef typename alAction<E, D>::Driver        Inherit;

      private:
        F                    _function;

      public:
                            Driver(F function);

      public:
    virtual typename alAction<E, D>::Driver*        create_clone() const;

      public:
    virtual void                    apply(E element) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alAction<E, D>::Driver*    create_driver(F function);

};
/*}}}*/

//class BinaryFunction<E, D>/*{{{*/
template<typename E, typename D>
class BinaryFunction : public alAction<E, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alAction<E, D>::Driver {

      private:
    typedef typename alAction<E, D>::Driver        Inherit;

      private:
        F                    _function;
        D                    _datum;

      public:
                            Driver(F function);
                            Driver(F function, D datum);

      public:
    virtual typename alAction<E, D>::Driver*        create_clone() const;
    virtual typename alAction<E, D>::Driver*        create_clone(D datum) const;

      public:
    virtual void                    apply(E element) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alAction<E, D>::Driver*    create_driver(F function);

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAction<E, D> implementation                                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alAction<E, D>::~alAction()/*{{{*/
template<typename E, typename D>
inline
alAction<E, D>::~alAction()
{
    if (is_driven()) {
        delete get_driver();
    }
}
/*}}}*/

//alAction<E, D>::alAction(Driver* driver)/*{{{*/
template<typename E, typename D>
inline
alAction<E, D>::alAction(Driver* driver)
  : _driver(driver)
{
}
/*}}}*/

//alAction<E, D>::alAction(R (X::*member)())/*{{{*/
template<typename E, typename D>
template<typename R, typename X>
inline
alAction<E, D>::alAction(R (X::*member)())
  : _driver(UnaryMember<E, D>::create_driver(member))
{
}
/*}}}*/

//alAction<E, D>::alAction(R (X::*member)() const)/*{{{*/
template<typename E, typename D>
template<typename R, typename X>
inline
alAction<E, D>::alAction(R (X::*member)() const)
  : _driver(UnaryMember<E, D>::create_driver(member))
{
}
/*}}}*/

//alAction<E, D>::alAction(R (X::*member)(D))/*{{{*/
template<typename E, typename D>
template<typename R, typename X>
inline
alAction<E, D>::alAction(R (X::*member)(D))
  : _driver(BinaryMember<E, D>::create_driver(member))
{
}
/*}}}*/

//alAction<E, D>::alAction(R (X::*member)(D) const)/*{{{*/
template<typename E, typename D>
template<typename R, typename X>
inline
alAction<E, D>::alAction(R (X::*member)(D) const)
  : _driver(BinaryMember<E, D>::create_driver(member))
{
}
/*}}}*/

//alAction<E, D>::alAction(R (*function)(E))/*{{{*/
template<typename E, typename D>
template<typename R>
inline
alAction<E, D>::alAction(R (*function)(E))
  : _driver(UnaryFunction<E, D>::create_driver(function))
{
}
/*}}}*/

//alAction<E, D>::alAction(R (*function)(E, D))/*{{{*/
template<typename E, typename D>
template<typename R>
inline
alAction<E, D>::alAction(R (*function)(E, D))
  : _driver(BinaryFunction<E, D>::create_driver(function))
{
}
/*}}}*/

//alAction<E, D>::alAction(const alAction<E, D>& action)/*{{{*/
template<typename E, typename D>
inline
alAction<E, D>::alAction(const alAction<E, D>& action)
  : _driver(action.is_driven() ? action.get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alAction<E, D>::operator=(Driver* driver)/*{{{*/
template<typename E, typename D>
inline alAction<E, D>&
alAction<E, D>::operator=(Driver* driver)
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

//alAction<E, D>::operator=(const alAction<E, D>& action)/*{{{*/
template<typename E, typename D>
inline alAction<E, D>&
alAction<E, D>::operator=(const alAction<E, D>& action)
{
    return operator=((action.is_driven()) ? action.get_driver()->create_clone() : NULL);
}
/*}}}*/

//alAction<E, D>::operator()() const/*{{{*/
template<typename E, typename D>
inline alAction<E, D>
alAction<E, D>::operator()() const
{
    return (is_driven()) ? get_driver()->create_clone() : NULL;
}
/*}}}*/

//alAction<E, D>::operator()(D datum) const/*{{{*/
template<typename E, typename D>
inline alAction<E, D>
alAction<E, D>::operator()(D datum) const
{
    return (is_driven()) ? get_driver()->create_clone(datum) : NULL;
}
/*}}}*/

//alAction<E, D>::is_driven() const/*{{{*/
template<typename E, typename D>
inline bool
alAction<E, D>::is_driven() const
{
    return (get_driver() != NULL);
}
/*}}}*/

//alAction<E, D>::get_driver() const/*{{{*/
template<typename E, typename D>
inline typename alAction<E, D>::Driver*
alAction<E, D>::get_driver() const
{
    return _driver;
}
/*}}}*/

//alAction<E, D>::apply(E element) const/*{{{*/
template<typename E, typename D>
inline void
alAction<E, D>::apply(E element) const
{
    if (is_driven()) {
        get_driver()->apply(element);
    }
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAction<E, D>::Driver implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//alAction<E, D>::Driver::~Driver()/*{{{*/
template<typename E, typename D>
inline
alAction<E, D>::Driver::~Driver()
{
}
/*}}}*/

//alAction<E, D>::Driver::Driver()/*{{{*/
template<typename E, typename D>
inline
alAction<E, D>::Driver::Driver()
{
}
/*}}}*/

//alAction<E, D>::Driver::create_clone(D datum) const/*{{{*/
template<typename E, typename D>
inline typename alAction<E, D>::Driver*
alAction<E, D>::Driver::create_clone(D /*datum*/) const
{
    return create_clone();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  UnaryMember<E, D> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//UnaryMember<E, D>::create_driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alAction<E, D>::Driver*
UnaryMember<E, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  UnaryMember<E, D>::Driver<M> implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//UnaryMember<E, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
UnaryMember<E, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
{
}
/*}}}*/

//UnaryMember<E, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alAction<E, D>::Driver*
UnaryMember<E, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member);
}
/*}}}*/

//UnaryMember<E, D>::Driver<M>::apply(E element) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline void
UnaryMember<E, D>::Driver<M>::apply(E element) const
{
    (get_reference(element).*_member)();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  BinaryMember<E, D> implementation                                                             //
//                                                                                                //

#ifndef DOXYGEN
//BinaryMember<E, D>::create_driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alAction<E, D>::Driver*
BinaryMember<E, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  BinaryMember<E, D>::Driver<M> implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//BinaryMember<E, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
BinaryMember<E, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
  , _datum(D())
{
}
/*}}}*/

//BinaryMember<E, D>::Driver<M>::Driver(M member, D datum)/*{{{*/
template<typename E, typename D>
template<typename M>
inline
BinaryMember<E, D>::Driver<M>::Driver(M member, D datum)
  : Inherit()
  , _member(member)
  , _datum(datum)
{
}
/*}}}*/

//BinaryMember<E, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alAction<E, D>::Driver*
BinaryMember<E, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member, _datum);
}
/*}}}*/

//BinaryMember<E, D>::Driver<M>::create_clone(D datum) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline typename alAction<E, D>::Driver*
BinaryMember<E, D>::Driver<M>::create_clone(D datum) const
{
    return new Driver<M>(_member, datum);
}
/*}}}*/

//BinaryMember<E, D>::Driver<M>::apply(E element) const/*{{{*/
template<typename E, typename D>
template<typename M>
inline void
BinaryMember<E, D>::Driver<M>::apply(E element) const
{
    (get_reference(element).*_member)(_datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  UnaryFunction<E, D> implementation                                                            //
//                                                                                                //

#ifndef DOXYGEN
//UnaryFunction<E, D>::create_driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alAction<E, D>::Driver*
UnaryFunction<E, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  UnaryFunction<E, D>::Driver<F> implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//UnaryFunction<E, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
UnaryFunction<E, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
{
}
/*}}}*/

//UnaryFunction<E, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alAction<E, D>::Driver*
UnaryFunction<E, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function);
}
/*}}}*/

//UnaryFunction<E, D>::Driver<F>::apply(E element) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline void
UnaryFunction<E, D>::Driver<F>::apply(E element) const
{
    _function(element);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  BinaryFunction<E, D> implementation                                                           //
//                                                                                                //

#ifndef DOXYGEN
//BinaryFunction<E, D>::create_driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alAction<E, D>::Driver*
BinaryFunction<E, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  BinaryFunction<E, D>::Driver<F> implementation                                                //
//                                                                                                //

#ifndef DOXYGEN
//BinaryFunction<E, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
BinaryFunction<E, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//BinaryFunction<E, D>::Driver<F>::Driver(F function, D datum)/*{{{*/
template<typename E, typename D>
template<typename F>
inline
BinaryFunction<E, D>::Driver<F>::Driver(F function, D datum)
  : Inherit()
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//BinaryFunction<E, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alAction<E, D>::Driver*
BinaryFunction<E, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function, _datum);
}
/*}}}*/

//BinaryFunction<E, D>::Driver<F>::create_clone(D datum) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline typename alAction<E, D>::Driver*
BinaryFunction<E, D>::Driver<F>::create_clone(D datum) const
{
    return new Driver<F>(_function, datum);
}
/*}}}*/

//BinaryFunction<E, D>::Driver<F>::apply(E element) const/*{{{*/
template<typename E, typename D>
template<typename F>
inline void
BinaryFunction<E, D>::Driver<F>::apply(E element) const
{
    _function(element, _datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the definitions of the alAction and alAction::Driver classes.
    */
/*}}}*/

//class alAction<E, D>/*{{{*/
/*!\class    Action
    \brief    This concrete class implements the concept of \em "action".
    */
/*}}}*/

//class alAction<E, D>::Driver/*{{{*/
/*!\class    alAction::Driver
    \brief    This abstract class introduces the concept of \em "action driver".
    */
/*}}}*/



//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
