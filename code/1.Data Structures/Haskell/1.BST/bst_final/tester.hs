{-
@author    :     rscalia
@date      :     Sun 21/03/2021

Questo componente rappresenta un driver adibito al test del modulo Tree.

-}

import Tree

main = do 
            --Test Inserimento
            putStrLn ("\nCostruzione Albero, inserisco rispettivamente [50,10,80,75] ")
            let x1 = buildTree 50
            let x2 = insertValue x1 10
            let x3 = insertValue x2 80
            let x4 = insertValue x3 75


            --Test Conformità Albero rispetto ai BST
            putStrLn ("\nVerifico se l'Albero creato è un SearchTree ")
            print (isSearchT x4)


            --Test Ricerca nell'Albero
            putStrLn ("\nCerco 75 Nell'albero: ")
            print (search x4 75)

            putStrLn ("\nCerco 100 Nell'albero: ")
            print (search x4 180)


            --Visite Albero
            putStrLn ("\nVisita InOrder Albero: ")
            print(inOrder x4)

            putStrLn ("\nVisita PreOrder Albero: ")
            print(preOrder x4)

            putStrLn ("\nVisita PostOrder Albero: ")
            print(postOrder x4)


            --Test Cancellazione Nodo dall'Albero
            putStrLn ("\nCancello 80 dall'albero e lo ristampo utilizzando l'inOrder")
            let  x5 = deleteValue x4 80
            print (inOrder x5)


            --Test Calcolo Altezza dall'Albero
            putStrLn ("\nCalcolo Altezza dall'Albero")
            let  x6 = treeHeightCompute x5
            print (x6)


            --Test Prelievo Nodo Radice 
            putStrLn ("\nLa radice dell'Albero è")
            let  x7 = getRoot x5
            print (x7)


            --Test Albero Bilanciato 1
            putStrLn ("\nTest Albero Bilanciato sull'Albero Attuale")
            let  x8 = isBalanced x5
            print (x8)


            --Test Albero Bilanciato 2
            putStrLn ("\nTest Albero Bilanciato sull'Albero INIZIALE [50,10,80,75]")
            let  x9 = isBalanced x4
            print (x9)


            --Test Eguaglianza Alberi
            putStrLn ("\nTest Eguaglianza fra Albero Iniziale [50,10,80,75] e Albero Attuale [10,75,80]")
            let z1 = (x4 == x5)
            putStrLn (boolToString z1)


            --Test se l'Albero Attuale è Maggiore dell'Albero Iniziale
            putStrLn ("\nTest Albero Attuale [10,50,75] MAGGIORE Albero Iniziale [50,10,80,75] ")
            let z2 = (x5 > x4)
            putStrLn (boolToString z2)


            --Test Massimo fra Albero Iniziale e Albero Attuale
            putStrLn ("\nTest Massimo fra Albero Iniziale [50,10,80,75] e Albero Attuale [10,50,75]")
            let z3 = max x4 x5
            putStrLn (show z3)


            --Test Albero più Grande di una Lista di Alberi
            let z4 = buildTree 180
            let z5 = insertValue z4 300
            let z6 = insertValue z5 150 

            let q3 = buildTree 1500

            let h1 = buildTree 2
            let h3 = insertValue h1 200

            let ls = [z6]++[q3]++[h3]

            putStrLn ("\nTest Massimo Albero di una Lista: [ T1: "++(show z6)++" , T2:"++(show q3)++" , T3:"++(show h3)++" ]")
            let bigTrIdx = biggestTree ls
            putStrLn ("\t-> Il più grande albero è l'albero numero "++(show bigTrIdx))


            --Sort lista di Alberi
            putStrLn ("\t-> Lista di Alberi Ordinata: "++(show (quicksort ls)))           