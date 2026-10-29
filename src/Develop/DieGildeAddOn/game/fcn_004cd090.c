typedef struct {
	char pad[0x10];
	int tag;
	int value;
	int name;
} T_4cd090;

extern char* g_773da8;
extern char g_7f4ca0[];

int __cdecl fcn_00503fe0(int a, int b, int c);
int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl fcn_00549c50(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x004cd090 */
int __cdecl fcn_004cd090(T_4cd090* s, char* out)
{
	int h;
	int p;
	int i;
	int* q;

	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	if (s->tag == 0x6a6f696e) {
		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		for (i = 0; i < 4; i++) {
			if (*(int*) (p + 0x1c + i * 4) == s->value) {
				return 1;
			}
		}
		for (i = 0; i < 4; i++) {
			if (*(int*) (p + 0x1c + i * 4) == -1) {
				break;
			}
		}
		if (i >= 4) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		*(int*) (p + 0x1c + i * 4) = s->value;
		return 0;
	}
	if (s->tag == 0x6c656176) {
		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		q = (int*) (p + 0x1c);
		for (i = 0; i < 4; i++) {
			if (*q == s->value) {
				break;
			}
			q++;
		}
		if (i >= 4) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		*(int*) (p + 0x1c + i * 4) = -1;
		return 0;
	}
	if (s->tag == 0x636c6572) {
		char* e;

		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		if (*(unsigned short*) (h + 0x27) != 0xffff) {
			e = g_7f4ca0 + *(unsigned short*) (h + 0x27) * 0x21c;
			if (e != 0 && e != g_773da8 &&
			    *(char*) (e + 8) != 0 &&
			    *(unsigned char*) (e + 2) != 0xf) {
				return 1;
			}
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		q = (int*) (p + 0x1c);
		for (i = 4; i != 0; i--) {
			if (*q == s->value) {
				*q = -1;
			}
			q++;
		}
		return 0;
	}
	return 1;
}
