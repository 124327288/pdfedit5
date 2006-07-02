//========================================================================
//
// Parser.h
//
// Copyright 1996-2003 Glyph & Cog, LLC
//
//========================================================================

#ifndef PARSER_H
#define PARSER_H

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma interface
#endif

#include "Lexer.h"

//------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------

class Parser {
public:

  // Constructor.
  Parser(XRef *xrefA, Lexer *lexerA);

  // Destructor.
  ~Parser();

  // Get the next object from the input stream.
  Object *getObj(Object *obj,
		 Guchar *fileKey = NULL, int keyLength = 0,
		 int objNum = 0, int objGen = 0);

  // Get stream.
  Stream *getStream() { return lexer->getStream(); }

  // Get current position in file.
  int getPos() { return lexer->getPos(); }

  // End of actual stream
  bool eofOfActualStream () const { return (1 == endOfActStream); }

private:

  XRef *xref;			// the xref table for this PDF file
  Lexer *lexer;			// input stream
  Object buf1, buf2;		// next two tokens
  int inlineImg;		// set when inline image data is encountered
  size_t endOfActStream; // When 1 means end of act stream

  Stream *makeStream(Object *dict);
  void shift();
};

#endif

