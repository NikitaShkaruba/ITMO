JAX-RS/Jersey application sample
========================================
* [JAX-RS API](https://java.net/projects/jax-rs-spec) — Java API for RESTful services
  * [Jersey](https://jersey.java.net/) — JAX-RS implementation
* [Gradle](http://www.gradle.org/) — Build Automation tool

On this project, an application server used in a development cycle is:

* [Jetty](http://www.eclipse.org/jetty/) — Servlet engine and HTTP server


### Prerequisites

* [JDK](http://www.oracle.com/technetwork/java/javase/downloads/index.html)


### Building and running

```
# Building WAR file
./gradlew --daemon war

# Running on Jetty for development
./gradlew --daemon jettyRun
```
