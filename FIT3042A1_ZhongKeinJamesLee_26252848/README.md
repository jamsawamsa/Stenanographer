# FIT3042 Assignment 1

Zhong Keing James Lee
Monash student ID: 26252848

A stenanographic message encryptor that hides messages in PPM file type images. Written in C.

### Getting Started

To get things started, go ahead and unzip compressed files into a folder of your liking. There should be 7 files included:
 - struct.h
 - readPpm.h
 - hide.c
 - unhide.c
 - README.md
 - Makefile.txt
 - box.ppm
 
 If you think you're lacking something you can go ahead and redownload the repository from [github](https://github.com/jamsawamsa/Stenanographer).
 
### Compiling the program
Compile both programs using makefile by running these 2 commands:
```sh
 $make hide
 $make unhide
```

### Running the Program
Great! You're now ready to run your program. To load the hide program simply enter:
```sh
 $./hide [original_ppm_file] [new_ppm_file]
```
Just in case you don't have one, I've included a small PPM file called *box.ppm* in the archive file for you. The program will create the new PPM file for you. Also make sure to include the "./" just before your command to run the program or it will not run.
Do note that the only 2 supported formats are P6 and P3 and the RGB color component must be 255. The program will only write PPM files in the P6 format. So if you'll be using your own images, be sure to either edit the magic number or use one that is P6 or P3 and has 8 bits allocated for a color.

After running the program, you'll be prompted to enter your hidden message. Any of the ASCII characters are allowed, even whitespaces. The only constraint is that the length of your message is limited to the number of pixels your chosen PPM file has.
Once you've entered your secret message, hit enter and your new image should be created. You can view the image in the directory you unpacked the archive folder in.

To decode a hidden message, you'll have to run the second program:
```sh
 $./unhide [ppm_filename]
 ```
Voila! The message hidden in the image should now be displayed.

Bear in mind that if the image does not have a hidden message encoded in it, the resulting message that will be displayed might appear to be gibberish

### Known bugs and limitations
There are no known bugs at the moment but as I've previouly mentioned there are a few limitations with the program:
 - The amount of characters you can include in your message being limited by the number of pixels your PPM image file (3 * no. of pixels / 8 to be exact)
 - The inability to read text based PPM files
 - The PPM files' header format must not be in a single line or the image file will fail to read
 - The inability of the program to determine if any message is actually embedded into the image

### Authors

 - Zhong Kein James Lee, zklee1@student.monash.edu, student ID 26252848

