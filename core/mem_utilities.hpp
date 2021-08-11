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
 * This file provides almost of raw memory utility functions in sub-namespace `mem`.
 * 
 * @file mem_utilities.hpp
 * @date 2021-8-8
 * @author ZhangKeyangZzz
 * @version 1.0 Release
 */

#ifndef __GLX__CORE__MEM__UTILITIES__HPP__
#define __GLX__CORE__MEM__UTILITIES__HPP__
#include "basic_types.hpp"
#include "status_code.hpp"
#include <new>
#include <utility>
#include <cstdlib>
#include <cstring>

namespace glx {
    namespace mem {
        /**
         * Allocate a contiguous block of heap memory to hold at least ```count``` elements.
         * @author ZhangKeyangZzz
         * @param[in] count The specified elements count.
         * @tparam T The type of elements in both array.
         * @return Returns the address of the block.
         * @note If some errors is ocurred, throws the std::bad_alloc exception.
         */
        template <typename T>
        inline T* allocate(uint32 count) noexcept {
            auto totalBytes = uint32(count * sizeof(T));
            auto ptr        = new byte[totalBytes];
            return reinterpret_cast<T*>(ptr);
        }

        /**
         * Deallocate a contiguous block of heap memory.
         * @author ZhangKeyangZzz
         * @param[in] ptr The the address of the block.
         * @tparam T The type of elements in both array.
         */
        inline void deallocate(void* ptr) noexcept {
            auto rawPtr = reinterpret_cast<byte*>(ptr);
            delete[] rawPtr;
        }

        /**
         * Constructs an object at the specified position using the specified parameters.
         * @author ZhangKeyangZzz
         * @param[in] object The specified memory position.
         * @param[in] args The arguments of that constructor.
         * @tparam T The type of elements in both array.
         */
        template <typename T, typename... Args>
        void construct(T* object, Args&&... args) noexcept {
            new (object) T(std::forward<Args>(args)...);
        }

        /**
         * Destructs an object at the specified position.
         * @author ZhangKeyangZzz
         * @param[in] object The specified memory position.
         * @tparam T The type of elements in both array.
         */
        template <typename T>
        void destruct(T* object) noexcept {
            object->~T();
        }

        /**
         * Fill the initialized buffer `arr[index .. index + length) with the specified value.`
         * @author ZhangKeyangZzz
         * @param[in] arr The specified buffer.
         * @param[in] index The specified index.
         * @param[in] length The length of the buffer.
         * @param[in] value The target value.
         * @tparam T The type of elements in the array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int fill_of_range(T *const arr, uint32 index, uint32 length, T &const value) noexcept {
            while (length > 0) {
                arr[index + length - 1] = value;
                length--;
            }
        }

        ///-------------------------------------------------------------------------------------
        ///
        /// copy_of_range functions implementations.
        ///
        ///-------------------------------------------------------------------------------------
        namespace __ignore {
            /// This function is a part of implementation of memory utility function `copy_of_range`.
            /// For trivially data, the only thing we need to do is copying the memory bytes to bytes, 
            template <typename T>
            void __copy_of_range_unchecked(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length, std::true_type) noexcept {
                auto totalBytes = length * sizeof(T);
                memmove(dst, src, totalBytes);
            }

            /// This function is a part of implementation of memory utility function `copy_of_range`.
            /// For non-trivially data, we need to call its `operator=` function to override these objects.
            /// NOTE: If dst[dstIndex] is not initialized, the behaviour of this function is UNDEFINED.
            template <typename T>
            void __copy_of_range_unchecked(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length, std::false_type) noexcept {
                T* dstPtr = const_cast<T*>(dst + dstIndex);
                T* srcPtr = const_cast<T*>(src + srcIndex);
                if (dstPtr > srcPtr && dstPtr < srcPtr + length) {
                    while (length > 0) {
                        dstPtr[length - 1] = srcPtr[length - 1];
                        length--;
                    }
                } else {
                    while (length > 0) {
                        *dstPtr = *srcPtr;
                        dstPtr++;
                        srcPtr++;
                        length--;
                    }
                }
            }
        }

        /**
         * Copy specified count of objects from `src[srcIndex]` to `dst[dstIndex]`.
         * @author ZhangKeyangZzz
         * @param[in] dst The destination array.
         * @param[in] src The source array.
         * @param[in] srcIndex The offset of source position.
         * @param[in] dstIndex The offset of destination position.
         * @param[in] length The length of copy section.
         * @tparam T The type of elements in both array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int copy_of_range(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length) noexcept {
            if (dst == nullptr || src == nullptr || length == 0) {
                return StatusCode::IllegalArgument;
            }
            using IsTrivial = typename std::is_trivial<T>::type;
            __ignore::__copy_of_range_unchecked(dst, src, dstIndex, srcIndex, length, IsTrivial());
            return StatusCode::Success;
        }

        /**
         * Copy specified count of objects from `arr[srcIndex]` to `arr[dstIndex]`.
         * @author ZhangKeyangZzz
         * @param[in] arr A pointer to the array.
         * @param[in] srcIndex The offset of source position.
         * @param[in] dstIndex The offset of destination position.
         * @param[in] length The length of copy section.
         * @tparam T The type of elements in both array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int copy_of_range(T *const arr, uint32 dstIndex, uint32 srcIndex, uint32 length) noexcept {
            if (arr == nullptr || length == 0) {
                return StatusCode::IllegalArgument;
            }
            using IsTrivial = typename std::is_trivial<T>::type;
            __ignore::__copy_of_range_unchecked(arr, arr, dstIndex, srcIndex, length, IsTrivial());
            return StatusCode::Success;
        }

        ///-------------------------------------------------------------------------------------
        ///
        /// uninitialized_copy_of_range functions implementations.
        ///
        ///-------------------------------------------------------------------------------------
        namespace __ignore {
            /// This function is a part of implementation of memory utility function `uninitialized_copy_of_range`.
            /// For trivially data, the only thing we need to do is copying the memory bytes to bytes, 
            template <typename T>
            void __uninitialized_copy_of_range_unchecked(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length, std::true_type) noexcept {
                auto totalBytes = length * sizeof(T);
                memmove(dst, src, totalBytes);
            }

            /// This function is a part of implementation of memory utility function `uninitialized_copy_of_range`.
            /// For non-trivially data, we need to call utility function `construct` to construct these objects.
            /// NOTE: If dst[dstIndex] is already initialized, the behaviour of this function is UNDEFINED.
            template <typename T>
            void __uninitialized_copy_of_range_unchecked(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length, std::false_type) noexcept {
                T* dstPtr = const_cast<T*>(dst + dstIndex);
                T* srcPtr = const_cast<T*>(src + srcIndex);
                if (dstPtr > srcPtr && dstPtr < srcPtr + length) {
                    while (length > 0) {
                        construct(dstPtr + length - 1, srcPtr[length - 1]);
                        length--;
                    }
                } else {
                    while (length > 0) {
                        construct(dstPtr, *srcPtr);
                        dstPtr++;
                        srcPtr++;
                        length--;
                    }
                }
            }
        }

        /**
         * Copy specified count of objects from `src[srcIndex]` to `dst[dstIndex]`.
         * @author ZhangKeyangZzz
         * @param[in] dst The destination array.
         * @param[in] src The source array.
         * @param[in] srcIndex The offset of source position.
         * @param[in] dstIndex The offset of destination position.
         * @param[in] length The length of copy section.
         * @tparam T The type of elements in both array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int uninitialized_copy_of_range(T *const dst, const T* src, uint32 dstIndex, uint32 srcIndex, uint32 length) noexcept {
            if (dst == nullptr || src == nullptr || length == 0) {
                return StatusCode::IllegalArgument;
            }
            using IsTrivial = typename std::is_trivial<T>::type;
            __ignore::__uninitialized_copy_of_range_unchecked(dst, src, dstIndex, srcIndex, length, IsTrivial());
            return StatusCode::Success;
        }

        /**
         * Copy specified count of objects from `arr[srcIndex]` to `arr[dstIndex]`.
         * @author ZhangKeyangZzz
         * @param[in] arr A pointer to the array.
         * @param[in] srcIndex The offset of source position.
         * @param[in] dstIndex The offset of destination position.
         * @param[in] length The length of copy section.
         * @tparam T The type of elements in both array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int uninitialized_copy_of_range(T *const arr, uint32 dstIndex, uint32 srcIndex, uint32 length) noexcept {
            if (arr == nullptr || length == 0) {
                return StatusCode::IllegalArgument;
            }
            using IsTrivial = typename std::is_trivial<T>::type;
            __ignore::__uninitialized_copy_of_range_unchecked(arr, arr, dstIndex, srcIndex, length, IsTrivial());
            return StatusCode::Success;
        }

        ///-------------------------------------------------------------------------------------
        ///
        /// uninitialized_fill_of_range functions implementations.
        ///
        ///-------------------------------------------------------------------------------------
        namespace __ignore {
            /// This function is a part of implementation of memory utility function `uninitialized_fill_of_range`.
            /// For trivially data, the only thing we need to do is copying the memory bytes to bytes, 
            template <typename T>
            void __uninitialized_fill_of_range_unchecked(T *const arr, uint32 index, uint32 length, T &const value, std::true_type) noexcept {
                auto elementSize = sizeof(T);
                while (length > 0) {
                    memmove(arr + index + length - 1, &value, elementSize);
                    length--;
                }
            }

            /// This function is a part of implementation of memory utility function `uninitialized_fill_of_range`.
            /// For non-trivially data, we need to call utility function `construct` to construct these objects.
            /// NOTE: If dst[dstIndex] is already initialized, the behaviour of this function is UNDEFINED.
            template <typename T>
            void __uninitialized_fill_of_range_unchecked(T *const arr, uint32 index, uint32 length, T &const value, std::false_type) noexcept {
                while (length > 0) {
                    construct(arr + index + length - 1, value);
                    length--;
                }
            }
        }

        /**
         * Fill the uninitialized buffer `arr[index .. index + length) with the specified value.`
         * @author ZhangKeyangZzz
         * @param[in] arr The specified buffer.
         * @param[in] index The specified index.
         * @param[in] length The length of the buffer.
         * @param[in] value The target value.
         * @tparam T The type of elements in the array.
         * @return Return the status code representing whether the operation was successful.
         */
        template <typename T>
        int uninitialized_fill_of_range(T *const arr, uint32 index, uint32 length, T &const value) noexcept {
            if (arr == nullptr) {
                return StatusCode::IllegalArgument;
            }
            using IsTrivial = typename std::is_trivial<T>::type;
            __ignore::__uninitialized_fill_of_range_unchecked(arr, index, length, value, IsTrivial());
            return StatusCode::Success;
        }
    }
}

#endif

