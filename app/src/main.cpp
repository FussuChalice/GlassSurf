// main.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#define __PROGRAM_NAME__ "GlassSurf"
#define __PROGRAM_VERSION__ "0"

#include "windows/background_image.h"

#include "image_utilities.h"

int main(int argc, char const* argv[]) {

	std::vector<cv::Vec3b> image =
      ReadImage("D:\\src\\GlassSurf\\app\\src\\background.jpg");



	return 0;
}

// D:\\src\\GlassSurf\\app\\src\\background.jpg