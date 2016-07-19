"""Helper functions to implement per-language calls"""

import os
from subprocess import check_output, STDOUT

WINDOWS = os.name == "windows"

def implemented(index, extension):
	return os.path.isfile(source(index, extension))
	
def setup(compiled=True):
	os.makedirs('log',    exist_ok=True)
	if compiled:
		os.makedirs('target', exist_ok=True)

def clean(compiled=True):
	os.rmdir('log')
	if compiled:
		os.rmdir('target')

def source(index, extension):
	return os.path.join("src", "euler" + str(index) + extension)
	
def target(index):
	extension = ".exe" if WINDOWS else ""
	return os.path.join("target", "euler" + str(index) + extension)

def prepare(index, logger, extension=None, get_argv=None):
	src = source(index, extension)
	argv = get_argv(index, src)
	stdout_err = check_output(argv, stderr=STDOUT)
	return stdout_err.decode('utf8')

def run(index, logger=None, get_argv=None):
	if get_argv is None:
		argv = target(index)
	else:
		argv = get_argv(index)
	stdout_err = check_output(argv, stderr=STDOUT)
	return stdout_err.decode('utf8')