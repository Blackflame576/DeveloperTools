// #include "Logger.hpp"
#include "AppInstaller_Windows.hpp"
#include <iostream>

using namespace std;
// using namespace Json;
// using namespace Logger;

namespace Windows {
    class AppInstaller {
        public:
            void InstallGit() {
                cout << translate["InstallGit"].asString() << endl;
                system("winget install --id Git.Git -e --source winget");
                cout << translate["InstalledGit"].asString() << endl;
            }

            void InstallVSCode() {
                cout << translate["InstallVSCode"].asString() << endl;
                system("winget install -e --id Microsoft.VisualStudioCode");
                cout << translate["InstalledVSCode"] << endl;
            }

            void InstallWebStorm() {
                cout << translate["InstallWebStorm"].asString() << endl;
                system("winget install -e --id JetBrains.WebStorm");
                cout << translate["InstalledWebStorm"].asString() << endl;
            }

            void InstallDocker() {
                cout << translate["InstallDocker"].asString() << endl;
                system("winget install -e --id Docker.DockerDesktop");
                cout << translate["InstalledDocker"].asString() << endl;
            }

            void InstallPostman() {
                cout << translate["InstallPostman"].asString() << endl;
                system("winget install -e --id Postman.Postman");
                cout << translate["InstalledPostman"].asString() << endl;
            }

            void InstallRubyMine() {
                cout << translate["InstallRubyMine"].asString() << endl;
                system("winget install -e --id JetBrains.RubyMine");
                cout << translate["InstalledRubyMine"].asString() << endl;
            }

            void InstallCLion() {
                cout << translate["InstallCLion"].asString() << endl;
                system("winget install -e --id JetBrains.CLion");
                cout << translate["InstalledCLion"].asString() << endl;
            }

            void InstallDataGrip() {
                cout << translate["InstallDataGrip"].asString() << endl;
                system("winget install -e --id JetBrains.DataGrip");
                cout << translate["InstalledDataGrip"].asString() << endl;
            }

            void InstallDataSpell() {
                cout << translate["InstallDataSpell"].asString() << endl;
                system("winget install -e --id JetBrains.DataSpell");
                cout << translate["InstalledDataSpell"].asString() << endl;
            }

            void InstallGoLand() {
                cout << translate["InstallGoLand"].asString() << endl;
                system("winget install -e --id JetBrains.GoLand");
                cout << translate["InstalledGoLand"].asString() << endl;
            }

            void InstallIntelliJCommunity() {
                cout << translate["InstallIntelliJIDEA Community"].asString() << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Community");
                cout << translate["InstalledIntelliJIDEA Community"].asString() << endl;
            }

            void InstallIntelliJUltimate() {
                cout << translate["InstallIntelliJIDEA Ultimate"].asString() << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
                cout << translate["InstalledIntelliJIDEA Ultimate"].asString() << endl;
            }

            void InstallRider() {
                cout << translate["InstallRider"].asString() << endl;
                    system("winget install -e --id JetBrains.Rider");
                    cout << translate["InstalledRider"].asString() << endl;
            }

            void InstallPhpStorm() {
                cout << translate["InstallPHPStorm"].asString() << endl;
                system("winget install -e --id JetBrains.PHPStorm");
                cout << translate["InstalledPHPStorm"].asString() << endl;
            }

            void InstallSpace() {
                cout << translate["InstallSpace"].asString() << endl;
                system("winget install -e --id JetBrains.Space");
                cout << translate["InstalledSpace"].asString() << endl;
            }


        private:
    };

    string to_lower(string sentence)
    {
        string new_sentence = "";
        for(int i = 0;i < sentence.length();i++) {
            char ch = sentence[i];
            // cout << ch << endl;
            ch = tolower(ch);
            new_sentence += ch;
        }
        return new_sentence;
    }

    bool CheckAnswer(string answer)
    {
        bool status;
        // string Answer = to_lower(answer);

        string Answer = answer;
        for (int i = 0; i < TrueVarious->size(); i++) {
            if (Answer == TrueVarious[i] || Answer.empty() || Answer == "\n" || Answer == "да" || Answer == "ДА" || Answer == "Да") {
                status = true;
                break;
            }
        }
        return status;
    }
    size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }
    int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        // ensure that the file to be downloaded is not empty
        // because that would cause a division by zero error later on
        if (TotalToDownload <= 0.0) {
            return 0;
        }

        int percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != percentage && TempPercentage <= 100) {
            bar.update();
            TempPercentage = percentage;
        }
        return 0;
    }
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

    // typedef void (AppInstaller::*funct_t)(void);
    // typedef std::map<std::string, funct_t> AppInstaller_func_map_t;
    // AppInstaller_func_map_t Packages = {
    //     {"Git",&AppInstaller::InstallGit}
    // };
    // map<string, function<void()>> Packages = {
    //     {"Git",[&installer](){installer.InstallGit();}}
    // };
    using AppInstaller_funct_t = void(AppInstaller::*)(void);
    map<string,AppInstaller_funct_t> Packages = {
        {"Git",AppInstaller::InstallGit}
    };
}