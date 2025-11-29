#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 20
#define TAM_NOME 30
#define TAM_TIPO 20

// -------------------------------------------------------
// Structs principais
// -------------------------------------------------------
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// -------------------------------------------------------
// Contadores de comparações
// -------------------------------------------------------
long long compBuscaSequencial = 0;
long long compBuscaBinaria   = 0;

// -------------------------------------------------------
// Funções auxiliares
// -------------------------------------------------------
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int lerInteiro() {
    int valor;
    scanf("%d", &valor);
    getchar();
    return valor;
}

// -------------------------------------------------------
// Funções de VETOR
// -------------------------------------------------------

// Insere item no vetor (se houver espaço)
void inserirItemVetor(Item vet[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila (vetor) cheia! Nao e possivel inserir mais itens.\n");
        return;
    }

    printf("\n--- Inserir item (VETOR) ---\n");

    printf("Nome do item: ");
    fgets(vet[*qtd].nome, TAM_NOME, stdin);
    removerQuebraLinha(vet[*qtd].nome);

    printf("Tipo do item: ");
    fgets(vet[*qtd].tipo, TAM_TIPO, stdin);
    removerQuebraLinha(vet[*qtd].tipo);

    do {
        printf("Quantidade: ");
        vet[*qtd].quantidade = lerInteiro();
        if (vet[*qtd].quantidade < 1) {
            printf("Quantidade invalida! Digite valor >= 1.\n");
        }
    } while (vet[*qtd].quantidade < 1);

    (*qtd)++;
    printf("Item inserido no vetor com sucesso!\n");
}

// Remove item do vetor por nome
void removerItemVetor(Item vet[], int *qtd) {
    if (*qtd == 0) {
        printf("\nVetor vazio. Nao ha itens para remover.\n");
        return;
    }

    char alvo[TAM_NOME];
    printf("\n--- Remover item (VETOR) ---\n");
    printf("Nome do item a remover: ");
    fgets(alvo, TAM_NOME, stdin);
    removerQuebraLinha(alvo);

    int i, pos = -1;
    for (i = 0; i < *qtd; i++) {
        if (strcmp(vet[i].nome, alvo) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado no vetor.\n");
        return;
    }

    for (i = pos; i < *qtd - 1; i++) {
        vet[i] = vet[i + 1];
    }
    (*qtd)--;
    printf("Item removido do vetor.\n");
}

// Lista itens do vetor
void listarItensVetor(Item vet[], int qtd) {
    printf("\n--- Itens no VETOR ---\n");
    if (qtd == 0) {
        printf("Nenhum item no vetor.\n");
    } else {
        for (int i = 0; i < qtd; i++) {
            printf("%2d) Nome: %-20s | Tipo: %-10s | Quantidade: %d\n",
                   i + 1, vet[i].nome, vet[i].tipo, vet[i].quantidade);
        }
    }
    printf("----------------------\n");
}

// Busca sequencial no vetor por nome
int buscarSequencialVetor(Item vet[], int qtd, const char *alvo) {
    compBuscaSequencial = 0;
    for (int i = 0; i < qtd; i++) {
        compBuscaSequencial++;
        if (strcmp(vet[i].nome, alvo) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordena vetor por nome (Bubble Sort simples)
void ordenarVetorPorNome(Item vet[], int qtd) {
    int i, j, trocou;
    Item temp;
    for (i = 0; i < qtd - 1; i++) {
        trocou = 0;
        for (j = 0; j < qtd - 1 - i; j++) {
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

// Busca binária no vetor já ordenado por nome
int buscarBinariaVetor(Item vet[], int qtd, const char *alvo) {
    int ini = 0, fim = qtd - 1, meio;
    int cmp;
    compBuscaBinaria = 0;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        cmp = strcmp(alvo, vet[meio].nome);
        compBuscaBinaria++;

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    return -1;
}

// -------------------------------------------------------
// Funções de LISTA ENCADEADA
// -------------------------------------------------------

// Insere item no início da lista
void inserirItemLista(No **inicio) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro ao alocar memoria para novo no.\n");
        return;
    }

    printf("\n--- Inserir item (LISTA) ---\n");

    printf("Nome do item: ");
    fgets(novo->dados.nome, TAM_NOME, stdin);
    removerQuebraLinha(novo->dados.nome);

    printf("Tipo do item: ");
    fgets(novo->dados.tipo, TAM_TIPO, stdin);
    removerQuebraLinha(novo->dados.tipo);

    do {
        printf("Quantidade: ");
        novo->dados.quantidade = lerInteiro();
        if (novo->dados.quantidade < 1) {
            printf("Quantidade invalida! Digite valor >= 1.\n");
        }
    } while (novo->dados.quantidade < 1);

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item inserido na lista encadeada!\n");
}

// Remove item da lista por nome
void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista encadeada vazia. Nao ha itens para remover.\n");
        return;
    }

    char alvo[TAM_NOME];
    printf("\n--- Remover item (LISTA) ---\n");
    printf("Nome do item a remover: ");
    fgets(alvo, TAM_NOME, stdin);
    removerQuebraLinha(alvo);

    No *atual = *inicio;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, alvo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na lista.\n");
        return;
    }

    if (anterior == NULL) { // removendo o primeiro
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item removido da lista encadeada.\n");
}

// Lista itens da lista encadeada
void listarItensLista(No *inicio) {
    printf("\n--- Itens na LISTA ENCADEADA ---\n");
    if (inicio == NULL) {
        printf("Nenhum item na lista.\n");
    } else {
        int i = 1;
        No *p = inicio;
        while (p != NULL) {
            printf("%2d) Nome: %-20s | Tipo: %-10s | Quantidade: %d\n",
                   i, p->dados.nome, p->dados.tipo, p->dados.quantidade);
            p = p->proximo;
            i++;
        }
    }
    printf("--------------------------------\n");
}

// Busca sequencial na lista encadeada
No *buscarItemLista(No *inicio, const char *alvo) {
    compBuscaSequencial = 0;
    No *p = inicio;
    while (p != NULL) {
        compBuscaSequencial++;
        if (strcmp(p->dados.nome, alvo) == 0) {
            return p;
        }
        p = p->proximo;
    }
    return NULL;
}

// Libera toda a lista encadeada
void liberarLista(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

// -------------------------------------------------------
// Função principal - menu do nível Aventureiro
// -------------------------------------------------------
int main() {
    Item mochilaVet[MAX_ITENS];
    int qtdVet = 0;

    No *mochilaLista = NULL;

    int opcaoEstrutura;
    int opcao;
    int ordenadoPorNome = 0;

    printf("===== Nível Aventureiro - Vetor x Lista Encadeada =====\n");

    do {
        printf("\n=== Escolha a estrutura de dados ===\n");
        printf("1 - Operar com VETOR\n");
        printf("2 - Operar com LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        opcaoEstrutura = lerInteiro();

        if (opcaoEstrutura == 1) {
            // ---------------- VETOR ----------------
            do {
                printf("\n=== MENU VETOR ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial por nome\n");
                printf("5 - Ordenar por nome (Bubble) e buscar binaria\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                opcao = lerInteiro();

                switch (opcao) {
                    case 1:
                        inserirItemVetor(mochilaVet, &qtdVet);
                        break;

                    case 2:
                        removerItemVetor(mochilaVet, &qtdVet);
                        break;

                    case 3:
                        listarItensVetor(mochilaVet, qtdVet);
                        break;

                    case 4: {
                        if (qtdVet == 0) {
                            printf("\nVetor vazio.\n");
                        } else {
                            char alvo[TAM_NOME];
                            printf("\nNome do item para busca sequencial: ");
                            fgets(alvo, TAM_NOME, stdin);
                            removerQuebraLinha(alvo);

                            int pos = buscarSequencialVetor(mochilaVet, qtdVet, alvo);
                            if (pos != -1) {
                                printf("\nItem encontrado (busca sequencial, %lld comparacoes):\n",
                                       compBuscaSequencial);
                                printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                                       mochilaVet[pos].nome,
                                       mochilaVet[pos].tipo,
                                       mochilaVet[pos].quantidade);
                            } else {
                                printf("\nItem NAO encontrado (comparacoes: %lld).\n",
                                       compBuscaSequencial);
                            }
                        }
                        break;
                    }

                    case 5: {
                        if (qtdVet == 0) {
                            printf("\nVetor vazio.\n");
                        } else {
                            // Ordena por nome
                            ordenarVetorPorNome(mochilaVet, qtdVet);
                            ordenadoPorNome = 1;
                            printf("\nVetor ordenado por nome.\n");
                            listarItensVetor(mochilaVet, qtdVet);

                            // Busca binária
                            char alvo[TAM_NOME];
                            printf("\nNome do item para busca BINARIA: ");
                            fgets(alvo, TAM_NOME, stdin);
                            removerQuebraLinha(alvo);

                            int pos = buscarBinariaVetor(mochilaVet, qtdVet, alvo);
                            if (pos != -1) {
                                printf("\nItem encontrado (busca binaria, %lld comparacoes):\n",
                                       compBuscaBinaria);
                                printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                                       mochilaVet[pos].nome,
                                       mochilaVet[pos].tipo,
                                       mochilaVet[pos].quantidade);
                            } else {
                                printf("\nItem NAO encontrado (comparacoes: %lld).\n",
                                       compBuscaBinaria);
                            }
                        }
                        break;
                    }

                    case 0:
                        printf("\nVoltando ao menu principal...\n");
                        break;

                    default:
                        printf("\nOpcao invalida.\n");
                }

            } while (opcao != 0);

        } else if (opcaoEstrutura == 2) {
            // ---------------- LISTA ENCADEADA ----------------
            do {
                printf("\n=== MENU LISTA ENCADEADA ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial por nome\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                opcao = lerInteiro();

                switch (opcao) {
                    case 1:
                        inserirItemLista(&mochilaLista);
                        break;

                    case 2:
                        removerItemLista(&mochilaLista);
                        break;

                    case 3:
                        listarItensLista(mochilaLista);
                        break;

                    case 4: {
                        if (mochilaLista == NULL) {
                            printf("\nLista vazia.\n");
                        } else {
                            char alvo[TAM_NOME];
                            printf("\nNome do item para busca na lista: ");
                            fgets(alvo, TAM_NOME, stdin);
                            removerQuebraLinha(alvo);

                            No *resultado = buscarItemLista(mochilaLista, alvo);
                            if (resultado != NULL) {
                                printf("\nItem encontrado (busca sequencial, %lld comparacoes):\n",
                                       compBuscaSequencial);
                                printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                                       resultado->dados.nome,
                                       resultado->dados.tipo,
                                       resultado->dados.quantidade);
                            } else {
                                printf("\nItem NAO encontrado (comparacoes: %lld).\n",
                                       compBuscaSequencial);
                            }
                        }
                        break;
                    }

                    case 0:
                        printf("\nVoltando ao menu principal...\n");
                        break;

                    default:
                        printf("\nOpcao invalida.\n");
                }

            } while (opcao != 0);
        }

    } while (opcaoEstrutura != 0);

    // Libera a lista antes de sair
    liberarLista(&mochilaLista);

    printf("\nEncerrando o sistema do nivel Aventureiro.\n");
    return 0;
}
