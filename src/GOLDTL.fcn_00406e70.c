typedef struct OWNER_406e70 OWNER_406e70;
struct OWNER_406e70 {
	unsigned char pad_000[0x6c];
	unsigned char f6c;
	unsigned char f6d;
	unsigned char pad_06e[2];
	OWNER_406e70* f70;
	unsigned char pad_074[0x18];
	unsigned char f8c;
};

int __cdecl ch_AttachAni(void* owner, void* name, int flags);
int __cdecl fcn_004050c0(char* task);

/* ADDRESS: GOLDTL 0x00406e70 */
void __cdecl fcn_00406e70(char* task)
{
	OWNER_406e70* owner;
	OWNER_406e70* ani;

	owner = *(OWNER_406e70**) (task + 0x14);
	if (*(int*) (task + 0xc) == 0) {
		ani = (OWNER_406e70*) ch_AttachAni(owner, task + 0xf0, 1);
		owner->f70 = ani;
		if (ani != 0) {
			*(unsigned short*) ((char*) owner + 0x8c) |= 2;
			ani->f6c = 1;
			owner->f70->f70 = (OWNER_406e70*) ((unsigned int) owner->f70->f70 & 0xfffffffc);
			owner->f70->f6d |= 0x10;
			return;
		}
	} else {
		ani = owner->f70;
		if (ani == 0 || (ani->f6d & 0x20) == 0) {
			return;
		}
	}
	fcn_004050c0(task);
}
