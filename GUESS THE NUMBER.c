
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator using the current time
    srand(time(0));

    // Generate a random number between 0 and RAND_MAX (default range)
    int randomnumber = (rand()%100) + 1;
    int no_of_guesses= 0;
    int guessed;

    //printf("Random number between 0 and RAND_MAX: %d\n", random_number);

    do
    {
        printf("guess the number: ");
        scanf("%d", &guessed);
        if (guessed > randomnumber){
            printf("lower number pls!\n");
        }
        else if (guessed> randomnumber){
            printf("higher number pls!");
        }
        else {
            printf("congrats!!\n");
        }
        no_of_guesses++;
    } 
    while (guessed != randomnumber);
    printf("You guessed the number in %d guesses ",no_of_guesses);
    
    return 0;
}
