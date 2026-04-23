#include "NodoArvoreB.h"

NodoArvoreB::NodoArvoreB(int ordemDaArvore, bool NodoIsFolha) {
	ordem = ordemDaArvore;
	isFolha = NodoIsFolha;

	chaves = new int[(2 * ordem) + 1]; //+1 pra suportar o overflow temporário durante a inserção
	filhos = new NodoArvoreB * [(2 * ordem) + 2];

	qtdChavesAtuais = 0;

}

NodoArvoreB* NodoArvoreB::buscar(int chaveDesejada) {
	int i = 0;
	while (i < qtdChavesAtuais && chaveDesejada > chaves[i]) {
		i++;
	}

	if (i < qtdChavesAtuais && chaves[i] == chaveDesejada) {
		return this; // A chave foi encontrada neste nodo
	}

	if (isFolha == true) {
		return nullptr; //chegou no fim e não encontrou a chave;
	}

	return filhos[i]->buscar(chaveDesejada); // Continua a busca no filho apropriado
}

void NodoArvoreB::imprimirEmOrdem() {
	int i;
	for (i = 0; i < qtdChavesAtuais; i++) {
		if (isFolha == false) {
			filhos[i]->imprimirEmOrdem();
		}
		cout << chaves[i] << " ";
	}
	// Imprime o último filho à direita
	if (isFolha == false) {
		filhos[i]->imprimirEmOrdem();
	}
}

void NodoArvoreB::imprimirPreOrdem() {
	for (int i = 0; i < qtdChavesAtuais; i++) {
		cout << chaves[i] << " ";
	}
	cout << endl;

	if (isFolha == false) {
		for (int i = 0; i <= qtdChavesAtuais; i++) {
			filhos[i]->imprimirPreOrdem();
		}
	}
}

void NodoArvoreB::imprimirPosOrdem() {
	if (isFolha == false) {
		for (int i = 0; i <= qtdChavesAtuais; i++) {
			filhos[i]->imprimirPosOrdem();
		}
	}
	for (int i = 0; i < qtdChavesAtuais; i++) {
		cout << chaves[i] << " ";
	}
	cout << endl;
}