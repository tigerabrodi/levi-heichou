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
	int randomIndexForSubjects = rand() % 4; // rand() returns a random integer
	int randomIndexForVerbs = rand() % 4;
	int randomIndexForObjects = rand() % 4;

	char *sentence = malloc(50);

	// Create a random sentence using sprintf
	sprintf(sentence, "%s %s %s", subjects[randomIndexForSubjects], verbs[randomIndexForVerbs], objects[randomIndexForObjects]);

	// Return the created random sentence
	return sentence;
}

// Function to calculate typing accuracy
double calculateAccuracy(char *original, char *input)
{
	// Get lengths of original sentence and user input
	int lengthOriginal = strlen(original);
	int lengthInput = strlen(input);
	int errors = 0;

	// If lengths are different, it's an error
	if (lengthOriginal != lengthInput)
	{
		errors += abs(lengthOriginal - lengthInput);
	}

	// Choose smaller length to iterate through characters
	int lengthToIterate = lengthOriginal < lengthInput ? lengthOriginal : lengthInput;

	// Loop through characters and count errors
	for (int i = 0; i < lengthToIterate; i++)
	{
		if (original[i] != input[i])
		{
			errors++;
		}
	}

	// Calculate accuracy as percentage
	int totalCharacters = lengthOriginal;
	return 100.0 * (totalCharacters - errors) / totalCharacters;
}

// Main function
int main()
{
	srand(time(0)); // Seed the random number generator with current time

	// Initialize variables for keeping track of overall accuracy
	double total_accuracy = 0;
	int rounds_played = 0;

	// Print welcome message
	printf("Welcome to Levi!\n");
	printf("This is a typing practice game.\n");

	// Infinite loop for game
	while (1)
	{
		// Generate a random sentence
		char *random_sentence = create_random_sentence();

		// Display the random sentence to the user
		printf("Enter the sentence as fast as you can: %s\n", random_sentence);

		char user_sentence[256];
		fgets(user_sentence, 256, stdin);

		user_sentence[strcspn(user_sentence, "\n")] = 0;

		if (strcmp(user_sentence, "end") == 0)
		{
			printf("Your final accuracy score is: %f\n", total_accuracy / rounds_played);
			printf("Thanks for playing!\n");
			free(random_sentence);
			break;
		}

		if (strcmp(user_sentence, "score") == 0)
		{
			printf("Your current accuracy score is: %f\n", total_accuracy / rounds_played);
		}
		else
		{
			double accuracy = calculateAccuracy(random_sentence, user_sentence);
			total_accuracy += accuracy;
			rounds_played++;
		}

		// Free the allocated memory for the random sentence
		free(random_sentence);
	}

	return 0;
}
