#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H
#include <string.h>
#include "define.h"
namespace parse {
	#define SVG_RGB(r, g, b) (((unsigned int)r) | ((unsigned int)g << 8) | ((unsigned int)b << 16))
	#define SVG_PI (3.14159265358979323846264338327f)
	struct SVGNamedColor {
		const char* name;
		unsigned int color;
	};
	//===
	static SVGNamedColor svg__colors[] = {
		{ "red", SVG_RGB(255, 0, 0) },
		{ "green", SVG_RGB(0, 128, 0) },
		{ "blue", SVG_RGB(0, 0, 255) },
		{ "yellow", SVG_RGB(255, 255, 0) },
		{ "cyan", SVG_RGB(0, 255, 255) },
		{ "magenta", SVG_RGB(255, 0, 255) },
		{ "black", SVG_RGB(0, 0, 0) },
		{ "grey", SVG_RGB(128, 128, 128) },
		{ "gray", SVG_RGB(128, 128, 128) },
		{ "white", SVG_RGB(255, 255, 255) },
		{ "aliceblue", SVG_RGB(240, 248, 255) },
		{ "antiquewhite", SVG_RGB(250, 235, 215) },
		{ "aqua", SVG_RGB(0, 255, 255) },
		{ "aquamarine", SVG_RGB(127, 255, 212) },
		{ "azure", SVG_RGB(240, 255, 255) },
		{ "beige", SVG_RGB(245, 245, 220) },
		{ "bisque", SVG_RGB(255, 228, 196) },
		{ "blanchedalmond", SVG_RGB(255, 235, 205) },
		{ "blueviolet", SVG_RGB(138, 43, 226) },
		{ "brown", SVG_RGB(165, 42, 42) },
		{ "burlywood", SVG_RGB(222, 184, 135) },
		{ "cadetblue", SVG_RGB(95, 158, 160) },
		{ "chartreuse", SVG_RGB(127, 255, 0) },
		{ "chocolate", SVG_RGB(210, 105, 30) },
		{ "coral", SVG_RGB(255, 127, 80) },
		{ "cornflowerblue", SVG_RGB(100, 149, 237) },
		{ "cornsilk", SVG_RGB(255, 248, 220) },
		{ "crimson", SVG_RGB(220, 20, 60) },
		{ "darkblue", SVG_RGB(0, 0, 139) },
		{ "darkcyan", SVG_RGB(0, 139, 139) },
		{ "darkgoldenrod", SVG_RGB(184, 134, 11) },
		{ "darkgray", SVG_RGB(169, 169, 169) },
		{ "darkgreen", SVG_RGB(0, 100, 0) },
		{ "darkgrey", SVG_RGB(169, 169, 169) },
		{ "darkkhaki", SVG_RGB(189, 183, 107) },
		{ "darkmagenta", SVG_RGB(139, 0, 139) },
		{ "darkolivegreen", SVG_RGB(85, 107, 47) },
		{ "darkorange", SVG_RGB(255, 140, 0) },
		{ "darkorchid", SVG_RGB(153, 50, 204) },
		{ "darkred", SVG_RGB(139, 0, 0) },
		{ "darksalmon", SVG_RGB(233, 150, 122) },
		{ "darkseagreen", SVG_RGB(143, 188, 143) },
		{ "darkslateblue", SVG_RGB(72, 61, 139) },
		{ "darkslategray", SVG_RGB(47, 79, 79) },
		{ "darkslategrey", SVG_RGB(47, 79, 79) },
		{ "darkturquoise", SVG_RGB(0, 206, 209) },
		{ "darkviolet", SVG_RGB(148, 0, 211) },
		{ "deeppink", SVG_RGB(255, 20, 147) },
		{ "deepskyblue", SVG_RGB(0, 191, 255) },
		{ "dimgray", SVG_RGB(105, 105, 105) },
		{ "dimgrey", SVG_RGB(105, 105, 105) },
		{ "dodgerblue", SVG_RGB(30, 144, 255) },
		{ "firebrick", SVG_RGB(178, 34, 34) },
		{ "floralwhite", SVG_RGB(255, 250, 240) },
		{ "forestgreen", SVG_RGB(34, 139, 34) },
		{ "fuchsia", SVG_RGB(255, 0, 255) },
		{ "gainsboro", SVG_RGB(220, 220, 220) },
		{ "ghostwhite", SVG_RGB(248, 248, 255) },
		{ "gold", SVG_RGB(255, 215, 0) },
		{ "goldenrod", SVG_RGB(218, 165, 32) },
		{ "greenyellow", SVG_RGB(173, 255, 47) },
		{ "honeydew", SVG_RGB(240, 255, 240) },
		{ "hotpink", SVG_RGB(255, 105, 180) },
		{ "indianred", SVG_RGB(205, 92, 92) },
		{ "indigo", SVG_RGB(75, 0, 130) },
		{ "ivory", SVG_RGB(255, 255, 240) },
		{ "khaki", SVG_RGB(240, 230, 140) },
		{ "lavender", SVG_RGB(230, 230, 250) },
		{ "lavenderblush", SVG_RGB(255, 240, 245) },
		{ "lawngreen", SVG_RGB(124, 252, 0) },
		{ "lemonchiffon", SVG_RGB(255, 250, 205) },
		{ "lightblue", SVG_RGB(173, 216, 230) },
		{ "lightcoral", SVG_RGB(240, 128, 128) },
		{ "lightcyan", SVG_RGB(224, 255, 255) },
		{ "lightgoldenrodyellow", SVG_RGB(250, 250, 210) },
		{ "lightgray", SVG_RGB(211, 211, 211) },
		{ "lightgreen", SVG_RGB(144, 238, 144) },
		{ "lightgrey", SVG_RGB(211, 211, 211) },
		{ "lightpink", SVG_RGB(255, 182, 193) },
		{ "lightsalmon", SVG_RGB(255, 160, 122) },
		{ "lightseagreen", SVG_RGB(32, 178, 170) },
		{ "lightskyblue", SVG_RGB(135, 206, 250) },
		{ "lightslategray", SVG_RGB(119, 136, 153) },
		{ "lightslategrey", SVG_RGB(119, 136, 153) },
		{ "lightsteelblue", SVG_RGB(176, 196, 222) },
		{ "lightyellow", SVG_RGB(255, 255, 224) },
		{ "lime", SVG_RGB(0, 255, 0) },
		{ "limegreen", SVG_RGB(50, 205, 50) },
		{ "linen", SVG_RGB(250, 240, 230) },
		{ "maroon", SVG_RGB(128, 0, 0) },
		{ "mediumaquamarine", SVG_RGB(102, 205, 170) },
		{ "mediumblue", SVG_RGB(0, 0, 205) },
		{ "mediumorchid", SVG_RGB(186, 85, 211) },
		{ "mediumpurple", SVG_RGB(147, 112, 219) },
		{ "mediumseagreen", SVG_RGB(60, 179, 113) },
		{ "mediumslateblue", SVG_RGB(123, 104, 238) },
		{ "mediumspringgreen", SVG_RGB(0, 250, 154) },
		{ "mediumturquoise", SVG_RGB(72, 209, 204) },
		{ "mediumvioletred", SVG_RGB(199, 21, 133) },
		{ "midnightblue", SVG_RGB(25, 25, 112) },
		{ "mintcream", SVG_RGB(245, 255, 250) },
		{ "mistyrose", SVG_RGB(255, 228, 225) },
		{ "moccasin", SVG_RGB(255, 228, 181) },
		{ "navajowhite", SVG_RGB(255, 222, 173) },
		{ "navy", SVG_RGB(0, 0, 128) },
		{ "oldlace", SVG_RGB(253, 245, 230) },
		{ "olive", SVG_RGB(128, 128, 0) },
		{ "olivedrab", SVG_RGB(107, 142, 35) },
		{ "orange", SVG_RGB(255, 165, 0) },
		{ "orangered", SVG_RGB(255, 69, 0) },
		{ "orchid", SVG_RGB(218, 112, 214) },
		{ "palegoldenrod", SVG_RGB(238, 232, 170) },
		{ "palegreen", SVG_RGB(152, 251, 152) },
		{ "paleturquoise", SVG_RGB(175, 238, 238) },
		{ "palevioletred", SVG_RGB(219, 112, 147) },
		{ "papayawhip", SVG_RGB(255, 239, 213) },
		{ "peachpuff", SVG_RGB(255, 218, 185) },
		{ "peru", SVG_RGB(205, 133, 63) },
		{ "pink", SVG_RGB(255, 192, 203) },
		{ "plum", SVG_RGB(221, 160, 221) },
		{ "powderblue", SVG_RGB(176, 224, 230) },
		{ "purple", SVG_RGB(128, 0, 128) },
		{ "rosybrown", SVG_RGB(188, 143, 143) },
		{ "royalblue", SVG_RGB(65, 105, 225) },
		{ "saddlebrown", SVG_RGB(139, 69, 19) },
		{ "salmon", SVG_RGB(250, 128, 114) },
		{ "sandybrown", SVG_RGB(244, 164, 96) },
		{ "seagreen", SVG_RGB(46, 139, 87) },
		{ "seashell", SVG_RGB(255, 245, 238) },
		{ "sienna", SVG_RGB(160, 82, 45) },
		{ "silver", SVG_RGB(192, 192, 192) },
		{ "skyblue", SVG_RGB(135, 206, 235) },
		{ "slateblue", SVG_RGB(106, 90, 205) },
		{ "slategray", SVG_RGB(112, 128, 144) },
		{ "slategrey", SVG_RGB(112, 128, 144) },
		{ "snow", SVG_RGB(255, 250, 250) },
		{ "springgreen", SVG_RGB(0, 255, 127) },
		{ "steelblue", SVG_RGB(70, 130, 180) },
		{ "tan", SVG_RGB(210, 180, 140) },
		{ "teal", SVG_RGB(0, 128, 128) },
		{ "thistle", SVG_RGB(216, 191, 216) },
		{ "tomato", SVG_RGB(255, 99, 71) },
		{ "turquoise", SVG_RGB(64, 224, 208) },
		{ "violet", SVG_RGB(238, 130, 238) },
		{ "wheat", SVG_RGB(245, 222, 179) },
		{ "whitesmoke", SVG_RGB(245, 245, 245) },
		{ "yellowgreen", SVG_RGB(154, 205, 50) },
	};

	inline int isspace(char c)
	{
		return strchr(" \t\n\v\f\r", c) != 0;
	}

	inline int isdigit(char c)
	{
		return c >= '0' && c <= '9';
	}
	inline int IsCoordinate(const char* s)
	{
		// optional sign
		if (*s == '-' || *s == '+')
		s++;
		// must have at least one digit, or start by a dot
		return (isdigit(*s) || *s == '.');
	}

	inline const char* ParseNumber(const char* s, char* it, const int size)
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

	inline const char* GetNextPathItem(const char* s, char* it)
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

	static unsigned int ParseColorHex(const char* str)
	{
		unsigned int c = 0, r = 0, g = 0, b = 0;
		int n = 0;
		str++; // skip #
		// Calculate number of characters.
		while (str[n] && !isspace(str[n]))
			n++;
		if (n == 6) {
			sscanf_s(str, "%x", &c);
		}
		else if (n == 3) {
			sscanf_s(str, "%x", &c);
			c = (c & 0xf) | ((c & 0xf0) << 4) | ((c & 0xf00) << 8);
			c |= c << 4;
		}
		r = (c >> 16) & 0xff;
		g = (c >> 8) & 0xff;
		b = c & 0xff;
		return SVG_RGB(r, g, b);
	}
	//===
	static unsigned int ParseColorRGB(const char* str)
	{
		int r = -1, g = -1, b = -1;
		char s1[32] = "", s2[32] = "";
		sscanf_s(str + 4, "%d%[%%, \t]%d%[%%, \t]%d", &r, s1, &g, s2, &b);
		if (strchr(s1, '%')) {
			return SVG_RGB((r * 255) / 100, (g * 255) / 100, (b * 255) / 100);
		}
		else {
			return SVG_RGB(r, g, b);
		}
	}
	//===
	static unsigned int ParseColorName(const char* str)
	{
		int i, ncolors = sizeof(svg__colors) / sizeof(SVGNamedColor);

		for (i = 0; i < ncolors; i++) {
			if (strcmp(svg__colors[i].name, str) == 0) {
				return svg__colors[i].color;
			}
		}

		return SVG_RGB(128, 128, 128);
	}

	static void TransformInit(float* t)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}
	//===
	static void TransformSetTranslation(float* t, float tx, float ty)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = tx; t[5] = ty;
	}

	//
	static void TransformSetScale(float* t, float sx, float sy)
	{
		t[0] = sx; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = sy;
		t[4] = 0.0f; t[5] = 0.0f;
	}
	//===
	static void TransformSetSkewX(float* t, float a)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = tanf(a); t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}
	//===
	static void TransformSetSkewY(float* t, float a)
	{
		t[0] = 1.0f; t[1] = tanf(a);
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}
	//===
	static void TransformSetRotation(float* t, float a)
	{
		float cs = cosf(a), sn = sinf(a);
		t[0] = cs; t[1] = sn;
		t[2] = -sn; t[3] = cs;
		t[4] = 0.0f; t[5] = 0.0f;
	}
	//===
	static void TransformMultiply(float* t, float* s)
	{
		float t0 = t[0] * s[0] + t[1] * s[2];
		float t2 = t[2] * s[0] + t[3] * s[2];
		float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
		t[1] = t[0] * s[1] + t[1] * s[3];
		t[3] = t[2] * s[1] + t[3] * s[3];
		t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
		t[0] = t0;
		t[2] = t2;
		t[4] = t4;
	}

	static int ParseTransformArgs(const char* str, float* args, int maxNa, int* na)
	 {
		 const char* end;
		 const char* ptr;
		 char it[64];

		 *na = 0;
		 ptr = str;
		 while (*ptr && *ptr != '(') ++ptr;
		 if (*ptr == 0)
			 return 1;
		 end = ptr;
		 while (*end && *end != ')') ++end;
		 if (*end == 0)
			 return 1;

		 while (ptr < end) {
			 if (*ptr == '-' || *ptr == '+' || *ptr == '.' || isdigit(*ptr)) {
				 if (*na >= maxNa) return 0;
				 ptr =ParseNumber(ptr, it, 64);
				 args[(*na)++] = (float)atof(it);
			 }
			 else {
				 ++ptr;
			 }
		 }
		 return (int)(end - str);
	 }

	static void TransformPremultiply(float* t, float* s)
	 {
		 float s2[6];
		 memcpy(s2, s, sizeof(float) * 6);
		 TransformMultiply(s2, t);
		 memcpy(t, s2, sizeof(float) * 6);
	 }

	static int ParseMatrix(float* xform, const char* str)
	{
		float t[6];
		int na = 0;
		int len = ParseTransformArgs(str, t, 6, &na);
		if (na != 6) return len;
		memcpy(xform, t, sizeof(float) * 6);
		return len;
	}

	static int ParseTranslate(float* xform, const char* str)
	{
		float args[2];
		float t[6];
		int na = 0;
		int len = ParseTransformArgs(str, args, 2, &na);
		if (na == 1) args[1] = 0.0;

		TransformSetTranslation(t, args[0], args[1]);
		memcpy(xform, t, sizeof(float) * 6);
		return len;
	}

	static int ParseScale(float* xform, const char* str)
	{
		float args[2];
		int na = 0;
		float t[6];
		int len = ParseTransformArgs(str, args, 2, &na);
		if (na == 1) args[1] = args[0];
		TransformSetScale(t, args[0], args[1]);
		memcpy(xform, t, sizeof(float) * 6);
		return len;
	}

	static int ParseSkewX(float* xform, const char* str)
	{
		float args[1];
		int na = 0;
		float t[6];
		int len = ParseTransformArgs(str, args, 1, &na);
		TransformSetSkewX(t, args[0] / 180.0f * SVG_PI);
		memcpy(xform, t, sizeof(float) * 6);
		return len;
	}

	static int ParseSkewY(float* xform, const char* str)
	{
		float args[1];
		int na = 0;
		float t[6];
		int len = ParseTransformArgs(str, args, 1, &na);
		TransformSetSkewY(t, args[0] / 180.0f * SVG_PI);
		memcpy(xform, t, sizeof(float) * 6);
		return len;
	}

	static int ParseRotate(float* xform, const char* str)
	{
		float args[3];
		int na = 0;
		float m[6];
		float t[6];
		int len = ParseTransformArgs(str, args, 3, &na);
		if (na == 1)
			args[1] = args[2] = 0.0f;
		TransformInit(m);

		if (na > 1) {
			TransformSetTranslation(t, -args[1], -args[2]);
			TransformMultiply(m, t);
		}

		TransformSetRotation(t, args[0] / 180.0f * SVG_PI);
		TransformMultiply(m, t);

		if (na > 1) {
			TransformSetTranslation(t, args[1], args[2]);
			TransformMultiply(m, t);
		}

		memcpy(xform, m, sizeof(float) * 6);

		return len;
	}
}
#endif