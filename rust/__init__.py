import os
import subprocess
from subprocess import check_call, check_output, STDOUT

WINDOWS = os.name == "windows"

def basename(index):
	return "euler{}".format(index)

def prepare(index):
	source = "src/" + basename(index) + ".rs"
	with open("log/" + str(index) + ".prepare.log", "wt") as log:
		args = ["rustc", "--out-dir", "target", source]
		check_call(args, stdout=log, stderr=STDOUT)

def run(index):
	executable = "target/" + basename(index)
	if WINDOWS:
		executable += ".exe"

	with open("log/" + str(index) + ".run.log", "wt") as log:
		returncode = check_output(executable, stderr=log)
	return returncode
