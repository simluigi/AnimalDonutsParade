/*==================================================================
DIRECTX11 三校合同 main.cpp
「動物ドーナツパレード」
Author: Sim Luigi
Last Updated: 2020.08.27

2020.08.13:	
-donut.cpp, donut.h : Implemented Donut classes
-scene.h : Added AddGameObjectWithID method
-main.h  : Added <ctime> preprocessor command for srand/rand
-others	 : Added comments/cleanup for folders 00 to 03

2020.08.17:
-order.cpp, order.h : Added Order class and included methods
-UI_order.cpp, UI_order.h : Added Order UI display class and included methods

2020.08.18
-order.cpp, order.h, UI_order.cpp, UI_order.h : 
added CustomerQueue and PlayerQueue display (separate from each other)
-game_object.h : added AddGameObjectWithTwoArguments() template
-field.cpp : added MATERIAL (eliminate color change)

2020.08.23
-completing UI assets
-change camera to first person
-added player model (tongs)

2020.08.27
-bullet.cpp : removed completely, implemented player->GetForward collision for donut 
-order.cpp : migrated score elements to score.cpp

2020.08.29
-manager.cpp: added m_FirstPlay and respective get/set methods
-game.cpp : optimized load times (no double reload on game assets) via 
 Get/SetFirstPlay() implementation
 -UI_time.cpp: added countdown

 2020.08.30
 ★　game complete! v1.0　★
 -sound.cpp: all sounds implemented
 -all animations synced to sounds (SFX_Countdown, BGM_Result)
 -UI_Result.cpp: added PRESS ENTER and High Score Donut Icon
 -manager.cpp: UnloadAllResources() implemented as cleanup

 2020.09.01
 -added Player movement restriction
 -replaced Enter key with Space key (submission guidelines!)
===================================================================*/


#include "main.h"
#include "manager.h"

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "★動物ドーナツパレード";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	// Register Window Class
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	// Create Window
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	// 2020.08.13
	// ランダム設定の初期化
	// Initialize random value setup 
	srand(time(0));

	// 初期化処理(ウィンドウを作成してから行う)
	//Initialize all classes after window creation
	CManager::Init();

	// ウインドウの表示(初期化処理の後に行う)
	// Show window after initializing all classes : CManager::Init()
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);

	// フレームカウント初期化
	// Initialize Frame Count
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	// メッセージループ
	// Message Loop
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{	// PostQuitMessage()が呼ばれたらループ終了
				// Exit loop if PostQuitMessage is called
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				// Translate/Dispatch Message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			// 時間経過処理
			// Time elapsed processing
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				// Update all
				CManager::Update();

				// 描画処理
				// Draw all
				CManager::Draw();
			}
		}
	}

	// 分解能を戻す
	// return resolution value
	timeEndPeriod(1);				

	// ウィンドウクラスの登録を解除
	// unregister window class
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 2020.08.29
	// 後片付け：全ての使用済みリソースをアンロード
	// Cleanup: Unload all assets
	CManager::UnloadAllResources();

	// 終了処理
	// Uninit all (game exit)
	CManager::Uninit();
	

	return (int)msg.wParam;
}


//=============================================================================
// ウインドウプロシージャ
// Window Procedure
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			if (MessageBox(hWnd, "本当に終了してよろしいでしょうかにゃ～？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) ==IDOK )
				DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

