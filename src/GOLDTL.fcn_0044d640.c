


// SIZE 0x18
typedef struct Vert {
	float x;
	float y;
	float z;
	float rest[3];
} Vert;

extern char g_662d18[];

char* __cdecl fcn_004010b0(int);
char* __cdecl fcn_0064f026(char*, char*);
double __cdecl fcn_0064d62e(char*);

void __cdecl fcn_0044d640(int r, char* o)
{
	int i;
	char* line;

	for (i = 0; i < *(int*) (o + 0x24); i++) {
		line = fcn_004010b0(r);
		(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].x = (float) fcn_0064d62e(fcn_0064f026(line, g_662d18));
		(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].y = (float) fcn_0064d62e(fcn_0064f026(0, g_662d18));
		(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].z = (float) fcn_0064d62e(fcn_0064f026(0, g_662d18));
		(*(int*) (o + 0x28))++;
	}
	fcn_004010b0(r);
}
