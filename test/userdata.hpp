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

#ifndef __GLX__TEST__USERDATA__HPP__
#define __GLX__TEST__USERDATA__HPP__
#include "../core/basic_types.hpp"
#include <cstdlib>
#include <cstring>
#include <utility>

namespace glx {
    struct UserObject {
        void* ptr;
        
        UserObject() noexcept : ptr(nullptr) {
            this->ptr = new int[128];
            memset(this->ptr, 0, 128);
        }

        UserObject(UserObject const& rhs) noexcept : ptr(nullptr) {
            this->ptr = new int[128];
            memcpy(this->ptr, rhs.ptr, 128);
        }

        UserObject(UserObject&& rhs) noexcept : ptr(nullptr) {
            this->ptr = rhs.ptr;
            rhs.ptr = nullptr;
        }

        UserObject& operator=(UserObject const& rhs) noexcept {
            if (this != &rhs) {
                memcpy(this->ptr, rhs.ptr, 128);
            }
            return *this;
        }

        UserObject& operator=(UserObject&& rhs) noexcept {
            if (this != &rhs) {
                this->ptr = rhs.ptr;
                rhs.ptr = nullptr;
            }
            return *this;
        }

        ~UserObject() noexcept {
            delete[] this->ptr;
        }
    };

    struct UserData final : public UserObject {
        char bytes[128];
        uint32 i32;
        float f32;
        double f64;

        UserData() noexcept : UserObject(), i32(0), f32(0), f64(0) {
            auto len = sizeof(this->bytes, this->bytes[0]);
            memset(this->bytes, 0, len);
        }

        UserData(uint32 i32, float f32, double f64, const char *bytes) noexcept : UserObject(), i32(i32), f32(f32), f64(f64) {
            auto len = strlen(bytes);
            strncpy(this->bytes, bytes, len + 1);
        }

        UserData(UserData const& rhs) noexcept : UserObject(rhs), i32(rhs.i32), f32(rhs.f32), f64(rhs.f64) {
            auto len = sizeof(this->bytes, this->bytes[0]);
            memcpy(this->bytes, rhs.bytes, len);
        }

        UserData(UserData&& rhs) noexcept : UserObject(std::move(rhs)),i32(rhs.i32), f32(rhs.f32), f64(rhs.f64) {
            auto len = sizeof(this->bytes, this->bytes[0]);
            memcpy(this->bytes, rhs.bytes, len);
        }

        UserData& operator=(UserData const& rhs) noexcept {
            if (this != &rhs) {
                UserObject::operator=(rhs);
                this->i32 = rhs.i32;
                this->f32 = rhs.f32;
                this->f64 = rhs.f64;
                auto len = sizeof(this->bytes, this->bytes[0]);
                memcpy(this->bytes, rhs.bytes, len);
            }
            return *this;
        }

        UserData& operator=(UserData&& rhs) noexcept {
            if (this != &rhs) {
                UserObject::operator=(std::move(rhs));
                this->i32 = rhs.i32;
                this->f32 = rhs.f32;
                this->f64 = rhs.f64;
                auto len = sizeof(this->bytes, this->bytes[0]);
                memcpy(this->bytes, rhs.bytes, len);
            }
            return *this;
        }

        ~UserData() noexcept {
            this->i32 = 0;
            this->f32 = 0;
            this->f64 = 0;
            auto len = sizeof(this->bytes, this->bytes[0]);
            memset(this->bytes, 0, len);
        }
    };
}

#endif