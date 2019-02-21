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
int sum = 0; 
int square = 0;
//Fuctions
void getDataFromfile(void * param, FILE * file);
void *validateRow(void *param);
void *validateColumn(void *param);
void *validateSquare(void *param);
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
    int  sudoku[ROWS][COLUMNS];
    getDataFromfile((void *) sudoku, file);
    fclose(file);
    printGrid(sudoku);
    for(int x = 0; x < ROWS; x++){
        pthread_create(&tid[x], &attr[x], validateRow, (void *) sudoku);
        row++;
    } 
    for(int x = COLUMNS; x < COLUMNS + COLUMNS; x++){
        pthread_create(&tid[x], &attr[x], validateColumn, (void *) sudoku);
        column++;
    }
    column = 0;
    row = 0;
    for(int x = 18; x < 21 ; x++){
        sum=0;
        pthread_create(&tid[x], &attr[x], validateSquare, (void *) sudoku);
        row += 3;
    }
    column += 3;
    row = 0;
    for(int x = 21; x < 24; x++){
        sum = 0;
        pthread_create(&tid[x], &attr[x], validateSquare, (void *) sudoku);
        row += 3;
    }
    column += 3;
    row = 0;
    for(int x = 24; x < 27; x++){
        sum = 0;
        pthread_create(&tid[x], &attr[x], validateSquare, (void *) sudoku);
        row += 3;
    }

    for(int j = 0; j < 22; j++)
        pthread_join(tid[j], NULL);
    
    if(valid == '1'){
        printf("The Sudoku is valid\n");
    }
    else{
        printf("%c",valid);
        printf("The Sudoku is't valid\n");
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
void *validateRow(void *param){
    int (*sudoku)[ROWS] = param;
    for (int i = 0; i < 9; i++){
        for (int j = i+1; j < 9; j++) {
            if (sudoku[i][row] == sudoku[j][row]) {
                valid = '0';
            }
        }
    }
    pthread_exit(0);
}
void *validateColumn(void *param){
   int (*sudoku)[ROWS] = param;
   for (int i = 0; i < 9; i++){
        for (int j = i + 1; j < 9; j++) {
            if (sudoku[i] == sudoku[j]) {
                valid = '0';
            }
        }
    }
   pthread_exit(0);
}
void *validateSquare(void *param){
    
    int (*sudoku)[9] = param;
    int x = 0, y;

    if(square < 3){
        x = 0;
    } 
    else if (square < 6){
         x = 3;
    }
    y = (square % 3)*3;
    for(int posX = x; posX < x+3; posX++){
        for(int posY = y; posY < y+3; posY++){
            for(int i = posX; i < x+3; i++){
                for(int j = posY; j < y+3; j++){
                    if(posX != i || posY != j){
                        if(sudoku[posX][posY] == sudoku[i][j]){
                            valid = '0';
                        }
                    }
                }
            }
        }
    }
    square++;
    pthread_exit(0);
}
    