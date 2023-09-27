#ifndef LR3_RABIN_HPP
#define LR3_RABIN_HPP

#include <cmath>
#include <utility>
#include <array>


using BigNumber = unsigned long long;

const std::array<const BigNumber, 70> kFirstPrimes{
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103,
        107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223,
        227, 229, 233, 239, 241, 251, 257,
        263, 269, 271, 277, 281, 283, 293,
        307, 311, 313, 317, 331, 337, 347, 349
};

BigNumber random(const BigNumber n)
{
    const auto max{(BigNumber) powl(2, n) - 1};
    const auto min{(BigNumber) powl(2, n - 1) + 1};
    return min + (rand() % (max - min + 1));
}

BigNumber get_low_level_prime(const BigNumber n)
{
    while (true)
    {
        const unsigned long long prime_candidate {random(n)};

        for (const BigNumber divisor : kFirstPrimes)
        {
            if (prime_candidate % divisor == 0 && powl(divisor, 2) <= prime_candidate)
                break;
            else
                return prime_candidate;
        }
    }
}


std::pair<BigNumber, BigNumber> generate_rabin_key();


#endif //LR3_RABIN_HPP
