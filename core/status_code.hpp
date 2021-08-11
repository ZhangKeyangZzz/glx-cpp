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
 * @file status_code.hpp
 * @date 2021-8-8
 * @author ZhangKeyangZzz
 * @version 1.0 release
 */

#ifndef __GLX__CORE__STATUSCODE__HPP__
#define __GLX__CORE__STATUSCODE__HPP__

namespace glx {

    /**
     * This enumerator is used to indicate a operation status.
     * @date 2021-8-8
     * @author ZhangKeyangZzz
     * @version 1.0 release
     * @note I don't like the `Exception` feature of CPP, because 
     *       it will lead to inconsistent states between different modules.
     */
    enum StatusCode {
        Success          = 0, /// The operation was executed successfully.
        IllegalArgument  = 1, /// At least one argument is invaild.
        IllegalState     = 2, /// Some data is in illegal state.
        IndexOutOfRange  = 3, /// Index out of range. 
    };
}

#endif