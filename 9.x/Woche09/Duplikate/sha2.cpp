#include "sha2.h"
#include <fstream>
#include <sstream>

const sha256 prime_square_root_fractionals = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

const uint32_t prime_cube_root_fractionals[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t ror(uint32_t x, uint32_t n)
{
	return (x >> n) | (x << (32 - n));
}

uint32_t byteswap(uint32_t x)
{
	return x << 24 | (x & 0xff00) << 8 | (x >> 8) & 0xff00 | x >> 24;
}

void convert_endianness(uint32_t w[16])
{
	for (int i = 0; i != 16; ++i)
	{
		w[i] = byteswap(w[i]);
	}
}

void extend(uint32_t w[64])
{
	for (int i = 16; i != 64; ++i)
	{
		uint32_t s0 = ror(w[i-15], 7) ^ ror(w[i-15], 18) ^ (w[i-15] >> 3);
		uint32_t s1 = ror(w[i-2], 17) ^ ror(w[i-2], 19) ^ (w[i-2] >> 10);
		w[i] = w[i-16] + s0 + w[i-7] + s1;
	}
}

void shift(sha256& h, uint32_t temp1, uint32_t temp2)
{
	h.h = h.g;
	h.g = h.f;
	h.f = h.e;
	h.e = h.d + temp1;
	h.d = h.c;
	h.c = h.b;
	h.b = h.a;
	h.a = temp1 + temp2;
}

void add(sha256& lhs, const sha256& rhs)
{
	lhs.a += rhs.a;
	lhs.b += rhs.b;
	lhs.c += rhs.c;
	lhs.d += rhs.d;
	lhs.e += rhs.e;
	lhs.f += rhs.f;
	lhs.g += rhs.g;
	lhs.h += rhs.h;
}

void process(sha256& hash, uint32_t w[64])
{
	sha256 h = hash;
	for (int i = 0; i != 64; ++i)
	{
		uint32_t s1 = ror(h.e, 6) ^ ror(h.e, 11) ^ ror(h.e, 25);
		uint32_t ch = (h.e & h.f) ^ (~h.e & h.g);

		uint32_t s0 = ror(h.a, 2) ^ ror(h.a, 13) ^ ror(h.a, 22);
		uint32_t maj = (h.a & h.b) ^ (h.a & h.c) ^ (h.b & h.c);

		shift(h, h.h + s1 + ch + prime_cube_root_fractionals[i] + w[i], s0 + maj);
	}
	add(hash, h);
}

void sha256_round(sha256& hash, uint32_t w[16])
{
	convert_endianness(w);
	extend(w);
	process(hash, w);
}

void encode_big_endian(uint64_t x, uint8_t buffer[8])
{
	buffer[0] = (x >> 56)      ;
	buffer[1] = (x >> 48) & 255;
	buffer[2] = (x >> 40) & 255;
	buffer[3] = (x >> 32) & 255;
	buffer[4] = (x >> 24) & 255;
	buffer[5] = (x >> 16) & 255;
	buffer[6] = (x >>  8) & 255;
	buffer[7] = (x      ) & 255;
}

sha256 sha256_from_istream(std::istream& is)
{
	sha256 hash = prime_square_root_fractionals;
	union {
		uint8_t buffer[64];
		uint32_t w[64];
	};
	uint64_t size_in_bits = 0;

	// process full chunks
	while (is.read(reinterpret_cast<char*>(buffer), sizeof buffer))
	{
		size_in_bits += 8 * sizeof buffer;
		sha256_round(hash, w);
	}

	// append 1 bit
	auto rest_in_bytes = is.gcount();
	std::fill(buffer + rest_in_bytes, std::end(buffer), 0);
	buffer[rest_in_bytes] = 0x80;

	// ensure enough room for encoded size
	if (rest_in_bytes + 1 + 8 > sizeof buffer)
	{
		sha256_round(hash, w);
		std::fill(buffer, std::end(buffer), 0);
	}

	// encode size
	encode_big_endian(size_in_bits + 8 * rest_in_bytes, std::end(buffer) - 8);
	sha256_round(hash, w);

	return hash;
}

sha256 sha256_from_string(const std::string& str)
{
	std::istringstream is(str);
	return sha256_from_istream(is);
}

sha256 sha256_from_file(const std::string& filename)
{
	std::ifstream is(filename, std::ios::binary);
	return sha256_from_istream(is);
}

struct hex_t
{
	uint32_t x;
};

hex_t hex(int x)
{
	hex_t h = {x};
	return h;
}

const char H[] = "0123456789ABCDEF";

std::ostream& operator<<(std::ostream& os, hex_t h)
{
	char buf[8];
	buf[0] = H[(h.x >> 28)     ];
	buf[1] = H[(h.x >> 24) & 15];
	buf[2] = H[(h.x >> 20) & 15];
	buf[3] = H[(h.x >> 16) & 15];
	buf[4] = H[(h.x >> 12) & 15];
	buf[5] = H[(h.x >>  8) & 15];
	buf[6] = H[(h.x >>  4) & 15];
	buf[7] = H[(h.x      ) & 15];
	os.write(buf, 8);
	return os;
}

std::ostream& operator<<(std::ostream& lhs, const sha256& rhs)
{
	lhs << hex(rhs.a) << hex(rhs.b) << hex(rhs.c) << hex(rhs.d) << hex(rhs.e) << hex(rhs.f) << hex(rhs.g) << hex(rhs.h);
	return lhs;
}

bool operator==(const sha256& lhs, const sha256& rhs)
{
	return (lhs.a == rhs.a)
		&& (lhs.b == rhs.b)
		&& (lhs.c == rhs.c)
		&& (lhs.d == rhs.d)
		&& (lhs.e == rhs.e)
		&& (lhs.f == rhs.f)
		&& (lhs.g == rhs.g)
		&& (lhs.h == rhs.h);
}

bool operator<(const sha256& lhs, const sha256& rhs)
{
	if (lhs.a < rhs.a) return true;
	if (rhs.a < lhs.a) return false;

	if (lhs.b < rhs.b) return true;
	if (rhs.b < lhs.b) return false;

	if (lhs.c < rhs.c) return true;
	if (rhs.c < lhs.c) return false;

	if (lhs.d < rhs.d) return true;
	if (rhs.d < lhs.d) return false;

	if (lhs.e < rhs.e) return true;
	if (rhs.e < lhs.e) return false;

	if (lhs.f < rhs.f) return true;
	if (rhs.f < lhs.f) return false;

	if (lhs.g < rhs.g) return true;
	if (rhs.g < lhs.g) return false;

	return (lhs.h < rhs.h);
}
