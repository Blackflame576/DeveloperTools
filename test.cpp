// #include <iostream>
// // #include <unistd.h>
// #include <map>
// #include <stdio.h>
// #include <stdlib.h>
// #include <curl/curl.h>
// #include "src/Progressbar.hpp"
// #include <cctype>
// #include <fstream>
// #include <filesystem>
// // #include <Windows.h>
// #include "src/DatabaseConnect.cpp"
// // #include <tchar.h>

// // #include <shlwapi.h>

// // #pragma comment(lib,"shlwapi.lib")

// // #include "shlobj.h"

// using namespace std;
// using namespace DB;
// using namespace Bar;

// string DoneChar = "#";
// string TodoChar = " ";
// string StartChar = "[";
// string EndChar = "]";
// string output;
// int n_char = 50;
// int n_current = 0;
// int process = 0;
// int TempPercentage;
// double DownloadSpeed = 0.0;
// CURL *curl = curl_easy_init();
// CURLcode res;
// string ProjectDir = std::filesystem::current_path().generic_string();
// // int n_done = 0;
// ProgressBar_v1 bar;
// // TCHAR szPath[MAX_PATH];

// int CallbackProgress(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
// {
//     if (TotalToDownload <= 0.0)
//     {
//         return 0;
//     }

//     int Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
//     if (TempPercentage != Percentage && TempPercentage <= 100)
//     {
//         curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
//         if ((CURLE_OK == res) && (DownloadSpeed > 0.0))
//         {
//             // printf("Average download speed: %lu kbyte/sec.\n",
//             //         (unsigned long)(DownloadSpeed / 1024));
//             float Speed = (float)(DownloadSpeed / 1024);
//             bar.Update(Speed);
//             TempPercentage = Percentage;
//         }
//     }
//     return 0;
// }
// // Function for write data from curl
// size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
// {
//     size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
//     return WriteProcess;
// }
// int Download(string url, string dir)
// {
//     try
//     {
//         string name = (url.substr(url.find_last_of("/")));
//         string filename = dir + "/" + name.replace(name.find("/"), 1, "");
//         FILE *file = fopen(filename.c_str(), "wb");
//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
//         curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &CallbackProgress);
//         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//         curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
//         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteData);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
//         CURLcode response = curl_easy_perform(curl);
//         curl_easy_cleanup(curl);
//         fclose(file);
//         cout << "" << endl;
//         return 200;
//     }
//     catch (exception &error)
//     {
//         return 502;
//     }
// }

// int main()
// {

//     string Tables[11] = {"CDevelopmentTools", "CppDevelopmentTools", "CSDevelopmentTools", "PythonDevelopmentTools", "JavaDevelopmentTools",
//                          "JavaScriptDevelopmentTools", "KotlinDevelopmentTools", "RubyDevelopmentTools", "RustDevelopmentTools", "GoDevelopmentTools",
//                          "PHPDevelopmentTools"};
//     const char *ch = "DB/AppInstaller.db";
//     std::filesystem::path current_path = std::filesystem::current_path().generic_string();
//     string DB_PATH = current_path.string() + "/src/" + ch;
//     // cout << DB_PATH << endl;
//     Database database;
//     database.open(&DB_PATH);
//     // string Command = database.GetValueFromDB("Applications","Docker","Windows");
//     // cout << Command << endl;
//     // string url = "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/v0.1_win_amd64/AppInstaller.db";
//     // string name = (url.substr(url.find_last_of("/")));
//     // string filename = ProjectDir + "/" + name.replace(name.find("/"), 1, "");
//     // FILE *file = fopen(filename.c_str(), "wb");
//     // CURL *curl = curl_easy_init();
//     // curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//     // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//     // curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
//     // curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
//     // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//     // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
//     // curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
//     // CURLcode response = curl_easy_perform(curl);
//     // curl_easy_cleanup(curl);
//     // fclose(file);
//     database.AddApplications(Tables);
//     // char *user = getenv("USERPROFILE");
//     // SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, szPath);
//     // cout << user << endl;
//     return 0;
// }
#include <iostream>
const char *getBuild()
{ // Get current architecture, detectx nearly every architecture. Coded by Freak
#if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
        return "x86_32";
#elif defined(__ARM_ARCH_2__)
        return "ARM2";
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
        return "ARM3";
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
        return "ARM4T";
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
        return "ARM5"
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
        return "ARM6T2";
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
        return "ARM6";
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7";
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7A";
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7R";
#elif defined(__ARM_ARCH_7M__)
        return "ARM7M";
#elif defined(__ARM_ARCH_7S__)
        return "ARM7S";
#elif defined(__aarch64__) || defined(_M_ARM64)
        return "ARM64";
#elif defined(mips) || defined(__mips__) || defined(__mips)
        return "MIPS";
#elif defined(__sh__)
        return "SUPERH";
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
        return "POWERPC";
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
        return "POWERPC64";
#endif
}
 
int main()
{
    printf(getBuild());
    return 0;
}