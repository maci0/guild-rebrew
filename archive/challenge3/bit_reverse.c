/*
 * bit_reverse from server.dll (Die Gilde AddOn Server)
 * VA 0x10008880, 31 bytes
 *
 * Origin: zlib 1.1.3 trees.c bi_reverse() — statically linked into server.dll.
 * Renamed from bi_reverse to bit_reverse, changed from K&R to ANSI style,
 * removed 'local' (static) and 'register' keywords. Algorithm is identical.
 *
 * Reverses the lowest 'nbits' bits of 'value'.
 * Used in deflate/Huffman coding (canonical code reversal).
 *
 * Compiled with: /O2 /Gd (maximize speed, __cdecl)
 * Result: 31/31 bytes, exact byte-for-byte match
 *
 * Key insight: server.dll app code uses /O2 not /O1.
 * /O2 keeps both params in registers (edx=nbits, ecx=value)
 * and uses esi as scratch (push/pop around function).
 * /O1 avoids push/pop overhead but shifts memory directly.
 * do-while loop produces bottom-tested jg (no initial check).
 */

unsigned int __cdecl bit_reverse(unsigned int value, int nbits)
{
    unsigned int result = 0;

    do {
        result |= (value & 1);
        value >>= 1;
        result <<= 1;
    } while (--nbits > 0);

    result >>= 1;
    return result;
}
