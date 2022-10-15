#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    # noms: mare-balena-vocabulary-3.txt, quijote-vocabulary-3.txt, dracula-vocabulary-4.txt
    # normal
    arraySoupSize = [10,    25,    50,   75,  100,  150,  200,  250,  500, 1000, 2500]
    arrayWords    = [500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 ]
    # balena canviar mida seleccio
    #arraySoupSize  = [300, 300, 300,  300, 300, 300, 300,  300, 300]
    #arrayWords     = [10,  50,  100,  300, 500, 750, 1000, 2500, 5000]
    for i in range (len(arraySoupSize)):
        outname = "JocsDeProva/balena_"+str(arraySoupSize[i])+"_"+str(arrayWords[i])+".inp"
        print("generating: " + outname)
        #os.wait(10)
        os.system("./generator.x " + str(arraySoupSize[i]) + " " + str(arrayWords[i]) + " " + " < ../mare-balena-vocabulary-3.txt > " + outname)

if __name__ == "__main__":
    main()
