#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "string_struct_and_functions.h"

typedef struct
{
    StringOfChars * buffer_strings;
    size_t length;
    size_t capacity;
} VectorStrings;

void continue_program(void)
{
    StringOfChars input = input_growable_string();
    free(input.buffer);
}

void print_vector_strings(StringOfChars * vector_strings, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%s\n", vector_strings[i].buffer);
    }
}

void free_strings_in_vector(StringOfChars * vector_strings, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        free(vector_strings[i].buffer);
    }
}

int main(void)
{
    
    /*size_t len_1 = calc_arraychars_length("ABCDJSDKSDDFSJ");
    StringOfChars string1 = new_string("ABCDJSDKSDDFSJ", len_1);
    printf("%s\n", string1.buffer);
    size_t len_2 = calc_arraychars_length("ZNKVISHNDFSIDFJSDJFG");
    StringOfChars string2 = new_string("ZNKVISHNDFSIDFJSDJFG", len_2);
    printf("%s\n", string2.buffer);

    concatenate_strings(&string1, &string2);
    printf("%s\n", string1.buffer);
    free(string1.buffer);
    free(string2.buffer);*/

    //printf("================= PART 1 OF THE PROGRAM =================\n");

    int amount_strings;
    printf("(Please enter only numbers in order not to crash the program)\nHow many text strings would you like to input? ");
    scanf("%d", &amount_strings);

    StringOfChars * buffer_strings = (StringOfChars*)malloc(amount_strings * sizeof(StringOfChars));

    int i = 0;
    //bool continue_loop = false;

    //while (i <= amount_strings)
    while (i < amount_strings)
    {
        //if (i >= 1)
        //{
            printf("Enter the string number %d (any amount of characters should work!): ", i + 1);
            buffer_strings[i] = input_growable_string();
        //}
        ++i;
        //continue_loop = true;
    }

    printf("These were the strings you printed: \n");
    print_vector_strings(buffer_strings, amount_strings);

    char first_string_to_concat[] = "The fully concatenated string: ";
    size_t length = calc_arraychars_length(first_string_to_concat);
    //printf("%s, %d\n", first_string_to_concat, length);

    StringOfChars concatenated_string = new_string(first_string_to_concat, length);
    //printf("%s\n", concatenated_string.buffer);

    //StringOfChars concatenated_string = construct_string();
    printf("Now let us concatenate them all (as well as insert some text of our own!). Press any key: \n");
    //StringOfChars input_1 = input_growable_string();
    continue_program();
    for (size_t j = 0; j < amount_strings; ++j)
    {
        int success = concatenate_strings(&concatenated_string, &buffer_strings[j]);
        if (success == 1)
        {
            printf("Successfully concatenated strings in loop number %d\n", j + 1);
        } else
        {
            printf("There was an error while concatenating the strings.");
        }
    }

    //printf("The fully concatenated string with all the inputs you provided is %s\n", concatenated_string.buffer);
    printf("%s\n", concatenated_string.buffer);

    //free(input_1.buffer);

    //printf("\n================= PART 2 OF THE PROGRAM =================\n");
    printf("Moreover, the characters in the concatenated string all have ASCII values that can be expressed in hexadecimal and decimal.\n");
    printf("Let's have a look. Press any key: ");
    continue_program();
    //StringOfChars input_2 = input_growable_string();
    print_str_skip_lines(&concatenated_string);
    //free(input_2.buffer);

    printf("\nAs you know, 64-bit operating systems can express numbers that are up to 8 bytes long. And since characters are actually numbers,"
    " let us choose 8 random characters from the concatenated string! Press any key: ");
    //StringOfChars input_3 = input_growable_string();
    //free(input_3.buffer);
    continue_program();

    srand(time(NULL));
    const size_t RAND_ARRAY_LEN = 8;
    uint8_t array_with_rand_values[RAND_ARRAY_LEN];
    for (size_t j = 0; j < RAND_ARRAY_LEN; ++j)
    {
        size_t random_value = get_random_val_in_string(&concatenated_string);
        array_with_rand_values[j] = concatenated_string.buffer[random_value];
        printf("Random value (INDEX POSITION): %d | CHAR: %c - HEX: %x - DECIMAL: %u\n", random_value, array_with_rand_values[j], array_with_rand_values[j], array_with_rand_values[j]);
    }

    // Let's see what those values are:
    
    printf("\nWe can also transform this new array of characters into a 64-bit number of its own by concatenating these characters with the help of the "
    "'concat_elements_in_array_of_chars' function in our little library inside the 'array_char_functions.h' header file!\n");
    printf("Press any key: ");
    //StringOfChars input_4 = input_growable_string();
    //free(input_4.buffer);
    continue_program();

    uint64_t resulting_64bit_num = concat_elements_in_array_of_chars(array_with_rand_values, RAND_ARRAY_LEN, false);
    printf("\nA proof that this operation indeed worked is the fact that we can print the resulting 64-bit number for this operation"
    " by using the llu and llx format specifiers for printing very large numbers in C!\n");
    printf("Like so -> In HEX: %llx | In DECIMAL: %llu\n", resulting_64bit_num, resulting_64bit_num);

    printf("\nIf you notice, though, this number was the result of the concatenation of all of these characters in big endian format, where the most significant"
    " byte is stored first, and the least significant byte is stored last.\nThat is not how numbers are actually stored in memory in x86 processors, which are the"
    " processors most of our computers use. Thankfully, our 'concat_elements_in_array_of_chars' function gives us the option concatenate our characters in little"
    " endian format (which corresponds to the architecture of the x86 Intel-based processors)!\n");
    printf("Press any key: ");
    //StringOfChars input_5 = input_growable_string();
    //free(input_5.buffer);
    continue_program();

    uint64_t resulting_64bit_little_endian = concat_elements_in_array_of_chars(array_with_rand_values, RAND_ARRAY_LEN, true);
    printf("Here's our 64-bit number in little endian format -> In HEX: %llx | In DECIMAL: %llu\n", resulting_64bit_little_endian, resulting_64bit_little_endian);

    printf("However, we may also want to do the contrary, that is, get a 64-bit number and transform that into an array of chars by separating its bytes!\n");
    printf("So let's get the address of the first value inside our concatenated string and use that!\n");
    printf("Press any key: ");
    //StringOfChars input_6 = input_growable_string();
    //free(input_6.buffer);
    continue_program();

    uint64_t address_first_char = (uint64_t)&concatenated_string.buffer[0];
    printf("Here's the address of the first character: %llx - %llu", address_first_char, address_first_char);

    size_t amount_bytes_64bit_nums = 8;
    uint8_t * array_chars_address = transform_uinteger_into_array_chars(address_first_char, 8, false);
    printf("\nAnd here's the resulting null-terminated array in big endian format (notice that we can even iterate through it, char by char!):\n");
    print_array_chars_skip_line(array_chars_address, amount_bytes_64bit_nums);
    printf("Press any key: ");
    continue_program();

    uint8_t * array_chars_little_endian = transform_uinteger_into_array_chars(address_first_char, amount_bytes_64bit_nums, true);
    printf("This was in big endian format, though! Here's what it looks like in little endian format:\n");
    print_array_chars_skip_line(array_chars_little_endian, amount_bytes_64bit_nums);
    printf("\n(Notice how these characters don't necessarily have a valid ASCII representation in human-readable letters!)");

    //printf("Press any key: ");
    //continue_program();
    printf("\n================ This is the end of our program! Thank you for checking it out! ================\n");
    printf("Press any key to end it: ");
    continue_program();

    free(array_chars_address);
    free(array_chars_little_endian);
    free(concatenated_string.buffer);
    free_strings_in_vector(buffer_strings, amount_strings);
    return 0;
}