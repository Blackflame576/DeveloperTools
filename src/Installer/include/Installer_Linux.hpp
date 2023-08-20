#include <filesystem>
#include <iostream>
#include "Progressbar.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

using namespace std;

namespace Linux
{
    int result;
    int Percentage;
    int TempPercentage = 0;
    string ProjectDir = std::filesystem::current_path().generic_string();
    const string UrlStableVersion;
    const string UrlBetaVersion;
    // const string DownloadURL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    // const string InstallPath = "kotlin-compiler-1.8.22.zip";
    string Answer;
    const string NewApplicationFolder = "C:\\ProgramData\\DeepForge\\DeepForge Toolset";
    ProgressBar progressbar;
    CURL *curl = curl_easy_init();
    CURLcode res;

    // Function for calc percentage of download progresss 
    int CallbackProgress(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0)
        {
            return 0;
        }

        Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != Percentage && TempPercentage <= 100)
        {
            curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
            if ((CURLE_OK == res) && (DownloadSpeed > 0.0))
            {
                // printf("Average download speed: %lu kbyte/sec.\n",
                //         (unsigned long)(DownloadSpeed / 1024));
                float Speed = (float)(DownloadSpeed / 1024);
                progressbar.Update(Speed);
                TempPercentage = Percentage;
            }
        }
        return 0;
    }

    // Function for write data from curl
    size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }
    // Main class 
    class Installer
    {
        public:
            void InstallStableVersion();
            void InstallBetaVersion();
            Installer();

        private:
            int Download(string url,string dir)
            {
                try
                {
                    string name = (url.substr(url.find_last_of("/")));
                    string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                    FILE *file = fopen(filename.c_str(), "wb");
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
                    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &CallbackProgress);
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                    curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
                    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
                    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteData);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
                    CURLcode response = curl_easy_perform(curl);
                    curl_easy_cleanup(curl);
                    fclose(file);
                    cout << "" << endl;
                    return 200;
                }
                catch (exception &error)
                {
                    return 502;
                }
            }
    };
}