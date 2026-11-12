/* ADDRESS: GOLD 0x00504100 */
int __cdecl fcn_00504100(unsigned int kind, int* a, int* b)
{
	switch (kind) {
	case 11: *a = 2; *b = 3; return 1;
	case 9: *a = 0; *b = 4; return 1;
	case 7: *a = 4; *b = 1; return 1;
	case 6: *a = 0; *b = 1; return 1;
	case 8: *a = 0; *b = 3; return 1;
	case 5: *a = 1; *b = 0; return 1;
	case 12: *a = 3; *b = 2; return 1;
	case 10: *a = 3; *b = 2; return 1;
	case 2: *a = 1; *b = 0; return 1;
	case 4: *a = 1; *b = 2; return 1;
	case 13: *a = 2; *b = 0; return 1;
	case 1:
	case 3:
	case 14:
	case 15:
	case 16:
	default: *a = 1; *b = 0; return 1;
	}
}
