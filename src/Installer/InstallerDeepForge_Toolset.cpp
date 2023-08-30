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


Installer installer;
map<string,string> Channels = {
    {"1","stable\\latest"},
    {"2","stable"},
    {"3","beta\\latest"},
    {"4","beta"}
};
string LabelChannels[4] = {
    "1. Latest Stable Version",
    "2. Stable Version",
    "3. Latest Beta Version",
    "4. Beta Version"
};

void Installer::InstallDeepForgeToolset(string channel)
{
    string version;
    string ApplicationURL;
    string name;
    string filename;
    string ArchivePath;
    string Command;
    string file_path;

    MakeDirectory(NewTempFolder);
    result = Download(DB_URL,NewTempFolder);
    Database database(&DB_PATH);
    switch (result) {
        case 200:
            version = database.GetVersionFromDB(NameVersionTable,channel,"Version",Architecture);
            ApplicationURL = database.GetApplicationURL(NameVersionTable,channel,"Url",Architecture,version);
            // result = Download(ApplicationURL,NewTempFolder);
            result = 200;
            if (result == 200) 
            {
                name = (ApplicationURL.substr(ApplicationURL.find_last_of("/")));
                ArchivePath = NewTempFolder + "\\" + name.replace(name.find("/"), 1, "");
                Command = "tar -xf " + ArchivePath + " --directory " + NewApplicationFolder;
                // system(Command.c_str());
                file_path = NewApplicationFolder + "\\DeepForgeToolset.exe";
                CreateSymlink("DeepForgeToolset.exe",file_path);
            }
            break;
        case 502:
            throw domain_error("Error downloading archive - 502"); 
    }
}

int main()
{
    for (int i = 0;i < (sizeof(LabelChannels)/sizeof(LabelChannels[0]));i++) 
    {
        cout << LabelChannels[i] << endl;
    }
    cout << "Change version of DeepForge Toolset:";
    getline(cin, Answer);
    // with for loop
    if (Channels.find(Answer) != Channels.end())
    {
        installer.InstallDeepForgeToolset(Channels[Answer]);
    }
    return 0;
}