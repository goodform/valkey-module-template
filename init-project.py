import os
import re
import sys

def validate_name(name):
    # Use regular expression to validate the name
    pattern = r'^[a-zA-Z_-]+$'
    if re.match(pattern, name):
        return True
    return False

def replace_string_in_files(file_paths, old_string, new_string):
    script_directory = os.path.dirname(os.path.abspath(__file__))
    for file_path in file_paths:
        # Construct the absolute path based on the script directory
        absolute_path = os.path.join(script_directory, file_path)
        # Process files only, excluding directories
        if os.path.isfile(absolute_path):
            with open(absolute_path, 'r') as f:
                content = f.read()
            # Replace the specified string
            new_content = content.replace(old_string, new_string)
            with open(absolute_path, 'w') as f:
                f.write(new_content)

# Get the name from command line argument
if len(sys.argv) > 1:
    name = sys.argv[1]
else:
    name = input("Enter a name: ")

# Validate the name
if validate_name(name):
    # Get the array of relative file paths to replace
    file_paths = [
        "CMakeLists.txt",
        "runtest.sh",
        # Add more file paths...
    ]
    # Replace the specified string (old_string) with the input name (new_string) in the project files
    replace_string_in_files(file_paths, "valkeytemplate", name)
    print("Replacement completed.")
else:
    print("Invalid name. Only letters, hyphens, and underscores are allowed.")