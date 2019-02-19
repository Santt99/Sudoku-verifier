//Librarys
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Costants
#define THREADS 27
#define COLUMNS 9
#define ROWS 9
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

    for(int x = 0; x < ROWS; x++){
        pthread_create(&tid[x], &attr[x], validateRow, (void *) sudoku);
    }
    for(int x = COLUMNS; x < COLUMNS + COLUMNS; x++){
        pthread_create(&tid[x], &attr[x], validateColumn, (void *) sudoku);
    }

}

void printGrid(void * param){
    int(*sudoku)[ROWS] = param;
    for(int x = 0; x < ROWS; x++){
        for(int y = 0; y < COLUMNS; y++){
            printf("%d ", sudoku[x][y]);
        }
        printf("\n");
    }
}
void getDataFromfile(void * param, FILE * file){
    int index;
    int (*sudoku)[ROWS] = param;
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < ROWS; j++){
            fscanf(file, "%d", &sudoku[j][i]);
            index++;
        }
    }
}
void validateRow(void *param){
    int (*sudoku)[ROWS] = param;
    int sum = 0;  
    for(int i = 0; i < 9; i++){
        sum += sudoku[row][i];
        if(sum > 45){
            valid = '0';
        }else if(sudoku[row][i] > 9 || sudoku[row][i] < 1){
            valid = '0';
        }
    }
    row++;
    pthread_exit(0);
}
void validateColumn(void *param){
   int (*sudoku)[ROWS] = param;
   int sum = 0;  
   for(int i = 0; i < ROWS; i++){
       sum += sudoku[i][column];
        if(sum > 45){
            valid = '0';
        }else if(sudoku[i][row] > 9 || sudoku[i][column] < 1){
            valid = '0';
        }
   }
   pthread_exit(0);
}