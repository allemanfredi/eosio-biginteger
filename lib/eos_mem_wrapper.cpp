/** 
 * BigInteger for EOS.IO smart contract v1.6 by allemanfredi.
 */
#include <stdlib.h>

void* operator new (unsigned int size){
    return malloc( size );
}

void* operator new[] (unsigned int size){
    return malloc( size );
}

void operator delete (void* ptr){
    free( ptr);
}

void operator delete[] (void* ptr) {
    free( ptr);
}