####### kdevelop will overwrite this part!!! (begin)##########
lib_LTLIBRARIES = libsladmin.la


## INCLUDES were found outside kdevelop specific part


LDFLAGS =            


libsladmin_la_LDFLAGS = -lstdc++ -version-info 0:2:0 

libsladmin_la_METASOURCES = AUTO

libsladmin_la_SOURCES = game-sc.cpp game-client.cpp game-server.cpp game-create.cpp server.cpp player.cpp parser.cpp lex.cpp game.cpp 


EXTRA_DIST = game.cpp game.h lex.cpp parser-use.h parser.cpp parser.h parser.y player.cpp player.h server.cpp game-client.h game-server.h game-create.h game-create.cpp game-server.cpp game-client.cpp game-sc.h game-sc.cpp 

####### kdevelop will overwrite this part!!! (end)############

if NO_LIBSTDCPP
  INCL = -I$(top_srcdir)/stellarlegacy
else
  INCL = -I$(top_srcdir)/stellarlegacy -I$(libstdcxxdir)/include/g++-v3
endif

INCLUDES = $(all_includes) $(INCL)

