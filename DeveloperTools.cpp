// Импортирование необходимых библиотек
#include <curl/curl.h>
#include <iostream>
#include <cstdio>
#include <string>
#include "AppInstaller.h"
// #include <cctype>
// #include <cstring>
// #include <fstream>
// #include <iterator>
// #include <algorithm>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    std::cout << "Linux" << endl;
#elif __FreeBSD__
    std::cout << "FreeBSD" << endl;
#elif __APPLE__
    std::cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

using namespace std;
using namespace AppInstaller;

// Переменные 
bool JavaDevelopment;
bool PythonDevelopment;
bool JavaScriptDevelopment;
bool RustDevelopment;
bool RubyDevelopment;
bool CppDevelopment;
bool CSDevelopment;
bool GoDevelopment;
bool Install;
string OS_NAME;
string Answer;
string new_sentence;
Installer installer;
const string TrueVarious[] = {"yes","y","1","Y","YES","Yes"};

size_t WriteData(void* ptr,size_t size,size_t nmemb,FILE* stream) {
    size_t WriteProcess = fwrite(ptr,size,nmemb,stream);
    return WriteProcess;
}

// Функции
string to_lower(string sentence) {
    new_sentence = "";
    for (int i = 0;i<sizeof(sentence);i++) {
        new_sentence += tolower(sentence[i]);
    }
    return new_sentence;
}

bool CheckAnswer(string answer) {
    bool status;
    // string Answer = to_lower(answer);
    string Answer = answer;
    for (int i = 0;i < TrueVarious->size();i++) {
        if (Answer == TrueVarious[i] || Answer.empty() || Answer == "\n") {
            status = true;
        }
        else {
            status = false;
        }
    }
    return status;
}

class Main {
    public:
        // void Download(string url,auto filename) {
        //     cout << typeid(url).name() << endl;
        //     CURL* curl = curl_easy_init();
        //     FILE* file = fopen(filename,"wb");
        //     curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
        //     curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteData);
        //     curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
        //     CURLcode response = curl_easy_perform(curl);
        //     curl_easy_cleanup(curl);
        // }
        void CommandManager() {
            string InstallTools;
            cout << "1. Choose a ready-made set of DevelopmentTools for a specific programming language" << endl;
            cout << "2. Manual selection of DeveloperTools tools" << endl;
            cout << "Select the option to install DeveloperTools (Default - 2):";
            getline(cin,InstallTools);
            if (InstallTools == "1") {
                ReadySet();
            }
            else if (InstallTools == "2" or InstallTools.empty()) {
                ManualSelection();
            }
            else {
                ManualSelection();
            }

        }
        void ManualSelection() {
            installer.InstallGit();
            installer.InstallVSCode();
            installer.InstallPyCharmCommunity();
            installer.InstallPyCharmProffessional();
            installer.InstallSublimeText();
            installer.InstallPython3_9();
            installer.InstallPython3_10();
            installer.InstallPython3_11();
            installer.InstallNodeJS();
            installer.InstallJDK_18();
            installer.InstallJDK_19();
            installer.InstallGoLang();
            installer.InstallRuby();
            installer.InstallRust();
            installer.InstallNetFramework();
            installer.InstallMSYS2();
            installer.InstallDocker();
            installer.InstallCLink();
            installer.InstallNgrok();
            installer.InstallNuget();
            installer.InstallPostgresql();
            installer.InstallPostman();
            installer.InstallWget();
            installer.InstallVNCServer();
            installer.InstallVNCViewer();
            installer.InstallMongoDB();
            installer.InstallMongoDBAtlas();
            installer.InstallMongoDBCompass();
            installer.InstallTelegram();
            installer.InstallDiscord();
        }
        void ReadySet() {

        }
    private:
        void InstallBrew() {
            system("bash ./Scripts/InstallBrew.sh");
        }
        
};

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_CTYPE,"Russian");
    #if defined(__linux__)
        OS_NAME = "Linux";
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
    #endif
    
    Main main;
    main.CommandManager();
    // string url;
    // cin >> url;
    // main.Download(url,"file.exe");
    system("pause");
    return 0;
}