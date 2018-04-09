/*
 Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008,
 2009, 2010, 2011, 2012, 2013, 2014, 2015 Free Software Foundation, Inc.
 
 This file is part of GNU Inetutils.
 
 GNU Inetutils is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at
 your option) any later version.
 
 GNU Inetutils is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see `http://www.gnu.org/licenses/'. */

#include <config.h>

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/time.h>
#include <time.h>

#include "extern.h"


/* If name is "ftp" or "anonymous", the name is not in
 PATH_FTPUSERS, and ftp account exists, set cred, then just return.
 If account doesn't exist, ask for passwd anyway.  Otherwise, check user
 requesting login privileges.  Disallow anyone who does not have a standard
 shell as returned by getusershell().  Disallow anyone mentioned in the file
 PATH_FTPUSERS to allow people such as root and uucp to be avoided.  */

int
auth_user (const char *name, struct credentials *pcred)
{
    int err = -1;		/* Never remove initialisation!  */
    
    size_t len;
    free (pcred->message);
    len = (size_t) (64 + strlen (name));
    pcred->message = malloc (len);
    if (pcred->message == NULL) {
        return -1;
    }
    if (sgetcred (name, pcred) != 0)
    {
        free (pcred->message);
        pcred->message = NULL;
        return 1;
    }
    snprintf (pcred->message, len, "Password required for %s.", pcred->name);
    err = 0;
        
    return err;
}

int
sgetcred (const char *name, struct credentials *pcred)
{
    struct passwd *p;
    
    p = getpwnam (name);
    if (p == NULL)
        return 1;
    
    free (pcred->name);
    free (pcred->homedir);
    free (pcred->rootdir);
    free (pcred->shell);
    
    
    pcred->uid = p->pw_uid;
    pcred->gid = p->pw_gid;
    pcred->name = sgetsave (p->pw_name);
    pcred->rootdir = sgetsave (p->pw_dir);
    pcred->homedir = sgetsave ("/Pictures");
    pcred->shell = sgetsave (p->pw_shell);
    
    return 0;
}
