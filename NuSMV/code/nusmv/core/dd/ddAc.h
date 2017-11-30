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

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Modified print function
  
  Prints BDD in human readable format, based on <i>Cudd_DumpFactoredForm</i>
  
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
			      FILE * fp);

/*!
  \brief Performs recursive step of <i>Cudd_DumpFormula_modified</i>
  
  Recursively traverses the given bdd and writes the formula.
  
  \param dd The DDManager
  \param f BDD to be written in human readable format
  \param fp Pointer to the output file
  \param names Variable names to be used in the formula or NULL
  
*/

static int ddDoDumpFactoredForm_modified(DdManager * dd,
					 DdNode * f,
					 FILE * fp,
					 const char ** names);



