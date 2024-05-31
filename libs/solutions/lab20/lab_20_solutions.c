#include "lab_20_solutions.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <signal.h>
#include <unistd.h>

int** addOneToMatrix(size_t size, int** query, int querySize) {
    int **matrix = (int**) malloc(size * sizeof(int*));

    for (size_t i = 0; i < size; i++) {
        matrix[i] = (int*) calloc(size, sizeof(int));
    }

    for (size_t i = 0; i < querySize; i++) {
        int row1 = query[i][0];
        int col1 = query[i][1];
        int row2 = query[i][2];
        int col2 = query[i][3];

        for (size_t x = row1; x <= row2; x++) {
            for (size_t y = col1; y <= col2; y++) {
                matrix[x][y]++;
            }
        }
    }

    return matrix;
}

int countNeighbors(int** board, size_t rows, size_t columns, int i, int j) {
    int count = 0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            count += board[(i + x + rows) % rows][(j + y + columns) % columns];
        }
    }

    return count - board[i][j];
}

void printBoard(int** board, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            printf("%d ", board[i][j]);
        }

        printf("\n");
    }
}

void nextGeneration(int** board, size_t rows, size_t columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int neighbors = countNeighbors(board, rows, columns, i, j);

            if (board[i][j] == 1) {
                board[i][j] = ((neighbors < 2) || (neighbors > 3)) ? 0 : 1;
            } else {
                board[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}

void printMatrix(int** matrix, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}

void sortArray(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int findMedian(int array[], int size) {
    sortArray(array, size);
    return array[size / 2];
}

void applyMedianFilter(int** matrix, size_t rows, size_t columns, int filterSize) {
    int paddedMatrix[rows + filterSize - 1][columns + filterSize - 1];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            paddedMatrix[i + filterSize / 2][j + filterSize / 2] = matrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int window[filterSize * filterSize];
            int k = 0;
            for (int x = -filterSize / 2; x <= filterSize / 2; x++) {
                for (int y = -filterSize / 2; y <= filterSize / 2; y++) {
                    window[k++] = paddedMatrix[i + x][j + y];
                }
            }
            matrix[i][j] = findMedian(window, filterSize * filterSize);
        }
    }
}

int compare(const void *a, const void *b) {
    Domain *domain1 = (Domain *)a;
    Domain *domain2 = (Domain *)b;
    return strcmp(domain1->domain, domain2->domain);
}

void countDomains(char* cpdomains[]) {
    Domain domains[MAX_DOMAIN_AMOUNT];

    int domainCount = 0;
    for (int i = 0; i < MAX_DOMAIN_AMOUNT; i++) {
        char *token = strtok(cpdomains[i], " ");

        if (token == NULL) break;

        int count = atoi(token);
        token = strtok(NULL, " ");
        char *domain = token;

        while (domain) {
            Domain domainData;
            strcpy(domainData.domain, domain);
            domainData.count = count;
            domains[domainCount++] = domainData;

            char *dot = strchr(domain, '.');

            while (dot) {
                *dot = '\0';
                strcpy(domainData.domain, domain);
                domainData.count = count;
                domains[domainCount++] = domainData;
                *dot = '.';
                dot = strchr(dot + 1, '.');
            }

            token = strtok(NULL, " ");
            domain = token;
        }
    }

    qsort(domains, domainCount, sizeof(Domain), compare);

    for (int i = 0; i < domainCount; i++) {
        int total_count = domains[i].count;

        while (i + 1 < domainCount && strcmp(domains[i].domain, domains[i+1].domain) == 0) {
            total_count += domains[i+1].count;
            i++;
        }

        printf("%d %s\n", total_count, domains[i].domain);
    }
}

int countSubMatrices(int** matrix, size_t rows, size_t columns) {
    int numbers[rows][columns];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                numbers[i][j] = 0;
            } else {
                numbers[i][j] = (j > 0 ? numbers[i][j - 1] : 0) + 1;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            for (int k = j; k < columns; k++) {
                int min_val = numbers[i][j];

                for (int l = i; l < rows; l++) {
                    count += (min_val = (numbers[l][k] < min_val ? numbers[l][k] : min_val));
                }
            }
        }
    }

    return count;
}

void increaseAndDecreaseByIandD(const char* pattern, char* result) {
    int length = (int) strlen(pattern);
    int numbers[10] = {0};
    char number[length + 1];

    int currentMin = 0, currentMax = 9, index = 0;

    for (int i = 0; i <= length; i++) {
        if (i == length || pattern[i] == 'I') {
            result[i] = '\0';

            while (numbers[currentMin]) currentMin++;

            numbers[currentMin] = 1;
            number[index++] = '0' + currentMin;

            for (int j = index - 1; j >= 0; j--) {
                for (int k = number[j + 1] ? number[j + 1] - '0' : currentMax; k > number[j] - '0'; k--) {
                    if (!numbers[k]) {
                        numbers[k] = 1;
                        number[j] = '0' + k;
                        for (int l = j + 1; l < index; l++) {
                            for (int m = currentMin; m <= currentMax; m++) {
                                if (!numbers[m]) {
                                    numbers[m] = 1;
                                    number[l] = '0' + m;
                                    break;
                                }
                            }
                        }
                        currentMin = 0;
                        index = length;
                        break;
                    }
                }
            }
        } else {
            result[i] = '9';
            numbers[9] = 1;
            for (int j = length - i; j > 0; j--) {
                for (int k = '0' + currentMax; k >= '0'; k--) {
                    if (!numbers[k - '0']) {
                        result[i+j] = k;
                        numbers[k - '0'] = 1;
                        currentMax = k - '0' - 1;
                        break;
                    }
                }
            }
        }
    }
}

int returnMaxDigit(const int *nums, size_t size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->digit = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildTree(const int *nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int maxIndex = left;

    for (int i = left + 1; i <= right; i++) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    TreeNode* root = createNode(nums[maxIndex]);
    root->left = buildTree(nums, left, maxIndex - 1);
    root->right = buildTree(nums, maxIndex + 1, right);

    return root;
}

void printTreeInOrder(TreeNode* node) {
    if (node == NULL) {
        return;
    }

    printTreeInOrder(node->left);
    printf("%d ", node->digit);
    printTreeInOrder(node->right);
}

void swap(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void permute(char* s, int* indices, int n) {
    for (int i = 0; i < n; i++) {
        if (indices[i] != i) {
            swap(&s[i], &s[indices[i]]);
            int temp = indices[i];
            indices[i] = indices[temp];
            indices[temp] = temp;
        }
    }
}

void taskNine(char *args[], int argAmount) {
    SetConsoleOutputCP(CP_UTF8);

    if (argAmount < 4) {
        printf("Использование: программа <исходный_файл> <файл-результат> <число>\n");
        exit(EXIT_FAILURE);
    }

    char *inputFileName = args[1];
    char *outputFileName = args[2];
    int N = atoi(args[3]);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Ошибка при открытии файлов.\n");
        exit(EXIT_FAILURE);
    }

    int num;
    while (fscanf(inputFile, "%d", &num) == 1) {
        if (num < N) {
            fprintf(outputFile, "%d\n", num);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Файл с числами, меньшими чем %d, успешно создан.\n", N);
}

static void handleSignal(int signal) {
    printf("\n");
    fflush(stdout);
}

void taskTen(char* args[], int argAmount) {
    if (argAmount != 3) {
        printf("Неверное количество аргументов. Использование: %s <файл> <Число>\n", args[0]);
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(args[1], "r");
    if (file == NULL) {
        printf("Не удается открыть файл %s для чтения\n", args[1]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(args[2]);
    if (N <= 0) {
        printf("Число должно быть больше нуля\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int lineCount = 0;

    signal(SIGINT, handleSignal);

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        fflush(stdout);

        lineCount++;
        if (lineCount == N) {
            lineCount = 0;
            signal(SIGINT, handleSignal);
            sleep(1);
        }
    }

    fclose(file);
}