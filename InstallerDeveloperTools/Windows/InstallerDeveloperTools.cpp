#include <Windows.h>
#include <iostream>
#include "Progressbar.hpp"
#include "InstallerDeveloperTools.hpp"
#pragma comment(lib, "urlmon.lib")

using namespace std;
using namespace InstallerDeveloperTools;

progressbar bar(100);

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
        
        Percentage = static_cast<float>(ulProgress) / static_cast<float>(ulProgressMax) * 100;
        if (TempPercentage != Percentage && TempPercentage <= 98) {
            bar.update();
            TempPercentage = Percentage;
        }
        return S_OK;
    }
};

class Installer {
    public:
        void InstallDeveloperTools_Stable() {
            DownloadProgress Progress;
            HRESULT Download = URLDownloadToFile(NULL, DownloadURL.c_str(), InstallPath.c_str(), 0, static_cast<IBindStatusCallback*>(&Progress));
            cout << "" << endl;
        }
        void InstallDeveloperTools_Beta() {
            DownloadProgress Progress;
            HRESULT Download = URLDownloadToFile(NULL, BetaDownloadURL.c_str(), InstallPath.c_str(), 0, static_cast<IBindStatusCallback*>(&Progress));
            cout << "" << endl;
        }
    private:
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Installer installer;
    cout << "1. DeveloperTools Stable Version" << endl;
    cout << "2. DeveloperTools Beta Version" << endl;
    cout << "Выберите версию DeveloperTools:";
    getline(cin,Answer);
    if (Answer == "1") {
        installer.InstallDeveloperTools_Stable();
    }
    else if (Answer == "2") {
        installer.InstallDeveloperTools_Beta();
    }
    return 0;
}