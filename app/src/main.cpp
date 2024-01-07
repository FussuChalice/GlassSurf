// main.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#define __PROGRAM_NAME__ "GlassSurf"
#define __PROGRAM_VERSION__ "0"

#include "windows/background_image.h"

#include <opencv2/opencv.hpp>

int main(int argc, char const* argv[]) {
      cv::Mat image = cv::imread("D:\\src\\GlassSurf\\app\\src\\background.jpg");

      // Проверка наличия изображения
      if (image.empty()) {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
      }

	return 0;
}

// D:\\src\\GlassSurf\\app\\src\\background.jpg