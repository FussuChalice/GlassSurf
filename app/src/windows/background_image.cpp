// windows/background_image.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "background_image.h"

std::wstring glass_surf::win::GetDesktopWallPaperPath()
{
	winreg::RegKey reg_key{HKEY_CURRENT_USER, L"Control Panel\\Desktop"};

	std::wstring wallpaper_path = reg_key.GetStringValue(L"WallPaper");

	return wallpaper_path;
}

void glass_surf::win::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}
