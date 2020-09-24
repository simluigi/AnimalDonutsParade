/*==================================================================
DIRECTX11 三校合同 main.h
Author: Sim Luigi
Last Updated: 2020.08.13

2020.08.13:
-main.h  : Added <ctime> preprocessor command for srand/rand
===================================================================*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>

// 2020.08.13 
// 乱数処理の初期化
// Added for randomizer use
#include <ctime>

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")

// Aspect Ratio 16:9

// Full HD 1080p
//#define SCREEN_WIDTH	(1920)			// ウインドウの幅
//#define SCREEN_HEIGHT	(1080)			// ウインドウの高さ

// Mid Resolution 720p
#define SCREEN_WIDTH	(1280)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ

// 2020.08.23 Adjusting screen resolution
//static int g_ScreenWidth;
//static int g_ScreenHeight;
//
//static int GetScreenWidth() { return g_ScreenWidth; }
//static int GetScreenHeight() { return g_ScreenHeight; }

HWND GetWindow();
