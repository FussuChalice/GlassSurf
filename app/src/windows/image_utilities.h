// windows/image_utilities.h

#ifndef IMAGE_UTILITIES_H
#define IMAGE_UTILITIES_H

#include "pch.h"

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
std::vector<cv::Vec3b> readImage(const std::string& filePath);

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
std::vector<cv::Vec3b> cutImage(
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
std::vector<cv::Vec3b> gaussianBlur(
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
void saveAsPNG(
	const std::vector<cv::Vec3b>& image,
	int width,
	int height,
	const std::string& filename);


#endif // !IMAGE_UTILITIES_H