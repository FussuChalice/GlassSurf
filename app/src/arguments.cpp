// arguments.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "arguments.h"

void glass_surf::arguments::RegistryArguments(argparse::ArgumentParser &argv_parser) {
    argv_parser.add_argument("-c", "--config").help("Path to config (SETTINGS) file");
}
