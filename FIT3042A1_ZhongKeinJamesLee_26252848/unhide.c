#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structs.h"
#include "readPpm.h"
#include <math.h>

#define DIGIT 8

// appends chars to a string
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

// retrieves the binary form of the hidden msg from an image
char* retrieveMsg(ppmImage *img){
    if (img) {
        size_t size = img->x * img->y;
        char *msg = malloc(size*8 + 1);
        for (int i = 0; i < size; i++){
            // bit = (number >> x) & 1;
            // char bit = (img->data[i].red >> 0) & 1;
            // printf("%d\n", (img->data[i].red >> 0) & 1);
            if ((img->data[i].red >> 0) & 1) {
                strcat(msg, "1");
            }
            else {
                strcat(msg, "0");
            }
            if ((img->data[i].green >> 0) & 1) {
                strcat(msg, "1");
            }
            else {
                strcat(msg, "0");
            }
            if ((img->data[i].blue >> 0) & 1) {
                strcat(msg, "1");
            }
            else {
                strcat(msg, "0");
            }
            
        }
        // printf("%lu\n", strlen(msg));
        return msg;
    }
}

// converts the binary message into ascii characters
char* decodeMsg(char* msg) {
    int i =0;
    int count = 0;
    int stop = 0;
    size_t len = strlen(msg);
    char *sentence = malloc(len*8 + 1);
    /* remove padded 0s */
    for (i = 0;i < len;i++) {
        if (msg[i] == '0') {
            count++;
            if (count == 8) {
                stop =i;
                break;
            }
            else{
                continue;
            }
        }
        else {
            count = 0;
        }
    }
    count =0;
    int letter =0;
    for (i = 0; i<= stop; i++){
        // printf("char is %c\n", msg[i]);
        if (count == 8){
            // letter = letter;
            // printf("letter to append is %d\n", letter);
            append(sentence, letter);
            // printf("%s\n", sentence);
            count =0;
            letter = 0;
        }
        // printf("%d\n", msg[i]);
        if (msg[i] == 49) {
            letter += pow(2,(8-i%DIGIT-1));
            // printf("letter score is: %d\n",letter);
        }
        count++;
    }
    return sentence;
}


int main(int argc, char * argv[]){
	// exits the program if the number of parameters taken in command line is incorrect
	if (argc != 2) {			
		fprintf(stderr, "Invalid number of arguments, expected 3 arguments. Received %d instead.\n", argc);	
		exit(1);	
	}
    // read the image file
    ppmImage *image;
    image = readPpm(argv[1]);

    // retrieve the message and decode it
    char* x = decodeMsg(retrieveMsg(image));

    // print the message to stdout
    printf("The secret message is: %s\n", x);
    printf("Press any key to continue...\n");
    getchar();
    return 0;

}