import re
import glob

renames = {
    "func_1001a286": "fopen",
    "func_1001a2eb": "ftell",
    "func_1001a527": "_ctime"
}

def replace_in_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    new_content = content
    for old, new in renames.items():
        new_content = re.sub(rf'\b{old}\b', new, new_content)
        
    if new_content != content:
        with open(filepath, 'w') as f:
            f.write(new_content)
        print(f"Updated {filepath}")

files_to_check = glob.glob("src/**/*.c", recursive=True) + \
                 glob.glob("src/**/*.h", recursive=True) + \
                 glob.glob("src/**/CATALOG.md", recursive=True) + \
                 glob.glob("src/**/functions.txt", recursive=True) + \
                 glob.glob("src/**/ghidra_functions.json", recursive=True)

for f in files_to_check:
    replace_in_file(f)

