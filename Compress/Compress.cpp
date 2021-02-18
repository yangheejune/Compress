#include "pch.h"
#include "Compress.h"
#include "../zip/unzip.h"
#include "../zip/zip.h"

std::vector<std::string>  Compress::get_files_inDirectory(const std::string& _path, const std::string& _filter)
{
    std::string searching = _path + _filter;

    std::vector<std::string> return_;

    _finddata_t fd;
    long handle = _findfirst(searching.c_str(), &fd);   // 현재 폴더 내 모든 파일을 찾는다.

    if (handle == -1)
        return return_;

    int result = 0;
    do
    {
        return_.push_back(fd.name);
        result = _findnext(handle, &fd);
    } while (result != -1);

    _findclose(handle);

    return return_;
}

std::string Compress::convLPCWSTRtoString(LPCWSTR wString)
{
    long size = wcslen(wString) + 1;
    char* cString = new char[size];
    for (long i = 0; i < size; i++)
    {
        cString[i] = wString[i];
    }
    std::string String(cString);
    return String;
}

DWORD Compress::CompressFile(LPCWSTR lpSourceFile, LPCWSTR lpTargetPath) {
    HZIP hz;
    ZRESULT zr = ZR_OK;

    // 디렉토리 안에 있는 파일 리스트 획득
    std::vector<std::string> fileLists = get_files_inDirectory(convLPCWSTRtoString(lpSourceFile), "*");
    hz = CreateZip(lpTargetPath, 0);
    
    for (int cnt = 0; cnt < fileLists.size(); cnt++)
    {
        if (fileLists.at(cnt).empty())
            break;
        else
        {
            std::wstring FullPath(lpSourceFile);
            TCHAR* param = new TCHAR[fileLists.at(cnt).size() + 1];
            param[fileLists.at(cnt).size()] = 0;
            std::copy(fileLists.at(cnt).begin(), fileLists.at(cnt).end(), param);
            if (wcscmp(param, L".") == 0 || wcscmp(param, L"..") == 0)
            {
                wprintf(L"%s exclude\n", param);
            }
            else {
                FullPath += param;
                ZipAdd(hz, param, (wchar_t *)FullPath.c_str());
            }

            delete [] param;
        }
    }

    CloseZip(hz);

    return zr;

}

DWORD Compress::ExtractFile(LPCWSTR lpSourceFile, LPCWSTR lpTargetPath) {
    HZIP hz;
    ZRESULT zr = ZR_OK;

    hz = OpenZip(lpSourceFile, 0);
    if (hz == 0)
    {
        return GetLastError();
    }

    zr = SetUnzipBaseDir(hz, lpTargetPath);
    if (ZR_OK != zr) {
        CloseZip(hz);
        return zr;
    }

    ZIPENTRY ze;
    zr = GetZipItem(hz, -1, &ze);
    if (ZR_OK != zr) { // -1은 zip 파일에 대한 전체적인 정보를 의미
        CloseZip(hz);
        return zr;
    }

    int numitems = ze.index;
    for (int zi = 0; zi < numitems; zi++)
    {
        ZIPENTRY ze;
        GetZipItem(hz, zi, &ze); // 압축 파일 내의 각각의 파일(아이템)에 대한 정보 가져오기
        UnzipItem(hz, zi, ze.name); // 각 아이템에 대한 압축 풀기
    }

    CloseZip(hz);

    return zr;
}