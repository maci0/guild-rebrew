


unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestPlayAnimation(int, char*, int);

void __cdecl ch_PlayRandomGesture(char* o)
{
	switch (gm_RandomMod(4)) {
	case 0:
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 1:
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/herranwinken", 1);
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 2:
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/kinn_kratzen", 1);
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	case 3:
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/durch_haar_fahr", 1);
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/herranwinken", 1);
		cm_RequestPlayAnimation(*(int*) (o + 4), "gestik/haende_reiben", 1);
		break;
	}
}
