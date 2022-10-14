#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    for i in range (0,11):
        outname = "JocsDeProva/quijote_size"+str(i*100)+".inp"
        print("generating: " + outname)
        os.system("./generator.x " + str(i*100) + " " + str(i*50) + " " + " < ../quijote-vocabulary-3.txt > " + outname)

if __name__ == "__main__":
    main()
