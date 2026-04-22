#include "ArvoreB.h"

ArvoreB::ArvoreB(int ordemDaArvore) {
	raiz = nullptr; //nasce vazia, sem paginas
	ordem = ordemDaArvore;
}

NodoArvoreB* ArvoreB::buscar(int chaveDesejada) {
	if (raiz == nullptr) {
		return nullptr; //arvore vazia
	}
	else {
		return raiz->buscar(chaveDesejada); //chama a funcao de busca do nodo raiz, que vai chamar recursivamente nos filhos

	}
}

void ArvoreB::imprimirPreOrdem() {
	if (raiz != nullptr) {
		raiz->imprimirPreOrdem(); //toda vez que tem um raiz->funcao, ele vai chamar a funcao da classe NodoArvoreB, ela que faz todo o trabalho. Na main vai ser chamado a funcao levando em conta a arvore em si, mas ela vai distribuir a operação pro nodo
	}
}

void ArvoreB::imprimirEmOrdem() {
	if (raiz != nullptr) {
		raiz->imprimirEmOrdem();
	}
}

void ArvoreB::imprimirPosOrdem() {
	if (raiz != nullptr) {
		raiz->imprimirPosOrdem();
	}
}

void ArvoreB::gerarArquivoDot(string nomeArquivo) { //pro graphviz imprimir
        // ofstream cria um arquivo de texto
        ofstream arquivo(nomeArquivo);

        if (!arquivo.is_open()) {
            cout << "Erro ao tentar criar o arquivo: " << nomeArquivo << endl;
            return;
        }

        // Escreve o cabeçalho padrão da linguagem DOT para árvores
        arquivo << "digraph ArvoreB {" << endl;
        arquivo << "  node [shape=record];" << endl; // Faz os nodos ficarem com formato de caixa

        // Se a árvore não estiver vazia, manda a raiz fazer o caminhamento pré-ordem
        if (raiz != nullptr) {
            raiz->gerarDotPreOrdem(arquivo);
        }

        // Fecha a estrutura do arquivo DOT
        arquivo << "}" << endl;

        // Salva e fecha o arquivo no computador
        arquivo.close();

        cout << "Arquivo " << nomeArquivo << " gerado com sucesso!" << endl;
    }

//Funções de inserção e remoção da Árvore B, que vão chamar as funções de inserção e remoção do nodo raiz, que vão chamar recursivamente nos filhos, e assim por diante. A função de inserção tem que verificar se a raiz está cheia antes de inserir, se estiver cheia tem que dividir a raiz e criar uma nova raiz. A função de remoção tem que verificar se a raiz está vazia depois de remover, se estiver vazia tem que deletar a raiz e setar a raiz como nullptr.

void ArvoreB::inserir(int novaChave) { 
	//primeiro, caso a raiz esteja vazia, tem que criar um novo nodo e colocar a nova chave nele, e setar a raiz como esse novo nodo
    if (raiz == nullptr) {
        raiz = new NodoArvoreB(ordem, true);
        raiz->chaves[0] = novaChave;
        raiz->qtdChavesAtuais = 1; 
    } else {
     //a árvore já tem uma raiz. Precisamos checar se ela está cheia.
     //o limite máximo de chaves em um nodo é 2 * m
     if (raiz->qtdChavesAtuais == 2 * ordem) {

         //se entrar aqui, a raiz está cheia e a arvore precisa crescer em altura
         // Criamos uma nova raiz (ela começa vazia e NÃO é folha, pois terá a raiz antiga como filha)
         NodoArvoreB* novaRaiz = new NodoArvoreB(ordem, false);

         // Faz a nova raiz apontar para a raiz antiga no seu primeiro ponteiro de filho
         novaRaiz->filhos[0] = raiz;

         // Chama a função de dividir (split) para quebrar a raiz antiga no meio e subir uma chave
         novaRaiz->dividirFilhoCheio(0, raiz);

         // Agora que a nova raiz tem 1 chave e 2 filhos, precisamos decidir para qual
         // dos dois filhos a novaChave deve ir.
         int i = 0;
         if (novaRaiz->chaves[0] < novaChave) {
             i++;
         }

         // Manda o filho escolhido inserir a chave
         novaRaiz->filhos[i]->inserirNoNodoNaoCheio(novaChave);

         // Atualiza o ponteiro oficial da árvore para esta nova página topo
         raiz = novaRaiz;
     }
     else {
         // Cenário 3: A raiz ainda tem espaço sobrando.
         // Apenas repassamos a ordem para a raiz fazer o trabalho padrão.
         raiz->inserirNoNodoNaoCheio(novaChave);
     }
     }
}

void ArvoreB::remover(int chaveParaRemover) {
}