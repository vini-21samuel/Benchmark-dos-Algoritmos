#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um arquivo com números aleatórios
void gerarArquivo(const char *nomeArquivo, int quantidade) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo != NULL) {
        for (int i = 0; i < quantidade; i++) {
            int numero = rand() % 1000; // Números aleatórios entre 0 e 999
            fprintf(arquivo, "%d ", numero);
        }
        fclose(arquivo);
        printf("Arquivo gerado com sucesso!\n");
    } else {
        perror("Erro ao abrir o arquivo");
    }
}

// Algoritmo de ordenação: Insertion Sort
void insertionSort(int arr[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

// Algoritmo de ordenação: Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função auxiliar para o Quick Sort: particiona o array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Algoritmo de ordenação: Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função de busca linear em um arquivo
int buscaLinear(const char *nomeArquivo, int alvo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL) {
        int numero;
        int posicao = 0;
        while (fscanf(arquivo, "%d", &numero) != EOF) {
            posicao++;
            if (numero == alvo) {
                fclose(arquivo);
                return posicao;
            }
        }
        fclose(arquivo);
    } else {
        perror("Erro ao abrir o arquivo");
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

// Função de busca com sentinela em um arquivo
int buscaSentinela(const char *nomeArquivo, int alvo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL) {
        int numero;
        int posicao = 0;
        while (fscanf(arquivo, "%d", &numero) != EOF) {
            posicao++;
            if (numero == alvo) {
                fclose(arquivo);
                return posicao;
            }
        }
        fclose(arquivo);
    } else {
        perror("Erro ao abrir o arquivo");
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

// Função de busca binária em um arquivo
int buscaBinaria(const char *nomeArquivo, int alvo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL) {
        int numero;
        int posicao = 0;
        int *numeros = NULL;
        int tamanho = 0;

        while (fscanf(arquivo, "%d", &numero) != EOF) {
            tamanho++;
            numeros = (int *)realloc(numeros, tamanho * sizeof(int));
            numeros[tamanho - 1] = numero;
        }

        fclose(arquivo);

        int esquerda = 0, direita = tamanho - 1;
        int meio;

        while (esquerda <= direita) {
            posicao++;
            meio = esquerda + (direita - esquerda) / 2;

            if (numeros[meio] == alvo) {
                free(numeros);
                return posicao;
            }

            if (numeros[meio] < alvo)
                esquerda = meio + 1;
            else
                direita = meio - 1;
        }

        free(numeros);
    } else {
        perror("Erro ao abrir o arquivo");
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

int main() {
    srand(time(NULL));

    int opcao, quantidade, alvo;
    char nomeArquivo[] = "numeros.txt";

    // Solicita a quantidade de números a serem gerados
    printf("Digite a quantidade de números a serem gerados: ");
    scanf("%d", &quantidade);

    // Gera o arquivo com números aleatórios
    gerarArquivo(nomeArquivo, quantidade);

    // Menu de opções
    printf("\nEscolha uma opção:\n");
    printf("1- busca de elemento\n");
    printf("2- Classificação de Elementos (Bubble Sort, Insertion Sort, Quick Sort)\n");
    printf("3- Sair\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        // Busca Linear
        printf("Digite o número que deseja buscar: ");
        scanf("%d", &alvo);
        clock_t inicio = clock();
        int posicaoLinear = buscaLinear(nomeArquivo, alvo);
        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (posicaoLinear != -1) {
            printf("Elemento encontrado na posição %d (Busca Linear)\n", posicaoLinear);
        } else {
            printf("Elemento não encontrado (Busca Linear)\n");
        }
        printf("Tempo de execução da Busca Linear: %f segundos\n", tempo);

        // Busca Sentinela
        inicio = clock();
        int posicaoSentinela = buscaSentinela(nomeArquivo, alvo);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (posicaoSentinela != -1) {
            printf("Elemento encontrado na posição %d (Busca Sentinela)\n", posicaoSentinela);
        } else {
            printf("Elemento não encontrado (Busca Sentinela)\n");
        }
        printf("Tempo de execução da Busca Sentinela: %f segundos\n", tempo);

        // Busca Binária
        inicio = clock();
        int posicaoBinaria = buscaBinaria(nomeArquivo, alvo);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (posicaoBinaria != -1) {
            printf("Elemento encontrado na posição %d (Busca Binária)\n", posicaoBinaria);
        } else {
            printf("Elemento não encontrado (Busca Binária)\n");
        }
        printf("Tempo de execução da Busca Binária: %f segundos\n", tempo);
    } else if (opcao == 2) {
        // Operações de classificação
        int *numeros = malloc(quantidade * sizeof(int));
        FILE *arquivo = fopen(nomeArquivo, "r");
        if (arquivo != NULL) {
            for (int i = 0; i < quantidade; i++) {
                if (fscanf(arquivo, "%d", &numeros[i]) == EOF) {
                    break;
                }
            }
            fclose(arquivo);

            clock_t inicio, fim;
            double tempo;

            // Classificação com Insertion Sort
            int *copiaInsertionSort = malloc(quantidade * sizeof(int));
            for (int i = 0; i < quantidade; i++) {
                copiaInsertionSort[i] = numeros[i];
            }
            inicio = clock();
            insertionSort(copiaInsertionSort, quantidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo de execução do Insertion Sort: %f segundos\n", tempo);
            free(copiaInsertionSort);

            // Classificação com Bubble Sort
            int *copiaBubbleSort = malloc(quantidade * sizeof(int));
            for (int i = 0; i < quantidade; i++) {
                copiaBubbleSort[i] = numeros[i];
            }
            inicio = clock();
            bubbleSort(copiaBubbleSort, quantidade);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo de execução do Bubble Sort: %f segundos\n", tempo);
            free(copiaBubbleSort);

            // Classificação com Quick Sort
            int *copiaQuickSort = malloc(quantidade * sizeof(int));
            for (int i = 0; i < quantidade; i++) {
                copiaQuickSort[i] = numeros[i];
            }
            inicio = clock();
            quickSort(copiaQuickSort, 0, quantidade - 1);
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo de execução do Quick Sort: %f segundos\n", tempo);
            free(copiaQuickSort);
        } else {
            perror("Erro ao abrir o arquivo");
        }
        free(numeros);
        
    } else if (opcao == 3) {
        printf("Encerrando o programa. Obrigado!\n");
    } else {
        printf("Opção inválida!\n");
    }

    return 0;
}
