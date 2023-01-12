#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../inc/hash.h"

//SHA256(src,size,dest)
//src and dest are of type unsigned char *

FILE *block;
struct block{
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    int blockData;
    struct block *link;
}*head;
void addBlock(int);
void verifyChain();
void alterNthBlock(int,int);
void hackChain();
unsigned char* toString(struct block);
void printBlock(struct block*);
void printAllBlocks();
void addBlock(int data){
    if(head==NULL){
        head=malloc(sizeof(struct block));
        SHA256("",sizeof(""),head->prevHash);
        head->blockData=data;
        return;
    }
    struct block *currentBlock=head;
    while(currentBlock->link)
        currentBlock=currentBlock->link;
    struct block *newBlock=malloc(sizeof(struct block));
    currentBlock->link=newBlock;
    newBlock->blockData=data;
    SHA256(toString(*currentBlock),sizeof(*currentBlock),newBlock->prevHash);       
}

void verifyChain(){
    if(head==NULL){
        printf("BlockChain is empty! try again after adding some blocks!\n");
        return;
    }
    struct block *curr=head->link, *prev=head;
    int count=1;
    while(curr){
        printf("%d\t[%d]\t", count++, curr->blockData);
        hashPrinter(SHA256(toString(*prev),sizeof(*prev),NULL),SHA256_DIGEST_LENGTH);
        printf(" - ");
        hashPrinter(curr->prevHash,SHA256_DIGEST_LENGTH);
        if(hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash))
            printf("\tVerified!\n");
        else
            printf("\tVerification Failed\n");
            prev=curr;
            curr=curr->link;
    }
}

void alterNthBlock(int n, int newData){
    struct block *curr=head;
    if(curr==NULL){
        printf("Nth block does not exist!!\n");
        return;
    }
    int count=0;
    while(count!=n){
        if(curr->link==NULL && count!=n){
            printf("Nth block does not exist!!\n");
            return;
        }
        else if(count==n)
            break;
        curr=curr->link;
        count++;
    }
    printf("Before: ");
        printBlock(curr);
    curr->blockData=newData;
    printf("After: ");
        printBlock(curr);
    //printf("\n");
}

void hackChain(){
    struct block *curr=head, *prev;
    if(curr==NULL){
        printf("BlockChain is empty!");
        return;
    }
    while(1){
        prev=curr;
        curr=curr->link;
        if(curr==NULL)
            return;
        if(!hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash)){
            hashPrinter(
                SHA256(toString(*prev),sizeof(*prev),curr->prevHash),
                SHA256_DIGEST_LENGTH
            );
            printf("\n");
        }
    }
}

unsigned char* toString(struct block b){
    unsigned char *str=malloc(sizeof(unsigned char)*sizeof(b));
    memcpy(str, &b,sizeof(b));
    return str;
}


void printBlock(struct block *b){
    printf("%p\t", b);
    hashPrinter(b->prevHash, sizeof(b->prevHash));
    printf("\t[%d]\t", b->blockData);
    printf("%p\n", b->link);
}
void printAllBlocks(){
    struct block *curr=head;
    int count=0;
    
    while(curr){
        printBlock(curr);
        curr=curr->link;
    }
}
int main(){
    int c,n,r;
    while(1){
        printf("1)add_Block\n2)add n random blocks\n3)alter_Nth_Block\n4)print_All_Blocks\n5)verify_Chain\n6)hack_Chain\n");
        printf("你想要使用第幾個功能？＾＿＾： ");
        scanf("%d",&c);
        switch(c){
            case 1:
                printf("輸入你想要加入的data: ");
                scanf("%d",&n);
                addBlock(n);
                break;
            case 2:
                printf("你要加幾個block?: ");
                scanf("%d",&n);
                block=fopen("blockchainnnnn!.txt","w+");
                for(int i=0;i<n;i++){
                    r=rand()%(n*10);
                    printf("Entering[%d]: %d\n",i+1, r);
                    fprintf(block,"Entering[%d]: %d\n", i+1,r);
                    addBlock(r);
                }
                fclose(block);
                break;
            case 3:
                printf("你想要調整第幾個block?: ");
                scanf("%d",&n);
                printf("輸入你想變成的data: ");
                scanf("%d",&r);
                alterNthBlock(n,r);
                break;
            case 4:
                printAllBlocks();
                break;
            case 5:
                verifyChain();
                break;
            case 6:
                hackChain();
                break;
            default:
                printf("無此選項！\n");
                break;
        }
        printf("\n");
    }
    return 0;
}

//gcc blockchain.c -o blockchain -lcrypto
//./blockchain.c.o