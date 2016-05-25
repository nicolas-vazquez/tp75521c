#Cmake based project

## Installations steps ##

Run install.sh in repository root:

```
#!bash

sudo ./install.sh
```

## Build steps ##

**Generate make file with cmake:**

```
#!bash
 cd build
 sudo cmake ..

```

**Run make:** (This will add app and tests executables)

```
#!bash

sudo make
```

**Run app:** 

```
#!bash

./appServer
```


## Run tests ##

From build folder:

```
#!bash

ctest
```

## Run funcional tests ##

Install Python, PIP and requests module

```
#!bash

sudo apt-get install python2.7
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
sudo pip install requests

```

Run tests
```
cd functionalTests/
python restTester.py
```


[![Build Status](https://travis-ci.org/nicolas-vazquez/tp75521c.svg?branch=develop)](https://travis-ci.org/nicolas-vazquez/tp75521c)
