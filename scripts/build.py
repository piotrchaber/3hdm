import argparse
import os
import subprocess
import time

from typing import List


parser = argparse.ArgumentParser()
parser.add_argument("--remove", action="store_true", help="rebuild from scratch by removing build directory")
args = parser.parse_args()


def check_build_directory(build_directory:str):
    if os.path.exists(build_directory) and args.remove:
        subprocess.run(["rm", "-rf", "build"], stdout=subprocess.PIPE)

    if not os.path.exists(build_directory): 
        subprocess.run(["mkdir", "build"], stdout=subprocess.PIPE)


def run_process(commands:List[str]):
    process = subprocess.Popen(commands, stdout=subprocess.PIPE)
    while True:
        line = process.stdout.readline().decode('utf-8')
        if not line:
            print()
            break
        print(line.strip())

    return process


def print_process_statement(process, name:str, time:float):
    process.communicate()
    print("{} process {} in {:.4f} seconds, exit code {}".format(name, "failed" if process.returncode else "completed successfully", time, process.returncode))


if __name__ == "__main__":
    start_time = time.time()
    current_work_directory = os.getcwd()
    build_directory = current_work_directory + "/build"

    check_build_directory(build_directory)
    os.chdir(build_directory)

    cmake_process = run_process(["cmake", ".."])
    make_process = run_process(["make"])

    elapsed_time = time.time() - start_time
    print_process_statement(make_process, "Build", elapsed_time)
