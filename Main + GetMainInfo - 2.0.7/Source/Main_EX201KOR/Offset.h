#pragma	once

#define	MAIN_WINDOW				0x05792778
#define	MAIN_CONNECTION_STATUS	0x05796B50
#define	MAIN_SCREEN_STATE		0x00708760
#define	MAIN_CHARACTER_STRUCT	0x076C1D90
#define	MAIN_VIEWPORT_STRUCT	0x07469838
#define	MAIN_PACKET_SERIAL		0x05796B4B
#define	MAIN_FONT_SIZE			0x077DDFF8
#define	MAIN_RESOLUTION			0x05792568
#define	MAIN_RESOLUTION_X		0x007086F8
#define	MAIN_RESOLUTION_Y		0x007086FC
#define	MAIN_PARTY_MEMBER_COUNT	0x0793F560
#define	MAIN_CURRENT_MAP		0x006FB604
#define	MAIN_HOOK_RECV			0x006E8588
#define	MAIN_HOOK_SEND			0x006E8598
#define MAIN_ACTIVE_SOCKET		0x057928F8

#define STRUCT_DECRYPT			((void(__thiscall*)(void*,void*))0x00505030)((void*)0x057922F8,*(void**)0x076C1D94);
#define STRUCT_ENCRYPT			((void(__thiscall*)(void*,void*))0x00410410)((void*)0x057922F8,*(void**)0x076C1D94);

#define	ProtocolCore			((BOOL(*)(DWORD,BYTE*,DWORD,DWORD))0x004FFE40)
#define	pGetPosFromAngle		((void(__cdecl*)(float*,int*,int*))0x00657250)
#define	pCursorX				*(int*)0x07DCB074
#define	pCursorY				*(int*)0x07DCB070
#define DrawInterfaceText		((void(*)(int,int,char*))0x0065A370)
#define	pDrawText				((char*(__cdecl*)(int,int,char*,int,int,int))0x0057A770)
#define	pDrawBarForm			((void(__cdecl*)(float,float,float,float,float,int))0x00658780)
#define	pSetBlend				((void(__cdecl*)(BYTE))0x006576A0)
#define	pGLSwitchBlend			((void(__cdecl*)())0x00657730)
#define	pGLSwitch				((void(__cdecl*)())0x00657620)
#define	pDrawBigText			((void(*)(float,float,DWORD,float,float))0x006585D0)
#define	pDrawImage				((void(*)(DWORD,float,float,float,float,float,float,float,float,int,int,GLfloat))0x00658840)
#define	pDrawMessage			((int(__cdecl*)(char*,int))0x0057AC00)
#define	pLoadItemModel			((void(*)(int,char*,char*,int))0x00642C00)
#define	pLoadItemTexture		((void(*)(int,char*,int,int,int))0x006427C0)
#define pCheckWindow			((bool(__stdcall*)(int)) 0x00694DD0)
#define pViewportAddress		*(DWORD*)(0x07469834)
#define pChaosMixIndex			*(DWORD*)(0x07DC1878)

#define pRenderPartObjectEffect	((void(*)(DWORD,int,float*,float,int,int,int,int,int))0x0063F080)
#define pTransformPosition      ((int(__thiscall*)(DWORD,DWORD,float*,float*,bool))0x005097D0)
#define pCreateSprite	        ((int(*)(int,float*,float,float*,DWORD,float,int))0x0056F430)
#define pCreateParticle			((int(__cdecl*)(DWORD,float*,DWORD,float*,DWORD,float,DWORD))(0x00564580))
#define pCreateEffect			((void(__cdecl*)(int,float*,DWORD,float*,int,DWORD,short,BYTE,float,BYTE,float*))0x00538E60)

#define pCreateMonster			((DWORD(*)(int,int,int,int))0x00450A40)
#define pCreateCharacter		((DWORD(*)(int,int,int,int,float))0x00531C90)
#define pSettingMonster			((DWORD(*)(int,int))0x005334F0)
#define pSetCharacterScale		((void(*)(DWORD))0x00531D60)

#define pGetTextLine(x)			((char*)(0x076FD0BC+(0x12C*x)))

#define ITEM_BASE_MODEL			582

#define GET_ITEM(x,y)			(((x)*512)+(y))
#define GET_ITEM_MODEL(x,y)		((((x)*512)+(y))+ITEM_BASE_MODEL)
#define GET_ITEM_OPT_LEVEL(x)	((x>>3)&15)
#define GET_ITEM_OPT_EXC(x)		((x)-(x&64))
#define GET_MAX_WORD_VALUE(x)	(((x)>65000)?65000:((WORD)(x)))

enum eWindowsType
{
	WINDOWS_NONE				= 0 << 0,
	WINDOWS_FRIEND				= 1 << 0,
	WINDOWS_MOVE_LIST			= 1 << 1,
	WINDOWS_PARTY				= 1 << 2,
	WINDOWS_QUEST				= 1 << 3,
	WINDOWS_GUILD				= 1 << 4,
	WINDOWS_TRADE				= 1 << 5,
	WINDOWS_WAREHOUSE			= 1 << 6,
	WINDOWS_UNKNOWN_1			= 1 << 7,
	WINDOWS_CHAOS_MIX			= 1 << 8,
	WINDOWS_COMMAND				= 1 << 9,
	WINDOWS_PET					= 1 << 10,
	WINDOWS_STORE				= 1 << 11,
	WINDOWS_DEVIL_SQUARE		= 1 << 12,
	WINDOWS_MOVING_SERVER		= 1 << 13,
	WINDOWS_BLOOD_CASTLE		= 1 << 14,
	WINDOWS_PET_TRAINER			= 1 << 15,
	WINDOWS_SHOP				= 1 << 16,
	WINDOWS_STOREOTHER			= 1 << 17,
	WINDOWS_GUILD_MASTER		= 1 << 18,
	WINDOWS_GUARDMAN_SIEGUE		= 1 << 19,
	WINDOWS_SENIOR_MIX			= 1 << 20,
	WINDOWS_GUARDMAN_LAND		= 1 << 21,
	WINDOWS_CATAPULT_INVADING	= 1 << 22,
	WINDOWS_CATAPULT_DEFENDING	= 1 << 23,
	WINDOWS_CASTLE_GATE_SWITCH  = 1 << 24,
	WINDOWS_CHARACTER			= 1 << 25,
	WINDOWS_INVENTORY			= 1 << 26,
	WINDOWS_REFINERY			= 1 << 27,
	WINDOWS_KANTURU_GATE		= 1 << 28,
};

static const BYTE module0[12] = { 0xB7,0xAA,0xD9,0x92,0xAA,0xC7,0xCF,0xFD,0x85,0x98,0xA3,0xC7 };
static const BYTE module1[11] = { 0xB3,0xBF,0xCE,0x92,0x9F,0xD9,0x93,0xAC,0xCE,0x8F,0xBC };
static const BYTE module2[11] = { 0xB9,0xB7,0xC2,0x88,0x9F,0xD9,0x93,0xAC,0xCE,0x8F,0xBC };
static const BYTE module3[16] = { 0xA8,0xAA,0xD9,0x91,0xA6,0xC5,0x9D,0xBB,0xCE,0xAC,0xBD,0xC4,0x9F,0xAA,0xD8,0x8F };
static const BYTE module4[23] = { 0xAD,0xBA,0xCE,0x8E,0xB6,0xFB,0x99,0xBD,0xCD,0x93,0xBD,0xC6,0x9D,0xA1,0xC8,0x99,0x8C,0xC4,0x89,0xA1,0xDF,0x99,0xBD };
static const BYTE module5[25] = { 0xAD,0xBA,0xCE,0x8E,0xB6,0xFB,0x99,0xBD,0xCD,0x93,0xBD,0xC6,0x9D,0xA1,0xC8,0x99,0x89,0xD9,0x99,0xBE,0xDE,0x99,0xA1,0xC8,0x85 };
static const BYTE module6[12] = { 0xBB,0xAA,0xDF,0xA8,0xA6,0xC8,0x97,0x8C,0xC4,0x89,0xA1,0xDF };