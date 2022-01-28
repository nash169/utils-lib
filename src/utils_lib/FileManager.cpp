/*
    This file is part of utils-lib.

    Copyright (c) 2020, 2021, 2022 Bernardo Fichera <bernardo.fichera@gmail.com>

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

#include "utils_lib/FileManager.hpp"

namespace utils_lib {
    FileManager::FileManager(const std::string& file)
    {
        setFile(file);
    }

    FileManager::FileManager() {}

    FileManager::~FileManager() {}

    std::string FileManager::fileName() const
    {
        return _name;
    }

    std::string FileManager::filePath() const
    {
        return _path;
    }

    FileManager& FileManager::setFile(const std::string& file)
    {
        _path = path(file);

        if (!_path.empty()) {
            if (!isDirectory(_path))
                mkpath(_path);
        }

        _name = filename(file);

        _open = false;

        return *this;
    }
} // namespace utils_lib