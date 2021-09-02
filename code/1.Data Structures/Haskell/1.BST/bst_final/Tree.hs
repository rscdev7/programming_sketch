{-
@author    :     rscalia
@date      :     Sun 21/03/2021

Questo modulo implementa un Albero Binario di Ricerca (BST) avente etichette aventi Tipo di Dato Generico.

Inoltre, il modulo supporta le seguenti operazioni:

    1) Inserimento 
    2) Cancellazione
    3) Ricerca
    4) Check Correttezza Albero rispetto al Criterio di Ricerca
    5) Visita inOrder/preOrder/postOrder dell'Albero
    6) Calcolo Altezza Albero
    7) Prelievo Radice dall'Albero
    8) Check Bilanciatezza Albero
    9) Derivazione Manuale Data Type rispetto alle Type Class Predefinite Ord/Eq/Show
    10) Calcolo Albero più grande in una lista di Alberi
    11) Sort di una Lista di Alberi attraverso il QuickSort

-}


module Tree where
import Data.Set
import Data.List
import Prelude

--Definizione Data Type
data BinaryTree a   = Empty | Leaf a | MkTree a (BinaryTree a) (BinaryTree a) 


--Aggiunta BST alla Type Class "Predefinita" EQ
instance Eq a => Eq (BinaryTree a) where
   t1 == t2 = inOrder t1 == inOrder t2
   t1 /= t2 = not (inOrder t1 == inOrder t2)


--Aggiunta BST alla Type Class "Predefinita" Ord
instance Ord a =>  Ord (BinaryTree a) where
    min t1 t2       | (minT t1 <= minT t2)                                  = t1
                    | otherwise                                             = t2
    
    max t1 t2       | (maxT t1 >= maxT t2)                                  = t1
                    | otherwise                                             = t2
    
    t1 <= t2        | ( length(inOrder t1)  <= length(inOrder t2) )         = True
                    | otherwise                                             = False

    t1 >= t2        | (length(inOrder t1) >= length(inOrder t2))            = True
                    | otherwise                                             = False

    compare t1 t2   | (length(inOrder t1) == length(inOrder t2))            = EQ
                    | (length(inOrder t1) < length(inOrder t2))             = LT
                    | (length(inOrder t1) > length(inOrder t2))             = GT 


--Aggiunta BST alla Type Class "Predefinita" Show
instance (Show a) => Show (BinaryTree a) where
   show x = show(inOrder x)


--Conversion Booleano a Stringa
boolToString :: Bool -> String
boolToString True   = "True"
boolToString False  = "False" 
                  

--Costruzione Albero
buildTree root                                            = Leaf root


-- Inserimento elemento nell'albero
insertValue Empty v                                       = Leaf v
insertValue (Leaf root) v                   | (v < root)  = MkTree root (Leaf v) Empty 
                                            | (v == root) = Leaf root
                                            | (v > root)  = MkTree root Empty (Leaf v) 

insertValue (MkTree root sx dx) v           | (v < root)  = MkTree root (insertValue sx v) dx 
                                            | (v == root) = MkTree root sx dx
                                            | (v > root)  = MkTree root sx (insertValue dx v)

-- Calcellazione elemento dall'albero
minT (Leaf m)                                             = m
minT (MkTree m Empty Empty)                               = m
minT (MkTree m t1 Empty)                                  = min m (minT t1)
minT (MkTree m Empty t2)                                  = min m (minT t2)
minT (MkTree m t1 t2)                                     = min m (min (minT t1) (minT t2))

deleteRoot (MkTree root Empty dx)                         = dx
deleteRoot (MkTree root sx Empty)                         = sx
deleteRoot (MkTree root sx (Leaf l))                      = MkTree l sx Empty
deleteRoot (MkTree root sx dx)                            = MkTree (minT dx) sx (deleteValue dx (minT dx)) 


deleteValue Empty v                                       = Empty
 
deleteValue (Leaf root) v                   | (v < root)  = Leaf root 
                                            | (v == root) = Empty
                                            | (v > root)  = Leaf root

deleteValue (MkTree root sx dx) v           | (v < root)  = MkTree root (deleteValue sx v) dx 
                                            | (v == root) = deleteRoot (MkTree root sx dx)
                                            | (v > root)  = MkTree root sx (deleteValue dx v)

-- Ricerca nell'albero
search Empty v                                  = False
search (Leaf root) v            | (root == v)   = True
                                | otherwise     = False

search (MkTree root sx dx) v    | (v < root)    = search sx v 
                                | (v == root)   = True 
                                | (v > root)    = search dx v

-- Funzione per Controllare se un Albero è un Search Tree
maxT :: Ord a => BinaryTree a -> a
maxT (Leaf m)                                             = m
maxT (MkTree m Empty Empty)                               = m
maxT (MkTree m t1 Empty)                                  = max m (maxT t1)
maxT (MkTree m Empty t2)                                  = max m (maxT t2)
maxT (MkTree m t1 t2)                                     = max m (max (maxT t1) (maxT t2))


isSearchT Empty             = True
isSearchT (Leaf m)          = True
isSearchT (MkTree m t1 t2)  = m>=(maxT t1) && m<=(maxT t2)


-- Visita InOrder dell'Albero
inOrder Empty                              = []
inOrder (Leaf m)                           = [m]
inOrder (MkTree root sx dx)                = inOrder sx ++ [root] ++ inOrder dx

-- Visita PostOrder dell'Albero
postOrder Empty                            = []
postOrder (Leaf m)                         = [m]
postOrder (MkTree root sx dx)              = postOrder sx ++ postOrder dx ++ [root]

-- Visita PreOrder dell'Albero
preOrder Empty                             = []
preOrder (Leaf m)                          = [m]
preOrder (MkTree root sx dx)               = [root] ++ preOrder sx ++ preOrder dx 


--Altezza Albero
height_counter                                                              = 0

height_cp_wrapper :: Ord a => BinaryTree a -> Integer -> Integer
height_cp_wrapper (Leaf m) height_counter                                   = height_counter
height_cp_wrapper (MkTree m Empty Empty) height_counter                     = height_counter
height_cp_wrapper (MkTree m (Leaf t1) Empty) height_counter                 = height_counter + 1
height_cp_wrapper (MkTree m Empty (Leaf t2)) height_counter                 = height_counter + 1
height_cp_wrapper (MkTree m (Leaf t1) (Leaf t2)) height_counter             = height_counter + 1
height_cp_wrapper (MkTree m sx dx) height_counter                           = max (height_cp_wrapper sx height_counter+1) (height_cp_wrapper dx height_counter+1)

treeHeightCompute :: Ord a => BinaryTree a -> Integer
treeHeightCompute t                                                         = height_cp_wrapper t height_counter


--Metodo che restituisce la radice dell'Albero
getRoot (Leaf v)                    = v
getRoot (MkTree root sx dx)         = root


--Verifica se l'albero è bilanciato
isBalanced :: Ord a => BinaryTree a -> Bool
isBalanced (Leaf m)                                    = True
isBalanced (MkTree m Empty Empty)                      = True
isBalanced (MkTree m (Leaf t1) Empty)                  = False
isBalanced (MkTree m Empty (Leaf t2))                  = False
isBalanced (MkTree m (Leaf t1) (Leaf t2))              = True
isBalanced (MkTree m sx dx)                            = size ( fromList( 
                                                
                                                [(treeHeightCompute sx)]++[(treeHeightCompute dx)] 
                                                
                                                ) ) == 1


--Metodo che calcola l'Albero più grande in una lista di Alberi
indexedList ls            = zip ls [1 ..]
tree2max ls               = Prelude.map maxT ls


maxTail currentMax []     = Prelude.snd currentMax
maxTail (m , n) (p:ps)      | m < (fst p) = maxTail p ps
                            | otherwise   = maxTail (m, n) ps
maxLTT (x:xs)             = maxTail x xs


biggestTree ls            = maxLTT ( ( indexedList ( tree2max ls ) ) )


--Implementazione QuickSort per lista di Alberi
quicksort :: Ord a => [BinaryTree a] -> [BinaryTree a]
quicksort []     = []
quicksort (p:xs) = (quicksort lesser) ++ [p] ++ (quicksort greater)
                           where
                              lesser  = Prelude.filter (< p) xs
                              greater = Prelude.filter (>= p) xs