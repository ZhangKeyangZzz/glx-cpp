/*
 * MIT License
 * Copyright (c) 2021 ZhangKeyangZzz
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
            return mem::allocate<byte>(totalBytes);
        }
        static void* operator new[](size_t totalBytes) noexcept {
            return mem::allocate<byte>(totalBytes);
        }
        static void operator delete(void* ptr) noexcept {
            mem::deallocate(ptr);
        }
        static void operator delete[](void* ptr) noexcept {
            mem::deallocate(ptr);
        }
        virtual ~Object() noexcept = default;
    };
}

#endif