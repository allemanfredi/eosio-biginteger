#ifndef __EOS_MEM_WRAPPER_H__
#define __EOS_MEM_WRAPPER_H__

#include <stdlib.h>

void* operator new (unsigned int size);
void* operator new[] (unsigned int size);
void operator delete (void* ptr);
void operator delete[] (void* ptr);
#endif