// windows/process_detector.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef PROCESS_DETECTOR_H_
#define PROCESS_DETECTOR_H_

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

namespace glass_surf::win {

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
		 * @brief Finds process IDs associated with a specified executable file.
		 *
		 * This function uses the Windows Toolhelp API to create a snapshot of the current
		 * processes and iterates through the list to find process IDs associated with the
		 * specified executable file.
		 *
		 * @param executableName The name of the executable file to search for.
		 * @return A vector of DWORDs representing the process IDs associated with the specified executable.
		 *         If no processes are found or an error occurs, an empty vector is returned.
		 */
		std::vector<DWORD> FindProcessIdsByExecutable(const std::string& executableName);

} // namespace glass_surf::win

#endif // !PROCESS_DETECTOR_H_
