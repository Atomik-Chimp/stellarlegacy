// Code File to define Operating-System specific functions
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

#include "common/defs.h"
#include "common/os_specific.h"



#ifdef OS_UNIX                         // Unix:

  #include <sys/types.h>
  #include <sys/stat.h>

  int osSpecificMkdir(const char *path, mode_t mode){
    return mkdir(path,mode);  // for unix systems only
  }

#elif defined OS_WINDOWS                      // windows:

  #include <direct.h>

  int osSpecificMkdir(const char *path, mode_t mode){
    mkdir(path);       // for windows
  }

#endif


