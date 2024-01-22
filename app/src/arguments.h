// arguments.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <argparse/argparse.hpp>

namespace glass_surf::arguments {
        void RegistryArguments(argparse::ArgumentParser& argv_parser);

} // namespace glass_surf::arguments


#endif // !ARGUMENTS_H_