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
 * @file object.hpp
 * @date 2021-8-8
 * @author ZhangKeyangZzz
 * @version 1.0 Debug
 */

#ifndef __GLX__CORE__OBJECT__HPP__
#define __GLX__CORE__OBJECT__HPP__
#include "mem_utilities.hpp"

namespace glx {
    struct Object {
        static void* operator new(size_t totalBytes) noexcept {
            return mem::Allocate<byte>(totalBytes);
        }
        static void* operator new[](size_t totalBytes) noexcept {
            return mem::Allocate<byte>(totalBytes);
        }
        static void operator delete(void* ptr) noexcept {
            mem::Deallocate(ptr);
        }
        static void operator delete[](void* ptr) noexcept {
            mem::Deallocate(ptr);
        }
        virtual ~Object() noexcept = default;
    };
}

#endif