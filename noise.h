#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "FastNoiseLite.h"

struct Noise {

	fnl_state noise;
};

void noise_gen_height_map(struct Noise* in_noise, int seed);