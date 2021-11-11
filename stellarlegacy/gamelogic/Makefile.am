####### kdevelop will overwrite this part!!! (begin)##########
lib_LTLIBRARIES = libslgamelogic.la


## INCLUDES were found outside kdevelop specific part


LDFLAGS =            


libslgamelogic_la_LDFLAGS = -lstdc++ -version-info 0:2:0 

libslgamelogic_la_METASOURCES = AUTO

libslgamelogic_la_SOURCES = rulesystem.cpp universe.cpp ruleatom.cpp waypoint.cpp property.cpp race.cpp shipdesign.cpp item.cpp subfleet.cpp fleetaction.cpp action.cpp fleet.cpp system.cpp galaxy.cpp stolist.cpp stobj.cpp substance.cpp 

SUBDIRS = modules ruleatoms 

EXTRA_DIST = substance.cpp substance.h stobj.cpp stobj.h stolist.cpp stolist.h galaxy.cpp galaxy.h race.h fleet.h system.h system.cpp fleet.cpp action.cpp action.h fleetaction.cpp subfleet.h subfleet.cpp item.cpp item.h shipdesign.cpp shipdesign.h planet.h race.cpp property.h property.cpp waypoint.cpp waypoint.h ruleatom.cpp ruleatom.h universe.cpp universe.h fleetaction.h fleetaction.act rulesystem.h rulesystem.cpp 

####### kdevelop will overwrite this part!!! (end)############

if NO_LIBSTDCPP
  INCL = -I$(top_srcdir)/stellarlegacy
else
  INCL = -I$(top_srcdir)/stellarlegacy -I$(libstdcxxdir)/include/g++-v3
endif

INCLUDES = $(all_includes) $(INCL)

ACTTOCPP = ../tools/act_to_cpp/act-to-cpp.pl

SUFFIXES = .act

.act.cpp:
	pwd
	$(top_srcdir)/$(ACTTOCPP) $*.act

.act.h:
	pwd
	$(top_srcdir)/$(ACTTOCPP) $*.act

fleetaction.h: fleetaction.act
fleetaction.cpp: fleetaction.act
