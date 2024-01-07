// main.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#define __PROGRAM_NAME__ "GlassSurf"
#define __PROGRAM_VERSION__ "0"

#include "win/window_utilities.h"

int main(int argc, char const *argv[])
{
	HWND hwnd = FindWindowHandleByTitleSubstring("Google Chrome");

	WINDOW_INFO window_info = FindWindowInfoByHWND(hwnd);

	std::cout << "Width: " << window_info.width << std::endl;
	std::cout << "Height: " << window_info.height << std::endl;
	std::cout << "X: " << window_info.position_x << std::endl;
	std::cout << "Y: " << window_info.position_y << std::endl;


	return 0;
}