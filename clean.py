import os
import shutil

def delete_path(path: str) -> bool :
    if os.path.isfile(path):
        print("Deleting file \"" + path + "\"")
        os.remove(path)
        return True

    if os.path.isdir(path):
        print("Deleting folder \"" + path + "\"")
        shutil.rmtree(path)
        return True

    return False

# Files created by cmake
junk_list = ["cmake_install.cmake", "CMakeCache.txt", "CMakeFiles", "Makefile", "e_voting"]

# Compiled files
extensions_junk = [".o", ".a", ".so"]

def delete_junk(path: str):
    for file in os.listdir(path):
        full_path = os.path.join(path, file)

        if file in junk_list:
            delete_path(full_path)
            continue

        file_extention = os.path.splitext(full_path)[1]
        if file_extention in extensions_junk :
            delete_path(full_path)
            continue
            
        if os.path.isdir(full_path):
            delete_junk(full_path)

current_dir = os.getcwd()
delete_junk(current_dir)