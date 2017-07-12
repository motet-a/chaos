/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _CHAOS_ERR_H_
# define _CHAOS_ERR_H_

# include <limits.h>

/*
** This enum contains all the possible error-codes a function can return.
**
** Feel free to complete it according your needs.
*/
enum				status
{
	OK			= 0,

	__ERR_UNKNOWN		= CHAR_MIN, /* Used to calibrate the next enum values. Should never be used. */

	/* Internal errors */
	ERR_INTERNAL,			/* Internal / unspecified error. Keep this one for extrem cases. */
	ERR_NOT_IMPLEMENTED,		/* Operation is not implemented */
	ERR_NOT_SUPPORTED,		/* Operation is not supported */
	ERR_NO_MEMORY,			/* Operation couldn't complete because it went out of memory */
	ERR_INTERRUPTED,		/* Operation got interrupted */

	/* Parameters errors */
	ERR_INVALID_ARGS,		/* Invaid arguments */
	ERR_OUT_OF_RANGE,		/* One of the argument was outside the valid range for this operation */
	ERR_BAD_HANDLE,			/* The operation is missing a handler or callback to call */

	/* State errors */
	ERR_BAD_STATE,			/* Operation failed because it's current state wouldn't allow the operation to complete (eg: pre-conditions not satisfied) */
	ERR_TIMED_OUT,			/* The operation timed-out */
	ERR_CANCELED,			/* The operation has been canceled */
	ERR_NOT_FOUND,			/* A component is missing */
	ERR_ALREADY_EXIST,		/* A given unique-id is already taken */
	ERR_ACCESS_DENIED,		/* The operation couldn't be completed because it's missing privileges */

	/* Input / output errors */
	ERR_IO,				/* I/O error */
};

typedef enum status	status_t;

#endif /* !_CHAOS_ERR_H_ */
