####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = stellarlegacy

## INCLUDES were found outside kdevelop specific part

stellarlegacy_SOURCES = sl.cpp 
stellarlegacy_LDADD   = ./testing/libtesting.a ./admin/libsladmin.la ./gamelogic/ruleatoms/libslruleatoms.la ./gamelogic/modules/libslmodules.la ./gamelogic/libslgamelogic.la ./common/libslcommon.la 

SUBDIRS = common gamelogic admin testing

EXTRA_DIST = sl.cpp 

####### kdevelop will overwrite this part!!! (end)############
# set the include path found by configure
INCLUDES= $(all_includes)
 
# the library search path.
stellarlegacy_LDFLAGS = $(all_libraries) 



bin_PROGRAMS = stellarlegacy

if NO_LIBSTDCPP
  INCL =
  LDFL =
else
  INCL = -I$(libstdcxxdir)/include/g++-v3
  LDFL = -L$(libstdcxxdir)/lib
endif

# set the include path found by configure
INCLUDES= $(all_includes) $(INCL)

# the library search path.
stellarlegacy_LDFLAGS = $(all_libraries) $(LDFL)
