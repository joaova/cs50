#include <stdio.h>
#include <math.h>
#include <cs50.h>

// Prototypes
bool is_card_valid(long, int, int, bool);
void card_company(long);
int count_digits(long);

// Main function
int main(void)
{
    bool digit_position = 0;
    int sum = 0;
    int sum2 = 0;
    long card_number = get_long("Number: ");

    // Checks if function returns true
    if (is_card_valid(card_number, sum, sum2, digit_position) == 1)
    {
        card_company(card_number);
        return 0;
    }

    printf("INVALID\n");

    return 0;

}

// Function that performs Luhn’s Algorithm
bool is_card_valid(long card_number, int sum, int sum2, bool digit_position)
{
    // Base condition for recursion
    if (card_number == 0)
    {
        // Adds results from digits manipulation
        int total_sum = sum + sum2;

        // Checks if sum ends with 0
        if (total_sum % 10 == 0)
        {
            // Returns true
            return 1;
        }

        // Returns false
        return 0;
    }

    // new_card is used as a card_number without the last digit, for recursion
    long new_card = card_number / 10;

    // Digits that won't be multiplied
    if (digit_position == 0)
    {
        
        // Adds last digit's value to overall sum
        sum += card_number % 10;

        // Change digit's position (next digit is going to be multiplied by 2)
        digit_position = 1;

        // Call itself with updated values
        return (is_card_valid(new_card, sum, sum2, digit_position));
    }

    // Every other digit, starting with the second-to-last digit
    else
    {
        int last_digit_multiplied;
        int digit_sum;

        // Get the last digit and multiply it by 2
        last_digit_multiplied = card_number % 10 * 2;

        // If the last_digit multiplication is a 2 digit number, gets the sum of those digits. Else, it just stores the digit value.
        digit_sum = last_digit_multiplied % 10 + last_digit_multiplied / 10;

        // Keeps track of the digits' sum
        sum2 += digit_sum;

        // Change the next digit's position
        digit_position = 0;

        // Call itself with updated values
        return (is_card_valid(new_card, sum, sum2, digit_position));
    }

}

// Prints card brand
void card_company(long card_number)
{
    int total_digits = count_digits(card_number);
    int first_two_digits = card_number / pow(10, total_digits - 2);

    // Condition for american express cards
    if (total_digits == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }

    // Condition for mastercard cards
    else if (total_digits == 16 && (first_two_digits > 50 && first_two_digits < 56))
    {
        printf("MASTERCARD\n");
    }

    // Condition for VISA cards
    else if ((total_digits == 16 || total_digits == 13) && first_two_digits / 10 == 4)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}

// Calculates total digits in a card number
int count_digits(long number)
{
    int count = 0;

    while (number != 0)
    {
        number /= 10;
        count ++;
    }

    return count;
}
