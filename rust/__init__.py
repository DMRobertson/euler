import os, sys
sys.path.insert(1, os.path.join(sys.path[0], '..'))
import common
from functools import partial

def get_prepare_argv(index, source):
	return ["rustc", "--out-dir", "target", source]

implemented = partial(common.implemented, extension='.rs')
clean   = common.clean
setup   = common.setup
prepare = partial(common.prepare,
	extension='.rs', get_argv=get_prepare_argv)
run     = common.run