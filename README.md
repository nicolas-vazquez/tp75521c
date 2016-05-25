#Cmake based project

## Installations steps ##

Run install.sh in repository root:

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

Run tests
```
cd functionalTests/
python restTester.py
```


[![Build Status](https://travis-ci.org/nicolas-vazquez/tp75521c.svg?branch=develop)](https://travis-ci.org/nicolas-vazquez/tp75521c)
