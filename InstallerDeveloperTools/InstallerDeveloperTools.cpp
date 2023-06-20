#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"

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