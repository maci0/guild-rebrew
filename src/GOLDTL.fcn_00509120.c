int __cdecl fcn_00500d60(int* src, char* dst);

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
	packed[1] = (char) (((seed >> 3) % 7 + age % 0x13) % 0xc + 1);
	packed[0] = (char) ((seed >> 5) % 0x1c + 1);
	*(int*) out = *(int*) packed;
	*(int*) (out + 4) = *(int*) (packed + 4);
	*(short*) (out + 8) = *(short*) (packed + 8);
	return 1;
}
