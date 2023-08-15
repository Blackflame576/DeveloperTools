#include <iostream>
#include <unistd.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "src/Progressbar.hpp"
#include <cctype>
#include <fstream>
#include "src/DatabaseConnect.cpp"

using namespace std;
using namespace DB;
string DoneChar = "#";
string TodoChar = " ";
string StartChar = "[";
string EndChar = "]";
string output;
int n_char = 50;
int n_current = 0;
int process = 0;
int TempPercentage;
double DownloadSpeed = 0.0;
CURL* curl = curl_easy_init();
CURLcode res;
// int n_done = 0;
ProgressBar bar;

int CallbackProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
    if (TotalToDownload <= 0.0) {
        return 0;
    }

    int Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
    if (TempPercentage != Percentage && TempPercentage <= 100) {
        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
        if ((CURLE_OK == res) && (DownloadSpeed > 0.0)) {
            // printf("Average download speed: %lu kbyte/sec.\n",
            //         (unsigned long)(DownloadSpeed / 1024));
            float Speed = (float) (DownloadSpeed / 1024);
            bar.Update(Speed);
            TempPercentage = Percentage;
        }
    }
    return 0;
}
// Function for write data from curl
size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
    return WriteProcess;
}
int Download(string url, string dir)
{
    try {
        string name = (url.substr(url.find_last_of("/")));
        string filename = dir + "/" + name.replace(name.find("/"), 1, "");
        FILE* file = fopen(filename.c_str(), "wb");
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
    catch (exception& error) {
        return 502;
    }
}


int main() {

    // string Tables[11] = {"CDevelopmentTools","CppDevelopmentTools","CSDevelopmentTools","PythonDevelopmentTools","JavaDevelopmentTools",
    //                    "JavaScriptDevelopmentTools","KotlinDevelopmentTools","RubyDevelopmentTools","RustDevelopmentTools","GoDevelopmentTools",
    //                    "PHPDevelopmentTools"
    // };
    // Database database;
    // database.AddValues(Tables);
//    map<string,string> DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks","Language");
//    for (const auto &element:DevelopmentPacks) {
//        cout << element.first << " " << element.second << endl;
//    }
    // colours.insert(std::pair<int,string(*)[3]>(1,&red));
    // colours.insert(std::pair<int,int(*)[3]>(GLUT_MIDDLE_BUTTON,&blue));
    // colours.insert(std::pair<int,int(*)[3]>(GLUT_RIGHT_BUTTON,&green));
//    Download("http://212.183.159.230/100MB.zip",".\\");
    // std::cout << "\rDone            " << std::endl;
    return 0;
}