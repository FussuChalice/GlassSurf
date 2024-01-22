// windows/window_utilities.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "window_utilities.h"

// Map to associate descriptors with window handles
std::unordered_map<int, HWND> descriptorToWindowMap;

void glass_surf::win::ListAllWindowsWithDescriptors() {
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

void glass_surf::win::ListWindowsWithTitleSubstring(const std::string& titleSubstring) {
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

HWND glass_surf::win::GetWindowHandleByTitle(const std::string& titleSubstring) {
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

HWND glass_surf::win::FindWindowHandleByTitleSubstring(const std::string& titleSubstring) {
    FindWindowHandleByTitleSubstring_(titleSubstring);

    return global_window_handler;
}


void glass_surf::win::PrintWindowHandle(HWND hwnd) {
    std::cout << "Window Handle: " << hwnd << std::endl;
}

HWND glass_surf::win::FindWindowByProcessId(DWORD processId) {
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

void glass_surf::win::PrintWindowInfo(const WINDOW_INFO &windowInfo) {
    std::cout << "Process ID: " << windowInfo.processId << std::endl;
    std::cout << "Width: " << windowInfo.width << std::endl;
    std::cout << "Height: " << windowInfo.height << std::endl;
    std::cout << "Position X: " << windowInfo.position_x << std::endl;
    std::cout << "Position Y: " << windowInfo.position_y << std::endl;
}

glass_surf::win::WINDOW_INFO glass_surf::win::FindWindowInfoByHWND(HWND hwnd) {
    glass_surf::win::WINDOW_INFO windowInfo = { 0, 0, 0, 0, 0};

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

// Very SLOW
// bool glass_surf::win::CompareWindowInfo(WINDOW_INFO &first_window_info, WINDOW_INFO &second_window_info) {
//     return (
//         first_window_info.processId == second_window_info.processId &&
//         first_window_info.width == second_window_info.width &&
//         first_window_info.height == second_window_info.height &&
//         first_window_info.position_x == second_window_info.position_x &&
//         first_window_info.position_y == second_window_info.position_y
//     );
// }

void glass_surf::win::HideConsole() {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void glass_surf::win::ShowConsole() {
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool glass_surf::win::IsConsoleVisible() {
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}
