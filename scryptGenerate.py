#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    # noms: mare-balena-vocabulary-3.txt, quijote-vocabulary-3.txt, dracula-vocabulary-4.txt
    # normal
    arraySoupSize = [10, 10, 10, 10, 10, 10, 10, 10]
    arrayWords    = [50, 100, 500, 1000,2500,5000,10000,20000]
    # balena canviar mida seleccio
    #arraySoupSize  = [300, 300, 300,  300, 300, 300, 300,  300, 300]
    #arrayWords     = [10,  50,  100,  300, 500, 750, 1000, 2500, 5000]
    for i in range (len(arraySoupSize)):
        outname = "ProvesDicc/dicc_"+str(arrayWords[i])+".inp"
        print("generating: " + outname)
        #os.wait(10)
        os.system("./generator.x " + str(arraySoupSize[i]) + " " + str(arrayWords[i]) + " " + " < ../dracula-vocabulary-4.txt > " + outname)

if __name__ == "__main__":
    main()
