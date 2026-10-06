// FUNCTION: GOLD 0x0050b090
// FUNCTION: GOLDTL 0x0050e520

extern unsigned char* g_868050;

int __cdecl fcn_0050e520(int k, int* out)
{
	int r;

	r = 1;
	switch (g_868050[k * 0x24d]) {
	case 15:
		*out = 1;
		break;
	case 23:
		*out = 2;
		break;
	case 24:
		*out = 3;
		break;
	case 25:
		*out = 4;
		break;
	case 26:
		*out = 5;
		break;
	case 7:
		*out = 6;
		r = 0;
		break;
	case 4:
		*out = 7;
		r = 0;
		break;
	case 16:
		*out = 7;
	default:
		r = 0;
		break;
	}
	return r;
}
