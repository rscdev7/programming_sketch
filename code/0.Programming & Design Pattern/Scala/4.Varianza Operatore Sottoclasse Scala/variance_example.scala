//HOW-TO-RUN: sbt run

// SET                                  = { Animale, Gatto , Cane,  }
// RELAZIONE_BDI_SOTTOTIPO              = {Gatto,Cane} <: Animale 
// CONTENITORI                          = 
//                                        1) COVARIANZA     --->  List[Gatto]              <: List[Animale]
//                                        2) CONTRAVARIANZA --->  Printer[Animale]         <: Printer[Gatto] 
//                                        3) INVARIANZA     --->     Container[Gatto]  NOT(<:) Container[Cane]
//                                                                && Container[Cane]   NOT(<:) Container[Gatto]


import scala.math._
import scala.sys._
import scala.io._

import scala.collection.mutable._

import scala.util.matching._

import scala.collection.parallel._
import scala.concurrent._

import scala.reflect._



//SET DATA - "extends"" implicit declares subtype relationship among classes
abstract class Animal {
  def name: String
}
case class Cat(name: String) extends Animal
case class Dog(name: String) extends Animal


//CONTRAVARIANT-CONTAINER
abstract class Printer[-A] {
  def print(value: A): Unit
}

class AnimalPrinter extends Printer[Animal] {
  def print(animal: Animal): Unit =
    println("The animal's name is: " + animal.name)
}

class CatPrinter extends Printer[Cat] {
  def print(cat: Cat): Unit =
    println("The cat's name is: " + cat.name)
}



object Main extends App {

        //Functions
        def printAnimalNames(animals: List[Animal]): Unit =animals.foreach {animal => println(animal.name)}
        def printMyCat(printer: Printer[Cat], cat: Cat): Unit = printer.print(cat)


        //Covariance Example
        val cats: List[Cat] = List(Cat("Whiskers"), Cat("Tom"))
        val dogs: List[Dog] = List(Dog("Fido"), Dog("Rex"))

        // prints: Whiskers, Tom
        printAnimalNames(cats)

        // prints: Fido, Rex
        printAnimalNames(dogs)


        //Contravariance Example
        val catPrinter: Printer[Cat] = new CatPrinter
        val animalPrinter: Printer[Animal] = new AnimalPrinter

        printMyCat(catPrinter, Cat("Boots"))
        printMyCat(animalPrinter, Cat("Boots"))

}
