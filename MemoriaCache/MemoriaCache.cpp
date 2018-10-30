#include <iostream>
#include <vector>
#include <sstream>
 

#include "menu.h"
#include "hash.h"

//Realiza a consistencia p/ que nao seja digitado valores que nao sejam numeros
//Recebe uma variavel para o valor ser salvo, x e y sao as coordenadas do cin
//Retorna true caso seja um inteiro, false caso não
void validacao(int &valor, int x, int y)
{
	bool saida;
	do
	{
		gotoxy(x, y);
		saida = false;
		std::string aux;
		textcolor(BRIGHTWHITE, BLACK);
		std::cin >> aux;
		textcolor(WHITE, BLACK);
		std::stringstream valid(aux);
		if (valid >> valor)
		{
			if (valor <= 0)
			{
				saida = false;
				gotoxy(x, y);
				std::cout << "                                    ";
				gotoxy(x, y + 2);
				textcolor(RED, BLACK);
				std::cout << "Erro! Inserir numeros maiores que zero!";
				textcolor(WHITE, BLACK);
			}
			else
				saida = true;
		}
		else
		{
			gotoxy(x, y);
			std::cout << "                                    ";
			gotoxy(x, y + 1);
			textcolor(RED, BLACK);
			std::cout << "Erro! Inserir apenas numeros!";
			textcolor(WHITE, BLACK);
		}
	} while (!saida);
}

//Calcula o expoente
int expoente(int x) {
	int exp = 1;

	while (pow(2, exp) < x) {
		exp++;
	}

	return exp;
}

//Mostra os dados da cache na tela
void mostra_cache(std::vector<THash> memCache, int tamCache, int qtdEndederecosCache, int tempoLimite)
{
	int x = 36, y;
	for (int i = 0; i < qtdEndederecosCache; i++)
	{
		y = 9;
		for (int j = 0; j < tamCache; j++)
		{
			//Printa o bit de validade
			gotoxy(x, y);
			if (memCache[j].dado[i].validade)
			{
				textcolor(GREEN, BLACK);
				std::cout << "1";
			}
			else
			{
				textcolor(RED, BLACK);
				std::cout << "0";
			}
			textcolor(WHITE, BLACK);

			//Printa o tempo
			x += 2;
			gotoxy(x, y);
			std::cout << "  ";
			gotoxy(x, y);
			if (memCache[j].dado[i].tempo == 4294967295)
			{
				textcolor(GRAY, BLACK);
				std::cout << "-";
			}
			else
			{
				if (memCache[j].dado[i].tempo > tempoLimite)
					textcolor(LIGHTRED, BLACK);
				else
					textcolor(LIGHTYELLOW, BLACK);
				std::cout << memCache[j].dado[i].tempo;
			}
			textcolor(WHITE, BLACK);

			//Printa o dado
			x += 6;
			if (memCache[j].dado[i].chave != -1)
			{
				gotoxy(x, y);
				std::cout << "          ";
				gotoxy(x, y);
				textcolor(BRIGHTWHITE, BLACK);
				std::cout << memCache[j].dado[i].chave;
				textcolor(WHITE, BLACK);
			}
			else {
				gotoxy(x, y);
				textcolor(GRAY, BLACK);
				std::cout << "-";
				textcolor(WHITE, BLACK);
			}
			x -= 8;
			y++;
		}
		x += 17;
	}
}

int main()
{
	cabecalho();

	int tamCache;
	gotoxy(0, 5);
	std::cout << "Entre com o tamanho da memoria cache:";
	validacao(tamCache, 0, 6);

	int qtdEnderecosCache;
	gotoxy(0, 9);
	std::cout << "Entre com o grau de associatividade:";
	validacao(qtdEnderecosCache, 0, 10);

	std::vector<THash> memCache;
	for (int i = 0; i < tamCache; i++)
	{
		THash aux = THash();
		inicializa_tabela(aux, qtdEnderecosCache);
		memCache.push_back(aux);
	}

	int tempoLimite;
	gotoxy(0, 13);
	std::cout << "Entre com o tempo limite para variaveis na cache:";
	validacao(tempoLimite, 0, 14);

	int qtdEndereco;
	gotoxy(0, 17);
	std::cout << "Entre com a quantidade de enderecos para salvar:";
	validacao(qtdEndereco, 0, 18);

	//Calculo de custo de tag
	//custo= w*(tamanho da cache(qtd de linhas)/w)*(32-n-m-k)
	/*
		no caso
		w=qtdEnderecosCache
		tamanho=tamCache
		k=2 constante
		m=indice para selecionar uma word, no caso so vamos utilizar 1 word por bloco
	*/
	double custo;
	int m = 1, k = 2;
	custo = qtdEnderecosCache * (tamCache / qtdEnderecosCache) * (32 - expoente(tamCache) - m - k);

	//Preenche a tabela
	int y = 8;
	system("cls");
	cabecalho();
	//Printa o custo em tag
	gotoxy(30, 5);
	std::cout << "Custo em tag: " << custo << " bits";

	gotoxy(0, y);
	std::cout << "Endereco";
	gotoxy(10, y);
	std::cout << "Acerto/Falta";
	gotoxy(29, y);
	std::cout << "Bloco";
	int x = 36;
	tamCache = tamCache / qtdEnderecosCache;
	for (int i = 0; i < qtdEnderecosCache; i++)
	{
		gotoxy(x, y);
		std::cout << "v";
		x += 2;
		gotoxy(x, y);
		std::cout << "t";
		x += 3;
		gotoxy(x, y);
		std::cout << "Endereco " << i;
		x += 12;
	}

	y++;
	for (int i = 0; i < tamCache; i++)
	{
		gotoxy(31, y);
		std::cout << i;
		y++;
	}

	y = 9;
	for (int i = 0; i < qtdEndereco; i++)
	{
		int aux;

		mostra_cache(memCache, tamCache, qtdEnderecosCache, tempoLimite);

		gotoxy(0, 5);
		std::cout << "Digite o endereco:\n";
		std::cin >> aux;

		insere(memCache, aux, tempoLimite, tamCache, qtdEnderecosCache);

		gotoxy(4, y);
		textcolor(BRIGHTWHITE, BLACK);
		std::cout << aux;
		textcolor(WHITE, BLACK);

		gotoxy(15, y);
		if (memCache[hash(aux, tamCache)].acerto)
		{
			textcolor(LIGHTGREEN, BLACK);
			std::cout << "Acerto";
			textcolor(WHITE, BLACK);
		}
		else
		{
			textcolor(LIGHTRED, BLACK);
			std::cout << "Falta";
			textcolor(WHITE, BLACK);
		}

		//"Limpa" o que foi escrito anteriormente
		gotoxy(0, 6);
		std::cout << "          ";
		y++;
	}

	_getch();
	return 0;
}