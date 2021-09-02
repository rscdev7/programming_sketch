//Language Libraries
import scala.math._
import scala.sys._
import scala.io._

import scala.collection.mutable._

import scala.util.matching._

import scala.collection.parallel._
import scala.concurrent._

import scala.reflect._

import org.apache.spark.sql._

case class MatrixItem(row: Int, col:Int, value:Int)

object Main {

  def main(args: Array[String]): Unit = {

    val spark = SparkSession.builder.appName("Spark App Name").getOrCreate()
    import spark.implicits._


    //Lettura dati di Input
    val matrix1 = spark.read.textFile("hdfs://localhost:9000/dataset/matrix1.txt").map(_.split(",")).map(attributes => MatrixItem(attributes(0).toInt, attributes(1).toInt, attributes(2).toInt))
  .toDF("Riga", "Colonna", "Valore")

    val matrix2 = spark.read.textFile("hdfs://localhost:9000/dataset/matrix2.txt").map(_.split(",")).map(attributes => MatrixItem(attributes(0).toInt, attributes(1).toInt, attributes(2).toInt))
  .toDF("Riga", "Colonna", "Valore")

    matrix1.show()
    matrix2.show()    


    //Prima Map
    val matrix1MapData = matrix1.map (x => (x.getInt(0), "M",x.getInt(1),x.getInt(2))    ).toDF ("ID","A","C","V")

    val matrix2MapData = matrix2.map (x => (x.getInt(1), "N",x.getInt(0),x.getInt(2))   ).toDF ("ID","Appartenenza","Riga","Valore")

    matrix1MapData.show()
    matrix2MapData.show()

    //Aggregation
    val matrix1SQL = matrix1MapData.createOrReplaceTempView("m1SQL")
    val matrix2SQL = matrix2MapData.createOrReplaceTempView("m2SQL")
    
    val agg        = spark.sql ("SELECT m2SQL.Riga AS i, m1SQL.C AS j, m1SQL.V * m2SQL.Valore AS Item  FROM m1SQL NATURAL JOIN m2SQL ORDER BY i , j ASC ")

    agg.show(1000)

    val cv = agg.groupBy(agg.col("i"), agg.col("j")).sum("Item")
    cv.show()

    val fn = agg.createOrReplaceTempView("Red")

    val z = spark.sql ("SELECT i,j, SUM (Item) FROM Red GROUP BY i,j")
    z.show()

  }

}