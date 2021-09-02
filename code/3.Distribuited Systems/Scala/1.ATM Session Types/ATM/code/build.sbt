// Kludge to avoid building an empty .jar for the root project
Keys.`package` := {
    (Keys.`package` in (lchannels, Compile)).value
    (Keys.`package` in (atm, Compile)).value
}

lazy val commonSettings = Seq(
  version := "0.0.3",
  scalaVersion := "2.12.7",
  scalacOptions ++= Seq(
    "-target:jvm-1.8", "-unchecked", "-feature", "-Ywarn-unused-import" // "-deprecation"
  ),
  // ScalaDoc setup
  autoAPIMappings := true,
  scalacOptions in (Compile,doc) ++= Seq(
    "-no-link-warnings" // Workaround for ScalaDoc @throws links issues
  )
)

lazy val lchannels = (project in file("lchannels")).
  settings(commonSettings: _*).
  settings(
    name := "lchannels",

    libraryDependencies ++= Seq(
      "com.typesafe.akka" %% "akka-typed" % "2.5.0",
      "com.typesafe.akka" %% "akka-remote" % "2.5.0"
    )
  )

lazy val atm = (project in file("atm")).
  dependsOn(lchannels).
  settings(commonSettings: _*).
  settings(
    name := "source",

    libraryDependencies ++= Seq(
      "org.slf4j" % "slf4j-simple" % "1.7.25",
      "com.typesafe.scala-logging" %% "scala-logging" % "3.5.0"
    )
  )
