#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>

// Define a structure to store namespaces and their variables
struct Namespace {
    std::unordered_map<std::string, std::string> variables;
    std::unordered_map<std::string, std::string> functions;
};

void compileSpsToJs(const std::string& inputFilename, const std::string& outputFilename) {
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
    bool insideFunction = false;
    bool insideClass = false;
    bool insideNamespace = false;
    std::string className;
    std::string namespaceName;
    std::unordered_map<std::string, Namespace> namespaces;
    Namespace currentNamespace;

    while (std::getline(inputFile, line)) {
        // Replace Sappyscript syntax with JavaScript syntax
        std::regex varRegex("var\\(([^,]+),\\s*\"([^\"]+)\"\\);");
        line = std::regex_replace(line, varRegex, "let $1 = \"$2\";");

        std::regex constRegex("const\\(([^,]+),\\s*\"([^\"]+)\"\\);");
        line = std::regex_replace(line, constRegex, "const $1 = \"$2\";");

        std::regex inputRegex("input\\(([^)]+)\\);");
        line = std::regex_replace(line, inputRegex, "let $1 = prompt();");

        std::regex logRegex("log\\(\"([^\"]+)\",\\s*([^)]+)\\);");
        line = std::regex_replace(line, logRegex, "console.log($1.replace(\"%s\", $2));");

        std::regex ifRegex("if\\(\\&([^=]+)==\"([^\"]+)\"\\)\\{\\}");
        line = std::regex_replace(line, ifRegex, "if ($1 === \"$2\") { }");

        std::regex forRegex("for\\(\\s*;\\s*;\\s*;\\s*\\)\\{\\}");
        line = std::regex_replace(line, forRegex, "for (;;) { }");

        std::regex elseRegex("else\\{\\}");
        line = std::regex_replace(line, elseRegex, "} else { }");

        std::regex elseIfRegex("elseif\\(\\&([^=]+)==\"([^\"]+)\"\\)\\{\\}");
        line = std::regex_replace(line, elseIfRegex, "} else if ($1 === \"$2\") { }");

        std::regex importRegex("import\\s+\"([^\"]+)\";");
        line = std::regex_replace(line, importRegex, "require(\"$1\");");

        std::regex functionRegex("function\\s+([^\\(]+)\\(([^\\)]*)\\)\\s*\\{");
        if (std::regex_search(line, functionRegex)) {
            insideFunction = true;
            if (insideNamespace) {
                currentNamespace.functions[std::regex_replace(line, functionRegex, "$1")] = line;
            }
        }

        std::regex returnRegex("return\\s+([^;]+);");
        line = std::regex_replace(line, returnRegex, "return $1;");

        // If inside a function, add function keyword to the line
        if (insideFunction && !std::regex_search(line, functionRegex)) {
            line = "function " + line;
        }

        // Check if leaving a function block
        if (insideFunction && line.find("}") != std::string::npos) {
            insideFunction = false;
        }

        std::regex classRegex("class\\s+([^\\{]+)\\s*\\{");
        if (std::regex_search(line, classRegex)) {
            insideClass = true;
            className = std::regex_replace(line, classRegex, "$1");
        }

        // If inside a class, add class keyword to the line
        if (insideClass && !std::regex_search(line, classRegex)) {
            line = className + "." + line;
        }

        // Check if leaving a class block
        if (insideClass && line.find("}") != std::string::npos) {
            insideClass = false;
        }

        std::regex namespaceRegex("namespace\\s+([^\\{]+)\\s*\\{");
        if (std::regex_search(line, namespaceRegex)) {
            insideNamespace = true;
            namespaceName = std::regex_replace(line, namespaceRegex, "$1");
            currentNamespace = namespaces[namespaceName];
        }

        // If inside a namespace, add namespace keyword to the line
        if (insideNamespace && !std::regex_search(line, namespaceRegex)) {
            line = namespaceName + "." + line;
        }

        // Check if leaving a namespace block
        if (insideNamespace && line.find("}") != std::string::npos) {
            insideNamespace = false;
            namespaces[namespaceName] = currentNamespace;
        }

        // Replace new keyword
        std::regex newRegex("new\\s+(\\w+)\\(([^\\)]*)\\);");
        line = std::regex_replace(line, newRegex, "new $1($2)");

        // Replace await keyword
        std::regex awaitRegex("await\\s+(\\w+)\\(([^\\)]*)\\);");
        line = std::regex_replace(line, awaitRegex, "await $1($2)");

        // Replace function arguments default values
        std::regex defaultArgRegex("&(\\w+)=(\"[^\"]+\"|[^\\s,\\)]+)");
        line = std::regex_replace(line, defaultArgRegex, "$1 = $2");

        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Compilation successful. Output file: " << outputFilename << std::endl;
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
