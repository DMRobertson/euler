import os, sys
sys.path.insert(1, os.path.join(sys.path[0], '..'))
import common
from functools import partial

def get_run_argv(index):
	return ["python3", "src/euler{}.py".format(index)]

implemented = partial(common.implemented, extension='.py')
setup = partial(common.setup, compiled=False)
def clean():
	os.rmdir('log')
	for file in iglob('*.pyc'):
		os.remove(file)
		
prepare = None
run = partial(common.run, get_argv=get_run_argv)