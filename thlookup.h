/**
 * @file thlookup.h
 * Map / model color lookup module.
 */
  
/* Copyright (C) 2012 Stacho Mudrak
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * --------------------------------------------------------------------
 */
 
#ifndef thlookup_h
#define thlookup_h


#include "thdataobject.h"
#include "thlocale.h"
#include <list>

/**
 * lookup command options tokens.
 */
 
enum {
  TT_LOOKUP_UNKNOWN = 2000,
  TT_LOOKUP_TYPE = 2001,
  TT_LOOKUP_SCALE = 2001,
  TT_LOOKUP_TITLE = 2002,
};


/**
 * Lookup command options parsing table.
 */
 
static const thstok thtt_lookup_opt[] = {
  {"scale", TT_LOOKUP_SCALE},
  {"title", TT_LOOKUP_TITLE},
  {"type", TT_LOOKUP_TYPE},
  {NULL, TT_LOOKUP_UNKNOWN},
};


/**
 * lookup scale tokens.
 */

enum {
  TT_LOOKUP_SCALE_UNKNOWN = 0,
  TT_LOOKUP_SCALE_CONTINUOUS,
  TT_LOOKUP_SCALE_DISCRETE,
};


/**
 * lookup scale token table.
 */
 
static const thstok thtt_lookup_scale[] = {
  {"continuous", TT_LOOKUP_SCALE_CONTINUOUS},
  {"discrete", TT_LOOKUP_SCALE_DISCRETE},
  {NULL, TT_LOOKUP_SCALE_UNKNOWN}
};


/**
 * lookup type tokens.
 */

enum {
  TT_LOOKUP_TYPE_UNKNOWN = 0,
  TT_LOOKUP_TYPE_DATE,
  TT_LOOKUP_TYPE_NUMERIC,
  TT_LOOKUP_TYPE_STRING,
};


/**
 * lookup grid token table.
 */
 
static const thstok thtt_lookup_types[] = {
  {"date", TT_LOOKUP_TYPE_DATE},
  {"numeric", TT_LOOKUP_TYPE_NUMERIC},
  {"string", TT_LOOKUP_TYPE_STRING},
  {NULL, TT_LOOKUP_TYPE_UNKNOWN}
};


/**
 * Supported color lookup schemes.
 */

enum {
  TT_LOOKUP_COLORSCHEME_UNKNOWN = 0,
  TT_LOOKUP_COLORSCHEME_HSV,
};


/**
 * Lookup table row.
 */

struct thlookup_table_row {
  double m_valueDbl, m_valueDblFrom;
  thdate m_valueDate;
  const char * m_valueString;
  const char * m_label;
  thlayout_color m_color;
  thlookup_table_row() : m_valueDbl(thnan), m_valueDblFrom(thnan), m_valueString(""), m_label("") {}
  void parse(char ** args);
};

typedef std::list<thlookup_table_row> thlookup_table_list;


/**
 * lookup class.
 */

class thlookup : public thdataobject {

  public:

  int m_type, m_scale, m_colorscheme;
  thlookup_table_list m_table;
  const char * m_title;

  /**
   * Standard constructor.
   */
  
  thlookup();
  
  
  /**
   * Standard destructor.
   */
   
  ~thlookup();
  
  
  /**
   * Return class identifier.
   */
  
  virtual int get_class_id();
  
  
  /**
   * Return class name.
   */
   
  virtual const char * get_class_name() {return "thlookup";};
  
  
  /**
   * Return true, if son of given class.
   */
  
  virtual bool is(int class_id);
  
  
  /**
   * Return number of command arguments.
   */
   
  virtual int get_cmd_nargs();
  
  
  /**
   * Return command name.
   */
   
  virtual const char * get_cmd_name();
  
  
  /**
   * Return command end option.
   */
   
  virtual const char * get_cmd_end();
  
  
  /**
   * Return option description.
   */
   
  virtual thcmd_option_desc get_cmd_option_desc(const char * opts);
  thcmd_option_desc get_default_cod(int id);
  
  /**
   * Set command option.
   *
   * @param cod Command option description.
   * @param args Option arguments array.
   * @param argenc Arguments encoding.
   */
   
  virtual void set(thcmd_option_desc cod, char ** args, int argenc, unsigned long indataline);


  /**
   * Delete this object.
   *
   * @warn Always use this methos instead of delete function.
   */
   
  virtual void self_delete();


  /**
   * Get context for object.
   */
   
  virtual int get_context();

  /**
   * Automatically lookup range.
   */

  virtual void auto_set(double from, double to);

  virtual void auto_set(class thdate fromto);

  /**
   * Get color from the scale.
   */

  virtual thlayout_color get_color(thdate d);

  virtual thlayout_color get_color(double d);
  
};

#endif


