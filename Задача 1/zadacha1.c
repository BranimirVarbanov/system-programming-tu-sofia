#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE 100

uint16_t integers = 0;
uint16_t real_numbers = 0;
uint16_t unsigned_numbers = 0;
uint16_t octal_numbers = 0;
uint16_t hex_numbers = 0;
uint16_t float_numbers = 0;
uint16_t state_number = 1;

uint16_t long_numbers = 0;
uint16_t long_long_numbers = 0;
uint16_t long_double_numbers = 0;

void FSM_Integers(char word[MAX_BUFFER_SIZE], int word_size){
    uint8_t index = 0;
    while(state_number != 35 && index != word_size + 2){ //35 -> ERROR STATE
        switch(state_number){

        case 1:
            //printf("Currents state is 1\n");
            if(word[index] >= '1' && word[index] <= '9'){
                state_number = 2;
                index+=1;
                break;
            }
            else if(word[index] == '+'){
                state_number = 3;
                index+=1;
                break;
            }
            else if(word[index] == '0'){
                state_number = 8;
                index+=1;
                break;
            }
            else if(word[index] == '-'){
                state_number = 4;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 2:
            //printf("Currents state is 2\n");
            if(index == word_size + 1 && (word[index-1] >= '0' && word[index-1] <= '9')){
                integers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '9'){
                state_number = 2;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 5;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 6;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 3:
            //printf("Currents state is 3\n");
            if(word[index] >= '1' && word[index] <= '9'){
                state_number = 2;
                index+=1;
                break;
            }
            else if(word[index] == '0'){
                state_number = 7;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 4:
            //printf("Currents state is 4\n");
            if(word[index] == '0'){
                state_number = 9;
                index+=1;
                break;
            }
            else if(word[index] >= '1' && word[index] <= '9'){
                state_number = 10;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 5:
           // printf("Currents state is 5\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                integers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 11;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }


        case 6:
            //printf("Currents state is 6\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 12;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 13;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 7:
            //printf("Currents state is 7\n");
            if(index == word_size + 1 && word[index-1] == '0'){
                integers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 6;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 5;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 8:
            //printf("Currents state is 8\n");
            if(index == word_size + 1 && word[index-1] == '0'){
                integers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] =='L'){
                state_number = 6;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 5;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '7'){
                state_number = 14;
                index+=1;
                break;
            }
            else if(word[index] == 'x' || word[index] == 'X'){
                state_number = 15;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 9:
           // printf("Currents state is 9\n");
            if(index == word_size + 1 && word[index-1] == '0'){
                integers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 16;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 10:
            //printf("Currents state is 10\n");
            if(index == word_size + 1 && (word[index-1] >= '0' && word[index-1] <= '9')){
                integers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '9'){
                state_number = 10;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 16;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 11:
            //printf("Currents state is 11\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                unsigned_numbers++;
                long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] =='L'){
                state_number = 17;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 12:
            //printf("Currents state is 12\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 18;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 13:
           // printf("Currents state is 13\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                integers++;
                long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 14:
            //printf("Currents state is 14\n");
            if(index == word_size + 1 && (word[index-1] >= '0' && word[index-1] <= '7')){
                integers++;
                octal_numbers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '7'){
                state_number = 14;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 20;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 19;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 15:
            //printf("Currents state is 15\n");
            if((word[index] >= '0' && word[index] <= '9') || (word[index] >= 'a' && word[index] <= 'f') || (word[index] >= 'A' && word[index] <= 'F')){
                state_number = 21;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 16:
           // printf("Currents state is 16\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 22;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 17:
            //printf("Currents state is 17\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                unsigned_numbers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 18:
            //printf("Currents state is 18\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                integers++;
                unsigned_numbers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 19:
            //printf("Currents state is 19\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                octal_numbers++;
                integers++;
                long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 23;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 24;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 20:
            //printf("Currents state is 20\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                octal_numbers++;
                integers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 25;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 21:
            //printf("Currents state is 21\n");
            if(index == word_size + 1 && ((word[index-1] >= '0' && word[index-1] <= '9') || (word[index-1] >= 'a' && word[index-1] <= 'f') || (word[index-1] >= 'A' && word[index-1] <= 'F'))){
                hex_numbers++;
                integers++;
                index+=1;
                break;
            }
            else if((word[index] >= '0' && word[index] <= '9') || (word[index] >= 'a' && word[index] <= 'f') || (word[index] >= 'A' && word[index] <= 'F')){
                state_number = 21;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 27;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 26;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 22:
            //printf("Currents state is 22\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                integers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 23:
            //printf("Currents state is 23\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                octal_numbers++;
                integers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 28;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 24:
            //printf("Currents state is 24\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                octal_numbers++;
                integers++;
                long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 25:
            //printf("Currents state is 25\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                octal_numbers++;
                integers++;
                long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 32;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 26:
           // printf("Currents state is 26\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                hex_numbers++;
                integers++;
                long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 29;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 30;
                index+=1;
                break;
            }
           else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 27:
            //printf("Currents state is 27\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                hex_numbers++;
                integers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 31;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 28:
            //printf("Currents state is 28\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                octal_numbers++;
                integers++;
                long_long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 29:
            //printf("Currents state is 29\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                hex_numbers++;
                integers++;
                long_long_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'u' || word[index] == 'U'){
                state_number = 33;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 30:
            //printf("Currents state is 30\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                hex_numbers++;
                integers++;
                long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 31:
            //printf("Currents state is 31\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                hex_numbers++;
                integers++;
                long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 34;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 32:
            //printf("Currents state is 32\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                octal_numbers++;
                integers++;
                long_long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 33:
            //printf("Currents state is 33\n");
            if(index == word_size + 1 && (word[index-1] == 'u' || word[index-1] == 'U')){
                hex_numbers++;
                integers++;
                long_long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }

        case 34:
            //printf("Currents state is 34\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                hex_numbers++;
                integers++;
                long_long_numbers++;
                unsigned_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 35;
                break;
            }
        }
    }
    /*if(index == word_size + 2){
        printf("CORRECT ONE IS: ");
        for(int i=0; i<=word_size; i++)
            printf("%c",word[i]);
        printf("\n");
    }*/
}
//THAT WORD IS WRONG: +1LU
//THAT WORD IS WRONG: 1LU
//trqbva da opravq avtomata za realnite chisla -> 1. i -1. sa validni
//imam greshka pri +0e5, +10.10e-534 i podobni
void FSM_RealNumbers(char word[MAX_BUFFER_SIZE], int word_size){
    uint8_t index = 0;
    while(state_number != 20 && index != word_size + 2){
        switch(state_number){

        case 1:
            //printf("Currents state is 1\n");
            if(word[index] == '.'){
                state_number = 2;
                index+=1;
                break;
            }
            else if(word[index] == '+' || word[index] == '-'){
                state_number = 3;
                index+=1;
                break;
            }
            else if (word[index] >= '1' && word[index] <= '9'){
                state_number = 4;
                index+=1;
                break;
            }
            else if(word[index] == '0'){
                state_number = 5;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 2:
            //printf("Currents state is 2\n");
            if(word[index] >= '0' && word[index] <= '9'){
                state_number = 6;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 3:
            //printf("Currents state is 3\n");
            if(word[index] == '.'){
                state_number = 2;
                index+=1;
                break;
            }
            else if(word[index] == '0'){
                state_number = 5;
                index+=1;
                break;
            }
            else if(word[index] >= '1' && word[index] <= '9'){
                state_number = 4;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 4:
            //printf("Currents state is 4\n");
            if(word[index] >= '0' && word[index] <= '9'){
                state_number = 4;
                index+=1;
                break;
            }
            else if(word[index] == '.'){
                state_number = 9;
                index+=1;
                break;
            }
            else if(word[index] == 'e' || word[index] == 'E'){
                state_number = 12;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 5:
            //printf("Currents state is 5\n");
            if(word[index] == '.'){
                state_number = 9;
                index+=1;
                break;
            }
            else if(word[index] == 'e' || word[index] == 'E'){
                state_number = 12;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 6:
            //printf("Currents state is 6\n");
            if(index == word_size + 1 && (word[index-1] >= '0' && word[index-1] <= '9')){
                real_numbers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '9'){
                state_number = 6;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 7;
                index+=1;
                break;
            }
            else if(word[index] == 'f' || word[index] == 'F'){
                state_number = 8;
                index+=1;
                break;
            }
            else if(word[index] == 'e' || word[index] == 'E'){
                state_number = 12;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 7:
            //printf("Currents state is 7\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                real_numbers++;
                long_double_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 8:
            //printf("Currents state is 8\n");
            if(index == word_size + 1 && (word[index-1] == 'f' || word[index-1] == 'F')){
                real_numbers++;
                float_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }
        case 9:
            //printf("Currents state is 9\n");
            if(index == word_size + 1 && (word[index-1] == '.')){
                real_numbers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '9'){
                state_number = 6;
                index+=1;
                break;
            }
            else if(word[index] == 'e' || word[index] == 'E'){
                state_number = 12;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 10;
                index+=1;
                break;
            }
            else if(word[index] == 'f' || word[index] == 'F'){
                state_number = 11;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 10:
            //printf("Currents state is 10\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                real_numbers++;
                long_double_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 11:
            //printf("Currents state is 11\n");
            if(index == word_size + 1 && (word[index-1] == 'f' || word[index-1] == 'F')){
                real_numbers++;
                float_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 12:
            //printf("Currents state is 12\n");
            if(word[index] >= '1' && word[index] <= '9'){
                state_number = 16;
                index+=1;
                break;
            }
            else if(word[index] == '0'){
                state_number = 13;
                index+=1;
                break;
            }
            else if(word[index] == '+' || word[index] == '-'){
                state_number = 17;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 13:
            //printf("Currents state is 13\n");
            if(index == word_size + 1 && (word[index-1] == '0')){
                real_numbers++;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 14;
                index+=1;
                break;
            }
            else if(word[index] == 'f' || word[index] == 'F'){
                state_number = 15;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 14:
            //printf("Currents state is 14\n");
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                real_numbers++;
                long_double_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 15:
            //printf("Currents state is 15\n");
            if(index == word_size + 1 && (word[index-1] == 'f' || word[index-1] == 'F')){
                real_numbers++;
                float_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 16:
            //printf("Currents state is 16\n");
            if(index == word_size + 1 && (word[index-1] >= '0' && word[index-1] <= '9')){
                real_numbers++;
                long_double_numbers++;
                index+=1;
                break;
            }
            else if(word[index] >= '0' && word[index] <= '9'){
                state_number = 16;
                index+=1;
                break;
            }
            else if(word[index] == 'l' || word[index] == 'L'){
                state_number = 18;
                index+=1;
                break;
            }
            else if(word[index] == 'f' || word[index] == 'F'){
                state_number = 19;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 17:
            if(word[index] == '0'){
                state_number = 13;
                index+=1;
                break;
            }
            else if(word[index] >= '1' && word[index] <= '9'){
                state_number = 16;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 18:
            if(index == word_size + 1 && (word[index-1] == 'l' || word[index-1] == 'L')){
                real_numbers++;
                long_double_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }

        case 19:
            if(index == word_size + 1 && (word[index-1] == 'f' || word[index-1] == 'F')){
                real_numbers++;
                float_numbers++;
                index+=1;
                break;
            }
            else{
                /*printf("THAT WORD IS WRONG: ");
                for(int i=0; i<=word_size; i++)
                    printf("%c",word[i]);
                printf("\n");*/
                state_number = 20;
                break;
            }
        }
        /*if(index == word_size + 2){
            printf("CORRECT ONE IS: ");
            for(int i=0; i<=word_size; i++)
                printf("%c",word[i]);
            printf("\n");
        }*/
    }
}



int main()
{
FILE* file_pointer;
file_pointer = fopen("test2_FSM.txt", "r");
if(file_pointer == NULL){
    //printf("The text file can't be opened!\n");
    exit(1);
}
//else printf("The text file is opened successfully!\n");

char ch;
char buffer[MAX_BUFFER_SIZE];
uint8_t buffer_index = 0;
int buffer_filled = 0;
uint8_t isReal = 0;

while((ch = fgetc(file_pointer)) != EOF){
    if(ch != ' ' && ch != '\n' && ch != '\t' && ch != ','){
        buffer[buffer_index] = ch;
        buffer_index++;
    }
    else{
        if(buffer_index > 0) buffer_filled = 1;
        if(buffer_filled){

            //printf("\nThere is word: ");
            for(int i=0; i<buffer_index; i++){
                //printf("%c",buffer[i]);
                if(buffer[i] == '.' || buffer[i] == 'e' || buffer[i] == 'E')
                    isReal = 1;
            }
            /*printf("\n");
            printf("BUFFER SIZE: %d\n",buffer_index);*/
            if(isReal){
                //printf("THE WORD IS CONSIDERED REAL!\n\n");
                FSM_RealNumbers(buffer,buffer_index-1);
            }
            else{
                //printf("THE WORD IS CONSIDERED INTEGER!\n");
                FSM_Integers(buffer,buffer_index-1);
            }
            state_number = 1;
            buffer_index = 0;
            buffer_filled = 0;
            isReal = 0;
        }
    }
}

if((ch = fgetc(file_pointer) == EOF)){
    if(buffer_index > 0)
    for(int i=0; i<=buffer_index; i++)
        printf("%c",buffer[i]);
}
//0x1234567890ABCDEF
//debugging
printf("\n");
/*char word[MAX_BUFFER_SIZE] = {'0','x','1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F'};
FSM_Integers(word,17);
printf("\n");*/
/*printf("EVALUATING THE WORD: ");
for(int i=0; i<=17; i++)
    printf("%c",word[i]);*/
printf("\n");
//printf("\n");
printf("OCTAL: %d\n",octal_numbers);
printf("HEX: %d\n",hex_numbers);
printf("UNSIGNED: %d\n",unsigned_numbers);
printf("INTEGERS: %d\n\n",integers);
printf("FLOAT: %d\n",float_numbers);
printf("REAL: %d\n\n",real_numbers);
printf("ALL NUMBERS: %d\n",real_numbers+integers);
/*printf("\n");
printf("LONG: %d\n",long_numbers);
printf("LONG LONG: %d\n",long_long_numbers);*/


fclose(file_pointer);
return 0;
}
