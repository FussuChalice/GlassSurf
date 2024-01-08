// image_utilities.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "image_utilities.h"

std::vector<cv::Vec3b> ReadImage(const std::string& file_path) {
    cv::Mat image = cv::imread(file_path);

    if (image.empty()) {
        std::cerr << "Error: Unable to read the image file " << file_path << std::endl;
        return std::vector<cv::Vec3b>();
    }

    cv::Mat reshaped_image = image.reshape(1, 1);

    std::vector<cv::Vec3b> pixel_vector(reshaped_image.begin<cv::Vec3b>(), reshaped_image.end<cv::Vec3b>());

    return pixel_vector;
}

std::vector<cv::Vec3b> CutImage(const std::vector<cv::Vec3b>& image, int image_width, int cut_width, int cut_height, int start_pos_x, int start_pos_y) {
    // Ensure start position is within the image boundaries
    if (start_pos_x < 0 || start_pos_y < 0 || start_pos_x >= image_width || start_pos_y >= image.size() / image_width) {
        // Handle invalid start position
        // You can throw an exception or return an empty vector based on your requirements
        // For simplicity, let's just return the original image
        return image;
    }

    // Calculate the end position of the cut region
    int end_pos_x = static_cast<int>(std::min(static_cast<long long>(start_pos_x) + cut_width, static_cast<long long>(image_width)));
    int end_pos_y = static_cast<int>(std::min(static_cast<long long>(start_pos_y) + cut_height, static_cast<long long>(image.size() / image_width)));

    // Initialize the vector for the cut region
    std::vector<cv::Vec3b> cut_region;

    // Iterate over the specified region and copy the pixels to the cut_region vector
    for (int y = start_pos_y; y < end_pos_y; ++y) {
        for (int x = start_pos_x; x < end_pos_x; ++x) {
            cut_region.push_back(image[y * image_width + x]);
        }
    }

    return cut_region;
}

std::vector<cv::Vec3b> GaussianBlur(const std::vector<cv::Vec3b>& image, int width, int height, double radius) {
    // Convert the 1D vector to a 3-channel (BGR) image
    cv::Mat input_image(height, width, CV_8UC3);
    std::memcpy(input_image.data, image.data(), image.size() * sizeof(cv::Vec3b));

    // Apply Gaussian blur
    cv::Mat blurred_image;
    cv::GaussianBlur(input_image, blurred_image, cv::Size(0, 0), radius);

    // Convert the blurred image back to a 1D vector
    std::vector<cv::Vec3b> blurred_vector(blurred_image.data, blurred_image.data + blurred_image.total() * blurred_image.channels());

    return blurred_vector;
}

void SaveAsPNG(const std::vector<cv::Vec3b>& image, int width, int height, const std::string& filename) {
    // Convert the 1D vector to a 3-channel (BGR) image
    cv::Mat output_image(height, width, CV_8UC3);
    std::memcpy(output_image.data, image.data(), image.size() * sizeof(cv::Vec3b));

    cv::imwrite(filename, output_image);
}

cv::Vec3b* SaveAsPNGToDRAM(const std::vector<cv::Vec3b>& image, int width, int height) {
    // Allocate memory for the image in DRAM
    cv::Vec3b* dram_image = new cv::Vec3b[width * height];
    
    // Copy the image data to the allocated memory
    std::memcpy(dram_image, image.data(), image.size() * sizeof(cv::Vec3b));
    
    return dram_image;
}

cv::Vec3b* SaveAsPNGToDRAMWithBuffer(const std::vector<cv::Vec3b>& image, int width, int height, int buffer) {
    // Allocate memory for the image in DRAM with buffer space
    cv::Vec3b* dram_image = new cv::Vec3b[(width + buffer) * height];
    
    // Copy the image data to the allocated memory
    std::memcpy(dram_image, image.data(), image.size() * sizeof(cv::Vec3b));

    // You can perform additional operations on dram_image if needed
    
    return dram_image;
}

void FreeDRAMImage(cv::Vec3b* dram_image) {
    delete[] dram_image;
}
