/* Device teardown: resets the two render targets through interface slots
   0x7c and 0xd8, releases the cached objects at +0x28/+0x2c, and either
   releases +0x34 or walks the two slot pairs at +0x38, passing each through
   slot 0x3c into the device slot 0x70 before releasing it. The native entry
   keeps its argument on the stack (stdcall, ret 4). */
typedef struct Vtbl6164fa {
	char pad0[8];
	void (__stdcall* release)(void*);
	char padc[0x30];
	int (__stdcall* v3c)(void*, int, void**);
	char pad40[0x30];
	void (__stdcall* v70)(void*, void*, int, int, void*, int);
	char pad74[8];
	void (__stdcall* v7c)(void*, int, int);
	char pad80[0x58];
	void (__stdcall* vd8)(void*, int);
} Vtbl6164fa;

typedef struct S6164fa {
	char pad0[8];
	int f8;
	char padc[0x1c];
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	int f48;
	int f4c;
	char pad50[0x410];
	int f460;
	char pad464[0xc];
	int f470;
} S6164fa;

int __fastcall fcn_00616426(S6164fa*);

/* ADDRESS: GOLDTL 0x006164fa */
int __stdcall fcn_006164fa(S6164fa* arg)
{
	S6164fa* orig;
	int i;
	int* p;
	int r;
	void* dev;

	orig = arg;
	r = fcn_00616426(arg);
	if (r < 0)
		return r;
	dev = (void*)arg->f8;
	(*(Vtbl6164fa**)*(int*)dev)->v7c(dev, arg->f28, arg->f2c);
	dev = (void*)arg->f8;
	(*(Vtbl6164fa**)*(int*)dev)->vd8(dev, arg->f470);
	if (arg->f28) {
		(*(Vtbl6164fa**)*(int*)arg->f28)->release((void*)arg->f28);
		arg->f28 = 0;
	}
	if (arg->f2c) {
		(*(Vtbl6164fa**)*(int*)arg->f2c)->release((void*)arg->f2c);
		arg->f2c = 0;
	}
	if (arg->f460 == 1) {
		if (arg->f34) {
			(*(Vtbl6164fa**)*(int*)arg->f34)->release((void*)arg->f34);
			arg->f34 = 0;
		}
	}
	else {
		p = (int*)((char*)arg + 0x38);
		for (i = 2; i != 0; i--) {
			if (*p) {
				if (p[4] == 0 && p[2] != 0) {
					(*(Vtbl6164fa**)*p)->v3c((void*)*p, 0, (void**)&arg);
					dev = (void*)orig->f8;
					(*(Vtbl6164fa**)*(int*)dev)->v70(dev, (void*)p[2], 0, 0, arg, 0);
					if (arg) {
						(*(Vtbl6164fa**)*(int*)arg)->release(arg);
						arg = 0;
					}
				}
				if (*p) {
					(*(Vtbl6164fa**)*p)->release((void*)*p);
					*p = 0;
				}
			}
			p++;
		}
	}
	arg->f460 = 0;
	return 0;
}
