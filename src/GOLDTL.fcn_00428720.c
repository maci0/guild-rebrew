


char* __cdecl fcn_004262b0(char* c, const char* name);
void __cdecl fcn_00427c40(char* c, char* d);
void __cdecl fcn_00429670(char* c);
void __cdecl fcn_00425bf0(char* c, int h, const char* msg);
void __cdecl fcn_00429d30(char* c);

int __cdecl fcn_00428720(char* c)
{
	unsigned int flags;
	char* d;
	char* t;

	if (c == 0) {
		return 0;
	}
	flags = *(unsigned int*) (c + 0x124);
	*(int*) (c + 0xc5c) = 0;
	*(int*) (c + 0xc60) = 0;
	if ((flags & 2) == 0) {
		d = fcn_004262b0(c, "exit");
		if (d != 0) {
			*(unsigned int*) (c + 0x124) = flags | 3;
			fcn_00427c40(c, d);
			*(int*) (c + 0xc84) = 2;
			fcn_00429670(c);
			return 0;
		}
	}
	t = *(char**) (c + 0xc94);
	*(int*) (c + 0x100) = 0;
	*(int*) (c + 0x124) = 0;
	if (t != 0) {
		*(int*) (t + 0x28) = -1;
	}
	fcn_00425bf0(c, 0, "Script done...");
	fcn_00429d30(c);
	return 1;
}
