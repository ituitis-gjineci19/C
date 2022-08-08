#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct instruction_s {
    int step;
    int index;
};

char* get_word(char* s, int n){
    char* word = strtok(s, " ");

    int i = 1;
    while(word != NULL){
        if(i == n){
            return word;
        }
        i += 1;
        word = strtok(NULL, " ");
    }

    return NULL;

}


void get_sentence(char lines[][200], struct instruction_s* instructions, int n_instructions, char* sentence){
    int k;
	int sum=-1;
	for(int i=0; i<n_instructions; i++){
        sum +=instructions[i].step;

        //Extract the requested word
        sentence = get_word(&lines[sum][1], instructions[i].index);

        //Removing punctuation
        for(int j=0; sentence[j]!='\0'; j++){
            if( !( ((sentence[j]>='a'|| 'A') && (sentence[j]<='z' || 'Z'))  ||  (sentence[j]=='\0') ) ){
                for(k=j; sentence[k]!='\0'; k++){
                    sentence[k]=sentence[k+1];
                }
                sentence[k]='\0';
            }
        }

        //Upper case to lower case
        for(int m=0; m<strlen(sentence); m++){
            if(sentence[m]>='A' && sentence[m]<='Z'){
                sentence[m]=sentence[m]+0x20;
            }else if (sentence[m] < 'a' || sentence[m] > 'z'){
                sentence[m] = '\0';
            }
        }
        printf("%s", sentence);
        if (i != n_instructions - 1){
            printf(" ");
        }
	}

}


int main(int argc, char** argv){

    FILE* book;
    FILE* instructions;
    char ch;

    //book = fopen(argv[1], "r");
    //instructions = fopen(argv[2], "r");

    book = fopen("alice.txt", "r");
    instructions = fopen("instructions.txt", "r");

    //alice operations
    if (book == NULL || instructions == NULL) {
        printf("One of the files can't be opened \n");
        return (-1);
    }

    char book_array[10000][200];
    int i = 0;
    while(!feof(book)){
        fgets(book_array[i], 200, book);
        i++;
    }

    //instructions operations
    struct instruction_s instruct[50];
    int no1, no2;
    int j = 0;
    bool flag = true;
    while(flag && fscanf(instructions, "%d %d", &no1, &no2) == 2){
        (instruct+j)->step = no1;
        (instruct+j)->index = no2;
        if(feof(instructions)){
            flag = false;
        }else{
           j += 1;
        }
    }

//    for(int k = 0; k < j; k++){
//        printf("%d %d\n", instruct[k].step, instruct[k].index);
//    }

    char* sentence = malloc(sizeof(char)*300);
    get_sentence(book_array, instruct, j-1, sentence);

    free(sentence);
    fclose(book);
    fclose(instructions);
	

    return 0;
}
