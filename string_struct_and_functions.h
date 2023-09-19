#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "array_char_functions.h"

// Code a growable string struct
typedef struct
{
    uint8_t * buffer;
    size_t length;
    size_t capacity;
} StringOfChars;

StringOfChars construct_string(void)
{
    StringOfChars string_to_return;
	string_to_return.buffer = NULL;
    uint8_t space_for_null_char = 1;

    string_to_return.buffer = (uint8_t*)malloc(space_for_null_char * sizeof(uint8_t)); // 1 is just enough space for the '\0' character
    // As more elements are added to the string, more space is allocated
    string_to_return.length = 0; // Equals to zero because the '\0' character doesn't count as part of its length
    string_to_return.capacity = 10; // If the length equals the capacity, the capacity will increase by 10

    return string_to_return;
}

int initialize_string(StringOfChars * p_string_destination, uint8_t * p_array_of_chars_param, size_t len_array_chars_param)
{
    if (p_string_destination->buffer == NULL)
    {
        return -1;
    }

	deep_copy_array_chars(p_string_destination->buffer, p_array_of_chars_param, len_array_chars_param);
	p_string_destination->length = len_array_chars_param;

    if (p_string_destination->length >= p_string_destination->capacity)
    {
        p_string_destination->capacity = p_string_destination->length + 10;
    }

    return 0;
}

StringOfChars new_string(uint8_t * p_array_of_chars_param, size_t len_array_chars_param)
{
	//StringOfChars string_to_return = construct_string();
	//initialize_string(&string_to_return, p_array_of_chars_param, len_array_chars_param);
	StringOfChars string_to_return;
	string_to_return.buffer = NULL;

	/*if (p_string_destination->buffer == NULL)
    {
        return -1;
    }*/

	//deep_copy_array_chars(string_to_return.buffer, p_array_of_chars_param, len_array_chars_param);
	string_to_return.buffer = transfer_array_chars(p_array_of_chars_param, len_array_chars_param);
	string_to_return.length = len_array_chars_param;

    if (string_to_return.length >= string_to_return.capacity)
    {
        string_to_return.capacity = string_to_return.length + 10;
    }

	return string_to_return;
}

StringOfChars input_growable_string(void)
{
	size_t more_characters = 10;
	uint8_t input_char = ' ';
	uint8_t * buffer = (uint8_t*)malloc(more_characters * sizeof(uint8_t));
	size_t buffer_index = 0;
	//const size_t MAX_CHARACTERS = 20;
	// Bug to fix: 25 or more characters causes a "double free detected in tcache 2" error
	// See: https://www.positioniseverything.net/double-free-detected-in-tcache-2/

	while (input_char != '\n')
	{
		/*if (buffer_index >= MAX_CHARACTERS)
		{
			break;
		}*/

		if (buffer_index >= more_characters)
		{
			more_characters += 10;
			//buffer = (uint8_t*)realloc(buffer, more_characters * sizeof(uint8_t));
			uint8_t * temp_buffer = transfer_array_chars_resize(buffer, buffer_index, (more_characters * sizeof(uint8_t)));
			buffer = temp_buffer;
		}

		input_char = getc(stdin);
		if (input_char == '\n' && buffer_index == 0)
		{
			input_char = ' ';
			continue;
		} else
		{
			buffer[buffer_index] = input_char;
			++buffer_index;
		}
	}
	buffer[buffer_index] = '\0';

	StringOfChars output_string = new_string(buffer, (buffer_index - 1));
	free(buffer);

	return output_string;
}

int concatenate_strings(StringOfChars * str_dest, StringOfChars * str_source)
{
	size_t str_dest_new_len = str_dest->length + str_source->length;
	
	//uint8_t * temp_array_chars = (uint8_t *)malloc((str_dest_new_len + 1) * sizeof(uint8_t));
	//deep_copy_array_chars(temp_array_chars, str_dest->buffer, str_dest_new_len);
	uint8_t * temp_array_chars = transfer_array_chars(str_dest->buffer, str_dest_new_len);
	
	size_t index_null_char_str_dest = str_dest->length;
	size_t i = 0;
	for (index_null_char_str_dest; index_null_char_str_dest < str_dest_new_len; ++index_null_char_str_dest)
	{
		temp_array_chars[index_null_char_str_dest] = *(str_source->buffer + i);
		//++str_source->buffer;
		++i;
	}

    temp_array_chars[index_null_char_str_dest] = '\0';
    //str_source->buffer -= str_source->length;

	//uint8_t * temp_buffer = (uint8_t*)malloc((str_dest_new_len + 1)*sizeof(uint8_t));
	//str_dest->buffer = temp_buffer;

	//str_dest->buffer = (uint8_t *)realloc(str_dest->buffer, (str_dest_new_len + 10)*sizeof(uint8_t)); // 1 for the '\0' character, as always
	
	if (str_dest->buffer == NULL)
		return 0;
	
	uint8_t * temp_buffer = transfer_array_chars(temp_array_chars, str_dest_new_len);
	//deep_copy_array_chars(temp_buffer, temp_array_chars, str_dest_new_len);
    str_dest->length = str_dest_new_len;
	str_dest->buffer = temp_buffer;
	//deep_copy_array_chars(str_dest->buffer, temp_array_chars, str_dest_new_len);

    if (str_dest->length >= str_dest->capacity)
    {
        str_dest->capacity = str_dest->length + 10;
    }

	//deep_copy_array_chars(str_dest->buffer, temp_array_chars, str_dest_new_len);
	//str_dest->buffer = temp_buffer;

	free(temp_array_chars);
	return 1;
}

size_t get_random_val_in_string(StringOfChars * str_param)
{
    size_t random_val;
    size_t maximum = str_param->length - 1;
    size_t minimum = 0;
    for (size_t i = 0; i < str_param->length; ++i)
    {
        random_val = (rand() % (maximum - minimum + 1)) + minimum;
    }

    return random_val;
}

void print_str_skip_lines(StringOfChars * p_string_param)
{
	size_t i = 0;
	while (i < p_string_param->length)
	{
		printf("INDEX POSITION: %d - CHAR: %c - HEX: %x - DECIMAL: %u\n", i, p_string_param->buffer[i], p_string_param->buffer[i], p_string_param->buffer[i]);
		++i;
	}
}