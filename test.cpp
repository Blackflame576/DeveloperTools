// #include <iostream>
// #include <map>
// #include <filesystem>
// #include <curl/curl.h>
// // #include <sys/utsname.h>

// using namespace std;
// // using namespace zipper;
// using funct_t = void(*)(void);
// void InstallGit() {
//     cout << "Git installer" << endl;
// }
// // map<string,funct_t> apps {
// //     {"Git",InstallGit}
// // };

// size_t WriteData(void* ptr,size_t size,size_t nmemb,FILE* stream) {
//     size_t WriteProcess = fwrite(ptr,size,nmemb,stream);
//     return WriteProcess;
// }
// // int uname(struct utsname *buf);
// // struct utsname 
// // {
// //        char sysname[];    /* Operating system name (e.g., "Linux") */
// //        char nodename[];   /* Name within "some implementation-defined network" */
// //        char release[];    /* OS release (e.g., "2.6.28") */
// //        char version[];    /* OS version */
// //        char machine[];    /* Hardware identifier */
// //        #ifdef _GNU_SOURCE
// //           char domainname[]; /* NIS or YP domain name */
// //        #endif
// // };
// void Download(string url) {
//     string name = (url.substr(url.find_last_of("/")));
//     string filename = name.replace(name.find("/"),1,"");
//     CURL* curl = curl_easy_init();
//     FILE* file = fopen(filename.c_str(),"wb");
//     curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
//     curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//     curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
//     curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER, false);
//     curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteData);
//     curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
//     CURLcode response = curl_easy_perform(curl);
//     curl_easy_cleanup(curl);
//     fclose(file);
// }
// int main() {
//     auto ProjectDir = std::filesystem::current_path();
//     string path_string = ProjectDir.generic_string();
//     // string KotlinDir = path_string + "/Programms/Kotlin";
//     string NewKotlinDir = "C:\\Kotlin";
//     std::filesystem::create_directory(NewKotlinDir);
    
//     // cout << "Current Path:" << ProjectDir << endl;
//     // cout << "Kotlin Path:" << KotlinDir << endl;
//     // std::filesystem::copy(KotlinDir,NewKotlinDir,std::filesystem::copy_options::recursive);
//     // system("copy " + KotlinDir + " " + NewKotlinDir);
//     // apps["Git"]();
    
//     // Download("https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip");
//     // Unzipper unzipper("kotlin-compiler-1.8.22.zip");
//     // unzipper.extract();
//     // unzipper.close();
//     string command = "tar -xf" + path_string +"/kotlin-compiler-1.8.22.zip " + "--directory " + NewKotlinDir;
//     system(command.c_str());
//     system("pause");
//     return 0;
// }
#define FMT_HEADER_ONLY
#include <iostream>
// #include "test.hpp"
#include <map>
#include <functional>
// #include "test_test.cpp"
// #include "src/Logger.cpp"
// #include <iomanip>
#include <stdio.h>
#include <format>
#include <Windows.h>
// #include "fmt/format.h"

using namespace std;
// using namespace Logger;
using funct_t = void (*)(void);

void print() {
    cout << "ddjisjidd" << endl;
}

class example {
    public:
        void print() {
            cout << "ddjisjidd" << endl;
        }

};
string haveString = "";
string new_sentence = "";
string new_string(string sentence) {
    if (haveString == "") {
        new_sentence = "";
        haveString = sentence;
        return new_sentence;
    }
    else {
        new_sentence = "";
        new_sentence = format("{:<40} {:<15}\n",haveString,sentence);
        // new_sentence = haveString
        // cout << new_sentence << endl;
        haveString = "";
        return new_sentence;
    }
}
// typedef void (example::*Ptr) ();
// using namespace N;
// using MapType = std::map<string, std::function<void()>>;
// typedef void(example::*runFunc)(void) mapType;
// typedef std::map<string, runFunc> myMapType;

int main() {
    example example_class;
    string table_rows;
    map<int,string> programms = {
        {1,"Git"},{2,"VSCode"},{3,"PyCharm"},{4,"Sublime Text"},
        {5,"IntelliJIDEA Community"},{6,"IntelliJIDEA Ultimate"}
    };
    for(int i = 1;const auto &element:programms) {
        string name = to_string(element.first) + ". " + element.second;
        string getString = new_string(name);
        if (programms.size() % 2 == 0) {
            if (getString != "") {
                cout << getString << endl;
            }
        }
        else {
            if (getString != "") {
                cout << getString << endl;
            }
            if (i == programms.size()) {
                cout << name << endl;
            }
        }
        i++;
    }
    cout << table_rows << endl;
    for(int i = 1;const auto &element:programms) {
        string name = to_string(element.first) + ". " + element.second;
        string getString = new_string(name);
        if (programms.size() % 2 == 0) {
            if (getString != "") {
                cout << getString << endl;
            }
        }
        else {
            if (getString != "") {
                cout << getString << endl;
            }
            if (i == programms.size()) {
                cout << name << endl;
            }
        }
        i++;
    }
    cout << table_rows << endl;
    string PATH = std::getenv("PATH");
    string Command = "start powershell.exe -File .\\src\\Scripts\\AddEclipsePath.ps1";
    system(Command.c_str());
    string NewPath = ";C:\\eclipse'";
    SetEnvironmentVariableA("PATH",NewPath.c_str());
    // Ptr ptr;
    // system("chcp 65001");
    // using funct_t = void(example::*)(void);
    // map<int,funct_t> Commands= {
    //     {1,&example::print}
    // };
    // (example_class.*(Commands[1]))();
    // map<string, function<void()>> Tools = {
    //     {"test",[&example_class](){example_class.print();}}
    // };
    // Tools["test"]();
    // typedef void (example::*funct_t)(void);
    // typedef std::map<std::int, funct_t> Commands_func_map_t;
    // Commands_func_map_t Commands = {
    //     {1,&example::print}
    // };


    // funct_t functions[] = {&print};
    // functions[0]();
    // const char *test_str = "test_string error test_string error test_string error test_string error test_string error test_string error test_string error test_string error test_string error";
    // MainLogger main_class(false);
    // main_class.SetLogPath("logs/test.log");
    // main_class.Debug("Test");
    // main_class.Error("Error");
    // main_class.Info("Info");
    // main_class.Success("Success");
    // main_class.Warning("Warning");
    return 0;
}