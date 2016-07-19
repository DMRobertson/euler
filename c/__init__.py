import os, sys
sys.path.insert(1, os.path.join(sys.path[0], '..'))
import common
from functools import partial

def get_prepare_argv(index, source):
	return ["gcc",
		"-Wall", "-Wextra", "-std=c99",
		"-o", common.target(index),
		source,
		"-lm", #link maths library. See http://stackoverflow.com/q/1033898/5252017
	]

implemented = partial(common.implemented, extension='.c')
clean   = common.clean
setup   = common.setup
prepare = partial(common.prepare,
	extension='.c', get_argv=get_prepare_argv)
run     = common.run