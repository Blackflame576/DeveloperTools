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
#include <curl/curl.h>

using namespace std;
using namespace InstallerDeveloperTools;

progressbar bar(100);

size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
    return WriteProcess;
}
int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{

    if (TotalToDownload <= 0.0) {
        return 0;
    }

    Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
    if (TempPercentage != Percentage && TempPercentage <= 100) {
        bar.update();
        TempPercentage = Percentage;
    }
    return 0;
}

class Installer {
    public:
        void InstallDeveloperTools_Stable() {
            string chmod_command = "sudo chmod -R 777 /usr/local/bin/";
            string mkdir_command = "sudo mkdir " + NewOrganizationFolder;
            // system(chmod_command.c_str());
            // system(mkdir_command.c_str());
            // mkdir(NewOrganizationFolder.c_str(),0777);
            // mkdir(NewApplicationFolder.c_str(),0777);
            chmod("/etc/", S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
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
            // if (filesystem::exists(NewOrganizationFolder) == false) {
            //     filesystem::create_directory(NewOrganizationFolder);
            // }
            // if (filesystem::exists(NewApplicationFolder) == false) {
            //     filesystem::create_directory(NewApplicationFolder);
            // }
            Download(BetaDownloadURL,BetaInstallPath);
            cout << "" << endl;
        }
        void InstallSnap() {
            cout << "Установка Snap ..." << endl;
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
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
                curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
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
    installer.InstallSnap();
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