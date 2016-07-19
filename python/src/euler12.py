from math import sqrt, floor, ceil

def divisors(n):
	for d in range(1, ceil(sqrt(n))):
		if n % d == 0:
			yield d
			yield n / d
	root = sqrt(n) 
	if root == floor(root):
		yield root

def genlen(gen):
	count = 0
	for _ in gen:
		count += 1
	return count

def triangle_numbers():
	i = 1
	n = 0
	while True:
		n += i
		i += 1
		yield n

for t in triangle_numbers():
	if genlen(divisors(t)) > 500:
		print(t)
		break