/* $Id: libdynamite.h,v 1.1.1.1 2003/08/22 08:55:42 twogood Exp $ */
#ifndef __libdynamite_h__
#define __libdynamite_h__

/*
Copyright (c) 2003 David Eriksson <twogood@users.sourceforge.net>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Changes made Dec 2005 by Jonathan Wilson to account for the fact that Visual Studio .NET 2003 does not have stdint.h, stdbool.h or sys/param.h
*/
/*
   She's a dancehall queen for life
   Gonna explode like dynamite
   And she's moving outta sight
   Now she a guh mash up di place like dynamite

   http://www.beenie-man.com/dancehall_queen.htm
 */

//#include <stdbool.h>
//#include <sys/param.h>

typedef enum 
{
  DYNAMITE_SUCCESS,
  DYNAMITE_NOT_IMPLEMENTED,
  DYNAMITE_BAD_FORMAT,
  DYNAMITE_UNEXPECTED_ERROR,
  DYNAMITE_READ_ERROR,
  DYNAMITE_WRITE_ERROR
} DynamiteResult;

typedef size_t (*dynamite_reader)(void* buffer, size_t size, void* cookie);
typedef size_t (*dynamite_writer)(void* buffer, size_t size, void* cookie);

DynamiteResult dynamite_explode(dynamite_reader reader, dynamite_writer writer, void* cookie);

#endif

