#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

// Global array to store words from the file
char words[5000][21];

// Hint Messages
// Level 1 Hints
const char *levelonehinthow[4] = {
    "Hint 1: I'm not straightforward, I'm straight-backward!",
    "Hint 1: To find the original, you might need to reflect on your answer.",
    "Hint 1: Sometimes, the right perspective is looking at things from the end.",
    "Hint 1: I've turned things around, quite literally."};
const char *levelonehinttaunt[4] = {
    "Are you for real??",
    "Really, you can't even figure this one out?",
    "Come on, this is as easy as it gets!",
    "Oh my god, you can't actually be this stupid!"};
const char *levelonehintfinal[4] = {
    "The word was just reversed. As simple as that.",
    "All I did was flip the word. That's it.",
    "The answer was in front of you, just backward.",
    "It was just reversed. The simplest trick in the book."};

// Level 2 Hints
const char *leveltwohinthow[4] = {
    "Hint 1: I'm a fan of moving things around, following a certain number's lead.",
    "Hint 1: Every letter has taken a uniform step away from its original self.",
    "Hint 1: Think of the alphabet as a circular journey, and every letter has traveled the same distance.",
    "Hint 1: A simple shift is all that hides the truth."};
const char *leveltwohintfinal[4] = {
    "Each letter of the word was shifted by a constant factor along the alphabet.",
    "The word was encrypted using a Caesar cipher, shifting each letter by the same amount.",
    "A simple letter shift was applied to the entire word.",
    "Every letter was moved forward or backward by the same number of steps."};

// Level 3 Hints
const char *levelthreehinthow[4] = {
    "Hint 1: I like to keep things balanced, a little push, a little pull.",
    "Hint 1: The letters are dancing, one step forward, one step back.",
    "Hint 1: This is a game of alternating perspectives.",
    "Hint 1: The encryption is a two-step, a rhythmic shift."};
const char *levelthreehintfinal[4] = {
    "The letters were shifted alternately forward and backward by the factor.",
    "An alternating Caesar cipher was used, switching between adding and subtracting the factor.",
    "Each letter was shifted, but the direction of the shift alternated.",
    "The encryption involved shifting letters, with the direction changing for each subsequent letter."};

// Level 4 Hints
const char *levelfourhinthow[4] = {
    "Hint 1: A little mix-up between neighbors can change everything.",
    "Hint 1: Things have gotten shuffled, but not too far from home.",
    "Hint 1: I've played a little switcheroo with adjacent characters.",
    "Hint 1: The word is a bit scrambled, like partners changing places on a dance floor."};
const char *levelfourhintfinal[4] = {
    "Adjacent letters in the word were swapped with each other.",
    "The encryption was a simple adjacent letter shuffle.",
    "I just interchanged each letter with its neighbor to encrypt the word.",
    "The word's letters were swapped in pairs."};

// Level 5 Hints
const char *levelfivehinthow[4] = {
    "Hint 1: This encryption is a bit of an equation, where position and value matter.",
    "Hint 1: Think of it as a polynomial problem, where each letter is a coefficient.",
    "Hint 1: The complexity grows with each letter, exponentially you might say.",
    "Hint 1: It's a mathematical transformation, a function of the letter's place and the secret factor."};
const char *levelfivehintfinal[4] = {
    "Each letter's alphabet position was multiplied by the factor raised to the power of the letter's position in the word. The result modulo 26 gave the new letter.",
    "The encryption followed the formula: (letter's value) * (factor ^ letter's index), then mapped back to the alphabet.",
    "It's a positional-exponential cipher. The new letter is ((original_char - 'a' + 1) * pow(factor, index + 1)) mod 26.",
    "A polynomial-like function was applied, where each letter's value was scaled by a power of the factor."};

// Level 6 Hints
const char *levelsixhinthow[4] = {
    "Hint 1: I've taken the last puzzle and added a layer of calculus to it.",
    "Hint 1: What happens when you find the rate of change of the previous level's equation?",
    "Hint 1: It's not just a function, but its derivative that holds the key.",
    "Hint 1: From polynomials to their derivatives, the logic has evolved."};
const char *levelsixhintfinal[4] = {
    "The word was treated as a polynomial. This polynomial was then differentiated a number of times equal to the factor. The resulting polynomial evaluated at the factor gave the new word.",
    "It's a derivative-based encryption. The word-as-a-polynomial was differentiated 'factor' times.",
    "The logic is the same as Level 5, but applied to the 'factor'-th derivative of the word's polynomial representation.",
    "Calculus was the key. We differentiated the polynomial of the word and evaluated it."};

// Generic Hints
const char *factorparityeven[4] = {
    "Hint 2: The secret number, the 'factor', is an even one.",
    "Hint 2: I can tell you this much: the factor is divisible by two.",
    "Hint 2: The key number in this puzzle is an even one.",
    "Hint 2: You're looking for an even number as the factor."};
const char *factorparityodd[4] = {
    "Hint 2: The secret 'factor' is an odd number.",
    "Hint 2: The number you're looking for, the factor, isn't divisible by two.",
    "Hint 2: I've chosen an odd number for the factor.",
    "Hint 2: The factor is an odd one, that's your clue."};
const char *factorprimeis[4] = {
    "Hint 3: The factor is a prime number, divisible only by 1 and itself.",
    "Hint 3: Your secret number is a prime.",
    "Hint 3: I chose a prime number for the factor.",
    "Hint 3: The factor is a number in its prime."};
const char *factorprimenot[4] = {
    "Hint 3: The factor is not a prime number.",
    "Hint 3: The secret number is a composite one.",
    "Hint 3: I can assure you the factor is not a prime.",
    "Hint 3: The factor has more divisors than just 1 and itself."};

// Function Prototypes
void showmenu();
int isprime(int n);
void printrandomhint(const char *hints[4]);
void levelone();
void leveltwo();
void levelthree();
void levelfour();
void levelfive();
void levelsix();
void playgame(int level, const char *word, int factor);

// The main function
int main()
{
    FILE *file = fopen("WORDS.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open WORDS.txt. Please make sure the file exists in the same directory.\n");
        return 1;
    }
    for (int i = 0; i < 5000; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    fclose(file);

    srand(time(NULL));

    printf("\n\n========================================================\n");
    printf("==                 WELCOME TO WORDLE!                 ==\n");
    printf("========================================================\n\n");
    printf("This is a word-guessing game where you try to figure out the original word\n");
    printf("from an encrypted version. Are you ready for the challenge?\n\n");

    printf("--------------------[ TIPS & TRICKS ]---------------------\n");
    printf("| - Each level uses a secret number called a 'factor' (1-9).\n");
    printf("| - Difficulty increases with each level.\n");
    printf("| - You can type 'H' for a hint or 'Q' to quit anytime.\n");
    printf("| - You have 5 hints per round. Use them wisely!\n");
    printf("----------------------------------------------------------\n\n");

    char choice[10];
    int levelchoice;

    while (1)
    {
        showmenu();
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strlen(choice) == 1)
        {
            if (toupper(choice[0]) == 'Q')
            {
                printf("\nThank you for playing Wordle!\n");
                break;
            }
            if (toupper(choice[0]) == 'H')
            {
                printf("\nYou need to be in a game to ask for a hint, silly!\n\n");
                continue;
            }
        }

        levelchoice = atoi(choice);
        switch (levelchoice)
        {
        case 1:
            levelone();
            break;
        case 2:
            leveltwo();
            break;
        case 3:
            levelthree();
            break;
        case 4:
            levelfour();
            break;
        case 5:
            levelfive();
            break;
        case 6:
            levelsix();
            break;
        default:
            printf("\nInvalid choice. Please enter a number between 1 and 6.\n\n");
        }
    }

    return 0;
}

void showmenu()
{
    printf("Choose a level to begin:\n");
    printf("1. Super Easy\n");
    printf("2. Easy\n");
    printf("3. Moderate\n");
    printf("4. Hard\n");
    printf("5. Super Hard\n");
    printf("6. Impossible\n");
    printf("\nType 'Q' to quit the game.\n\n");
}

int isprime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void printrandomhint(const char *hints[4])
{
    printf("%s\n\n", hints[rand() % 4]);
}

void levelone()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int factor = 1;

    char encrypted[21];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        encrypted[i] = word[len - 1 - i];
    }
    encrypted[len] = '\0';

    printf("\n--- LEVEL 1: SUPER EASY ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(levelonehinthow);

    playgame(1, word, factor);
}

void leveltwo()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int factor = (rand() % 9) + 1;

    char encrypted[21];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int shift = factor % 2 != 0 ? factor : -factor;
        encrypted[i] = 'a' + (word[i] - 'a' + shift + 26) % 26;
    }
    encrypted[len] = '\0';

    printf("\n--- LEVEL 2: EASY ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(leveltwohinthow);

    playgame(2, word, factor);
}

void levelthree()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int factor = (rand() % 9) + 1;

    char encrypted[21];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int shift;
        if (factor % 2 != 0)
        {
            shift = (i % 2 == 0) ? factor : -factor;
        }
        else
        {
            shift = (i % 2 == 0) ? -factor : factor;
        }
        encrypted[i] = 'a' + (word[i] - 'a' + shift + 26) % 26;
    }
    encrypted[len] = '\0';

    printf("\n--- LEVEL 3: MODERATE ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(levelthreehinthow);

    playgame(3, word, factor);
}

void levelfour()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int factor = (rand() % 5) * 2 + 1; // Always odd

    char encrypted[21];
    strcpy(encrypted, word);
    int len = strlen(word);
    for (int i = 0; i < len - 1; i += 2)
    {
        char temp = encrypted[i];
        encrypted[i] = encrypted[i + 1];
        encrypted[i + 1] = temp;
    }

    printf("\n--- LEVEL 4: HARD ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(levelfourhinthow);

    playgame(4, word, factor);
}

void levelfive()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int factor = (rand() % 9) + 1;

    char encrypted[21];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        long long val = (word[i] - 'a' + 1) * (long long)pow(factor, i + 1);
        encrypted[i] = 'a' + (val - 1) % 26;
    }
    encrypted[len] = '\0';

    printf("\n--- LEVEL 5: SUPER HARD ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(levelfivehinthow);

    playgame(5, word, factor);
}

void levelsix()
{
    char word[21];
    strcpy(word, words[rand() % 5000]);
    int maxfactor = strlen(word) > 9 ? 9 : strlen(word);
    if (maxfactor < 1) maxfactor = 1;
    int factor = (rand() % maxfactor) + 1;

    char encrypted[21];
    int len = strlen(word);
    long long coeffs[21];
    for(int i=0; i<len; i++) {
        coeffs[i] = word[i] - 'a' + 1;
    }

    for (int d = 0; d < factor; d++) {
        for (int i = 0; i < len - 1; i++) {
            coeffs[i] = (i + 1) * coeffs[i+1];
        }
        coeffs[len - 1 - d] = 0;
    }

    for (int i = 0; i < len; i++) {
        long long termval = 0;
        if(coeffs[i] > 0) {
            termval = coeffs[i] * (long long)pow(factor, i);
        }
        if (termval <= 0) {
            encrypted[i] = 'z';
        } else {
             encrypted[i] = 'a' + (termval - 1) % 26;
        }
    }
    encrypted[len] = '\0';

    printf("\n--- LEVEL 6: IMPOSSIBLE ---\n");
    printf("The encrypted word is: %s\n\n", encrypted);
    printrandomhint(levelsixhinthow);

    playgame(6, word, factor);
}

void playgame(int level, const char *word, int factor)
{
    char guess[21];
    int hints = 1;

    while (1)
    {
        printf("Enter your guess: ");
        scanf("%s", guess);

        if (strlen(guess) == 1)
        {
            if (toupper(guess[0]) == 'Q')
            {
                printf("\nThe correct word was '%s'.\n", word);
                if (level == 1) printrandomhint(levelonehintfinal);
                if (level == 2) printrandomhint(leveltwohintfinal);
                if (level == 3) printrandomhint(levelthreehintfinal);
                if (level == 4) printrandomhint(levelfourhintfinal);
                if (level == 5) printrandomhint(levelfivehintfinal);
                if (level == 6) printrandomhint(levelsixhintfinal);
                printf("Thank you for playing Wordle!\n");
                exit(0);
            }
            if (toupper(guess[0]) == 'H')
            {
                hints++;
                if (hints > 5)
                {
                    printf("You have used all your hints!\n\n");
                    continue;
                }

                if (level == 1)
                {
                    if (hints >= 2 && hints <= 4)
                        printrandomhint(levelonehinttaunt);
                    if (hints == 5)
                    {
                        printf("The word was '%s'.\n", word);
                        printrandomhint(levelonehintfinal);
                        return;
                    }
                }
                else
                {
                    if (hints == 2)
                    {
                        if (factor % 2 == 0)
                            printrandomhint(factorparityeven);
                        else
                            printrandomhint(factorparityodd);
                    }
                    else if (hints == 3)
                    {
                        if (isprime(factor))
                            printrandomhint(factorprimeis);
                        else
                            printrandomhint(factorprimenot);
                    }
                    else if (hints == 4)
                    {
                        printf("Hint 4: The logic is simpler than you think. Re-read the first hint carefully!\n\n");
                    }
                    else if (hints == 5)
                    {
                        printf("The word was '%s'.\n", word);
                        if (level == 2) printrandomhint(leveltwohintfinal);
                        if (level == 3) printrandomhint(levelthreehintfinal);
                        if (level == 4) printrandomhint(levelfourhintfinal);
                        if (level == 5) printrandomhint(levelfivehintfinal);
                        if (level == 6) printrandomhint(levelsixhintfinal);
                        return;
                    }
                }
                continue;
            }
            // An error message for single letter guesses
            printf("SINGLE LETTERS ARE NOT ALLOWED AS VALID WORD GUESSES.\n\n");
            continue;
        }

        // The user's guess is compared
        if (strcasecmp(guess, word) == 0)
        {
            printf("\nCongratulations! You guessed the word correctly!\n\n");
            return;
        }
        else
        {
            printf("Incorrect guess. Try again!\n\n");
        }
    }
}
