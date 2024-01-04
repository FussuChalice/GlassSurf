// windows/process_detector.cpp

#include "process_detector.h"

void ListProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: CreateToolhelp32Snapshot failed." << std::endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Error: Process32First failed." << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        std::cout << "Process ID: " << pe32.th32ProcessID << std::endl;
        std::cout << "Executable File: " << pe32.szExeFile << std::endl;
        std::cout << "----------------------------------" << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

DWORD FindProcessIdByExecutable(const std::string& executableName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (_stricmp(processEntry.szExeFile, executableName.c_str()) == 0) {
                CloseHandle(snapshot);
                return processEntry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return 0;
}

HWND FindWindowByProcessId(DWORD processId) {
    HWND targetWindow = NULL;

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD windowProcessId;
        GetWindowThreadProcessId(hwnd, &windowProcessId);

        if (windowProcessId == static_cast<DWORD>(lParam)) {
            *reinterpret_cast<HWND*>(lParam) = hwnd;
            return FALSE;
        }

        return TRUE;
        }, reinterpret_cast<LPARAM>(&targetWindow));

    return targetWindow;
}

WINDOW FindWindowInfoByHWND(HWND hwnd) {
    WINDOW windowInfo = { 0 };

    DWORD windowProcessId;
    GetWindowThreadProcessId(hwnd, &windowProcessId);

    if (windowProcessId != 0) {
        RECT windowRect;
        GetWindowRect(hwnd, &windowRect);

        windowInfo.processId = windowProcessId;
        windowInfo.width = windowRect.right - windowRect.left;
        windowInfo.height = windowRect.bottom - windowRect.top;
        windowInfo.position_x = windowRect.left;
        windowInfo.position_y = windowRect.top;
    }

    return windowInfo;
}