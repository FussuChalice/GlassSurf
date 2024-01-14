// settings/settings_manager.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "settings_manager.h"

#include <iostream>

void glass_surf::settings::SaveSettingsFile(Settings settings, std::string filename) {
    nlohmann::json file_data;

    file_data["theme"] = settings.theme;
    file_data["blend_color"] = settings.blendColor;
    file_data["blur_radius"] = settings.blurRadius;
    file_data["browser"] = settings.browser;

    std::ofstream file(filename);
    file << file_data.dump() << std::endl;
    file.close();
}

glass_surf::settings::Settings glass_surf::settings::ReadSettingsFile(std::string filename) {
    Settings tmp_settings;

    std::ifstream file(filename);
    if (!file.is_open()) {
        // Handle file opening error
        std::cerr << "Error opening file: " << filename << std::endl;
        // You may throw an exception, return a default settings object, or handle it in another way
        // For simplicity, let's return an empty settings object
        return tmp_settings;
    }

    try {
        nlohmann::json json_data = nlohmann::json::parse(file);
        // Check if keys exist before accessing them
        if (json_data.contains("theme")) {
            tmp_settings.theme = json_data["theme"];
        }
        if (json_data.contains("blendColor")) {
            tmp_settings.blendColor = json_data["blendColor"];
        }
        if (json_data.contains("blurRadius")) {
            tmp_settings.blurRadius = json_data["blurRadius"];
        }
        if (json_data.contains("browser")) {
            tmp_settings.browser = json_data["browser"];
        }
    } catch (const nlohmann::json::exception& e) {
        // Handle JSON parsing error
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        // You may throw an exception, return a default settings object, or handle it in another way
        // For simplicity, let's return an empty settings object
        return tmp_settings;
    }

    return tmp_settings;
}

void glass_surf::settings::PrintSettings(const Settings &settings) {
    std::cout << "Browser: " << settings.browser << std::endl;
    std::cout << "Theme: ";
    
    switch (settings.theme) {
        case Themes::ACRYLIC:
            std::cout << "ACRYLIC";
            break;
        case Themes::DARK:
            std::cout << "DARK";
            break;
        case Themes::LIGHT:
            std::cout << "LIGHT";
            break;
        // Add other cases for different themes if needed
    }
    std::cout << std::endl;

    std::cout << "Blend Color: " << settings.blendColor << std::endl;
    std::cout << "Blur Radius: " << settings.blurRadius << std::endl;
}
