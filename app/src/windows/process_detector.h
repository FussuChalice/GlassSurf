// windows/process_detector.h

#ifndef PROCESS_DETECTOR_H_
#define PROCESS_DETECTOR_H_

#include "../pch.h"

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>


/**
 * @brief Lists all running processes and prints their process ID and executable filename.
 *
 * This function uses the Windows Toolhelp API to create a snapshot of the current
 * processes and iterates through the list, printing information about each process.
 */
void ListProcesses();

/**
 * @brief Finds the process ID of a given executable filename.
 *
 * @param executableName The name of the executable file to search for.
 * @return The process ID of the first matching process, or 0 if not found.
 *
 * This function uses the Windows Toolhelp API to create a snapshot of the current
 * processes and iterates through the list to find the process with the specified
 * executable filename.
 */
DWORD FindProcessIdByExecutable(const std::string& executableName);

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
 * @struct WINDOW
 * @brief Represents information about a window, including its process ID, dimensions, and position.
 *
 * The WINDOW structure is designed to store details about a window, making it convenient
 * to gather and manage information related to window properties.
 *
 * Members:
 * - processId: A DWORD representing the process ID associated with the window.
 * - width: An integer indicating the width of the window.
 * - height: An integer indicating the height of the window.
 * - position_x: An integer representing the x-coordinate of the window's position.
 * - position_y: An integer representing the y-coordinate of the window's position.
 */
struct WINDOW
{
	DWORD processId;
	int width, height;
	int position_x, position_y;
};

/**
 * @brief Retrieves information about a window using its handle.
 *
 * @param hwnd The handle of the window.
 * @return A WINDOW structure containing information about the window.
 *
 * This function extracts information about the specified window, including its process ID,
 * width, height, and position, and returns this information in a WINDOW structure.
 */
WINDOW FindWindowInfoByHWND(HWND hwnd);


#endif // !PROCESS_DETECTOR_H_
