// FUNCTION: GOLDTL 0x004ef250
// SIZE: 140

typedef struct
{
	int id;
	int pad4;
	int kind;
	float f;
} Rec16;
// SIZE 0x10

typedef struct
{
	int n;
	int pad4;
	Rec16 recs[3];
} Set;
// SIZE 0x38

extern char g_7f4ca0[];
extern float g_662da8;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);
void __cdecl fcn_005b3410(char* e, char* r, int mode);

int __cdecl fcn_004ef250(Set* p)
{
	int i;
	int mode;
	char* r;
	char* e;

	for (i = 0; i < 3; i++) {
		if (p->n == i) {
			r = gm_StartFilteredEntitySearch(1, 1, p->recs[i].id);
			mode = 0;
			if (r != 0 && *(unsigned short*) (r + 0x27) != 0xffff) {
				e = g_7f4ca0 + *(unsigned short*) (r + 0x27) * 0x21c;
				if (p->recs[i].kind == 1) {
					mode = 2;
					if (!(p->recs[i].f > g_662da8)) {
						mode = 1;
					}
				}
				if (e[2] == 6) {
					fcn_005b3410(e, r, mode);
				}
			}
		}
	}
	return 0;
}
