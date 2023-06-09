#include <iostream>
#include <cstdio>
#include <string>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    cout << "Linux" << endl;
#elif __FreeBSD__
    cout << "FreeBSD" << endl;
#elif __APPLE__
    cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

using namespace std;




namespace AppInstaller {

    class Installer
    {
        public:
            // Переменные
            bool Install;
            string OS_NAME;
            string Answer;
            string new_sentence;
            const string TrueVarious[6] = {"yes","y","1","Да","ДА","да"};
            // const string FalseVarious[] = {};

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
                InstallVNCServer();
                InstallVNCViewer();
            }
            void JavaScriptDevelopment() {
                InstallGit();
                InstallNodeJS();
                InstallWebStorm();
                InstallSublimeText();
                InstallVSCode();
                InstallPostman();
                InstallPostgresql();
                InstallPostman();
                InstallMongoDB();
                InstallMongoDBAtlas();
                InstallMongoDBCompass();
                InstallVNCServer();
                InstallVNCViewer();
                InstallDocker();
            }
            void RustDevelopment() {
                InstallGit();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void RubyDevelopment() {
                InstallGit();
                InstallRubyMine();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void CppDevelopment() {
                InstallGit();
                InstallCLion();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void CSDevelopment() {
                InstallGit();
                InstallRider();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void CDevelopment() {
                InstallGit();
                InstallCLion();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void GoDevelopment() {
                InstallGit();
                InstallGoLand();
                InstallSublimeText();
                InstallVSCode();
                InstallPostgresql();
                InstallPostman();
                InstallMongoDB();
                InstallMongoDBAtlas();
                InstallMongoDBCompass();
                InstallVNCServer();
                InstallVNCViewer();
                InstallDocker();
            }
            void JavaDevelopment() {
                InstallGit();
                InstallIntelliJCommunity();
                InstallIntelliJUltimate();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
            }
            void PHPDevelopment() {
                InstallGit();
                InstallPhpStorm();
                InstallSublimeText();
                InstallVSCode();
                InstallDocker();
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
            void InstallWebStorm() {
                cout << "Do you want to install JetBrains WebStorm?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.WebStorm");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
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
                cout << "Do you want to install Postman?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Postman.Postman");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallRubyMine() {
                cout << "Do you want to install JetBrains RubyMine?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.RubyMine");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallAqua() {
                cout << "Do you want to install JetBrains Aqua?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.Aqua.EAP");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallCLion() {
                cout << "Do you want to install JetBrains CLion?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.CLion");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallDataGrip() {
                cout << "Do you want to install JetBrains DataGrip?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.DataGrip");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallDataSpell() {
                cout << "Do you want to install JetBrains DataSpell?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.DataSpell");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallFleet() {
                cout << "Do you want to install JetBrains Fleet?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.FleetLauncher.Preview");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallGoLand() {
                cout << "Do you want to install JetBrains GoLand?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.GoLand");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallIntelliJCommunity() {
                cout << "Do you want to install JetBrains IntelliJIDEA Community?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.IntelliJIDEA.Community");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallIntelliJUltimate() {
                cout << "Do you want to install JetBrains IntelliJIDEA Ultimate?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallReSharper() {
                cout << "Do you want to install JetBrains ReSharper?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.ReSharper");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallRider() {
                cout << "Do you want to install JetBrains Rider?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.Rider");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPhpStorm() {
                cout << "Do you want to install JetBrains PHPStorm?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.PHPStorm");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstalldotUltimate() {
                cout << "Do you want to install JetBrains dotUltimate?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.dotUltimate");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallSpace() {
                cout << "Do you want to install JetBrains Space?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.Space");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallToolBox() {
                cout << "Do you want to install JetBrains Toolbox?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.Toolbox");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPostgresql() {
                cout << "Do you want to install PostgreSQL?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id PostgreSQL.PostgreSQL");
                        system("winget install -e --id PostgreSQL.pgAdmin");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallCLink() {
                cout << "Do you want to install Clink?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id chrisant996.Clink");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallNgrok() {
                cout << "Do you want to install Ngrok?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Ngrok.Ngrok");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallWget() {
                cout << "Do you want to install Wget?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JernejSimoncic.Wget");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallSublimeText() {
                cout << "Do you want to install SublimeText?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id SublimeHQ.SublimeText.4");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPyCharmCommunity() {
                cout << "Do you want to install PyCharm Community?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.PyCharm.Community");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPyCharmProffessional() {
                cout << "Do you want to install PyCharm Professional?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id JetBrains.PyCharm.Professional");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPowerToys() {
                cout << "Do you want to install Microsoft PowerToys?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Microsoft.PowerToys");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallDiscord() {
                cout << "Do you want to install Discord?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Discord.Discord");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallTelegram() {
                cout << "Do you want to install Telegram?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Telegram.TelegramDesktop");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallVNCServer() {
                cout << "Do you want to install RealVNC Server?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id RealVNC.VNCServer");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallVNCViewer() {
                cout << "Do you want to install RealVNC Viewer?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id RealVNC.VNCViewer");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallMongoDBCompass() {
                cout << "Do you want to install MongoDB Compass?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id MongoDB.Compass.Full");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallMongoDB() {
                cout << "Do you want to install MongoDB Server?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id MongoDB.Server");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallMongoDBAtlas() {
                cout << "Do you want to install MongoDB MongoDBAtlasCLI?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id MongoDB.MongoDBAtlasCLI");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallNodeJS() {
                cout << "Do you want to install NodeJS?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id OpenJS.NodeJS");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallGoLang() {
                cout << "Do you want to install GoLang?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id GoLang.Go.1.18");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPython3_9() {
                cout << "Do you want to install Python 3.9?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Python.Python.3.9");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPython3_10() {
                cout << "Do you want to install Python 3.10?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Python.Python.3.10");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallPython3_11() {
                cout << "Do you want to install Python 3.11?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Python.Python.3.11");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallJDK_19() {
                cout << "Do you want to install JDK 19?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Oracle.JDK.19");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallJDK_18() {
                cout << "Do you want to install JDK 18?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Oracle.JDK.18");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallRust() {
                cout << "Do you want to install Rust?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Rustlang.Rust.MSVC");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallNetFramework() {
                cout << "Do you want to install Microsoft DotNet Framework?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Microsoft.DotNet.Framework.DeveloperPack_4");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallRuby() {
                cout << "Do you want to install Ruby?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id RubyInstallerTeam.Ruby.3.1");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallMSYS2() {
                cout << "Do you want to install MSYS2?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id MSYS2.MSYS2");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallNuget() {
                cout << "Do you want to install Microsoft NuGet?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id Microsoft.NuGet");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallGitHubDesktop() {
                cout << "Do you want to install GitHub Desktop?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id GitHub.GitHubDesktop");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
            }
            void InstallGitHubCLi() {
                cout << "Do you want to install GitHub CLI?(default yes)";
                getline(cin,Answer);
                Install = CheckAnswer(Answer);
                if (Install == true) {
                    if (OS_NAME == "Windows") {
                        system("winget install -e --id GitHub.cli");
                    }
                    else if (OS_NAME == "macOS") {

                    }
                    else if (OS_NAME == "Linux") {
                        
                    }
                }
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
    // Installer::Installer()
    // {
    // }
    
    // Installer::~Installer()
    // {
    // }
    
}