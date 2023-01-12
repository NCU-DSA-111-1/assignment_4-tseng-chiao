#ifndef __HASH_H__
#define __HASH_H__
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "openssl/crypto.h"
#include "openssl/sha.h"

void hashPrinter(unsigned char*, int);
int hashCompare(unsigned char*, unsigned char*);

#endif 
