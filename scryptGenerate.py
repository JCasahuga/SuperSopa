#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    for i in range (2,11):
        outname = "JocsDeProva/quijote_size"+str(i*5)+".inp"
        print("generating: " + outname)
        os.system("./generator.x " + str(i*5) + " < ../quijote-vocabulary-3.txt > " + outname)

if __name__ == "__main__":
    main()
