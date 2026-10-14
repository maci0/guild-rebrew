extern char* g_aed32c;

void __cdecl fcn_00541ff0(int);

// SIZE 0x21c
struct s_7f4ca0 {
	unsigned short id;
	char kind;
	char pad;
	int f4;
	char pad2[0x14];
	float f1c;
	char pad3[0x144];
	char b164;
	char b165;
	char pad4[0x4b];
	unsigned char b1b1;
	char pad5[0x6a];
};

extern char g_7f4ca0[];




int __cdecl fcn_0050db40(struct s_7f4ca0*, int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004c4510(struct s_7f4ca0*, int);
void __cdecl fcn_004c4670(int, int, int, char*);
void __cdecl fcn_004c5360(void);

void __cdecl fcn_005421f0(void)
{
	int i;
	char* k;
	struct s_7f4ca0* r;
	char c;

	i = 0;
	for (k = &((struct s_7f4ca0*)g_7f4ca0)[0].kind; (int) k < (int) &((struct s_7f4ca0*)g_7f4ca0)[768].kind; k += sizeof(struct s_7f4ca0)) {
		r = (struct s_7f4ca0*) (k - 2);
		if (r->id != 0xffff) {
			if (r->b164 != 0 || r->b165 != 0) {
				fcn_00541ff0(i);
			}
			if ((r->kind == 2 || r->kind == 5 || r->kind == 4) && fcn_0050db40(r, 0) != 0) {
				fcn_004ff210(r->id, (int) -(r->f1c + 5.0f));
			}
			if (r->b1b1 > 0) {
				c = -1;
				fcn_004c4510(r, r->f4);
				fcn_004c4670(1, 1, k - g_aed32c + 0x1af, &c);
				fcn_004c5360();
			}
		}
		i++;
	}
}
