#include <iostream>

// Checking the name of the operating system and importing the necessary libraries for this system
#if defined(__linux__)
    #include "include/Installer_Linux.hpp"
    using namespace Linux;
#elif __APPLE__
    #include "include/Installer_macOS.hpp"
    using namespace macOS;
#elif _WIN32
    #include "include/Installer_Windows.hpp"
    using namespace Windows;
#endif

using namespace std;

void Installer::InstallStableVersion()
{
    filesystem::exists(NewApplicationFolder) == false ; filesystem::create_directory(NewApplicationFolder);
    // result = Download(UrlStableVersion,NewApplicationFolder);
    // switch (result) {
    //     case 200:
    //         return 0;
    // }
}

void Installer::InstallBetaVersion()
{
    filesystem::exists(NewApplicationFolder) == false ; filesystem::create_directory(NewApplicationFolder);
    // result = Download(UrlStableVersion,NewApplicationFolder);
    // switch (result) {
    //     case 200:
    //         return 0;
    // }
}

int main()
{
    Installer installer;
    cout << "1. Stable Version" << endl;
    cout << "2. Beta Version" << endl;
    cout << "Выберите версию DeepForge Toolset:";
    getline(cin, Answer);
    switch (stoi(Answer)) {
        case 1:
            installer.InstallStableVersion();
        case 2:
            installer.InstallBetaVersion();
    }
    return 0;
}