# tools/cprgen.py
# -----------------------------------------------------
# Copyright 2024 The GlassSurf Authors
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

#! /usr/bin/env python

import argparse
import os

DELIMETER = "----------------------------------------"
COPYRIGHT_FILE_HEADER = (
    "Open-Source Licenses\n"
    "Portions of this software may utilize the following copyrighted material, "
    "the use of which is hereby acknowledged:\n"
)
COPYRIGHT_FILE_HEADER += DELIMETER

def read_file(file_path):
    """
    Read the content of a file and return it as a string.

    Parameters:
        file_path (str): The path to the file to be read.

    Returns:
        str: The content of the file.
    """
    try:
        with open(file_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        return None
    except Exception as e:
        print(f"Error: {e}")
        return None
    
def append_to_file(file_path, content):
    """
    Append content to a file.

    Parameters:
        file_path (str): The path to the file to which content will be appended.
        content (str): The content to be appended to the file.
    """
    try:
        with open(file_path, 'a') as file:
            file.write(content)
        print(f"Content successfully appended to '{file_path}'.")
    except Exception as e:
        print(f"Error: {e}")

def find_copyright_files(base_dir):
    """
    Recursively scan directories within a base directory to find files with the name "copyright."

    Parameters:
        base_dir (str): The base directory path to start the search.

    Returns:
        list: A list of file paths with the name "copyright."
    """
    copyright_files = []

    for root, dirs, files in os.walk(base_dir):
        for file_name in files:
            if file_name.lower() == 'copyright':
                copyright_files.append(os.path.join(root, file_name))

    return copyright_files

def get_parent_folder_name(path):
    """
    Get the immediate parent folder name from a given path.

    Parameters:
        path (str): The path from which to extract the parent folder name.

    Returns:
        str: The immediate parent folder name.
    """
    return os.path.basename(os.path.dirname(path))

if __name__ == "__main__":
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument("-o", "--output", type=str, required=True)
    argument_parser.add_argument("-s", "--share", type=str, required=True)
    args = argument_parser.parse_args()

    copyright_files = find_copyright_files(args.share)

    append_to_file(args.output, COPYRIGHT_FILE_HEADER + "\n")

    for file in copyright_files:
        file_content = read_file(file)
        lib_name = get_parent_folder_name(file)

        append_to_file(args.output, lib_name + "\n" + file_content + "\n" + DELIMETER + "\n")

    print("Copyright generated")

