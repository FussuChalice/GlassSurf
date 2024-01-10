# merge.py
# -----------------------------------------------------
# Copyright 2024 The GlassSurf Authors
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

#!/usr/bin/python

import os

def merge_js_files(directory_path, output_file_path):
    with open(output_file_path, 'w') as output_file:
        for filename in os.listdir(directory_path):
            if filename.endswith(".js"):
                filepath = os.path.join(directory_path, filename)
                with open(filepath, 'r') as input_file:
                    output_file.write(input_file.read())
                    output_file.write('\n')

if __name__ == "__main__":
    input_directory = input("Enter input directory: ")
    output_file = input("Output file: ")

    merge_js_files(input_directory, output_file)
    print(f"All JavaScript files in {input_directory} have been merged into {output_file}")