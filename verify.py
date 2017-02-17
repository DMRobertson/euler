#! /usr/bin/env python3
"""
Check that the solutions for a given language are valid.
The language-specific calls are implemented in /language/__init__.py

Usage:
    verify.py [options] <language>

Arguments:
    language              The language to verify solutions to.

Options:
    -a, --accept-any       Don't verify that the solution gives the correct answer.
    -b, --build-only       Don't attempt to run a solution.
    -c, --clean            Remove previous builds and any intermediate files.
    -d, --debug            Run a solution in debug mode.
    -h, --help             Display this help message.
    -t, --summarise-times  Display the min, max, mean, median and total solution runtime.
    -r, --run-only         Skip the preparation (compiling/building) step.
    -p, --problem=number   Verify a specific problem only.
    -v, --verbose          Print all output to screen as well as log.
"""

#TODO --timeout         Stop the problem from running if it takes over a minute. Without this option we run until completion.

import logging
import statistics

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
	if args['--accept-any'] or args['--build-only']:
		return DummyList()
	with open('resource/answers.txt', 'rb') as f:
		f.readline()
		answers = [ int( decode(line, 'base64') ) for line in f ]
		return answers

class DummyList:
	def __getitem__(self, key):
		return None

def verify(index, expected, lang, args, logger):
	"""Verify that <lang>'s solution to problem <index> is the expected <answer>.
	Use <logger> for reporting sucess or failure.
	The command line <args> are passed on too.
	"""
	result = {}
	#1. Prepare if neccessary.
	if lang.prepare is not None:
		if args['--run-only']:
			logger.debug("Not building problem {}".format(
				index))
		else:
			try:
				stdout_err = lang.prepare(index, logger)
			except CalledProcessError as e:
				logger.critical("Could not prepare problem {}: {}".format(
					index, e))
				output = e.output.decode('utf8').rstrip()
				logger.debug("Prepare stdout/err was:\n" + output)
				result["prepare_error"] = output
				return result
			else:
				output = stdout_err.rstrip()
				logger.debug("Problem {} prepared successfully. Output and error was:\n{}".format(
				index, output))
				result["prepare_success"] = output
	
	if args['--build-only']:
		logger.debug("Not running Problem {}".format(index))
		return result
	
	#2. Time the run.
	with Timer() as t:
		try:
			answer = lang.run(index, logger, debug=args['--debug'])
		except CalledProcessError as e:
			logger.critical("Could not run problem {}: {}".format(
				index, e))
			output = e.output.decode('utf8').rstrip()
			logger.debug("Run stdout/err was:\n" + output)
			result["run_error"] = output
			return result
		except Exception as e:
			logger.critical("Could not run problem {}: {}".format(
				index, e))
			logger.debug("Traceback was:", exc_info=exc_info())
			return result
	
	answer = answer.rstrip()
	result["answer"] = answer
	
	#3. Did the program finish within a minute?
	logger.debug("Problem {} completed successfully".format(index))
	result["time"] = t.elapsed
	if t.elapsed > 60:
		logger.warn("Problem {} took too long ({:.2f}sec) to run".format(
			index, t.elapsed))
	else:
		logger.debug("Problem {} ran in {:.2f}sec".format(
			index, t.elapsed))
	logger.debug("Problem {}'s output was: \n{}".format(
		index, answer.rstrip()))
	
	#4. Don't bother checking the output if we're just debugging.
	if args['--accept-any']:
		result["correct"] = None
		logger.debug("Skipping verification: any answer accepted")
		return result
	
	#4. Is the result an integer?
	try:
		answer = int(answer)
	except Exception as e:
		result["correct"] = None
		logger.error("Couldn't interpret problem {} answer as an integer: {}".format(
			index, e))
		return result
	
	#5. Is the answer correct?
	result["correct"] = answer == expected
	if not result["correct"]:
		logger.error("Problem {} answer: {!r} expected {!r}".format(
			index, answer, expected))
	else:
		logger.debug("Problem {} gave the correct answer".format(
			index))
	return result

def main(args):
	#1. Check to see if we support the given language.
	logger = setup_logging("euler", args)
	try:
		lang = import_module(args["<language>"])
	except ImportError as e:
		logger.critical("No language file '{}/__init__.py' found.".format(
			args["<language>"]))
		logger.exception(e)
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
		
		if not lang.implemented(index):
			logger.critical("Language {} has no solution implemented for problem {}".format(
				args['--lang'], args['--problem']))
			return
		
		indices = [index]
	else :
		indices = lang.implemented_indices()
	
	expected_answers = {}
	for index in indices:
		try:
			expected_answers[index] = answers[index - 1]
		except IndexError:
			logger.critical("Can't verify problem {}: no answer in resource/answers.txt. Use --accept-any to disable answer checking".format(
				index))
	
	#4. Time to verify
	if lang.prepare is None:
		logger.info("Language {} has no preparation step.".format(
			lang.name))
	results = {}
	for index, answer in expected_answers.items():
		result = verify(index, answer, lang, args, logger)
		if result is None:
			result = {}
		results[index] = result
	
	if args['--summarise-times']:
		runtime_data = { index: result["time"] for index, result in results.items() if "time" in result }
		runtimes = list(runtime_data.values())
		
		time_extractor = lambda x: x[1]
		
		successes = len(runtimes)
		attempts = len(results)
		
		print(successes, "out of", attempts, "problems ran successfully")
		if successes ==  1:
			print("Runtime: {:.3f}s".format(runtimes[0]))
		elif successes > 1:
			print("min: Problem {} @ {:.3f}s".format( *min(runtime_data.items(), key=time_extractor) ) )
			print("max: Problem {} @ {:.3f}s".format( *max(runtime_data.items(), key=time_extractor) ) )
			print("mean: {:.3f}s".format( statistics.mean(runtimes) ) )
			print("median: {:.3f}s".format( statistics.median(runtimes) ) )
			print("total: {:.3f}s".format( sum(runtimes) ) )
	
	logger.info("Verification script complete")

if __name__ == "__main__":
	args = docopt(__doc__)
	main(args)
