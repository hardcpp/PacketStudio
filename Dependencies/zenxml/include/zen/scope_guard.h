// **************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under *
// * GNU General Public License: http://www.gnu.org/licenses/gpl-3.0        *
// * Copyright (C) Zenju (zenju AT gmx DOT de) - All Rights Reserved        *
// **************************************************************************

#ifndef ZEN_SCOPEGUARD_8971632487321434
#define ZEN_SCOPEGUARD_8971632487321434

#include <cassert>
//#include <type_traits> //std::decay
//#include <utility>

//best of Zen, Loki and C++11

namespace zen
{
//Scope Guard
/*
    zen::ScopeGuard lockAio = zen::makeGuard([&] { ::CloseHandle(hDir); });
		...
	lockAio.dismiss();
*/

//Scope Exit
/*
	ZEN_ON_SCOPE_EXIT(::CloseHandle(hDir));
*/

class ScopeGuardBase
{
public:
    void dismiss() { dismissed_ = true; }

protected:
    ScopeGuardBase() : dismissed_(false) {}
    ScopeGuardBase(ScopeGuardBase&& other) : dismissed_(other.dismissed_) { other.dismiss(); } //take over responsibility
    ~ScopeGuardBase() {} //[!] protected non-virtual base class destructor

    bool isDismissed() const { return dismissed_; }

private:
    ScopeGuardBase           (const ScopeGuardBase&) = delete;
    ScopeGuardBase& operator=(const ScopeGuardBase&) = delete;

    bool dismissed_;
};


template <typename F>
class ScopeGuardImpl : public ScopeGuardBase
{
public:
    explicit ScopeGuardImpl(const F& fun) : fun_(fun) {}
    explicit ScopeGuardImpl(     F&& fun) : fun_(std::move(fun)) {}
    ScopeGuardImpl(ScopeGuardImpl&& other) : ScopeGuardBase(std::move(other)), fun_(std::move(other.fun_)) {}

    ~ScopeGuardImpl()
    {
        if (!this->isDismissed())
            try
            {
                fun_();
            }
            catch (...) { assert(false); }
    }

private:
    F fun_;
};

typedef ScopeGuardBase&& ScopeGuard;

template <class F> inline
ScopeGuardImpl<typename std::decay<F>::type> makeGuard(F&& fun) { return ScopeGuardImpl<typename std::decay<F>::type>(std::forward<F>(fun)); }
}

#define ZEN_CONCAT_SUB(X, Y) X ## Y
#define ZEN_CONCAT(X, Y) ZEN_CONCAT_SUB(X, Y)

#define ZEN_ON_SCOPE_EXIT(X) auto ZEN_CONCAT(dummy, __LINE__) = zen::makeGuard([&]{ X; }); (void)ZEN_CONCAT(dummy, __LINE__);

#endif //ZEN_SCOPEGUARD_8971632487321434
