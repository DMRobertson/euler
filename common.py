"""Common patterns to be specialised per-language"""

import os
from subprocess import check_call, check_output, STDOUT, CalledProcessError
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

def prepare(index, logger=None, extension='.code', get_argv=None):
	source = "src/" + basename(index) + extension
	logfile = "log/" + str(index) + ".prepare.log"
	argv = get_argv(index, source)
	with open(logfile, "wt") as log:
		check_call(argv, stdout=log, stderr=STDOUT)
	if logger:
		dump_log(logger, logfile)

def run(index, logger=None):
	executable = "target/" + basename(index)
	if WINDOWS:
		executable += ".exe"
	
	logfile = "log/" + str(index) + ".run.log"
	try:
		error = None
		with open(logfile, "wt", encoding='utf-8') as log:
			try:
				stdout = check_output(executable, stderr=log)
			except CalledProcessError as e:
				error = e
				stdout = e.output
				raise
			finally:
				if stdout.strip():
					log.write("** STDOUT **\n")
					log.write(str(stdout, encoding='ascii'))
	finally:
		if logger:
			dump_log(logger, logfile)
	return stdout

def dump_log(logger, logfile):
	with open(logfile, "rt") as f:
		for line in f:
			logger.debug(line.rstrip())