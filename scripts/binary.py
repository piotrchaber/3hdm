import argparse
import os
import subprocess
import time


parser = argparse.ArgumentParser()
parser.add_argument("--verbose", action="store_true", help="provide additional information when the execution of binary file failed")
args = parser.parse_args()


WIDTH = 8


def statement_line(status:str, msg:str, align:str=""):
    return "[{:{align}{width}s}] {}".format(status, msg, align=align, width=WIDTH)


def print_process_statement(process, name:str, time:float):
    return_code = process.returncode
    if not return_code:
        print(statement_line("OK", "Succeed in {:.4f} seconds, exit code {}".format(time, return_code), ">"))
    else:
        print(statement_line("NOK", "Failed in {:.4f} seconds, exit code {}".format(time, return_code), ">"))
        if args.verbose:
            print(process.stderr.decode("utf-8").strip())


def print_processes_statement(processes_status):
    any_failed = any(processes_status.values())
    if any_failed:
        how_many = len([item for item in processes_status.values() if item])
        print(statement_line("Failed", "{} binary files, listed below:".format(how_many), "^"))
        print(*[statement_line("Failed", key, "^") for (key, value) in processes_status.items() if value], sep="\n")
    else:
        print(statement_line("Passed", "{} binary files".format(len(processes_status)), "^"))


if __name__ == "__main__":
    current_work_directory = os.getcwd()
    build_directory = current_work_directory + "/build"
    binary_directory = build_directory + "/bin"

    if os.path.exists(binary_directory):
        os.chdir(build_directory)
        total_time = 0.0
        processes_status = dict()
        binary_files = [fs_object for fs_object in os.listdir(binary_directory)]
        print(statement_line("="*WIDTH, "Running {} binary files".format(len(binary_files))))
        for binary_file in binary_files:
            print(statement_line("RUN", binary_file))
            start_time = time.time()
            process = subprocess.run("./bin/" + binary_file, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            elapsed_time = time.time() - start_time
            print_process_statement(process, binary_file, elapsed_time)
            processes_status[binary_file] = process.returncode
            total_time = total_time + elapsed_time
        print(statement_line("="*WIDTH, "{} binary files ran ({:.4f} seconds)".format(len(binary_files), total_time)))
        print_processes_statement(processes_status)
