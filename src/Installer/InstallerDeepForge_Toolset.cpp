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

void Installer::InstallLatestStableVersion() 
{
    MakeDirectory(NewTempFolder);
}


void Installer::InstallStableVersion()
{
    MakeDirectory(NewTempFolder);
    result = Download(DB_URL,NewTempFolder);
    // filesystem::exists(NewApplicationFolder) == false ; filesystem::create_directory(NewApplicationFolder);
    // result = Download(UrlStableVersion,NewApplicationFolder);
    // switch (result) {
    //     case 200:
    //         return 0;
    // }
}

void Installer::InstallLatestBetaVersion()
{
    MakeDirectory(NewTempFolder);
}

void Installer::InstallBetaVersion()
{
    MakeDirectory(NewTempFolder);
    // filesystem::exists(NewApplicationFolder) == false ; filesystem::create_directory(NewApplicationFolder);
    // result = Download(UrlStableVersion,NewApplicationFolder);
    // switch (result) {
    //     case 200:
    //         return 0;
    // }
}

int main()
{
    Installer installer;
    cout << "1. Latest Stable Version" << endl;
    cout << "2. Stable Version" << endl;
    cout << "3. Latest Beta Version" << endl;
    cout << "4. Beta Version" << endl;
    cout << "Выберите версию DeepForge Toolset:";
    getline(cin, Answer);
    switch (stoi(Answer)) {
        case 1:
            installer.InstallLatestStableVersion();
            break;
        case 2:
            installer.InstallStableVersion();
            break;
        case 3:
            installer.InstallLatestBetaVersion();
            break;
        case 4:
            installer.InstallBetaVersion();
    }
    return 0;
}