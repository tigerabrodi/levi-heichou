#include <stdio.h>
#include <stdlib.h>

// This is typing practice program

const char *subjects[] = {"The cat", "A boy", "She", "John"};
const char *verbs[] = {"jumps", "runs", "plays", "reads"};
const char *objects[] = {"the book", "a ball", "over the fence", "fast"};

int get_arr_length(char *array)
{
	return sizeof(array) / sizeof(array[0]);
}

char *create_random_sentence()
{
	char *sentence = malloc(get_arr_length(subjects) + get_arr_length(verbs) + get_arr_length(objects) + 1);
	int randomIndexForSubjects = rand() % get_arr_length(subjects);
	int randomIndexForVerbs = rand() % get_arr_length(verbs);
	int randomIndexForObjects = rand() % get_arr_length(objects);

	sprintf(sentence, "%s %s %s", subjects[randomIndexForSubjects], verbs[randomIndexForVerbs], objects[randomIndexForObjects]);

	return sentence;
}

double calculateAccuracy(char *original, char *input)
{
	int lengthOriginal = strlen(original);
	int lengthInput = strlen(input);
	int errors = 0;

	// If the lengths differ, add the difference to errors
	if (lengthOriginal != lengthInput)
	{
		errors += abs(lengthOriginal - lengthInput);
	}

	// Iterate over the smallest length
	int lengthToIterate = lengthOriginal < lengthInput ? lengthOriginal : lengthInput;

	for (int i = 0; i < lengthToIterate; i++)
	{
		if (original[i] != input[i])
		{
			errors++;
		}
	}

	int totalCharacters = lengthOriginal; // Total characters from the original sentence
	return 100.0 * (totalCharacters - errors) / totalCharacters;
}

int main()
{

	int randomIndexForSubjects = rand() % (sizeof(subjects) / sizeof(subjects[0]));
	int randomIndexForVerbs = rand() % (sizeof(verbs) / sizeof(verbs[0]));
	int randomIndexForObjects = rand() % (sizeof(objects) / sizeof(objects[0]));

	double total_accuracy = 0;

	printf("Welcome to Levi!\n");
	printf("This is typing practice game.\n");
	printf("We will calculate your accuracy throughout your tries.\n");
	printf("A random sentence will be generated and you've to under the sentence as fast as you can.\n");
	printf("If you enter 'end' the program will exit and display your score.\n");
	printf("If you enter 'score' the program will display your score.\n");

	while (1)
	{
		char *random_sentence = create_random_sentence();
		printf("Enter the sentence as fast as you can: %s", random_sentence);
		int user_sentence_length = get_arr_length(subjects) + get_arr_length(verbs) + get_arr_length(objects) + 1;
		char user_sentence[user_sentence_length];
		fgets(user_sentence, user_sentence_length, stdin);

		if (user_sentence == "end")
		{
			printf("Your accuracy score is: %f", total_accuracy);
			break;
		}

		if (user_sentence == "score")
		{
			printf("Your accuracy score is: %f", total_accuracy);
			continue;
		}

		// Here we calculate accuracy
		total_accuracy += calculateAccuracy(random_sentence, user_sentence);
	}

	return 0;
}