#! /usr/bin/env python3
"""
Check that the solutions for a given language are valid.
The language-specific calls are implemented in /LANGUAGE/__init__.py

Usage:
    verify.py [options] <language>

Arguments:
	

Options:
    --clean           Remove previous builds and any intermediate files.
    -h, --help        Display this help message.
    --noprep          Skip the preparation (compiling/building) step.
    --problem=number  Verify a specific problem only. If so, the program's output stdout will be printed to file. [default: all]
    --timeout         Stop the problem from running if it takes over a minute. Without this option we 
"""

import logging

from codecs       import decode
from contexttimer import Timer
from docopt       import docopt
from importlib    import import_module
from os           import chdir, makedirs
from sys          import exc_info

def setup_logging(lang):
	makedirs('log', exist_ok=True)
	logger = logging.getLogger("euler " + lang)
	logger.setLevel('DEBUG')

	filename = "log/verify.log"
	filedump = logging.FileHandler(filename, mode='wt', encoding='utf-8')
	filedump.setLevel('DEBUG')
	formatter = logging.Formatter('%(asctime)s %(levelname)-8s %(message)s')
	filedump.setFormatter(formatter)
	logger.addHandler(filedump)

	console = logging.StreamHandler()
	console.setLevel('INFO') #show info and above
	formatter = logging.Formatter('%(levelname)-8s %(message)s')
	console.setFormatter(formatter)
	logger.addHandler(console)

	return logger

def get_answers():
	with open('resource/answers.txt', 'rb') as f:
		f.readline()
		answers = [ int( decode(line, 'base64') ) for line in f ]
		return answers

def verify(index, answer, display, lang, args, logger):
	"""Verify that <lang>'s solution to problem <index> is the expected <answer>. If <display> is True, print the contents of stdout and stderr. The command line <args> are passed on too."""
	#1. Prepare if neccessary.
	if not args['--noprep']:
		try:
			lang.prepare(index, logger if display else None)
		except Exception as e:
			logger.critical("Could not prepare problem {}: {}".format(
				index, e))
			logger.info("See {} for details.".format(lang.name + '/log'))
			logger.debug("Traceback below", exc_info=exc_info())
			return
	
	#2. Time the run.
	with Timer() as t:
		try:
			result = lang.run(index, logger if display else None)
		except Exception as e:
			logger.critical("Could not run problem {}: {}".format(
				index, e))
			logger.info("See {} for details.".format(lang.name + '/log'))
			logger.debug("Traceback below", exc_info=exc_info())
			return
	
	#3. Is the result an integer?
	try:
		result = int(result)
	except Exception as e:
		logger.error("Couldn't format problem {} answer: {}".format(
			index, e
		))
		return
	
	#4. Was the answer computed within a minute?
	if t.elapsed > 60:
		logger.warn("Problem {} took too long ({}sec) to run".format(
			index, t.elapsed))
	
	#5. Is the answer correct?
	if result != answer:
		logger.error("Problem {} result: {!r} expected {!r}".format(
			index, result, answer))
	else:
		logger.debug("Problem {}: okay".format(index))

def main(args):
	#1. Check to see if we support the given language.
	try:
		lang = import_module(args["<language>"])
	except ImportError as e:
		e.msg = "No language file '{}/__init__.py' found: ".format(args["<language>"]) + e.msg
		raise e
	else:
		lang.name = args["<language>"]
	
	#2. If so, prepare to compile/run
	logger = setup_logging(lang.name)
	answers = get_answers()
	
	chdir(lang.name)
	if args['--clean']:
		lang.clean()
	lang.setup()
	
	#3. Determine which problems we're going to verify.
	try:
		index = int(args['--problem'])
	except Exception:
		expected = enumerate(answers, start=1)
		single = True
	else:
		expected = [(index, answers[index - 1])]
		single = False
	
	#4. Time to verify
	for index, answer in expected:
		verify(index, answer, single, lang, args, logger)

if __name__ == "__main__":
	args = docopt(__doc__)
	main(args)
