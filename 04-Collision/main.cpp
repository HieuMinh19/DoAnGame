﻿/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "Goomba.h"
#include "Fire.h"
#include "BackGround.h"
#include "MorningStar.h"
#include "Global.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

#define MAX_FRAME_RATE	120
#define Y_SOILD			150			//y position of enemy in the ground

#define ID_TEX_SIMON		100
#define ID_TEX_ENEMY		200
#define ID_TEX_MISC			300
#define ID_TEX_BACKGROUND	400
#define ID_TEX_FIRE			500
#define ID_TEX_WEAPON		600

#define SIMON_ANI_IDLE_RIGHT	400
#define SIMON_ANI_IDLE_LEFT		401 
#define SIMON_ANI_WALK_LEFT		501
#define SIMON_ANI_WALK_RIGHT	500  
#define SIMON_ANI_DOWN_RIGHT	402
#define SIMON_ANI_DOWN_LEFT		403
#define SIMON_ANI_ATTACT_LEFT	106
#define SIMON_ANI_ATTACT_RIGHT	107


CGame *game;

CSimon *simon;

CBackGround *background;
CFire *fire;
CMorningstar *weapon;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		//cho simon roi xuong 
		simon->SetPosition(50.0f,0.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_X:
		simon->StartAttact();
		simon->getMorningStar()->SetPosition(simon->x, simon->y);
		weapon->setAttact(simon->nx);
		break;
	}
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT)) 
		simon->SetState(SIMON_STATE_WALKING_RIGHT);		
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
	if(game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SITDOWN);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"textures\\not_weapons.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BACKGROUND, L"textures\\Level_1_Entrance.png", D3DCOLOR_XRGB(0, 128, 128));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_FIRE, L"textures\\fire.png", D3DCOLOR_XRGB(255, 0, 255));
	//sprite bi dao nguoc -> can lay right_bottom top_left
	textures->Add(ID_TEX_WEAPON, L"textures\\Resources\\morningstar.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	
	int IDSprite = 0;
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 16; j++) {
			IDSprite++;
			sprites->Add(IDSprite*ID_TEX_SIMON, 30*j, i*33, 30*j+30, 33*i+33, texSimon);
		}
	
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 1, 1, 30, 30, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);
	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	LPANIMATION ani;	

	ani = new CAnimation(FRAME_LASTED);	// idle right
	ani->Add(1400);
	animations->Add(SIMON_ANI_IDLE_RIGHT, ani);

	ani = new CAnimation(FRAME_LASTED);	// walk right
	ani->Add(1400);
	ani->Add(1500);	
	ani->Add(1600);	
	animations->Add(SIMON_ANI_WALK_RIGHT, ani);

	ani = new CAnimation(FRAME_LASTED);	// ngoi phai
	ani->Add(1200);
	animations->Add(SIMON_ANI_DOWN_RIGHT, ani);

	ani = new CAnimation(FRAME_LASTED);	// idle left
	ani->Add(300);
	animations->Add(SIMON_ANI_IDLE_LEFT, ani);

	ani = new CAnimation(FRAME_LASTED);	// // walk left
	ani->Add(300);
	ani->Add(200);
	ani->Add(100);
	animations->Add(SIMON_ANI_WALK_LEFT, ani);

	ani = new CAnimation(ATTACT_FRAME_LASTED);
	ani->Add(600);
	ani->Add(700);
	ani->Add(800);
	animations->Add(SIMON_ANI_ATTACT_LEFT, ani);

	ani = new CAnimation(ATTACT_FRAME_LASTED);
	ani->Add(1100);
	ani->Add(1000);
	ani->Add(900);
	animations->Add(SIMON_ANI_ATTACT_RIGHT, ani);

	ani = new CAnimation(FRAME_LASTED);	// ngoi trai
	ani->Add(500);
	animations->Add(SIMON_ANI_DOWN_LEFT, ani);

	ani = new CAnimation(FRAME_LASTED);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	//add weapon enemy
	LPDIRECT3DTEXTURE9 texWeapon = textures->Get(ID_TEX_WEAPON);
	sprites->Add(60000, 63, 5, 80, 35, texWeapon);
	sprites->Add(60004, 505, 30, 480, 5, texWeapon);
	sprites->Add(60002, 205, 20, 175, 5, texWeapon);

	//attact right
	sprites->Add(60001, 160, 30, 135, 5, texWeapon);
	sprites->Add(60003, 465, 20, 440, 5, texWeapon);
	sprites->Add(60005, 560, 5, 575, 35, texWeapon);

	weapon = new CMorningstar();
	ani = new CAnimation(ATTACT_FRAME_LASTED);
	ani->Add(60000);
	ani->Add(60004);
	ani->Add(60002);
	animations->Add(6001, ani);
	weapon->AddAnimation(6001);	//morningstar attact left

	ani = new CAnimation(ATTACT_FRAME_LASTED);
	ani->Add(60005);
	ani->Add(60001);
	ani->Add(60003);
	animations->Add(6002, ani);
	weapon->AddAnimation(6002);	//morningstar attact right

	weapon->SetPosition(70.0f, Y_SOILD - 60);
	objects.push_back(weapon);


	simon = new CSimon(weapon);
	simon->AddAnimation(SIMON_ANI_IDLE_RIGHT);		         
	simon->AddAnimation(SIMON_ANI_IDLE_LEFT);		                     
	simon->AddAnimation(SIMON_ANI_WALK_RIGHT);		              
	simon->AddAnimation(SIMON_ANI_WALK_LEFT);				
	simon->AddAnimation(SIMON_ANI_DOWN_RIGHT);		 
	simon->AddAnimation(SIMON_ANI_DOWN_LEFT);
	simon->AddAnimation(SIMON_ANI_ATTACT_LEFT);
	simon->AddAnimation(SIMON_ANI_ATTACT_RIGHT);
	
	// background
	LPDIRECT3DTEXTURE9 texBG = textures->Get(ID_TEX_BACKGROUND);
	sprites->Add(70010, 0, 0, 770, 185, texBG);
	background = new CBackGround();
	ani = new CAnimation(100);		
	ani->Add(70010);
	animations->Add(701, ani);
	background->AddAnimation(701);
	objects.push_back(background);

	//add fire enemy
	LPDIRECT3DTEXTURE9 texFire = textures->Get(ID_TEX_FIRE);
	sprites->Add(4001, 0, 0, 32, 63, texFire);
	sprites->Add(4002, 32, 0, 63, 63, texFire);
	fire = new CFire();
	ani = new CAnimation(200);
	ani->Add(4001);
	ani->Add(4002);
	animations->Add(40, ani);
	fire->AddAnimation(40);
	fire->SetPosition(20.0f, Y_SOILD-60);
	objects.push_back(fire);

	objects.push_back(simon);


	//khoi tao hang gach ngang
	for (int i = 0; i < 50; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i * 16.0f, Y_SOILD);
		objects.push_back(brick);
	}
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		for (int i = 0; i < objects.size(); i++) {
			//x va y dong vai tro la x_cam
			float x = simon->x - SCREEN_WIDTH/2;		//khoi tao gia tri x_cam ban dau  = x_simon
			float y = 0;
		
			float left, top, right, bottom;
			background->GetBoundingBox(left, top, right, bottom);
			
			//gioi han dau map
			if (x < 0)
				x = 0;		//khoi tao gia tri ban dau x_cam= 0
			//gioi han cuoi map
			else if (x > (right- SCREEN_WIDTH))
				x = right - SCREEN_WIDTH;
			objects[i]->Render(x,y);
		}
		spriteHandler->End();
		d3ddv->EndScene();
	}
	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}