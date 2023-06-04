#include <curl/curl.h>
#include <iostream>
#include <cstdio>
using namespace std;

size_t WriteData(void* ptr,size_t size,size_t nmemb,FILE* stream) {
    size_t WriteProcess = fwrite(ptr,size,nmemb,stream);
    return WriteProcess;
}

class Main {
    public:
        void Download(string url,auto filename) {
            cout << typeid(url).name() << endl;
            CURL* curl = curl_easy_init();
            FILE* file = fopen(filename,"wb");
            curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteData);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
            CURLcode response = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        void CommandManager() {

        }
    private:
        void InstallBrew() {
            system("bash ./Scripts/InstallBrew.sh");
        }
        void InstallGit() {
            system("winget install --id Git.Git -e --source winget");
        }
        void InstallVSCode() {
            system("winget install -e --id Microsoft.VisualStudioCode");
        }
        void InstallDocker() {
            system("winget install -e --id Docker.DockerDesktop");
        }
        void InstallPostman() {
            system("winget install -e --id Postman.Postman");
        }
        void InstallPostgresql() {
            system("winget install -e --id PostgreSQL.PostgreSQL");
            system("winget install -e --id PostgreSQL.pgAdmin");
        }
        void InstallCLink() {
            system("winget install -e --id chrisant996.Clink");
        }
        void InstallNgrok() {
            system("winget install -e --id Ngrok.Ngrok");
        }
        void InstallWget() {
            system("winget install -e --id JernejSimoncic.Wget");
        }
        void InstallSublimeText() {
            system("winget install -e --id SublimeHQ.SublimeText.4");
        }
        void InstallPyCharmCommunity() {
            system("winget install -e --id JetBrains.PyCharm.Community");
        }
        void InstallPyCharmProffessional() {
            system("winget install -e --id JetBrains.PyCharm.Professional");
        }
        void InstallPowerToys() {
            system("winget install -e --id Microsoft.PowerToys");
        }
        void InstallDiscord() {
            system("winget install -e --id Discord.Discord");
        }
        void InstallTelegram() {
            system("winget install -e --id Telegram.TelegramDesktop");
        }
        void InstallVNCServer() {
            system("winget install -e --id RealVNC.VNCServer");
        }
        void InstallVNCViewer() {
            system("winget install -e --id RealVNC.VNCViewer");
        }
        void InstallMongoDBCompass() {
            system("winget install -e --id MongoDB.Compass.Full");
        }
        void InstallMongoDB() {
            system("winget install -e --id MongoDB.Server");
        }
        void InstallMongoDBAtlas() {
            system("winget install -e --id MongoDB.MongoDBAtlasCLI");
        }
        void InstallNodeJS() {
            system("winget install -e --id OpenJS.NodeJS");
        }
        void InstallGoLang() {
            system("winget install -e --id GoLang.Go.1.18");
        }
        void InstallPython3_9() {
            system("winget install -e --id Python.Python.3.9");
        }
        void InstallPython3_10() {
            system("winget install -e --id Python.Python.3.10");
        }
        void InstallPython3_11() {
            system("winget install -e --id Python.Python.3.11");
        }
        void InstallJDK_19() {
            system("winget install -e --id Oracle.JDK.19");
        }
        void InstallJDK_18() {
            system("winget install -e --id Oracle.JDK.18");
        }

};

int main() {
    Main main;
    string url;
    // cin >> url;
    // main.Download(url,"file.exe");
    system("winget install --id Git.Git -e --source winget");
    system("pause");
    return 0;
}