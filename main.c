//Librarys
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Costants
#define THREADS 27

//Global Variables
char valid = '1';
int row = 0;
int column = 0;

//Fuctions
void getDataFromfile(void * param, FILE * file);
void validateRow(void *param);
void validateColumn(void *param);
void validateSquare(void *param);
void printGrid(void * param);

int main(int argc, char *argv[]) {
    pthread_t tid[THREADS];
    pthread_attr_t attr[THREADS];
    FILE * file;

    if (argc < 2){
        printf("Error! Retry please");
        return -1;
    }

    for(int i = 0; i < THREADS; i++){
        pthread_attr_init(&attr[i]);
    }

    file = fopen(argv[1], "r");
    int  sudoku[THREADS/3][THREADS/3];
    getDataFromfile((void *) sudoku, file);
    fclose(file);

    for(int x = 0; x < 9; x++){
        pthread_create(&tid[x], &attr[x], validateRow, (void *) sudoku);
    }
    row = 0;

}

void printGrid(void * param){
    int(*sudoku)[9] = param;
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            printf("%d ", sudoku[x][y]);
        }
        printf("\n");
    }
}
void getDataFromfile(void * param, FILE * file){
    int index;
    int (*sudoku)[9] = param;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(file, "%d", &sudoku[j][i]);
            index++;
        }
    }
}
void validateRow(void *param){
    int (*rows)[9] = param;
    int sum = 0;  
    for(int i = 0; i < 9; i++){
        sum += rows[row][i];
        if(sum > 45){
            valid = '0';
        }else if(rows[i][row] > 9 || rows[row][i] < 1){
            valid = '0';
        }
    }
    row++;
    pthread_exit(0);
}
void validateColumn(void *param){
   
}