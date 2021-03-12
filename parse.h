#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H
#include <string.h>
namespace parse {
 class Parse {
 public:
	static int isspace(char c)
	{
		return strchr(" \t\n\v\f\r", c) != 0;
	}

	static int isdigit(char c)
	{
	return c >= '0' && c <= '9';
	}

	static int IsCoordinate(const char* s)
	{
		// optional sign
		if (*s == '-' || *s == '+')
		s++;
		// must have at least one digit, or start by a dot
		return (isdigit(*s) || *s == '.');
	}

	static const char* ParseNumber(const char* s, char* it, const int size)
	{
		const int last = size - 1;
		int i = 0;

		// sign
		if (*s == '-' || *s == '+') {
			if (i < last) it[i++] = *s;
			s++;
		}
		// integer part
		while (*s && isdigit(*s)) {
			if (i < last) it[i++] = *s;
			s++;
		}
		if (*s == '.') {
			// decimal point
			if (i < last) it[i++] = *s;
			s++;
			// fraction part
			while (*s && isdigit(*s)) {
				if (i < last) it[i++] = *s;
				s++;
			}
		}
		// exponent
		if ((*s == 'e' || *s == 'E') && (s[1] != 'm' && s[1] != 'x')) {
			if (i < last) it[i++] = *s;
			s++;
			if (*s == '-' || *s == '+') {
				if (i < last) it[i++] = *s;
				s++;
			}
			while (*s && isdigit(*s)) {
				if (i < last) it[i++] = *s;
				s++;
			}
		}
		it[i] = '\0';

		return s;
	}

	static const char* GetNextPathItem(const char* s, char* it)
	{
		it[0] = '\0';
		// Skip white spaces and commas
		while (*s && (isspace(*s) || *s == ',')) 
			s++;
		if (!*s) 
			return s;
		if (*s == '-' || *s == '+' || *s == '.' || isdigit(*s)) {
			s = ParseNumber(s, it, 64);
		}
		else {
			// Parse command
			it[0] = *s++;
			it[1] = '\0';
			return s;
		}

		return s;
	}

  };
}
#endif