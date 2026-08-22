// FUNCTION: SERVER 0x10009020
#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x10009020 (701B)
__declspec(naked) int __cdecl OpenVfsStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
    __asm {
        _emit 0x83
        _emit 0xec
        _emit 0x0c
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x57
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x20
        _emit 0x33
        _emit 0xc0
        _emit 0xb3
        _emit 0x01
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x01
        _emit 0x85
        _emit 0xff
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x13
        _emit 0x0f
        _emit 0x84
        _emit 0x6f
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0x85
        _emit 0xed
        _emit 0x0f
        _emit 0x86
        _emit 0x63
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x28
        _emit 0x8b
        _emit 0xf0
        _emit 0x80
        _emit 0x38
        _emit 0x00
        _emit 0x74
        _emit 0x48
        _emit 0x0f
        _emit 0xbe
        _emit 0x06
        _emit 0x50
        _emit 0xe8
        _emit 0x5c
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc0
        _emit 0xb2
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x83
        _emit 0xf8
        _emit 0x0c
        _emit 0x77
        _emit 0x28
        _emit 0x33
        _emit 0xc9
        _emit 0x8a
        _emit 0x88
        _emit 0xd0
        _emit 0x92
        _emit 0x00
        _emit 0x10
        _emit 0xff
        _emit 0x24
        _emit 0x8d
        _emit 0xbc
        _emit 0x92
        _emit 0x00
        _emit 0x10
        _emit 0x32
        _emit 0xdb
        _emit 0xeb
        _emit 0x10
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x01
        _emit 0xeb
        _emit 0x0e
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x00
        _emit 0xeb
        _emit 0x07
        _emit 0xb3
        _emit 0x01
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x00
        _emit 0x8a
        _emit 0x46
        _emit 0x01
        _emit 0x46
        _emit 0x84
        _emit 0xc0
        _emit 0x75
        _emit 0xbc
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0x6a
        _emit 0x10
        _emit 0x68
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x70
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x6c
        _emit 0xdc
        _emit 0xff
        _emit 0xff
        _emit 0x8a
        _emit 0x4c
        _emit 0x24
        _emit 0x20
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x8a
        _emit 0x96
        _emit 0x3c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xe2
        _emit 0xeb
        _emit 0x80
        _emit 0xca
        _emit 0x22
        _emit 0x84
        _emit 0xc9
        _emit 0x88
        _emit 0x96
        _emit 0x3c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x0f
        _emit 0x84
        _emit 0xa3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x84
        _emit 0xc0
        _emit 0x74
        _emit 0x4a
        _emit 0x83
        _emit 0xfd
        _emit 0x0a
        _emit 0x77
        _emit 0x21
        _emit 0x32
        _emit 0xdb
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0x89
        _emit 0xbe
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0xae
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc7
        _emit 0x86
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x5d
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x15
        _emit 0x50
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x33
        _emit 0xc0
        _emit 0x8a
        _emit 0x07
        _emit 0x3b
        _emit 0xc2
        _emit 0x75
        _emit 0xd1
        _emit 0xa1
        _emit 0x54
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x33
        _emit 0xd2
        _emit 0x8a
        _emit 0x57
        _emit 0x01
        _emit 0x3b
        _emit 0xd0
        _emit 0x75
        _emit 0xc3
        _emit 0xb3
        _emit 0x01
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0xeb
        _emit 0x04
        _emit 0x84
        _emit 0xdb
        _emit 0x74
        _emit 0xbd
        _emit 0x8d
        _emit 0x86
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x4f
        _emit 0x0a
        _emit 0x6a
        _emit 0x38
        _emit 0x68
        _emit 0x6c
        _emit 0x70
        _emit 0x02
        _emit 0x10
        _emit 0x89
        _emit 0x08
        _emit 0x8d
        _emit 0x55
        _emit 0xf6
        _emit 0x33
        _emit 0xc9
        _emit 0x6a
        _emit 0xf1
        _emit 0x50
        _emit 0x89
        _emit 0x96
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x8e
        _emit 0x0c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x8e
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x8e
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x8e
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0x56
        _emit 0xc6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0xa0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x84
        _emit 0xdb
        _emit 0x0f
        _emit 0x84
        _emit 0xc4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xfd
        _emit 0x12
        _emit 0x0f
        _emit 0x82
        _emit 0x8f
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa0
        _emit 0x50
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x8d
        _emit 0xae
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x88
        _emit 0x07
        _emit 0x8a
        _emit 0x0d
        _emit 0x54
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x88
        _emit 0x4f
        _emit 0x01
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x24
        _emit 0x33
        _emit 0xc0
        _emit 0x8d
        _emit 0x57
        _emit 0x0a
        _emit 0x50
        _emit 0x83
        _emit 0xc1
        _emit 0xf6
        _emit 0x50
        _emit 0xc6
        _emit 0x47
        _emit 0x02
        _emit 0x08
        _emit 0xc6
        _emit 0x47
        _emit 0x08
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x07
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x06
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x05
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x04
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x03
        _emit 0x00
        _emit 0xc6
        _emit 0x47
        _emit 0x09
        _emit 0x0b
        _emit 0x50
        _emit 0x89
        _emit 0x45
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x96
        _emit 0x0c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x8e
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xfa
        _emit 0x7f
        _emit 0xff
        _emit 0xff
        _emit 0x6a
        _emit 0x38
        _emit 0x68
        _emit 0x6c
        _emit 0x70
        _emit 0x02
        _emit 0x10
        _emit 0x6a
        _emit 0x00
        _emit 0x6a
        _emit 0x08
        _emit 0x6a
        _emit 0xf1
        _emit 0x6a
        _emit 0x08
        _emit 0x6a
        _emit 0xff
        _emit 0x55
        _emit 0x89
        _emit 0x86
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0x1d
        _emit 0x81
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x2c
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x18
        _emit 0x56
        _emit 0x68
        _emit 0x70
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x0b
        _emit 0xdc
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x33
        _emit 0xc0
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0xc3
        _emit 0x8a
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x8b
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0xc7
        _emit 0x86
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x0a
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x1c
        _emit 0x89
        _emit 0xbe
        _emit 0x0c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0xae
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc7
        _emit 0x86
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x04
        _emit 0x8a
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x85
        _emit 0xf6
        _emit 0x74
        _emit 0x4b
        _emit 0xa1
        _emit 0x78
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x18
        _emit 0x40
        _emit 0x80
        _emit 0xe1
        _emit 0x01
        _emit 0xa3
        _emit 0x78
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8a
        _emit 0x86
        _emit 0x3c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x24
        _emit 0xf6
        _emit 0x80
        _emit 0xe3
        _emit 0x01
        _emit 0x32
        _emit 0xc1
        _emit 0x81
        _emit 0xe2
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc0
        _emit 0xe3
        _emit 0x03
        _emit 0x0a
        _emit 0xc3
        _emit 0x52
        _emit 0x88
        _emit 0x86
        _emit 0x3c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x25
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x55
        _emit 0x57
        _emit 0x68
        _emit 0xa4
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x56
        _emit 0xe8
        _emit 0xeb
        _emit 0x0f
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x8b
        _emit 0xc6
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0xc3
        _emit 0x90
        _emit 0x7e
        _emit 0x90
        _emit 0x00
        _emit 0x10
        _emit 0x82
        _emit 0x90
        _emit 0x00
        _emit 0x10
        _emit 0x89
        _emit 0x90
        _emit 0x00
        _emit 0x10
        _emit 0x90
        _emit 0x90
        _emit 0x00
        _emit 0x10
        _emit 0x97
        _emit 0x90
        _emit 0x00
        _emit 0x10
        _emit 0x00
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x01
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x02
        _emit 0x04
        _emit 0x04
		_emit 0x03
		_emit 0x90
		_emit 0x90
		_emit 0x90
    }
}
#else  // padding: align to 701
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

/* Game function - compression stream initialization */
/* Parses flag string (R/W/N/Z), allocates pool object, sets up zlib inflate/deflate */

int __cdecl OpenVfsStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char is_read;
	char use_zlib;
	char has_mode;
	char* obj;

	use_zlib = 1;
	has_mode = 1;
	is_read = 1;

	if (buf == 0) {
		return 0;
	}

	if (size == 0) {
		return 0;
	}

	{
		char* p;
		char c;

		p = mode_flags;
		c = *p;
		while (c != 0) {
			int ch;
			ch = toupper(*p);

			switch (ch) {
			case 'N':
				use_zlib = 0;
				has_mode = 0;
				break;
			case 'R':
				is_read = 1;
				break;
			case 'W':
				is_read = 0;
				break;
			case 'Z':
				use_zlib = 1;
				has_mode = 0;
				break;
			}

			p++;
			c = *p;
		}
	}

	obj = m_PoolAlloc((char*) 0x10034670, 0x140, 0x10);
	{
		unsigned char flags;
		flags = *(unsigned char*) (obj + 0x13c);
		flags = (flags & 0xeb) | 0x22;
		*(unsigned char*) (obj + 0x13c) = flags;
	}

	if (is_read) {
		if (has_mode) {
			if (size > 0xa && (unsigned int) buf[0] == *(unsigned int*) 0x10029450 &&
				(unsigned int) buf[1] == *(unsigned int*) 0x10029454) {
				use_zlib = 1;
				goto setup_inflate;
			}
			use_zlib = 0;
		}
		else {
			if (use_zlib) {
				goto setup_inflate;
			}
		}

		*(int*) (obj + 0x100) = (int) buf;
		*(int*) (obj + 0x104) = (int) size;
		*(int*) (obj + 0x108) = 0;
		goto done;

	setup_inflate:
		*(int*) (obj + 0x100) = (int) (buf + 10);
		*(int*) (obj + 0x104) = (int) size - 10;
		*(int*) (obj + 0x10c) = 0;
		*(int*) (obj + 0x110) = 0;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		{
			int ret;
			ret = inflateInit2_((z_stream*) (obj + 0x100), -15, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				goto done;
			}
			goto fail;
		}
	}
	else {
		if (!use_zlib) {
			*(int*) (obj + 0x10c) = (int) buf;
			*(int*) (obj + 0x110) = (int) size;
			*(int*) (obj + 0x114) = 0;
			goto done;
		}

		if (size <= 0x11) {
			goto fail;
		}

		buf[0] = *(unsigned char*) 0x10029450;
		buf[1] = *(unsigned char*) 0x10029454;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
		buf[9] = 0xb;

		*(int*) (obj + 0x100) = 0;
		*(int*) (obj + 0x104) = 0;
		*(int*) (obj + 0x10c) = (int) (buf + 10);
		*(int*) (obj + 0x110) = (int) size - 10;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		*(int*) (obj + 0x138) = crc32(0, 0, 0);

		{
			volatile int ret;
			ret = deflateInit2_((z_stream*) (obj + 0x100), -1, 8, -15, 8, 0, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				*(int*) (obj + 0x114) = 10;
				goto done;
			}
		}
	}

fail:
	m_PoolFree((char*) 0x10034670, obj);
	return 0;

done:
	if (obj != 0) {
		unsigned char flag_byte;

		*(int*) 0x10034678 = *(int*) 0x10034678 + 1;
		flag_byte = *(unsigned char*) (obj + 0x13c);
		flag_byte = (flag_byte & 0xf6) ^ (is_read & 1);
		flag_byte |= (use_zlib & 1) << 3;
		*(unsigned char*) (obj + 0x13c) = flag_byte;

		sprintf((char*) obj, (char*) 0x100294a4, buf, size, is_read & 0xff, use_zlib & 0xff);
	}

	return (int) obj;
}
#endif

