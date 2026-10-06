// FUNCTION: GOLD 0x005518f0
// FUNCTION: GOLDTL 0x5599c0

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c5ed0(int, char*, int);

void __cdecl fcn_005599c0(char* o)
{
	switch (fcn_0042e410(4)) {
	case 0:
		fcn_004c5ed0(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 1:
		fcn_004c5ed0(*(int*) (o + 4), "gestik/herranwinken", 1);
		fcn_004c5ed0(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 2:
		fcn_004c5ed0(*(int*) (o + 4), "gestik/kinn_kratzen", 1);
		fcn_004c5ed0(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 3:
		fcn_004c5ed0(*(int*) (o + 4), "gestik/durch_haar_fahr", 1);
		fcn_004c5ed0(*(int*) (o + 4), "gestik/herranwinken", 1);
		fcn_004c5ed0(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	}
}
