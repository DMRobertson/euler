import os, sys
sys.path.insert(1, os.path.join(sys.path[0], '..'))
import common
from functools import partial

def get_prepare_argv(index, source):
	with open(source, 'rt') as f:
		first_line = f.readline()
		if first_line.startswith('//prepare:'):
			args = first_line[10:]
			#assume there are no quoted arguments for now
			extras = [arg.strip() for arg in args.split()]
		else:
			extras = []
	
	return ["gcc",
		"-Wall", "-Wextra", "-std=c99",
		"-g",
		"-o", common.target(index),
		source,
	] + extras

implemented = partial(common.implemented, extension='.c')
clean   = common.clean
setup   = common.setup
prepare = partial(common.prepare,
	extension='.c', get_argv=get_prepare_argv)
run     = common.run