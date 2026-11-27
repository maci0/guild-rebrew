char* __cdecl ahm_GetWorkshopOwner(char*);
float __cdecl ahm_GetEssenceValue(char*, int);
char* __cdecl ahm_FindRecipePrototypeByKey(int);

/* ADDRESS: GOLDTL 0x004ee160 */
int __cdecl ahm_CalcWorkshopOutputScore(char* a0)
{
	char* p;
	char* e;
	char* q;
	char* p2;
	float total;
	float sum;
	float r;
	int n;

	sum = 0;
	p = ahm_GetWorkshopOwner(a0);
	if (p == 0) {
		return -1;
	}
	e = *(char**) (a0 + 0x65);
	r = ahm_GetEssenceValue(p, 0);
	total = r * r;
	r = ahm_GetEssenceValue(p, 1);
	total = r * r + total;
	r = ahm_GetEssenceValue(p, 2);
	total = r * r + total;
	r = ahm_GetEssenceValue(p, 3);
	total = r * r + total;
	for (p2 = e + 0x10, n = 6; n != 0; n--, p2 += 8) {
		q = ahm_FindRecipePrototypeByKey(*(int*) (p2 - 4));
		if (q != 0) {
			sum += *(float*) (q + 4) + *(float*) p2;
		}
	}
	return (int) (sum * 500.0f + total * 500.0f) << 5;
}
