#include "window_utilities.h"

// Map to associate descriptors with window handles
std::unordered_map<int, HWND> descriptorToWindowMap;

void ListAllWindowsWithDescriptors() {
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        int descriptor = static_cast<int>(lParam);
        descriptorToWindowMap[descriptor] = hwnd;

        int titleLength = GetWindowTextLength(hwnd) + 1;

        char* windowTitle = new char[titleLength];
        GetWindowTextA(hwnd, windowTitle, titleLength);

        std::cout << "Descriptor: " << descriptor << "\tWindow Handle: " << hwnd
            << "\tTitle: " << windowTitle << std::endl;

        delete[] windowTitle;

        lParam++;

        return TRUE;
        }, 1);
}

void ListWindowsWithTitleSubstring(const std::string& titleSubstring) {
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        // Get the length of the window title
        int titleLength = GetWindowTextLength(hwnd) + 1;

        // Allocate memory for the window title
        char* windowTitle = new char[titleLength];
        GetWindowTextA(hwnd, windowTitle, titleLength);

        // Check if the title contains the specified substring
        if (strstr(windowTitle, reinterpret_cast<const char*>(lParam)) != nullptr) {
            // Display information about the window
            std::cout << "Window Handle: " << hwnd << "\tTitle: " << windowTitle << std::endl;
        }
        // Free the allocated memory for the window title
        delete[] windowTitle;

        // Continue enumeration
        return TRUE;
        }, reinterpret_cast<LPARAM>(titleSubstring.c_str()));
}

HWND GetWindowHandleByTitle(const std::string& titleSubstring) {
    HWND foundWindow = nullptr;

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        // Get the length of the window title
        int titleLength = GetWindowTextLength(hwnd) + 1;

        // Allocate memory for the window title
        std::unique_ptr<char[]> windowTitle(new char[titleLength]);
        GetWindowTextA(hwnd, windowTitle.get(), titleLength);

        // Check if the title contains the specified substring
        if (strstr(windowTitle.get(), reinterpret_cast<const char*>(lParam)) != nullptr) {
            // Match found, set the window handle and stop enumeration
            *reinterpret_cast<HWND*>(lParam) = hwnd;
            return FALSE;
        }

        return TRUE;  // Continue enumeration
        }, reinterpret_cast<LPARAM>(&foundWindow));

    return foundWindow;
}

HWND global_window_handler;
void FindWindowHandleByTitleSubstring_(const std::string& titleSubstring) {
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        int titleLength = GetWindowTextLength(hwnd) + 1;

        char* windowTitle = new char[titleLength];
        GetWindowTextA(hwnd, windowTitle, titleLength);

        if (strstr(windowTitle, reinterpret_cast<const char*>(lParam)) != nullptr) {
            global_window_handler = hwnd;
        }
        delete[] windowTitle;

        return TRUE;
        }, reinterpret_cast<LPARAM>(titleSubstring.c_str()));
}

HWND FindWindowHandleByTitleSubstring(const std::string& titleSubstring) {
    FindWindowHandleByTitleSubstring_(titleSubstring);

    return global_window_handler;
}


void PrintWindowHandle(HWND hwnd) {
    std::cout << "Window Handle: " << hwnd << std::endl;
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

WINDOW_INFO FindWindowInfoByHWND(HWND hwnd) {
    WINDOW_INFO windowInfo = { 0 };

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