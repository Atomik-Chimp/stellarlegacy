// Header File to define Operating-System specific functions
// Written by: Henning Maas

// Copyright (C) 2001 - , Henning Maas <maash@gmx.net>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 1, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef __OSSPECIFIC_INCLUDED
#define __OSSPECIFIC_INCLUDED


#include <sys/types.h>


/*  Makes a new directory, which name and path is taken from 'path',
 *  while the file-permission bits are set with mode_t, a short integer.
 *  Unix: The function calls the unix mkdir() from sys/stat.h with the given
 *        parameters.
 *  Windows: The function calls the windows mkdir() from direct.h with only the
 *        path/name-information.
 */
int osSpecificMkdir(const char *path, mode_t mode);

#endif // __OSSPECIFIC_INCLUDED
