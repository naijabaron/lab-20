#ifndef OP_LAB_20_LAB_20_SOLUTIONS_H
#define OP_LAB_20_LAB_20_SOLUTIONS_H

#include <corecrt.h>

#define MAX_DOMAIN_LENGTH 256
#define MAX_DOMAIN_AMOUNT 10000

typedef struct {
    char domain[MAX_DOMAIN_LENGTH];
    int count;
} Domain;

typedef struct TreeNode {
    int digit;
    struct TreeNode *right;
    struct TreeNode *left;
} TreeNode;

int** addOneToMatrix(size_t size, int **query, int querySize);

void nextGeneration(int** board, size_t rows, size_t columns);

void printBoard(int** board, size_t rows, size_t columns);

int countNeighbors(int** board, size_t rows, size_t columns, int i, int j);

void applyMedianFilter(int** matrix, size_t rows, size_t columns, int filterSize);

int findMedian(int array[], int size);

void sortArray(int array[], int size);

void printMatrix(int** matrix, size_t rows, size_t columns);

void countDomains(char* cpdomains[]);

int compare(const void *a, const void *b);

int countSubMatrices(int** matrix, size_t rows, size_t columns);

void increaseAndDecreaseByIandD(const char* pattern, char* result);

void printTreeInOrder(TreeNode* node);

int returnMaxDigit(const int* nums, size_t size);

TreeNode* buildTree(const int* nums, int left, int right);

TreeNode* createNode(int value);

void swap(char* a, char* b);

void permute(char* s, int* indices, int n);

void taskNine(char* args[], int argAmount);

void taskTen(char* args[], int argAmount);

#endif //OP_LAB_20_LAB_20_SOLUTIONS_H