#include <iostream>
#include "Progressbar.hpp"
#include <curl/curl.h>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    #include <curl/curl.h>
    // cout << "Linux" << endl;
#elif __FreeBSD__
    // cout << "FreeBSD" << endl;
#elif __APPLE__
    #include <curl/curl.h>
    // cout << "macOS" << endl;
#elif _WIN32
    #pragma comment(lib, "urlmon.lib")
    #include <winsock2.h>
    #include <Windows.h>
#endif

using namespace std;
int TempPercentage = 0;
progressbar bar(100);

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

#if defined(_WIN32) 
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
        
        // wcout << ulProgress << L" of " << ulProgressMax;
        int percentage = static_cast<float>(ulProgress) / static_cast<float>(ulProgressMax) * 100;
        // cout << percentage << endl;
        if (TempPercentage != percentage && TempPercentage <= 98) {
            // bar.update();
            cout << percentage << endl;
            TempPercentage = percentage;
        }
        // if (szStatusText) wcout << " " << szStatusText;
        // wcout << endl;
        return S_OK;
    }
};
#endif

class Installer {
    public:
        void InstallDeveloperTools() {

        }
    private:
        int Download(string url, string dir)
        {
            try {
                string name = (url.substr(url.find_last_of("/")));
                string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                CURL* curl = curl_easy_init();
                FILE* file = fopen(filename.c_str(), "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
                curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_func);
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
};

int main()
{
    Installer installer;
    string dwnld_URL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    string savepath = "kotlin.zip";
    DownloadProgress progress;
    HRESULT download = URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, static_cast<IBindStatusCallback*>(&progress));
    cout << "" << endl;
    cout << "filename.txt saved to current path.";
    return 0;
}