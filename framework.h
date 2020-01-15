// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib, "msimg32.lib") //TransparentBlt 를 사용하기 위함.

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<stdio.h>
// 리소스 헤더
#include"resource.h"

//전역 변수
extern HINSTANCE hInst; 
extern HWND exturn_hwnd;

//싱글톤 
#include"CStatusManger.h"