#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025-2026, The OpenDMI contributors
#
# SPDX-License-Identifier: BSD-3-Clause
#
import os
import getopt
import subprocess
import sys
import yaml
from yaml.loader import SafeLoader

base_dir = os.path.dirname(os.path.realpath(__file__))
opendmi_dir = os.path.join(base_dir, "build/opendmi")
data_dir = os.path.join(base_dir, "data")

def data_files():
    for root, _, files in os.walk(data_dir):
        for file_name in files:
            file_path = os.path.join(root, file_name)

            file_base, file_ext = os.path.splitext(file_path)
            if file_ext != ".bin":
                continue

            yield file_path, file_base + ".yaml"

def load_spec(spec_path: str):
    with open(spec_path) as spec_file:
        return yaml.load(spec_file, Loader=SafeLoader)

def load_dump(dump_path: str):
    try:
        process = subprocess.Popen(
            [f"{opendmi_dir}/bin/opendmi", "--from-dump", dump_path, "--format=yaml"],
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE
        )
        stdout, stderr = process.communicate()

        return yaml.load(stdout, Loader=SafeLoader)
    except subprocess.CalledProcessError as e:
        print("FAILED:")
        print(e.stderr)

def generate_spec(dump_path: str, spec_path: str):
    print(f"Generating spec: {dump_path}")
    pass

def check_spec(dump_path: str, spec_path: str):
    if not os.path.isfile(spec_path):
        print(f"Skipping: {dump_path} (no spec)")
        return

    print(f"Checking spec: {dump_path}")
    spec = load_spec(spec_path)
    data = load_dump(dump_path)

def show_usage():
    pass

def main(argv):
    mode = "test"

    try:
        opts, args = getopt.getopt(argv, "hb", ["help", "baseline"])
    except getopt.GetoptError as e:
        print(str(e))
        print('Use -h or --help for help')
        sys.exit(1)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            show_usage()
            sys.exit(0)
        elif opt in ("-b", "--baseline"):
            mode = "generate"

    for dump_path, spec_path in data_files():
        if mode == "generate":
            generate_spec(dump_path, spec_path)
        else:
            check_spec(dump_path, spec_path)

if __name__ == "__main__":
	main(sys.argv[1:])
