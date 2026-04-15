#pragma once
#include <iostream>
#include <fstream> // Necessário para gerar o arquivo .dot do Graphviz

using namespace std;

// Classe que representa uma página (nodo) da Árvore B
class NodoArvoreB {
public:
    int* chaves;
    int ordem;
    NodoArvoreB** filhos;
    int qtdChavesAtuais;
    bool isFolha;

    NodoArvoreB(int ordemDaArvore, bool NodoIsFolha);

    void imprimirPreOrdem(); //caminhamentos
    void imprimirEmOrdem();
    void imprimirPosOrdem();

    void gerarDotPreOrdem(ofstream& arquivoDot);

    NodoArvoreB* buscar(int chaveDesejada);

    void inserirNoNodoNaoCheio(int novaChave); //inserir na posicao correta do array quando a pagina nao estiver cheia
    void dividirFilhoCheio(int indiceDoFilho, NodoArvoreB* filhoQueSeraDividido); //pra fazer a divisao no meio quando o nodo estiver cheio

	int encontrarChave(int chaveDesejada); //busca no array o indice da chave desejada ou o indice onde ela deveria estar
	void remover(int chaveParaRemover); //funcao que decide qual tipo de remocao sera feita (folha ou nao folha)
    void removerDaFolha(int indice); //exclusao de uma chave na pagina folha, sem underflow
    void removerDeNaoFolha(int indice); //exclusao de uma chave nao folha, sem underflow
    int obterPredecessor(int indice);
    int obterSucessor(int indice);
    void preencher(int indice);
    void pegarEmprestadoAnterior(int indice);
    void pegarEmprestadoProximo(int indice);
    void fundirNodos(int indice); // Faz o merge de nodos
};