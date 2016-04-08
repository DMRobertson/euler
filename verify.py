#!/usr/bin/env python3
import os
import sys
import re
from subprocess import check_output
from time import time

WINDOWS = os.name == 'nt'

problem_source = re.compile(r"euler(\d+)\.rs")
answers = """
233168
4613732
6857
906609
232792560
25164150
104743
23514624000
31875000
142913828922
""".split()

for file in os.listdir('src'):
	match = problem_source.match(file)
	if match is None:
		continue
	problem = match.groups()[0]

	binary = "target/euler" + problem
	if WINDOWS:
		binary += ".exe"

	#really crude way to measure time spent
	before = time()
	result = check_output(binary).decode(encoding='utf-8').strip()
	delta = time() - before

	try:
		expected = answers[int(problem)-1]
	except IndexError:
		print("Don't know the answer for problem " + problem)
		break
	if result != expected:
		raise ValueError("Problem {} result: {!r} expected {!r}".format(
			problem, result, expected))
	if delta > 60:
		print("Problem {} took too long ({}sec) to run".format(problem, delta))
