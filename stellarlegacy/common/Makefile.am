####### kdevelop will overwrite this part!!! (begin)##########
lib_LTLIBRARIES = libslcommon.la


## INCLUDES were found outside kdevelop specific part


LDFLAGS =            


libslcommon_la_LDFLAGS = -lstdc++ -version-info 0:2:0 

libslcommon_la_METASOURCES = AUTO

libslcommon_la_SOURCES = stringtools.cpp os_specific.cpp link.cpp line.cpp datapackage.cpp rectangle.cpp random.cpp point.cpp osval.cpp bitmap.cpp global.cpp 


EXTRA_DIST = defs.h global.cpp global.h bitmap.cpp bitmap.h osval.cpp osval.h point.cpp point.h random.cpp random.h rectangle.cpp rectangle.h datapackage.h datapackage.cpp plist.h leakchecker.h line.h line.cpp link.cpp link.h os_specific.cpp os_specific.h stringtools.h stringtools.cpp prototype.h 

####### kdevelop will overwrite this part!!! (end)############

if NO_LIBSTDCPP
  INCL = -I$(top_srcdir)/stellarlegacy
else
  INCL = -I$(top_srcdir)/stellarlegacy -I$(libstdcxxdir)/include/g++-v3
endif

INCLUDES = $(all_includes) $(INCL)
