/* Action handler registered for "bewegung/dreh_90_rechts" (index 7). It turns
 * the owner onto the requested heading and starts the matching 90 degree turn
 * animation. The 12 byte option block and the 2 x 0x58 frame pair are the same
 * aggregates StartObjectTransformAnimation hands to fcn_004339e0.
 *
 * Reconstructed from the native body at 0x004079f0 (915 bytes). Three codegen
 * deltas remain and are reported, not hidden: the native puts the links branch
 * out of line (`and eax,0x100; je`), it keeps the option byte at +1 as a
 * read-modify-write instead of a folded byte store, and it emits a second full
 * frame/option copy on the default-frame path instead of reusing the
 * animation path tail. */

typedef struct {
	unsigned char unbekannt_000;
	unsigned char bit_1_0 : 1;
	unsigned char bit_1_1 : 1;
	unsigned char bit_1_2 : 1;
	unsigned char bit_1_3 : 1;
	unsigned char bit_1_4 : 1;
	unsigned char unbekannt_1_rest : 3;
	unsigned char unbekannt_002[6];
	unsigned char bit_8_0 : 1;
	unsigned char bit_8_1 : 1;
	unsigned char unbekannt_8_rest : 6;
	unsigned char unbekannt_009[3];
} D3_OBJ_ANIM_FLAGS;

typedef struct {
	int unbekannt_000;
	float position[3];
	char unbekannt_010[4];
	float drehung[3];
	char unbekannt_020[0x58 - 0x20];
} D3_OBJ_ANIM_FRAME;

typedef struct {
	float v[4];
} VEC4_4079f0;

extern float g_662d40[3];

void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_00451380(float*, float*);
char* __cdecl ch_AttachAni(char*, char*, unsigned char);
int __cdecl fcn_004339e0(char*, D3_OBJ_ANIM_FLAGS, int, D3_OBJ_ANIM_FRAME*);
void __cdecl fcn_00433780(char*);
void __cdecl fcn_00435500(char*, char*);
void __cdecl fcn_00438cb0(char*, float*);
int __cdecl fcn_004050c0(char*);

/* ADDRESS: GOLDTL 0x004079f0 */
void __cdecl fcn_004079f0(char* task)
{
	D3_OBJ_ANIM_FRAME frames[2];
	int type;
	VEC4_4079f0 dir;
	D3_OBJ_ANIM_FLAGS flags;
	float angle;
	char* owner;
	char* stream;
	char* frame;

	owner = *(char**) (task + 0x14);
	if ((*(char**) (owner + 0x70) != 0 || *(int*) (owner + 0x7c) != 0)
	    && *(unsigned char*) (task + 0xf0) == 0) {
		*(int*) (task + 0xc) = -1;
		return;
	}
	if (*(int*) (task + 0xc) == 0) {
		angle = (float) *(int*) (task + 0x30) * *(float*) 0x662900;
		if (*(int*) (task + 0x34) != 0) {
			fcn_00455140(*(char**) (owner + 0x34), g_662d40, dir.v);
			angle = -fcn_00451380(g_662d40, dir.v) - angle;
			if (angle > *(float*) 0x6628fc) {
				angle -= *(float*) 0x6628c8;
			} else if (angle < *(float*) 0x6628f8) {
				angle += *(float*) 0x6628c8;
			}
		} else {
			*(float*) (task + 0x18) = 0.0f;
			*(float*) (task + 0x1c) = angle;
			*(float*) (task + 0x20) = 0.0f;
			*(float*) (task + 0x18) = *(float*) (*(char**) (owner + 0x34) + 0x84);
			*(float*) (task + 0x1c) = angle + *(float*) (*(char**) (owner + 0x34) + 0x88);
			*(float*) (task + 0x20) = *(float*) (*(char**) (owner + 0x34) + 0x8c);
		}
		if (angle >= *(double*) 0x6628f0) {
			*(char**) (owner + 0x70) = ch_AttachAni(*(char**) (task + 0x14),
								 "bewegung/dreh_90_links", 1);
		} else {
			if (angle < *(double*) 0x6628e8) {
				*(char**) (owner + 0x70) = ch_AttachAni(*(char**) (task + 0x14),
									 "bewegung/dreh_90_rechts", 1);
			}
		}
		*(unsigned char*) (task + 0xf0) = 1;
		if (*(char**) (owner + 0x70) != 0) {
			stream = *(char**) (*(char**) (owner + 0x70) + 0x68);
			frame = *(char**) (stream + 0x15c) + *(int*) (stream + 0x148) * 0xc0;
			dir.v[2] = *(float*) (frame - 0x8c);
			dir.v[1] = *(float*) (frame - 0x90);
			dir.v[0] = *(float*) (frame - 0x94);
			*(int*) &flags = 0;
			type = *(int*) (frame - 0xc0) - 0x1e;
			frames[0].unbekannt_000 = type;
			*(int*) ((char*) &flags + 8) = 0;
			flags.bit_1_2 = 1;
			flags.bit_1_4 = 1;
			frames[1].drehung[0] = -dir.v[0];
			frames[1].drehung[1] = angle - dir.v[1];
			flags.bit_1_3 = 1;
			frames[1].drehung[2] = -dir.v[2];
			flags.bit_8_1 = 1;
			frames[0].position[0] = 0.0f;
			frames[0].position[1] = 0.0f;
			frames[0].position[2] = 0.0f;
			frames[0].drehung[0] = 0.0f;
			frames[0].drehung[1] = 0.0f;
			frames[0].drehung[2] = 0.0f;
			frames[1].position[0] = 0.0f;
			frames[1].position[1] = 0.0f;
			frames[1].position[2] = 0.0f;
			*(int*) (owner + 0x78) = fcn_004339e0(*(char**) (*(char**) (task + 0x14) + 0x34),
							      flags, 2, frames);
			return;
		}
		frames[0].unbekannt_000 = 8;
		*(int*) &flags = 0;
		*(int*) ((char*) &flags + 8) = 0;
		flags.bit_1_2 = 1;
		flags.bit_1_4 = 1;
		flags.bit_1_3 = 1;
		frames[1].drehung[1] = angle;
		flags.bit_8_1 = 1;
		frames[0].drehung[0] = 0.0f;
		frames[0].drehung[1] = 0.0f;
		frames[0].drehung[2] = 0.0f;
		frames[0].position[0] = 0.0f;
		frames[0].position[1] = 0.0f;
		frames[0].position[2] = 0.0f;
		frames[1].drehung[0] = 0.0f;
		frames[1].drehung[2] = 0.0f;
		frames[1].position[0] = 0.0f;
		frames[1].position[1] = 0.0f;
		frames[1].position[2] = 0.0f;
		*(int*) (owner + 0x78) = fcn_004339e0(*(char**) (*(char**) (task + 0x14) + 0x34),
						      flags, 2, frames);
		return;
	}
	if (*(int*) (owner + 0x78) != 0
	    && (*(unsigned char*) (*(char**) (owner + 0x78) + 0x2d) & 0x20) != 0) {
		fcn_00433780(*(char**) (owner + 0x34));
		*(int*) (owner + 0x78) = 0;
		if (*(char**) (owner + 0x70) == 0) {
			fcn_004050c0(task);
			task = 0;
		}
	}
	if (*(char**) (owner + 0x70) != 0) {
		if ((*(unsigned char*) (*(char**) (owner + 0x70) + 0x6d) & 0x20) != 0) {
			fcn_00435500(*(char**) (*(char**) (*(char**) (task + 0x14) + 0x34) + 0x1ec) + 0xf4,
				     *(char**) (*(char**) (owner + 0x70) + 0x68));
			fcn_00438cb0(*(char**) (*(char**) (task + 0x14) + 0x34),
				     (float*) (task + 0x18));
			fcn_00433780(*(char**) (*(char**) (task + 0x14) + 0x34));
			*(int*) (owner + 0x78) = 0;
			fcn_004050c0(task);
			return;
		}
		return;
	}
	if (*(int*) (owner + 0x78) == 0 && task != 0) {
		fcn_004050c0(task);
	}
}
