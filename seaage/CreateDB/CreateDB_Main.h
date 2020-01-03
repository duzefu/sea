/*
**	CreateDB_Main.h 
**	create database functions.
**
**	Jack, 2003.1.8
*/
#pragma once
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#include "NetGE_MainFunc.h"
#include "CreateDB_Test.h"



#ifdef	_DEBUG
#pragma comment(lib, "ComLibdbg")
#pragma comment(lib, "2denginedbg.lib")
#else//!_DEBUG
#pragma comment(lib, "ComLib")
#pragma comment(lib, "2dengine.lib")
#endif//_DEBUG


