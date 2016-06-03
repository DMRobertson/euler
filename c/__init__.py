import os, sys;
sys.path.insert(1, os.path.join(sys.path[0], '..'));
from common import *
_prepare = prepare

def prepare(index, logger=None):
	_prepare(index, logger,
		'.c',
		["gcc", "-Wall", "-Wextra", "-std=c99", "-o", "target/" + basename(index)],
	)
