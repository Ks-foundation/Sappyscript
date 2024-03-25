#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string middlewareFile = "middleware.txt";

std::vector<std::string> getMiddlewareList() {
    std::ifstream file(middlewareFile);
    std::vector<std::string> middlewareList;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            middlewareList.push_back(line);
        }
        file.close();
    }

    return middlewareList;
}

void saveMiddlewareList(const std::vector<std::string>& middlewareList) {
    std::ofstream file(middlewareFile);

    if (file.is_open()) {
        for (const auto& middleware : middlewareList) {
            file << middleware << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to save middleware list." << std::endl;
    }
}

void addMiddleware(const std::string& name) {
    auto middlewareList = getMiddlewareList();
    middlewareList.push_back(name);
    saveMiddlewareList(middlewareList);
}

void removeMiddleware(const std::string& name) {
    auto middlewareList = getMiddlewareList();
    middlewareList.erase(std::remove(middlewareList.begin(), middlewareList.end(), name), middlewareList.end());
    saveMiddlewareList(middlewareList);
}

void displayMiddlewareList() {
    auto middlewareList = getMiddlewareList();
    std::cout << "Middleware List:" << std::endl;
    for (const auto& middleware : middlewareList) {
        std::cout << middleware << std::endl;
    }
}

int main() {
    std::cout << "Welcome to Fastnpm" << std::endl;
    while (true) {
        std::cout << "1. Add Middleware" << std::endl;
        std::cout << "2. Remove Middleware" << std::endl;
        std::cout << "3. Display Middleware List" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose an option: ";

        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string middlewareName;
                std::cout << "Enter middleware name: ";
                std::cin >> middlewareName;
                addMiddleware(middlewareName);
                break;
            }
            case 2: {
                std::string middlewareName;
                std::cout << "Enter middleware name to remove: ";
                std::cin >> middlewareName;
                removeMiddleware(middlewareName);
                break;
            }
            case 3:
                displayMiddlewareList();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cerr << "Invalid option! Please choose a valid option." << std::endl;
        }
    }

    return 0;
}
