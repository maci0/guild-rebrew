/* Locks, clears and re-creates the render surfaces of the 64 tile records
 * that start at object offset 0x244, then flushes the tile cache. */

#include <string.h>

extern char* g_6b5de0;
extern int d3_LastReleaseRefCount;

void __cdecl d3_UpdateFloorLighting(char* a0);
long __stdcall D3DXCreateMeshFVF(int a0, int a1, int a2, int a3, char* a4, char* a5);

/* ADDRESS: GOLDTL 0x0043b990 */
/* ADDRESS: GOLDDE 0x00434740 */
void __cdecl d3_RebuildFloorMeshes(char* terrainObject)
{
	char* rec;
	char* start;
	char* q;
	char* srf2;
	void* buf;
	int i;
	int j;
	int k;
	int n;
	int m;

	start = terrainObject + 0x244;
	i = 8;
	do {
		rec = start;
		j = 8;
		do {
			if (*(unsigned char*) (rec + 0x18) != 0
			    && *(int*) rec == 0) {
				(*(void (__stdcall**)(void*, int, int, int, int, void*))
				    (*(int*) g_6b5de0 + 0x5c))
				    (g_6b5de0, *(int*) (rec + 8) * 6 * 4,
				    0x208, 0x142, 0, rec);
			}
			q = rec - 0x190;
			k = 8;
			do {
				n = *(int*) q;
				if (n != 0) {
					d3_LastReleaseRefCount = (*(int (__stdcall**)(int))
					    (*(int*) n + 8))(n);
					*(int*) q = 0;
				}
				n = *(int*) (q + 0x18);
				if ((unsigned int) n > 0) {
					m = *(int*) (q + 0xc);
					if ((unsigned int) m > 0) {
						D3DXCreateMeshFVF(n, m, 0x6c0, 0x142,
						    g_6b5de0, q);

						(*(void (__stdcall**)(void*, int, void**))
						    (*(int*) *(int*) q + 0x40))
						    (*(void**) q, 0, &buf);
						{
							int copy_count;
							void* copy_src;

							copy_count = *(int*) (q + 0x18) * 6;
							copy_src = *(void**) (q - 8);
							__asm {
								mov edi, buf
								mov esi, copy_src
								mov ebx, copy_count
								lea ecx, [edi+edi*2]
								and ecx, 3
								sub ebx, ecx
								jle short L_copy_0x18_6
								rep movsb
								mov ecx, ebx
								and ebx, 3
								shr ecx, 2
								rep movsd
							L_copy_0x18_6:
								add ecx, ebx
								rep movsb
							}
						}
						(*(void (__stdcall**)(void*))
						    (*(int*) *(int*) q + 0x44))
						    (*(void**) q);
					}
				}
				srf2 = q + 4;
				if (*(int*) srf2 != 0) {
					d3_LastReleaseRefCount = (*(int (__stdcall**)(int))
					    (*(int*) *(int*) srf2 + 8))
					    (*(int*) srf2);
					*(int*) srf2 = 0;
				}
				n = *(int*) (q + 0x1c);
				if ((unsigned int) n > 0) {
					m = *(int*) (q + 0x10);
					if ((unsigned int) m > 0) {
						D3DXCreateMeshFVF(n, m, 0x6c0, 0x142,
						    g_6b5de0, srf2);

						(*(void (__stdcall**)(void*, int, void**))
						    (*(int*) *(int*) srf2 + 0x40))
						    (*(void**) srf2, 0, &buf);
						{
							int copy_count;
							void* copy_src;

							copy_count = *(int*) (q + 0x1c) * 6;
							copy_src = *(void**) (q - 4);
							__asm {
								mov edi, buf
								mov esi, copy_src
								mov ebx, copy_count
								lea ecx, [edi+edi*2]
								and ecx, 3
								sub ebx, ecx
								jle short L_copy_0x1c_6
								rep movsb
								mov ecx, ebx
								and ebx, 3
								shr ecx, 2
								rep movsd
							L_copy_0x1c_6:
								add ecx, ebx
								rep movsb
							}
						}
						(*(void (__stdcall**)(void*))
						    (*(int*) *(int*) srf2 + 0x44))
						    (*(void**) srf2);
						if (*(int*) (q - 0x14) != 0) {
							void* buf2;

							(*(void (__stdcall**)(void*, int, void**))
							    (*(int*) *(int*) srf2 + 0x58))
							    (*(void**) srf2, 0x2000, &buf2);
							{
								int copy_count;
								void* copy_src;

								copy_count = *(int*) (q + 0x1c) * 4;
								copy_src = *(void**) (q - 0x14);
								__asm {
									mov edi, buf2
									mov esi, copy_src
									mov ebx, copy_count
									lea ecx, [edi+edi*2]
									and ecx, 3
									sub ebx, ecx
									jle short L_copy_0x1c_4
									rep movsb
									mov ecx, ebx
									and ebx, 3
									shr ecx, 2
									rep movsd
								L_copy_0x1c_4:
									add ecx, ebx
									rep movsb
								}
							}
							(*(void (__stdcall**)(void*))
							    (*(int*) *(int*) srf2 + 0x5c))
							    (*(void**) srf2);
						}
					}
				}
				q += 0x34;
			} while (--k);
			rec += 0x1f4;
		} while (--j);
		start = rec;
	} while (--i);
	d3_UpdateFloorLighting(terrainObject);
}
