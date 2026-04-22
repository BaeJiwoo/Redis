#pragma once
#pragma once
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

class EnvReader {
public:
    EnvReader(const std::string& filename) {
        load(filename);
    }

    // 설정값 가져오기 (문자열)
    std::string get(const std::string& key, const std::string& defaultValue = "") {
        if (mEnvData.find(key) != mEnvData.end()) {
            return mEnvData[key];
        }
        return defaultValue;
    }

    // 설정값 가져오기 (정수형)
    int getInt(const std::string& key, int defaultValue = 0) {
        if (mEnvData.find(key) != mEnvData.end()) {
            return std::stoi(mEnvData[key]);
        }
        return defaultValue;
    }

    bool isLoaded() const { return mIsLoaded; }

private:
    std::map<std::string, std::string> mEnvData;
    bool mIsLoaded = false;

    void load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;

            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = trim(line.substr(0, delimiterPos));
                std::string value = trim(line.substr(delimiterPos + 1));
                mEnvData[key] = value;
            }
        }
        mIsLoaded = true;
    }

    std::string trim(const std::string& s) {
        if (s.empty()) return s;
        size_t first = s.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = s.find_last_not_of(" \t\n\r");
        return s.substr(first, (last - first + 1));
    }
};