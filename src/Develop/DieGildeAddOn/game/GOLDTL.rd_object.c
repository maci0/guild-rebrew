#include <stdio.h>
#include <string.h>

int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* dst);
int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
void __cdecl fcn_00401280(void* stream, void* dst);
void __cdecl ReportClientMessage(const char* msg);
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

extern unsigned char g_6b85a4;

#define RD_DRAW(o) (*(char**) ((o) + 0x1ec))
#define RD_LIGHTS(o) (*(char**) ((o) + 0x1e8))

#define RD_LIGHT_NINE(dst, src) \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x28) = *(int*) (RD_LIGHTS(object) + (src) + 0x28); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x24) = *(int*) (RD_LIGHTS(object) + (src) + 0x24); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x2c) = *(int*) (RD_LIGHTS(object) + (src) + 0x2c); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x18) = *(int*) (RD_LIGHTS(object) + (src) + 0x18); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x1c) = *(int*) (RD_LIGHTS(object) + (src) + 0x1c); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x20) = *(int*) (RD_LIGHTS(object) + (src) + 0x20); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x00) = *(int*) (RD_LIGHTS(object) + (src) + 0x00); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x04) = *(int*) (RD_LIGHTS(object) + (src) + 0x04); \
	*(int*) (RD_LIGHTS(object) + (dst) + 0x08) = *(int*) (RD_LIGHTS(object) + (src) + 0x08);

/* ADDRESS: GOLDTL 0x00447110 */
char* __cdecl rd_object(void* stream, char* parent, unsigned int version, unsigned char resources)
{
	unsigned char b;
	unsigned char placeholder;
	unsigned char marker;
	unsigned char sibling;
	int type;
	int aux_a;
	int aux_b;
	int start;
	int left;
	char name[256];
	char tmp[256];
	char* object;
	char* lights;
	int kind;
	int i;
	int off;
	int count;

	object = 0;
	placeholder = 0;
	aux_b = 0;
	aux_a = 0;
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
		if (version < 0x3a6c00a6u) {
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
				kind = 4;
				break;
			case 4:
				kind = 5;
				break;
			case 5:
				kind = 6;
				break;
			case 6:
				kind = 7;
				break;
			case 7:
				kind = 8;
				break;
			case 8:
				kind = 2;
				break;
			default:
				kind = 2;
				break;
			}
		} else {
			kind = type;
			fcn_00401180(stream, &marker);
			if (name[0] == '!' && marker == 0) {
				strcpy(tmp, name + 1);
				strcpy(name, tmp);
			}
		}
		object = fcn_00439750(kind, name);
		kind = *(int*) (object + 0x218);
		*(int*) (object + 0x204) = aux_a;
		*(int*) (object + 0x220) = aux_b;
		*(char**) (object + 0x1fc) = parent;
		if (parent != 0) {
			object[0x214] = (char) (object[0x214] & 0xfe);
		}
		switch (kind) {
		case 1:
		case 4:
			fcn_00401180(stream, &b);
			object[0x214] = (char) ((object[0x214] & ~0x20) | ((b << 5) & 0x20));
			fcn_00401180(stream, &b);
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
				if (RD_DRAW(object) == 0) {
					fcn_00439fa0(object);
				}
				for (i = 0; i < type; i++) {
					fcn_004011a0(stream, name);
					fcn_0044c200(name, name);
					fcn_00449f90(object, RD_DRAW(object) + i * 0x4a4 + 0xf4, name);
				}
				if (version >= 0x3a6c00a3u) {
					fcn_00401180(stream, &b);
					if (b != 0) {
						fcn_004011a0(stream, name);
						fcn_0044c200(name, name);
						fcn_00449f90(object, RD_DRAW(object) + 0xee0, name);
					}
				} else {
					if (*(char**) (RD_DRAW(object) + 0x40c) != 0) {
						strcpy(name, *(char**) (RD_DRAW(object) + 0x40c));
						strcat(name, "_s");
						if (fcn_0044c200(name, name) != 0) {
							fcn_00449f90(object, RD_DRAW(object) + 0xee0, name);
						}
					}
				}
			}
			/* FALLTHROUGH */
		case 2:
		case 3:
			fcn_00401280(stream, object + 0x4c);
			fcn_00401280(stream, object + 0x84);
			fcn_00401180(stream, &b);
			object[0x214] = (char) ((object[0x214] & ~0x40) | ((b << 6) & 0x40));
			if (b != 0) {
				fcn_00401280(stream, object + 0x5c);
				fcn_00401280(stream, object + 0x90);
			}
			if (version >= 0x3a6c00afu) {
				for (i = 0, lights = object + 0xa8; i < 10; i++) {
					fcn_00401280(stream, lights - 0x0c);
					fcn_00401280(stream, lights);
					lights += 0x18;
				}
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
				count = fcn_00446ca0(version);
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
					fcn_004011d0(stream, RD_LIGHTS(object) + 0x198);
					fcn_004011f0(stream, RD_LIGHTS(object) + 0x19c);
				}
				start = 0;
				if (count > 0) {
					off = 0;
					left = count;
					start = count;
					for (; left != 0; left--) {
						fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x28);
						fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x24);
						fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x2c);
						fcn_00401280(stream, RD_LIGHTS(object) + off + 0x18);
						fcn_00401280(stream, RD_LIGHTS(object) + off);
						fcn_00401280(stream, RD_LIGHTS(object) + off + 0x0c);
						if (version >= 0x3a6c00acu) {
							fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x30);
							fcn_004011f0(stream, RD_LIGHTS(object) + off + 0x34);
						}
						off += 0x38;
					}
				}
				if (start < 7) {
					for (i = start; i < 7; i++) {
						RD_LIGHT_NINE(i * 0x38, (count - 1) * 0x38)
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
					count = fcn_00446ca0(version);
					start = 0;
					if (count > 0) {
						off = 0;
						left = count;
						start = count;
						for (; left != 0; left--) {
							fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x28);
							fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x24);
							fcn_004011d0(stream, RD_LIGHTS(object) + off + 0x2c);
							fcn_00401280(stream, RD_LIGHTS(object) + off + 0x18);
							fcn_00401280(stream, RD_LIGHTS(object) + off);
							off += 0x38;
						}
					}
					if (start < 7) {
						for (i = start; i < 7; i++) {
							RD_LIGHT_NINE(i * 0x38, (count - 1) * 0x38)
						}
					}
				} else {
					for (off = 0; off < 0x188; off += 0x38) {
						*(int*) (off + RD_LIGHTS(object) + 0x28) = *(int*) (object + 0x90);
						*(int*) (off + RD_LIGHTS(object) + 0x24) = *(int*) (object + 0x94);
						*(int*) (off + RD_LIGHTS(object) + 0x2c) = *(int*) (object + 0x98);
						*(int*) (off + RD_LIGHTS(object) + 0x00) = *(int*) (object + 0x4c);
						*(int*) (off + RD_LIGHTS(object) + 0x04) = *(int*) (object + 0x50);
						*(int*) (off + RD_LIGHTS(object) + 0x08) = *(int*) (object + 0x54);
						*(int*) (off + RD_LIGHTS(object) + 0x18) = *(int*) (object + 0x5c);
						*(int*) (off + RD_LIGHTS(object) + 0x1c) = *(int*) (object + 0x60);
						*(int*) (off + RD_LIGHTS(object) + 0x20) = *(int*) (object + 0x64);
						*(int*) (off + RD_LIGHTS(object) + 0x0c) = *(int*) (object + 0x90);
						*(int*) (off + RD_LIGHTS(object) + 0x10) = *(int*) (object + 0x94);
						*(int*) (off + RD_LIGHTS(object) + 0x14) = *(int*) (object + 0x98);
					}
				}
			}
			break;
		default:
			ReportClientMessage("Unkown Object-Type in rd_object()!");
			break;
		}
		fcn_00438cb0(object, object + 0x84);
		fcn_00438b40(object, object + 0x4c);
		object[0x214] = (char) (object[0x214] | 0x80);
		if (marker != 0) {
			fcn_00442c00(object, 0);
			if (object[0] != '!') {
				strcpy(name, object);
				strcpy(object, "!");
				strcat(object, name);
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
		if (*(int*) (object + 0x218) != 0 && *(int*) (object + 0x220) != 4 && *(int*) (object + 0x220) != 3 && *(int*) (object + 0x220) != 2) {
			*(int*) (object + 0x224) = 0;
		} else {
			*(int*) (object + 0x224) = -1;
		}
		if (resources != 0 && RD_DRAW(object) != 0) {
			for (off = 0; off < 0xdec; off += 0x4a4) {
				char* entries;
				if (*(char**) (RD_DRAW(object) + off + 0x40c) != 0) {
					entries = *(char**) (RD_DRAW(object) + off + 0x410);
					if (entries != 0) {
						count = *(int*) (*(char**) (RD_DRAW(object) + off + 0x40c) + 0x1e4);
						for (type = 0; type < count; type++) {
							if (*(char**) (entries + type * 4) != 0) {
								fcn_0045ce90(*(char**) (entries + type * 4));
							}
						}
					}
				}
			}
		}
	}
	}
	return object;
}
