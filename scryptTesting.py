#Scrypt per testing

import subprocess
import os
from os import listdir
from os.path import isfile, join
import subprocess

def system_call(command):
    #print(command)
    p = subprocess.Popen([command], stdout=subprocess.PIPE, shell=True)
    return p.stdout.read()

def get_average(number, path, file):
    result = str(system_call("./program.x " + number + " < " + path + "/" + file))
    #print(result)
    split = result.split()
    return int(split[-2])

def main():
    os.system("make -j")
    path = os.getcwd() + "/JocsDeProva/"
    numberOfReps = 5
    print(path)
    files = [f for f in listdir(path) if isfile(join(path, f))]
    for f in files:
        print("Testing input: " + f)
        
        average = 0
        for i in range (0, numberOfReps):
            average += (get_average("1", path, f)/numberOfReps)
        print("Sorted vector time:  " + str(average) + " ms")

        average = 0
        for i in range (0, numberOfReps):
            average += (get_average("2", path, f)/numberOfReps)
        print("Trie time:           " + str(average) + " ms")
        
        average = 0
        for i in range (0, numberOfReps):
            average += (get_average("3", path, f)/numberOfReps)
        print("Bloom filter time:   " + str(average) + " ms")

        average = 0
        for i in range (0, numberOfReps):
            average += (get_average("4", path, f)/numberOfReps)
        print("Double hashing time: " + str(average) + " ms")
        print("")


if __name__ == "__main__":
    main()
