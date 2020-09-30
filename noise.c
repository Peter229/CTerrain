#define FNL_IMPL
#include "noise.h"

void noise_gen_height_map(struct Noise* in_noise, int seed) {

	in_noise->noise = fnlCreateState(seed);
	in_noise->noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
}