/*
    This file is part of utils-lib.

    Copyright (c) 2020, 2021, 2022, 2023 Bernardo Fichera <bernardo.fichera@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef UTILSLIB_TIMER_HPP
#define UTILSLIB_TIMER_HPP

#include <chrono>
#include <iostream>

namespace utils_lib {
    class Timer {
    public:
        Timer()
        {
            _start_time = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            stop();
        }

        void stop()
        {
            auto end_time = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_start_time).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

            auto duration = end - start;
            double ms = duration * 0.001;
            double s = ms * 0.001;

            std::cout << duration << "us (" << ms << "ms)"
                      << " - (" << s << "s)" << std::endl;
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _start_time;
    };
} // namespace utils_lib

#endif // UTILSLIB_TIMER_HPP