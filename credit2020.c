#include<stdio.h>
#include<cs50.h>

int get_length(long n);
int checksum(long n, int d);
long expon(int e);

int main(void)
{

    //the name of the variables pretty much are self explanatory
    long cc_number = get_long("Type your credit card number: \n");
    int digits = get_length(cc_number);
    int luhns_validation = checksum(cc_number, digits) % 10;
    int first_two_digits = cc_number / expon(digits - 2);
    int first_digit = cc_number / expon(digits - 1);

    //this line is not really needed, but it makes the algorithm really straight foward if the cc number is obviously invalid
    if (luhns_validation != 0 || digits > 16 || digits < 13)
    {
        printf("INVALID\n");
    }
    
    //i use the switch here in order to differentiate between the companies
    else 
    {
        switch (digits)
        {
            case 13: 
                if (first_digit == 4)
                {
                    printf("VISA\n");
                }
                
                //even though there is a default, in some cases luhn's algorithm is satisfied, 
                //but the number doesnt start with a valid digit
                else
                {
                    printf("INVALID\n"); 
                }
                break;

            case 14:
                if (first_digit == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n"); 
                }
                break;

            //here I need to separete between visa and amex, since they both have 15 digits
            case 15: 
                if (first_digit == 4)
                {
                    printf("VISA\n");
                }
                else if (first_two_digits == 34 || first_two_digits == 37)
                {
                    printf("AMEX\n");
                }
                else 
                {
                    printf("INVALID\n"); 
                }
                break;

            //since master and visa can both have 16 digits, I need to segreggate them here
            case 16:
                if (first_digit == 4)
                {
                    printf("VISA\n");
                }
                else if (first_two_digits > 50 && first_two_digits < 56)
                {
                    printf("MASTERCARD\n");
                }
                else 
                {
                    printf("INVALID\n"); 
                }
                break;
            //if invalid, it will print the default option
            default:
                printf("INVALID\n");
                break;
        }
    }
}

//this is a simple function to get the length of the credit card number in digits
int get_length(long n)
{
    int i = 1;

    while (n / 10 > 0)
    {
        n = n / 10;
        i++;
    }
    return i;
}

//this function is responsible to give me the sum of Luhn's algorithm
int checksum(long n, int d)
{
    int sum = 0;
    long modulo_result = 0;

    //this loop will check if the number is odd or even.
    for (int c = 1; c <= d; c++)
    {
        long new_n = n / expon(c - 1);
        int single_digit = new_n % 10;

        //whenever odd, I'll add the number to sum
        if (c % 2 != 0) 
        {
            sum += single_digit;
        }
        
        //if even, I'll multiply it by 2
        else
        {   
            modulo_result = single_digit * 2;

            //it is important to note that if the number if >= 10, we need to separate the digits before incrementing sum
            if (modulo_result >= 10)
            {
                sum += modulo_result % 10 + modulo_result / 10;
            }
            else
            {
                sum += modulo_result;
            }    
        }        
    }

    return sum;         
}

//I se this function to exponentiate 10 by 10 n times. Is is useful in order to get each digit later
long expon(int e) 
{
    long res = 1;

    for (int counter = 0; counter < e; counter++)
    {
        res *= 10;
    }

    return res;
}
