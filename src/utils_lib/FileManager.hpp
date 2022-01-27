#ifndef UTILSLIB_FILEMANAGER_HPP
#define UTILSLIB_FILEMANAGER_HPP

#include <Corrade/Utility/Directory.h>
#include <Eigen/Core>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace Corrade::Utility::Directory;

namespace utils_lib {
    class FileManager {
    public:
        // Contructor
        FileManager(const std::string& file);
        FileManager();

        // Destroyer
        ~FileManager();

        // Get file & path
        std::string fileName() const;
        std::string filePath() const;

        // Set file & path
        FileManager& setFile(const std::string& file);

        // Write file
        template <typename VarType>
        void write(VarType var)
        {
            if (!_open)
                _file.open(join(_path, _name), std::ios::out);

            _file << var << std::endl;

            _file.close();
            _open = false;
        }

        template <typename VarType, typename... Args>
        void write(VarType var, Args... args)
        {
            if (!_open) {
                _file.open(join(_path, _name), std::ios::out);
                _open = true;
            }

            _file << var << "\n"
                  << std::endl;

            write(args...);
        }

        // Apppend file
        template <typename VarType>
        void append(VarType var)
        {
            if (!_open)
                _file.open(join(_path, _name), std::ios::out | std::ios::app);

            _file << var << std::endl;

            _file.close();
            _open = false;
        }

        template <typename VarType, typename... Args>
        void append(VarType var, Args... args)
        {
            if (!_open) {
                _file.open(join(_path, _name), std::ios::out | std::ios::app);
                _file << std::endl;
                _open = true;
            }

            _file << var << "\n"
                  << std::endl;

            append(args...);
        }

        template <typename VarType>
        VarType read(const std::string& keyStart = "", size_t ignore = 0, const std::string& keyEnd = "")
        {
            if (!_open)
                _file.open(join(_path, _name), std::ios::in);

            std::string line;
            std::vector<double> values;
            uint rows = 0;
            bool read;

            if (!keyStart.empty())
                read = false;
            else
                read = true;

            while (std::getline(_file, line)) {
                if (!keyStart.compare(line))
                    read = true;
                else if (!keyEnd.compare(line) && !values.empty())
                    break;

                if (read && ignore == 0) {
                    std::stringstream lineStream(line);
                    std::string cell;
                    while (std::getline(lineStream, cell, ' ')) {
                        if (!cell.empty())
                            values.push_back(std::stod(cell));
                    }

                    ++rows;
                }
                else if (read)
                    ignore--;
            }

            _file.close();
            _open = false;

            return Eigen::Map<const Eigen::Matrix<typename VarType::Scalar, VarType::RowsAtCompileTime, VarType::ColsAtCompileTime, Eigen::RowMajor>>(values.data(), rows, values.size() / rows);
        }

        // Read file
        // template <typename VarType>
        // VarType read()
        // {
        //     if (!_open)
        //         _file.open(join(_path, _name), std::ios::in);

        //     std::string line;
        //     std::vector<double> values;
        //     uint rows = 0;

        //     while (std::getline(_file, line)) {
        //         std::stringstream lineStream(line);
        //         std::string cell;
        //         while (std::getline(lineStream, cell, ' ')) {
        //             if (!cell.empty())
        //                 values.push_back(std::stod(cell));
        //         }
        //         ++rows;
        //     }

        //     _file.close();
        //     _open = false;

        //     return Eigen::Map<const Eigen::Matrix<typename VarType::Scalar, VarType::RowsAtCompileTime, VarType::ColsAtCompileTime, Eigen::RowMajor>>(values.data(), rows, values.size() / rows);
        // }

        // template <typename VarType>
        // VarType read(const std::string& file)
        // {
        //     setFile(file);

        //     return this->read<VarType>();
        // }

    protected:
        bool _open;
        std::fstream _file;
        std::string _path, _name;
    };
} // namespace utils_lib

#endif // UTILSLIB_FILEMANAGER_HPP