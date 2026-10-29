int __cdecl fcn_00500d60(int* src, char* dst);

#pragma pack(push, 1)
typedef struct {
	int a;
	int b;
	short c;
} PACKED10_509120;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x00509120 */
int __cdecl fcn_00509120(char* e, char* out)
{
	int time[4];
	char packed[12];
	unsigned int seed;
	int age;

	if (e[8] != 0) {
		return 0;
	}
	age = *(short*) (e + 0x28);
	time[0] = age;
	fcn_00500d60(time, packed);
	seed = *(unsigned int*) (e + 0x30) ^ *(short*) (packed + 2);
	packed[1] = (char) ((unsigned int) ((seed >> 3) % 7 + age % 0x13) % 0xc + 1);
	packed[0] = (char) ((seed >> 5) % 0x1c + 1);
	*(PACKED10_509120*) out = *(PACKED10_509120*) packed;
	return 1;
}
