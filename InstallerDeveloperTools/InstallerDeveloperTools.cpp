#include <iostream>
#include<string>
#pragma comment(lib, "urlmon.lib")
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"
#include <regex>
#include <fstream>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    // std::cout << "Linux" << endl;
#elif __FreeBSD__
    // std::cout << "FreeBSD" << endl;
#elif __APPLE__
    // std::cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

using namespace std;
using namespace InstallerDeveloperTools;

string GetNameDistribution() {
    if (OS_NAME == "Windows") {
        ifstream stream("/etc/os-release");
        string line;
        regex nameRegex("^NAME=\"(.*?)\"$");
        smatch match;
        string name;
        while (getline(stream,line)) {
            if (regex_search(line,match,nameRegex)) {
                name = match[1].str();
                break;
            }
        }
        return name;
    } 
}

class Installer {
    public:
        void InstallDeveloperTools() {
            
        }
    private:
    // Installer();
    // ~Installer();
};

int main() {
    #if defined(__linux__)
        OS_NAME = "Linux";
        NameDistribution = GetNameDistribution();
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    Installer installer;
    installer.InstallDeveloperTools();
} 