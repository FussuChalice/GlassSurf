// windows/image_utilities.cpp

#include "image_utilities.h"

std::wstring GetDesktopWallpaperPath() 
{
    wchar_t wallpaperPath[MAX_PATH];

    if (SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, wallpaperPath, 0)) 
    {
        wallpaperPath[MAX_PATH - 1] = L'\0';  // Ensure null-termination
        return std::wstring(wallpaperPath);
    }
    else 
    {
        // Handle error (optional)
        std::cerr << "Error getting desktop wallpaper path." << std::endl;
        return L"";
    }
}


std::vector<cv::Vec3b> readImage(const std::string& filePath) {
    cv::Mat image = cv::imread(filePath);

    if (image.empty()) {
        std::cerr << "Error: Unable to read the image file " << filePath << std::endl;
        return std::vector<cv::Vec3b>();
    }

    cv::Mat reshapedImage = image.reshape(1, 1);

    std::vector<cv::Vec3b> pixelVector(reshapedImage.begin<cv::Vec3b>(), reshapedImage.end<cv::Vec3b>());

    return pixelVector;
}


std::vector<cv::Vec3b> cutImage(const std::vector<cv::Vec3b>&image, int image_width, int cut_width, int cut_height, int start_pos_x, int start_pos_y) 
{
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
    std::vector<cv::Vec3b> cutRegion;

    // Iterate over the specified region and copy the pixels to the cutRegion vector
    for (int y = start_pos_y; y < end_pos_y; ++y) {
        for (int x = start_pos_x; x < end_pos_x; ++x) {
            cutRegion.push_back(image[y * image_width + x]);
        }
    }

    return cutRegion;
}


std::vector<cv::Vec3b> gaussianBlur(const std::vector<cv::Vec3b>& image, int width, int height, double radius) {
    // Convert the 1D vector to a 3-channel (BGR) image
    cv::Mat inputImage(height, width, CV_8UC3);
    std::memcpy(inputImage.data, image.data(), image.size() * sizeof(cv::Vec3b));

    // Apply Gaussian blur
    cv::Mat blurredImage;
    cv::GaussianBlur(inputImage, blurredImage, cv::Size(0, 0), radius);

    // Convert the blurred image back to a 1D vector
    std::vector<cv::Vec3b> blurredVector(blurredImage.data, blurredImage.data + blurredImage.total() * blurredImage.channels());

    return blurredVector;
}


void saveAsPNG(const std::vector<cv::Vec3b>& image, int width, int height, const std::string& filename) {
    // Convert the 1D vector to a 3-channel (BGR) image
    cv::Mat outputImage(height, width, CV_8UC3);
    std::memcpy(outputImage.data, image.data(), image.size() * sizeof(cv::Vec3b));

    cv::imwrite(filename, outputImage);
}