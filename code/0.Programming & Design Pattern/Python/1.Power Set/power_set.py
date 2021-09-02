from itertools import chain
from itertools import combinations
import copy

def powerset (iterable):
	s=list(iterable)
	l = list( chain.from_iterable (combinations(s,r) for r in range (1,len(s)+1)) )

	raw_list=list()
	for i in range (len(l)):
		raw_list.append(list())

	for i in range (len(l)):
		for j in range (len(l[i])):
			raw_list[i].append(int(l[i][j]))

	return raw_list	
						
raw_list=powerset("12345")

l=[ [1,0,0,0,0], [ 0,1,0,0,0 ], [0,0,1,0,0], [0,0,0,1,0], [0,0,0,0,1],[1,1,0,0,0],[1,0,1,0,0],[1,0,0,1,0], [1,0,0,0,1], [0,1,1,0,0], [0,1,0,1,0], [0,1,0,0,1], [0,0,1,1,0], [0,0,1,0,1], [0,0,0,1,1],[1,1,1,0,0],[1,1,0,1,0],[1,1,0,0,1], [1,0,1,1,0],[1,0,1,0,1],[1,0,0,1,1],[0,1,1,1,0],[0,1,1,0,1],[0,1,0,1,1], [0,0,1,1,1], [1,1,1,1,0],[1,1,1,0,1],[1,1,0,1,1], [1,0,1,1,1], [0,1,1,1,1],[1,1,1,1,1]]

l_pow=[ [1,0,0,0,0],[2,0,0,0,0],[3,0,0,0,0], [ 0,1,0,0,0 ],[ 0,2,0,0,0 ],[ 0,3,0,0,0 ], [0,0,1,0,0],[0,0,2,0,0],[0,0,3,0,0], [0,0,0,1,0],[0,0,0,2,0],[0,0,0,3,0], [0,0,0,0,1],[0,0,0,0,2],[0,0,0,0,3],  [1,1,0,0,0], [2,1,0,0,0], [1,2,0,0,0], [2,2,0,0,0], [3,1,0,0,0], [1,0,1,0,0],[2,0,1,0,0],[1,0,2,0,0],[2,0,2,0,0],[3,0,1,0,0],[1,0,0,1,0], [2,0,0,1,0],[1,0,0,2,0],[2,0,0,2,0],[3,0,0,1,0],[1,0,0,0,1],[2,0,0,0,1],[1,0,0,0,2],[2,0,0,0,2],[3,0,0,0,1], [0,1,1,0,0],[0,2,1,0,0],[0,1,2,0,0],[0,2,2,0,0],[0,3,1,0,0], [0,1,0,1,0],[0,2,0,1,0],[0,1,0,2,0],[0,2,0,2,0],[0,3,0,1,0], [0,1,0,0,1],[0,2,0,0,1],[0,1,0,0,2],[0,2,0,0,2],[0,3,0,0,1], [0,0,1,1,0],[0,0,2,1,0],[0,0,1,2,0],[0,0,2,2,0],[0,0,3,1,0], [0,0,1,0,1],[0,0,2,0,1],[0,0,1,0,2], [0,0,2,0,2],[0,0,3,0,1], [0,0,0,1,1],[0,0,0,2,1],[0,0,0,1,2],[0,0,0,2,2],[0,0,0,3,1],[1,1,1,0,0], [2,1,1,0,0], [1,2,1,0,0], [2,2,1,0,0], [3,1,1,0,0], [1,1,0,1,0], [2,1,0,1,0], [1,2,0,1,0], [2,2,0,1,0], [3,1,0,1,0], [1,1,0,0,1], [2,1,0,0,1], [1,2,0,0,1], [2,2,0,0,1],[3,1,0,0,1], [1,0,1,1,0], [2,0,1,1,0], [1,0,2,1,0],[2,0,2,1,0], [3,0,1,1,0], [1,0,1,0,1], [2,0,1,0,1], [1,0,2,0,1], [2,0,2,0,1], [3,0,1,0,1], [1,0,0,1,1],[2,0,0,1,1],[1,0,0,2,1],[2,0,0,2,1],[3,0,0,1,1],[0,1,1,1,0],[0,2,1,1,0],[0,1,2,1,0],[0,2,2,1,0],[0,3,1,1,0],[0,1,1,0,1],[0,2,1,0,1],[0,1,2,0,1],[0,2,2,0,1],[0,3,1,0,1],[0,1,0,1,1], [0,2,0,1,1],[0,1,0,2,1],[0,2,0,2,1],[0,3,0,1,1],[0,0,1,1,1],[0,0,2,1,1], [0,0,1,2,1],[0,0,2,2,1],[0,0,3,1,1], [1,1,1,1,0],[2,1,1,1,0],[1,2,1,1,0],[2,2,1,1,0],[3,1,1,1,0],[1,1,1,0,1],[2,1,1,0,1],[1,2,1,0,1],[2,2,1,0,1],[3,1,1,0,1],[1,1,0,1,1], [2,1,0,1,1],[1,2,0,1,1],[2,2,0,1,1],[3,1,0,1,1],[1,0,1,1,1],[2,0,1,1,1],[1,0,2,1,1],[2,0,2,1,1],[3,0,1,1,1], [0,1,1,1,1],[0,2,1,1,1],[0,1,2,1,1], [0,2,2,1,1], [0,3,1,1,1], [1,1,1,1,1], [2,1,1,1,1], [2,2,1,1,1], [3,1,1,1,1], ]


for i in range (len(l)):
	print ("{} \t\t {}".format(raw_list[i],l[i]))

print ("\n\n")

for i in range (len(l)):
	print ("{}".format(l[i]))

print ("\n\n")

for i in range (len(l_pow)):
	print ("{}".format(l_pow[i]))

print (len(l_pow))


