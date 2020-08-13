//program to return readability grade level of given text
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//declare functions
int count_letters(string text, int n);
int count_words(string text, int n);
int count_sents(string text, int n);

int main(void)
{
    //get user input
    string text = get_string("Text: ");

    //find total number of characters
    int n = strlen(text);

    //determine number of letters
    int letters = count_letters(text, n);

    //determine number of words
    int words = count_words(text, n);

    //determine number of sentences
    int sents = count_sents(text, n);

    //average number of letters per 100 words
    float l = ((float)letters / (float)words) * 100;

    //average number of sentences per 100 words
    float s = ((float)sents / (float)words) * 100;

    //calculate grade level
    float index = round(0.0588 * l - 0.296 * s - 15.8);

    //print grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

//define funtion that counts number of letters in a string
int count_letters(string text, int n)
{
    //declare variables
    int letters = 0;

    //count only letters
    for (int i = 0; i <= n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            letters += 1;
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters += 1;
        }
    }
    return letters;
}

//define function that counts number of words in a string
int count_words(string text, int n)
{
    //declare variables
    int words = 1;

    //find number of spaces to determine word count
    for (int i = 0; i <= n; i++)
    {
        if (text[i] == ' ')
        {
            words += 1;
        }
    }
    return words;
}

//define function that counts number of sentences in a string
int count_sents(string text, int n)
{
    //declare variables
    int sents = 0;

    //find number of ".", "!", and "?" to determine sentence count
    for (int i = 0; i <= n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sents += 1;
        }
    }
    return sents;
}