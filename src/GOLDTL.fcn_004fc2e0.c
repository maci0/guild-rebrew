// FUNCTION: GOLDTL 0x4fc2e0
// SIZE: 87

extern float g_773d4c;
extern float g_773d54;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* One expression keeps the quotient on the x87 stack; a named local spills it. */
float __cdecl fcn_004fc2e0(void)
{
	return MIN(1.0f, MAX(-1.0f, (g_773d54 - g_773d4c) / g_773d4c));
}
