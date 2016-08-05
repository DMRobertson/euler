#! /usr/bin/env python3
"""
Check that the solutions for a given language are valid.
The language-specific calls are implemented in /LANGUAGE/__init__.py

Usage:
    verify.py [options] <language>

Arguments:
	

Options:
    -d, --debug           Don't verify solution output.
    -c, --clean           Remove previous builds and any intermediate files.
    -h, --help            Display this help message.
    --noprep              Skip the preparation (compiling/building) step.
    -p, --problem=number  Verify a specific problem only.
    -v, --verbose         Print all output to screen as well as log.
"""

#TODO --timeout         Stop the problem from running if it takes over a minute. Without this option we run until completion.

import logging

from codecs       import decode
from contexttimer import Timer
from docopt       import docopt
from importlib    import import_module
from os           import chdir, makedirs
from sys          import exc_info
from subprocess   import CalledProcessError

def setup_logging(lang, args):
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
	if args['--verbose']:
		console.setLevel('DEBUG')
	else:
		console.setLevel('INFO')
	formatter = logging.Formatter('%(levelname)-8s %(message)s')
	console.setFormatter(formatter)
	logger.addHandler(console)
	
	logger.info("Logging to {}".format(filename))
	return logger

def get_answers(args):
	if args['--debug']:
		return DummyList()
	with open('resource/answers.txt', 'rb') as f:
		f.readline()
		answers = [ int( decode(line, 'base64') ) for line in f ]
		return answers

class DummyList:
	def __getitem__(self, key):
		return None

def verify(index, answer, lang, args, logger):
	"""Verify that <lang>'s solution to problem <index> is the expected <answer>.
	Use <logger> for reporting sucess or failure.
	The command line <args> are passed on too.
	"""
	#1. Prepare if neccessary.
	if args['--noprep']:
		logger.debug("Skipping preparation for problem {}".format(
			index))
	elif lang.prepare is not None:
		try:
			stdout_err = lang.prepare(index, logger)
		except CalledProcessError as e:
			logger.critical("Could not prepare problem {}: {}".format(
				index, e))
			logger.debug("Prepare stdout/err was:\n" + e.output.decode('utf8').rstrip())
			return
		else:
			logger.debug("Problem {} prepared successfully. Output and error was:\n{}".format(
			index, stdout_err.rstrip() ))
	
	#2. Time the run.
	with Timer() as t:
		try:
			result = lang.run(index, logger)
		except CalledProcessError as e:
			logger.critical("Could not run problem {}: {}".format(
				index, e))
			logger.debug("Run stdout/err was:\n" + e.output.decode('utf8').rstrip())
			return
		except Exception as e:
			logger.critical("Could not run problem {}: {}".format(
				index, e))
			logger.debug("Traceback was:", exc_info=exc_info())
			return
		else:
			# Don't bother checking the output if we're just debugging.
			logger.debug("Problem {} ran successfully".format(index))
			if args['--debug']:
				logger.info("Problem {}'s output was: \n{}".format(
					index, result.rstrip()))
				logger.info("Skipping verification")
				return
	
	#3. Is the result an integer?
	try:
		result = int(result)
	except Exception as e:
		logger.error("Couldn't format problem {} answer: {}".format(
			index, e))
		return
	
	#4. Is the answer correct?
	if result != answer:
		logger.error("Problem {} result: {!r} expected {!r}".format(
			index, result, answer))
	else:
		logger.debug("Problem {} gave the correct answer".format(
			index))
		
	#5. Was the answer computed within a minute?
	if t.elapsed > 60:
		logger.warn("Problem {} took too long ({:.2f}sec) to run".format(
			index, t.elapsed))
	else:
		logger.debug("Problem {} ran in {:.2f}sec".format(
			index, t.elapsed))


def main(args):
	#1. Check to see if we support the given language.
	logger = setup_logging("euler", args)
	try:
		lang = import_module(args["<language>"])
	except ImportError as e:
		logger.critical("No language file '{}/__init__.py' found.".format(
			args["<language>"]))
		return
	else:
		lang.name = args["<language>"]
		logger.info("Found language file for {}".format(
			args["<language>"]))
	
	#2. If so, prepare to compile/run
	answers = get_answers(args)
	chdir(lang.name)
	if args['--clean']:
		lang.clean()
	lang.setup()
	
	#3. Determine which problems we're going to verify.
	if args['--problem'] is not None:
		try:
			index = int(args['--problem'])
			if index <= 0:
				raise ValueError
		except Exception:
			logger.exception("Couldn't interpret '--problem {}' as a positive integer".format(
				args['--problem']))
			return
		
		try:
			expected = [(index, answers[index - 1])]
		except IndexError:
			logger.critical("Can't verify problem {}: no answer in resource/answers.txt".format(
				args['problem']
			))
	else:
		expected = enumerate(answers, start=1)
	
	#4. Time to verify
	if lang.prepare is None:
		logger.info("Language {} has no preparation step.".format(
			lang.name))
	for index, answer in expected:
		if not lang.implemented(index):
			if args['--problem']:
				reporter = logger.critical
			else:
				reporter = logger.warning
			reporter("Problem {} is not implemented for {}".format(
				index, lang.name))
			continue
				
		verify(index, answer, lang, args, logger)
	
	logger.info("Verification script complete")

if __name__ == "__main__":
	args = docopt(__doc__)
	main(args)
