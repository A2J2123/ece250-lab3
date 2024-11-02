//./tokenize.out < inputs/test01.in
#include <iostream>
#include "tokenize.h"
#include <sstream>

int main() {
    std::string command;
    getline(std::cin, command);
    TwoWayDictionary d(std::stoi(command.substr(7))); 
    std::cout << "success" << std::endl;


    while (true) {
        std::cin >> command; 
        if (command == "insert") {
            std::string word;
            std::cin >> word;
            if (d.insert(word)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        } else if (command == "load") {
            std::string filename;
            std::cin >> filename;
            if (d.load(filename)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }

        } else if (command == "tok") {
            std::string word;
            std::cin >> word;
            std::cout << d.tok(word) << std::endl;
        } else if (command == "ret") {
            int token;
            std::cin >> token;
            std::cout << d.ret(token) << std::endl;

        } else if (command == "tok_all") {
            std::string input;
            std::getline(std::cin >> std::ws, input);
            std::stringstream ss(input);
            std::string word;

            while (ss >> word) {
                std::cout << d.tok(word) << " ";
            }
            std::cout << std::endl;

        } else if (command == "ret_all") {
            std::string input;
            std::getline(std::cin >> std::ws, input);

            std::istringstream iss(input);
            std::string token_str;

            while (iss >> token_str) {
                int token = std::stoi(token_str);
                std::cout << d.ret(token) << " ";
            }
            std::cout << std::endl;

        } else if (command == "print") {
            int k;
            std::cin >> k;
            d.print(k);
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}