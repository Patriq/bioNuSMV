/* ---------------------------------------------------------------------------

  This file is part of  the ``dd'' package of NuSMV version 2. 
  Copyright (C) 2016 by FBK-irst. 

  NuSMV version 2 is free software; you can redistribute it and/or 
  modify it under the terms of the GNU Lesser General Public 
  License as published by the Free Software Foundation; either 
  version 2 of the License, or (at your option) any later version.

  NuSMV version 2 is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public 
  License along with this library; if not, write to the Free Software 
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  For more information on NuSMV see <http://nusmv.fbk.eu>
  or email to <nusmv-users@fbk.eu>.
  Please report bugs to <nusmv-users@fbk.eu>.

  To contact the NuSMV development board, email to <nusmv@fbk.eu>. 

-----------------------------------------------------------------------------*/

/*!
  \author Sarah Nee, Hannes Klarner, Frederike Heinitz, Mehmet Can
  \brief Header file for modified Cudd print functions.
  
  Implements functions for printing a bdd as formula. The implementation is 
  based on the <i>Cudd_DumpFactoredForm</i> function of the Cudd package, but 
  slightly modified as to be more consistent with <i>nusmv</i>'s output formats.

*/

#include "nusmv/core/dd/ddInt.h"
#include "nusmv/core/dd/DDMgr_private.h"
#include "nusmv/core/dd/ddAc.h"

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/

static int ddDoDumpFactoredForm_modified(DdManager * dd,
					 DdNode * f,
					 FILE * fp,
					 const char ** names);

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/
 
 /*!
  \brief Modified print function
  
  Prints BDD in human readable format, based on <i>Cudd_DumpFactoredForm</i>.
  It returns 1 in case of success; 0 otherwise. The file must be closed by
  the calling function, as <i>Cudd_DumpFormula_modified</i> does not close it.
  The argument inames can be NULL - then variable names x0, x1, ... will be 
  taken. Otherwise, it is assumed to hold pointers to the input variable 
  names.
  
  \param dd_ptr DDManager Pointer
  \param n Number of output nodes to be dumped
  \param f BDD to be written in human readable format
  \param inames Variable names to be used in the formula or NULL
  \param fp Pointer to the output file
  
*/
int Cudd_DumpFormula_modified(DDMgr_ptr dd_ptr,
			      int  n,
			      DdNode ** f,
			      const char ** inames,
			      FILE * fp)
{
    /* get the pointer to the DdManager from the given dd_ptr */
    DdManager * dd = dd_ptr->dd;
    int		retval;
    int		i;

    /* Call the function that really gets the job done. */
    for (i = 0; i < n; i++) {
	
	if (retval == EOF) return(0);
	if (f[i] == DD_TRUE(dd)) {
	    retval = fprintf(fp, "TRUE");
	    if (retval == EOF) return(0);
	} else if (f[i] == Cudd_Not(DD_TRUE(dd)) || f[i] == DD_FALSE(dd)) {
	    retval = fprintf(fp, "FALSE");
	    if (retval == EOF) return(0);
	} else {
	    retval = fprintf(fp, "%s", Cudd_IsComplement(f[i]) ? "!(" : "");
	    if (retval == EOF) return(0);
	    retval = ddDoDumpFactoredForm_modified(dd,Cudd_Regular(f[i]),fp,inames);
	    if (retval == 0) return(0);
	    retval = fprintf(fp, "%s", Cudd_IsComplement(f[i]) ? ")" : "");
	    if (retval == EOF) return(0);
	}
	retval = fprintf(fp, "%s", i == n-1 ? "" : "\n");
	if (retval == EOF) return(0);
    }

    return(1);

}

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/

/*!
  \brief Performs recursive step of <i>Cudd_DumpFormula_modified</i>
  
  Recursively traverses the given bdd and writes the formula to the file 
  pointed to by fp.
  
  \param dd The DDManager
  \param f BDD to be written in human readable format
  \param fp Pointer to the output file
  \param names Variable names to be used in the formula or NULL
  
*/

static int ddDoDumpFactoredForm_modified(DdManager * dd,
					 DdNode * f,
					 FILE * fp,
					 const char ** names)
{
    DdNode	*T, *E;
    int		retval;

#ifdef DD_DEBUG
    assert(!Cudd_IsComplement(f));
    assert(!Cudd_IsConstant(f));
#endif

    /* Check for abnormal condition that should never happen. */
    if (f == NULL)
        return(0);

    /* Recursive calls. */
    T = cuddT(f);
    E = cuddE(f);
    if (T != DD_FALSE(dd)) {
	if (E != DD_TRUE(dd)) {
	    if (names != NULL) {
		retval = fprintf(fp, "%s", names[f->index]);
	    } else {
		retval = fprintf(fp, "x%d", f->index);
	    }
	    if (retval == EOF) return(0);
	}
	if (T != DD_TRUE(dd)) {
	    retval = fprintf(fp, "%s(", E != DD_TRUE(dd) ? " & " : "");
	    if (retval == EOF) return(0);
	    retval = ddDoDumpFactoredForm_modified(dd,T,fp,names);
	    if (retval != 1) return(retval);
	    retval = fprintf(fp, ")");
	    if (retval == EOF) return(0);
	}
	if (E == Cudd_Not(DD_TRUE(dd)) || E == DD_FALSE(dd)) return(1);
	retval = fprintf(fp, " | ");
	if (retval == EOF) return(0);
    }
    E = Cudd_Regular(E);
    if (T != DD_TRUE(dd)) {
	if (names != NULL) {
	    retval = fprintf(fp, "!%s", names[f->index]);
	} else {
	    retval = fprintf(fp, "!x%d", f->index);
	}
	if (retval == EOF) return(0);
    }
    if (E != DD_TRUE(dd)) {
	retval = fprintf(fp, "%s%s(", T != DD_TRUE(dd) ? " & " : "",
			 E != cuddE(f) ? "!" : "");
	if (retval == EOF) return(0);
	retval = ddDoDumpFactoredForm_modified(dd,E,fp,names);
	if (retval != 1) return(retval);
	retval = fprintf(fp, ")");
	if (retval == EOF) return(0);
    }
    return(1);

}

