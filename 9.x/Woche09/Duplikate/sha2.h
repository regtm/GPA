#pragma once

/*
a very simple data type that holds SHA-256 hashes
plus two functions to compute them from strings and files
*/

#include <stdint.h>
#include <string>
#include <ostream>

struct sha256
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
};

sha256 sha256_from_string(const std::string& str);
sha256 sha256_from_file(const std::string& filename);

std::ostream& operator<<(std::ostream& lhs, const sha256& rhs);

bool operator==(const sha256& lhs, const sha256& rhs);
bool operator<(const sha256& lhs, const sha256& rhs);
