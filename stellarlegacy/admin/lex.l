%{
// $Id: lex.l,v 1.1 2001/11/04 01:33:01 mkrohn5 Exp $

/*
 * $Log: lex.l,v $
 * Revision 1.1  2001/11/04 01:33:01  mkrohn5
 * moved some files around
 *
 * Revision 1.1  2001/08/07 20:58:28  mkrohn5
 * recommit parser & lex files
 *
 * Revision 1.9  2001/07/25 19:12:31  ishark
 * major additions in game/sl.cpp - skeleton of localserver
 *
 * Revision 1.8  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 * Revision 1.7  2001/07/05 20:34:18  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.6  2001/06/28 21:30:42  ishark
 * parser can read savefile, TObjectID now uses []
 *
 * Revision 1.5  2001/06/25 21:07:12  ishark
 * modified parser (still bad) + removed minor warnings in waypoint
 *
 * Revision 1.3  2001/04/29 21:38:37  ishark
 * TAction updated to use TDataPackage/Load
 *
 * Revision 1.2  2001/04/18 20:56:52  ishark
 * minor changes in TAction, added meat in TActionSequencer
 *
 * Revision 1.1  2001/04/13 21:56:54  ishark
 * fixed osval/substance tests, added preliminary version of action
 *
 */

class TLinkList;
class TObjectID;
class TPoint;
class TDataPackageList;

#include <string>
#include <ctype.h>
#include "common/defs.h"
#include "parser-use.h"
#include "parser.h"

#define yywrap() 1

%}

%x IDreadmode

%%

[ \t\r]		;

"\n"		lineno++;

"{"		return (LBRACE);

"}"		return (RBRACE);

"["		{
		  BEGIN(IDreadmode);
		  return (LBRACKET);
		}

"="		return (ASSIGN);

<INITIAL,IDreadmode>","		return (COMMA);

";"		return (SEMICOLON);

"("		return (LPARE);

")"		return (RPARE);

"\""		{
                  char c, *t, tstr[512];
		  t = tstr;

		  while ( '"' != (c = yyinput()) ) {
		    if (c == '\n') {
		      lineno++;

		      while (isspace(c))
			c = yyinput();

		      if (c == '"')
			break;

		      *(t++) = ' ';
		    }

		    if (c == EOF)
		      yyerror("EOF in quoted string");

		    *(t++) = c;
		  }

		  *t = 0;
		  yylval.y_str = new string(tstr);

		  return (YSTRING);
                }

"/*"		{
                  char c, oc;

		  oc = yyinput();
		  c = yyinput();

		  while (oc != '*' || c != '/') {

		    if (oc == '\n')
		      lineno++;

		    if (oc == EOF)
		      yyerror("EOF in comment");

		    oc = c;
		    c = yyinput();
		  }
                }

int2		return (INT2SPEC);

vec3d		return (VEC3DSPEC);

temp		return (IDOPTTEMP);

(true|false)	{
		  yylval.y_bol = yytext[0] == 't';
		  return (YBOOLEAN);
		}

[0-9]+          {
                  yylval.y_int = atoi(yytext);

                  return (YINTEGER);
                }

[0-9]*(\.[0-9]*)?((e|E)[+-]?[0-9]+)?  {
                  yylval.y_dbl = atof(yytext);

                  return (YDOUBLE);
                }

[A-Za-z][A-Za-z0-9_.]* {
                  yylval.y_str = new string(yytext);

                  return (YSTRING);
                }

<IDreadmode>[0-9A-Fa-f]+ {
                  // convert from hex value
                  // (crop to 2 bytes, or should we check for a valid value?)
                  yylval.y_int = (0xFF & strtol(yytext, NULL, 16));
		  return YINTEGER;
                }

<IDreadmode>"]" {
		  BEGIN(INITIAL);
		  return (RBRACKET);
		}
%%
