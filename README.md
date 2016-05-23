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

[![Build Status](https://travis-ci.org/nicolas-vazquez/tp75521c.svg?branch=develop)](https://travis-ci.org/nicolas-vazquez/tp75521c)
