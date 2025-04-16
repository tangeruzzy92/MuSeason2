#include "stdafx.h"
#include "Camera.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"

CCamera gCamera;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera() // OK
{
	this->m_Enable = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0;

	this->m_Zoom.MaxPercent = 300.0;

	this->m_Zoom.Precision = 2.0;		

	this->m_Address.Zoom = (float*)0x0066D8C1;

	this->m_Address.RotX = (float*)0x07DCB0B8;

	this->m_Address.RotY = (float*)0x006EA878;

	this->m_Address.PosZ = (float*)0x006E86E4;

	this->m_Address.ClipX = (float*)0x006EA788;

	this->m_Address.ClipY = (float*)0x006EA790;

	this->m_Address.ClipGL = (float*)0x0066DBDC;

	this->m_Default.IsLoad = 0;

	MemorySet(0x0065853E,0x90,6);

	SetCompleteHook(0xE9,0x006585AA,&this->RotateDamageAngle);
}

CCamera::~CCamera() // OK
{

}

void CCamera::Toggle() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		pDrawMessage(pGetTextLine((1992+this->m_Enable)),1);

		this->m_Enable ^= 1;

		if(((this->m_Default.IsLoad == 0) ? (this->m_Default.IsLoad++) : this->m_Default.IsLoad) == 0)
		{
			this->m_Default.Zoom = (*this->m_Address.Zoom);

			this->m_Default.RotX = (*this->m_Address.RotX);

			this->m_Default.RotY = (*this->m_Address.RotY);

			this->m_Default.PosZ = (*this->m_Address.PosZ);

			this->m_Default.ClipX = (*this->m_Address.ClipX);

			this->m_Default.ClipY = (*this->m_Address.ClipY);

			this->m_Default.ClipGL = (*this->m_Address.ClipGL);
		}
	}
}

void CCamera::Restore() // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->SetDefaultValue();
	}
}

void CCamera::SetIsMove(BOOL IsMove) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void CCamera::SetCursorX(LONG CursorX) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void CCamera::SetCursorY(LONG CursorY) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void CCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove != 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default.Zoom/100)*this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default.Zoom/100)*this->m_Zoom.MaxPercent;

	if(((int)lpMouse->mouseData) > 0)
	{
		if((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)-this->m_Zoom.Precision));
		}
	}

	if(((int)lpMouse->mouseData) < 0)
	{
		if((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)+this->m_Zoom.Precision));
		}
	}

	this->SetCurrentValue();
}

void CCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove == 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if(this->m_CursorX < lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)+6.0f));
		}
	}

	if(this->m_CursorX > lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)-6.0f));
		}
	}

	if(this->m_CursorY < lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) < -22.5f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)+2.420f));
			SetFloat((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)-44.0f));
		}
	}

	if(this->m_CursorY > lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) > -90.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)-2.420f));
			SetFloat((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)+44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	this->SetCurrentValue();
}

void CCamera::SetCurrentValue() // OK
{
	SetFloat((DWORD)this->m_Address.ClipX,(4190.0f+(abs(((*this->m_Address.PosZ)-150.0f))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY,(5400.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipGL,(2100.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));
}

void CCamera::SetDefaultValue() // OK
{
	if(this->m_Default.IsLoad != 0)
	{
		SetFloat((DWORD)this->m_Address.Zoom,this->m_Default.Zoom);

		SetFloat((DWORD)this->m_Address.RotX,this->m_Default.RotX);

		SetFloat((DWORD)this->m_Address.RotY,this->m_Default.RotY);

		SetFloat((DWORD)this->m_Address.PosZ,this->m_Default.PosZ);

		SetFloat((DWORD)this->m_Address.ClipX,this->m_Default.ClipX);

		SetFloat((DWORD)this->m_Address.ClipY,this->m_Default.ClipY);

		SetFloat((DWORD)this->m_Address.ClipGL,this->m_Default.ClipGL);
	}

	pDrawMessage(pGetTextLine(1994),1);
}

void CCamera::CalcDamageAngle(float& X,float& Y,float D) // OK
{
	const float DamageAngle = 0.01745329f;

	float AngleX = cos(DamageAngle*(*gCamera.m_Address.RotX));
	float AngleY = sin(DamageAngle*(*gCamera.m_Address.RotX));

	X += D/0.7071067f*AngleX/2;
	Y -= D/0.7071067f*AngleY/2;
}

void __declspec(naked) CCamera::RotateDamageAngle() // OK
{
	static DWORD RotateDamageAngleAddress1 = 0x006585C2;

	_asm
	{
		Add Esp,0x1C
		Lea Eax,[Ebp-0x8]
		Lea Ecx,[Ebp-0xC]
		Push Dword Ptr[Ebp+0x8]
		Push Eax
		Push Ecx
		Call CalcDamageAngle
		Add Esp,0x0C
		Inc Esi
		Cmp Esi,Ebx
		Jmp[RotateDamageAngleAddress1]
	}
}