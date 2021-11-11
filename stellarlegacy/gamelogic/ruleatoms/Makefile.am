####### kdevelop will overwrite this part!!! (begin)##########
lib_LTLIBRARIES = libslmodules.la


## INCLUDES were found outside kdevelop specific part


LDFLAGS =            


libslmodules_la_LDFLAGS = -lstdc++ -version-info 0:2:0 

libslmodules_la_METASOURCES = AUTO

libslmodules_la_SOURCES = race_sl.cpp system_basic.cpp subfleet_basic.cpp fleet_basic.cpp race_basic.cpp 


EXTRA_DIST = race_basic.cpp race_basic.h fleet_basic.cpp fleet_basic.h subfleet_basic.cpp subfleet_basic.h system_basic.cpp system_basic.h race_sl.h race_sl.cpp 

####### kdevelop will overwrite this part!!! (end)############

if NO_LIBSTDCPP
  INCL = -I$(top_srcdir)/stellarlegacy
else
  INCL = -I$(top_srcdir)/stellarlegacy -I$(libstdcxxdir)/include/g++-v3
endif

INCLUDES = $(all_includes) $(INCL)

