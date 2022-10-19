#Script generador de inputs
import subprocess
import os

def main():
    print("Script generador de inputs! :)")
    arraySoupSize = [50, 100, 150, 200, 250, 500, 750, 100, 1500, 2000, 2500, 3000, 4000, 5000]
    arrayWords    = [500,500, 500, 500, 500, 500, 500, 500, 500,  500,  500,  500, 500, 500]
    diccionari    = "quijote-vocabulary-3"                                      #introduir nom del diccionari sense l'extensió .txt.
    for i in range (len(arraySoupSize)):
        outname = "JocsDeProva/"+diccionari+"_"+str(arraySoupSize[i])+"_"+str(arrayWords[i])+".inp"
        print("generating: " + outname)
        cmd = "./generator.x " + str(arraySoupSize[i]) + " " + str(arrayWords[i]) + " " + " < Diccionaris/" + diccionari +".txt"+ " > " + outname
        print(cmd)
        os.system(cmd)

if __name__ == "__main__":
    main()
