/* Sprite and mask blitter, hand-written assembly. The compiler supplies the
 * frame (push ebp; mov ebp,esp; push ebx/esi/edi at entry, pop edi/esi/ebx/ebp;
 * ret at exit), so the __asm block covers the native body from 0x47a326 to
 * 0x47a564 only. Instructions whose operands are absolute data addresses are
 * emitted as their exact native bytes: MASM cannot encode an absolute memory
 * operand without a segment prefix or a relocation, and either one changes the
 * bytes. Four arguments are read from [ebp+8..0x14] by the block. */
/* ADDRESS: GOLDTL 0x0047a320 */
void __cdecl fcn_0047a320(int a, int b, int c, int d)
{
	__asm {
		push edi
		push esi
		push eax
		push ebx
		push edx
		push ecx
		push ebp
		mov eax, dword ptr [ebp+8]
		mov edx, dword ptr [ebp+0CH]
		mov ebx, dword ptr [ebp+10H]
		mov ecx, dword ptr [ebp+14H]
		mov edi, ebx
		mov esi, ecx
		shl eax, 1
		xor ecx, ecx
		mov ebx, edx
		mov cx, word ptr [esi+0AH]
		add ebx, ecx
		_emit 03BH
		_emit 01DH
		_emit 0FCH
		_emit 025H
		_emit 077H
		_emit 000H
		jle L_47A55E
		_emit 03BH
		_emit 015H
		_emit 068H
		_emit 0D9H
		_emit 067H
		_emit 000H
		jge L_47A55E
		push edx
		_emit 08BH
		_emit 02DH
		_emit 06CH
		_emit 0D9H
		_emit 067H
		_emit 000H
		sub bp, word ptr [esi+6]
		shl ebp, 1
		_emit 089H
		_emit 02DH
		_emit 060H
		_emit 0EBH
		_emit 000H
		_emit 001H
		xor ebx, ebx
		mov bx, word ptr [esi+0AH]
		_emit 089H
		_emit 01DH
		_emit 068H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 0C7H
		_emit 005H
		_emit 064H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 032H
		_emit 000H
		_emit 000H
		_emit 000H
		add edi, eax
		mov ebx, edx
		_emit 08BH
		_emit 00DH
		_emit 0FCH
		_emit 025H
		_emit 077H
		_emit 000H
		sub ecx, ebx
		cmp ecx, 0
		jle L_47A3B5
		mov eax, esi
		add eax, dword ptr [esi+2AH]
		mov edx, dword ptr [eax+ecx*4]
		_emit 089H
		_emit 015H
		_emit 064H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 029H
		_emit 00DH
		_emit 068H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 08BH
		_emit 01DH
		_emit 0FCH
		_emit 025H
		_emit 077H
		_emit 000H
L_47A3B5:
		_emit 08BH
		_emit 00DH
		_emit 068H
		_emit 0D9H
		_emit 067H
		_emit 000H
		pop edx
		mov eax, edx
		add ax, word ptr [esi+0AH]
		sub eax, ecx
		jle L_47A3D9
		_emit 029H
		_emit 005H
		_emit 068H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 083H
		_emit 03DH
		_emit 068H
		_emit 0EBH
		_emit 000H
		_emit 001H
		_emit 000H
		jle L_47A55E
L_47A3D9:
		_emit 0A1H
		_emit 06CH
		_emit 0D9H
		_emit 067H
		_emit 000H
		shl eax, 1
		mul ebx
		add edi, eax
		_emit 08BH
		_emit 01DH
		_emit 068H
		_emit 0EBH
		_emit 000H
		_emit 001H
		cmp ebx, 0
		je L_47A55E
		mov ax, word ptr [esi+6]
		_emit 066H
		_emit 0A3H
		_emit 0F0H
		_emit 025H
		_emit 077H
		_emit 000H
		mov ax, word ptr [esi+0AH]
		_emit 066H
		_emit 0A3H
		_emit 0F2H
		_emit 025H
		_emit 077H
		_emit 000H
		mov al, byte ptr [esi+0DH]
		_emit 003H
		_emit 035H
		_emit 064H
		_emit 0EBH
		_emit 000H
		_emit 001H
L_47A410:
		mov edx, dword ptr [esi]
		add esi, 4
L_47A415:
		add edi, dword ptr [esi]
		mov ecx, dword ptr [esi+4]
		add esi, 8
		cmp ecx, 0
		je L_47A438
		bt ecx, 0
		jae L_47A434
		mov ax, word ptr [esi]
		mov word ptr [edi], ax
		add edi, 2
		add esi, 2
L_47A434:
		shr ecx, 1
		 rep movsd
L_47A438:
		dec edx
		jne L_47A415
		add edi, ebp
		dec ebx
		jne L_47A410
		jmp L_47A55E
		xor ebp, ebp
L_47A447:
		mov edx, dword ptr [esi]
		add esi, 4
L_47A44C:
		add edi, dword ptr [esi]
		mov ecx, dword ptr [esi+4]
		add esi, 8
		cmp ecx, 0
		je L_47A494
		bt ecx, 0
		jae L_47A476
		mov bp, word ptr [edi]
		shr bp, 1
		and bp, 3DEFH
		add bp, word ptr [esi]
		mov word ptr [edi], bp
		add esi, 2
		add edi, 2
L_47A476:
		shr ecx, 1
		cmp ecx, 0
		je L_47A494
L_47A47D:
		mov ebp, dword ptr [edi]
		shr ebp, 1
		and ebp, 3DEFBDEFH
		add ebp, dword ptr [esi]
		mov dword ptr [edi], ebp
		add edi, 4
		add esi, 4
		dec ecx
		jne L_47A47D
L_47A494:
		dec edx
		jne L_47A44C
		_emit 003H
		_emit 03DH
		_emit 060H
		_emit 0EBH
		_emit 000H
		_emit 001H
		dec ebx
		jne L_47A447
		jmp L_47A55E
		xor ebp, ebp
L_47A4A7:
		mov edx, dword ptr [esi]
		add esi, 4
L_47A4AC:
		add edi, dword ptr [esi]
		mov ecx, dword ptr [esi+4]
		add esi, 8
		cmp ecx, 0
		je L_47A4F4
		bt ecx, 0
		jae L_47A4D6
		mov bp, word ptr [edi]
		shr bp, 1
		and bp, 3DEFH
		add bp, word ptr [esi]
		mov word ptr [edi], bp
		add esi, 2
		add edi, 2
L_47A4D6:
		shr ecx, 1
		cmp ecx, 0
		je L_47A4F4
L_47A4DD:
		mov ebp, dword ptr [edi]
		shr ebp, 1
		and ebp, 3DEFBDEFH
		add ebp, dword ptr [esi]
		mov dword ptr [edi], ebp
		add edi, 4
		add esi, 4
		dec ecx
		jne L_47A4DD
L_47A4F4:
		dec edx
		jne L_47A4AC
		_emit 003H
		_emit 03DH
		_emit 060H
		_emit 0EBH
		_emit 000H
		_emit 001H
		dec ebx
		jne L_47A4A7
		jmp L_47A55E
		xor ebp, ebp
L_47A504:
		mov edx, dword ptr [esi]
		add esi, 4
L_47A509:
		add edi, dword ptr [esi]
		mov ecx, dword ptr [esi+4]
		add esi, 8
		cmp ecx, 0
		je L_47A548
		bt ecx, 0
		jae L_47A52F
		mov bp, word ptr [edi]
		shr bp, 1
		_emit 066H
		_emit 023H
		_emit 02DH
		_emit 06CH
		_emit 0EBH
		_emit 000H
		_emit 001H
		mov word ptr [edi], bp
		add edi, 2
L_47A52F:
		shr ecx, 1
		cmp ecx, 0
		je L_47A548
L_47A536:
		mov ebp, dword ptr [edi]
		shr ebp, 1
		_emit 023H
		_emit 02DH
		_emit 0B0H
		_emit 0F1H
		_emit 000H
		_emit 001H
		mov dword ptr [edi], ebp
		add edi, 4
		dec ecx
		jne L_47A536
L_47A548:
		mov cx, word ptr [esi-4]
		shl ecx, 1
		add esi, ecx
		dec edx
		jne L_47A509
		_emit 003H
		_emit 03DH
		_emit 060H
		_emit 0EBH
		_emit 000H
		_emit 001H
		dec ebx
		jne L_47A504
		jmp L_47A55E
L_47A55E:
		pop ebp
		pop ecx
		pop edx
		pop ebx
		pop eax
		pop esi
		pop edi
	}
}
