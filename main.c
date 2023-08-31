#include <stdio.h>  // For standard input-output functions
#include <stdlib.h> // For memory allocation and random number generation
#include <string.h> // For string manipulation functions like strlen
#include <time.h>   // For time-related functions (used for random seed)

// Declare arrays of subjects, verbs, and objects for random sentence generation
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

// Function to calculate typing accuracy
double calculate_accuracy(char *original, char *input)
{
	// Get lengths of original sentence and user input
	int length_original = strlen(original);
	int length_input = strlen(input);
	int errors = 0;

	// If lengths are different, it's an error (for now)
	if (length_original != length_input)
	{
		errors += abs(length_original - length_input);
	}

	// Choose smaller length to iterate through characters
	int is_input_longer = length_original < length_input;
	int length_to_iterate = is_input_longer ? length_original : length_input;

	// Loop through characters and count errors
	for (int i = 0; i < length_to_iterate; i++)
	{
		int is_letter_not_match = original[i] != input[i];
		if (is_letter_not_match)
		{
			errors++;
		}
	}

	// Calculate accuracy as percentage
	int total_characters = length_original;
	return 100.0 * (total_characters - errors) / total_characters;
}

void print_start_message()
{
	printf("Welcome to Levi!\n");
	printf("This is a typing practice game.\n");
	printf("We will calculate your accuracy throughout your tries.\n");
	printf("A random sentence will be generated and you've to under the sentence as fast as you can.\n");
	printf("If you enter 'end' the program will exit and display your score.\n");
	printf("If you enter 'score' the program will display your score.\n");
}

int main()
{
	srand(time(0)); // Seed the random number generator with current time

	double total_accuracy = 0;
	int rounds_played = 0;

	print_start_message();

	while (1)
	{
		char *random_sentence = create_random_sentence();

		printf("Enter the sentence as fast as you can: %s\n", random_sentence);

		char user_sentence[256];
		fgets(user_sentence, 256, stdin);

		user_sentence[strcspn(user_sentence, "\n")] = 0;

		int should_exit = strcmp(user_sentence, "end") == 0;
		if (should_exit)
		{
			printf("Your final accuracy score is: %f\n", total_accuracy / rounds_played);
			printf("Thanks for playing!\n");
			free(random_sentence);
			break;
		}

		int should_display_score = strcmp(user_sentence, "score") == 0;
		if (should_display_score)
		{
			printf("Your current accuracy score is: %f\n", total_accuracy / rounds_played);
			continue;
		}

		double accuracy = calculate_accuracy(random_sentence, user_sentence);
		total_accuracy += accuracy;
		rounds_played++;

		// Free the allocated memory for the random sentence
		free(random_sentence);
	}

	return 0;
}
