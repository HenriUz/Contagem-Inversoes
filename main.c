/*
main.c

Descrição: este código tem o objetivo de identificar o número de inversões entre duas listas. A maneira adotada para resolver isso foi por meio do mapeamento das posições dos elementos do segundo vetor no primeiro, para isso foi utilizado uma árvore balanceada para armazenar o primeiro vetor com os índices equivalentes, e depois é buscado na árvore os elementos do vetor 2, se não encontrar não faz nada, mas se encontrar salva o índice em outro vetor auxiliar. Por fim, basta apenas contar as inversões dos elementos mapeados enquanto ordenamos eles.

Visualização do mapeamento:
Vetor 1: 1 3 5 2 4 6
Vetor 2: 5 6 1 4 2 3

Índices do vetor 1 na árvore: 0 1 2 3 4 5
Vetor 2 mapeado: 2 5 0 4 3 1
Note que o algoritmo funcionará mesmo para vetores de tamanho diferentes e com muitos elementos que não sejam em comum.

Observação: foi escolhido usar uma árvore balanceada, no caso AVL, para garantir que o "for" do mapeamento não seja de complexidade O(n²), pois com a busca da árvore sendo O(log n), o "for" do mapeamento será O(nlog n).
*/

/* --- Includes. --- */

#include <stdio.h>
#include <stdlib.h>

/* --- Estruturas. --- */

typedef struct no {
    int valor; //Valor no vetor.
    int indice; //Índice do valor no vetor.
    int fb; //Fator de balanceamento.
    struct no *fEsq, *fDir, *pai; //Ponteiros para os nós próximos.
}no;

typedef struct arvore {
    no *sentinela; //Armazena a raiz da árvore no filho direito.
}arvore;

/* --- Funções. --- */

/*
Descrição: função que cria e inicializa uma estrutura de árvore, inicializando junto o sentinela.
Entrada: nada.
Saída: ponteiro para a árvore.
*/
arvore *criaArvore() {
    arvore *arv = (arvore *)malloc(sizeof(arvore));
    if(!arv) {
        return NULL;
    }
    arv->sentinela = (no *)malloc(sizeof(no));
    if(!arv->sentinela) {
        free(arv);
        return NULL;
    }
    /* Setando valores do sentinela. */
    arv->sentinela->valor = -1000;
    arv->sentinela->indice = -1;
    arv->sentinela->fb = 0;
    arv->sentinela->fEsq = arv->sentinela->fDir = arv->sentinela->pai = NULL;
    return arv;
}

/*
Descrição: função que busca um elemento na árvore e retorna seu índice.
Entrada: ponteiro para a árvore, inteiro do valor.
Saída: inteiro do índice, ou −1 em caso de não encontrado.
*/
int busca(arvore *arv, int valor) {
    no *atual = arv->sentinela->fDir;
    /* Buscando elemento na árvore. */
    while(atual && atual->valor != valor) {
        if(valor < atual->valor) {
            atual = atual->fEsq;
        }else {
            atual = atual->fDir;
        }
    }
    /* Retornando. */
    if(atual) {
        return atual->indice;
    }
    return -1;
}

/*
Descrição: função que realiza uma rotação para a esquerda no nó informado.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void rotacaoEsq(no *noDesbalanceado) {
    /* Vinculando o pai com o novo filho (fDir). */
    if(noDesbalanceado == noDesbalanceado->pai->fEsq) {
        noDesbalanceado->pai->fEsq = noDesbalanceado->fDir;
    }else {
        noDesbalanceado->pai->fDir = noDesbalanceado->fDir;
    }
    noDesbalanceado->fDir->pai = noDesbalanceado->pai;
    /* Atualizando o novo pai do nó. */
    noDesbalanceado->pai = noDesbalanceado->fDir;
    /* Vinculando o novo filho direito do nó. */
    noDesbalanceado->fDir = noDesbalanceado->pai->fEsq;
    if(noDesbalanceado->fDir) {
        noDesbalanceado->fDir->pai = noDesbalanceado;
    }
    /* Vinculando o nó como o novo filho esquerdo do pai. */
    noDesbalanceado->pai->fEsq = noDesbalanceado;
}

/*
Descrição: função que realiza uma rotação para a direita no nó informado.
Entrada: ponteiro para o nó.
Saída: nada.
*/
void rotacaoDir(no *noDesbalanceado) {
    /* Vinculando o pai com o novo filho (fEsq). */
    if(noDesbalanceado == noDesbalanceado->pai->fEsq) {
        noDesbalanceado->pai->fEsq = noDesbalanceado->fEsq;
    }else {
        noDesbalanceado->pai->fDir = noDesbalanceado->fEsq;
    }
    noDesbalanceado->fEsq->pai = noDesbalanceado->pai;
    /* Atualizando o novo pai do nó. */
    noDesbalanceado->pai = noDesbalanceado->fEsq;
    /* Vinculando o novo filho esquerdo do nó. */
    noDesbalanceado->fEsq = noDesbalanceado->pai->fDir;
    if(noDesbalanceado->fEsq) {
        noDesbalanceado->fEsq->pai = noDesbalanceado;
    }
    /* Vinculando o nó como o novo filho direito do pai. */
    noDesbalanceado->pai->fDir = noDesbalanceado;
}

/*
Descrição: função que identifica qual tipo de rotação deve ser feito para balancear a árvore, e corrige os fb dos nós envolvidos na rotação.
Entrada: ponteiro para a árvore, ponteiro para o nó desbalanceado.
Saída: nada.
*/
void balanceia(arvore *arv, no *noDesbalanceado) {
    no *filho;
    /* Balanceando. */
    if(noDesbalanceado->fb == 2) {
        //Subárvore direita tem mais elementos.
        filho = noDesbalanceado->fDir;
        if(filho->fb >= 0) {
            //Rotação simples.
            /* Corrigindo FBs. */
            if(filho->fb == 1) {
                noDesbalanceado->fb = filho->fb = 0;
            }else {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
            /* Rotacionando. */
            rotacaoEsq(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->fDir == noDesbalanceado) {
                arv->sentinela->fDir = filho;
            }
        }else {
            //Rotação dupla.
            /* Corrigindo FBs. */
            if(filho->fEsq->fb == 0){
                noDesbalanceado->fb = filho->fb = 0;
            }else if(filho->fEsq->fb == 1){
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }else{
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            filho->fEsq->fb = 0;
            /* Rotacionando. */
            rotacaoDir(filho);
            rotacaoEsq(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->fDir == noDesbalanceado){
                arv->sentinela->fDir = noDesbalanceado->pai;
            }
        }
    }else {
        //Subárvore esquerda tem mais elementos.
        filho = noDesbalanceado->fEsq;
        if(filho->fb <= 0) {
            //Rotação simples.
            /* Corrigindo FBs. */
            if(filho->fb == -1) {
                noDesbalanceado->fb = filho->fb = 0;
            }else {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
            /* Rotacionando. */
            rotacaoDir(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->fDir == noDesbalanceado) {
                arv->sentinela->fDir = filho;
            }
        }else {
            //Rotação dupla.
            /* Corrigindo FBs. */
            if(filho->fDir->fb == 0){
                noDesbalanceado->fb = filho->fb = 0;
            }else if(filho->fDir->fb == 1){
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }else{
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            filho->fDir->fb = 0;
            /* Rotacionando. */
            rotacaoEsq(filho);
            rotacaoDir(noDesbalanceado);
            /* Verificando raiz. */
            if(arv->sentinela->fDir == noDesbalanceado){
                arv->sentinela->fDir = noDesbalanceado->pai;
            }
        }
    }
}

/*
Descrição: função que atualiza os fb dos nós na subárvore onde o novo nó foi inserido. Caso identifique um balanceamento, chama a função de balancear.
Entrada: ponteiro para a árvore, ponteiro para o nó.
Saída: nada.
*/
void atualizaFB_insercao(arvore *arv, no *novo) {
    no *atual = novo;
    /* Atualizando FBs. */
    do {
        if(atual == atual->pai->fEsq && atual->pai != arv->sentinela) {
            atual->pai->fb--;
        }else if(atual->pai != arv->sentinela) {
            atual->pai->fb++;
        }
        atual = atual->pai;
    }while(atual->fb != 0 && atual->fb != 2 && atual->fb != -2 && atual != arv->sentinela);
    /* Verificando se houve um desbalanceamento. */
    if(atual->fb == 2 || atual->fb == -2) {
        balanceia(arv, atual);
    }
}

/*
Descrição: função que atualiza os fb dos nós na subárvore onde o elemento foi removido. Diferente da inserção, não para de verificar após realizar um balanceamento.
Entrada: ponteiro para a árvore, ponteiro para o pai do elemento removido, inteiro do valor (para identificar em qual subárvore estava).
Saída: nada.
*/
void atualizaFB_remocao(arvore *arv, no *pai, int valor) {
    no *atual = pai;
    /* Atualizando os FBs. */
    if(atual != arv->sentinela) {
        //O elemento removido não foi a raiz.
        if(valor <= atual->valor) { //≤, pois estamos usando o predecessor, então, na remoção o pai pode passar a ter o mesmo valor da chave removida na esquerda.
            atual->fb++;
        }else {
            atual->fb--;
        }
        while(atual->pai != arv->sentinela && atual->fb != 1 && atual->fb != -1 && atual->fb != 2 && atual->fb != -2) {
            atual = atual->pai;
            if(valor <= atual->valor) {
                atual->fb++;
            }else {
                atual->fb--;
            }
        }
        /* Verificando se houve um desbalanceamento. */
        if(atual->fb == 2 || atual->fb == -2) {
            balanceia(arv, atual);
            if(atual->pai != arv->sentinela && atual->pai->fb == 0) {
                atualizaFB_remocao(arv, atual->pai->pai, valor);
            }
        }
    }
}

/*
Descrição: função que cria um novo nó, e o insere na árvore.
Entrada: ponteiro para a árvore, inteiro do valor, inteiro do índice.
Saída: 1 - sucesso, 0 - erro.
*/
int insereArv(arvore *arv, int valor, int indice) {
    no *novo = (no *)malloc(sizeof(no));
    no *atual, *pai = NULL; //O primeiro irá percorrer a árvore, e segundo simboliza o pai do primeiro.
    if(!novo) {
        return 0;
    }
    /* Setando valores do nó. */
    novo->valor = valor;
    novo->indice = indice;
    novo->fb = 0;
    novo->fEsq = novo->fDir = NULL;
    /* Inserindo, se a árvore estiver vazia simplesmente linka com o sentinela, se não percorre ela até achar seu local como folha. */
    if(!arv->sentinela->fDir) {
        /* Linkando nó com o sentinela. */
        arv->sentinela->fDir = novo;
        novo->pai = arv->sentinela;
    }else {
        /* Percorrendo. */
        atual = arv->sentinela->fDir;
        while(atual) {
            pai = atual;
            if(valor < atual->valor) {
                atual = atual->fEsq;
            }else {
                atual = atual->fDir;
            }
        }
        /* Linkando novo nó com o pai. */
        novo->pai = pai;
        if(valor < pai->valor) {
            pai->fEsq = novo;
        }else {
            pai->fDir = novo;
        }
    }
    /* Verificando balanceamento. */
    atualizaFB_insercao(arv, novo);
    return 1;
}

/*
Descrição: função que remove um elemento da árvore.
Entrada: ponteiro para a árvore, inteiro do valor.
Saída: 1 - sucesso, 0 - árvore vazia, −1 - elemento não encontrado.
*/
int removeArv(arvore *arv, int valor) {
    no *atual, *aux; //O primeiro percorre a árvore, e o segundo é utilizado somente na situação de remoção por predecessor.
    /* Removendo. */
    if(arv->sentinela->fDir) {
        atual = arv->sentinela->fDir;
        /* Buscando elemento na árvore. */
        while(atual && atual->valor != valor) {
            if(valor < atual->valor) {
                atual = atual->fEsq;
            }else {
                atual = atual->fDir;
            }
        }
        if(atual) {
            if(atual->fEsq && atual->fDir) {
                /* Removendo por cópia do predecessor. */
                aux = atual;
                /* Buscando predecessor. */
                atual = atual->fEsq;
                while(atual->fDir) {
                    atual = atual->fDir;
                }
                /* Copiando valores. */
                aux->valor = atual->valor;
                aux->indice = atual->indice;
                /* Removendo predecessor da árvore. */
                if(atual == atual->pai->fEsq) {
                    atual->pai->fEsq = atual->fEsq;
                }else {
                    atual->pai->fDir = atual->fEsq;
                }
                if(atual->fEsq) {
                    atual->fEsq->pai = atual->pai;
                }
            }else if(!atual->fEsq && !atual->fDir) {
                /* Desvinculando elemento. */
                if(atual == atual->pai->fEsq) {
                    atual->pai->fEsq = NULL;
                }else {
                    atual->pai->fDir = NULL;
                }
            }else if(atual->fEsq) {
                /* Desvinculando elemento, e vinculando o filho esquerdo com o novo pai. */
                if(atual == atual->pai->fEsq) {
                    atual->pai->fEsq = atual->fEsq;
                }else {
                    atual->pai->fDir = atual->fEsq;
                }
                atual->fEsq->pai = atual->pai;
            }else {
                /* Desvinculando elemento, e vinculando o filho direito com o novo pai. */
                if(atual == atual->pai->fEsq) {
                    atual->pai->fEsq = atual->fDir;
                }else {
                    atual->pai->fDir = atual->fDir;
                }
                atual->fDir->pai = atual->pai;
            }
            /* Verificando balanceamento. */
            atualizaFB_remocao(arv, atual->pai, atual->valor);
            /* Liberando memória. */
            free(atual);
            atual = NULL;
            return 1;
        }
        return -1;
    }
    return 0;
}

/*
Descrição: função responsável por esvaziar uma árvore utilizando a função removeArv.
Entrada: ponteiro para a árvore.
Saída: nada.
*/
void destroiArv(arvore *arv) {
    /* Removendo a raiz até a árvore ficar vazia. */
    while(arv->sentinela->fDir) {
        removeArv(arv, arv->sentinela->fDir->valor);
    }
    /* Liberando memória da árvore. */
    free(arv->sentinela);
    free(arv);
    arv = NULL;
}

/*
Descrição: função responsável por ordenar os elementos na parte [inicio, meio] com a parte [meio + 1, fim] do vetor informado. Nisso, também é contado o número de inversões que há entre as duas partes (inversões do tipo split).
Entrada: ponteiro do vetor, inteiro do início, inteiro do meio, inteiro do fim.
Saída: inteiro da quantidade de inversões.
*/
int countSplit(int *vetor, int inicio, int meio, int fim) {
    int ind1 = inicio, ind2 = meio + 1, indAux = 0; //Índices dos vetores, os dois primeiros simbolizam o índice da parte 1 e 2, respectivamente, e o terceiro é o índice do vetor auxiliar.
    int *vetorAux = (int *)malloc(sizeof(int) * (fim - inicio + 1));
    int t = 0; //Número de inversões. É contado por meio da quantidade de elementos restante na parte 1.
    /* Ordenando as duas partes no vetor auxiliar, e contando as inversões quando ocorrem. */
    while(ind1 <= meio && ind2 <= fim) {
        if(vetor[ind1] < vetor[ind2]) {
            vetorAux[indAux++] = vetor[ind1++];
        }else {
            vetorAux[indAux++] = vetor[ind2++];
            t += meio - ind1 + 1; //O tamanho da primeira parte equivale a (meio - inicio + 1), e para descobrirmos quantos ainda faltam basta subtrair pelo (índice - inicio).
        }
    }
    /* Verificando se falta colocar elementos no vetor auxiliar. */
    if(ind1 <= meio) {
        while(ind1 <= meio) {
            vetorAux[indAux++] = vetor[ind1++];
        }
    }else if(ind2 <= fim) {
        while(ind2 <= fim) {
            vetorAux[indAux++] = vetor[ind2++];
        }
    }
    /* Jogando os elementos do vetor auxiliar no vetor original. */
    indAux = 0;
    for(int x = inicio; x <= fim; x++, indAux++) {
        vetor[x] = vetorAux[indAux];
    }
    /* Liberando memória do vetor auxiliar. */
    free(vetorAux);
    vetorAux = NULL;
    return t;
}

/*
Descrição: função responsável por realizar a divisão e conquista, dividindo o problema em 2 subproblemas com a metade do tamanho, e no final retornando o número de inversões encontradas.
Entrada: ponteiro do vetor, inteiro do início, inteiro do fim (deve ser o índice final, e não o tamanho de vetor).
Saída: inteiro da quantidade de inversões.
*/
int count(int *vetor, int inicio, int fim) {
    int meio = (inicio + fim) / 2, inversoes = 0;
    if(inicio < fim) {
        /* Conquistando. */
        inversoes += count(vetor, inicio, meio);
        inversoes += count(vetor, meio+1, fim);
        /* Combinando resultados e retornando. */
        inversoes += countSplit(vetor, inicio, meio, fim);
        return inversoes;
    }
    return 0;
}

/*
Descrição: função principal, responsável por lidar com os inputs, por mapear os vetores e por mostrar o resultado das inversões.
Entrada: nada.
Saída: 0 - sucesso, 1 - erro ao alocar memória.
*/
int main(void) {
    FILE *arq = fopen("/home/henriuz/01-Universidade/04-Periodo/CTCO04-Projeto-E-Analise-De-Algoritmos/Trabalho-02-Inversoes/Codigo/Casos-De-Teste/7.in", "r");
    arvore *arv = criaArvore();
    int tamVet1, tamVet2, tamVetMap = 0; //O tamanho real do vetor mapeado será o tamanho do menor vetor, este tamVetMap vai dizer até onde está os elementos.
    int vet1, *vet2; //O vetor 1 será mapeado diretamente na árvore, por isso ele só é um valor. Já o segundo será um vetor mesmo.
    int *vetMap; //Este será o vetor 2 mapeado conforme o 1.
    int indice; //Índice retornado na busca.
    /* Verificando se houve algum erro na criação de algo. */
    if(!arq) {
        printf("\nErro ao abrir o arquivo.");
        return 1;
    }
    if(!arv) {
        printf("\nErro ao criar a árvore.");
        return 1;
    }
    /* Lendo vetor 1 e inserindo na árvore. */
    fscanf(arq, "%d", &tamVet1);
    for(int i = 0; i < tamVet1; i++) {
        fscanf(arq, "%d", &vet1);
        if(!insereArv(arv, vet1, i)) {
            printf("\nErro ao inserir elemento.");
        }
    }
    /* Lendo vetor 2 e inserindo no vetor. */
    fscanf(arq, "%d", &tamVet2);
    vet2 = (int *)malloc(sizeof(int) * tamVet2);
    if(!vet2) {
        printf("\nErro ao alocar memoria.");
        destroiArv(arv);
        fclose(arq);
        return 1;
    }
    for(int i = 0; i < tamVet2; i++) {
        fscanf(arq, "%d", &vet2[i]);
    }
    /* Fechando o arquivo. */
    fclose(arq);
    /* Criando o vetor mapeado com o menor tamanho dos vetores. */
    if(tamVet1 < tamVet2) {
        vetMap = (int *)malloc(sizeof(int) * tamVet1);
    }else {
        vetMap = (int *)malloc(sizeof(int) * tamVet2);
    }
    if(!vetMap) {
        printf("\nErro ao alocar memoria.");
        destroiArv(arv);
        free(vet2);
        return 1;
    }
    /* Percorrendo o vetor 2 mapeando ele conforme o 1. */
    for(int i = 0; i < tamVet2; i++) {
        indice = busca(arv, vet2[i]);
        if(indice != -1) {
            vetMap[tamVetMap++] = indice;
        }
    }
    /* Liberando memória da árvore. */
    destroiArv(arv);
    /* Calculando inversões. */
    printf("%d", count(vetMap, 0, tamVetMap-1));
    /* Liberando memória. */
    free(vet2);
    free(vetMap);
    return 0;
}
