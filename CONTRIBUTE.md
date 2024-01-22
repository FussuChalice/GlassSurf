# Contribute Guidelines

Welcome to the GlassSurf repository! We're thrilled that you're interested in contributing to our project. Before you get started, please take a moment to review the following guidelines to ensure a smooth contribution process.

## Getting Started

### 1. Fork the Repository

To contribute to GlassSurf, you need to fork the repository to your GitHub account. Click the "Fork" button on the top right of this repository page.

### 2. Clone Your Fork

After forking, clone your fork to your local machine:

```bash
git clone https://github.com/YourUsername/GlassSurf.git
cd GlassSurf
```

### 3. Set Up Upstream

Set up an upstream remote to keep your fork synced with the main repository:

```bash
git remote add upstream https://github.com/FussuChalice/GlassSurf.git
```

Now, you can fetch the changes from the main repository:

```bash
git fetch upstream
```

### 4. Build and Install Dependencies

Use [Conan](https://conan.io/) and [CMake](https://cmake.org/).

## Code Style

- For C++ code, adhere to the [Chromium C++ Code Style](https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/c++/c++.md).
- If you are writing extensions for browsers, use the [Chromium Web Code Style](https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/web/web.md).

## File headers

All files in GlassSurf start with a common license header. That header should look like this:

```CXX
// $LOCAL_PATH_TO_FILE
// -----------------------------------------------------
// Copyright $YEAR The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.
```

For instance `$LOCAL_PATH_TO_FILE` is `windows/process_detector.cpp`

## Commit Message Convention

We follow a specific commit message convention to maintain a clear and organized version history. Please use the following tags at the beginning of your commit messages:

- `[FEATURE]`: A new feature has been added.
- `[FIX]`: A bug or issue has been fixed.
- `[UPDATE]`: Code or dependencies have been updated.
- `[REFACTOR]`: Code has been refactored without changing its functionality.
- `[OPTIMIZATION]`: Code has been optimized for better performance.
- `[DOCUMENTATION]`: Changes or additions to documentation.
- `[TEST]`: Adding or modifying tests.
- `[STYLE]`: Code style changes (e.g., formatting, indentation).
- `[CLEANUP]`: Removal of unnecessary code or files.
- `[CHORE]`: Routine tasks, maintenance, or miscellaneous changes.

When making a commit, use these tags at the beginning of your commit message to provide a quick overview of the nature of the changes. For example:

```bash
git commit -m "[FEATURE] Add new authentication module"
```

This helps maintain a clear and organized commit history.

## Submitting Changes

1. Create a new branch for your feature or bug fix:

   ```bash
   git checkout -b feature
   ```

2. Make your changes and ensure that the code follows the established code style.
3. Write tests for your changes, if applicable.
4. Ensure that your changes do not break existing functionality.
5. Commit your changes with a clear and concise commit message:

   ```bash
   git commit -m "Your concise commit message"
   ```

6. Push your branch to your fork:

   ```bash
   git push origin feature
   ```

7. Submit a pull request from your branch to the main repository.

## Code of Conduct

Please note that we have a [Code of Conduct](CODE_OF_CONDUCT.md) in place. Make sure to follow it in all your interactions with the project.

Thank you for contributing to GlassSurf! We appreciate your time and effort in making this project even better.
