// main.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifdef _WIN32
#include "windows/window_utilities.h"
#include "windows/background_image.h"

#include <conio.h>
#endif

#include "settings/settings_manager.h"
#include "image_utilities.h"
#include "arguments.h"

#define __PROGRAM_NAME__ "GlassSurf"
#define __PROGRAM_VERSION__ "1.0.0 (Beta)"

const std::string default_config_file_name = "config.json";

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main(int argc, char const *argv[]) {

    // Argument Parsing
    argparse::ArgumentParser argv_parser(__PROGRAM_NAME__, __PROGRAM_VERSION__);
    glass_surf::arguments::RegistryArguments(argv_parser);

    try {
        argv_parser.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << argv_parser;
        std::exit(1);
    }

    // Set default config file path if not provided
    std::string config_file_path;
    if (argv_parser.get<std::string>("--config") == "") {
        config_file_path = default_config_file_name;
    }
    else {
        config_file_path = argv_parser.get<std::string>("--config");
    }

    // Read Settings file
    if (!fileExists(config_file_path)) {
        glass_surf::settings::Settings tmp_settings;
        glass_surf::settings::SaveSettingsFile(tmp_settings, config_file_path);
    }
    glass_surf::settings::Settings settings = glass_surf::settings::ReadSettingsFile(config_file_path);

    std::cout << "Configuration file loaded!" << std::endl;
    glass_surf::settings::PrintSettings(settings);

    #ifdef _WIN32

    // Read Desktop Background Image Path
    std::wstring desktop_background_image_path_wstring = glass_surf::win::GetDesktopWallPaperPath();
    std::string desktop_background_image_path_string = std::string(
        desktop_background_image_path_wstring.begin(), desktop_background_image_path_wstring.end());

    std::cout << "Desktop Background Image Path: " << desktop_background_image_path_string << std::endl;
    
    // Get Screen Resolution
    int screen_width, screen_height;
    glass_surf::win::GetDesktopResolution(screen_width, screen_height);

    std::cout << "Screen Resolution: " << screen_width << "x" << screen_height << std::endl;

    // Get HWND of Browser Window
    HWND browser_window = glass_surf::win::FindWindowHandleByTitleSubstring(settings.browser);

    // dbi - desktop background image
    cv::Mat dbi = glass_surf::ReadImage(desktop_background_image_path_string);
    cv::Mat dbi_with_compress = glass_surf::CompressImage(dbi, screen_width, screen_height);

    std::cout << "---";
    
    cv::Mat dbi_with_tint_blend = dbi_with_compress;
    if (settings.blendColor != "#000000") {
        glass_surf::RGB_Tint tint_color = glass_surf::HexStringToRGBTint(settings.blendColor);
        dbi_with_tint_blend = glass_surf::ApplyTintBlend(dbi_with_compress, tint_color);
    }

    cv::Mat dbi_with_blur = glass_surf::GausianBlur(dbi_with_tint_blend, settings.blurRadius);

    // Running ...
    glass_surf::win::WINDOW_INFO window_info = {0, 0, 0, 0, 0};
    cv::Mat result_image;
    while (true) {
        glass_surf::win::WINDOW_INFO tmp_browser_window_info = glass_surf::win::FindWindowInfoByHWND(browser_window);
        
        if (!glass_surf::win::CompareWindowInfo(window_info, tmp_browser_window_info)) {
            window_info = tmp_browser_window_info;

            std::cout << "Changed!" << std::endl;
        }

        std::cout << "\x1B[2J\x1B[H";


    }
    

    #endif // _WIN32

    return 0;
}
