[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9386133&assignment_repo_type=AssignmentRepo)


# simple blockchain in C

This is assignment 4

## Compile & Run

* sh is for ubuntu command line (Bash)
* if you are ios system, you need to have install openssl first to have crypto.h, sha.h library
```sh
# Compile
gcc src/blockchain.c src/hash.c inc/hash.h -o bin/blockchain -lcrypto
# Run
./bin/blockchain
```
