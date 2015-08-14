/*
 * Copyright (C) 2005 Universitat d'Alacant / Universidad de Alicante
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

// cstdio wrapper for backwards compatibility

#ifndef _IOHEADER_
#define _IOHEADER_

#include <cstdio>

// Check individually all '_unlocked' functions because using
// g++-2.95 fgetc_unlocked and fputc_unlocked compile perfectly but
// fputs_unlocked is not defined in their C headers.

#if !HAVE_DECL_FPUTS_UNLOCKED
#define fputs_unlocked fputs
#endif

#if !HAVE_DECL_FGETC_UNLOCKED 
#define fgetc_unlocked fgetc
#endif

#if !HAVE_DECL_FPUTC_UNLOCKED
#define fputc_unlocked fputc
#endif

#if !HAVE_DECL_FWRITE_UNLOCKED
#define fwrite_unlocked fwrite
#endif

#if !HAVE_DECL_FREAD_UNLOCKED
#define fread_unlocked fread
#endif

#if !HAVE_DECL_FGETWC_UNLOCKED
#define fgetwc_unlocked fgetwc
#endif

#if !HAVE_DECL_FPUTWC_UNLOCKED
#define fputwc_unlocked fputwc
#endif

#if !HAVE_DECL_FPUTWS_UNLOCKED
#define fputws_unlocked fputws
#endif



#endif
