//program recieves key from command line arguement, prompts for plaintext, encrypts and then returns ciphertext
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

//declare function
string encrypt(int i, int a, int z, int key, string arrc, char j, string text);

int main(int argc, string argv[])
{
    //check if single command line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //check if chars of argument are non-negative integers
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            //look at each character
            char c = argv[1][i];
            
            //check ascii value to see if between 0 & 9
            if (c < 48 || c > 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        //ask for plaintext to encrypt
        string text = get_string("plaintext: ");

        //declare variables
        char arrc[strlen(text) + 1];
        char j;
        int key = atoi(argv[1]);
        int a = 97;
        int z = 122;
        int A = 65;
        int Z = 90;

        //shift chars in plaintext by key amount (create ciphertext)
        for (int i = 0; text[i] != '\0'; i++)
        {
            //check if capital letter and encrypt
            if (text[i] >= A && text[i] <= Z)
            {
                //use encrypt function with lower case boundaries
                encrypt(i, A, Z, key, arrc, j, text);
            }

            //check if lowercase letter and encrypt
            else if (text[i] >= a && text[i] <= z)
            {
                //use encrypt function with lower case boundaries
                encrypt(i, a, z, key, arrc, j, text);
            }

            //if not letter, do not encrypt
            else
            {
                j = text[i];
                arrc[i] = j;
            }
        }
        //append zero character to end of ciphertext char array (creating string)
        arrc[strlen(text)] = '\0';

        //print ciphertext
        printf("ciphertext: %s\n", arrc);
        return 0;
    }
}

//define encrypt function
string encrypt(int i, int a, int z, int key, string arrc, char j, string text)
{
    //check if key is longer than length of alphabet
    if (key > 26)
    {
        //reduce key to remainder after divison by 26 (alphabet length)
        key = key % 26;

        //if key will extend char value past z, wrap back to a
        if (key > z - text[i])
        {
            j = key - (z - text[i]) + a - 1;
        }
        else
        {
            j = text[i] + key;
        }
    }

    //if key will extend char value past z, wrap back to a
    else if (key > z - text[i])
    {
        j = key - (z - text[i]) + a - 1;
    }
    else
    {
        j = key + text[i];
    }
    arrc[i] = j;
    return arrc;
}
