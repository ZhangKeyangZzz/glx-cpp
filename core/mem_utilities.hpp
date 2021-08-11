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
 * @file mem_utilities.hpp
 * @date 2021-8-8
 * @author ZhangKeyangZzz
 * @version 1.0 Debug
 */

#ifndef __GLX__CORE__MEM__UTILITIES__HPP__
#define __GLX__CORE__MEM__UTILITIES__HPP__
#include <new>
#include <cstdlib>
#include <cstring>
#include "basic_types.hpp"

namespace glx {
    namespace mem {
        /**
         * Allocate a contiguous block of heap memory to hold at least ```count``` elements.
         * @author ZhangKeyangZzz
         * @param[in] count The specified elements count.
         * @return Returns the address of the block.
         * @note If some errors is ocurred, throws the std::bad_alloc exception.
         */
        template <typename T>
        T* Allocate(uint32 count) noexcept {
            auto totalBytes = uint32(count * sizeof(T));
            auto ptr        = new byte[totalBytes];
            return reinterpret_cast<T*>(ptr);
        }

        /**
         * Deallocate a contiguous block of heap memory.
         * @author ZhangKeyangZzz
         * @param[in] ptr The the address of the block.
         */
        template <typename T>
        void Deallocate(T* ptr) noexcept {
            auto rawPtr = reinterpret_cast<byte*>(ptr);
            delete[] rawPtr;
        }
    }
}

#endif

