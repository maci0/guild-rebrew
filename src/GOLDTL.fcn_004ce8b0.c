float __cdecl fcn_00507f10(char*, int);
int* __cdecl fcn_004ce610(char*);
float __cdecl fcn_004ff040(char*);

/* ADDRESS: GOLD 0x004cdcf0 */
/* ADDRESS: GOLDTL 0x004ce8b0 */

float __cdecl fcn_004ce8b0(char* e)
{
	float mult;
	float base;
	int* p;

	mult = 0.5f;
	base = fcn_00507f10(e, 3);
	p = fcn_004ce610(e);
	if (p != 0) {
		switch (*p) {
		case 0x158:
			mult = 1.0f;
			break;
		case 0x154:
			mult = 0.5f;
			break;
		case 0x156:
		case 0x16e:
		case 0x172:
			mult = 0.8f;
			break;
		case 0x174:
		case 0x176:
			mult = 0.9f;
			break;
		case 0x15e:
		case 0x160:
			mult = 0.7f;
			break;
		default:
			mult = 0.3f;
			break;
		}
	}
	return fcn_004ff040(e) * base * mult;
}
