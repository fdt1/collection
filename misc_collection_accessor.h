//                                                                                                //
//  File: misc_collection_accessor.h                                                                              //
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

//class alAccessor<E, A, D = bool>/*{{{*/
template<typename E, typename A, typename D = bool>
class alAccessor {

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
    virtual bool                is_dynamic_access() const PURE;
    //@}

      public:
    virtual Driver*                create_clone() const PURE;
    virtual Driver*                create_clone(const D& datum) const;
    virtual A                get_associate(const E& element) const PURE;

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
                    ~alAccessor();
    //@}

  public:
    //!\name Default Constructor:
    //@{
                    alAccessor(Driver* driver = NULL);
    //@}

  public:
    //!\name Copy Constructor:
    //@{
                    alAccessor(const alAccessor<E, A, D>& accessor);
    //@}

  public:
    //!\name Member Based Constructors:
    //@{
        template<typename X>    alAccessor(A (X::*member)());
        template<typename X>    alAccessor(A (X::*member)() const);
        template<typename X>    alAccessor(A (X::*member)(D));
        template<typename X>    alAccessor(A (X::*member)(D) const);
        template<typename X>    alAccessor(A (X::*member)(const D&));
        template<typename X>    alAccessor(A (X::*member)(const D&) const);
        template<typename X>    alAccessor(const A& (X::*member)());
        template<typename X>    alAccessor(const A& (X::*member)() const);
        template<typename X>    alAccessor(const A& (X::*member)(D));
        template<typename X>    alAccessor(const A& (X::*member)(D) const);
        template<typename X>    alAccessor(const A& (X::*member)(const D&));
        template<typename X>    alAccessor(const A& (X::*member)(const D&) const);
    //@}

  public:
    //!\name Function Based Constructors:
    //@{
                    alAccessor(A (*function)(E));
                    alAccessor(A (*function)(const E&));
                    alAccessor(A (*function)(E, D));
                    alAccessor(A (*function)(const E&, D));
                    alAccessor(A (*function)(E, const D&));
                    alAccessor(A (*function)(const E&, const D&));
                    alAccessor(const A& (*function)(E));
                    alAccessor(const A& (*function)(const E&));
                    alAccessor(const A& (*function)(E, D));
                    alAccessor(const A& (*function)(const E&, D));
                    alAccessor(const A& (*function)(E, const D&));
                    alAccessor(const A& (*function)(const E&, const D&));
    //@}

  public:
    //!\name Assignment Operators:
    //@{
        alAccessor<E, A, D>&        operator=(Driver* driver);
        alAccessor<E, A, D>&        operator=(const alAccessor<E, A, D>& accessor);
    //@}

  public:
    //!\name Functional Operators:
    //@{
        alAccessor<E, A, D>        operator()() const;
        alAccessor<E, A, D>        operator()(const D& datum) const;
    //@}

  public:
    //!\name Predicates:
    //@{
        bool            is_driven() const;
        //! return true if accessor supports dynamic modifications on datas
        bool            is_dynamic_access() const;
    //@}

  public:
    //!\name alAccessors:
    //@{
        Driver*            get_driver() const;
        A                get_associate(const E& element) const;
    //@}

  #ifndef DOXYGEN
  private:
        Driver*            _driver;
  #endif // DOXYGEN

};
/*}}}*/

//class alSwapAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alSwapAccessor :public alAccessor<E, A, D> {

  public:
    //!\name Member Based Constructors:
    //@{
        template<typename X>    alSwapAccessor(A (X::*member)(E));
        template<typename X>    alSwapAccessor(A (X::*member)(E) const);
        template<typename X>    alSwapAccessor(A (X::*member)(const E&));
        template<typename X>    alSwapAccessor(A (X::*member)(const E&) const);
        template<typename X>    alSwapAccessor(const A& (X::*member)(E));
        template<typename X>    alSwapAccessor(const A& (X::*member)(E) const);
        template<typename X>    alSwapAccessor(const A& (X::*member)(const E&));
        template<typename X>    alSwapAccessor(const A& (X::*member)(const E&) const);
    //@}

  public:
    //!\name Function Based Constructors:
    //@{
                    alSwapAccessor(A (*function)(D, E));
                    alSwapAccessor(A (*function)(const D&, E));
                    alSwapAccessor(A (*function)(D, const E&));
                    alSwapAccessor(A (*function)(const D&, const E&));
                    alSwapAccessor(const A& (*function)(D, E));
                    alSwapAccessor(const A& (*function)(const D&, E));
                    alSwapAccessor(const A& (*function)(D, const E&));
                    alSwapAccessor(const A& (*function)(const D&, const E&));
    //@}

  #ifndef DOXYGEN
  private:
    typedef alAccessor<E, A, D>        Inherit;

  #endif // DOXYGEN

};
/*}}}*/

#ifndef DOXYGEN
//class alMemberAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alMemberAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        M                    _member;

      public:
                            Driver(M member);
      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alMemberDatumAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alMemberDatumAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        M                    _member;
        D                    _datum;

      public:
                            Driver(M member);
                            Driver(M member, const D& datum);

      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual typename alAccessor<E, A, D>::Driver* create_clone(const D& datum) const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alSwapMemberAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alSwapMemberAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename M>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        M                    _member;
        D                    _datum;

      public:
                            Driver(M member);
                            Driver(M member, const D& datum);

      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual typename alAccessor<E, A, D>::Driver* create_clone(const D& datum) const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename M>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(M member);

};
/*}}}*/

//class alFunctionAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alFunctionAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        F                    _function;

      public:
                            Driver(F function);

      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(F function);

};
/*}}}*/

//class alFunctionDatumAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alFunctionDatumAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        F                    _function;
        D                    _datum;

      public:
                            Driver(F function);
                            Driver(F function, const D& datum);

      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual typename alAccessor<E, A, D>::Driver* create_clone(const D& datum) const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(F function);

};
/*}}}*/

//class alSwapFunctionAccessor<E, A, D>/*{{{*/
template<typename E, typename A, typename D>
class alSwapFunctionAccessor : public alAccessor<E, A, D> {

  public:
    //class Driver/*{{{*/
    template<typename F>
    class Driver : public alAccessor<E, A, D>::Driver {

      private:
    typedef typename alAccessor<E, A, D>::Driver  Inherit;

      private:
        F                    _function;
        D                    _datum;

      public:
                            Driver(F function);
                            Driver(F function, const D& datum);

      public:
    virtual bool                is_dynamic_access() const;

      public:
    virtual typename alAccessor<E, A, D>::Driver* create_clone() const;
    virtual typename alAccessor<E, A, D>::Driver* create_clone(const D& datum) const;
    virtual A                    get_associate(const E& element) const;

    };
    /*}}}*/

  public:
    template<typename F>
    static  typename alAccessor<E, A, D>::Driver*    create_driver(F function);

};
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAccessor<E, A, D> implementation                                                              //
//                                                                                                //

#ifndef DOXYGEN
//alAccessor<E, A, D>::~alAccessor()/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::~alAccessor()
{
    if (is_driven()) {
        delete get_driver();
    }
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(Driver* driver)/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(Driver* driver)
  : _driver(driver)
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)())/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)())
  : _driver(alMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)() const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)() const)
  : _driver(alMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)(D))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)(D))
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)(D) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)(D) const)
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)(const D&))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)(const D&))
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (X::*member)(const D&) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(A (X::*member)(const D&) const)
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)())/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)())
  : _driver(alMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)() const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)() const)
  : _driver(alMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)(D))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)(D))
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)(D) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)(D) const)
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)(const D&))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)(const D&))
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (X::*member)(const D&) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alAccessor<E, A, D>::alAccessor(const A& (X::*member)(const D&) const)
  : _driver(alMemberDatumAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(E))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(E))
  : _driver(alFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(const E&))
  : _driver(alFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(E, D))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(E, D))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(const E&, D))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(const E&, D))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(E, const D&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(E, const D&))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(A (*function)(const E&, const D&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(A (*function)(const E&, const D&))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(E))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(E))
  : _driver(alFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&))
  : _driver(alFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(E, D))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(E, D))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&, D))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&, D))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(E, const D&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(E, const D&))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&, const D&))/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const A& (*function)(const E&, const D&))
  : _driver(alFunctionDatumAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alAccessor<E, A, D>::alAccessor(const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::alAccessor(const alAccessor<E, A, D>& accessor)
  : _driver(accessor.is_driven() ? accessor.get_driver()->create_clone() : NULL)
{
}
/*}}}*/

//alAccessor<E, A, D>::operator=(Driver* driver)/*{{{*/
template<typename E, typename A, typename D>
inline alAccessor<E, A, D>&
alAccessor<E, A, D>::operator=(Driver* driver)
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

//alAccessor<E, A, D>::operator=(const alAccessor<E, A, D>& accessor)/*{{{*/
template<typename E, typename A, typename D>
inline alAccessor<E, A, D>&
alAccessor<E, A, D>::operator=(const alAccessor<E, A, D>& accessor)
{
    return operator=((accessor.is_driven()) ? accessor.get_driver()->create_clone() : NULL);
}
/*}}}*/

//alAccessor<E, A, D>::operator()() const/*{{{*/
template<typename E, typename A, typename D>
inline alAccessor<E, A, D>
alAccessor<E, A, D>::operator()() const
{
    return (is_driven()) ? get_driver()->create_clone() : NULL;
}
/*}}}*/

//alAccessor<E, A, D>::operator()(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
inline alAccessor<E, A, D>
alAccessor<E, A, D>::operator()(const D& datum) const
{
    return (is_driven()) ? get_driver()->create_clone(datum) : NULL;
}
/*}}}*/

//alAccessor<E, A, D>::is_driven() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAccessor<E, A, D>::is_driven() const
{
    return (get_driver() != NULL);
}
/*}}}*/

//alAccessor<E, A, D>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAccessor<E, A, D>::is_dynamic_access() const
{
    return is_driven() && get_driver()->is_dynamic_access();
}
/*}}}*/

//alAccessor<E, A, D>::get_driver() const/*{{{*/
template<typename E, typename A, typename D>
inline typename alAccessor<E, A, D>::Driver*
alAccessor<E, A, D>::get_driver() const
{
    return _driver;
}
/*}}}*/

//alAccessor<E, A, D>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
inline A
alAccessor<E, A, D>::get_associate(const E& element) const
{
    return (is_driven()) ? get_driver()->get_associate(element) : A();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alAccessor<E, A, D>::Driver implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alAccessor<E, A, D>::Driver::~Driver()/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::Driver::~Driver()
{
}
/*}}}*/

//alAccessor<E, A, D>::Driver::Driver()/*{{{*/
template<typename E, typename A, typename D>
inline
alAccessor<E, A, D>::Driver::Driver()
{
}
/*}}}*/

//alAccessor<E, A, D>::Driver::create_clone(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
inline typename alAccessor<E, A, D>::Driver*
alAccessor<E, A, D>::Driver::create_clone(const D& /*datum*/) const
{
    return create_clone();
}
/*}}}*/

//alAccessor<E, A, D>::Driver::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
inline bool
alAccessor<E, A, D>::Driver::is_dynamic_access() const
{
    return false;
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapAccessor<E, A, D> implementation                                                          //
//                                                                                                //

#ifndef DOXYGEN
//alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(E))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(E))
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(E) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(E) const)
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(const E&))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(const E&))
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(const E&) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (X::*member)(const E&) const)
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(E))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(E))
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(E) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(E) const)
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(const E&))/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(const E&))
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(const E&) const)/*{{{*/
template<typename E, typename A, typename D>
template<typename X>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (X::*member)(const E&) const)
  : Inherit(alSwapMemberAccessor<E, A, D>::create_driver(member))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(D, E))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(D, E))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(const D&, E))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(const D&, E))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(D, const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(D, const E&))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(const D&, const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(A (*function)(const D&, const E&))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(D, E))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(D, E))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(const D&, E))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(const D&, E))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(D, const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(D, const E&))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/

//alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(const D&, const E&))/*{{{*/
template<typename E, typename A, typename D>
inline
alSwapAccessor<E, A, D>::alSwapAccessor(const A& (*function)(const D&, const E&))
  : Inherit(alSwapFunctionAccessor<E, A, D>::create_driver(function))
{
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberAccessor<E, A, D> implementation                                                        //
//                                                                                                //

#ifndef DOXYGEN
//alMemberAccessor<E, A, D>::create_driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alMemberAccessor<E, A, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberAccessor<E, A, D>::Driver<M> implementation                                             //
//                                                                                                //

#ifndef DOXYGEN
//alMemberAccessor<E, A, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline
alMemberAccessor<E, A, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
{
}
/*}}}*/

//alMemberAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alMemberAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMemberAccessor<E, A, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alMemberAccessor<E, A, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member);
}
/*}}}*/

//alMemberAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline A
alMemberAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const
{
    return (get_reference(element).*_member)();
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberDatumAccessor<E, A, D> implementation                                                   //
//                                                                                                //

#ifndef DOXYGEN
//alMemberDatumAccessor<E, A, D>::create_driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alMemberDatumAccessor<E, A, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alMemberDatumAccessor<E, A, D>::Driver<M> implementation                                        //
//                                                                                                //

#ifndef DOXYGEN
//alMemberDatumAccessor<E, A, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline
alMemberDatumAccessor<E, A, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
  , _datum(D())
{
}
/*}}}*/

//alMemberDatumAccessor<E, A, D>::Driver<M>::Driver(M member, const D& datum)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline
alMemberDatumAccessor<E, A, D>::Driver<M>::Driver(M member, const D& datum)
  : Inherit()
  , _member(member)
  , _datum(datum)
{
}
/*}}}*/

//alMemberDatumAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alMemberDatumAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alMemberDatumAccessor<E, A, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alMemberDatumAccessor<E, A, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member, _datum);
}
/*}}}*/

//alMemberDatumAccessor<E, A, D>::Driver<M>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alMemberDatumAccessor<E, A, D>::Driver<M>::create_clone(const D& datum) const
{
    return new Driver<M>(_member, datum);
}
/*}}}*/

//alMemberDatumAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline A
alMemberDatumAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const
{
    return (get_reference(element).*_member)(_datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapMemberAccessor<E, A, D> implementation                                                    //
//                                                                                                //

#ifndef DOXYGEN
//alSwapMemberAccessor<E, A, D>::create_driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alSwapMemberAccessor<E, A, D>::create_driver(M member)
{
    return new Driver<M>(member);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapMemberAccessor<E, A, D>::Driver<M> implementation                                         //
//                                                                                                //

#ifndef DOXYGEN
//alSwapMemberAccessor<E, A, D>::Driver<M>::Driver(M member)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline
alSwapMemberAccessor<E, A, D>::Driver<M>::Driver(M member)
  : Inherit()
  , _member(member)
  , _datum(D())
{
}
/*}}}*/

//alSwapMemberAccessor<E, A, D>::Driver<M>::Driver(M member, const D& datum)/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline
alSwapMemberAccessor<E, A, D>::Driver<M>::Driver(M member, const D& datum)
  : Inherit()
  , _member(member)
  , _datum(datum)
{
}
/*}}}*/

//alSwapMemberAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alSwapMemberAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSwapMemberAccessor<E, A, D>::Driver<M>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alSwapMemberAccessor<E, A, D>::Driver<M>::create_clone() const
{
    return new Driver<M>(_member, _datum);
}
/*}}}*/

//alSwapMemberAccessor<E, A, D>::Driver<M>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline typename alAccessor<E, A, D>::Driver*
alSwapMemberAccessor<E, A, D>::Driver<M>::create_clone(const D& datum) const
{
    return new Driver<M>(_member, datum);
}
/*}}}*/

//alSwapMemberAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline A
alSwapMemberAccessor<E, A, D>::Driver<M>::get_associate(const E& element) const
{
    return (get_reference(_datum).*_member)(element);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionAccessor<E, A, D> implementation                                                      //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionAccessor<E, A, D>::create_driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alFunctionAccessor<E, A, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionAccessor<E, A, D>::Driver<F> implementation                                           //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionAccessor<E, A, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline
alFunctionAccessor<E, A, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
{
}
/*}}}*/

//alFunctionAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alFunctionAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alFunctionAccessor<E, A, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alFunctionAccessor<E, A, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function);
}
/*}}}*/

//alFunctionAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline A
alFunctionAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const
{
    return _function(element);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionDatumAccessor<E, A, D> implementation                                                 //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionDatumAccessor<E, A, D>::create_driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alFunctionDatumAccessor<E, A, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alFunctionDatumAccessor<E, A, D>::Driver<F> implementation                                      //
//                                                                                                //

#ifndef DOXYGEN
//alFunctionDatumAccessor<E, A, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline
alFunctionDatumAccessor<E, A, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//alFunctionDatumAccessor<E, A, D>::Driver<F>::Driver(F function, const D& datum)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline
alFunctionDatumAccessor<E, A, D>::Driver<F>::Driver(F function, const D& datum)
  : Inherit()
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//alFunctionDatumAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alFunctionDatumAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alFunctionDatumAccessor<E, A, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alFunctionDatumAccessor<E, A, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function, _datum);
}
/*}}}*/

//alFunctionDatumAccessor<E, A, D>::Driver<F>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alFunctionDatumAccessor<E, A, D>::Driver<F>::create_clone(const D& datum) const
{
    return new Driver<F>(_function, datum);
}
/*}}}*/

//alFunctionDatumAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline A
alFunctionDatumAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const
{
    return _function(element, _datum);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapFunctionAccessor<E, A, D> implementation                                                  //
//                                                                                                //

#ifndef DOXYGEN
//alSwapFunctionAccessor<E, A, D>::create_driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alSwapFunctionAccessor<E, A, D>::create_driver(F function)
{
    return new Driver<F>(function);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  alSwapFunctionAccessor<E, A, D>::Driver<F> implementation                                       //
//                                                                                                //

#ifndef DOXYGEN
//alSwapFunctionAccessor<E, A, D>::Driver<F>::Driver(F function)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline
alSwapFunctionAccessor<E, A, D>::Driver<F>::Driver(F function)
  : Inherit()
  , _function(function)
  , _datum(D())
{
}
/*}}}*/

//alSwapFunctionAccessor<E, A, D>::Driver<F>::Driver(F function, const D& datum)/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline
alSwapFunctionAccessor<E, A, D>::Driver<F>::Driver(F function, const D& datum)
  : Inherit()
  , _function(function)
  , _datum(datum)
{
}
/*}}}*/

//alSwapFunctionAccessor<E, A, D>::Driver<M>::is_dynamic_access() const/*{{{*/
template<typename E, typename A, typename D>
template<typename M>
inline bool
alSwapFunctionAccessor<E, A, D>::Driver<M>::is_dynamic_access() const
{
    return true;
}
/*}}}*/

//alSwapFunctionAccessor<E, A, D>::Driver<F>::create_clone() const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alSwapFunctionAccessor<E, A, D>::Driver<F>::create_clone() const
{
    return new Driver<F>(_function, _datum);
}
/*}}}*/

//alSwapFunctionAccessor<E, A, D>::Driver<F>::create_clone(const D& datum) const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline typename alAccessor<E, A, D>::Driver*
alSwapFunctionAccessor<E, A, D>::Driver<F>::create_clone(const D& datum) const
{
    return new Driver<F>(_function, datum);
}
/*}}}*/

//alSwapFunctionAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const/*{{{*/
template<typename E, typename A, typename D>
template<typename F>
inline A
alSwapFunctionAccessor<E, A, D>::Driver<F>::get_associate(const E& element) const
{
    return _function(_datum, element);
}
/*}}}*/
#endif // DOXYGEN



//                                                                                                //
//  Documentations                                                                                //
//                                                                                                //

//file/*{{{*/
/*!\file
    \brief    This file contains the definitions of the alAccessor, alAccessor::Driver and
        alSwapAccessor classes.
    */
/*}}}*/

//class alAccessor<E, A, D>/*{{{*/
/*!\class    alAccessor
    \brief    This concrete class implements the concept of \em "accessor".
    */
/*}}}*/

//class alAccessor<E, A, D>::Driver/*{{{*/
/*!\class    alAccessor::Driver
    \brief    This abstract class introduces the concept of \em "accessor driver".
    */
/*}}}*/

//class alSwapAccessor<E, A, D>/*{{{*/
/*!\class    alSwapAccessor
    \brief    This concrete class implements the concept of \em "swap accessor".
    */
/*}}}*/



//footer/*{{{*/
}

/*}}}*/

//                                                                                                //
//  End of file.                                                                                  //
//                                                                                                //
