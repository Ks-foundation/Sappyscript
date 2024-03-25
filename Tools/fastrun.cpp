#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    // 입력된 명령을 분석
    if (argc < 2) {
        std::cerr << "Usage: qnode <script_file>" << std::endl;
        return 1;
    }

    std::string command = "node " + std::string(argv[1]);

    // 명령 실행
    int result = std::system(command.c_str());

    // 실행 결과 확인
    if (result == 0) {
        std::cout << "Script executed successfully." << std::endl;
        return 0;
    } else {
        std::cerr << "Error executing script." << std::endl;
        return 1;
    }
}
