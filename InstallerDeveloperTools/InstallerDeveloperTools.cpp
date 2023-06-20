#include <iostream>
#include<string>
#pragma comment(lib, "urlmon.lib")
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    // cout << "Linux" << endl;
#elif __FreeBSD__
    // cout << "FreeBSD" << endl;
#elif __APPLE__
    // cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

using namespace std;
using namespace InstallerDeveloperTools;

class Installer {
    public:
        void InstallDeveloperTools() {
            progressbar bar(100);
            for (int i = 0;i < 51;i++) {
                bar.update();
            }
            cout << "" << endl;
        }
    private:
    // Installer();
    // ~Installer();
};

int main() {
    Installer installer;
    installer.InstallDeveloperTools();
} 