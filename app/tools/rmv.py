# tools/rmv.py
# -----------------------------------------------------
# Copyright 2024 The GlassSurf Authors
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

"""
GlassSurf Directory Processor

This script is designed to process directories by copying files and subdirectories
from subdirectories with names matching a specific pattern to the base directory,
and then removing those subdirectories.

Usage:
    rmv.py -b/--base <base_path>

Arguments:
    -b, --base <base_path>
        The base directory path where the script will process subdirectories.

Example:
    To process subdirectories in the 'data' directory:
    $ python rmv.py --base data

Directory Processing Details:
1. Retrieves a list of subdirectories from the specified base directory.
2. For each subdirectory with a name matching the pattern '-[0-9]+':
    a. Copies all files and subdirectories from the matching subdirectory to the base directory.
    b. Removes the matching subdirectory.

Note:
- The script uses a regular expression to identify subdirectories with names
  matching the pattern '-[0-9]+'.
- After processing, the base directory will contain the files and subdirectories
  from the matching subdirectories, and those subdirectories will be removed.

Dependencies:
- Python 3.x

License:
This script is distributed under the terms of the MIT License. See the LICENSE
file for details.

"""

#! /usr/bin/env python

import argparse
import os
import shutil
import re

def get_directory_names(path):
    """
    Get a list of subdirectories in the specified path.

    Parameters:
        path (str): The path to the directory.

    Returns:
        list: A list of subdirectory names.
    """
    try:
        items = os.listdir(path)
        
        directories = [item for item in items if os.path.isdir(os.path.join(path, item))]
        
        return directories
    except OSError as e:
        print(f"Error: {e}")
        return []

def copy_files_and_dirs(source_dir, dest_dir):
    """
    Copy files and subdirectories from the source directory to the destination directory.

    Parameters:
        source_dir (str): The source directory path.
        dest_dir (str): The destination directory path.
    """
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    for root, dirs, files in os.walk(source_dir):
        for file in files:
            source_path = os.path.join(root, file)
            dest_path = os.path.join(dest_dir, os.path.relpath(source_path, source_dir))

            if not os.path.exists(os.path.dirname(dest_path)):
                os.makedirs(os.path.dirname(dest_path))

            shutil.copy2(source_path, dest_path)

    print("Copy operation completed.")

def remove_directory(directory_path):
    """
    Remove the specified directory.

    Parameters:
        directory_path (str): The path to the directory to be removed.
    """
    try:
        shutil.rmtree(directory_path, ignore_errors=True)
        print(f"Directory '{directory_path}' successfully removed.")
    except Exception as e:
        print(f"Error: {e}")

def process_folders(base_path):
    """
    Process subdirectories in the specified base directory based on a naming pattern.

    Parameters:
        base_path (str): The path to the base directory.
    """
    directories = get_directory_names(base_path)

    for dir in directories:
        if re.search(r'-[0-9]+', dir):
            print(dir)

            tmp_path = base_path + dir + "\\"
            print(tmp_path)

            copy_files_and_dirs(tmp_path, base_path)
            remove_directory(tmp_path)


if __name__ == "__main__":
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument("-b", "--base", type=str)
    args = argument_parser.parse_args()

    process_folders(args.base)