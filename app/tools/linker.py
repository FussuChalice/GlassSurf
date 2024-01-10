# tools/linker.py
# -----------------------------------------------------
# Copyright 2024 The GlassSurf Authors
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

#! /usr/bin/env python

import os

PROJECT_NAME = "GlassSurf"

def read_file_lines(file_path):
    """
    Read a file and return a list of its lines.

    Parameters:
    - file_path (str): The path to the file.

    Returns:
    - list: A list containing the lines of the file.
    """
    lines = []
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"Error reading file: {e}")

    return lines

def find_line_index(lines, search_str):
    """
    Find the index of the first line containing the specified search string in a list of lines.

    Parameters:
    - lines (list): A list of strings representing lines.
    - search_str (str): The string to search for.

    Returns:
    - int or None: The index of the first line containing the search string, or None if not found.
    """
    for i, line in enumerate(lines):
        if search_str in line:
            return i
    return None

def get_file_names_in_directory(directory_path):
    """
    Get a list of file names in a specified directory.

    Parameters:
    - directory_path (str): The path to the directory.

    Returns:
    - list: A list containing the names of files in the directory.
    """
    try:
        file_names = [f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
        return file_names
    except FileNotFoundError:
        print(f"Directory not found: {directory_path}")
        return []
    except Exception as e:
        print(f"Error scanning directory: {e}")
        return []
    
def generate_target_link_libraries(files_names):
    target_link = f"target_link_libraries({PROJECT_NAME} "

    for file in files_names:
        target_link += "\"${DEPS_DIR}lib/" + file + "\" "

    target_link += ")\n"

    return target_link

def rewrite_file_with_lines(file_path, lines_list):
    """
    Rewrite the content of a file with a list of lines.

    Parameters:
    - file_path (str): The path to the file.
    - lines_list (list): A list of strings representing lines to be written to the file.
    """
    try:
        with open(file_path, 'w') as file:
            file.writelines(lines_list)
        print(f"File '{file_path}' has been successfully rewritten.")
    except Exception as e:
        print(f"Error rewriting file: {e}")

if __name__ == "__main__":
    files_names = get_file_names_in_directory("./deps/lib/")

    cmake_file_lines = read_file_lines("./CMakeLists.txt")

    flag_index = find_line_index(cmake_file_lines, "# LINKER")

    cmake_file_lines[flag_index] = generate_target_link_libraries(files_names)

    rewrite_file_with_lines("./CMakeLists.txt", cmake_file_lines)