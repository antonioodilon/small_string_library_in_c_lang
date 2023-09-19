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

    string_to_return.buffer = (uint8_t*)malloc(space_for_null_char * sizeof(uint8_t));
    string_to_return.length = 0;
    string_to_return.capacity = 10;

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
	StringOfChars string_to_return;
	string_to_return.buffer = NULL;
	
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
	
	while (input_char != '\n')
	{
		if (buffer_index >= more_characters)
		{
			more_characters += 10;
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
	uint8_t * temp_array_chars = transfer_array_chars(str_dest->buffer, str_dest_new_len);
	
	size_t index_null_char_str_dest = str_dest->length;
	size_t i = 0;
	for (index_null_char_str_dest; index_null_char_str_dest < str_dest_new_len; ++index_null_char_str_dest)
	{
		temp_array_chars[index_null_char_str_dest] = *(str_source->buffer + i);
		++i;
	}

    temp_array_chars[index_null_char_str_dest] = '\0';
	if (str_dest->buffer == NULL)
		return 0;
	
	uint8_t * temp_buffer = transfer_array_chars(temp_array_chars, str_dest_new_len);
    str_dest->length = str_dest_new_len;
	str_dest->buffer = temp_buffer;

    if (str_dest->length >= str_dest->capacity)
    {
        str_dest->capacity = str_dest->length + 10;
    }
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
