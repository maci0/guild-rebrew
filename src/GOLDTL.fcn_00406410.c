struct anim_406410 {
	char pad0[0x6c];
	char started;
	unsigned char pad6d0 : 4;
	unsigned char looping : 1;
	unsigned char paused : 1;
	char pad6e[2];
	unsigned int flags;
};


extern int g_6b8010;

struct anim_406410* __cdecl fcn_00404dc0(char* obj, char* name, int mode);
void __cdecl fcn_00436a00(int h, struct anim_406410* a, int n);
int __cdecl fcn_00404f60(char* ev);
int __cdecl fcn_00413190(char* p);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_004050c0(char* ev);

// FUNCTION: GOLDTL 0x406410
// SIZE: 248
void __cdecl fcn_00406410(char* ev)
{
	char* obj;
	struct anim_406410* a;
	int saved;

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) == 0) {
		if (ev[0xf0] != 0 && *(int*) (*(char**) (*(char**) (obj + 0x34) + 0x1cc) + 0x390) == 0) {
			*(short*) (obj + 0x8c) |= 2;
			if (ev[0x18c] & 1) {
				a = fcn_00404dc0(*(char**) (ev + 0x14), ev + 0xf0, 1);
				*(struct anim_406410**) (obj + 0x70) = a;
				*(struct anim_406410**) (obj + 0x74) = a;
				fcn_00436a00(*(int*) (obj + 0x34), a, -1);
			} else {
				a = fcn_00404dc0(*(char**) (ev + 0x14), ev + 0xf0, 1);
				*(struct anim_406410**) (obj + 0x70) = a;
				*(struct anim_406410**) (obj + 0x74) = a;
			}
		}
		if (*(struct anim_406410**) (obj + 0x70) != 0) {
			(*(struct anim_406410**) (obj + 0x70))->started = 1;
			(*(struct anim_406410**) (obj + 0x70))->flags &= ~3;
			(*(struct anim_406410**) (obj + 0x70))->looping = 1;
		}
	} else if (fcn_00404f60(ev) == -1) {
		saved = g_6b8010;
		fcn_004432d0(fcn_00413190(*(char**) (obj + 0x88)), 1);
		*(short*) (*(char**) (ev + 0x14) + 0x8c) |= 0x10;
		*(short*) (*(char**) (ev + 0x14) + 0x8c) &= ~2;
		fcn_004432d0(saved, 1);
		fcn_004050c0(ev);
	}
}
