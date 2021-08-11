/*
 * Copyright 1992-2021 The FreeBSD Project.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file skeleton.hpp
 * @date 2021-8-8
 * @author ZhangKeyangZzz
 * @version 1.0 Debug
 */

#ifndef __GLX__TEST__SKELETON__HPP__
#define __GLX__TEST__SKELETON__HPP__
#include <cstdlib>

namespace glx {
    enum TestStatusCode {
        Pass,
        IsNullptr,
        IsNotNullptr,  
        IsNotTrue,
        IsNotFalse,
        IsEquals,
        IsNotEquals,  
    };

    struct Assertion {
        static inline void AssertTrue(bool cond) noexcept {
            if (cond != true) {
                std::exit(TestStatusCode::IsNotTrue);
            }
        }
        static inline void AssertFalse(bool cond) noexcept {
            if (cond != false) {
                std::exit(TestStatusCode::IsNotFalse);
            }
        }
        static inline void AssertIsNullptr(void* ptr) noexcept {
            if (ptr != nullptr) {
                std::exit(TestStatusCode::IsNotNullptr);
            }
        }
        static inline void AssertIsNotNullptr(void* ptr) noexcept {
            if (ptr == nullptr) {
                std::exit(TestStatusCode::IsNotNullptr);
            }
        }
        template <typename T1, typename T2> 
        static inline void AssertIsEquals(T1 const& lhs, T2 const& rhs) {
            if (lhs != rhs) {
                std::exit(TestStatusCode::IsNotEquals);
            }
        }
        template <typename T1, typename T2> 
        static inline void AssertIsNotEquals(T1 const& lhs, T2 const& rhs) {
            if (lhs == rhs) {
                std::exit(TestStatusCode::IsEquals);
            }
        }
    };
}

#endif