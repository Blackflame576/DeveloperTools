#include <iostream>
#include<string>
#pragma comment(lib, "urlmon.lib")
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"
#include <regex>
#include <fstream>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    // std::cout << "Linux" << endl;
#elif __FreeBSD__
    // std::cout << "FreeBSD" << endl;
#elif __APPLE__
    // std::cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

using namespace std;
using namespace InstallerDeveloperTools;

string GetNameDistribution() {
    if (OS_NAME == "Windows") {
        ifstream stream("/etc/os-release");
        string line;
        regex nameRegex("^NAME=\"(.*?)\"$");
        smatch match;
        string name;
        while (getline(stream,line)) {
            if (regex_search(line,match,nameRegex)) {
                name = match[1].str();
                break;
            }
        }
        return name;
    } 
}

class DownloadProgress : public IBindStatusCallback {
    public:
        HRESULT __stdcall QueryInterface(const IID &,void **) { 
            return E_NOINTERFACE;
        }
        ULONG STDMETHODCALLTYPE AddRef(void) { 
            return 1;
        }
        ULONG STDMETHODCALLTYPE Release(void) {
            return 1;
        }
        HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding *pib) {
            return E_NOTIMPL;
        }
        virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG *pnPriority) {
            return E_NOTIMPL;
        }
        virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) {
            return S_OK;
        }
        virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) {
            return E_NOTIMPL;
        }
        virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD *grfBINDF, BINDINFO *pbindinfo) {
            return E_NOTIMPL;
        }
        virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed) {
            return E_NOTIMPL;
        }        
        virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown *punk) {
            return E_NOTIMPL;
        }

        virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
        {
            
            int percentage = static_cast<float>(ulProgress) / static_cast<float>(ulProgressMax) * 100;
            // cout << percentage << endl;
            if (TempPercentage != percentage && TempPercentage <= 98) {
                // bar.update();
                cout << percentage << endl;
                TempPercentage = percentage;
            }
            return S_OK;
        }
};

class Installer {
    public:
        void InstallDeveloperTools() {
            string dwnld_URL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
            string savepath = "kotlin.zip";
            if (OS_NAME == "Windows") {
                DownloadProgress progress;
                HRESULT download = URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, static_cast<IBindStatusCallback*>(&progress));
                cout << "" << endl;
            }
            else if (OS_NAME == "macOS") {

            }
            else if (OS_NAME == "Linux") {

            }
        }
    private:
        // int Download(string url, string dir)
        // {
        //     try {
        //         string name = (url.substr(url.find_last_of("/")));
        //         string filename = dir + "/" + name.replace(name.find("/"), 1, "");
        //         CURL* curl = curl_easy_init();
        //         FILE* file = fopen(filename.c_str(), "wb");
        //         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //         curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
        //         curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_func);
        //         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        //         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        //         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        //         curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //         CURLcode response = curl_easy_perform(curl);
        //         curl_easy_cleanup(curl);
        //         fclose(file);
        //         cout << "" << endl;
        //         return 200;
        //     }
        //     catch (string error) {
        //         return 502;
        //     }
        // }
    // Installer();
    // ~Installer();
};

int main() {
    #if defined(__linux__)
        OS_NAME = "Linux";
        NameDistribution = GetNameDistribution();
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    Installer installer;
    installer.InstallDeveloperTools();
} 