#include <iostream>
#include <map>
#include <filesystem>
#include <curl/curl.h>
// #include <sys/utsname.h>

using namespace std;
// using namespace zipper;
using funct_t = void(*)(void);
void InstallGit() {
    cout << "Git installer" << endl;
}
// map<string,funct_t> apps {
//     {"Git",InstallGit}
// };

size_t WriteData(void* ptr,size_t size,size_t nmemb,FILE* stream) {
    size_t WriteProcess = fwrite(ptr,size,nmemb,stream);
    return WriteProcess;
}
// int uname(struct utsname *buf);
// struct utsname 
// {
//        char sysname[];    /* Operating system name (e.g., "Linux") */
//        char nodename[];   /* Name within "some implementation-defined network" */
//        char release[];    /* OS release (e.g., "2.6.28") */
//        char version[];    /* OS version */
//        char machine[];    /* Hardware identifier */
//        #ifdef _GNU_SOURCE
//           char domainname[]; /* NIS or YP domain name */
//        #endif
// };
void Download(string url) {
    string name = (url.substr(url.find_last_of("/")));
    string filename = name.replace(name.find("/"),1,"");
    CURL* curl = curl_easy_init();
    FILE* file = fopen(filename.c_str(),"wb");
    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteData);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
    CURLcode response = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(file);
}
int main() {
    auto ProjectDir = std::filesystem::current_path();
    string path_string = ProjectDir.generic_string();
    // string KotlinDir = path_string + "/Programms/Kotlin";
    string NewKotlinDir = "C:\\Kotlin";
    std::filesystem::create_directory(NewKotlinDir);
    
    // cout << "Current Path:" << ProjectDir << endl;
    // cout << "Kotlin Path:" << KotlinDir << endl;
    // std::filesystem::copy(KotlinDir,NewKotlinDir,std::filesystem::copy_options::recursive);
    // system("copy " + KotlinDir + " " + NewKotlinDir);
    // apps["Git"]();
    
    // Download("https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip");
    // Unzipper unzipper("kotlin-compiler-1.8.22.zip");
    // unzipper.extract();
    // unzipper.close();
    string command = "tar -xf" + path_string +"/kotlin-compiler-1.8.22.zip " + "--directory " + NewKotlinDir;
    system(command.c_str());
    system("pause");
    return 0;
}