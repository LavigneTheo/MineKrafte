#pragma once
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <tchar.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
std::string BrowseFolder(std::string saved_path);
std::string get_path();
