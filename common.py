"""Common patterns to be specialised per-language"""

import os
from subprocess import check_call, check_output, STDOUT
from functools  import partial

WINDOWS = os.name == "windows"

__all__ = ["setup", "clean", "prepare", "run", "basename", "partial"]

def basename(index):
	return "euler{}".format(index)

def setup():
	os.makedirs('log',    exist_ok=True)
	os.makedirs('target', exist_ok=True)

def clean():
	os.rmdir('log')
	os.rmdir('target')

def prepare(index, logger=None, extension='.code', argv=tuple(), ):
	source = "src/" + basename(index) + extension
	logfile = "log/" + str(index) + ".prepare.log"
	with open(logfile, "wt") as log:
		check_call(argv + [source], stdout=log, stderr=STDOUT)
	if logger:
		dump_log(logger, logfile)

def run(index, logger=None):
	executable = "target/" + basename(index)
	if WINDOWS:
		executable += ".exe"
	
	logfile = "log/" + str(index) + ".run.log"
	with open(logfile, "wt") as log:
		returncode = check_output(executable, stderr=log)
	if logger:
		dump_log(logger, logfile)
	return returncode

def dump_log(logger, logfile):
	with open(logfile, "rt") as f:
		for line in f:
			logger.info(line)