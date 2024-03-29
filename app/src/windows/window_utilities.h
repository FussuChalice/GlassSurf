// windows/window_utilities.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef WINDOW_UTILITIES_H_
#define WINDOW_UTILITIES_H_

#include <iostream>
#include <unordered_map>
#include <windows.h>

namespace glass_surf::win {
		/**
		 * @brief Lists all top-level windows, associating each window handle with a unique descriptor.
		 *
		 * The function uses the EnumWindows function to enumerate through all top-level windows.
		 * For each window, it associates a unique descriptor with its handle and displays information
		 * including the descriptor, window handle, and window title.
		 */
		void ListAllWindowsWithDescriptors();

		/**
		 * @brief Lists all top-level windows whose titles contain a specified substring.
		 *
		 * The function uses the EnumWindows function to enumerate through all top-level windows.
		 * For each window, it checks if the window title contains the specified substring.
		 * If a match is found, it displays information about the window.
		 *
		 * @param titleSubstring The substring to search for within window titles.
		 */
		void ListWindowsWithTitleSubstring(const std::string& titleSubstring);

		/**
		 * @brief Prints the window handle (HWND) of a specified window.
		 *
		 * The function directly prints the window handle of the specified window to the console.
		 *
		 * @param hwnd The window handle of the window to print.
		 */
		void PrintWindowHandle(HWND hwnd);

		/**
		 * @brief Finds a window handle by searching for a substring in its title.
		 *
		 * This function searches for a window with a title containing the specified substring.
		 * It utilizes the FindWindowHandleByTitleSubstring_ function internally to perform the search.
		 *
		 * @param titleSubstring The substring to search for in the window titles.
		 * @return The window handle of the first window with a title containing the specified substring.
		 *         If no matching window is found, the return value is NULL.
		 *
		 * @see FindWindowHandleByTitleSubstring_
		 */
		HWND FindWindowHandleByTitleSubstring(const std::string& titleSubstring);

		/**
		 * @brief Finds the window handle associated with a given process ID.
		 *
		 * @param processId The process ID to search for.
		 * @return The window handle of the first matching window, or NULL if not found.
		 *
		 * This function uses the EnumWindows function to iterate through all top-level windows
		 * and checks each window's associated process ID using GetWindowThreadProcessId. If a match
		 * is found, the window handle is returned.
		 */
		HWND FindWindowByProcessId(DWORD processId);

		/**
		 * @brief Retrieves the window handle by searching for a specified title substring.
		 *
		 * The function enumerates through all top-level windows and retrieves the window handle
		 * of the first window with a title containing the specified substring.
		 *
		 * @param titleSubstring The substring to search for within window titles.
		 * @return The window handle (HWND) of the first matching window. If no matching window is found, returns nullptr.
		 */
		HWND GetWindowHandleByTitle(const std::string& titleSubstring);

		/**
		* @struct WINDOW_INFO
		* @brief Represents information about a window, including its process ID, dimensions, and position.
		*
		* The WINDOW_INFO structure is designed to store details about a window, making it convenient
		* to gather and manage information related to window properties.
		*
		* Members:
		* - processId: A DWORD representing the process ID associated with the window.
		* - width: An integer indicating the width of the window.
		* - height: An integer indicating the height of the window.
		* - position_x: An integer representing the x-coordinate of the window's position.
		* - position_y: An integer representing the y-coordinate of the window's position.
		*/
		struct WINDOW_INFO
		{
			DWORD processId;
			int width, height;
			int position_x, position_y;
		};

		/**
		 * @brief Prints the contents of a WINDOW_INFO structure.
		 *
		 * This function prints the values of a WINDOW_INFO structure, including process ID,
		 * width, height, position X, and position Y, to the standard output (console).
		 *
		 * @param windowInfo The WINDOW_INFO structure to be printed.
		 *
		 */
		void PrintWindowInfo(const WINDOW_INFO& windowInfo);

		/**
		 * @brief Retrieves information about a window using its handle.
		 *
		 * @param hwnd The handle of the window.
		 * @return WINDOW_INFO structure containing information about the window.
		 *
		 * This function extracts information about the specified window, including its process ID,
		 * width, height, and position, and returns this information in a WINDOW_INFO structure.
		 */
		WINDOW_INFO FindWindowInfoByHWND(HWND hwnd);

		/**
		 * @brief Hides the console window.
		 * 
		 * This function hides the console window associated with the current
		 * process. It uses Windows API functions to achieve this.
		 * 
		 * @note This function has no effect if the application does not have a console window.
		 * 
		 * @see ShowConsole(), IsConsoleVisible()
		 */
		void HideConsole();

		/**
		 * @brief Shows the console window if hidden.
		 * 
		 * This function shows the console window associated with the current
		 * process if it is currently hidden. It uses Windows API functions to achieve this.
		 * 
		 * @note This function has no effect if the application does not have a console window.
		 * 
		 * @see HideConsole(), IsConsoleVisible()
		 */
		void ShowConsole();

		/**
		 * @brief Checks if the console window is currently visible.
		 * 
		 * This function checks whether the console window associated with the current
		 * process is currently visible.
		 * 
		 * @note This function returns false if the application does not have a console window.
		 * 
		 * @return True if the console window is visible, false otherwise.
		 * 
		 * @see HideConsole(), ShowConsole()
		 */
		bool IsConsoleVisible();

} // namespace glass_surf::win

#endif // !WINDOW_UTILITIES_H_
