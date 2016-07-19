#! /usr/bin/env python3
"""Language-specific instructions for verifying solutions. This example file documents the interface."""

"""This is automatically set to the name of the parent folder."""
name = None

def implemented(index):
	"""returns True if a solution exists to problem *index*, else False"""
	pass

def clean():
	"""Remove any non-source files created by the prepare or run steps."""
	pass

def setup():
	"""Ensure preconditions for prepare and run steps."""
	pass

def prepare(index, logger):
	"""Prepare the solution to problem *index*. Typically this refers to compilation. If no such function is needed define prepare=None.
	
		- *index*: positive integer, the problem number to be tested;
		- *logger*: a Logger object from the Python standard library. Use this to report success or failure, etc.
	
	returns the concatenation of stdout as a string
	"""
	pass

def run(index, logger):
	"""Run the solution to problem *index*. Typically this refers to compilation.
	
		- *index*: positive integer, the problem number to be tested;
		- *logger*: a Logger object from the Python standard library. Use this to report success or failure, etc.
		
	return solution's stdout as a string.
	"""
	pass