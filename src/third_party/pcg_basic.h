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
 *     http://www.pcg-random.org
 */

/*
 * This code is derived from the full C implementation, which is in turn
 * derived from the canonical C++ PCG implementation. The C++ version
 * has many additional features and is preferable if you can use C++ in
 * your project.
 */

#ifndef PCG_BASIC_H_INCLUDED
#define PCG_BASIC_H_INCLUDED 1

#include <inttypes.h>

/**
 * @struct pcg_state_setseq_64
 * @brief PCG state, internals are private.
 */
struct pcg_state_setseq_64 {
    /** RNG state. All values are possible. */
    uint64_t state;
    /** Controls which RNG sequence (stream) is selected. Must be ALWAYS be odd. */
    uint64_t inc;
};
/**
 * @typedef pcg32_random_t
 * @brief Type defination of pcg_state_setseq_64.
 */
typedef struct pcg_state_setseq_64 pcg32_random_t;

/// If you *must* statically initialize it, here's one.
#define PCG32_INITIALIZER   { 0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL }

/**
 * @brief Seed the default RNG.
 *
 * Initializes the internal RNG state using the given seed and sequence (stream ID).
 *
 * @param initstate The initial state value for the RNG.
 * @param initseq The stream selector (must be odd internally; allows multiple independent streams).
 */
void pcg32_srandom(uint64_t initstate, uint64_t initseq);

/**
 * @brief Seed a specific RNG instance (reentrant).
 *
 * Initializes a user-provided RNG state with the given seed and stream selector.
 *
 * @param rng Pointer to a pcg32_random_t instance to initialize.
 * @param initstate The initial state value for the RNG.
 * @param initseq The stream selector (must be odd internally).
 */
void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq);

/**
 * @brief Generate a random 32-bit number from the default RNG.
 *
 * @return A uniformly distributed 32-bit unsigned integer.
 */
uint32_t pcg32_random(void);

/**
 * @brief Generate a random 32-bit number from a specific RNG instance.
 *
 * @param rng Pointer to the RNG state.
 * @return A uniformly distributed 32-bit unsigned integer.
 */
uint32_t pcg32_random_r(pcg32_random_t* rng);

/**
 * @brief Generate a bounded random number from the default RNG.
 *
 * @param bound The upper bound (exclusive). The result will be in the range [0, bound).
 * @return A uniformly distributed random integer less than bound.
 */
uint32_t pcg32_boundedrand(uint32_t bound);

/**
 * @brief Generate a bounded random number from a specific RNG instance.
 *
 * @param rng Pointer to the RNG state.
 * @param bound The upper bound (exclusive). The result will be in the range [0, bound).
 * @return A uniformly distributed random integer less than bound.
 */
uint32_t pcg32_boundedrand_r(pcg32_random_t* rng, uint32_t bound);


#endif // PCG_BASIC_H_INCLUDED