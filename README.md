# eosio-biginteger

Refactoring of [this repo](https://github.com/playerone-id/biginteger-for-eosio) to be compatible with EOSIO.cdt v1.6.

## Original Author

Matt McCutchen ( [C++ Big Integer Library](https://mattmccutchen.net/bigint/) ) 

## Added Features

* __`addmod(a,b,c)`__ => (a + b) % c
* __`submod(a,b,c)`__ => (a - b) % c
* __`mulmod(a,b,c)`__ => (a * b) % c
* __`divmod(a,b,c)`__ => (a / b) % c = ((a mod c) * (b^(-1) mod c)) mod c

## Use 

```c++
#include "BigIntegerLibrary.hpp" 
#include <eosio/eosio.hpp>
BigInteger a = 65536;  
print("a * a * a * a * a * a * a * a: ", ( a * a * a * a * a * a * a * a ) ); 
```

## Build 

```
eosio-cpp your_file_name.cpp eos_mem_wrapper.cpp BigInteger.cpp BigIntegerAlgorithms.cpp BigIntegerUtils.cpp BigUnsigned.cpp BigUnsignedInABase.cpp  -o your_file_name.wasm
```


