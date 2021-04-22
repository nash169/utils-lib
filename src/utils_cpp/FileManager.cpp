#include "utils_cpp/FileManager.hpp"

namespace utils_cpp {
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
} // namespace utils_cpp