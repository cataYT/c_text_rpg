/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *       http://www.pcg-random.org
 */

/*
 * This code is derived from the full C implementation, which is in turn
 * derived from the canonical C++ PCG implementation. The C++ version
 * has many additional features and is preferable if you can use C++ in
 * your project.
 */

#include "pcg_basic.h"

/// state for global RNGs
static pcg32_random_t pcg32_global = PCG32_INITIALIZER;

/// Seed the rng.  Specified in two parts, state initializer and a sequence selection constant (a.k.a. stream id)
void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq)
{
    // Start with a known, fixed state (zero) before applying the seed.
    // Important to ensure deterministic behaviour when seeding.
    rng->state = 0U;
    // Multiplies sequence by 2 and OR it to ensure its odd
    rng->inc = (initseq << 1u) | 1u;
    // Advance the generator
    pcg32_random_r(rng);
    // Add user seed
    rng->state += initstate;
    // Advance again
    pcg32_random_r(rng);
}

void pcg32_srandom(uint64_t seed, uint64_t seq)
{
    pcg32_srandom_r(&pcg32_global, seed, seq);
}

/// Generate a uniformly distributed 32-bit random number
uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    // Need old state to generate output.
    uint64_t oldstate = rng->state;
    // Standard LCG formula, magic value is carefully chosen to ensure randomness.
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    // Mix the bits of old state, reduces the 64-bit state down to 32 bits with good distribution.
    uint32_t xorshifted = (uint32_t)((oldstate >> 18u) ^ oldstate) >> 27u;
    // Take the top 5 bits of oldstate to determine how much to rotate, gives value between 0 and 31.
    uint32_t rot = oldstate >> 59u;
    // bitwise rotate right, ensures full use of entropy and rotation amount varies dynamically, adding more randomness to the output.
    return (xorshifted >> rot) | (xorshifted << ((32 - rot) & 31));
}

uint32_t pcg32_random(void)
{
    return pcg32_random_r(&pcg32_global);
}

uint32_t pcg32_boundedrand_r(pcg32_random_t* rng, uint32_t bound)
{
    // To avoid bias, we need to make the range of the RNG a multiple of
    // bound, which we do by dropping output less than a threshold.
    // A naive scheme to calculate the threshold would be to do
    //
    //     uint32_t threshold = 0x100000000ull % bound;
    //
    // but 64-bit div/mod is slower than 32-bit div/mod (especially on
    // 32-bit platforms).  In essence, we do
    //
    //     uint32_t threshold = (0x100000000ull-bound) % bound;
    //
    // because this version will calculate the same modulus, but the LHS
    // value is less than 2^32.

    uint32_t threshold = (0u - bound) % bound;

    // Uniformity guarantees that this loop will terminate.  In practice, it
    // should usually terminate quickly; on average (assuming all bounds are
    // equally likely), 82.25% of the time, we can expect it to require just
    // one iteration.  In the worst case, someone passes a bound of 2^31 + 1
    // (i.e., 2147483649), which invalidates almost 50% of the range.  In 
    // practice, bounds are typically small and only a tiny amount of the range
    // is eliminated.
    for (;;) {
        uint32_t r = pcg32_random_r(rng);
        if (r >= threshold) {
            return r % bound;
        }
    }
}

uint32_t pcg32_boundedrand(uint32_t bound)
{
    return pcg32_boundedrand_r(&pcg32_global, bound);
}