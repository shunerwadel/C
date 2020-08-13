//calculates minimum coins required for amount of change owed
#include <stdio.h>
#include <cs50.h>
#include <math.h>

//declare functions
int change(int *new_owed, int coin, int *returned);

int main(void)
{
    //declare variables
    int returned = 0;
    int new_returned = 0;
    int coin = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    float owed;

    //ask for change owed
    do
    {
        owed = get_float("Change owed: ");
    }
    while (owed < 0);

    //convert to integer
    owed = round(owed * 100);
    int new_owed = (int)owed;

    //determine how many quarters should be returned
    if (new_owed >= quarter)
    {
        coin = quarter;
        change(&new_owed, coin, &returned);
    }

    //determine how many dimes should be returned
    if (new_owed >= dime)
    {
        coin = dime;
        change(&new_owed, coin, &returned);
    }

    //determine how many nickels should be returned
    if (new_owed >= nickel)
    {
        coin = nickel;
        change(&new_owed, coin, &returned);
    }

    //determine how many pennies should be returned
    if (new_owed >= penny)
    {
        coin = penny;
        change(&new_owed, coin, &returned);
    }

    //number of coins returned
    printf("%i\n", returned);
}

//function to determine amount of each coin required
int change(int *new_owed, int coin, int *returned)
{
    int new_returned = (*new_owed / coin);
    *returned = *returned + new_returned;
    *new_owed = *new_owed - new_returned * coin;
    return *new_owed;
    return *returned;
}

