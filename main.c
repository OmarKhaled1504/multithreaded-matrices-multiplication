#include <stdio.h>
#include <malloc.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

int rows1, columns1, rows2, columns2, thCount = 0, argsIndex = 0, args2Index = 0;
int **m1; //matrix 1
int **m2; //matrix 2
int **mrByElement; //result matrix
int **mrByRow; //result matrix

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

void *threadToRow(void *args) {
    int *arguments = (int *) args;
    int i = arguments[0];
    for (int j = 0; j < columns2; j++) {
        mrByRow[i][j] = 0;
        for (int k = 0; k < rows2; k++)
            mrByRow[i][j] += m1[i][k] * m2[k][j];
    }
}

void multiplyByRow() {

    pthread_t *thArrByRow = malloc(sizeof(pthread_t) * rows1);

    int *args2 = malloc(sizeof(int) * 2 * rows1);
    for (int i = 0; i < rows1; i++) {
        args2[args2Index++] = i;
        pthread_create(&thArrByRow[thCount++], NULL, &threadToRow, (void *) &args2[args2Index - 1]);
    }
    for (int i = 0; i < thCount; i++) {
        pthread_join(thArrByRow[i], NULL);
    }
    printf("Resultant Matrix By Row: \n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; j++) {
            printf("%d ", mrByRow[i][j]);
        }
        printf("\n");
    }
}

void *threadToElement(void *args) {
    int *arguments = (int *) args;
    int i = arguments[0];
    int j = arguments[1];
//    printf("%d %d\n",i,j);

    for (int k = 0; k < rows2; k++)
        mrByElement[i][j] += m1[i][k] * m2[k][j];

}

void multiplyByElement() {

    int threadCount = rows1 * columns2;
    pthread_t *thArrByElement = malloc(sizeof(pthread_t) * threadCount);

    int *args = malloc(sizeof(int) * 2 * threadCount);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; j++) {
            mrByElement[i][j] = 0;
            args[argsIndex++] = i;
            args[argsIndex++] = j;
            pthread_create(&thArrByElement[thCount++], NULL, &threadToElement, (void *) &args[argsIndex - 2]);
        }

    }
    for (int i = 0; i < thCount; i++) {
        pthread_join(thArrByElement[i], NULL);
    }
    thCount = 0;
    printf("Resultant Matrix By Element: \n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; j++) {
            printf("%d ", mrByElement[i][j]);
        }
        printf("\n");
    }
}

int main() {

    input();
    mrByElement = (int **) malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; ++i) {
        mrByElement[i] = (int *) malloc(columns2 * sizeof(int *));
    }
    mrByRow = (int **) malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; ++i) {
        mrByRow[i] = (int *) malloc(columns2 * sizeof(int *));
    }
    clock_t t1 = clock();

    multiplyByElement();
    t1 = clock() - t1;
    double time1 = ((double) t1) / CLOCKS_PER_SEC;
    printf("Elapsed Time: %f\n", time1);
    clock_t t2 = clock();
    multiplyByRow();
    t2 = clock() - t2;
    double time2 = ((double) t2) / CLOCKS_PER_SEC;
    printf("Elapsed Time: %f", time2);
    return 0;
}
