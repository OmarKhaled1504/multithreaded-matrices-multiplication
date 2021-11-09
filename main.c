#include <stdio.h>
#include <stdlib.h>

#define r1 4
#define c1 4
#define r2 4
#define c2 4

void multiply(int matrix1[][c1], int matrix2[][c2]) {
    int result[2][2];
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < r2; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int matrix1[r1][c1] = {
            {1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}
    };

    int matrix2[r2][c2] = {
            {1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}
    };
    if (c1 == c2)
        multiply(matrix1, matrix2);
    else
        printf("# of columns in matrix 1 not equal to the # of rows in matrix 2\n");
    return 0;
}
