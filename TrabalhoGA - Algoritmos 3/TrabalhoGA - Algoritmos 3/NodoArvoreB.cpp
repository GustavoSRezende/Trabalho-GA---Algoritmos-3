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
	for (i = 0; i < qtdChavesAtuais; i++) { //antes de imprimir a chave atual, visita todos os seus filhos menores e imprime eles
		if (isFolha == false) { //caminhamento em ordem imprime em ordem crescente
			filhos[i]->imprimirEmOrdem();
		}
		cout << chaves[i] << " "; 
	}
	// Imprime o último filho à direita
	if (isFolha == false) {
		filhos[i]->imprimirEmOrdem();
	}
}

void NodoArvoreB::imprimirPreOrdem() { //imprime a arvore de cima pra baixo, ou seja, primeiro imprime a chave do nodo, depois os filhos da esquerda pra direita
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

void NodoArvoreB::imprimirPosOrdem() { //imprime a arvore de baixo pra cima, ou seja, primeiro imprime os filhos da esquerda pra direita, depois a chave do nodo
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
void NodoArvoreB::gerarDotPreOrdem(ofstream& arquivoDot) {
	//desenha a caixa deste nodo
	arquivoDot << "  node" << this << " [label=\"";
	for (int i = 0; i < qtdChavesAtuais; i++) {
		arquivoDot << "<f" << i << "> " << chaves[i];
		if (i < qtdChavesAtuais - 1) {
			arquivoDot << " | ";
		}
	}
	arquivoDot << "\"];" << endl;

	//desenha as setas e manda os filhos se desenharem
	if (isFolha == false) {
		for (int i = 0; i <= qtdChavesAtuais; i++) {
			if (filhos[i] != nullptr) {
				arquivoDot << "  node" << this << " -> node" << filhos[i] << ";" << endl;
				filhos[i]->gerarDotPreOrdem(arquivoDot);
			}
		}
	}
}

void NodoArvoreB::inserirNoNodoNaoCheio(int novaChave) {
	int i = qtdChavesAtuais - 1;

	if (isFolha == true) {
		while (i >= 0 && chaves[i] > novaChave) { //vasculha o array de trás pra frente
			chaves[i + 1] = chaves[i]; //empurrando os números maiores que a chave para a direita
			i--; //quando achar um número menor, para de empurrar e insere a nova chave na posição correta
		}
		chaves[i + 1] = novaChave; //aqui insere a nova chave
		qtdChavesAtuais++;
	}
	else {
		while (i >= 0 && chaves[i] > novaChave) {
			i--; //mesma logica de cima, percorre a array de trás pra frente
		}
		i++;

		//manda o filho inserir
		filhos[i]->inserirNoNodoNaoCheio(novaChave); //como filhos[] e n+1, o i++ acessa o filho correto
													 //exemplo, num array de 10,20, se tentar colocar 25, o i do array vai ser 1, i++ acessa filhos [2], que e o filho de 20

		//se após inserir o filho passou do limite, quebra ele!
		if (filhos[i]->qtdChavesAtuais > 2 * ordem) {
			dividirFilhoCheio(i, filhos[i]); //chama a divisao
		}
	}
}

void NodoArvoreB::dividirFilhoCheio(int indiceDoFilho, NodoArvoreB* filho) {
	//essa função e executada pelo pai, o pai olha para o filho e ve que ele estourou o numero de chaves
	//o pai vai fatiar o filho no meio, criar um novoIrmao pra ficar com a metade da direita e puxar a chave central pra ele mesmo

	NodoArvoreB* novoIrmao = new NodoArvoreB(filho->ordem, filho->isFolha); //o pai cria o novo irmao
	novoIrmao->qtdChavesAtuais = filho->ordem;

	int meio = filho->ordem; //a ordem sempre e numericamente igual a metade do numero maximo de chaves, entao o meio e a orSdem

	for (int j = 0; j < filho->ordem; j++) { //faz um loop que percorre ate a ordem, que e a metade do numero maximo de chaves
		novoIrmao->chaves[j] = filho->chaves[meio + 1 + j]; //o novo irmao recebe a metade da direita do filho, que comeca no numero sequencia do meio mais 1, depois ele soma j pra ir pegando os próximos
	}

	if (filho->isFolha == false) { //transfere os filhos para o irmao, se nao for folha
		for (int j = 0; j <= filho->ordem; j++) { //vai pegar a metade da direita e todos os filhos dessa metade
			novoIrmao->filhos[j] = filho->filhos[meio + 1 + j]; //e colocar na caixa de enderecos do novo irmao, que agora guarda a metade da direita e seus filhos
		}
	}

	filho->qtdChavesAtuais = filho->ordem; //como parte da pagina foi pro novo irmao, a pagina precisa ser atualizada pra saber quantas chaves estao sendo usadas, ou seja, se antes tinham 4 e 2 foram pro novo irmao, agora qtdChavesAtuais tem que ser 2

	for (int j = qtdChavesAtuais; j >= indiceDoFilho + 1; j--) { //o pai precisa abrir espaço para o novo irmao, ele empurra os filhos pra direita
		filhos[j + 1] = filhos[j]; //coloca o novo irmao na posicao do filho + 1, e o filho que foi dividido fica a esquerda, o novo irmao a direita
	}
	filhos[indiceDoFilho + 1] = novoIrmao; //o filho que foi dividido fica a esquerda, o novo irmao a direita

	for (int j = qtdChavesAtuais - 1; j >= indiceDoFilho; j--) { //segue a mesma ideia da parte de cima, mas ao inves de colocar os enderecos da esquerda e direita, coloca o numero que subiu
		chaves[j + 1] = chaves[j]; //ou seja, se o pai antes era so o numero 80, agora ele abre espaco pra um 30, os filhos de 30 ja tem espaco na caixa de enderecos do pai, mas precisamos abrir espaco pro proprio 30
	}
	chaves[indiceDoFilho] = filho->chaves[meio]; //a chave do meio sobe para o pai, ou seja, o numero 30 sobe para o pai, e o filho que foi dividido fica a esquerda, o novo irmao a direita

	qtdChavesAtuais++; //o pai ganha a chave promovida
}

int NodoArvoreB::encontrarChave(int chaveDesejada) {
	int idx = 0;

	//caminha para a direita enquanto as chaves forem menores que a desejada
	while (idx < qtdChavesAtuais && chaves[idx] < chaveDesejada) {
		idx++; //faz uma micro busca, o idx vai parar no indice da chave desejada, ou no indice onde ela deveria estar se fosse inserida, ou seja, o primeiro numero maior que a chave desejada
	} //ele busca o endereco da chave desejada, se nao tiver ali, diz onde ela devia estar

	return idx;
}