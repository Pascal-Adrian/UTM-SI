#include <Arduino.h>
#include <string.h>
#include "NoiseFilter.h"

/**
 * Salt and Pepper filter (median filter)
 * Removes impulsive noise by taking the median value from a window
 */
float process_median_filter(float input_value, float *history, int filter_length)
{
    float temp_array[filter_length];

    // Shift values in history buffer
    for (int idx = 0; idx < filter_length - 1; idx++)
    {
        history[idx] = history[idx + 1];
    }
    history[filter_length - 1] = input_value;

    // Copy values to sorting array
    memcpy(temp_array, history, sizeof(float) * filter_length);

    // Perform simple bubble sort (sufficient for small arrays)
    for (int outer = 0; outer < filter_length - 1; outer++)
    {
        for (int inner = 0; inner < filter_length - outer - 1; inner++)
        {
            if (temp_array[inner] > temp_array[inner + 1])
            {
                float swap = temp_array[inner];
                temp_array[inner] = temp_array[inner + 1];
                temp_array[inner + 1] = swap;
            }
        }
    }

    // Return median value
    return temp_array[filter_length / 2];
}

/**
 * Weighted Average filter
 * Applies weighted average to smooth the signal
 */
float process_weighted_average(float input_value, float *history, const float *coefficients, int filter_length)
{
    // Shift values in history buffer
    for (int idx = 0; idx < filter_length - 1; idx++)
    {
        history[idx] = history[idx + 1];
    }
    history[filter_length - 1] = input_value;

    // Apply weighted average
    float result = 0.0;
    for (int idx = 0; idx < filter_length; idx++)
    {
        result += history[idx] * coefficients[idx];
    }

    return result;
}

/**
 * Apply saturation to ensure value is within valid range
 */
float apply_limits(float value, float lower_bound, float upper_bound)
{
    if (value < lower_bound)
    {
        return lower_bound;
    }
    else if (value > upper_bound)
    {
        return upper_bound;
    }
    else
    {
        return value;
    }
}