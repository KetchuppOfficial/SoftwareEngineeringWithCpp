#ifndef INCLUDE_HASH_HPP
#define INCLUDE_HASH_HPP

#include <climits>
#include <string_view>
#include <utility>

namespace dts {

class Hash final {
  public:
    enum class Algo { kRS, kJS, kPJW, kELF, kBKDR, kSDBM, kDJB, kDEK, kAP };

    static unsigned operator()(std::string_view input, Algo algo) {
        switch (algo) {
        case Algo::kRS:
            return RSHash(input.data(), input.size());
        case Algo::kJS:
            return JSHash(input.data(), input.size());
        case Algo::kPJW:
            return PJWHash(input.data(), input.size());
        case Algo::kELF:
            return ELFHash(input.data(), input.size());
        case Algo::kBKDR:
            return BKDRHash(input.data(), input.size());
        case Algo::kSDBM:
            return SDBMHash(input.data(), input.size());
        case Algo::kDJB:
            return DJBHash(input.data(), input.size());
        case Algo::kDEK:
            return DEKHash(input.data(), input.size());
        case Algo::kAP:
            return APHash(input.data(), input.size());
        default:
            std::unreachable();
        }
    }

    static std::string_view to_string_view(Algo algo) {
        using namespace std::string_view_literals;
        switch (algo) {
        case Algo::kRS:
            return "RS"sv;
        case Algo::kJS:
            return "JS"sv;
        case Algo::kPJW:
            return "PJW"sv;
        case Algo::kELF:
            return "ELF"sv;
        case Algo::kBKDR:
            return "BKDR"sv;
        case Algo::kSDBM:
            return "SDBM"sv;
        case Algo::kDJB:
            return "DJB"sv;
        case Algo::kDEK:
            return "DEK"sv;
        case Algo::kAP:
            return "AP"sv;
        default:
            std::unreachable();
        }
    }

  private:
    static unsigned RSHash(const char *str, unsigned length) {
        constexpr unsigned kB = 378551u;

        unsigned hash = 0u;
        for (auto i = 0u, a = 63689u; i < length; ++str, ++i) {
            hash = hash * a + *str;
            a *= kB;
        }
        return hash;
    }

    static unsigned JSHash(const char *str, unsigned length) {
        unsigned hash = 1315423911;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash ^= ((hash << 5) + *str + (hash >> 2));
        }
        return hash;
    }

    static unsigned PJWHash(const char *str, unsigned length) {
        constexpr unsigned kBitsInUnsignedInt = sizeof(unsigned) * CHAR_BIT;
        constexpr unsigned kThreeQuarters = (kBitsInUnsignedInt * 3u) / 4u;
        constexpr unsigned kOneEighth = kBitsInUnsignedInt / 8u;
        constexpr unsigned kHighBits = ~0u << (kBitsInUnsignedInt - kOneEighth);

        unsigned hash = 0;
        for (auto i = 0u, test = 0u; i < length; ++str, ++i) {
            hash = (hash << kOneEighth) + *str;

            if ((test = hash & kHighBits) != 0) {
                hash = ((hash ^ (test >> kThreeQuarters)) & (~kHighBits));
            }
        }
        return hash;
    }

    static unsigned ELFHash(const char *str, unsigned length) {
        unsigned int hash = 0;
        for (auto i = 0u, x = 0u; i < length; ++str, ++i) {
            hash = (hash << 4) + *str;

            if ((x = hash & 0xF0000000L) != 0) {
                hash ^= (x >> 24);
            }

            hash &= ~x;
        }
        return hash;
    }

    static unsigned BKDRHash(const char *str, unsigned length) {
        constexpr unsigned kSeed = 131; /* 31 131 1313 13131 131313 etc.. */

        unsigned hash = 0;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash = (hash * kSeed) + *str;
        }
        return hash;
    }

    static unsigned SDBMHash(const char *str, unsigned length) {
        unsigned hash = 0;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash = *str + (hash << 6) + (hash << 16) - hash;
        }
        return hash;
    }

    static unsigned DJBHash(const char *str, unsigned length) {
        unsigned hash = 5381;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash = ((hash << 5) + hash) + *str;
        }
        return hash;
    }

    static unsigned DEKHash(const char *str, unsigned length) {
        unsigned hash = length;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash = ((hash << 5) ^ (hash >> 27)) ^ *str;
        }
        return hash;
    }

    static unsigned APHash(const char *str, unsigned length) {
        unsigned hash = 0xAAAAAAAA;
        for (auto i = 0u; i < length; ++str, ++i) {
            hash ^= ((i & 1) == 0) ? ((hash << 7) ^ *str * (hash >> 3))
                                   : (~((hash << 11) + (*str ^ (hash >> 5))));
        }
        return hash;
    }
};

} // namespace dts

#endif // INCLUDE_HASH_HPP
