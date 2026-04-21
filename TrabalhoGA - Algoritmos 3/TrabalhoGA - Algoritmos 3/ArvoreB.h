#pragma once
#include <iostream>
#include <fstream> // Necessário para gerar o arquivo .dot do Graphviz
#include "NodoArvoreB.h"
using namespace std;

// Classe principal da Árvore B
class ArvoreB {
public:
	NodoArvoreB* raiz; //endereco de memoria que guarda um objeto da classe NodoArvoreB, que representa a pagina raiz da arvore
    int ordem;

    ArvoreB(int ordemDaArvore);

    // Funções públicas que você chamará na sua main()
    void imprimirPreOrdem();
    void imprimirEmOrdem();
    void imprimirPosOrdem();

    void gerarArquivoDot(string nomeArquivo);

    NodoArvoreB* buscar(int chaveDesejada);
    void inserir(int novaChave);
    void remover(int chaveParaRemover);
};