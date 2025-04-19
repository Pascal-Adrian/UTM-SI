#ifndef NOISE_FILTER_H
#define NOISE_FILTER_H

float process_median_filter(float input_value, float *history, int filter_length);
float process_weighted_average(float input_value, float *history, const float *coefficients, int filter_length);
float apply_limits(float value, float lower_bound, float upper_bound);

#endif