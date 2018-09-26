#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>

constexpr int M = 16;

struct THash{
    int chave;
    bool acerto;
};

//Preenche todos os valores da chave com -1, que seria um "null", pois um endereco nunca vai ser negativo
void inicializa_tabela(THash t[]){
    for (int i = 0; i < M; i++)
        t[i].chave = -1;
}

int hash(int x){
    return x % M;
}

void insere(THash t[], int chave){
	int pos = hash(chave);

    if(t[pos].chave == chave)
        t[pos].acerto = true;
    else
        t[pos].acerto = false;

    t[pos].chave = chave;
}

#endif // HASH_H
