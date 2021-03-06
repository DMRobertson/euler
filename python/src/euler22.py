"""Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?"""

def euler22(filepath):
	with open(filepath, "rt") as f:
		names = f.read().split(",")
	names = [ name[1:-1] for name in names ]
	names.sort()
	print(len(names), names[0], names[-1])
	score = sum( i * word_score(name) for i, name in enumerate(names) )
	return score

def word_score(name):
	offset = ord('A') - 1
	return sum(ord(char) - offset for char in name)
	
if __name__ == "__main__":
	assert( word_score("COLIN") == 53 )
	print(euler22("../resource/problem22.names"))