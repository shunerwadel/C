//exercise in implementing a function in C

#include <stdio.h>
#include <cs50.h>

//declare function
bool valid_triangle(float a, float b, float c);

int main(void)
{
    //get input from user
    int a = get_int("What is length of side 1?: ");
    int b = get_int("What is length of side 2?: ");
    int c = get_int("What is length of side 3?: ");

    //call function
    bool result = valid_triangle(a, b, c);

    //print to terminal
    if (result == true)
    {
        printf("That can be a triangle :)\n");
    }
    else
    {
        printf("Can't make a triangle from that :(\n");
    }
}


//define function
bool valid_triangle(float a, float b, float c)
{
    //check if all inputs are positive
    if (a > 0 && b > 0 && c > 0)
    {
        //check if inputs could make triangle
        if (a + b > c && b + c > a && a + c > b)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}