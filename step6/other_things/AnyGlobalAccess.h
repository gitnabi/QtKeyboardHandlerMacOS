#ifndef ANYGLOBALACCESS_H
#define ANYGLOBALACCESS_H

#include <cassert>
#include <memory>

namespace NSLibrary {

//---------------------------------------------------------------------------
// Description of usage
//---------------------------------------------------------------------------
//
// The pattern is used to make a global object with non-trivial constructor
// without explicitely defining the object globaly.
//
// WARNING this thing is NOT thread safe!
//
// In order to use the pattern we must provide:
// 1) TAccessible -- the class for the global object
//
// 2) TID -- identification class. If we want to have several global objects
// of a class Type, we must distinguish them by a dummy class TID. For example,
// CAnyGlobalAccessible<Type, A> and CAnyGlobalAccessible<Type, B> store
// different instances of objects of type Type in static storage.
// Since static objects defined by the class they belong to, classes A and B
// are required to distinguish the instances.
// Example of a dummy class declaration:
// class CGlobalAccessibleID;
//
// 3) A class for initialization of the global object. It must be
// inherited from CAnyGlobalInitializer.
// The class must inherit all the constructors of the base class.
// class CMyInitializer : CAnyGlobalInitializer<TAccessible, TID> {
//   using CBase = CAnyGlobalInitializer<TAccessible, TID>;
// public:
//   using CBase::CBase;
// };
//
// 4) A class for getting access to the global object must be publicly inherited
// from CAnyGlobalAccess. It has only a default constructor. It asserts if
// the global object has not yet been initialized.
// class CMyAccessor : public CAnyGlobalAccess<TAccessible, TID> {};
//
// Example:
// Suppose we want a global int variable for logging:
//
// class CLoggerCounterID;
// class CLoggerCounterInitializer :
//   CAnyGlobalInitializer<int, CLoggerCounterID> {
//   using CBase = CAnyGlobalInitializer<int, CLoggerCounterID>;
// public:
//   using CBase::CBase;
// };
// class CLoggerCounterAccess : public CAnyGlobalAccess<int, CLoggerCounterID>
// {};
//
// Then in code we write something like that:
// ...
// CLoggerCounterInitializer Init(0);
// ...
// CLoggerCounterAccess LogCounter;
// ++(*LogCounter);
// std::cout << *LogCounter << std::endl;
// ...
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
class CAnyGlobalAccessible {
  using CAccessibleType = std::unique_ptr<TAccessible>;

protected:
  inline ~CAnyGlobalAccessible() = default;

  static CAccessibleType& get() {
    static CAccessibleType gObject = nullptr;
    return gObject;
  }
};

template<class TAccessible, class TID>
class CAnyGlobalAccess : public CAnyGlobalAccessible<TAccessible, TID> {
  using CBase = CAnyGlobalAccessible<TAccessible, TID>;

public:
  CAnyGlobalAccess() {
    assert(CBase::get());
  }

  const TAccessible* operator->() const {
    assert(CBase::get());
    return CBase::get().get();
  }

  TAccessible* operator->() {
    assert(CBase::get());
    return CBase::get().get();
  }

  const TAccessible& operator*() const {
    assert(CBase::get());
    assert(CBase::get().get());
    return *(CBase::get().get());
  }

  TAccessible& operator*() {
    assert(CBase::get());
    assert(CBase::get().get());
    return *(CBase::get().get());
  }
};

template<class TAccessible, class TID>
class CAnyGlobalInitializer : public CAnyGlobalAccessible<TAccessible, TID> {
  using CBase = CAnyGlobalAccessible<TAccessible, TID>;

public:
  template<class... TArgs>
  CAnyGlobalInitializer(TArgs&&... args) {
    assert(!CBase::get());
    if (!CBase::get())
      CBase::get() =
          std::make_unique<TAccessible>(std::forward<TArgs>(args)...);
  }
};

} // namespace NSLibrary

#endif // ANYGLOBALACCESS_H
