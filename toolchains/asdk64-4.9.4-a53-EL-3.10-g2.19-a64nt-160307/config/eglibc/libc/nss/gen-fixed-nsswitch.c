/* gen-fixed-nsswitch.c --- generate fixed name service data structures
   Copyright (C) 1996-1999, 2001-2006, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>

#include "gnu/lib-names.h"
#include "nss.h"

/* Provide a fallback definition to allow this file to be compiled outside
   libc.  */
#ifndef internal_function
# define internal_function
#endif


/* Simple utilities.  */

void __attribute__ ((noreturn))
error (const char *message)
{
  fprintf (stderr, "%s\n", message);
  exit (1);
}


void *
check_alloc (void *p)
{
  if (p)
    return p;
  else
    error ("out of memory");
}

void *
xmalloc (size_t size)
{
  return check_alloc (malloc (size));
}


/* Format ARGS according to FORMAT, and return the result as a
   malloc'ed string.  */
char *
saprintf (const char *format, ...)
{
  va_list args;
  size_t len;
  char *buf;
  
  va_start (args, format);
  len = vsnprintf (NULL, 0, format, args);
  va_end (args);

  buf = xmalloc (len + 1);
  va_start (args, format);
  assert (len == vsnprintf (buf, len + 1, format, args));
  va_end (args);

  return buf;
}



/* Data structures representing the configuration file in memory.  */

/* These are copied from nsswitch.h.

   We could simply #include that file, but this program runs on the
   build machine and links against the build machine's libraries,
   whereas that header is meant for use by target code; it uses
   'libc_hidden_proto', 'internal_function', and related hair.  Since
   we've copied the parsing code, we might as well copy the data
   structure definitions as well.  */

/* Actions performed after lookup finished.  */
typedef enum
{
  NSS_ACTION_CONTINUE,
  NSS_ACTION_RETURN
} lookup_actions;


typedef struct service_library
{
  /* Name of service (`files', `dns', `nis', ...).  */
  const char *name;
  /* Pointer to the loaded shared library.  */
  void *lib_handle;
  /* And the link to the next entry.  */
  struct service_library *next;
} service_library;


/* For mapping a function name to a function pointer.  It is known in
   nsswitch.c:nss_lookup_function that a string pointer for the lookup key
   is the first member.  */
typedef struct
{
  const char *fct_name;
  void *fct_ptr;
} known_function;


typedef struct service_user
{
  /* And the link to the next entry.  */
  struct service_user *next;
  /* Action according to result.  */
  lookup_actions actions[5];
  /* Link to the underlying library object.  */
  service_library *library;
  /* Collection of known functions.

     With OPTION_EGLIBC_NSSWITCH enabled, this is the root of a
     'tsearch'-style tree.

     With OPTION_EGLIBC_NSSWITCH disabled, this is an array of
     pointers to known_function structures, NULL-terminated.  */
  union
  {
    void *tree;
    const known_function **array;
  } known;
  /* Name of the service (`files', `dns', `nis', ...).  */
  const char *name;
} service_user;

/* To access the action based on the status value use this macro.  */
#define nss_next_action(ni, status) ((ni)->actions[2 + status])


typedef struct name_database_entry
{
  /* And the link to the next entry.  */
  struct name_database_entry *next;
  /* List of service to be used.  */
  service_user *service;
  /* Name of the database.  */
  const char *name;
} name_database_entry;


typedef struct name_database
{
  /* List of all known databases.  */
  name_database_entry *entry;
  /* List of libraries with service implementation.  */
  service_library *library;
} name_database;



/* Gathering the contents of the FIXED_FUNCTIONS file.  */

/* It should be possible to generate this list automatically by
   looking at the services and databases used in the nsswitch.conf
   file, and having a hard-coded set of queries supported on each
   database.  */

/* We #include the FIXED_FUNCTIONS file several times to build an
   array of function structures holding its data.  */
enum function_kind {
  fk_end = 0,                   /* Last entry.  */
  fk_setent,                    /* Like setpwent.  */
  fk_getent,                    /* Like getpwent.  */
  fk_endent,                    /* Like endpwent.  */
  fk_getby,                     /* Like gethostbyname.  */
  fk_get                        /* Like getpwnam.  */
};


struct function {
  /* What kind of function this is.  */
  enum function_kind kind;

  /* The database and service of the function being hardwired in.  */
  char *database, *service;

  /* The kind of entry being queried, for 'fk_setent', 'fk_getent',
     'fk_endent', and 'fk_getby' functions.  */
  char *entry;

  /* The key, for 'fk_getby' entries.  */
  char *key;

  /* The value and key, for 'fk_get' entries.  */
  char *value_and_key;
};


const struct function functions[] =
  {

#define DEFINE_ENT(database, service, entry)    \
    { fk_setent, #database, #service, #entry }, \
    { fk_getent, #database, #service, #entry }, \
    { fk_endent, #database, #service, #entry },
#define DEFINE_GETBY(database, service, entry, key)   \
    { fk_getby, #database, #service, #entry, #key },
#define DEFINE_GET(database, service, value_and_key)     \
    { fk_get, #database, #service, NULL, NULL, #value_and_key },

#include FIXED_FUNCTIONS

#undef DEFINE_ENT
#undef DEFINE_GETBY
#undef DEFINE_GET

    { fk_end }
  };


/* Parsing the config file.  Functions copied from nsswitch.c.  */

#define __strchrnul strchrnul
#define __getline getline
#define __strncasecmp strncasecmp

/* Prototypes for the local functions.  */
static name_database *nss_parse_file (const char *fname) internal_function;
static name_database_entry *nss_getline (char *line) internal_function;
static service_user *nss_parse_service_list (const char *line)
     internal_function;

static name_database *
internal_function
nss_parse_file (const char *fname)
{
  FILE *fp;
  name_database *result;
  name_database_entry *last;
  char *line;
  size_t len;

  /* Open the configuration file.  */
  fp = fopen (fname, "rc");
  if (fp == NULL)
    return NULL;

  // /* No threads use this stream.  */
  // __fsetlocking (fp, FSETLOCKING_BYCALLER);

  result = (name_database *) xmalloc (sizeof (name_database));

  result->entry = NULL;
  result->library = NULL;
  last = NULL;
  line = NULL;
  len = 0;
  do
    {
      name_database_entry *this;
      ssize_t n;

      n = __getline (&line, &len, fp);
      if (n < 0)
	break;
      if (line[n - 1] == '\n')
	line[n - 1] = '\0';

      /* Because the file format does not know any form of quoting we
	 can search forward for the next '#' character and if found
	 make it terminating the line.  */
      *__strchrnul (line, '#') = '\0';

      /* If the line is blank it is ignored.  */
      if (line[0] == '\0')
	continue;

      /* Each line completely specifies the actions for a database.  */
      this = nss_getline (line);
      if (this != NULL)
	{
	  if (last != NULL)
	    last->next = this;
	  else
	    result->entry = this;

	  last = this;
	}
    }
  while (!feof_unlocked (fp));

  /* Free the buffer.  */
  free (line);
  /* Close configuration file.  */
  fclose (fp);

  return result;
}


/* Read the source names:
	`( <source> ( "[" "!"? (<status> "=" <action> )+ "]" )? )*'
   */
static service_user *
internal_function
nss_parse_service_list (const char *line)
{
  service_user *result = NULL, **nextp = &result;

  while (1)
    {
      service_user *new_service;
      const char *name;

      while (isspace (line[0]))
	++line;
      if (line[0] == '\0')
	/* No source specified.  */
	return result;

      /* Read <source> identifier.  */
      name = line;
      while (line[0] != '\0' && !isspace (line[0]) && line[0] != '[')
	++line;
      if (name == line)
	return result;


      new_service = (service_user *) xmalloc (sizeof (*new_service));
      new_service->name = (char *) xmalloc (line - name + 1);

      *((char *) __mempcpy ((char *) new_service->name, name, line - name))
        = '\0';

      /* Set default actions.  */
      new_service->actions[2 + NSS_STATUS_TRYAGAIN] = NSS_ACTION_CONTINUE;
      new_service->actions[2 + NSS_STATUS_UNAVAIL] = NSS_ACTION_CONTINUE;
      new_service->actions[2 + NSS_STATUS_NOTFOUND] = NSS_ACTION_CONTINUE;
      new_service->actions[2 + NSS_STATUS_SUCCESS] = NSS_ACTION_RETURN;
      new_service->actions[2 + NSS_STATUS_RETURN] = NSS_ACTION_RETURN;
      new_service->library = NULL;
      new_service->known.tree = NULL;
      new_service->next = NULL;

      while (isspace (line[0]))
	++line;

      if (line[0] == '[')
	{
	  /* Read criterions.  */
	  do
	    ++line;
	  while (line[0] != '\0' && isspace (line[0]));

	  do
	    {
	      int not;
	      enum nss_status status;
	      lookup_actions action;

	      /* Grok ! before name to mean all statii but that one.  */
	      not = line[0] == '!';
	      if (not)
		++line;

	      /* Read status name.  */
	      name = line;
	      while (line[0] != '\0' && !isspace (line[0]) && line[0] != '='
		     && line[0] != ']')
		++line;

	      /* Compare with known statii.  */
	      if (line - name == 7)
		{
		  if (__strncasecmp (name, "SUCCESS", 7) == 0)
		    status = NSS_STATUS_SUCCESS;
		  else if (__strncasecmp (name, "UNAVAIL", 7) == 0)
		    status = NSS_STATUS_UNAVAIL;
		  else
		    return result;
		}
	      else if (line - name == 8)
		{
		  if (__strncasecmp (name, "NOTFOUND", 8) == 0)
		    status = NSS_STATUS_NOTFOUND;
		  else if (__strncasecmp (name, "TRYAGAIN", 8) == 0)
		    status = NSS_STATUS_TRYAGAIN;
		  else
		    return result;
		}
	      else
		return result;

	      while (isspace (line[0]))
		++line;
	      if (line[0] != '=')
		return result;
	      do
		++line;
	      while (isspace (line[0]));

	      name = line;
	      while (line[0] != '\0' && !isspace (line[0]) && line[0] != '='
		     && line[0] != ']')
		++line;

	      if (line - name == 6 && __strncasecmp (name, "RETURN", 6) == 0)
		action = NSS_ACTION_RETURN;
	      else if (line - name == 8
		       && __strncasecmp (name, "CONTINUE", 8) == 0)
		action = NSS_ACTION_CONTINUE;
	      else
		return result;

	      if (not)
		{
		  /* Save the current action setting for this status,
		     set them all to the given action, and reset this one.  */
		  const lookup_actions save = new_service->actions[2 + status];
		  new_service->actions[2 + NSS_STATUS_TRYAGAIN] = action;
		  new_service->actions[2 + NSS_STATUS_UNAVAIL] = action;
		  new_service->actions[2 + NSS_STATUS_NOTFOUND] = action;
		  new_service->actions[2 + NSS_STATUS_SUCCESS] = action;
		  new_service->actions[2 + status] = save;
		}
	      else
		new_service->actions[2 + status] = action;

	      /* Skip white spaces.  */
	      while (isspace (line[0]))
		++line;
	    }
	  while (line[0] != ']');

	  /* Skip the ']'.  */
	  ++line;
	}

      *nextp = new_service;
      nextp = &new_service->next;
    }
}

static name_database_entry *
internal_function
nss_getline (char *line)
{
  const char *name;
  name_database_entry *result;
  size_t len;

  /* Ignore leading white spaces.  ATTENTION: this is different from
     what is implemented in Solaris.  The Solaris man page says a line
     beginning with a white space character is ignored.  We regard
     this as just another misfeature in Solaris.  */
  while (isspace (line[0]))
    ++line;

  /* Recognize `<database> ":"'.  */
  name = line;
  while (line[0] != '\0' && !isspace (line[0]) && line[0] != ':')
    ++line;
  if (line[0] == '\0' || name == line)
    /* Syntax error.  */
    return NULL;
  *line++ = '\0';

  len = strlen (name) + 1;

  result = (name_database_entry *) xmalloc (sizeof (*result));
  result->name = (char *) xmalloc (len);

  /* Save the database name.  */
  memcpy ((char *) result->name, name, len);

  /* Parse the list of services.  */
  result->service = nss_parse_service_list (line);

  result->next = NULL;
  return result;
}



/* Generating code for statically initialized nsswitch structures.  */


/* Return the service-neutral suffix of the name of the service
   library function referred to by the function F.  The result is
   allocated with malloc.  */
char *
known_function_suffix (const struct function *f)
{
  switch (f->kind)
    {
    case fk_setent:
      return saprintf ("set%sent", f->entry);

    case fk_getent:
      return saprintf ("get%sent_r", f->entry);

    case fk_endent:
      return saprintf ("end%sent", f->entry);

    case fk_getby:
      return saprintf ("get%sby%s_r", f->entry, f->key);

    case fk_get:
      return saprintf ("get%s_r", f->value_and_key);

    default:
      abort ();
    }
}


/* Return the name of the service library function referred to by the
   function F.  The result is allocated with malloc.  */
char *
known_function_name (const struct function *f)
{
  return saprintf ("_nss_%s_%s", f->service, known_function_suffix (f));
}


/* Write initialized known_function structures to OUT for
   all the functions we'll use.  */
void
generate_known_functions (FILE *out)
{
  int i;

  /* First, generate weak references to the functions.  The service
     libraries depend on libc, and if these references weren't weak,
     we'd be making libc depend circularly on the service
     libraries.  */
  for (i = 0; functions[i].kind; i++)
    {
      char *name = known_function_name (&functions[i]);
      fprintf (out, "typeof (%s) %s __attribute__ ((weak));\n",
               name, name);
    }
  fputs ("\n", out);

  /* Then, a table mapping names to functions.  */
  fputs ("static const known_function fixed_known_functions[] = {\n",
         out);
  for (i = 0; functions[i].kind; i++)
    {
      const struct function *f = &functions[i];
      char *suffix = known_function_suffix (f);

      fprintf (out, "  /* %2d */ { \"%s\", _nss_%s_%s },\n",
               i, suffix, f->service, suffix);
    }
  fputs ("};\n", out);
  fputs ("\n", out);
}


/* Print code to OUT for an initialized array of pointers to the
   'known_function' structures needed for USER, which is for
   DATABASE.  Return its name, allocated with malloc.  */
char *
generate_known_function_list (FILE *out,
                              const name_database_entry *database,
                              const service_user *user)
{
  char *list_name = saprintf ("fixed_%s_%s_known_funcs",
                              database->name, user->name);
  fprintf (out, "static const known_function *%s[] = {\n",
           list_name);
  int i;
  for (i = 0; functions[i].kind; i++)
    if (strcmp (functions[i].database, database->name) == 0
        && strcmp (functions[i].service, user->name) == 0)
      fprintf (out, "  &fixed_known_functions[%d], /* %s */\n",
               i, known_function_name (&functions[i]));
  fputs ("  NULL\n", out);
  fputs ("};\n", out);
  fputs ("\n", out);

  return list_name;
}


/* Return the name of the status value STATUS, as a statically
   allocated string.  */
const char *
lookup_status_name (enum nss_status status)
{
  switch (status)
    {
    case NSS_STATUS_TRYAGAIN: return "NSS_STATUS_TRYAGAIN";
    case NSS_STATUS_UNAVAIL: return "NSS_STATUS_UNAVAIL";
    case NSS_STATUS_NOTFOUND: return "NSS_STATUS_NOTFOUND";
    case NSS_STATUS_SUCCESS: return "NSS_STATUS_SUCCESS";
    case NSS_STATUS_RETURN: return "NSS_STATUS_RETURN";
    default: abort ();
    };
}


/* Return the name of ACTION as a statically allocated string.  */
const char *
lookup_action_name (lookup_actions action)
{
  switch (action)
    {
    case NSS_ACTION_CONTINUE: return "NSS_ACTION_CONTINUE";
    case NSS_ACTION_RETURN: return "NSS_ACTION_RETURN";
    default: abort ();
    }
}


/* Print code to OUT for the list of service_user structures starting
   with USER, which are all for DATABASE.  Return the name of the 
   first structure in that list, or zero if USER is NULL.  */
char *
generate_service_user_list (FILE *out,
                            name_database_entry *database,
                            service_user *user)
{
  if (user)
    {
      /* Generate the tail of the list.  */
      char *next_name = generate_service_user_list (out, database, user->next);
      /* Generate our known function list.  */
      char *known_function_list_name =
        generate_known_function_list (out, database, user);

      char *name = saprintf ("fixed_%s_%s_user", database->name, user->name);

      fprintf (out, "static const service_user %s = {\n", name);
      if (next_name)
        fprintf (out, "  (service_user *) &%s,\n", next_name);
      else
        fprintf (out, "  NULL, /* no next entry */\n");
      fputs ("  {\n", out);
      int i;
      for (i = 0; i < sizeof (user->actions) / sizeof (user->actions[0]); i++)
        fprintf (out, "    %s, /* %s */\n",
                 lookup_action_name (user->actions[i]),
                 lookup_status_name (i - 2));
      fputs ("  },\n", out);
      fprintf (out, "  NULL,  /* we never need the service library */\n");
      fprintf (out, "  { .array = %s },\n", known_function_list_name);
      fprintf (out, "  \"%s\"\n", user->name);
      fputs ("};\n", out);
      fputs ("\n", out);
      
      return name;
    }
  else
    return NULL;
}


/* Print code to OUT for the list of name_database_entry structures
   starting with DATABASE.  Return the name of the first structure 
   in that list, or zero if DATABASE is NULL.  */
char *
generate_name_database_entries (FILE *out, name_database_entry *database)
{
  if (database)
    {
      char *next_name = generate_name_database_entries (out, database->next);
      char *service_user_name
        = generate_service_user_list (out, database, database->service);
      char *name = saprintf ("fixed_%s_name_database", database->name);

      fprintf (out, "static const name_database_entry %s = {\n", name);

      if (next_name)
        fprintf (out, "  (name_database_entry *) &%s,\n", next_name);
      else
        fprintf (out, "  NULL,\n");
      
      if (service_user_name)
        fprintf (out, "  (service_user *) &%s,\n", service_user_name);
      else
        fprintf (out, "  NULL,\n");

      fprintf (out, "  \"%s\"\n", database->name);
      fprintf (out, "};\n");
      fputs ("\n", out);

      return name;
    }
  else
    return NULL;
}


void
generate_name_database (FILE *out, name_database *service_table)
{
  /* Produce a linked list of the known name_database_entry
     structures.  */
  char *entries = generate_name_database_entries (out, service_table->entry);

  /* Now produce the main structure that points to them all.  */
  fprintf (out, "static const name_database fixed_name_database = {\n");
  if (entries)
    fprintf (out, "  (name_database_entry *) &%s,\n", entries);
  else
    fprintf (out, "  NULL,\n");
  fputs ("  NULL /* we don't need the libraries */\n"
         "};\n",
         out);
}



/* Generating the list of service libraries we generate references to.  */

/* String with revision number of the shared object files.  */
static const char *const nss_shlib_revision = LIBNSS_FILES_SO + 15;

void
generate_service_lib_list (FILE *out, name_database *service_table)
{
  int i, j;
  int printed_any = 0;

  for (i = 0; functions[i].kind; i++)
    {
      /* Mention each service library only once.  */
      for (j = 0; j < i; j++)
        if (strcmp (functions[i].service, functions[j].service) == 0)
          break;

      if (j >= i)
        {
          if (printed_any)
            putc (' ', out);
          fprintf (out, "-lnss_%s",
                   functions[i].service,
                   nss_shlib_revision);
          printed_any = 1;
        }
    }
}


/* Main.  */

int
main (int argc, char **argv)
{
  if (argc != 4)
    {
      fprintf (stderr, "usage: gen-fixed-nsswitch HEADER SERVLIBS CONFIG\n");
      exit (1);
    }
  
  name_database *service_table = nss_parse_file (argv[3]);
  
  FILE *header = fopen (argv[1], "w");
  if (! header)
    {
      fprintf (stderr,
               "gen-fixed-nsswitch: couldn't open output file %s: %s\n",
               argv[1], strerror (errno));
      exit (1);
    }
  fputs ("/* Generated by nss/gen-fixed-nsswitch.c.  */\n", header);
  fputs ("\n", header);
  generate_known_functions (header);
  generate_name_database (header, service_table);
  fclose (header);

  FILE *service_lib_list = fopen (argv[2], "w");
  if (! service_lib_list)
    {
      fprintf (stderr,
               "gen-fixed-nsswitch: couldn't open output file %s: %s\n",
               argv[2], strerror (errno));
      exit (1);
    }
  generate_service_lib_list (service_lib_list, service_table);
  fclose (service_lib_list);

  return 0;
}
