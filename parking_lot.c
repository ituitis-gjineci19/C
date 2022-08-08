#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Write a C program that will get the size of the parking area(matrix), the number of cars parked, and a sequence
of locations occupied by the cars.
You are required to calculate the distance between two locations using Manhattan distance.
Return the empty slot which has the largest distance to all cars.
If there are two locations that can potentially be the best slots your program should return the one with the smaller X value.
If they both have the same X value, then your program should return the one with the smaller Y value
*/

int main(){

    int size;
    printf("Enter the size of the parking area: ");
    scanf("%d", &size);
    int parking_lot[size][size];
    //initializing the array
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            parking_lot[i][j] = 0;
        }
    }


    int cars;
    printf("\nNumber of cars: ");
    scanf("%d", &cars);
    if(cars > size*size){
        printf("Too many cars for the slot. Please enter a new number: ");
        scanf("%d", &cars);
    }


    int x, y;
    for(int i = 0; i < cars; i++){
        printf("\nEnter the coordinates:");
        scanf("%d %d", &x, &y);
        while(x > size || y > size){
            printf("These coordinates are not correct. Please enter new ones: ");
            scanf("%d %d", &x, &y);
        }
        if(parking_lot[x-1][y-1] == 1){
            printf("This parking space is already occupied. Choose another one: ");
            scanf("%d %d", &x, &y);
        }
        parking_lot[x-1][y-1] = 1;
    }


    int empty_slots = size*size - cars;


    int sum[empty_slots];       //array to keep track of all empty slots' distance
    for(int i = 0; i < empty_slots; i++){
        sum[i] = 0;
    }
    int coordinates[empty_slots][2];        //matrix to keep track of all empty slots' coordinates
    int index = 0;
    int distance = 0;
    for(int i = 0; i<size; i++){
        for(int j=0; j<size; j++){
            if(parking_lot[i][j] == 0){
                for(int k = 0; k<size; k++){
                    for(int m=0; m<size; m++){
                        if(parking_lot[k][m] == 1){
                            distance = abs(k-i) + abs(m-j);
                            sum[index] += distance;                 //Manhattan distance
                            coordinates[index][0] = i;
                            coordinates[index][1] = j;
                        }
                    }
                }
                index += 1;
            }
        }
    }

    int max = 0;
    int x_coordinate = 0, y_coordinate = 0;
    printf("Distance\tCoordinates\n");
    for(int a = 0; a < empty_slots; a++){
        printf("%d\t\t(%d,%d)\n", sum[a], coordinates[a][0]+1, coordinates[a][1]+1);
        if(max < sum[a]){
            max = sum[a];
            x_coordinate = coordinates[a][0] + 1;
            y_coordinate = coordinates[a][1] + 1;
        }else if(max == sum[a]){
            max = sum[a];
            if (x_coordinate> coordinates[a][0] + 1){
                x_coordinate = coordinates[a][0] + 1;
            }
            else if (x_coordinate == coordinates[a][0] + 1) {
                if (y_coordinate > coordinates[a][1] + 1) {
                    y_coordinate = coordinates[a][1] + 1;
                }
            }
        }
    }

    printf("\nBest slot found in: %d %d\n", x_coordinate, y_coordinate);




    return 0;

}

