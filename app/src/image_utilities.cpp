// image_utilities.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "image_utilities.h"

cv::Mat glass_surf::ReadImage(const std::string& image_path) {
  cv::Mat uploaded_image = cv::imread(image_path);

  if (uploaded_image.empty()) {
    std::cerr << "[ERROR]: Uploading " << image_path << " failed!" << std::endl;
  }

  return uploaded_image;
}

void glass_surf::PreviewImage(cv::Mat image, int window_width, int window_height)
{
    cv::namedWindow("OpenCV Preview", cv::WINDOW_NORMAL);

    cv::resize(image, image, cv::Size(window_width, window_height));

    cv::imshow("OpenCV Preview", image);
    cv::waitKey(0);

    cv::destroyWindow("OpenCV Preview");
}

cv::Mat glass_surf::GausianBlur(cv::Mat image, double radius)
{
    cv::Mat image_with_effect;

    cv::GaussianBlur(image, image_with_effect, cv::Size(0, 0), radius);

    return image_with_effect;
}

cv::Mat glass_surf::CalculateLuminosity(cv::Mat& image)
{
    cv::Mat image_with_luminosity(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b intensity = image.at<cv::Vec3b>(i, j);

            // Calculate luminosity using the formula: 0.299*R + 0.587*G + 0.114*B
            uchar luminosity = static_cast<uchar>(0.299 * intensity[2] + 0.587 * intensity[1] + 0.114 * intensity[0]);

            image_with_luminosity.at<uchar>(i, j) = luminosity;
        }
    }

    return image_with_luminosity;
}

cv::Mat glass_surf::ApplyTintBlend(cv::Mat& image, RGB_Tint rgb_tint)
{
    cv::Mat tinted_image(image.rows, image.cols, CV_8UC3);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b intensity = image.at<cv::Vec3b>(i, j);

            // Apply tint by multiplying each channel with the corresponding tint value
            intensity[2] = static_cast<uchar>(intensity[2] * (rgb_tint.red / 255.0));
            intensity[1] = static_cast<uchar>(intensity[1] * (rgb_tint.green / 255.0));
            intensity[0] = static_cast<uchar>(intensity[0] * (rgb_tint.blue / 255.0));

            tinted_image.at<cv::Vec3b>(i, j) = intensity;
        }
    }

    return tinted_image;
}

glass_surf::RGB_Tint glass_surf::HexStringToRGBTint(const std::string& hexColor)
{
    glass_surf::RGB_Tint tint;

    if (hexColor.length() != 7 || hexColor[0] != '#') {
        std::cerr << "Error: Invalid hex color string." << std::endl;
        return RGB_Tint{ 0, 0, 0 };
    }

    std::istringstream stream(hexColor.substr(1));
    unsigned int colorValue;

    stream >> std::hex >> colorValue;
    tint.red = static_cast<uchar>(colorValue);

    stream >> std::hex >> colorValue;
    tint.green = static_cast<uchar>(colorValue);

    stream >> std::hex >> colorValue;
    tint.blue = static_cast<uchar>(colorValue);

    return tint;
}

cv::Mat glass_surf::CropImage(const cv::Mat& image, int start_pos_x, int start_pos_y, int width, int height) {
    // Ensure that the cropping region is within the image bounds
    int max_width = std::min(width, image.cols - start_pos_x);
    int max_height = std::min(height, image.rows - start_pos_y);

    // Create a Rect object representing the cropping region
    cv::Rect roi(start_pos_x, start_pos_y, max_width, max_height);

    // Crop the image using the region of interest (ROI)
    cv::Mat croppedImage = image(roi).clone();

    return croppedImage;
}

cv::Mat glass_surf::CompressImage(const cv::Mat& image, int newWidth, int newHeight) {

    if (image.empty()) {
        std::cerr << "Error: Input image is empty." << std::endl;
        return cv::Mat();
    }

    cv::Mat compressed_image;
    cv::resize(image, compressed_image, cv::Size(newWidth, newHeight));

    return compressed_image;
}