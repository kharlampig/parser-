#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class parser {
private:
    std::string str;
    std::vector<std::string> lines;

    // Метод для парсинга строк
    void parseLines() {
        std::string line;
        auto ss = std::stringstream{ str };

        while (std::getline(ss, line, '|')) {
            // Удаляем символы таблицы
            filterTableChars(line);
            // Если строка не пустая после фильтрации, добавляем её
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
    }

    void fixNumsToNames() {
        std::vector <int> removeLines;
        for (int i = 0; i < lines.size() - 1; i++) {
            if (!isdigit(lines[i].back()) && isdigit(lines[i + 1].front())) {
                removeLines.push_back(i + 1);
                lines[i] += lines[i + 1];
            }
        }

        for (int i = removeLines.size() - 1; i >= 0; i--) {
            lines.erase(lines.begin() + removeLines[i]);
        }

    }

    // Метод для удаления символов, которые формируют табличку
    void filterTableChars(std::string& line) {
        line.erase(
            std::remove_if(line.begin(), line.end(),
                [](char c) {
                    return c == '+' || c == '-' || c == '|' || c == ' ' || c == '\t' || c == '\r' || c == '\n'; // Удаляем символы
                }),
            line.end());
    }

public:
    parser(const std::string& str) {
        this->str = str;
        parseLines();
        fixNumsToNames();
    }

    const std::vector<std::string>& getLines() const {
        return lines;
    }

    std::string findParameter(const std::string& prompt) {
        bool exists = 0;
        for (int i = 0; i < lines.size(); i++) {
            size_t caught = lines[i].find(prompt);
            if (caught != std::string::npos) {
                if (prompt.size() == lines[i].size())
                    return "none";
                else
                    return lines[i].substr(prompt.size(), lines[i].size());
                exists = 1;
            }
        }
        if (!exists) return "none";
    }
};