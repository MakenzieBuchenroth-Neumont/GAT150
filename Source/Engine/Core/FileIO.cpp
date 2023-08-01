#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;

namespace neko {
    std::string getFilePath()
    {
        return std::filesystem::current_path().string();
    }

    bool setFilePath(const std::filesystem::path& path) {
        std::error_code ec;
        std::filesystem::current_path(path, ec);

        return ec.value() == 0;
    }

    std::string getFileName(const std::filesystem::path& path) {
        return path.filename().string();
    }

    bool fileExists(const std::filesystem::path& path) {
        return std::filesystem::exists(path);
    }

    bool getFileSize(const std::filesystem::path& path, size_t& size) {
        std::error_code ec;
        size = std::filesystem::file_size(path, ec);

        return ec.value() == 0;

    }
    bool readFile(const std::filesystem::path& path, std::string& buffer) {
        if (!fileExists(path))
        {
            WARNING_LOG;
            return false;
        }

        size_t size;
        if (!getFileSize(path, size)) return false;

        buffer.resize(size);
        std::ifstream stream(path);
        stream.read(buffer.data(), size);
        stream.close();

        return true;
    }

    bool writeFile(const std::filesystem::path& path, const std::string& data) {
        try {
            // Step 1: Open the file in write mode
            std::ofstream outFile(path);

            if (!outFile) {
                std::cerr << "Error opening the file for writing." << std::endl;
                return false;
            }

            // Step 2: Write data to the file
            outFile << data;

            // Step 3: Close the file
            outFile.close();

            return true; // Success
        }
        catch (const std::exception& ex) {
            std::cerr << "Error while writing to the file: " << ex.what() << std::endl;
            return false;
        }
    }

    bool readScore(const std::filesystem::path& path, std::string& buffer) {
        try {
            // Step 1: Open the file in read mode
            std::ifstream inFile(path);

            if (!inFile) {
                std::cerr << "Error opening the file for reading." << std::endl;
                return false;
            }

            // Step 2: Read data from the file
            buffer.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());

            // Step 3: Close the file (optional for ifstream as it will automatically close when it goes out of scope)
            inFile.close();

            return true; // Success
        }
        catch (const std::exception& ex) {
            std::cerr << "Error while reading from the file: " << ex.what() << std::endl;
            return false;
        }
    }
}