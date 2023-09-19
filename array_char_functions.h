#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

size_t calc_arraychars_length(uint8_t * chars_buffer)
{
    size_t i = 0;
    while (*(chars_buffer + i) != 0)
    {
        ++i;
    }
    size_t length = i;
    return length;
}

size_t n_to_the_power_of_k(size_t n, size_t k)
{
	size_t result = n;
	for (size_t i = 1; i < k; ++i)
	{
		result *= n;
	}
	
	return result;
}

int deep_copy_array_chars(uint8_t * p_array_chars_dest, uint8_t * p_array_chars_source, size_t len_source)
{
	uint8_t * temporary = (uint8_t *)malloc((len_source + 1) * sizeof(uint8_t));
	if (temporary == NULL)
	{
		return -1;
	}

	size_t i = 0;
	while (i < len_source)
	{
        temporary[i] = p_array_chars_source[i];
		++i;
	}
	
	//p_array_chars_dest[i] = '\0';
    temporary[i] = '\0';
    p_array_chars_dest = temporary;
	
	return 0;
}

uint8_t * transfer_array_chars(uint8_t * p_array_chars_source, size_t len_source)
{
    uint8_t * array_chars_to_return = (uint8_t *)malloc((len_source + 1) * sizeof(uint8_t));

	size_t i = 0;
	while (i < len_source)
	{
        array_chars_to_return[i] = p_array_chars_source[i];
		++i;
	}
    array_chars_to_return[i] = '\0';

    return array_chars_to_return;
}

uint8_t * transfer_array_chars_resize(uint8_t * p_array_chars_source, size_t len_source, size_t amount_bytes)
{
    uint8_t * array_chars_to_return = (uint8_t *)malloc(amount_bytes);

	size_t i = 0;
	while (i < len_source)
	{
        array_chars_to_return[i] = p_array_chars_source[i];
		++i;
	}
	
	//p_array_chars_dest[i] = '\0';
    array_chars_to_return[i] = '\0';

    return array_chars_to_return;
}

uint64_t concat_elements_in_array_of_chars(uint8_t * array_param, size_t length, bool do_concatenate_in_little_endian)
{
    uint64_t result = 0;
    uint64_t result_to_return = 0;
    uint64_t val_256_in_hex = 0x100;

    if (do_concatenate_in_little_endian)
    {
        for (uint64_t i = length; i > 0; --i)
        {
            uint64_t power_of_256 = 0;
            uint8_t array_param_i_converted = (uint8_t)array_param[i - 1];

            if ((i - 1) == 0)
            {
                power_of_256 = 1;
            } else
            {
                power_of_256 = n_to_the_power_of_k(val_256_in_hex, (i - 1));
            }
            
            result = (uint64_t)array_param_i_converted * power_of_256;

            result_to_return += result;
        }
    } else
    {
        uint64_t temp_k = length - 1;
        for (uint64_t i = 0; i < length; ++i)
        {
            uint64_t power_of_256 = 0;
            uint8_t array_param_i_converted = (uint8_t)array_param[i];
            if (i == (length - 1))
            {
                power_of_256 = 1;
            } else
            {
                power_of_256 = n_to_the_power_of_k(val_256_in_hex, temp_k);
            }

            temp_k -= 1;
            result = (uint64_t)array_param_i_converted * power_of_256;
            result_to_return += result;
        }
    }
    return result_to_return;
}

int push_char_into_char_array(uint8_t * p_array_param, uint8_t char_to_push, size_t new_amount_of_bytes, size_t index)
{
    p_array_param = (uint8_t *)realloc(p_array_param, new_amount_of_bytes);
    if (p_array_param == NULL)
        return -1;

    p_array_param[index] = char_to_push;
    p_array_param[new_amount_of_bytes - 1] = 0;

    return 0;
}

uint8_t * transform_uinteger_into_array_chars(uint64_t integer_value, uint64_t len_return_array, bool make_array_little_endian)
{
    size_t amount_bytes_return_array = 1;
    uint8_t * p_array_to_return = (uint8_t *)malloc(amount_bytes_return_array * sizeof(uint8_t));
    uint64_t val_256_in_hex = 0x100;

    for (size_t i = (len_return_array - 1); i >= 0; --i)
    {
        uint64_t power_of_256 = 0;
        uint64_t temp_int_val = integer_value;

        if (i == 1)
        {
            power_of_256 = val_256_in_hex;
        } else if (i == 0)
        {
            power_of_256 = 1;
        } else
        {
            power_of_256 = n_to_the_power_of_k(val_256_in_hex, i);
        }

        temp_int_val /= power_of_256;

        ++amount_bytes_return_array;
        size_t index = amount_bytes_return_array - 2;
        uint8_t char_temp_int_val = (uint8_t)temp_int_val;
        push_char_into_char_array(p_array_to_return, char_temp_int_val, amount_bytes_return_array, index);
        uint64_t temp_temp_int_val = temp_int_val;

        temp_int_val *= power_of_256;
        if (temp_temp_int_val > 0)
            integer_value -= temp_int_val;

        if (i == 0)
            break;
    }

    if (make_array_little_endian)
    {
        size_t index_end_of_the_array = len_return_array - 1;
        for (size_t i = 0; i < len_return_array;)
        {
            uint8_t temp = p_array_to_return[i];
            p_array_to_return[i] = p_array_to_return[index_end_of_the_array];
            p_array_to_return[index_end_of_the_array] = temp;
            --index_end_of_the_array;
            ++i;
            if (i >= index_end_of_the_array)
                break;
        }
    }

    p_array_to_return[len_return_array] = '\0';

    return p_array_to_return;
}

void print_array_chars_skip_line(uint8_t * array_param, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("CHAR: %c - HEX: %x - DECIMAL: %d\n", *(array_param + i), *(array_param + i), *(array_param + i));
    }
}
