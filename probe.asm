	TITLE	.scratch/gold-p/221/probe.c
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT _f
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	_f
;	COMDAT _f
_TEXT	SEGMENT
_a0$ = 8
_plan$ = 12
_x$ = 8
_y$ = 12
_posA$ = -24
_posB$ = -48
_f	PROC NEAR					; COMDAT

; 5    : 	float x, y;
; 6    : 	int posA[6], posB[6];
; 7    : 	int r;
; 8    : 	if (plan->rate == 0) goto skip;

	mov	eax, DWORD PTR _plan$[esp-4]
	sub	esp, 48					; 00000030H
	mov	eax, DWORD PTR [eax+4]
	test	eax, eax
	je	SHORT $skip$546

; 9    : 	r = plan->rate(&x, &y, a0, 0, 0, posA, posB);

	lea	ecx, DWORD PTR _posB$[esp+48]
	lea	edx, DWORD PTR _posA$[esp+48]
	push	ecx
	mov	ecx, DWORD PTR _a0$[esp+48]
	push	edx
	push	0
	push	0
	push	ecx
	lea	edx, DWORD PTR _y$[esp+64]
	lea	ecx, DWORD PTR _x$[esp+64]
	push	edx
	push	ecx
	call	eax
	add	esp, 28					; 0000001cH

; 10   : 	if (r == 0) goto skip;

	test	eax, eax
	jne	SHORT $L539
$skip$546:

; 11   : 	return r;
; 12   : skip:
; 13   : 	return 0;

	xor	eax, eax
$L539:

; 14   : }

	add	esp, 48					; 00000030H
	ret	0
_f	ENDP
_TEXT	ENDS
END
