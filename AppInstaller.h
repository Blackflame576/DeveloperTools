#include <iostream>
#include <cstdio>
#include <string>

// �������� �������� ������������ ������� � ������������� ������ ��������� ��� ���� �������
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




namespace AppInstaller {

    class Installer
    {
        public:
            // ����������
            bool Install;
            string OS_NAME;
            string Answer;
            string new_sentence;
            const string TrueVarious[3] = {"yes","y","1"};

            // �������
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
            void PythonDevelopment() {
                InstallGit();
                InstallVSCode();
                InstallSublimeText();
                InstallPyCharmCommunity();
                InstallPyCharmProffessional();
                InstallDocker();
                InstallPython3_9();
                InstallPython3_10();
                InstallPython3_11();
                InstallPostgresql();
                InstallPostman();
                InstallMongoDB();
                InstallMongoDBAtlas();
                InstallMongoDBCompass();
            }
            void JavaScriptDevelopment() {

            }
            void RustDevelopment() {

            }
            void RubyDevelopment() {

            }
            void CppDevelopment() {

            }
            void CSDevelopment() {

            }
            void CDevelopment() {

            }
            void GoDevelopment() {

            }
            void JavaDevelopment() {

            }
            void InstallGit() {
                cout << "Do you want to install Git?(default yes):";
                // cin >> Answer;
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install --id Git.Git -e --source winget");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {

                    }
                }
            }
            void InstallVSCode() {
                cout << "Do you want to install VSCode?(default yes):";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    system("winget install -e --id Microsoft.VisualStudioCode");
                }
            }
            void InstallDocker() {
                cout << "Do you want to install Docker?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Docker.DockerDesktop");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
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
            void InstallRust() {
                system("winget install -e --id Rustlang.Rust.MSVC");
            }
            void InstallNetFramework() {
                system("winget install -e --id Microsoft.DotNet.Framework.DeveloperPack_4");
            }
            void InstallRuby() {
                system("winget install -e --id RubyInstallerTeam.Ruby.3.1");
            }
            void InstallMSYS2() {
                system("winget install -e --id MSYS2.MSYS2");
            }
            void InstallNuget() {
                system("winget install -e --id Microsoft.NuGet");
            }

            Installer() {
                #if defined(__linux__)
                    OS_NAME = "Linux";
                #elif __FreeBSD__
                    OS_NAME = "FreeBSD";
                #elif __APPLE__
                    OS_NAME = "macOS";
                #elif _WIN32
                    OS_NAME = "Windows";
                #endif
            };
            ~Installer() {

            };
        private:

    };
    // Installer::Installer(/* args */)
    // {
    // }
    
    // Installer::~Installer()
    // {
    // }
    
}