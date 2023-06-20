#include <iostream>
#include<Windows.h>
// #include<string>
#pragma comment(lib, "urlmon.lib")
#include "Progressbar.hpp"

using namespace std;
int TempPercentage = 0;
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
        
        // wcout << ulProgress << L" of " << ulProgressMax;
        int percentage = static_cast<float>(ulProgress) / static_cast<float>(ulProgressMax) * 100;
        // cout << percentage << endl;
        if (TempPercentage != percentage && TempPercentage <= 98) {
            bar.update();
            TempPercentage = percentage;
        }
        // if (szStatusText) wcout << " " << szStatusText;
        // wcout << endl;
        return S_OK;
    }
};
int main()
{
    
    
    string dwnld_URL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    string savepath = "kotlin.zip";
    DownloadProgress progress;
    HRESULT download = URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, static_cast<IBindStatusCallback*>(&progress));
    cout << "" << endl;
    cout << "filename.txt saved to current path.";
    return 0;
}