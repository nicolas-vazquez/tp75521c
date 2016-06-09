#Cmake based project

## Installations steps ##

From AppServer folder do:

Run install script:

```
sudo ./install.sh
```

## Build steps ##

**Generate make file with cmake:**

```
 cd build
 sudo cmake ..
```

**Run make:** (This will add app and tests executables)

```
sudo make
```

**Run app:** 

```
./appServer
```


## Run tests ##

From build folder:

```
ctest
```

## Run functional tests ##

Install Python, PIP and requests module

```
sudo apt-get install python2.7
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
sudo pip install requests
```

Run functional tests
```
cd functionalTests/
python restTester.py
```

## Run with Docker ##


With Docker installed and from repository root.

Build Docker container:

```
 sudo docker build -t appserver/ubuntu:14.04 .
```

Run Docker container:

```
 sudo docker run -t -i -p 127.0.0.1:8083:8083 appserver/ubuntu:14.04v3 /bin/bash
```

This will redirect you to container prompt at build folder, then run app:


```
./appServer
```










[![Build Status](https://travis-ci.org/nicolas-vazquez/tp75521c.svg?branch=develop)](https://travis-ci.org/nicolas-vazquez/tp75521c)
