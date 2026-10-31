


typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[3];
	int fc;
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

typedef struct {
	int a;
	int id;
	char pad8[0x10];
} tbl18;
// SIZE 0x18

int __cdecl fcn_004e8a80(int, rec18*);
char* __cdecl gm_LookupEntityRecordById(int);

char* __cdecl fcn_004e9110(int kind)
{
	rec18 r;

	if (kind == 0x24) {
		if (fcn_004e8a80(0x27, &r) != 0)
			return gm_LookupEntityRecordById(r.id);
	}
	else if (kind == 0x25 || kind == 0x23) {
		if (fcn_004e8a80(0x26, &r) != 0)
			return gm_LookupEntityRecordById(r.id);
	}
	return 0;
}
