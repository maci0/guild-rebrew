typedef struct {
	unsigned char id;
	char pad[0x23];
} Rec24;

int __cdecl gm_FindLawByKindAndSub(char*, int, Rec24*);
void __cdecl gm_FormatLawName(void*, int);
int __cdecl d2_ShowGesetzDialog(void*, void*);

/* ADDRESS: GOLDTL 0x004f8140 */
/* ADDRESS: GOLDDE 0x004e3f20 */
int __cdecl gm_HandlePrimaryLawPrivilege(char* a1, int* a2)
{
	Rec24 rec;
	int result;
	char* other;

	result = 0;
	if (*a2 == 3 || *a2 == 1) {
		if (a1[0x166] == 0)
			return 1;
		if (gm_FindLawByKindAndSub(a1, 1, &rec) == 0)
			return 1;
		if (a1[2] == 6)
			gm_FormatLawName((char*) a2 + 0x14, rec.id);
		if (*(int*) (a1 + 0x1c8) & 0x200)
			return 9;
		if (*(int*) (a1 + 0x1c8) & 0x80000)
			return 1;
		a2[1] = rec.id;
		if (*a2 == 3) {
			*(int*) ((char*) a2 + 0x214) = 1;
			result = d2_ShowGesetzDialog(a1, a2);
		}
		return result | 2;
	}
	if (*a2 == 4 || *a2 == 2) {
		if (((*(int*) (a1 + 0x1c8) & 0x100) == 0) || ((other = *(char**) ((char*) a2 + 0x21c)) == 0))
			return 1;
		if (other[0x166] == 0)
			return 1;
		if (*(int*) (other + 0x1c8) & 0x80000)
			return 1;
		if (gm_FindLawByKindAndSub(other, 1, &rec) == 0)
			return 1;
		a2[1] = rec.id;
		if (*a2 == 4) {
			*(int*) ((char*) a2 + 0x214) = 1;
			result = d2_ShowGesetzDialog(a1, a2);
		} else if (a1[2] == 6) {
			gm_FormatLawName((char*) a2 + 0x14, rec.id);
		}
		return result | 10;
	}
	return 1;
}
