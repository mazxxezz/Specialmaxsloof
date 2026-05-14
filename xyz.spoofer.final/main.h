
#ifndef __MAIN_H__
#define __MAIN_H__

// Windows 11 compatibility
#define _WIN32_WINNT 0x0A00     // Windows 10 and later
#define WINVER 0x0A00
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <d3d9.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "btfile/bytetofile.hpp"
#include "bytes/bytes.hpp"
#include "bytes/logo.hpp"
#include "bytes/font.h"
#include "menus.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "HWID Spoofer - Windows 11"

extern HWND main_hwnd;
extern IDirect3DDevice9* g_pd3dDevice;
extern D3DPRESENT_PARAMETERS g_d3dpp;
extern Menu* m_Menu;
extern bool loader_active;
extern std::string imagePath;

// Forward declarations
extern LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern HRESULT CreateDeviceD3D(HWND hWnd);
extern void CleanupDeviceD3D();
extern void ResetDevice();
extern HRESULT LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
extern bool FileExists(const std::string& path);

#endif
