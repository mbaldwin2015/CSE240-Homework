#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996) 

#define NUM_OF_CHUNKS 4
#define CHUNK_LENGTH 32

#define ENCRYPTION_SHIFT 5


// Given two strings, swaps their contents in memory.
void swap_strings(char* x, char* y)
{
	//create a temporary holding place for the data so we don't lose it.
	char temp[CHUNK_LENGTH];

	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

// [5 pts] Reset chunks Array
// TODO: Implement reset().  Iterate through the array to assign each element with a null terminator.
// Do not modify the function header, void reset(char *chunks); otherwise, it will fail the test cases.  
void reset(char chunks[NUM_OF_CHUNKS][CHUNK_LENGTH])
{
	for (int r = 0; r < NUM_OF_CHUNKS; r++) {
		for (int c = 0; c < CHUNK_LENGTH; c++) {
			chunks[r][c] = '\0';
		}
	}
} 

// [5 pts] Encrypt chunks Array
// TODO: Implment encrypt_chunks().  Loop over each string in the array and shift the characters in it
// by adding the ENCRYPTION_SHIFT value to each character.  Do NOT apply the shift to the first and last 
// characters in each row of the array. Do not modify the function header, 
// encrypt_chunks(char chunks[NUM_OF_CHUNKS][CHUNK_LENGTH]); otherwise, it will fail the test cases.   
void encrypt_chunks(char chunks[NUM_OF_CHUNKS][CHUNK_LENGTH])
{
	for (int r = 0; r < NUM_OF_CHUNKS; r++) {
		for (int c = 1; c < CHUNK_LENGTH; c++) {
			if (chunks[r][c] != '\0' && chunks[r][c+1] != '\0') chunks[r][c] = chunks[r][c] + ENCRYPTION_SHIFT;
		}
	}
}

// [10 pts] Decrypt chunks Array
// TODO: Implement decrypt chunks(). Using POINTERS, loop over the array and shift the characters in it
// by subtracting the ENCRYPTION_SHIFT value from each character.  Do NOT apply the shift to the first and
// last characters in each row of the array. Do not modify the function header, 
// encrypt_chunks(char chunks[NUM_OF_CHUNKS][CHUNK_LENGTH]); otherwise, it will fail the test cases.   
void decrypt_chunks(char *chunks)
{
	for (int i = 0; i < NUM_OF_CHUNKS*CHUNK_LENGTH; i++) {
		if (i != 0 && i % CHUNK_LENGTH != 0 && *chunks != '\0' && *(chunks+1) != '\0') *chunks = *chunks - ENCRYPTION_SHIFT;
		chunks++;
	}
}

// [10 pts] Displays the strings in chunks Array
// TODO: Implement display_chunks().  Loop over the array and print the string using POINTERS.  Do not 
// print the first character.  Do not modify the function header, void display_chunks(char *chunks); 
// otherwise, it will fail the test cases.
void display_chunks(char *chunks)
{
	for (int i = 0; i < NUM_OF_CHUNKS*CHUNK_LENGTH; i++) {
		if (i != 0 && i % CHUNK_LENGTH != 0 && *chunks != '\0') printf("%c", *chunks);
		chunks++;
	}
	printf("\n");
}

// [20 pts] Sorts the strings the global chunks variable by the first character.
// TODO: Implemente sort_chunks().  Using your favorite sorting algorithm (we suggest selection sort), sort
// the array containing the message chunks.  Sort based on the first character in the chunk - it will always 
// be a number.  You can only use POINTERs to refer the element in the array.  In this function, do NOT
// use NUM_OF_CHUNKS or CHUNK_LENGTH; instead use totalRows and totalColumn.  We provided a swap_strings 
// function that you may use.  Example usage: swap_strings(seg1, seg2) will swap the contents of the first 
// and second string.  Do not modify the function header, void sort_chunks(char *chunks); otherwise, it will fail 
// the test cases.  
void sort_chunks(int totalRows, int totalColumn, char *chunks)
{
	char *seg1 = chunks, *seg2 = chunks;

	for (int r = 0; r < (totalRows-1); r++) {
		for (int loc = r + 1; loc < totalRows; loc++) {
			seg2 = (chunks + (loc * totalColumn));
			if (strcmp(seg2, seg1) < 0) swap_strings(seg1, seg2);
		}
		seg1 = (chunks + ((r+1) * totalColumn));
	}
}

int main()
{
	char chunks[NUM_OF_CHUNKS][CHUNK_LENGTH];

	reset(chunks);

	strcpy(chunks[0], "3 else use it, and get a new on\0");
	strcpy(chunks[1], "2 toothbrush. Don't let anybody\0");
	strcpy(chunks[2], "4e every six months.\0");
	strcpy(chunks[3], "1Treat your password like your\0");
	
	// Encrypt chunks array
	encrypt_chunks(chunks);
	
	// Sort the chunks
	sort_chunks(4, 32, &chunks[0][0]);

	// Decrypt chunks array
	decrypt_chunks(&chunks[0][0]);
	
	// Display chunks
	display_chunks(&chunks[0][0]);
	
	return 0;
}