#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <vector>

constexpr int M = 16;

struct Dado
{
	unsigned int tempo;
	int chave;
};

struct THash
{
	std::vector<Dado> dado;
	bool acerto;
};

//Preenche todos os valores da chave com -1, que seria um "null", pois um endereco nunca vai ser negativo
//Preenche o tempo com o maior valor de um unsigned int
void inicializa_tabela(THash &h, int qtdEnderecosCache)
{
	for (int j = 0; j < qtdEnderecosCache; j++)
	{
		Dado dado = Dado();
		dado.chave = -1;
		dado.tempo = 4294967295;

		h.dado.push_back(dado);
	}
}

int hash(int chave, int tamCache)
{
	return chave % tamCache;
}

//Retorna a posicao que passou do tempo limite da cache
int LRU(std::vector<THash> h, int pos, int tempoLimite, int qtdEnderecosCache)
{
	int maiorTempo = h[pos].dado[0].tempo, retorno = 0;
	if (maiorTempo > tempoLimite)
		return 0;

	for (int i = 1; i < qtdEnderecosCache; i++)
	{
		if (h[pos].dado[i].tempo > tempoLimite)
			return i;

		else if (h[pos].dado[i].tempo > maiorTempo)
		{
			maiorTempo = h[pos].dado[i].tempo;
			retorno = i;
		}
	}
	return retorno;
}

void insere(std::vector<THash> &h, int chave, int tempoLimite, int tamCache, int qtdEnderecosCache)
{
	int pos = hash(chave, tamCache);

	bool saida = false;

	//Verifica se a chave ja existe, caso sim, eh um acerto
	for (int i = 0; i < qtdEnderecosCache; i++)
	{
		if (h[pos].dado[i].chave == chave)
		{
			h[pos].acerto = true;
			h[pos].dado[i].tempo = 0;
			saida = true;
		}
	}

	//Verifica se tem um espaco vago, caso nao, chama o LRU
	if (!saida)
	{
		for (int i = 0; i < qtdEnderecosCache; i++)
		{
			if (h[pos].dado[i].chave == -1)
			{
				h[pos].dado[i].chave = chave;
				saida = true;
				break;
			}
		}

		if (!saida)
		{
			int lru = LRU(h, pos, tempoLimite, qtdEnderecosCache);
			h[pos].dado[lru].chave = chave;
			h[pos].dado[lru].tempo = 0;
		}

		h[pos].acerto = false;
	}

	for (int i = 0; i < tamCache; i++)
		for (int j = 0; j < qtdEnderecosCache; j++)
		{
			if (h[i].dado[j].chave != -1)
				h[i].dado[j].tempo++;
		}
	//h[pos].dado[i].chave = chave;
}

//Procura em qual endereco esta a chave
int procura(THash h, int chave, int qtdEnderecosCache)
{
	for (int i = 0; i < qtdEnderecosCache; i++)
		if (h.dado[i].chave == chave)
			return i;
	return -1;
}

#endif // HASH_H
