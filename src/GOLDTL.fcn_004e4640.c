// FUNCTION: GOLDTL 0x4e4640
// SIZE: 64

typedef struct
{
	char pad[0x100];
	int id;
	int state;
	char mid[0x1c];
	unsigned char flags;
	char tail[0xb73];
} Obj;
// SIZE 0xc98

extern Obj* g_6b7e94;

void __cdecl fcn_00428720(Obj*);

int __cdecl fcn_004e4640(void)
{
	int i;
	Obj* o;

	for (i = 0; i < 128; i++) {
		o = &g_6b7e94[i];
		if (o->id != -1 && (o->flags & 1) != 0 && o->state == -2) {
			fcn_00428720(o);
		}
	}
	return 0;
}
