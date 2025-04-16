#pragma once

void InitItem();
void InitJewel();
void InitWing();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index,char* folder,char* name);
void LoadItemTexture(int index,char* folder);
void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);
void GetItemEffect(DWORD a,int b,float* c,float d,int e,int f,int g,int h,int i);
void DrawItemToolTip(DWORD address);
bool MoveItem(DWORD a,DWORD b,int c,int d,int e);
void WingMakePreviewCharSet(int a,BYTE* b,int c,int d,int e,int f,int g);
void GetItemToolTip();
void JewelCheckApplyItem1();
void JewelCheckApplyItem2();
void JewelCheckIndex1();
void JewelCheckIndex2();
void JewelCheckIndex3();
void JewelCheckIndex4();