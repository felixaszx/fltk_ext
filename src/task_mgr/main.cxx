#include <print>
#include <filesystem>
#include <windows.h>
#include <psapi.h>

#include "fltk.hxx"
#include "fl_theme.hxx"

void PrintProcessNameAndID(DWORD processID)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    // Get the process name.

    if (nullptr != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        DWORD dwsize = MAX_PATH;

        if (QueryFullProcessImageName(hProcess, {}, szProcessName, &dwsize))
        {
            std::filesystem::path path = szProcessName;
            std::string path_str = path.filename().generic_string();
        }
    }

    CloseHandle(hProcess);
}

int //
main(int argc, char** argv)
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            PrintProcessNameAndID(aProcesses[i]);
        }
    }

    return 0;
}