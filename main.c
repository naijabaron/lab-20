#include "libs/solutions/lab_20//lab_20_solutions.h"
#include <assert.h>
#include <stdio.h>
#include <windows.h>

void testFuncAddOneToMatrix() {
    int query1[4] = {0, 0, 1, 1};
    int query2[4] = {1, 1, 2, 2};
    int *queries[] = {query1, query2};

    int** matrix = addOneToMatrix(3, (int **)queries, 2);

    assert(matrix[0][0] == 1);
    assert(matrix[0][1] == 1);
    assert(matrix[0][2] == 0);
    assert(matrix[1][0] == 1);
    assert(matrix[1][1] == 2);
    assert(matrix[1][2] == 1);
    assert(matrix[2][0] == 0);
    assert(matrix[2][1] == 1);
    assert(matrix[2][2] == 1);
}

void testGameOfLife() {
    int board[3][3] = {
            {1, 0, 1},
            {0, 1, 0},
            {1, 1, 0}
    };

    int expectedCounts[3][3] = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0}
    };

    assert(countNeighbors(board, 3, 3, 1, 1) == 5);

    printf("Current Board:\n");
    printBoard(board, 3, 3);

    nextGeneration(board, 3, 3);
    printf("Next Generation:\n");
    printBoard(board, 3, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(board[i][j] == expectedCounts[i][j]);
        }
    }
}

void testSortArray() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    for (int i = 0; i < n; i++) {
        assert(arr[i] == expected[i]);
    }
}
void testFindMedian() {
    int arr[] = {3, 1, 4, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int median = findMedian(arr, n);

    assert(median == 3);
}

void testApplyMedianFilter() {
    int matrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    applyMedianFilter(matrix, 3, 3, 3);
}

void testDomain() {
    char cpdomains[4][MAX_DOMAIN_LENGTH] = {
            "9001 discuss.codeforces.com",
            "900 google.mail.com",
            "50 yahoo.com",
            "1 intel.mail.com"
    };

    char* cpdomains_ptr[4];
    for (int i = 0; i < 4; i++) {
        cpdomains_ptr[i] = cpdomains[i];
    }

    // Задаем ожидаемый вывод
    char expectedOutput[5][MAX_DOMAIN_LENGTH] = {
            "9001 com",
            "900 mail.com",
            "901 codeforces.com",
            "50 yahoo.com",
            "1 intel.mail.com"
    };

    freopen("temp_output.txt", "w", stdout);

    countDomains(cpdomains_ptr);

    FILE *fp = fopen("temp_output.txt", "r");
    char line[MAX_DOMAIN_LENGTH];
    int lineCount = 0;
    while (fgets(line, sizeof(line), fp)) {
        assert(strcmp(line, expectedOutput[lineCount]) == 0);
        lineCount++;
    }
    fclose(fp);

    remove("temp_output.txt");
}

void testCountSubmatrices() {
    int matrix[3][3] = {
            {1, 0, 1},
            {1, 1, 0},
            {1, 1, 0}
    };

    assert(countSubMatrices(matrix, 3, 3) == 13);

    int matrix2[3][3] = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
    };

    assert(countSubMatrices(matrix2, 3, 3) == 28);

    int matrix3[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };

    assert(countSubMatrices(matrix3, 3, 3) == 0);

    int matrix4[3][3] = {
            {1, 0, 1},
            {0, 1, 0},
            {1, 0, 1}
    };

    assert(countSubMatrices(matrix4, 3, 3) == 7);
}
void testFuncIncreaseAndDecreaseByIandD(){
    char pattern[] = "IIIDIDDD";
    char result[10];

    increaseAndDecreaseByIandD(pattern, result);
    printf("%s\n", result);
    increaseAndDecreaseByIandD(pattern, result);
    assert(result == "123549876");
}

void testGenerateNum(char* pattern, char* expected) {
    char result[10];
    increaseAndDecreaseByIandD(pattern, result);
    if (strcmp(result, expected) == 0) {
        printf("Pattern: %s, Result: %s - Test Passed\n", pattern, result);
    } else {
        printf("Pattern: %s, Result: %s - Test Failed (Expected: %s)\n", pattern, result, expected);
    }
}

void testTree(){
    const int nums[] = {3, 2, 1, 6, 0, 5};
    int size = sizeof(nums) / sizeof(nums[0]);

    TreeNode * rootNode = buildTree(nums, 0, size - 1);

    printf("Построенное дерево в порядке обхода в глубину (in-order): ");
    printTreeInOrder(rootNode);

}

void testSwapIndexesAndLetter(){
    char s[] = "abap";
    int indices[] = {0, 3, 2, 1};
    int n = strlen(s);

    permute(s, indices, n);
    printf("%s\n", s);
}

void test() {
    testFuncAddOneToMatrix();
    testGameOfLife();
    testApplyMedianFilter();
    testFindMedian();
    testSortArray();
    testDomain();
    testCountSubmatrices();
    testFuncIncreaseAndDecreaseByIandD();
    testGenerateNum("IIIDIDDD", "123549876");
    testTree();
    testSwapIndexesAndLetter();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    test();
}