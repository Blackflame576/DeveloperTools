#include <iostream>
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"
#include <filesystem>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace InstallerDeveloperTools;

progressbar bar(100);

class Installer {
    public:
        void InstallDeveloperTools_Stable() {
            if (filesystem::exists(NewOrganizationFolder) == false) {
                filesystem::create_directory(NewOrganizationFolder);
            }
            if (filesystem::exists(NewApplicationFolder) == false) {
                filesystem::create_directory(NewApplicationFolder);
            }
            cout << "" << endl;
        }
        void InstallDeveloperTools_Beta() {
            if (filesystem::exists(NewOrganizationFolder) == false) {
                filesystem::create_directory(NewOrganizationFolder);
            }
            if (filesystem::exists(NewApplicationFolder) == false) {
                filesystem::create_directory(NewApplicationFolder);
            }
            cout << "" << endl;
        }
    private:
};

int main()
{
    Installer installer;
    cout << "1. DeveloperTools Stable Version" << endl;
    cout << "2. DeveloperTools Beta Version" << endl;
    cout << "Выберите версию DeveloperTools:";
    getline(cin,Answer);
    if (Answer == "1") {
        installer.InstallDeveloperTools_Stable();
    }
    else if (Answer == "2") {
        installer.InstallDeveloperTools_Beta();
    }
    
    return 0;
}