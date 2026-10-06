// FUNCTION: GOLD 0x00514390
// FUNCTION: GOLDTL 0x517b90

#include <ctype.h>
#include <string.h>

int __cdecl fcn_00517b90(char* s, int end, char* out)
{
	int i;

	i = end;
	while (i >= 0 && isdigit(s[i])) {
		i--;
	}
	i++;
	memcpy(out, s + i, end - i + 1);
	out[end - i + 1] = 0;
	return i;
}
