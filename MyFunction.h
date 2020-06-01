#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Disc.h"

#define Wstr "\\\\.\\"
#define endStr ":"
#define PhysDrive "\\\\.\\PHYSICALDRIVE0" 

using namespace std;

void Menu();

void Print_PhisicalDrive(const char *drive);

bool ByteChange();

void SectionChange();