#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct No {
    char info;
    struct No* proximo;
} No;

typedef struct Fila {
    No* ini;
    No* fim;
} Fila;

void fila_entrar(Fila* fila) {
    fila->ini = fila->fim = NULL;
}

int fila_sair(Fila* fila) {
    return (fila->ini == NULL);
}

void fila_enfileirar(Fila* fila, char info) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->info = info;
    novoNo->proximo = NULL;

    if (fila_sair(fila)) {
        fila->ini = novoNo;
    } else {
        fila->fim->proximo = novoNo;
    }
    fila->fim = novoNo;
}

char fila_desenfileirar(Fila* fila) {
    if (fila_sair(fila)) {
        printf("\nA fila de nucleotideos está vazia.");
        return '\0';
    }

    No* temp = fila->ini;
    char info = temp->info;
    fila->ini = fila->ini->proximo;

    if (fila->ini == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return info;
}

void mostrar_fila(Fila* fila) {
    if (fila_sair(fila)) {
        printf("\nFila de nucleotideos: (vazia)");
        return;
    }

    No* atual = fila->ini;
    printf("\nFila de nucleotideos: ");
    while (atual != NULL) {
        printf("%c", atual->info);
        atual = atual->proximo;
    }
    printf("\n");
}

typedef struct NoPilha {
    char info;
    struct NoPilha* proximo;
} NoPilha;

typedef struct Pilha {
    NoPilha* topo;
} Pilha;

void pilha_entrar(Pilha* pilha) {
    pilha->topo = NULL;
}

int pilha_sair(Pilha* pilha) {
    return (pilha->topo == NULL);
}

void pilha_empilhar(Pilha* pilha, char info) {
    NoPilha* novoNo = (NoPilha*)malloc(sizeof(NoPilha));
    novoNo->info = info;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

char pilha_desempilhar(Pilha* pilha) {
    if (pilha_sair(pilha)) {
        printf("\nA pilha nucleotideos está vazia.");
        return '\0';
    }

    NoPilha* temp = pilha->topo;
    char info = temp->info;
    pilha->topo = pilha->topo->proximo;

    free(temp);
    return info;
}

void mostrar_pilha(Pilha* pilha) {
    if (pilha_sair(pilha)) {
        printf("\nPilha nucleotideos: (vazia)");
        return;
    }

    NoPilha* atual = pilha->topo;
    printf("\nPilha de nucleotideos : ");
    while (atual != NULL) {
        printf("%c", atual->info);
        atual = atual->proximo;
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Fila fila = {NULL, NULL};
    Fila fila_auxiliar = {NULL, NULL};
    Pilha pilha;
    char nucleotideo;
    int i;
    int sequencia_valida = 1; 
    int sequencia_invalida_exibida = 0; 

    fila_entrar(&fila);
    pilha_entrar(&pilha);

    char sequencia[100];
    printf("\nDigite uma sequencia de nucleotideos válidos (do tipo A G C T): ");
    scanf("%s", sequencia);

    for (i = 0; sequencia[i] != '\0'; i++) {
        fila_enfileirar(&fila, sequencia[i]);
    }

    while (!fila_sair(&fila)) {
        nucleotideo = fila_desenfileirar(&fila);

        switch (nucleotideo) {
            case 'A':
                pilha_empilhar(&pilha, 'T');
                fila_enfileirar(&fila_auxiliar, nucleotideo); 
                break;
            case 'T':
                pilha_empilhar(&pilha, 'A');
                fila_enfileirar(&fila_auxiliar, nucleotideo); 
                break;
            case 'C':
                pilha_empilhar(&pilha, 'G');
                fila_enfileirar(&fila_auxiliar, nucleotideo); 
                break;
            case 'G':
                pilha_empilhar(&pilha, 'C');
                fila_enfileirar(&fila_auxiliar, nucleotideo); 
                break;
            default:
                if (!sequencia_invalida_exibida) {
                    printf("\nSequencia de nucleotideos inválida. \n");
                    printf("A sequencia de nucleotideos deve ser escrita em caixa alta.\n");
                    sequencia_valida = 0; 
                    sequencia_invalida_exibida = 1; 
            }
            break;
        }
    }

    if (sequencia_valida) {
        mostrar_fila(&fila_auxiliar); 
        mostrar_pilha(&pilha);
    }

    return 0;
}
