#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    # normal
    #arraySoupSize = [10, 25, 50, 75, 100, 150, 200, 250, 500, 1000, 2500]
    #arrayWords    = [16, 32, 64, 128, 128, 128, 128, 128, 256, 256, 256]
    # balena canviar mida seleccio
    #arraySoupSize  = [300, 300, 300,  300, 300, 300, 300,  300, 300]
    #arrayWords     = [10,  50,  100,  300, 500, 750, 1000, 2500, 5000]
    # quijote canviar mida seleccio
    arraySoupSize  = [300,    300,   300]
    arrayWords     = [10000, 15000, 25000]
    for i in range (len(arraySoupSize)):
        outname = "JocsDeProva/quijote_"+str(arraySoupSize[i])+"_"+str(arrayWords[i])+".inp"
        print("generating: " + outname)
        #os.wait(10)
        os.system("./generator.x " + str(arraySoupSize[i]) + " " + str(arrayWords[i]) + " " + " < ../quijote-vocabulary-3.txt > " + outname)

if __name__ == "__main__":
    main()
