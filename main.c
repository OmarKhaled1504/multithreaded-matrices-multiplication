#include <stdio.h>

#include <malloc.h>

int rows1, columns1, rows2, columns2;
int **m1; //matrix 1
int **m2; //matrix 2
int **mr; //result matrix
void input() {
    char fname[100];
    printf("Enter file name: ");
    scanf("%s", &fname);
    FILE *fp = fopen(fname, "r");
    fscanf(fp, "%d%d", &rows1, &columns1);
    m1 = (int **) malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; ++i) {
        m1[i] = (int *) malloc(columns1 * sizeof(int *));
    }
    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < columns1; j++) {
            fscanf(fp, "%d ", &m1[i][j]);
        }
    fscanf(fp, "%d%d", &rows2, &columns2);
    m2 = (int **) malloc(rows2 * sizeof(int *));
    for (int i = 0; i < rows2; ++i) {
        m2[i] = (int *) malloc(columns2 * sizeof(int *));
    }
    for (int i = 0; i < rows2; i++)
        for (int j = 0; j < columns2; j++) {
            fscanf(fp, "%d ", &m2[i][j]);
        }
    printf("Input matrices: \n");
    printf("Matrix 1: \n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns1; j++) {
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }
    printf("Matrix 2: \n");
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < columns2; j++) {
            printf("%d ", m2[i][j]);
        }
        printf("\n");
    }

}

void multiply() {
    mr = (int **) malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; ++i) {
        mr[i] = (int *) malloc(columns2 * sizeof(int *));
    }
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; ++j) {
            mr[i][j] = 0;
            for (int k = 0; k < rows2; k++)
                mr[i][j] += m1[i][k] * m2[k][j];
            printf("%d\t", mr[i][j]);
        }
        printf("\n");
    }
}

int main() {

    input();
    multiply();

    return 0;
}
