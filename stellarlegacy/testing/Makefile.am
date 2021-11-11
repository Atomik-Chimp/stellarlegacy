####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libtesting.a

## INCLUDES were found outside kdevelop specific part

libtesting_a_METASOURCES = AUTO

libtesting_a_SOURCES = test-objectid.cpp test-def.cpp testing.cpp test-fleet.cpp test-subfleet.cpp test-shipdesign.cpp test-action.cpp test-osval.cpp test-substance.cpp test-link.cpp test-random.cpp 


EXTRA_DIST = test-random.cpp test-link.cpp test-substance.cpp test-osval.cpp test-action.cpp test-shipdesign.cpp test-subfleet.cpp test-fleet.cpp testing.cpp test-def.cpp test-objectid.cpp 

####### kdevelop will overwrite this part!!! (end)############

if NO_LIBSTDCPP
  INCL = -I$(top_srcdir)/stellarlegacy
else
  INCL = -I$(top_srcdir)/stellarlegacy -I$(libstdcxxdir)/include/g++-v3
endif

INCLUDES = $(all_includes) $(INCL)

