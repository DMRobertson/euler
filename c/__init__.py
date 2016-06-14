import os, sys;
sys.path.insert(1, os.path.join(sys.path[0], '..'));
from common import *

def get_argv(index, source):
	return ["gcc",
		"-Wall", "-Wextra", "-std=c99",
		"-o", "target/" + basename(index),
		source,
		"-lm", #link maths library. See http://stackoverflow.com/q/1033898/5252017
	]

prepare = partial(prepare, extension='.c', get_argv=get_argv)