#include "../inc/hash.h"

int hashCompare(unsigned char *str1, unsigned char *str2){
    for(int i=0;i<SHA_DIGEST_LENGTH;i++)
        if(str1[i]!=str2[i])
            return 0;
    return 1;
}
void hashPrinter(unsigned char hash[],int length){
    for(int i=0; i<length; i++)
        printf("%02x", hash[i]);
}
