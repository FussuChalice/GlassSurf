// settings/settings_manager.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef SETTINGS_MANAGER_H_
#define SETTINGS_MANAGER_H_

#include <nlohmann/json.hpp>
#include <fstream>

namespace glass_surf {
    namespace settings {
        /**
         * @brief Enum class representing different themes for the Glass Surf library.
         */
        enum class Themes {
            ACRYLIC,
            DARK,
            LIGHT,
        };

        /**
         * @brief Struct representing configurable settings for the Glass Surf library.
         */
        struct Settings {
            std::string browser = "Google Chrome";
            Themes theme = Themes::ACRYLIC;
            std::string blendColor = "#000000";
            double blurRadius = 25.0;
        };

        /**
         * @brief Save the provided settings to a JSON file.
         * @param settings The settings to be saved.
         * @param filename The name of the file to which settings will be saved.
         */
        void SaveSettingsFile(Settings settings, std::string filename);

        /**
         * @brief Read settings from a JSON file.
         * @param filename The name of the file from which settings will be read.
         * @return Settings read from the file.
         */
        Settings ReadSettingsFile(std::string filename);

        /**
         * @brief Prints the contents of a Settings structure.
         *
         * This function prints the values of a Settings structure, including browser,
         * theme, blend color, and blur radius, to the standard output (console).
         *
         * @param settings The Settings structure to be printed.
         *
         * @note The theme is printed as a string representation based on the Themes enum.
         * Additional cases can be added for different theme options.
         */
        void PrintSettings(const Settings& settings);

    } // namespace settings
} // namespace glass_surf

#endif // !SETTINGS_MANAGER_H_