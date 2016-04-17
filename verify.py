#! python3
"""
Check that the solutions for a given language are valid.
The language-specific calls are implemented in /LANGUAGE/__init__.py

Usage:
    verify.py [options] LANGUAGE

Options:
    --noprep       Skip the preparation (compiling/building) step.
    -h, --help     Display this help message.
"""

import logging

from codecs       import decode
from contexttimer import Timer
from docopt       import docopt
from importlib    import import_module
from os           import chdir

def setup_logging(lang):
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

def verify(args, answers, lang, prepare, run):
	logger = setup_logging(lang)
	for index, answer in enumerate(answers, start=1):
		if not '--noprep' in args:
			try:
				prepare(index)
			except Exception as e:
				logging.critical("Could not prepare problem {}: {}".format(
					index, e))
				continue

		with Timer() as t:
			try:
				result = run(index)
			except Exception as e:
				logger.critical("Could not run problem {}: {}".format(
					index, e))
				logger.debug("See {} for details.".format(lang + '/log'))
				continue
			else:
				result = int(result)

		delta = t.elapsed
		if delta > 60:
			logger.warn("Problem {} took too long ({}sec) to run".format(
				index, delta))
		if result != answer:
			logger.error("Problem {} result: {!r} expected {!r}".format(
				index, result, answer))
		else:
			logger.info("Problem {}: okay".format(index))

def main(args):
	lang = args["LANGUAGE"]
	try:
		lang_handler = import_module(lang)
	except ImportError as e:
		e.msg = "No language file '{}/__init__.py' found".format(lang)
		raise e
	answers = get_answers()
	chdir(lang)
	verify(args, answers, lang, lang_handler.prepare, lang_handler.run)

if __name__ == "__main__":
	args = docopt(__doc__)
	main(args)
