#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structs.h"
#include "readPpm.h"

void writePpm(const char *file, ppmImage *img)
{
    FILE *fp;
    // open the ppm file
    fp = fopen(file, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", file);
         exit(1);
    }

    // write the file header
    // image format
    fprintf(fp, "P6\n");

    // write comments
    fprintf(fp, "# Created by %s\n",CREATOR);

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}


void embedMsg(ppmImage *img, char* bin)
{
	int i = 0;
	int j =0;
    if(img){
		// loop through the message in binary form and adjust the bits of the image's pixels accordingly
		for (j = 0; j<strlen(bin); ++j) {
			i = j/3;
			switch(j%3) {
				case 0: 
					img->data[i].red = (bin[j] == '1') ? (img->data[i].red | (1 << 0)) : (img->data[i].red & ~(1 << 0));
					/*printf("%c and idx %d modulo %d and color val: %d\n", 'r', j, j%3, img->data[i].red);*/
					break;
				case 1: 
					img->data[i].green = (bin[j] == '1') ? (img->data[i].green | (1 << 0)) : (img->data[i].green & ~(1 << 0));
					/*printf("%c and idx %d modulo %d n color val: %d\n", 'g', j, j%3, img->data[i].green);*/
					break;
				case 2: 
					img->data[i].blue = (bin[j] == '1') ? (img->data[i].blue | (1 << 0)) : (img->data[i].blue & ~(1 << 0));
					/*printf("%c and idx %d modulo %d and color val: %d\n", 'r', j, j%3, img->data[i].blue);*/
					break;
			}
		}
		// pad the rest of the pixels with 0's
		if (j%3 == 1) {
			img->data[i].green = img->data[i].green & ~(1 << 0);
			j++;
		}
		if (j%3 == 2) {
			img->data[i].blue = img->data[i].blue & ~(1 << 0);
		}
        i++;
		for(i;i<img->x*img->y;i++){
            img->data[i].red = img->data[i].red & ~(1 << 0);
			img->data[i].green = img->data[i].green & ~(1 << 0);
			img->data[i].blue = img->data[i].blue & ~(1 << 0);
		}
    }
}


char* stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); 
    binary[0] = '\0';
	// convert strings to its binary representation
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
		if (s[i] == '\n') {
			continue;		
		}
		/*printf("%c\n", s[i]);*/
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
	// concatenate the null terminator at the end
	strcat(binary, "00000000");
    return binary;
}


int main(int argc, char * argv[]){
	// exits the program if the number of parameters taken in command line is incorrect
	if (argc != 3) {			
		fprintf(stderr, "Invalid number of arguments, expected 3 arguments. Received %d instead.\n", argc);	
		exit(1);	
	}

	// read the image file
    ppmImage *image;
    image = readPpm(argv[1]);

	// get maximum hidden message length
	int maxMsgLength = image->x * image->y;
	maxMsgLength = (maxMsgLength *3 /8) - 1;

	printf("Maximum size of message is %d characters.\n", maxMsgLength);
	
	// get hidden message from stdin
	char hiddenMsg[maxMsgLength];
	printf("Enter your hidden message: ");
	fgets(hiddenMsg, maxMsgLength, stdin);

	/*printf("%lu\n", strlen(hiddenMsg) - 1);*/
	
	// check if the message is too long
	if (strlen(hiddenMsg) -1 > maxMsgLength) {
		fprintf(stderr, "Message is too long, please input a message no longer than %d characters.\n", maxMsgLength);
		exit(1);
	}

	// get binary representation for the hidden message
	char binaryStr[maxMsgLength * 8];
	strcpy(binaryStr, stringToBinary(hiddenMsg));
	// printf("%s\n",binaryStr);

	// embed the hidden message
    embedMsg(image, binaryStr);
    printf("Message embedding complete.\n");

	// create the new image file
    writePpm(argv[2],image);
    printf("File created, press enter to continue...");
    getchar();
	return 0;
}
