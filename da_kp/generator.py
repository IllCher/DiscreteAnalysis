import random
from random_word import RandomWords
from RandomWordGenerator import RandomWord
r = RandomWords()
rw = RandomWord(max_word_size=7,
                constant_word_size=False)
train_docs_number = 4
test_docs_number = 2
random_word_list1 = ['alpha','delta','omega','charlie','fight','charley']
random_word_list2 = ['i','look','at','you','and','suddenly']
class0 = 0
class1 = 0
with open('cmake-build-debug/test.txt', 'wt', encoding='utf8') as filehandle:
    filehandle.write(str(train_docs_number) + " " + str(test_docs_number))
    filehandle.write("\n")
    for i in range(train_docs_number):
        c = random.randint(0, 1)
        filehandle.write(str(c))
        filehandle.write("\n")
        if c == 0:
            for j in range(random.randint(1, 4)):
                filehandle.write(random.choice(random_word_list1) + " ")
            filehandle.write("\n")
            class0 += 1
        else:
            for j in range(random.randint(1, 4)):
                filehandle.write(random.choice(random_word_list2) + " ")
            filehandle.write("\n")
            class1 += 1
    for k in range(test_docs_number):
        for j in range(random.randint(1, 4)):
            filehandle.write(random.choice(random_word_list1) + " ")
        for j in range(random.randint(1, 4)):
            filehandle.write(random.choice(random_word_list2) + " ")
        filehandle.write("\n")

print(class0, class1)

