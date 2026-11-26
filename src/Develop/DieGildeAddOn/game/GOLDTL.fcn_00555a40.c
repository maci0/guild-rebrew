


#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} S14;

#pragma pack(pop)
// SIZE 0xe

int __cdecl gm_RandomMod(int);

void __cdecl he_StartTalentLevelAction(void* action)
{
	*(S14*) ((char*) action + 0x52) = *(S14*) ((char*) action + 0x44);
	*(int*) ((char*) action + 0xb4) = gm_RandomMod(6) & 0xffff;
}
