#include <iostream>
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"
#include <filesystem>
// #include <conio.h>
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
            Download(DownloadURL,InstallPath);
            cout << "" << endl;
        }
        void InstallDeveloperTools_Beta() {
            if (filesystem::exists(NewOrganizationFolder) == false) {
                filesystem::create_directory(NewOrganizationFolder);
            }
            if (filesystem::exists(NewApplicationFolder) == false) {
                filesystem::create_directory(NewApplicationFolder);
            }
            Download(BetaDownloadURL,BetaInstallPath);
            cout << "" << endl;
        }
    private:
        int Download(string url, string dir)
        {
            try {
                string name = (url.substr(url.find_last_of("/")));
                string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                CURL* curl = curl_easy_init();
                FILE* file = fopen(filename.c_str(), "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
                curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_func);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
                CURLcode response = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                fclose(file);
                cout << "" << endl;
                return 200;
            }
            catch (string error) {
                return 502;
            }
        }
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