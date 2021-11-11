#ifndef BISON_PARSER_TAB_H
# define BISON_PARSER_TAB_H

#ifndef YYSTYPE
typedef union{
  string *y_str;
  double y_dbl;
  bool y_bol;
  int4 y_int;
  int* y_iar;
  TObjectID* y_oid;
  TPoint* y_pnt;
  TDataPackageList* y_dst;
} yystype;
# define YYSTYPE yystype
#endif
# define	YINTEGER	257
# define	YDOUBLE	258
# define	YSTRING	259
# define	YBOOLEAN	260
# define	LBRACE	261
# define	RBRACE	262
# define	LBRACKET	263
# define	RBRACKET	264
# define	LPARE	265
# define	RPARE	266
# define	ASSIGN	267
# define	COMMA	268
# define	SEMICOLON	269
# define	IDOPTTEMP	270
# define	INT2SPEC	271
# define	VEC3DSPEC	272


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_TAB_H */
