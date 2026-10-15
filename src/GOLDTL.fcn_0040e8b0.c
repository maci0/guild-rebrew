

void __cdecl fcn_00455350(char* src, char* pos, float* out);
int __cdecl fcn_004488e0(char* name, int a, int b);
void __cdecl fcn_00438b40(char* h, float* pos);
void __cdecl fcn_00455240(char* src, float* out);
void __cdecl fcn_00438cb0(char* h, float* v);

int __cdecl fcn_0040e8b0(char** name, char** a)
{
	float rot[3];
	float pos[4];
	int h;

	if (*a == 0) {
		return 0;
	}
	fcn_00455350(*a, *a + 0x4c, pos);
	h = fcn_004488e0(*name, 0, 0);
	fcn_00438b40(h, pos);
	fcn_00455240(*a, rot);
	fcn_00438cb0(h, rot);
	return h;
}
