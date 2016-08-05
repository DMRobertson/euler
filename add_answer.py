#! /usr/bin/env python3
import sys
from codecs import encode


if __name__ == "__main__":
	arg = sys.argv[1]
	if arg == "--count":
		with open("resource/answers.txt", "rt") as f:
			lines = 0
			f.readline() #ignore first line
			for line in f:
				lines += 1
			print(lines)
			
	else:
		with open("resource/answers.txt", "ab") as f:
			f.write( encode( bytes(str(arg), encoding='ascii'), 'base64' ) )
