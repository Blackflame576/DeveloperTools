#include <filesystem>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#pragma comment(lib, "urlmon.lib")
#include "Progressbar.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace Windows
{
    int result;
    int Percentage;
    int TempPercentage = 0;
    string ProjectDir = std::filesystem::current_path().generic_string();
    const string UrlStableVersion;
    const string UrlBetaVersion;
    // const string DownloadURL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    // const string InstallPath = "kotlin-compiler-1.8.22.zip";
    string Answer;
    const string NewApplicationFolder = "C:\\ProgramData\\DeepForge\\DeepForge Toolset";
    ProgressBar progressbar;

    class WriteData : public IBindStatusCallback
    {
        public:
            HRESULT __stdcall QueryInterface(const IID &, void **)
            {
                return E_NOINTERFACE;
            }
            ULONG STDMETHODCALLTYPE AddRef(void)
            {
                return 1;
            }
            ULONG STDMETHODCALLTYPE Release(void)
            {
                return 1;
            }
            HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding *pib)
            {
                return E_NOTIMPL;
            }
            virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG *pnPriority)
            {
                return E_NOTIMPL;
            }
            virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved)
            {
                return S_OK;
            }
            virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError)
            {
                return E_NOTIMPL;
            }
            virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD *grfBINDF, BINDINFO *pbindinfo)
            {
                return E_NOTIMPL;
            }
            virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed)
            {
                return E_NOTIMPL;
            }
            virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown *punk)
            {
                return E_NOTIMPL;
            }

            virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
            {

                Percentage = static_cast<float>(ulProgress) / static_cast<float>(ulProgressMax) * 100;
                if (TempPercentage != Percentage && TempPercentage <= 98)
                {
                    progressbar.Update();
                    TempPercentage = Percentage;
                }
                return S_OK;
            }
    };
    // Main class 
    class Installer {
        public:
            void InstallStableVersion();
            void InstallBetaVersion();
            Installer() {
                // Changing the encoding in the Windows console
                system("chcp 65001");
            }
        private:
            int Download(string url,string dir) {
                WriteData writer;
                string name = (url.substr(url.find_last_of("/")));
                string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                HRESULT Download = URLDownloadToFile(NULL, url.c_str(), filename.c_str(), 0, static_cast<IBindStatusCallback *>(&writer));
                cout << "" << endl;
            }
    };
}