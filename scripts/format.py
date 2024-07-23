import os
import re


def is_directory(fs_object:str):
    excluded_directories = ["build", "extern"]
    return os.path.isdir(fs_object) and not fs_object.startswith(".") and not fs_object in excluded_directories


def remove_whitespace(line:str):
    first_char = re.search(r'\S', line)
    if first_char:
        tabs_counter = line[0 : first_char.start()].count("\t")
        line = line.replace("\t", "    ", tabs_counter)
    else:
        line = line.strip() + '\n'
    line = line.rstrip() + '\n'
    return line


def has_whitespace(line:str):
    has_tabs = line.count("\t")
    has_spaces = line.endswith(" \n")
    return has_tabs or has_spaces


def check_whitespace(lines:list):
    return True in [has_whitespace(line) for line in lines]


def print_whitespace_statement(file_status:dict):
    if not len(file_status): return
    print(len(files_status), "files have been reformated:", '\n')
    print("\n".join(file_status.keys()), '\n')
    if True not in files_status.values():
        print("No more whitespace detected!")
    else:
        print("More whitespace deteceted:", '\n')
        print("\n".join([file for file in files_status.keys() if files_status[file] is True]))


if __name__ == "__main__":
    files_status = dict()
    directories = [fs_object for fs_object in os.listdir() if is_directory(fs_object)]

    for dir in directories:
        for root, dirs, files in os.walk(dir):
            files = [file for file in files if file.endswith(".cpp") or file.endswith(".h")]
            if files:
                file_paths = ['/'.join([root, file]) for file in files]
                for file_path in file_paths:
                    new_lines = []
                    with open(file_path) as file:
                        old_lines = file.readlines()
                        for line in old_lines:
                            new_lines.append(remove_whitespace(line))
                    with open(file_path, 'w') as file:
                        for line in new_lines:
                            file.write(line)
                    if old_lines != new_lines:
                        files_status[file_path] = check_whitespace(new_lines)
    
    print_whitespace_statement(files_status)
