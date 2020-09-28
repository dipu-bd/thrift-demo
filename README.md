# Thrift Demo

## Setup

- Either, install thrift 0.13.0:

```
# CentOS
$ sudo yum install thrift-devel

# Ubuntu
$ sudo apt-get install libboost-dev libthrift-dev thrift-compiler
```

- Or, build thrift 0.13.0:

```
$ wget -c https://downloads.apache.org/thrift/0.13.0/thrift-0.13.0.tar.gz
$ tar -zxvf thrift-0.13.0.tar.gz
$ cd thrift-0.13.0
$ ./configure
$ make
$ sudo make install
```

## Build and run

- Build application

```
$ ./gradlew clean build distTar
```

- Run application

```
# Run server
$ ./src/main/dist/exec/server

# Run client
$ ./gradlew run
```
