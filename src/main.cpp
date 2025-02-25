#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stack>
#include <unordered_map>

// 네임스페이스 및 클래스 관리 구조체
struct Namespace {
    std::unordered_map<std::string, std::string> variables;
    std::unordered_map<std::string, std::string> functions;
};

// 변환기 함수
void compileSpsToJs(const std::string &inputFilename, const std::string &outputFilename) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Failed to open input file." << std::endl;
        return;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return;
    }

    std::string line;
    std::stack<std::string> scopeStack;
    std::unordered_map<std::string, Namespace> namespaces;
    Namespace currentNamespace;
    std::string currentNamespaceName;
    std::string currentClassName;
    bool insideClass = false;
    int indentationLevel = 0;

    while (std::getline(inputFile, line)) {
        std::string originalLine = line;
        std::string indent = std::string(indentationLevel * 4, ' ');  // 들여쓰기 적용

        // 변수 변환
        std::regex varRegex(R"(var\(([^,]+),\s*\"([^\"]+)\"\);)");
        line = std::regex_replace(line, varRegex, indent + "let $1 = \"$2\";");

        // 상수 변환
        std::regex constRegex(R"(const\(([^,]+),\s*\"([^\"]+)\"\);)");
        line = std::regex_replace(line, constRegex, indent + "const $1 = \"$2\";");

        // 입력 처리 변환
        std::regex inputRegex(R"(input\(([^)]+)\);)");
        line = std::regex_replace(line, inputRegex, indent + "let $1 = prompt();");

        // 로그 변환 (템플릿 리터럴 적용)
        std::regex logRegex(R"(log\(\"([^\"]+)\",\s*([^)]+)\);)");
        line = std::regex_replace(line, logRegex, indent + "console.log(`$1`.replace('%s', $2));");

        // if 조건문 변환
        std::regex ifRegex(R"(if\(&([^=]+)==\"([^\"]+)\"\)\{\})");
        line = std::regex_replace(line, ifRegex, indent + "if ($1 === \"$2\") { }");

        // for 루프 변환
        std::regex forRegex(R"(for\(\s*;\s*;\s*;\s*\)\{\})");
        line = std::regex_replace(line, forRegex, indent + "for (;;) { }");

        // else 및 else-if 변환
        std::regex elseRegex(R"(else\{\})");
        line = std::regex_replace(line, elseRegex, indent + "} else { }");

        std::regex elseIfRegex(R"(elseif\(&([^=]+)==\"([^\"]+)\"\)\{\})");
        line = std::regex_replace(line, elseIfRegex, indent + "} else if ($1 === \"$2\") { }");

        // import 변환
        std::regex importRegex(R"(import\s+\"([^\"]+)\";)");
        line = std::regex_replace(line, importRegex, indent + "const $1 = require(\"$1\");");

        // 함수 변환 (스코프 고려)
        std::regex functionRegex(R"(function\s+([^\(]+)\(([^\)]*)\)\s*\{)");
        if (std::regex_search(line, functionRegex)) {
            scopeStack.push("function");
            indentationLevel++;
        }

        // return 변환
        std::regex returnRegex(R"(return\s+([^;]+);)");
        line = std::regex_replace(line, returnRegex, indent + "return $1;");

        // 클래스 변환 (JavaScript class)
        std::regex classRegex(R"(class\s+([^\{]+)\s*\{)");
        if (std::regex_search(line, classRegex)) {
            insideClass = true;
            currentClassName = std::regex_replace(line, classRegex, "$1");
            scopeStack.push("class");
            indentationLevel++;
        }

        // 네임스페이스 변환 (JavaScript 객체)
        std::regex namespaceRegex(R"(namespace\s+([^\{]+)\s*\{)");
        if (std::regex_search(line, namespaceRegex)) {
            currentNamespaceName = std::regex_replace(line, namespaceRegex, "$1");
            scopeStack.push("namespace");
            indentationLevel++;
            line = indent + "let " + currentNamespaceName + " = {";
        }

        // new 연산자 변환
        std::regex newRegex(R"(new\s+(\w+)\(([^)]*)\);)");
        line = std::regex_replace(line, newRegex, indent + "new $1($2);");

        // await 변환
        std::regex awaitRegex(R"(await\s+(\w+)\(([^)]*)\);)");
        line = std::regex_replace(line, awaitRegex, indent + "await $1($2);");

        // 기본 매개변수 변환
        std::regex defaultArgRegex(R"(&(\w+)=(\"[^\"]+\"|[^,)\s]+))");
        line = std::regex_replace(line, defaultArgRegex, indent + "$1 = $2");

        // 블록 종료(`}`) 감지
        if (line.find("}") != std::string::npos) {
            if (!scopeStack.empty()) {
                scopeStack.pop();
                indentationLevel--;
            }
        }

        // 최종 변환된 코드 출력
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "✅ Compilation successful! Output file: " << outputFilename << std::endl;
}

int main() {
    std::string inputFilename, outputFilename;
    std::cout << "Enter the input file name (with .sps extension): ";
    std::cin >> inputFilename;
    std::cout << "Enter the output file name (with .js extension): ";
    std::cin >> outputFilename;

    compileSpsToJs(inputFilename, outputFilename);
    
    return 0;
}
