/**************************************************************************
 * Assessment Title: Assessed Coursework Exercise #3
 *
 * Number of Submitted C Files: 1
 *
 * Date: 07/11/2016
 *
 *
 * Author: Filip Lejhanec, Reg no: 201537504
 *
 *
 * Personal Statement: I confirm that this submission is all my own work.
 *
 *          (Signed)_______________________(Filip Lejhanec)
 *
 *
 *
 **************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Declaring functions */

/* Creates a default memory for our program in a 32x9 character array passed into it by a pointer */
/* The content of each row is a string of eight binary numbers terminated with a null character */
void load_default_memory(char memory[32][9]);

/* Converts a given decimal number into binary and stores it as a string into a given array */
/* The resulting number is 8 bits long and can only be stored in an array 9 characters long */
void decimal_to_binary(int dec, char bin[9]);

/* Converts a SIGNED binary number stored as a string of 1s and 0s into a decimal number and returns it */
/* The source number can be of any length, provided its decimal value can be held as an integer variable */
int binary_to_decimal(char bin[]);

/* Converts an UNSIGNED binary number stored as a string of 1s and 0s into a decimal number and returns it */
/* The source number can be of any length, provided its decimal value can be held as an integer variable */
int binary_to_decimal_unsigned(char bin[]);

/* Displays the memory's contents with its respective locations on separate lines*/
void display_memory(char memory[32][9]);

/* Converts the memory's contents into an assembly language and displays the human readable code on the screen */
void convert_to_assembly(char memory[32][9]);

/* Prompts the user to input the memory contents from the console (i.e. command line), reads the input in and stores it into the memory */
/* The user inputs strings of eight binary numbers on the numbered lines */
/* User can decide to input "stop" instead of the binary string to fill in the rest of the memory with 0s */
void read_from_console(char memory[32][9]);

/* Runs the program stored in memory and prints the memory contents after coming to halt*/
void run(char memory[32][9]);

/* Loads the instructions from a file and stores its contents into the memory */
/* The format of the file should be so that the 8-bit memory blocks are separated by strictly one arbitrary character */
void load_from_file(char memory[32][9], char filename[]);

/* Main function that accepts strictly one of these arguments:
 * '-d' to load a default program into the memory, display its contents, run it and display its contents again after coming to halt
 * '-c' to let the user input the memory himself, display its contents, run it and display its contents again after coming to halt
 * '-f' to load the program into memory from a file "memory.txt", display its contents, run it and display its contents again after coming to halt
 * If no, or wrong argument is detected the program will terminate after outputting an error message */
int main(int argc, char **argv){
	char memory[32][9];
	int error = 0;
	if (argc == 2){
		if (argv[1][0]=='-' && argv[1][2]=='\0'){ /* check that the argument is in the correct format and use the letter as the switch argument */
			switch(argv[1][1]){
				case 'd':
					load_default_memory(memory);
					display_memory(memory);
					run(memory);
					break;
				case 'c':
					read_from_console(memory);
					display_memory(memory);
					run(memory);
					break;
				case 'f':
					load_from_file(memory,"memory.txt");
					display_memory(memory);
					run(memory);
					break;
				default:
					error = 3; /* Wrong letter in the first argument */
					break;
			}
		} else error = 2; /* Wrong format of the first argument */
	} else error = 1; /* Wrong number of arguments */
	if(error){
		printf(	"Error: %d\n" /* Error message if any problems are encountered */
				"Program expects one argument:\n"
				"-d: load default memory\n"
				"-c: read from console\n"
				"-f: load from file\n"
				"The program will now terminate...\n"
				, error);
	}
	return error; /* Returns an error value for possible debugging */
}

void load_default_memory(char memory[32][9]){
	strcpy(memory[0], "01000101"); /* Strings are simply copied one by one into the array */
	strcpy(memory[1], "01111110");
	strcpy(memory[2], "01001101");
	strcpy(memory[3], "10011110");
	strcpy(memory[4], "01111111");
	strcpy(memory[5], "00000000");
	strcpy(memory[6], "00000000");
	strcpy(memory[7], "00000000");
	strcpy(memory[8], "00000000");
	strcpy(memory[9], "00000000");
	strcpy(memory[10],"00000000");
	strcpy(memory[11],"00000000");
	strcpy(memory[12],"00000000");
	strcpy(memory[13],"00000000");
	strcpy(memory[14],"00000000");
	strcpy(memory[15],"00000000");
	strcpy(memory[16],"00000000");
	strcpy(memory[17],"00000000");
	strcpy(memory[18],"00000000");
	strcpy(memory[19],"00000000");
	strcpy(memory[20],"00000000");
	strcpy(memory[21],"00000000");
	strcpy(memory[22],"00000000");
	strcpy(memory[23],"00000000");
	strcpy(memory[24],"00000000");
	strcpy(memory[25],"00000000");
	strcpy(memory[26],"00000000");
	strcpy(memory[27],"00000000");
	strcpy(memory[28],"00000000");
	strcpy(memory[29],"00000000");
	strcpy(memory[30],"00000101");
	strcpy(memory[31],"00000000");
	printf("Default memory has been successfully loaded\n");
}

void decimal_to_binary(int dec, char bin[9]){
	dec = (dec+256)%256; /* converts the signed decimal into its unsigned representation which is the same as if we were to convert the signed decimal to signed binary and then read the binary as if it were unsigned */
	int i; /* Now we just convert an unsigned decimal to unsigned binary */
	int j=128; /* declaring 'j' to the value of the most significant bit */
	for (i=0;i<8;i++){ /* One loop for each resulting binary number */
		if(dec/j){ /* Every time we are able to divide our number by 'j' then make the current bit '1' else make it '0' */
			bin[i] = '1';
			dec -= j;
		} else bin[i] = '0';
		j/=2; /* Dont forget to divide 'j' by '2' every time going through the loop */
	}
	bin[8] = '\0'; /* string-terminating character */
}

int binary_to_decimal(char bin[]){
	int length = 0;
	int dec = 0;
	int j = -1;
	while (bin[length] != '\0') length++; /* Find out how long is the string passed on to us */
	int i;
	for (i=0;i<(length-1);i++) j *= 2; /* set 'j' to the value of the most significant bit */
	dec += (bin[0]-'0')*j; /* multiply the binary values by 'j' one by one and add it to the result */
	j /= -2; /* Divide 'j' by '2' in each loop (First loop accounts for the negative value of the most significant bit) */
	for (i=1;i<length;i++){ /* The rest of the loops have 'j' as a positive number */
		dec += (bin[i]-'0')*j;
		j /= 2;
	}
	return dec; /* result in binary */
}

int binary_to_decimal_unsigned(char bin[9]){
	int length = 0;
	int dec = 0;
	int j = 1;
	while (bin[length] != '\0') length++; /* Find out how long is the string passed on to us */
	int i;
	for (i=0;i<(length-1);i++) j *= 2; /* set 'j' to the value of the most significant bit */
	for (i=0;i<length;i++){ /* multiply the binary values by 'j' one by one and add it to the result */
		dec += (bin[i]-'0')*j; /* Divide 'j' by '2' in each loop */
		j /= 2;
	}
	return dec; /* result in binary */
}

void display_memory(char memory[32][9]){
	printf("Contents of memory blocks: \n");
	int i;
	int j;
	for(i=0;i<32;i++){ /* Loop through all 32 rows and print its contents (including the null terminating character for error checking) */
		printf("%2d: ",i);
		for (j=0;j<9;j++){
			printf("%c",memory[i][j]);
		}
		printf("\n");
	}
}

void convert_to_assembly(char memory[32][9]){
	int i;
	printf("The assembly code representing the data stored in memory: \n");
	for(i=0;i<32;i++){ /* Loop through all 32 rows */
		printf("%2d", i);
		switch(((memory[i][0]-'0')*4)+((memory[i][1]-'0')*2)+(memory[i][2]-'0')){ /* Get the decimal representation of the first three bits in each row and use it as a switch argument to print the appropriate command and value */
			case 0:
				printf("HLT\n");
				break;
			case 1:
				printf("LOD %d\n", binary_to_decimal_unsigned(&memory[i][3])); /* Passes  only the last 5 bits for the conversion, careful about signed and unsigned values */
				break;
			case 2:
				printf("LDC %d\n", binary_to_decimal(&memory[i][3]));
				break;
			case 3:
				printf("STO %d\n", binary_to_decimal_unsigned(&memory[i][3]));
				break;
			case 4:
				printf("ADD %d\n", binary_to_decimal_unsigned(&memory[i][3]));
				break;
			case 5:
				printf("SUB %d\n", binary_to_decimal_unsigned(&memory[i][3]));
				break;
			case 6:
				printf("JMP %d\n", binary_to_decimal_unsigned(&memory[i][3]));
				break;
			case 7:
				printf("JMZ %d\n", binary_to_decimal_unsigned(&memory[i][3]));
				break;
			default:
				break;
		}
	}
}

void read_from_console(char memory[32][9]){
	printf(	"Enter the contents of each memory block on the appropriate line\n"
			"To auto-fill the rest of the memory blocks with 0s type \"stop\"\n");
	char input[9] = ""; /* our one-line-of-input-temporary-variable to get data from the user */
	int i = 0;
	while (i < 32){ /* 32 loops */
		printf("%2d: ", i);
		if(!strcmp(fgets(input,9,stdin),"stop\n")) break; /* If we get "stop" at the line input we break */
		strcpy(memory[i], input); /* copy the input to memory */
		fgets(input,9,stdin); /* Read all the unwanted data in the stdin buffer (mostly new line) */
		i++;
	}
	while (i<32){
		strcpy(memory[i],"00000000"); /* Fills the rest of available memory with 0s */
		i++;
	}
	printf("Successfully finished storing all the memory data\n");
}

void run (char memory[32][9]){
	char ac[9] = "00000000"; /* initialize all the registers (trying preserve authentic binary registers) */
	char pc[9] = "00000000";
	char ir[9] = "00000000";
	printf("Attempting to execute a program stored in memory\n");
	while(1){ /* infinite loop */
		strcpy(ir,memory[binary_to_decimal_unsigned(pc)]); /* Copy the data pointed at by 'pc' into 'ir' */
		decimal_to_binary(binary_to_decimal_unsigned(pc)+1, pc); /* increment 'pc' by 1 (needs to be converted to decimal to do this and then back to binary) */
		switch(((ir[0]-'0')*4)+((ir[1]-'0')*2)+(ir[2]-'0')){ /* get the decimal representation fo the first 3 binary numbers in 'ir' and use that as a switch variable */
			case 0:
				goto exit; /* Halt execution of the program */
				break;
			case 1:
				decimal_to_binary(binary_to_decimal(memory[binary_to_decimal_unsigned(&ir[3])]), ac); /* Load a copy of the value in the referenced memory location in the accumulator */
				break;
			case 2:
				decimal_to_binary(binary_to_decimal(&ir[3]), ac); /* Load the constant value of the operand in the accumulator - Note: limited to 5 bits (-16 to +15) */
				break;
			case 3:
				strcpy(memory[binary_to_decimal_unsigned(&ir[3])], ac); /* Store a copy of the contents of the accumulator in the referenced memory location - Note: the value in the accumulator does not change */
				break;
			case 4:
				decimal_to_binary(binary_to_decimal(ac) + binary_to_decimal(memory[binary_to_decimal_unsigned(&ir[3])]), ac); /* Add the value in the referenced memory location to the value in the accumulator; store result in the accumulator */
				break;
			case 5:
				decimal_to_binary(binary_to_decimal(ac) - binary_to_decimal(memory[binary_to_decimal_unsigned(&ir[3])]), ac); /* Subtract the value in the referenced memory location from the value in the accumulator; store result in the accumulator */
				break;
			case 6:
				if (binary_to_decimal(ac) >= 0){
					decimal_to_binary(binary_to_decimal_unsigned(&ir[3]), pc); /* Jump to the referenced memory location if the value of the accumulator is a positive number (equal or greater than 0) */
				}
				break;
			case 7:
				if (binary_to_decimal(ac) == 0){
					decimal_to_binary(binary_to_decimal_unsigned(&ir[3]), pc); /* Jump to the referenced memory location if the value of the accumulator is 0 */
				}
				break;
			default:
				break;
		}
	}
	exit:
	printf("Program halted with the following content in it's registers:\n" /* Display the content of registers and memory */
			"ac: %s = %d\n"
			"pc: %s = %d\n"
			"ir: %s\n"
			, ac, binary_to_decimal(ac), pc, binary_to_decimal_unsigned(pc), ir);
	display_memory(memory);
}

void load_from_file(char memory[32][9], char filename[]){
	FILE *file; /* new FILE pointer */
	file = fopen(filename, "r"); /* asign the file of our chosen 'filename' to the pointer for reading only */
	printf("Successfully opened file %s\n", filename);
	int i = 0;
	int j = 0;
	char c;
	for (i=0;i < 32;i++){ /* Go through all 32 memory blocks*/
		for (j=0;j < 8;j++){
			c = fgetc(file); /* Get 9 characters one by one, check them for EOF, store 8 of them in memory and discard the last one */
			if (c==EOF) {
				printf("Error - Encountered end of file too early\n");
				goto exit;
			}
			memory[i][j] = c;
		}
		c = fgetc(file);
		memory[i][8] = '\0';
		if (c==EOF) {
				printf("Error - Encountered end of file too early\n");
				goto exit;
			}
	}
	exit: /* Label for jumping out of the reading loop when EOF is detected */
	printf("Finished reading all the memory data\n");
	fclose(file);
}
