#include <windows.h>
#include <string>

#define NAKED	__declspec(naked)
#define WIN32_LEAN_AND_MEAN

#define JUMP( from, to ) \
    *from = 0xE9;\
    *(DWORD*)(from+1) = (PBYTE)to - from - 5

#define VirtualProtectX( addr, size ) \
    VirtualProtect( addr, size, PAGE_EXECUTE_READWRITE, &dummy )

DWORD dummy;
int Topviewreturn = 0x004E7333;
int Rotationreturn = 0x004E3E9B;
int Rotationdefaultreturn = 0x004E3EC3;
int Wobblereturn = 0x004E735E;
int Wobbledefaultreturn = 0x004E7372;
int Targethudreturn = 0x062935EF;
int TargethudARCHreturn = 0x062A0386;
int Targetassingreturn = 0x004E3F51;
int Traverseequipmentreturn = 0x004E7C07;
int Traversearchreturn = 0x004E7CA9;
int Traversedefaultreturn = 0x004E7C50;
int Traversedefaultreturn2 = 0x004E7C14;
int Catchbuttonreturn = 0x004E2C2A;
int CatchbuttonreturnNoswitch = 0x004E2C33;
int CatchbuttonHUDreturn = 0x004E2BCC;
int Rotationvalues[10];
int Cship;
int EquipmentObj;
int EquipmentMatrix[3];
int TraverseTransform[10];
int Reserveadresses[1000];
int Reservetick;
int TickTraverse = 0;
int Ownship = 0;
int Clickpatch;
int ClickHUDpatch;

//Hud expanded
int HudTargetAdress;
int HudTargetreturn = 0x004E0F81;
int HudTargetModelAdress;
int HudFirstLaunch;

float HudBetween = 0.25f;
float HudBetweenS = 0.205f;
float HudBetweenS2 = 0.235f;
float HudBetweenW = 0.26f;

int CustomHudAdress[100];
int CustomHudTargetModelAdress;
float CustomHudTransform[10];

int StealHudDestroyreturn = 0x004E0CD7;

char sCustomHud[] = "Interface\\hud\\hud_targed_advanced.cmp";

NAKED
void Topview()
{
	__asm
	{
		mov eax, [ebp + 0x398]
		pushad

		mov DWORD PTR[esi], 0x3f800000
		mov DWORD PTR[esi + 0x4], 0x00000000
		mov DWORD PTR[esi + 0x8], 0x00000000
		mov DWORD PTR[esi + 0xC], 0x00000000
		mov DWORD PTR[esi + 0x10], 0x00000000
		mov DWORD PTR[esi + 0x14], 0x3f800000
		mov DWORD PTR[esi + 0x18], 0x00000000
		mov DWORD PTR[esi + 0x1C], 0xbf800000
		mov DWORD PTR[esi + 0x20], 0x00000000

		popad
		jmp Topviewreturn
	}
}

NAKED
void Rotationlock()
{
	__asm
	{
		lea ecx, [esi + 0x000003A0]
		push eax
		push ebx
		push ecx
		mov eax, [esp + 0x10]

		lea ebx, Rotationvalues
		mov ecx, [eax]
		mov[ebx], ecx
		mov ecx, [eax + 0x4]
		mov[ebx + 0x4], ecx
		mov ecx, [eax + 0x8]
		mov[ebx + 0x8], ecx
		mov ecx, [eax + 0xC]
		mov[ebx + 0xC], ecx
		mov ecx, [eax + 0x10]
		mov[ebx + 0x10], ecx
		mov ecx, [eax + 0x14]
		mov[ebx + 0x14], ecx
		mov ecx, [eax + 0x18]
		mov[ebx + 0x18], ecx
		mov ecx, [eax + 0x1C]
		mov[ebx + 0x1C], ecx
		mov ecx, [eax + 0x20]
		mov[ebx + 0x20], ecx

		mov DWORD PTR[eax], 0x3F800000
		mov DWORD PTR[eax + 0x4], 0x00000000
		mov DWORD PTR[eax + 0x8], 0x00000000
		mov DWORD PTR[eax + 0xC], 0x00000000
		mov DWORD PTR[eax + 0x10], 0x3F800000
		mov DWORD PTR[eax + 0x14], 0x00000000
		mov DWORD PTR[eax + 0x18], 0x00000000
		mov DWORD PTR[eax + 0x1C], 0x00000000
		mov DWORD PTR[eax + 0x20], 0x3F800000

		pop ecx
		pop ebx
		pop eax
		jmp Rotationreturn
	}
}

NAKED
void Rotationdefault()
{
	__asm
	{
		push 0x00000642
		push eax
		push ebx
		push ecx

		mov ebx, edi
		add ebx, 0x8

		lea eax, Rotationvalues
		mov ecx, [eax]
		mov[ebx], ecx
		mov ecx, [eax + 0x4]
		mov[ebx + 0x4], ecx
		mov ecx, [eax + 0x8]
		mov[ebx + 0x8], ecx
		mov ecx, [eax + 0xC]
		mov[ebx + 0xC], ecx
		mov ecx, [eax + 0x10]
		mov[ebx + 0x10], ecx
		mov ecx, [eax + 0x14]
		mov[ebx + 0x14], ecx
		mov ecx, [eax + 0x18]
		mov[ebx + 0x18], ecx
		mov ecx, [eax + 0x1C]
		mov[ebx + 0x1C], ecx
		mov ecx, [eax + 0x20]
		mov[ebx + 0x20], ecx

		pop ecx
		pop ebx
		pop eax
		jmp Rotationdefaultreturn
	}
}

NAKED
void Targetwobble()
{
	__asm
	{
		lea edx, [esp + 0x70]
		push edx
		push eax
		push ebx
		push ecx
		mov Cship, eax

		lea ebx, Rotationvalues
		mov ecx, [eax]
		mov[ebx], ecx
		mov ecx, [eax + 0x4]
		mov[ebx + 0x4], ecx
		mov ecx, [eax + 0x8]
		mov[ebx + 0x8], ecx
		mov ecx, [eax + 0xC]
		mov[ebx + 0xC], ecx
		mov ecx, [eax + 0x10]
		mov[ebx + 0x10], ecx
		mov ecx, [eax + 0x14]
		mov[ebx + 0x14], ecx
		mov ecx, [eax + 0x18]
		mov[ebx + 0x18], ecx
		mov ecx, [eax + 0x1C]
		mov[ebx + 0x1C], ecx
		mov ecx, [eax + 0x20]
		mov[ebx + 0x20], ecx

		mov DWORD PTR[eax], 0x3F800000
		mov DWORD PTR[eax + 0x4], 0x00000000
		mov DWORD PTR[eax + 0x8], 0x00000000
		mov DWORD PTR[eax + 0xC], 0x00000000
		mov DWORD PTR[eax + 0x10], 0x3F800000
		mov DWORD PTR[eax + 0x14], 0x00000000
		mov DWORD PTR[eax + 0x18], 0x00000000
		mov DWORD PTR[eax + 0x1C], 0x00000000
		mov DWORD PTR[eax + 0x20], 0x3F800000

		pop ecx
		pop ebx
		pop eax
		jmp Wobblereturn
	}
}

NAKED
void Targetwobbledefault()
{
	__asm
	{
		mov edx, [esp + 0x44]
		push eax
		push eax
		push ebx
		push ecx

		mov ebx, Cship

		lea eax, Rotationvalues
		mov ecx, [eax]
		mov[ebx], ecx
		mov ecx, [eax + 0x4]
		mov[ebx + 0x4], ecx
		mov ecx, [eax + 0x8]
		mov[ebx + 0x8], ecx
		mov ecx, [eax + 0xC]
		mov[ebx + 0xC], ecx
		mov ecx, [eax + 0x10]
		mov[ebx + 0x10], ecx
		mov ecx, [eax + 0x14]
		mov[ebx + 0x14], ecx
		mov ecx, [eax + 0x18]
		mov[ebx + 0x18], ecx
		mov ecx, [eax + 0x1C]
		mov[ebx + 0x1C], ecx
		mov ecx, [eax + 0x20]
		mov[ebx + 0x20], ecx

		pop ecx
		pop ebx
		pop eax
		jmp Wobbledefaultreturn
	}
}

NAKED
void Targethudbase()
{
	__asm
	{
		mov ecx, [0x06399040]
		mov EquipmentObj, eax

		jmp Targethudreturn
	}
}

NAKED
void TargethudbaseARCH()
{
	__asm
	{
		xor al, al
		cmp ecx, 0x03
		mov ebp, [esi + 0x08]
		mov EquipmentObj, ebp

		jmp TargethudARCHreturn
	}
}

NAKED
void Targethudassing()
{
	__asm
	{
		lea edx, [esp + 0x1C]
		push edx

		mov eax, EquipmentObj
		lea eax, [eax + 0x50]
		lea edx, EquipmentMatrix

		push ebx
		mov ebx, [eax]
		mov[edx], ebx
		add eax, 0x4
		add edx, 0x4
		mov ebx, [eax]
		mov[edx], ebx
		add eax, 0x4
		add edx, 0x4
		mov ebx, [eax]
		mov[edx], ebx
		pop ebx

		sub edx, 0x8
		fld dword ptr[esp + 0x20]
		fld dword ptr[edx]
		faddp st(1), st(0)
		fstp dword ptr[esp + 0x20]

		add edx, 0x4
		fld dword ptr[esp + 0x24]
		fld dword ptr[edx]
		faddp st(1), st(0)
		fstp dword ptr[esp + 0x24]

		add edx, 0x4
		fld dword ptr[esp + 0x28]
		fld dword ptr[edx]
		faddp st(1), st(0)
		fstp dword ptr[esp + 0x28]

		jmp Targetassingreturn
	}
}

NAKED
void TraverseEquipment()
{
	__asm
	{
			cmp DWORD PTR[ebp], 0x005D8504
			je Orginal

			pushad
		RepeatTraverse :
			mov ebp, eax
			lea ebx, [eax + 0x50]
			mov ecx, [eax]
			mov eax, [eax + 0x4]

			cmp ecx, 0x0
			je Nulltraverse
			jmp Normaltraverse

		Nulltraverse:
			add eax, 0x4

		Normaltraverse:
			mov edx, Reservetick
			imul edx, edx, 0x10
			lea esi, Reserveadresses
			add esi, edx
			lea edi, [eax + 0x28]
			mov[esi], edi
			add esi, 0x4
			mov edx, [edi]
			mov[esi], edx
			mov edx, [edi + 0x4]
			mov[esi + 0x4], edx
			mov edx, [edi + 0x8]
			mov[esi + 0x8], edx
			inc Reservetick
			//////

			cmp TickTraverse, 0x0
			jg Subgroup
			jmp Basegroup

		Subgroup:
			fld[TraverseTransform]
			fstp[eax + 0x28]
			fld[TraverseTransform + 0x4]
			fstp[eax + 0x2C]
			fld[TraverseTransform + 0x8]
			fstp[eax + 0x30]
			jmp Final

		Basegroup :
			mov edx, [esp + 0x48]
			add edx, 0x2C
			fld[edx]
			fld[ebx]
			faddp st(1), st(0)
			fst[TraverseTransform]
			fstp[eax + 0x28]
			fld[edx + 4]
			fld[ebx + 0x4]
			faddp st(1), st(0)
			fst[TraverseTransform + 0x4]
			fstp[eax + 0x2C]
			fld[edx + 0x8]
			fld[ebx + 0x8]
			faddp st(1), st(0)
			fst[TraverseTransform + 0x8]
			fstp[eax + 0x30]

		Final:
			inc TickTraverse
			mov eax, [ebp + 0x1c]
			cmp eax, 0x0
			jne RepeatTraverse

			popad
			mov Ownship, 0
			mov TickTraverse, 0
			lea ecx, [esp + 0x0000009C]
			jmp Traverseequipmentreturn

		Orginal:
			mov Ownship, 1
			lea ecx, [esp + 0x0000009C]
			jmp Traverseequipmentreturn
	}
}

NAKED
void TraverseArchgroup()
{
	__asm
	{
		cmp Ownship, 0x0
		jg Orginal
		pushad

	RepeatTraverse :
		mov ebp, eax
		lea ebx, [eax + 0x50]
		mov ecx, [eax]
		mov eax, [eax + 0x4]

		cmp ecx, 0x0
		je Nulltraverse
		jmp Normaltraverse

		Nulltraverse:
		add eax, 0x4

	Normaltraverse:
		mov DWORD PTR[eax + 0x4], 0x3f800000
		mov DWORD PTR[eax + 0x8], 0x0
		mov DWORD PTR[eax + 0xC], 0x0
		mov DWORD PTR[eax + 0x10], 0x0
		mov DWORD PTR[eax + 0x14], 0x3f800000
		mov DWORD PTR[eax + 0x18], 0x0
		mov DWORD PTR[eax + 0x1C], 0x0
		mov DWORD PTR[eax + 0x20], 0x0
		mov DWORD PTR[eax + 0x24], 0x3f800000

		cmp TickTraverse, 0x0
		jg Subgroup
		jmp Basegroup

	Subgroup:
		fld[TraverseTransform]
		fstp[eax + 0x28]
		fld[TraverseTransform + 0x4]
		fstp[eax + 0x2C]
		fld[TraverseTransform + 0x8]
		fstp[eax + 0x30]
		jmp Final

	Basegroup:
		mov edx, [esp + 0x48]
		add edx, 0x2C
		fld[edx]
		fld[ebx]
		faddp st(1), st(0)
		fst[TraverseTransform]
		fstp[eax + 0x28]
		fld[edx + 4]
		fld[ebx + 0x4]
		faddp st(1), st(0)
		fst[TraverseTransform + 0x4]
		fstp[eax + 0x2C]
		fld[edx + 0x8]
		fld[ebx + 0x8]
		faddp st(1), st(0)
		fst[TraverseTransform + 0x8]
		fstp[eax + 0x30]

	Final:
		inc TickTraverse
		mov eax, [ebp + 0x1c]
		cmp eax, 0x0
		jne RepeatTraverse

		popad
		mov TickTraverse, 0

	Orginal:
		lea ecx, [esp + 0x0000009C]
		jmp Traversearchreturn
	}
}

NAKED
void TraverseDefault()
{
	__asm
	{
		pushad
		cmp Reservetick, 0
		je EarlyExit

	Loop:
		lea ebx, Reserveadresses
		mov ecx, Reservetick
		sub ecx, 0x1
		imul eax, ecx, 0x10
		add eax, ebx

		mov ebx, [eax]
		mov ecx, [eax + 0x04]
		mov[ebx], ecx
		mov ecx, [eax + 0x08]
		mov[ebx + 0x4], ecx
		mov ecx, [eax + 0xC]
		mov[ebx + 0x8], ecx

		dec Reservetick
		cmp Reservetick, 0x0
		jne Loop
	EarlyExit:
		popad
		test al, al
		je Confirmedjump
		mov ax, [esi + 0x08]
		jmp Traversedefaultreturn2

	Confirmedjump:
		jmp Traversedefaultreturn
	}
}

void PatchX()
{
#define TopviewOffset ((PBYTE)0x004E732E)
#define TopviewOffset2 ((PBYTE)0x004E7333)
	JUMP(TopviewOffset, Topview);
	memcpy(TopviewOffset2, "\x90", 1);

#define Rotationoffset ((PBYTE)0x004E3E96)
#define Rotationoffset2 ((PBYTE)0x004E3E9B)
	JUMP(Rotationoffset, Rotationlock);
	memcpy(Rotationoffset2, "\x90", 1);

#define Rotationdefaultoffset ((PBYTE)0x004E3EBE)
	JUMP(Rotationdefaultoffset, Rotationdefault);

#define Wobbleoffset ((PBYTE)0x004E7359)
	JUMP(Wobbleoffset, Targetwobble);

#define Wobbledefaultoffset ((PBYTE)0x004E736D)
	JUMP(Wobbledefaultoffset, Targetwobbledefault);

#define Targethudbaseoffset ((PBYTE)0x062935E9)
#define Targethudbaseoffset2 ((PBYTE)0x062935EE)
#define Targethudbasecenterize ((PBYTE)0x004E3F1B)
	JUMP(Targethudbaseoffset, Targethudbase);
	memcpy(Targethudbaseoffset2, "\x90", 1);
	memcpy(Targethudbasecenterize, "\x90\x90", 2);

#define TargethudbaseARCHoffset ((PBYTE)0x062A0380)
#define TargethudbaseARCHoffset2 ((PBYTE)0x062A0385)
	JUMP(TargethudbaseARCHoffset, TargethudbaseARCH);
	memcpy(TargethudbaseARCHoffset2, "\x90", 1);

#define Targethudbaseassingoffset ((PBYTE)0x004E3F4C)
	JUMP(Targethudbaseassingoffset, Targethudassing);

#define TraverseEquipmentoffset ((PBYTE)0x004E7C00)
#define TraverseEquipmentoffset2 ((PBYTE)0x004E7C05)
	JUMP(TraverseEquipmentoffset, TraverseEquipment);
	memcpy(TraverseEquipmentoffset2, "\x90\x90", 2);

#define TraverseArchoffset ((PBYTE)0x004E7CA2)
#define TraverseArchoffset2 ((PBYTE)0x004E7CA7)
	VirtualProtectX(TraverseArchoffset, 8);
	JUMP(TraverseArchoffset, TraverseArchgroup);
	memcpy(TraverseArchoffset2, "\x90\x90", 2);

#define Traversendefaultoffset ((PBYTE)0x004E7C0C)
#define Traversendefaultoffset2 ((PBYTE)0x004E7C11)
	VirtualProtectX(Traversendefaultoffset, 10);
	JUMP(Traversendefaultoffset, TraverseDefault);
	memcpy(Traversendefaultoffset2, "\x90\x90\x90", 3);
}

void UnpatchX()
{
#define TopviewOffset ((PBYTE)0x004E732E)
	memcpy(TopviewOffset, "\x8B\x85\x98\x03\x00\x00", 6);

#define Rotationoffset ((PBYTE)0x004E3E96)
	memcpy(Rotationoffset, "\x8D\x8E\xA0\x03\x00\x00", 6);

#define Rotationdefaultoffset ((PBYTE)0x004E3EBE)
	memcpy(Rotationdefaultoffset, "\x68\x42\x06\x00\x00", 5);

#define Wobbleoffset ((PBYTE)0x004E7359)
	memcpy(Wobbleoffset, "\x8D\x54\x24\x70\x52", 5);

#define Wobbledefaultoffset ((PBYTE)0x004E736D)
	memcpy(Wobbledefaultoffset, "\x8B\x54\x24\x44\x50", 5);

#define Targethudbaseoffset ((PBYTE)0x062935E9)
#define Targethudbasecenterize ((PBYTE)0x004E3F1B)
	memcpy(Targethudbaseoffset, "\x8B\x0D\x40\x90\x39\x06", 6);
	memcpy(Targethudbasecenterize, "\x75\x29", 2);

#define TargethudbaseARCHoffset ((PBYTE)0x062A0380)
	memcpy(TargethudbaseARCHoffset, "\x8B\x6E\x08\x83\xFD\xFF", 6);

#define Targethudbaseassingoffset ((PBYTE)0x004E3F4C)
	memcpy(Targethudbaseassingoffset, "\x8D\x54\x24\x1C\x52", 5);

#define TraverseEquipmentoffset ((PBYTE)0x004E7C00)
	memcpy(TraverseEquipmentoffset, "\x8D\x8C\x24\x9C\x00\x00\x00", 7);

#define TraverseArchoffset ((PBYTE)0x004E7CA2)
	memcpy(TraverseArchoffset, "\x8D\x8C\x24\x9C\x00\x00\x00", 7);

#define Traversendefaultoffset ((PBYTE)0x004E7C0C)
	memcpy(Traversendefaultoffset, "\x84\xC0\x74\x40\x66\x8B\x46\x08", 8);
}


//////////////////////////////////////////Hud expanded functions 

void ShowTargetScreen()
{
#define ApplyOffset1 ((PBYTE)0x004E3CE0)
	VirtualProtectX(ApplyOffset1, 8);
	memcpy(ApplyOffset1, "\x90\x90\x90\x90\x90\x90", 6);

#define EnableSelection ((PBYTE)0x004E203E)
	VirtualProtectX(EnableSelection, 8);
	memcpy(EnableSelection, "\xE9\xB8\x00\x00\x00\x90", 6);
}

void HideTargetScreen()
{
#define ApplyOffset1 ((PBYTE)0x004E3CE0)
	VirtualProtectX(ApplyOffset1, 8);
	memcpy(ApplyOffset1, "\x0F\x85\x8F\x02\x00\x00", 6);

#define EnableSelection ((PBYTE)0x004E203E)
	VirtualProtectX(EnableSelection, 8);
	memcpy(EnableSelection, "\x0F\x84\xB7\x00\x00\x00", 6);
}

NAKED
void DefaultHudWindow()
{
	__asm
	{
		mov eax, HudTargetAdress
		lea ebx, CustomHudAdress
		mov ebx, [ebx + 0xC]
		mov ebx, [ebx + 0x84]
		lea eax, [eax + 0x84]
		mov ecx, HudTargetModelAdress
		mov[eax], ecx

		mov eax, HudTargetAdress
		mov eax, [eax + 0x4]
		mov[eax + 0x614], 1
		mov ebx, 0x004E0A80
		mov ebx, [ebx]
		mov[eax + 0x47c], ebx

		mov eax, HudTargetAdress
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov ebx, 0x004E10FF
		mov ebx, [ebx]
		mov[eax + 0x2d4], ebx

		mov eax, [eax + 0x8]
		mov ebx, 0x4e1180
		mov ebx, [ebx]
		mov[eax + 0x2d4], ebx

		mov eax, [eax + 0x8]
		mov ebx, 0x004E1247
		mov ebx, [ebx]
		mov[eax + 0xa8], ebx

		mov eax, [eax + 0x8]
		mov ebx, 0x004E12B4
		mov ebx, [ebx]
		mov[eax + 0xa8], ebx

		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov ebx, 0x004E175C
		mov ebx, [ebx]
		mov[eax + 0xa8], ebx

		call HideTargetScreen

		ret
	}
}

NAKED
void ExpandedHudWindow()
{
	__asm
	{
		mov eax, HudTargetAdress
		lea ebx, CustomHudAdress
		mov ebx, [ebx + 0xC]
		mov ebx, [ebx + 0x84]
		lea eax, [eax + 0x84]
		mov ecx, CustomHudTargetModelAdress
		mov[eax], ecx

		mov eax, HudTargetAdress //Wireframe
		mov eax, [eax + 0x4]
		mov[eax + 0x614], 1
		fld[eax + 0x47c]
		fld HudBetweenW
		fadd st(0), st(1)
		fstp[eax + 0x47c]
		fstp st(0)

		mov eax, HudTargetAdress //Shipname
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		fld[eax + 0x2d4]
		fld HudBetween
		fadd st(0), st(1)
		fstp[eax + 0x2d4]
		fstp st(0)

		mov eax, [eax + 0x8] //Subname
		fld[eax + 0x2d4]
		fld HudBetween
		fadd st(0), st(1)
		fstp[eax + 0x2d4]
		fstp st(0)

		mov eax, [eax + 0x8] //subtarget button
		fld[eax + 0xa8]
		fld HudBetweenS
		fadd st(0), st(1)
		fstp[eax + 0xa8]
		fstp st(0)

		mov eax, [eax + 0x8]//subtarget button
		fld[eax + 0xa8]
		fld HudBetweenS
		fadd st(0), st(1)
		fstp[eax + 0xa8]
		fstp st(0)

		mov eax, [eax + 0x8]//Level
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		mov eax, [eax + 0x8]
		fld[eax + 0xa8]
		fld HudBetweenS2
		fadd st(0), st(1)
		fstp[eax + 0xa8]
		fstp st(0)

		call ShowTargetScreen

		ret
	}
}

NAKED
void DestroyHud()//This is how the game destroys a HUD and removes the adress from its vector/list NOTE: I have decided not use this because it is more complex than this function, but this is the one
{
	__asm
	{
		lea ecx, CustomHudAdress
		mov eax, 0x0059FA50
		call eax
		ret
	}
}

NAKED
void CreateHud()// it has lots of parameters, and majority of them are flags, like SPIN animation flag for example, NOTE: WE CREATE THE MEMORY ONCE GAME LAUNCH AND NOT DESTROY IT
{
	__asm
	{
		lea eax, CustomHudTransform
		push eax

		//Transform
		mov[eax], 0
		mov[eax + 0x4], 0
		mov[eax + 0x8], 0
		mov[eax + 0xc], 0
		mov[eax + 0x10], 0
		mov[eax + 0x14], 0
		mov ebx, 0x004E0F63//steal HudShift/default position and scale values X
		mov ebx, [ebx]
		mov[eax + 0x18], ebx
		mov ebx, 0x004E0F6B//Y
		mov ebx, [ebx]
		mov[eax + 0x1c], ebx
		mov ebx, 0x004E0F73//Z
		mov ebx, [ebx]
		mov[eax + 0x20], ebx

		//Flags
		push 0
		push 0
		push 0
		push 1
		push 0
		push 0
		push 1
		push 0
		push 0
		push 0

		//ready the adress
		lea esi, CustomHudAdress
		mov[CustomHudAdress], 0x005D88B4

		//Matrix
		lea ecx, [eax + 0xc]
		push ecx

		push 0

		//Vector
		lea ecx, [eax + 0x18]
		push ecx

		//String and Style
		lea ecx, sCustomHud
		push ecx
		push 0x005D8CCC

		//Create()
		mov ecx, esi
		mov eax, 0x005A0DB0
		call eax
		ret
	}
}

NAKED
void Catchbutton()
{
	__asm
	{
		pushad
		call DefaultHudWindow
		popad

		mov al, [edi + 0x0000014C]
		pushad
		mov ebx, [edi + 0x000002C4]
		cmp ebx, 0x1
		je Process

		cmp ClickHUDpatch, 0x1
		je Process

	Invalidclick:
		popad
		cmp ClickHUDpatch, 0x0
		jne Defaultreturn
		jmp Catchbuttonreturn

	Defaultreturn:
		pushad
		call ExpandedHudWindow
		popad

		test al, al
		jmp CatchbuttonreturnNoswitch

	Process:
		cmp Clickpatch, 0x0
		je Patchit
		jne Unpatchit

	Patchit :
		call PatchX
		mov Clickpatch, 0x1
		jmp Invalidclick

	Unpatchit :
		call UnpatchX
		mov Clickpatch, 0x0
		jmp Invalidclick

	}
}

NAKED
void CatchbuttonHUD()
{
	__asm
	{
		mov al, [edi + 0x0000014C]
		pushad
		mov ebx, [edi + 0x000002C4]
		cmp ebx, 0x0
		jne Invalidclick

		cmp ClickHUDpatch, 0x0
		je Patchit
		jne Unpatchit

	Patchit:
		call ExpandedHudWindow
		mov ClickHUDpatch, 0x1
		jmp Invalidclick

	Unpatchit:
		call DefaultHudWindow
		mov ClickHUDpatch, 0x0
		jmp Invalidclick

	Invalidclick:
		popad
		jmp CatchbuttonHUDreturn
	}
}

NAKED
void StealHudTarget()//Steal Hud_Target creation adress, plus create and destroy our custom hud every call to clear memory out of leaks
{
	__asm
	{
		mov HudTargetAdress, eax
		mov eax, [eax + 0x84]
		mov HudTargetModelAdress, eax
		mov eax, HudTargetAdress
		mov[esi + 0x00000494], eax

		cmp HudFirstLaunch, 0x1
		je SkipOperation
		pushad
		call CreateHud
		popad
	SkipOperation :
		push eax
		lea eax, [CustomHudAdress + 0xc]
		mov eax, [eax]
		mov eax, [eax + 0x84]
		mov CustomHudTargetModelAdress, eax
		pop eax

		mov HudFirstLaunch, 0x1
		jmp HudTargetreturn
	}
}

NAKED
void StealHudDestroy()//Hud_Target is destroyed by this function, we swap the orginal adress
{
	__asm
	{
		push 0x005BE7CC
		push eax
		push ebx
		push ecx

		pushad
		call HideTargetScreen
		popad

		mov eax, HudTargetAdress
		lea ebx, CustomHudAdress
		mov ebx, [ebx + 0xC]
		mov ebx, [ebx + 0x84]

		lea eax, [eax + 0x84]

		mov ecx, HudTargetModelAdress
		mov[eax], ecx

		pop ecx
		pop ebx
		pop eax
		jmp StealHudDestroyreturn
	}
}

void Patch()
{
#define TopviewOffset ((PBYTE)0x004E732E)
#define TopviewOffset2 ((PBYTE)0x004E7333)
	VirtualProtectX(TopviewOffset, 8);

#define Rotationoffset ((PBYTE)0x004E3E96)
#define Rotationoffset2 ((PBYTE)0x004E3E9B)
	VirtualProtectX(Rotationoffset, 8);

#define Rotationdefaultoffset ((PBYTE)0x004E3EBE)
	VirtualProtectX(Rotationdefaultoffset, 8);

#define Wobbleoffset ((PBYTE)0x004E7359)
	VirtualProtectX(Wobbleoffset, 8);

#define Wobbledefaultoffset ((PBYTE)0x004E736D)
	VirtualProtectX(Wobbledefaultoffset, 8);

#define Targethudbaseoffset ((PBYTE)0x062935E9)
#define Targethudbasecenterize ((PBYTE)0x004E3F1B)
	VirtualProtectX(Targethudbaseoffset, 8);
	VirtualProtectX(Targethudbasecenterize, 4);

#define TargethudbaseARCHoffset ((PBYTE)0x062A0380)
	VirtualProtectX(TargethudbaseARCHoffset, 8);

#define Targethudbaseassingoffset ((PBYTE)0x004E3F4C)
	VirtualProtectX(Targethudbaseassingoffset, 8);

#define TraverseEquipmentoffset ((PBYTE)0x004E7C00)
	VirtualProtectX(TraverseEquipmentoffset, 8);

#define TraverseArchoffset ((PBYTE)0x004E7CA2)
	VirtualProtectX(TraverseArchoffset, 8);

#define Traversendefaultoffset ((PBYTE)0x004E7C0C)
	VirtualProtectX(Traversendefaultoffset, 10);

#define Catchbuttonoffset ((PBYTE)0x004E2C25)
#define Catchbuttonoffset2 ((PBYTE)0x004E2C2A)
	VirtualProtectX(Catchbuttonoffset, 10);
	JUMP(Catchbuttonoffset, Catchbutton);
	memcpy(Catchbuttonoffset2, "\x90", 1);

#define CatchbuttonHUDoffset ((PBYTE)0x004E2BC7)
#define CatchbuttonHUDoffset2 ((PBYTE)0x004E2BCC)
	VirtualProtectX(CatchbuttonHUDoffset, 10);
	JUMP(CatchbuttonHUDoffset, CatchbuttonHUD);
	memcpy(CatchbuttonHUDoffset2, "\x90", 1);

#define StealHudTargetoffset ((PBYTE)0x004E0F7C)
#define StealHudTargetoffset2 ((PBYTE)0x004E0F81)
	VirtualProtectX(StealHudTargetoffset, 10);
	JUMP(StealHudTargetoffset, StealHudTarget);
	memcpy(StealHudTargetoffset2, "\x90", 1);

#define StealHudDestroyoffset ((PBYTE)0x004E0CD2)
	VirtualProtectX(StealHudDestroyoffset, 10);
	JUMP(StealHudDestroyoffset, StealHudDestroy);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
		Patch();

	return TRUE;
}
