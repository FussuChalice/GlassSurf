// image_utilities.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef IMAGE_UTILITIES_H_
#define IMAGE_UTILITIES_H_

#include <vector>

#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <string>

#include <opencv2/opencv.hpp>

namespace glass_surf {

	/**
	 * @brief Reads an image from the specified file path.
	 *
	 * @param image_path The file path of the image to be read.
	 * @return A cv::Mat containing the read image.
	 */
	cv::Mat ReadImage(const std::string& image_path);

	/**
	 * @brief Displays an image in a resizable OpenCV window for preview.
	 *
	 * @param image The input image to be previewed.
	 * @param window_width The width of the preview window.
	 * @param window_height The height of the preview window.
	 */
	void PreviewImage(cv::Mat image, int window_width, int window_height);

	/**
	 * @brief Applies Gaussian blur to an input image.
	 *
	 * @param image The input image.
	 * @param radius The radius of the Gaussian blur.
	 * @return A cv::Mat containing the image with the applied Gaussian blur.
	 */
	cv::Mat GausianBlur(cv::Mat image, double Radius);

	/**
	 * @brief Calculates the luminosity of an input image using the formula: 0.299*R + 0.587*G + 0.114*B.
	 *
	 * @param image The input image.
	 * @return A cv::Mat containing the luminosity information of the image.
	 */
	cv::Mat CalculateLuminosity(cv::Mat& image);

	/**
	 * @brief Represents an RGB tint with individual color components.
	 *
	 * This struct is used to store the red, green, and blue color components of an RGB tint.
	 * Each component is an 8-bit unsigned integer (uchar) ranging from 0 to 255.
	 */
	struct RGB_Tint {
		uchar red;
		uchar green;
		uchar blue;
	};

	/**
	 * @brief Applies a tint to an input image using the specified RGB tint values.
	 *
	 * @param image The input image.
	 * @param rgb_tint An instance of the RGB_Tint struct containing tint values for red, green, and blue.
	 * @return A cv::Mat containing the tinted image.
	 */
	cv::Mat ApplyTintBlend(cv::Mat& image, RGB_Tint rgb_tint);

	/**
	 * @brief Converts a hex color string to an RGB_Tint struct.
	 *
	 * @param hexColor The input hex color string (e.g., "#RRGGBB").
	 * @return An instance of the RGB_Tint struct representing the RGB values of the hex color.
	 */
	RGB_Tint HexStringToRGBTint(const std::string& hexColor);

	/**
	 * @brief Crops a specified region from an input image.
	 *
	 * @param image The input image to be cropped.
	 * @param start_pos_x The starting x-coordinate of the cropping region.
	 * @param start_pos_y The starting y-coordinate of the cropping region.
	 * @param width The width of the cropping region.
	 * @param height The height of the cropping region.
	 * @return A cv::Mat containing the cropped region of the input image.
	 */
	cv::Mat CropImage(const cv::Mat& image, 
		int start_pos_x, int start_pos_y, int width, int height);

	/**
	 * @brief Resizes an input image to a new resolution.
	 *
	 * @param image The input image to be resized.
	 * @param newWidth The new width of the image.
	 * @param newHeight The new height of the image.
	 * @return A cv::Mat containing the resized image.
	 */
	cv::Mat CompressImage(const cv::Mat& image, int newWidth, int newHeight);
	
} // namespace glass_surf

#endif // !IMAGE_UTILITIES_H_