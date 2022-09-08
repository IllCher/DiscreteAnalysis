import string
import random
import sys

f = open('cmake-build-debug/test.txt', 'w')
i = 0
while i < 100:
    f.write(str(random.randint(1, 99)) + ' ' + str(random.randint(1, 99))  + '\n')
    i = i + 1
f.write('\n')
j = 0
while j < 10000:
    f.write(str(random.randint(1, 99)) + ' ' + str(random.randint(1, 99)) + ' ' + str(random.randint(1, 99)) + ' ' + str(random.randint(1, 99)) + ' ' + str(random.randint(1, 99)) + ' '+ str(random.randint(1, 99)) +'\n')
    j = j + 1
f.close()