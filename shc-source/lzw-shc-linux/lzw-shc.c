#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>
#include <string.h>

#include "lzw-decode.h"

// Defined in arch-selection block
//#include "my_mmap.h"

#define OVER_SHELLCODE

// INPUT/OUTPUT
#define FILENAME_INPUT "infile.lzw"
#define FILENAME_OUTPUT "outfile"

#ifdef OVER_SHELLCODE
//https://sourceforge.net/p/predef/wiki/Architectures/
#ifdef __i386__
    #ifndef _SHELLCODE_DEFINED
		#include "my_mmap_i386.h"
        #define _SHELLCODE_DEFINED
        byte shellcode[] = { 0x55, 0x57, 0x56, 0x53, 0x83, 0xec, 0x34, 0x8b, 0x6c, 0x24, 0x48, 0x6a, 0x00, 0x6a, 0xff, 0x6a,
			0x22, 0x6a, 0x03, 0x68, 0x08, 0x0c, 0x00, 0x00, 0x6a, 0x00, 0xe8, 0x4a, 0x03, 0x00, 0x00, 0x8d,
			0x90, 0x07, 0x0c, 0x00, 0x00, 0x8d, 0x48, 0xff, 0x83, 0xc4, 0x20, 0x90, 0x8d, 0x74, 0x26, 0x00,
			0xc6, 0x02, 0x00, 0x83, 0xea, 0x01, 0x39, 0xca, 0x75, 0xf6, 0xc7, 0x00, 0x06, 0x00, 0x00, 0x00,
			0xc7, 0x40, 0x04, 0x00, 0x02, 0x00, 0x00, 0x8d, 0x58, 0x08, 0x8d, 0x50, 0x0c, 0x31, 0xc0, 0x90,
			0x88, 0x02, 0x83, 0xc0, 0x01, 0x83, 0xc2, 0x06, 0x3d, 0x00, 0x01, 0x00, 0x00, 0x75, 0xf1, 0x8b,
			0x7c, 0x24, 0x44, 0x31, 0xf6, 0x85, 0xff, 0x0f, 0x84, 0x2b, 0x02, 0x00, 0x00, 0xb8, 0x02, 0x01,
			0x00, 0x00, 0xc7, 0x04, 0x24, 0x09, 0x00, 0x00, 0x00, 0xc7, 0x44, 0x24, 0x0c, 0x00, 0x02, 0x00,
			0x00, 0x66, 0x89, 0x44, 0x24, 0x0a, 0xc7, 0x44, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00, 0x31, 0xf6,
			0xc7, 0x44, 0x24, 0x04, 0x00, 0x00, 0x00, 0x00, 0x90, 0x8d, 0xb4, 0x26, 0x00, 0x00, 0x00, 0x00,
			0x3b, 0x34, 0x24, 0x8b, 0x44, 0x24, 0x04, 0x8b, 0x14, 0x24, 0x0f, 0x8d, 0x6a, 0x02, 0x00, 0x00,
			0x85, 0xff, 0x7e, 0x34, 0x83, 0xc5, 0x01, 0x0f, 0xb6, 0x4d, 0xff, 0xc1, 0xe0, 0x08, 0x83, 0xc6,
			0x08, 0x83, 0xef, 0x01, 0x09, 0xc8, 0x39, 0xd6, 0x7c, 0xe6, 0x2b, 0x34, 0x24, 0xba, 0x01, 0x00,
			0x00, 0x00, 0x89, 0xf1, 0xd3, 0xe2, 0x89, 0xc1, 0x83, 0xea, 0x01, 0x21, 0xd1, 0x89, 0x4c, 0x24,
			0x04, 0xeb, 0x16, 0x90, 0x8d, 0x74, 0x26, 0x00, 0x8b, 0x0c, 0x24, 0xc7, 0x44, 0x24, 0x04, 0x00,
			0x00, 0x00, 0x00, 0x29, 0xf1, 0x31, 0xf6, 0xd3, 0xe0, 0x89, 0xf1, 0xd3, 0xe8, 0x66, 0x3d, 0x01,
			0x01, 0x89, 0xc1, 0x66, 0x89, 0x44, 0x24, 0x10, 0x0f, 0x84, 0x86, 0x01, 0x00, 0x00, 0x66, 0x3d,
			0x00, 0x01, 0x0f, 0x84, 0xa0, 0x01, 0x00, 0x00, 0x66, 0x3b, 0x44, 0x24, 0x0a, 0x0f, 0x83, 0x71,
			0x01, 0x00, 0x00, 0x0f, 0xb7, 0x44, 0x24, 0x0a, 0x66, 0x81, 0xf9, 0xff, 0x00, 0x8d, 0x04, 0x40,
			0x8d, 0x14, 0x00, 0x66, 0x89, 0x0c, 0x43, 0x89, 0x54, 0x24, 0x18, 0x0f, 0xb7, 0x54, 0x24, 0x10,
			0x0f, 0x86, 0xf4, 0x01, 0x00, 0x00, 0x8d, 0x76, 0x00, 0x8d, 0xbc, 0x27, 0x00, 0x00, 0x00, 0x00,
			0x0f, 0xb7, 0xc2, 0x8d, 0x04, 0x40, 0x0f, 0xb7, 0x04, 0x43, 0x89, 0xc1, 0x8d, 0x04, 0x40, 0x66,
			0x81, 0xf9, 0xff, 0x00, 0x8d, 0x04, 0x43, 0x66, 0x89, 0x50, 0x02, 0x89, 0xca, 0x77, 0xe1, 0x66,
			0x89, 0x4c, 0x24, 0x10, 0x0f, 0xb6, 0x54, 0x24, 0x10, 0x8b, 0x4c, 0x24, 0x18, 0x88, 0x54, 0x0b,
			0xfe, 0x89, 0x74, 0x24, 0x10, 0x8b, 0x4c, 0x24, 0x14, 0x8b, 0x74, 0x24, 0x48, 0x8d, 0x76, 0x00,
			0x0f, 0xb6, 0x50, 0x04, 0x83, 0xc1, 0x01, 0x88, 0x54, 0x0e, 0xff, 0x0f, 0xb7, 0x50, 0x02, 0x66,
			0xc7, 0x40, 0x02, 0x00, 0x00, 0x8d, 0x04, 0x52, 0x8d, 0x04, 0x43, 0x66, 0x83, 0x78, 0x02, 0x00,
			0x75, 0xde, 0x8b, 0x74, 0x24, 0x10, 0x8d, 0x51, 0x01, 0x0f, 0xb6, 0x40, 0x04, 0x66, 0x83, 0x44,
			0x24, 0x0a, 0x01, 0x89, 0x54, 0x24, 0x14, 0x8b, 0x54, 0x24, 0x48, 0x88, 0x04, 0x0a, 0x0f, 0xb7,
			0x44, 0x24, 0x0a, 0x3b, 0x44, 0x24, 0x0c, 0x0f, 0x8c, 0xaf, 0x00, 0x00, 0x00, 0x83, 0x04, 0x24,
			0x01, 0x8b, 0x04, 0x24, 0x83, 0xf8, 0x10, 0x0f, 0x8f, 0xa7, 0x00, 0x00, 0x00, 0x8d, 0x4b, 0xf8,
			0xd1, 0x64, 0x24, 0x0c, 0x83, 0xec, 0x08, 0x8b, 0x44, 0x24, 0x14, 0x89, 0x4c, 0x24, 0x20, 0x6a,
			0x00, 0x6a, 0xff, 0x6a, 0x22, 0x6a, 0x03, 0x89, 0x44, 0x24, 0x24, 0x0f, 0xaf, 0x43, 0xf8, 0x83,
			0xc0, 0x08, 0x50, 0x6a, 0x00, 0xe8, 0x4f, 0x01, 0x00, 0x00, 0x8b, 0x53, 0xfc, 0x89, 0xc1, 0x89,
			0x54, 0x24, 0x30, 0x83, 0xc4, 0x20, 0x39, 0x54, 0x24, 0x0c, 0x0f, 0x86, 0xda, 0x00, 0x00, 0x00,
			0x8b, 0x44, 0x24, 0x10, 0x0f, 0xaf, 0x43, 0xf8, 0x83, 0xc0, 0x08, 0x85, 0xc0, 0x8d, 0x50, 0xff,
			0x74, 0x1d, 0x8d, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xb6, 0x44, 0x13, 0xf8, 0x88, 0x04, 0x11,
			0x83, 0xea, 0x01, 0x83, 0xfa, 0xff, 0x75, 0xf0, 0x8b, 0x43, 0xfc, 0x89, 0x44, 0x24, 0x10, 0x89,
			0x4c, 0x24, 0x1c, 0x83, 0xec, 0x08, 0x8b, 0x44, 0x24, 0x18, 0x0f, 0xaf, 0x43, 0xf8, 0x83, 0xc0,
			0x08, 0x50, 0xff, 0x74, 0x24, 0x24, 0xe8, 0x03, 0x01, 0x00, 0x00, 0x8b, 0x4c, 0x24, 0x2c, 0x8b,
			0x44, 0x24, 0x1c, 0x83, 0xc4, 0x10, 0x8d, 0x59, 0x08, 0x89, 0x41, 0x04, 0x85, 0xff, 0x0f, 0x85,
			0x0c, 0xfe, 0xff, 0xff, 0x8b, 0x74, 0x24, 0x14, 0x8b, 0x43, 0xfc, 0x83, 0xec, 0x08, 0x83, 0xeb,
			0x08, 0x0f, 0xaf, 0x03, 0x50, 0x53, 0xe8, 0xd3, 0x00, 0x00, 0x00, 0x83, 0xc4, 0x3c, 0x89, 0xf0,
			0x5b, 0x5e, 0x5f, 0x5d, 0xc3, 0x8d, 0x76, 0x00, 0x8b, 0x43, 0xfc, 0x0f, 0xaf, 0x43, 0xf8, 0x85,
			0xc0, 0x74, 0x10, 0x90, 0x8d, 0x74, 0x26, 0x00, 0x83, 0xe8, 0x01, 0x85, 0xc0, 0xc6, 0x04, 0x03,
			0x00, 0x75, 0xf5, 0x8d, 0x53, 0x04, 0x31, 0xc0, 0x90, 0x8d, 0xb4, 0x26, 0x00, 0x00, 0x00, 0x00,
			0x88, 0x02, 0x83, 0xc0, 0x01, 0x83, 0xc2, 0x06, 0x3d, 0x00, 0x01, 0x00, 0x00, 0x75, 0xf1, 0xb8,
			0x02, 0x01, 0x00, 0x00, 0xc7, 0x04, 0x24, 0x09, 0x00, 0x00, 0x00, 0xc7, 0x44, 0x24, 0x0c, 0x00,
			0x02, 0x00, 0x00, 0x66, 0x89, 0x44, 0x24, 0x0a, 0xeb, 0x82, 0x8b, 0x44, 0x24, 0x0c, 0x0f, 0xaf,
			0x43, 0xf8, 0x83, 0xc0, 0x08, 0xe9, 0x21, 0xff, 0xff, 0xff, 0x2b, 0x34, 0x24, 0xba, 0x01, 0x00,
			0x00, 0x00, 0x89, 0xf1, 0xd3, 0xe2, 0x8b, 0x4c, 0x24, 0x04, 0x83, 0xea, 0x01, 0x89, 0xc8, 0x21,
			0xd1, 0x89, 0x4c, 0x24, 0x04, 0xe9, 0xbf, 0xfd, 0xff, 0xff, 0x0f, 0xb7, 0xc1, 0x8d, 0x04, 0x40,
			0x8d, 0x04, 0x43, 0x0f, 0xb7, 0x50, 0x02, 0x66, 0x89, 0x54, 0x24, 0x10, 0x66, 0x83, 0x7c, 0x24,
			0x10, 0x00, 0x8b, 0x54, 0x24, 0x18, 0x88, 0x4c, 0x13, 0xfe, 0x0f, 0x85, 0x21, 0xfe, 0xff, 0xff,
			0x8b, 0x4c, 0x24, 0x14, 0xe9, 0x4d, 0xfe, 0xff, 0xff, 0x55, 0x57, 0x56, 0x53, 0x89, 0xe3, 0x83,
			0xc3, 0x14, 0xb8, 0x5a, 0x00, 0x00, 0x00, 0xcd, 0x80, 0x5b, 0x5e, 0x5f, 0x5d, 0xc3, 0x55, 0x57,
			0x56, 0x53, 0x8b, 0x5c, 0x24, 0x14, 0x8b, 0x4c, 0x24, 0x18, 0xb8, 0x5b, 0x00, 0x00, 0x00, 0xcd,
			0x80, 0x5b, 0x5e, 0x5f, 0x5d, 0xc3 };
    #else
        #error Some fck with arch selecting...
    #endif
#endif
#ifdef __amd64__
    #ifndef _SHELLCODE_DEFINED
		#include "my_mmap_x86_64.h"
        #define _SHELLCODE_DEFINED
        byte shellcode[] = { 0x41, 0x57, 0x41, 0x56, 0x45, 0x31, 0xc9, 0x41, 0x55, 0x41, 0x54, 0x49, 0x89, 0xfe, 0x55, 0x53,
			0x41, 0xb8, 0xff, 0xff, 0xff, 0xff, 0x48, 0x89, 0xf3, 0xb9, 0x22, 0x00, 0x00, 0x00, 0xbe, 0x10,
			0x0c, 0x00, 0x00, 0x48, 0x83, 0xec, 0x38, 0x31, 0xff, 0x48, 0x89, 0x54, 0x24, 0x10, 0xba, 0x03,
			0x00, 0x00, 0x00, 0xe8, 0x95, 0x03, 0x00, 0x00, 0x49, 0x89, 0xc3, 0x48, 0x8d, 0x80, 0x0f, 0x0c,
			0x00, 0x00, 0x49, 0x8d, 0x53, 0xff, 0x66, 0x2e, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xc6, 0x00, 0x00, 0x48, 0x83, 0xe8, 0x01, 0x48, 0x39, 0xd0, 0x75, 0xf4, 0x49, 0x8d, 0x6b, 0x10,
			0x49, 0x8d, 0x53, 0x14, 0x49, 0xc7, 0x03, 0x06, 0x00, 0x00, 0x00, 0x49, 0xc7, 0x43, 0x08, 0x00,
			0x02, 0x00, 0x00, 0x31, 0xc0, 0x0f, 0x1f, 0x00, 0x88, 0x02, 0x83, 0xc0, 0x01, 0x48, 0x83, 0xc2,
			0x06, 0x3d, 0x00, 0x01, 0x00, 0x00, 0x75, 0xf0, 0x85, 0xdb, 0x41, 0x89, 0xdd, 0x0f, 0x84, 0x2e,
			0x03, 0x00, 0x00, 0x31, 0xdb, 0x41, 0xba, 0x02, 0x01, 0x00, 0x00, 0x45, 0x31, 0xe4, 0x41, 0xbf,
			0x09, 0x00, 0x00, 0x00, 0xc7, 0x44, 0x24, 0x08, 0x00, 0x02, 0x00, 0x00, 0xc7, 0x44, 0x24, 0x0c,
			0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x40, 0x00, 0x45, 0x39, 0xfc, 0x7d, 0x33, 0x41, 0x8d, 0x47,
			0xff, 0x44, 0x29, 0xe0, 0x83, 0xe0, 0xf8, 0x41, 0x8d, 0x54, 0x04, 0x08, 0x0f, 0x1f, 0x40, 0x00,
			0x45, 0x85, 0xed, 0x7e, 0x73, 0x49, 0x83, 0xc6, 0x01, 0x41, 0x0f, 0xb6, 0x46, 0xff, 0xc1, 0xe3,
			0x08, 0x41, 0x83, 0xc4, 0x08, 0x41, 0x83, 0xed, 0x01, 0x09, 0xc3, 0x44, 0x39, 0xe2, 0x75, 0xe0,
			0x45, 0x29, 0xfc, 0xba, 0x01, 0x00, 0x00, 0x00, 0x89, 0xd8, 0x44, 0x89, 0xe1, 0xd3, 0xe2, 0x44,
			0x89, 0xe1, 0x83, 0xea, 0x01, 0xd3, 0xe8, 0x21, 0xd3, 0x66, 0x3d, 0x01, 0x01, 0x89, 0xc1, 0x0f,
			0xb7, 0xd0, 0x75, 0x53, 0x48, 0x8b, 0x45, 0xf0, 0x48, 0x63, 0x5c, 0x24, 0x0c, 0x4c, 0x8d, 0x5d,
			0xf0, 0x48, 0x0f, 0xaf, 0x45, 0xf8, 0x48, 0x89, 0xc6, 0x4c, 0x89, 0xdf, 0xe8, 0xc0, 0x02, 0x00,
			0x00, 0x48, 0x83, 0xc4, 0x38, 0x48, 0x89, 0xd8, 0x5b, 0x5d, 0x41, 0x5c, 0x41, 0x5d, 0x41, 0x5e,
			0x41, 0x5f, 0xc3, 0x0f, 0x1f, 0x44, 0x00, 0x00, 0x44, 0x89, 0xf9, 0x89, 0xd8, 0x31, 0xdb, 0x44,
			0x29, 0xe1, 0x45, 0x31, 0xe4, 0xd3, 0xe0, 0x44, 0x89, 0xe1, 0xd3, 0xe8, 0x66, 0x3d, 0x01, 0x01,
			0x89, 0xc1, 0x0f, 0xb7, 0xd0, 0x74, 0xad, 0x66, 0x3d, 0x00, 0x01, 0x0f, 0x84, 0xaf, 0x01, 0x00,
			0x00, 0x66, 0x44, 0x39, 0xd0, 0x73, 0x9d, 0x41, 0x0f, 0xb7, 0xc2, 0x66, 0x81, 0xf9, 0xff, 0x00,
			0x48, 0x8d, 0x04, 0x40, 0x48, 0x8d, 0x34, 0x00, 0x66, 0x89, 0x4c, 0x45, 0x00, 0x0f, 0x86, 0xf5,
			0x01, 0x00, 0x00, 0x0f, 0x1f, 0x44, 0x00, 0x00, 0x0f, 0xb7, 0xc2, 0x48, 0x8d, 0x04, 0x40, 0x0f,
			0xb7, 0x44, 0x45, 0x00, 0x48, 0x89, 0xc1, 0x48, 0x8d, 0x04, 0x40, 0x66, 0x81, 0xf9, 0xff, 0x00,
			0x48, 0x8d, 0x44, 0x45, 0x00, 0x66, 0x89, 0x50, 0x02, 0x89, 0xca, 0x77, 0xdb, 0x88, 0x4c, 0x35,
			0xfe, 0x8b, 0x4c, 0x24, 0x0c, 0x48, 0x8b, 0x7c, 0x24, 0x10, 0x83, 0xc1, 0x01, 0x48, 0x83, 0xef,
			0x01, 0x48, 0x63, 0xc9, 0x0f, 0x1f, 0x40, 0x00, 0x0f, 0xb6, 0x50, 0x04, 0x45, 0x31, 0xc0, 0x48,
			0x63, 0xf1, 0x88, 0x14, 0x0f, 0x0f, 0xb7, 0x50, 0x02, 0x48, 0x83, 0xc1, 0x01, 0x66, 0x44, 0x89,
			0x40, 0x02, 0x0f, 0xb7, 0xc2, 0x48, 0x8d, 0x04, 0x40, 0x48, 0x8d, 0x44, 0x45, 0x00, 0x66, 0x83,
			0x78, 0x02, 0x00, 0x75, 0xd3, 0x8d, 0x7e, 0x01, 0x0f, 0xb6, 0x40, 0x04, 0x41, 0x83, 0xc2, 0x01,
			0x4c, 0x8d, 0x5d, 0xf0, 0x89, 0x7c, 0x24, 0x0c, 0x48, 0x8b, 0x7c, 0x24, 0x10, 0x88, 0x04, 0x37,
			0x41, 0x0f, 0xb7, 0xc2, 0x3b, 0x44, 0x24, 0x08, 0x7d, 0x26, 0x45, 0x85, 0xed, 0x0f, 0x85, 0x85,
			0xfe, 0xff, 0xff, 0x48, 0x8b, 0x45, 0xf0, 0x48, 0x63, 0x5c, 0x24, 0x0c, 0x48, 0x0f, 0xaf, 0x45,
			0xf8, 0x48, 0x89, 0xc6, 0xe9, 0xe0, 0xfe, 0xff, 0xff, 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00,
			0x41, 0x83, 0xc7, 0x01, 0x48, 0x8b, 0x75, 0xf0, 0x41, 0x83, 0xff, 0x10, 0x0f, 0x8f, 0x4a, 0x01,
			0x00, 0x00, 0xd1, 0x64, 0x24, 0x08, 0x45, 0x31, 0xc9, 0xb9, 0x22, 0x00, 0x00, 0x00, 0x48, 0x63,
			0x44, 0x24, 0x08, 0xba, 0x03, 0x00, 0x00, 0x00, 0x31, 0xff, 0x41, 0xb8, 0xff, 0xff, 0xff, 0xff,
			0x4c, 0x89, 0x5c, 0x24, 0x28, 0x44, 0x89, 0x54, 0x24, 0x20, 0x48, 0x0f, 0xaf, 0xf0, 0x48, 0x89,
			0x44, 0x24, 0x18, 0x48, 0x83, 0xc6, 0x10, 0xe8, 0x31, 0x01, 0x00, 0x00, 0x48, 0x8b, 0x55, 0xf8,
			0x48, 0x39, 0x54, 0x24, 0x18, 0x48, 0x89, 0xc1, 0x44, 0x8b, 0x54, 0x24, 0x20, 0x4c, 0x8b, 0x5c,
			0x24, 0x28, 0x0f, 0x86, 0xbd, 0x00, 0x00, 0x00, 0x48, 0x8b, 0x75, 0xf0, 0x48, 0x0f, 0xaf, 0xf2,
			0x48, 0x83, 0xc6, 0x10, 0x48, 0x85, 0xf6, 0x48, 0x8d, 0x46, 0xff, 0x74, 0x19, 0x0f, 0x1f, 0x00,
			0x0f, 0xb6, 0x54, 0x05, 0xf0, 0x88, 0x14, 0x01, 0x48, 0x83, 0xe8, 0x01, 0x48, 0x83, 0xf8, 0xff,
			0x75, 0xee, 0x48, 0x8b, 0x55, 0xf8, 0x48, 0x0f, 0xaf, 0x55, 0xf0, 0x4c, 0x89, 0xdf, 0x44, 0x89,
			0x54, 0x24, 0x28, 0x48, 0x89, 0x4c, 0x24, 0x20, 0x48, 0x8d, 0x72, 0x10, 0xe8, 0xf0, 0x00, 0x00,
			0x00, 0x48, 0x8b, 0x4c, 0x24, 0x20, 0x48, 0x8b, 0x44, 0x24, 0x18, 0x44, 0x8b, 0x54, 0x24, 0x28,
			0x48, 0x89, 0x41, 0x08, 0x48, 0x8d, 0x69, 0x10, 0x49, 0x89, 0xcb, 0xe9, 0x0a, 0xff, 0xff, 0xff,
			0x48, 0x8b, 0x45, 0xf0, 0x48, 0x0f, 0xaf, 0x45, 0xf8, 0x48, 0x85, 0xc0, 0x74, 0x10, 0x66, 0x90,
			0x48, 0x83, 0xe8, 0x01, 0x48, 0x85, 0xc0, 0xc6, 0x44, 0x05, 0x00, 0x00, 0x75, 0xf2, 0x48, 0x8d,
			0x55, 0x04, 0x31, 0xc0, 0x0f, 0x1f, 0x40, 0x00, 0x88, 0x02, 0x83, 0xc0, 0x01, 0x48, 0x83, 0xc2,
			0x06, 0x3d, 0x00, 0x01, 0x00, 0x00, 0x75, 0xf0, 0x4c, 0x8d, 0x5d, 0xf0, 0x41, 0xba, 0x02, 0x01,
			0x00, 0x00, 0x41, 0xbf, 0x09, 0x00, 0x00, 0x00, 0xc7, 0x44, 0x24, 0x08, 0x00, 0x02, 0x00, 0x00,
			0xe9, 0xb5, 0xfe, 0xff, 0xff, 0x48, 0x8b, 0x74, 0x24, 0x18, 0x48, 0x0f, 0xaf, 0x75, 0xf0, 0x48,
			0x83, 0xc6, 0x10, 0xe9, 0x3c, 0xff, 0xff, 0xff, 0x48, 0x8d, 0x04, 0x52, 0x48, 0x8d, 0x44, 0x45,
			0x00, 0x0f, 0xb7, 0x50, 0x02, 0x88, 0x4c, 0x35, 0xfe, 0x66, 0x85, 0xd2, 0x0f, 0x85, 0x1f, 0xfe,
			0xff, 0xff, 0x48, 0x63, 0x74, 0x24, 0x0c, 0xe9, 0x59, 0xfe, 0xff, 0xff, 0x48, 0x8b, 0x45, 0xf8,
			0x48, 0x63, 0x5c, 0x24, 0x0c, 0x48, 0x0f, 0xaf, 0xc6, 0x48, 0x89, 0xc6, 0xe9, 0x68, 0xfd, 0xff,
			0xff, 0x31, 0xdb, 0xbe, 0x00, 0x0c, 0x00, 0x00, 0xe9, 0x5c, 0xfd, 0xff, 0xff, 0x55, 0x48, 0x89,
			0xe5, 0x89, 0x55, 0xf8, 0x89, 0x4d, 0xf4, 0x44, 0x89, 0x45, 0xf0, 0x8b, 0x55, 0xf8, 0x44, 0x8b,
			0x55, 0xf4, 0x44, 0x8b, 0x45, 0xf0, 0x48, 0xc7, 0xc0, 0x09, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x5d,
			0xc3, 0x55, 0x48, 0x89, 0xe5, 0x48, 0xc7, 0xc0, 0x0b, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x5d, 0xc3 };
    #else
        #error Some fck with arch selecting...
    #endif
#endif
// May be you want to expand this list? I'll wait your commit like hatiko...
#endif

int main()
{
	byte * in = (byte *)malloc(1048576);
	byte * out = (byte *)malloc(1048576);
	size_t in_size;
	size_t out_size;
	// Read input file
	FILE * fd = fopen(FILENAME_INPUT, "rb");
	if (fd == NULL)
	{
		fprintf(stderr, "Can't open file '%s'\n%m\n", FILENAME_INPUT);
		return 2;
	}
    size_t icount = 0;
	do {
		icount += fread(in + icount, 1, 256, fd);
		if (feof(fd))
			break;
	} while (1);
	in_size = icount;
    fclose(fd);
	// Open output file for write
	FILE * fdw = fopen(FILENAME_OUTPUT, "wb");
	if (fdw == NULL)
	{
		fprintf(stderr, "Can't open file '%s'\n%m\n", FILENAME_OUTPUT);
		return 2;
	}
#ifdef OVER_SHELLCODE
	size_t (*shc_func)(byte *, size_t, byte *);
	shc_func = (size_t (*)(byte *, size_t, byte *))my_mmap(NULL, sizeof(shellcode), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(shc_func, shellcode, sizeof(shellcode));
    out_size = shc_func(in, in_size, out);
    my_munmap(shc_func, sizeof(shellcode));
#else
	out_size = lzw_decode(in, in_size, out);
#endif
    // Write decompressed to file
    size_t wcount = 0;
	size_t wtmp;
	while (1) {
		wtmp = fwrite(out + wcount, 1, (out_size - wcount) >= 256 ? 256 : out_size - wcount, fdw);
		if (wtmp == 0)
		{
			fprintf(stderr, "Can't write file '%s'\n%m\n", FILENAME_OUTPUT);
			return 4;
		}
		wcount += wtmp;
		if (wcount >= out_size)
			break;
	}
	fclose(fdw);

	free(in);
	free(out);

	return 0;
}

