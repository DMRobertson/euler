#! /usr/bin/env python3
import sys
from codecs import encode


if __name__ == "__main__":
	arg = sys.argv[1]
	with open("resource/answers.txt", "ab") as f:
		f.write( encode( bytes(str(arg), encoding='ascii'), 'base64' ) )
