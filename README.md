# CONVERTER DOCUMENT
## Introduction
### origin version: use shift and or operation to replace addition and multiplication to raise the speed (k <= 64)
### v1.0 verison: use system function strtol to transform the number(k <= 64)
### v2.0 version: use the int array to represent the big number which is longer than 64 bits.( k  no limits ,but when k >= 100000,the time is over 70s)
### v3.0 version: use the multithreading to acclerate the computation process
## Operation
1. build all binary files
```
make all
```
2. run test
```
make test
```
3. clean
```
make clean
```

