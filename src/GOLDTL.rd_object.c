#include <stdio.h>
#include <string.h>

int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* dst);
int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
void __cdecl fcn_00401280(void* stream, void* dst);
void __cdecl fcn_0041d9e0(const char* msg);
void __cdecl fcn_00438b40(char* object, void* vector);
void __cdecl fcn_00438cb0(char* object, void* vector);
char* __cdecl fcn_00439750(int kind, char* name);
void __cdecl fcn_00439aa0(char* object);
void __cdecl fcn_00439ba0(char* object, char* sibling);
void __cdecl fcn_00439c00(char* object, char* child);
void __cdecl fcn_00439fa0(char* object);
void __cdecl fcn_0043b7b0(void* stream, char* object);
char __cdecl fcn_00442c00(char* object, char on);
int __cdecl fcn_00446ca0(unsigned int version);
void __cdecl fcn_00449f90(char* object, void* part, char* name);
int __cdecl fcn_0044c200(char* a, char* b);
void __cdecl fcn_0045ce90(void* resource);
void __cdecl m_FreeTracked(void* ptr);

extern unsigned char g_6b85a4;

#define RD_COPY_NINE(dst, src) \
	do { \
		*(int*) ((dst) + 0x28) = *(int*) ((src) + 0x28); \
		*(int*) ((dst) + 0x24) = *(int*) ((src) + 0x24); \
		*(int*) ((dst) + 0x2c) = *(int*) ((src) + 0x2c); \
		*(int*) ((dst) + 0x18) = *(int*) ((src) + 0x18); \
		*(int*) ((dst) + 0x1c) = *(int*) ((src) + 0x1c); \
		*(int*) ((dst) + 0x20) = *(int*) ((src) + 0x20); \
		*(int*) ((dst) + 0x00) = *(int*) ((src) + 0x00); \
		*(int*) ((dst) + 0x04) = *(int*) ((src) + 0x04); \
		*(int*) ((dst) + 0x08) = *(int*) ((src) + 0x08); \
	} while (0)

/* ADDRESS: GOLDTL 0x00447110 */
char* __cdecl rd_object(void* stream, char* parent, unsigned int version, unsigned char resources)
{
	unsigned char b;
	unsigned char placeholder;
	unsigned char marker;
	unsigned char sibling;
	int type;
	int scratch;
	int scratch2;
	int aux_a;
	int aux_b;
	char name[256];
	char tmp[256];
	char* object;
	int kind;
	int i;
	int off;
	char* draw;
	char* lights;
	char* cursor;

	object = 0;
	placeholder = 0;
	aux_a = 0;
	aux_b = 0;
	if (version >= 0x3a6c000bu) {
	fcn_00401180(stream, &b);
	if (b != 0) {
		fcn_004011a0(stream, name);
		if (version >= 0x3a6c00b2u) {
			fcn_004011f0(stream, &aux_a);
		}
		if (version >= 0x3a6c00abu) {
			fcn_004011f0(stream, &aux_b);
		}
		fcn_004011f0(stream, &type);
		if (version >= 0x3a6c00a6u) {
			fcn_00401180(stream, &marker);
			if (name[0] == '!' && marker == 0) {
				i = 0;
				do {
					b = (unsigned char) name[i + 1];
					tmp[i] = (char) b;
					i++;
				} while (b != 0);
				i = 0;
				do {
					b = (unsigned char) tmp[i];
					name[i] = (char) b;
					i++;
				} while (b != 0);
			}
			kind = type;
		} else {
			marker = 0;
			switch (type) {
			case 0:
				kind = 0;
				break;
			case 1:
				kind = 1;
				break;
			case 2:
				kind = 3;
				break;
			case 3:
			case 4:
				kind = 4;
				break;
			case 5:
				kind = 5;
				break;
			case 6:
				kind = 6;
				break;
			case 7:
				kind = 7;
				break;
			case 8:
				kind = 8;
				break;
			default:
				kind = 2;
				break;
			}
		}
		object = fcn_00439750(kind, name);
		*(int*) (object + 0x204) = aux_a;
		*(int*) (object + 0x220) = aux_b;
		*(char**) (object + 0x1fc) = parent;
		if (parent != 0) {
			object[0x214] = (char) (object[0x214] & 0xfe);
		}
		switch (*(int*) (object + 0x218)) {
		case 1:
		case 4:
			fcn_00401180(stream, &b);
			object[0x214] = (char) ((object[0x214] & ~0x20) | ((b << 5) & 0x20));
			fcn_00401180(stream, &scratch);
			if (version >= 0x3a6c000du) {
				fcn_00401180(stream, &b);
				object[0x215] = (char) ((object[0x215] & ~0x01) | (b & 0x01));
				if (version >= 0x3a6c00a6u) {
					fcn_00401180(stream, &b);
					object[0x216] = (char) ((object[0x216] & ~0x03) | (b & 0x03));
					if (version <= 0x3a6c00b8u) {
						object[0x216] = (char) (object[0x216] | ((object[0x216] & 0x01) << 1));
					}
					fcn_00401180(stream, &b);
					object[0x216] = (char) ((object[0x216] & ~0x04) | ((b << 2) & 0x04));
					if (version >= 0x3a6c00b4u) {
						fcn_00401180(stream, &b);
						object[0x216] = (char) ((object[0x216] & ~0x08) | ((b << 3) & 0x08));
					}
					if (version >= 0x3a6c00b9u) {
						fcn_00401180(stream, &b);
						object[0x216] = (char) ((object[0x216] & ~0x10) | ((b << 4) & 0x10));
					}
				}
			}
			fcn_004011f0(stream, &type);
			fcn_004011f0(stream, &type);
			if (version >= 0x3a6c00a4u) {
				if (type > 0) {
					fcn_004011a0(stream, name);
					if (fcn_0044c200(name, name) != 0) {
						fcn_00449f90(object, 0, name);
					} else {
						sprintf(tmp, "Missing LOD for Object \"%s\": [\"%s.bgf\"].", object, name);
						g_6b85a4 = 1;
					}
				}
			} else {
				if (*(char**) (object + 0x1ec) == 0) {
					fcn_00439fa0(object);
				}
				i = 0;
				off = 0;
				while (i < type) {
					fcn_004011a0(stream, name);
					fcn_0044c200(name, name);
					draw = *(char**) (object + 0x1ec);
					fcn_00449f90(object, draw + off + 0xf4, name);
					i++;
					off += 0x4a4;
				}
				if (version >= 0x3a6c00a3u) {
					fcn_00401180(stream, &b);
					if (b != 0) {
						fcn_004011a0(stream, name);
						fcn_0044c200(name, name);
						draw = *(char**) (object + 0x1ec);
						fcn_00449f90(object, draw + 0xee0, name);
					}
				} else {
					draw = *(char**) (object + 0x1ec);
					cursor = *(char**) (draw + 0x40c);
					if (cursor != 0) {
						i = 0;
						do {
							name[i] = cursor[i];
							i++;
						} while (cursor[i - 1] != 0);
						strcat(name, "_s");
						if (fcn_0044c200(name, name) != 0) {
							fcn_00449f90(object, draw + 0xee0, name);
						}
					}
				}
			}
			/* FALLTHROUGH */
		case 2:
		case 3:
			fcn_00401280(stream, object + 0x4c);
			fcn_00401280(stream, object + 0x84);
			fcn_00401180(stream, &aux_a);
			object[0x214] = (char) ((object[0x214] & ~0x40) | ((*(unsigned char*) &aux_a << 6) & 0x40));
			if (b != 0) {
				fcn_00401280(stream, object + 0x5c);
				fcn_00401280(stream, object + 0x90);
			}
			if (version >= 0x3a6c00afu) {
				cursor = object + 0xa8;
				i = 10;
				do {
					fcn_00401280(stream, cursor - 0x0c);
					fcn_00401280(stream, cursor);
					cursor += 0x18;
					i--;
				} while (i != 0);
			}
			break;
		case 0:
			fcn_00401180(stream, &b);
			object[0x214] = (char) ((object[0x214] & ~0x40) | ((b << 6) & 0x40));
			if (version < 0x3a6c00a0u) {
				object[0x214] = (char) (object[0x214] | 0x40);
			}
			fcn_004011d0(stream, object + 0x68);
			fcn_00401280(stream, object + 0x4c);
			fcn_00401280(stream, object + 0x5c);
			fcn_00401280(stream, object + 0x90);
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			fcn_00401180(stream, &b);
			if (version >= 0x3a6c00a8u) {
				scratch = fcn_00446ca0(version);
				if (version >= 0x3a6c00a9u) {
					fcn_00401180(stream, &b);
					object[0x215] = (char) ((object[0x215] & ~0x04) | ((b << 2) & 0x04));
				}
				fcn_004011d0(stream, object + 0x90);
				fcn_004011d0(stream, object + 0x94);
				fcn_004011d0(stream, object + 0x98);
				fcn_00401280(stream, object + 0x5c);
				fcn_00401280(stream, object + 0x4c);
				fcn_00401280(stream, object + 0x84);
				if (version >= 0x3a6c00acu) {
					lights = *(char**) (object + 0x1e8);
					fcn_004011d0(stream, lights + 0x198);
					fcn_004011f0(stream, lights + 0x19c);
				}
				aux_b = 0;
				if (scratch > 0) {
					aux_b = scratch;
					scratch2 = scratch;
					off = 0;
					do {
						lights = *(char**) (object + 0x1e8);
						fcn_004011d0(stream, lights + off + 0x28);
						lights = *(char**) (object + 0x1e8);
						fcn_004011d0(stream, lights + off + 0x24);
						lights = *(char**) (object + 0x1e8);
						fcn_004011d0(stream, lights + off + 0x2c);
						lights = *(char**) (object + 0x1e8);
						fcn_00401280(stream, lights + off + 0x18);
						lights = *(char**) (object + 0x1e8);
						fcn_00401280(stream, lights + off);
						lights = *(char**) (object + 0x1e8);
						fcn_00401280(stream, lights + off + 0x0c);
						if (version >= 0x3a6c00acu) {
							lights = *(char**) (object + 0x1e8);
							fcn_004011d0(stream, lights + off + 0x30);
							lights = *(char**) (object + 0x1e8);
							fcn_004011f0(stream, lights + off + 0x34);
						}
						off += 0x38;
						scratch2--;
					} while (scratch2 != 0);
				}
				if (scratch < 7) {
					for (i = aux_b; i < 7; i++) {
						lights = *(char**) (object + 0x1e8);
						RD_COPY_NINE(lights + i * 0x38, lights + (scratch - 1) * 0x38);
					}
				}
			} else {
				fcn_004011d0(stream, object + 0x84);
				fcn_004011d0(stream, object + 0x88);
				if (version >= 0x3a6c000cu) {
					fcn_004011d0(stream, object + 0x8c);
				} else {
					*(int*) (object + 0x8c) = 0x3f800000;
				}
				*(int*) (object + 0x90) = *(int*) (object + 0x84);
				*(int*) (object + 0x94) = *(int*) (object + 0x88);
				*(int*) (object + 0x98) = *(int*) (object + 0x8c);
				*(int*) (object + 0x84) = 0;
				*(int*) (object + 0x88) = 0;
				*(int*) (object + 0x8c) = 0;
				fcn_00401280(stream, object + 0x5c);
				fcn_00401280(stream, object + 0x4c);
				if (version >= 0x3a6c00a1u) {
					scratch = fcn_00446ca0(version);
					aux_b = 0;
					if (scratch > 0) {
						aux_b = scratch;
						scratch2 = scratch;
						off = 0;
						do {
							lights = *(char**) (object + 0x1e8);
							fcn_004011d0(stream, lights + off + 0x28);
							lights = *(char**) (object + 0x1e8);
							fcn_004011d0(stream, lights + off + 0x24);
							lights = *(char**) (object + 0x1e8);
							fcn_004011d0(stream, lights + off + 0x2c);
							lights = *(char**) (object + 0x1e8);
							fcn_00401280(stream, lights + off + 0x18);
							lights = *(char**) (object + 0x1e8);
							fcn_00401280(stream, lights + off);
							off += 0x38;
							scratch2--;
						} while (scratch2 != 0);
					}
					if (scratch < 7) {
						for (i = aux_b; i < 7; i++) {
							lights = *(char**) (object + 0x1e8);
							RD_COPY_NINE(lights + i * 0x38, lights + (scratch - 1) * 0x38);
						}
					}
				} else {
					lights = *(char**) (object + 0x1e8);
					off = 0;
					while (off < 0x188) {
						*(int*) (lights + off + 0x28) = *(int*) (object + 0x90);
						*(int*) (lights + off + 0x24) = *(int*) (object + 0x94);
						*(int*) (lights + off + 0x2c) = *(int*) (object + 0x98);
						*(int*) (lights + off + 0x00) = *(int*) (object + 0x4c);
						*(int*) (lights + off + 0x04) = *(int*) (object + 0x50);
						*(int*) (lights + off + 0x08) = *(int*) (object + 0x54);
						*(int*) (lights + off + 0x18) = *(int*) (object + 0x5c);
						*(int*) (lights + off + 0x1c) = *(int*) (object + 0x60);
						*(int*) (lights + off + 0x20) = *(int*) (object + 0x64);
						*(int*) (lights + off + 0x0c) = *(int*) (object + 0x90);
						*(int*) (lights + off + 0x10) = *(int*) (object + 0x94);
						*(int*) (lights + off + 0x14) = *(int*) (object + 0x98);
						off += 0x38;
					}
				}
			}
			break;
		default:
			fcn_0041d9e0("Unkown Object-Type in rd_object()!");
			break;
		}
		fcn_00438cb0(object, object + 0x84);
		fcn_00438b40(object, object + 0x4c);
		object[0x214] = (char) (object[0x214] | 0x80);
		if (marker != 0) {
			fcn_00442c00(object, 0);
			if (object[0] != '!') {
				strcpy(tmp, object);
				strcpy(object, "!");
				strcat(object, tmp);
			}
		}
	} else {
		object = fcn_00439750(1, "STRANGEFUCK");
		*(char**) (object + 0x1fc) = parent;
		if (parent != 0) {
			object[0x214] = (char) (object[0x214] & 0xfe);
		}
		placeholder = 1;
		object[0x214] = (char) (object[0x214] & 0x7f);
	}
	fcn_00401180(stream, &b);
	if (b != 0) {
		fcn_00439c00(object, rd_object(stream, object, version, resources));
	}
	if (*(char**) (object + 0x1fc) == 0 && placeholder == 0) {
		fcn_00439aa0(object);
	}
	fcn_00401180(stream, &sibling);
	if (sibling != 0) {
		fcn_00439ba0(object, rd_object(stream, parent, version, resources));
	}
	if (b == 0 && sibling == 0 && placeholder == 1) {
		m_FreeTracked(object);
		object = 0;
	} else if (placeholder != 0) {
		fcn_00439aa0(object);
	}
	if (version >= 0x3a6c00a7u) {
		fcn_0043b7b0(stream, object);
	}
	if (object != 0) {
		if (*(int*) (object + 0x218) == 0 || *(int*) (object + 0x220) == 4 || *(int*) (object + 0x220) == 3 || *(int*) (object + 0x220) == 2) {
			*(int*) (object + 0x224) = -1;
		} else {
			*(int*) (object + 0x224) = 0;
		}
		if (resources != 0 && *(char**) (object + 0x1ec) != 0) {
			off = 0;
			while (off < 0xdec) {
				draw = *(char**) (object + 0x1ec);
				cursor = *(char**) (draw + off + 0x40c);
				if (cursor != 0) {
					lights = *(char**) (draw + off + 0x410);
					if (lights != 0) {
						scratch = *(int*) (cursor + 0x1e4);
						i = 0;
						while (i < scratch) {
							if (*(char**) (lights + i * 4) != 0) {
								fcn_0045ce90(*(char**) (lights + i * 4));
							}
							i++;
						}
					}
				}
				off += 0x4a4;
			}
		}
	}
	}
	return object;
}
