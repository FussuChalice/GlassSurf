// windows/background_image.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef BACKGROUND_IMAGE_H_
#define BACKGROUND_IMAGE_H_

#include <WinReg.hpp>
#include <iostream>

namespace glass_surf {
	namespace win {
		/**
		 * \brief Retrieves the path of the current desktop wallpaper.
		 *
		 * This function queries the Windows registry to obtain the path of the wallpaper
		 * currently set as the desktop background.
		 *
		 * \return A std::wstring containing the full path of the desktop wallpaper.
		 *
		 * \note This function relies on the Windows registry and might not work as expected
		 *       if the registry keys are modified or if the user doesn't have the necessary
		 *       permissions.
		 */
		std::wstring GetDesktopWallPaperPath();

		/**
		 * @brief Retrieves the resolution of the desktop screen.
		 *
		 * @param horizontal Reference to an integer where the horizontal resolution will be stored.
		 * @param vertical Reference to an integer where the vertical resolution will be stored.
		 *
		 * This function utilizes the Windows API to obtain the resolution of the desktop screen.
		 * It retrieves the dimensions (width and height) of the desktop and stores them in the
		 * specified references passed as parameters.
		 */
		void GetDesktopResolution(int& horizontal, int& vertical);
	}
}

#endif // !BACKGROUND_IMAGE_H_
