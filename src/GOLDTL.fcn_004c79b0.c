// FUNCTION: GOLDTL 0x4c79b0
// SIZE: 162

// SIZE 0x21c
typedef struct {
	char data[0x21c];
} Rec21c;

extern Rec21c g_7f4ca0[];

int __cdecl fcn_00509620(int a, int b);
int __cdecl fcn_00508e40(int h);
int __cdecl fcn_004f4650(int h, char** obj, int** val);
unsigned char __cdecl fcn_004f1790(int a, int* b);
void __cdecl fcn_004f22e0(int h, char* obj, int v, int flag);

int __cdecl fcn_004c79b0(char* o, char* out)
{
	int idx;
	int h;

	idx = fcn_00509620(*(int*) (o + 0x10), *(int*) (o + 0x14));
	if (out != 0) {
		out[0] = 1;
		if (idx >= 0) {
			char* obj;
			int* val;

			h = fcn_00508e40(*(int*) (o + 0x14));
			if (fcn_004f4650(h, &obj, &val) != 0) {
				fcn_004f22e0(h, obj, *val, fcn_004f1790(*(int*) (obj + 0x65), val));
			}
			out[1] = 1;
			*(Rec21c**) (out + 6) = &g_7f4ca0[idx];
		} else {
			out[1] = 0;
			*(int*) (out + 6) = 0;
		}
	}
	return 0;
}
