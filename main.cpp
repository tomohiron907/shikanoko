#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

class BrainfuckInterpreter {
public:
    BrainfuckInterpreter(const std::wstring& code) : code(code), data(30000, 0), dataPointer(0), codePointer(0) {
        // Preprocess loops
        std::stack<int> loopStack;
        for (int i = 0; i < code.size(); i += 2) {
            std::wstring command = code.substr(i, 2);
            if (command == L"つの") {
                loopStack.push(i);
            } else if (command == L"のつ") {
                int start = loopStack.top();
                loopStack.pop();
                loopMap[start] = i;
                loopMap[i] = start;
            }
        }
    }

    void execute() {
        while (codePointer < code.size()) {
            std::wstring command = code.substr(codePointer, 2);
            if (command == L"こし") {
                ++dataPointer;
            } else if (command == L"たん") {
                --dataPointer;
            } else if (command == L"しか") {
                ++data[dataPointer];
            } else if (command == L"ぬん") {
                --data[dataPointer];
            } else if (command == L"のこ") {
                std::wcout << static_cast<wchar_t>(data[dataPointer]);
            } else if (command == L"なら") {
                data[dataPointer] = std::wcin.get();
            } else if (command == L"つの") {
                if (data[dataPointer] == 0) {
                    codePointer = loopMap[codePointer];
                }
            } else if (command == L"のつ") {
                if (data[dataPointer] != 0) {
                    codePointer = loopMap[codePointer];
                }
            }
            codePointer += 2;
        }
    }

private:
    std::wstring code;
    std::vector<int> data;
    int dataPointer;
    int codePointer;
    std::unordered_map<int, int> loopMap;
};

std::wstring readFile(const std::string& filename) {
    std::wifstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
    if (!file) {
        std::wcerr << L"Error: Could not open file " << std::wstring(filename.begin(), filename.end()) << std::endl;
        exit(1);
    }
    std::wstringstream buffer;
    buffer << file.rdbuf();
    std::wstring content = buffer.str();

    // Remove newlines
    content.erase(std::remove(content.begin(), content.end(), L'\n'), content.end());
    content.erase(std::remove(content.begin(), content.end(), L'\r'), content.end());
    content.erase(std::remove(content.begin(), content.end(), L' '), content.end());
    content.erase(std::remove(content.begin(), content.end(), L'\t'), content.end());

    return content;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::wcerr << L"Usage: " << std::wstring(argv[0], argv[0] + strlen(argv[0])) << L" <filename>" << std::endl;
        return 1;
    }

    std::wstring code = readFile(argv[1]);

    BrainfuckInterpreter interpreter(code);
    interpreter.execute();

    return 0;
}
