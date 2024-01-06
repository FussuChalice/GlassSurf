// image_utilities.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef IMAGE_UTILITIES_H_
#define IMAGE_UTILITIES_H_

#include <Windows.h>
#include <vector>

#include <iostream>
#include <cstring>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

/**
 * @brief Retrieves the path to the desktop wallpaper.
 *
 * @return A wide string containing the path to the desktop wallpaper.
 *         An empty string is returned if there is an error.
 */
std::wstring GetDesktopWallpaperPath();

/**
 * @brief Reads an image from a file and converts it into a vector of pixel values.
 *
 * @param filePath The path to the image file.
 * @return A vector of cv::Vec3b containing pixel values.
 *         An empty vector is returned if there is an error reading the image.
 */
std::vector<cv::Vec3b> ReadImage(const std::string& filePath);

/**
 * @brief Cuts a region from an image defined by specified parameters.
 *
 * @param image The input image represented as a 1D vector of cv::Vec3b.
 * @param image_width The width of the input image.
 * @param cut_width The width of the region to cut.
 * @param cut_height The height of the region to cut.
 * @param start_pos_x The x-coordinate of the starting position for the cut.
 * @param start_pos_y The y-coordinate of the starting position for the cut.
 * @return A vector of cv::Vec3b containing pixel values of the cut region.
 */
std::vector<cv::Vec3b> CutImage(
	const std::vector<cv::Vec3b>& image, 
	int image_width, 
	int cut_width, 
	int cut_height, 
	int start_pos_x, 
	int start_pos_y);

/**
 * @brief Applies Gaussian blur to an image represented as a vector of pixel values.
 *
 * @param image The input image represented as a 1D vector of cv::Vec3b.
 * @param width The width of the input image.
 * @param height The height of the input image.
 * @param radius The standard deviation of the Gaussian kernel for blurring.
 * @return A vector of cv::Vec3b containing pixel values of the blurred image.
 */
std::vector<cv::Vec3b> GaussianBlur(
	const std::vector<cv::Vec3b>& image,
	int width,
	int height,
	double radius);

/**
 * @brief Saves an image represented as a vector of pixel values to a PNG file.
 *
 * @param image The input image represented as a 1D vector of cv::Vec3b.
 * @param width The width of the input image.
 * @param height The height of the input image.
 * @param filename The name of the PNG file to save.
 */
void SaveAsPNG(
	const std::vector<cv::Vec3b>& image,
	int width,
	int height,
	const std::string& filename);

/**
 * @brief Allocates memory in DRAM and copies the image data.
 *
 * This function allocates memory in the Dynamic Random-Access Memory (DRAM) to store
 * an image and copies the pixel data from the provided vector to the allocated memory.
 * The caller is responsible for freeing the allocated memory using FreeDRAMImage
 * when it is no longer needed to avoid memory leaks.
 *
 * @param image The vector containing the pixel data of the image.
 * @param width The width of the image.
 * @param height The height of the image.
 * @return A pointer to the allocated memory containing the image data.
 */
cv::Vec3b* SaveAsPNGToDRAM(
	const std::vector<cv::Vec3b>& image, 
	int width, 
	int height);

/**
 * @brief Allocates memory in DRAM with a specified buffer size and copies the image data.
 *
 * This function allocates memory in the Dynamic Random-Access Memory (DRAM) to store
 * an image with additional buffer space and copies the pixel data from the provided vector
 * to the allocated memory. The caller is responsible for freeing the allocated memory using
 * FreeDRAMImage when it is no longer needed to avoid memory leaks.
 *
 * @param image The vector containing the pixel data of the image.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param buffer The additional buffer size to allocate beyond the required space.
 * @return A pointer to the allocated memory containing the image data with the buffer.
 */
cv::Vec3b* SaveAsPNGToDRAMWithBuffer(
	const std::vector<cv::Vec3b>& image, 
	int width, 
	int height, 
	int buffer);

/**
 * @brief Frees the memory allocated in DRAM for the image data.
 *
 * This function frees the memory previously allocated in the Dynamic Random-Access Memory (DRAM)
 * for storing image data. It is important to call this function when the allocated memory is
 * no longer needed to avoid memory leaks.
 *
 * @param dram_image A pointer to the memory allocated for image data in DRAM.
 */
void FreeDRAMImage(cv::Vec3b* dram_image);

#endif // !IMAGE_UTILITIES_H_