#include "File.h"
#include "Core/Logger.h"

#include <iostream>
#include <fstream>

namespace Rex::file {
    
    std::string GetCurrentDirectory() {

        std::error_code ec;
        auto path = std::filesystem::current_path(ec);
        return ec ? std::string{} : path.string();
    }

    bool SetCurrentDirectory(const std::string& path) {

        std::error_code ec;
        std::filesystem::current_path(path, ec);

        return !ec;
    }

    
    std::string GetExtension(const std::string& path) {

        std::filesystem::path p(path);
        return p.extension().string();
    }

    std::string GetFilename(const std::string& path) {

        std::filesystem::path p(path);
        return p.filename().string();
    }

    bool Exists(const std::string& path) {

        std::error_code ec;
        bool result = std::filesystem::exists(path, ec);

        return !ec && result;
    }

    std::vector<std::string> GetFilesInDirectory(const std::string& path) {

        std::vector<std::string> files;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return files; // return empty vector on error

        for (const auto& entry : iter) {

            if (entry.is_regular_file(ec) && !ec) {

                files.push_back(entry.path().string());
            }
        }

        return files;
    }

    std::vector<std::string> GetDirectoriesIn(const std::string& path) {

        std::vector<std::string> directories;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return directories; // return empty vector on error

        for (const auto& entry : iter) {

            if (entry.is_directory(ec) && !ec) {

                directories.push_back(entry.path().string());
            }
        }

        return directories;
    }

    bool ReadTextFile(const std::string& path, std::string& content) {

        std::ifstream file(path);
        if (!file.is_open()) {

            return false;
        }

        // read entire file into string
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();

        return true;
    }

    bool WriteTextFile(const std::string& path, const std::string& content, bool append) {

        std::ios::openmode mode = append ? std::ios::app : std::ios::out;
        std::ofstream file(path, mode);
        if (!file.is_open()) {

            return false;
        }

        file << content;

        return true;
    }

    /// <summary>
    /// Reads the contents of a binary file into a vector of bytes.
    /// </summary>
    /// <param name="path">The path to the binary file to read.</param>
    /// <param name="data">A reference to a vector that will be filled with the file's contents.</param>
    /// <returns>True if the file was successfully read; false otherwise.</returns>
    bool ReadBinaryFile(const std::string& path, std::vector<uint8_t>& data) {

        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {

            Rex::Logger::Error("Read binary file error: " , path);
            return false;
        }

        // Get file size
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (!file.good()) {

            Rex::Logger::Error("Read binary file error: " , path);
            return false;
        }

        // Resize vector and read file
        data.resize(size);
        file.read(reinterpret_cast<char*>(data.data()), size);

        return true;
    }

    bool WriteBinaryFile(const std::string& path, const std::vector<uint8_t>& data) {

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {

            return false;
        }

        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }
}



