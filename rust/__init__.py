import os, sys;
sys.path.insert(1, os.path.join(sys.path[0], '..'));
from common import *

prepare = partial(prepare,
	extension='.rs',
	argv=["rustc", "--out-dir", "target"]
)
