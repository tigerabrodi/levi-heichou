#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char *subjects[] = {"The cat", "A boy", "She", "John"};
const char *verbs[] = {"jumps", "runs", "plays", "reads"};
const char *objects[] = {"the book", "a ball", "over the fence", "fast"};

char *create_random_sentence()
{
	// Generate random index to pick subject, verb, and object
	int random_index_for_subjects = rand() % 4;
	int random_index_for_verbs = rand() % 4;
	int random_index_for_objects = rand() % 4;

	char *sentence = malloc(50);

	if (sentence == NULL)
	{
		printf("Error allocating memory!\n");
		exit(1);
	}

	// Create a random sentence using sprintf
	sprintf(sentence, "%s %s %s", subjects[random_index_for_subjects], verbs[random_index_for_verbs], objects[random_index_for_objects]);

	// Return the created random sentence
	return sentence;
}

// Function to find the minimum among three numbers
int find_minimum(int a, int b, int c)
{
	if (a <= b && a <= c)
		return a;
	if (b <= a && b <= c)
		return b;
	return c;
}

// Function to calculate typing accuracy using Levenshtein distance
double calculate_accuracy(char *original_sentence, char *input_sentence)
{
	// Get the length of both the original and input sentences
	int original_length = strlen(original_sentence);
	int input_length = strlen(input_sentence);

	// Initialize a 2D array to store Levenshtein distances
	int levenshtein_matrix[original_length + 1][input_length + 1];

	// Loop through each character of both strings
	for (int row = 0; row <= original_length; row++)
	{
		for (int col = 0; col <= input_length; col++)
		{
			// If original sentence is empty, distance is length of input sentence
			if (row == 0)
			{
				levenshtein_matrix[row][col] = col;
			}
			// If input sentence is empty, distance is length of original sentence
			else if (col == 0)
			{
				levenshtein_matrix[row][col] = row;
			}
			// If characters match, no additional cost
			else if (original_sentence[row - 1] == input_sentence[col - 1])
			{
				levenshtein_matrix[row][col] = levenshtein_matrix[row - 1][col - 1];
			}
			// If characters don't match, take minimum of three previous distances
			else
			{
				levenshtein_matrix[row][col] = 1 + find_minimum(
								       levenshtein_matrix[row - 1][col],    // Deletion
								       levenshtein_matrix[row][col - 1],    // Insertion
								       levenshtein_matrix[row - 1][col - 1] // Substitution
								   );
			}
		}
	}

	// Get Levenshtein distance from last element of matrix
	int total_errors = levenshtein_matrix[original_length][input_length];

	// Calculate and return the accuracy as percentage
	return 100.0 * (original_length - total_errors) / original_length;
}

void print_start_message()
{
	printf("Welcome to Levi!\n");
	printf("This is a typing practice game.\n");
	printf("We will calculate your accuracy throughout your tries using the Levenshtein distance.\n");
	printf("A random sentence will be generated and you've to under the sentence as fast as you can.\n");
	printf("If you enter 'end' the program will exit and display your score.\n");
	printf("If you enter 'score' the program will display your score.\n");
}