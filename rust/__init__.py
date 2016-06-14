import os, sys;
sys.path.insert(1, os.path.join(sys.path[0], '..'));
from common import *

def get_argv(index, source):
	return ["rustc", "--out-dir", "target", source]

prepare = partial(prepare,
	extension='.rs',
	get_argv=get_argv
)
