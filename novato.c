#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// -------------------------------------------------------
// Struct principal do nível Novato
// -------------------------------------------------------
typedef struct {
    char nome[TAM_NOME];   // Nome do item (ex: "AK-47", "Kit médico")
    char tipo[TAM_TIPO];   // Tipo do item (ex: "arma", "municao", "cura")
    int quantidade;        // Quantidade do item
} Item;

// -------------------------------------------------------
// Funções auxiliares
// -------------------------------------------------------

// Remove '\n' do final da string lida com fgets, se existir
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Lê um inteiro simples consumindo o '\n' depois
int lerInteiro() {
    int valor;
    scanf("%d", &valor);
    getchar(); // consome o '\n' deixado no buffer
    return valor;
}

// -------------------------------------------------------
// Funções obrigatórias
// -------------------------------------------------------

// Insere um novo item no vetor, se houver espaço
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Inserir novo item ---\n");

    printf("Nome do item: ");
    fgets(mochila[*qtd].nome, TAM_NOME, stdin);
    removerQuebraLinha(mochila[*qtd].nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(mochila[*qtd].tipo, TAM_TIPO, stdin);
    removerQuebraLinha(mochila[*qtd].tipo);

    do {
        printf("Quantidade: ");
        mochila[*qtd].quantidade = lerInteiro();
        if (mochila[*qtd].quantidade < 1) {
            printf("Quantidade invalida! Digite um valor maior ou igual a 1.\n");
        }
    } while (mochila[*qtd].quantidade < 1);

    (*qtd)++;
    printf("Item inserido com sucesso!\n");
}

// Remove um item pelo nome (busca sequencial)
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    char alvo[TAM_NOME];
    printf("\n--- Remover item ---\n");
    printf("Digite o NOME do item a ser removido: ");
    fgets(alvo, TAM_NOME, stdin);
    removerQuebraLinha(alvo);

    int i, pos = -1;

    // Busca sequencial pelo nome
    for (i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado na mochila.\n");
        return;
    }

    // "Compacta" o vetor para remover o item
    for (i = pos; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;
    printf("Item removido com sucesso!\n");
}

// Lista todos os itens da mochila
void listarItens(Item mochila[], int qtd) {
    printf("\n--- Itens na mochila ---\n");
    if (qtd == 0) {
        printf("Mochila vazia.\n");
    } else {
        for (int i = 0; i < qtd; i++) {
            printf("%2d) Nome: %-20s | Tipo: %-10s | Quantidade: %d\n",
                   i + 1,
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }
    printf("------------------------\n");
}

// Busca sequencial por nome e exibe o item, se encontrar
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    char alvo[TAM_NOME];
    printf("\n--- Buscar item ---\n");
    printf("Digite o NOME do item a ser buscado: ");
    fgets(alvo, TAM_NOME, stdin);
    removerQuebraLinha(alvo);

    int i;
    for (i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado na mochila.\n");
}

// -------------------------------------------------------
// Função principal - menu do nível Novato
// -------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;  // quantidade atual de itens
    int opcao;

    printf("===== Nível Novato - Sistema de Inventario (Mochila) =====\n");

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;

            case 2:
                removerItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;

            case 3:
                listarItens(mochila, qtd);
                break;

            case 4:
                buscarItem(mochila, qtd);
                break;

            case 0:
                printf("\nSaindo do sistema de inventario. Boa sorte no loot inicial!\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
