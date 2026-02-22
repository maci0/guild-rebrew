/*
 * _fassign from MSVC6 CRT (cvt.c / cvt.obj in LIBCMT.LIB)
 * Target function from server.dll at VA 0x1001f2cb (62 bytes)
 *
 * Dispatches float/double string-to-FP conversion for scanf:
 *   flag != 0 => double: _atodbl(&local_dbl, number), copy 8 bytes to argument
 *   flag == 0 => float:  _atoflt(&local_flt, number), copy 4 bytes to argument
 *
 * Called as: _fassign(longone-1, pointer, floatstring) from INPUT.C
 * Registered as _cfltcvt_tab[2] function pointer.
 *
 * Key insight: both paths use LOCAL struct variables (not &number reuse).
 * Using a local FLOAT for the float path produces correct register allocation
 * (argument in eax, value in ecx) matching the original cvt.obj.
 *
 * Compiled with: /O1 /Oy- /MT /Gd
 * Result: 62/62 bytes, bit-perfect .obj match with cvt.obj from LIBCMT.LIB
 */

typedef struct {
    double x;
} DOUBLE;

typedef struct {
    float f;
} FLOAT;

int __cdecl _atodbl(DOUBLE *, char *);
int __cdecl _atoflt(FLOAT *, char *);

void __cdecl _fassign(int flag, char *argument, char *number)
{
    DOUBLE dbl;
    FLOAT flt;

    if (flag) {
        _atodbl(&dbl, number);
        *(DOUBLE *)argument = dbl;
    } else {
        _atoflt(&flt, number);
        *(FLOAT *)argument = flt;
    }
}
