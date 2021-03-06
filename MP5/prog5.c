/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */

/*
 * Code breaking game - user enter a seed and try to guess the randomly generated 4 numbers in order. User has 12 chances
 * to guess the 4 numbers. With each valid guess the user will get feedback (perfect guess, misplaced guess) for each of
 * the 4 digits. Game ends when either user correctly guessed the 4 numbers or when user guessed 12 times incorrectly.
 */
#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
	int num = 0;
	char term;
	if (sscanf(seed_str, "%d%1s", &num, &term) != 1) 	// if more than 1 int input detected, invalid guess
	{
		printf("set_seed: invalid seed\n");
		return 0;
	}		
	
	num = abs(num);		// convert negative seed to positive seed
	srand(num);
	
    return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    guess_number = 1;			// init solution and guess #
    *one = rand() % 8 + 1;
    solution1 = *one;
    *two = rand() % 8 + 1;
    solution2 = *two;
    *three = rand() % 8 + 1;
    solution3 = *three;
    *four = rand() % 8 + 1;
    solution4 = *four;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
	int w,x,y,z;
	char term;
	int correct = 0;
	int misplaced = 0;
	int a = 0;	// a,b,c,d used as boolean values
	int b = 0;
	int c = 0;
	int d = 0;

	if (sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, &term) != 4)	// if didn't get 4 int, invalid guess
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}		
	else if (w < 1 || w > 8 || x < 1 || x > 8 || y < 1 || y > 8 || z < 1 || z > 8)		// 0 < guess < 9
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}

	*one = w;
	*two = x;
	*three = y;
	*four = z;

	if (solution1 == w) 	// these check for correct placements
	{
		a = 1;
		correct++;
	} 
	if (solution2 == x)
	{
		b = 1;
		correct++;
	}
	if (solution3 == y)
	{
		c = 1;
		correct++;
	}
	if (solution4 == z)
	{
		d = 1;
		correct++;
	}
							// these check for misplaced
	if ((a == 0) && ((b == 0 && w == solution2) || (c == 0 && w == solution3) || (d == 0 && w == solution4)))
		misplaced++;
	if ((b == 0) && ((a == 0 && x == solution1) || (c == 0 && x == solution3) || (d == 0 && x == solution4)))
		misplaced++;
	if ((c == 0) && ((b == 0 && y == solution2) || (a == 0 && y == solution1) || (d == 0 && y == solution4)))
		misplaced++;
	if ((d == 0) && ((b == 0 && z == solution2) || (c == 0 && z == solution3) || (a == 0 && z == solution1)))
		misplaced++;

	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, correct, misplaced);
	guess_number++;
    return 1;
}


