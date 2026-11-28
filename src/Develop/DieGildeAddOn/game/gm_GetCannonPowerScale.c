



int __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);

float __cdecl gm_GetCannonPowerScale(char* p)
{
	float v;

	v = 1.0f;
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x259)) {
		v = 1.05f;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x25b)) {
		v = v + 0.05f;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x261)) {
		return v + 0.05f;
	}
	return v;
}
