#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 10 15:20:32 2021

@author: Giovanni Russo
Es. 15_6_21_4
"""

import math

def f(x):
    y = math.exp(math.sin(math.pi*2*x))
    return y

for p in range(2,6):
    N = 2**p
    T = (f(0.0)+f(1.0))/2.0
    h = 1.0/N
    for i in range(N-1):
        T = T + f((i+1)*h)
    T = T*h
    print('p = ', p, ' T = ', T)


# Commento ai risultati
# L'esecuzione del problema prodice i seguenti risultati
# p =  2  T =  1.2715403174076219
# p =  3  T =  1.2660660769644891
# p =  4  T =  1.2660658777520089
# p =  5  T =  1.2660658777520082

# E' evidente una converhenza estremmete rapida. Questo è dovuto al fatto che la funzione
# f è regolare, periodica ed integrata su un periodo. In questi casi la formula dei trapezi 
# ha accuratezza spettrale, quindi bastano pochi punti per ottenere un errore confrontabile
# con la precisione di macchina.  