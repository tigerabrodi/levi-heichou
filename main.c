#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

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
