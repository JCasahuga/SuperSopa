#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    arraySoupSize = [10, 25, 50, 75, 100, 150, 200, 250, 500, 1000, 2500]
    arrayWords    = [16, 32, 64, 128, 128, 128, 128, 128, 256, 256, 256]
    for i in range (len(arraySoupSize)):
        outname = "JocsDeProva/balena_"+str(arraySoupSize[i])+"_"+str(arrayWords[i])+".inp"
        print("generating: " + outname)
        os.system("./generator.x " + str(arraySoupSize[i]) + " " + str(arrayWords[i]) + " " + " < ../mare-balena-vocabulary-3.txt > " + outname)

if __name__ == "__main__":
    main()
