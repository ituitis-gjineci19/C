#include <stdio.h>
#include <stdbool.h>

//Dart game
//Game starts/ends by scoring a double
//Game will get the starting points(target) and after hitting the double reduce the target
//User should also input the throws(number+letter(representing the area))


//1.Write a function that takes the segment and ring of a throw as parameters and returns the point value for the throw
/*2. Write a function that takes the current points, and the segment and ring for a throw as parameters and
returns the remaining points after that throw according to the rules described above.
This should cover the starting and ending of the game.*/
/*3. Using these functions, write a main function that interacts with the user and prints out the score
after every throw until the game is ended*/

int target, reduced_target;                 // keeping track of the initial target and reduced one throughout the game

int points_value(int segment, char ring){

	switch(ring) {
        case 'S':                       //single
            return segment;
        case 'D':                       //double
            return 2 * segment;
        case 'T':                       //triple
            return 3 * segment;
        case 'O':                       //outer bull
            return 25;
        case 'I':                       //inner bull
            return 50;
        case 's':                       //single
            return segment;
        case 'd':                       //double
            return 2 * segment;
        case 't':                       //triple
            return 3 * segment;
        case 'o':                       //outer bull
            return 25;
        case 'i':                       //inner bull
            return 50;
        default:
            printf("\nThis letter does not belong to any area in the dart board\n");
            return 0;
	}
}

int remaining_points(int subtrahend, int segment, char ring){

    if(reduced_target == target && ring != 'D' && ring != 'd'){                     //starting the game
        printf("\nGame begins only in the double ring\n");
        return reduced_target;
    }
    else if(reduced_target == target && ((ring == 'D') || (ring == 'd'))){          //first double throw
        return reduced_target - subtrahend;
    }
    else if(reduced_target != target)                                               //after first double throw
    {
        if((reduced_target - subtrahend < 0) || (reduced_target - subtrahend == 1)){        //criteria for ending the game
            return reduced_target;
        }
        else if(reduced_target - subtrahend == 0){
            if(ring == 'D' || ring == 'd')
                return 0;
            else
                printf("A double is needed to end the game\n");
                return reduced_target;
        }
        else{
            return reduced_target - subtrahend;                         //otherwise return the reduced result
        }
    }

}

int main(){

	printf("Target(enter the initial points): ");
	scanf("%d", &target);


    int segment;
    char ring;
    reduced_target = target;
	while(reduced_target != 0){

		printf("\nThrow: ");
		scanf("%d %c", &segment, &ring);

		reduced_target = remaining_points(points_value(segment,ring), segment, ring);

		printf("Points: %d", reduced_target);

	}
	return 0;
}



