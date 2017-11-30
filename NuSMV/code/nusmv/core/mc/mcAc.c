/* ---------------------------------------------------------------------------


  This file is part of  the ``mc'' package of NuSMV version 2. 
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
  \brief Source file for print accepting states addon.
  
  Print function for printing initial, accepting and initial accepting 
  states when the commandline option `-a` is specified. 
  
  \param env The environment
  \param prop The properties of the environment
  \param dd The decision diagram
  \param enc Support for printing bdd's
  \param opts OptsHandler_ptr to check where to print
  \param streams StreamMgr_ptr for printing
  \param init bdd_ptr holding the initial states
  \param accepting bdd_ptr holding the accepting states

*/

#include "nusmv/core/bmc/sbmc/sbmcGen.h"
#include "nusmv/core/dd/ddAc.h"
#include "nusmv/core/mc/mcAc.h"

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

void print_accepting_states(NuSMVEnv_ptr env,
		  Prop_ptr prop,
		  DDMgr_ptr dd,
		  BddEnc_ptr enc,
		  const OptsHandler_ptr opts,
		  const StreamMgr_ptr streams,
		  bdd_ptr init, 
		  bdd_ptr accepted)
{
  
  /* needed for printing to commandline/file */
  const MasterPrinter_ptr wffprint =
    MASTER_PRINTER(NuSMVEnv_get_value(env, ENV_WFF_PRINTER));
  OStream_ptr stream = StreamMgr_get_output_ostream(streams);
  FILE * out = StreamMgr_get_output_stream(streams);
  
  /* get ctlspec as char* */
  node_ptr p = Prop_get_expr(prop);
  const char* ctlspec = (char*) sprint_node(wffprint, p);
  
  /* get file name for output file */
  const char * file_name = get_print_accepting(opts);
  
  /* holds names of input variables */
  const char** inames;
  int lev;
  
  /* get index of ctlspec */
  int index_of_spec = Prop_get_index(prop);
  
  /* hold size of bdd's */ 
  double init_size, acc_size, inacc_size;
  
  /* get size of decision diagram */
  const int dd_size = dd_get_size(dd);
  
  /* compute initial and accepting states */
  bdd_ptr init_and_accepted = bdd_dup(init);
  bdd_and_accumulate(dd, &init_and_accepted, accepted);
  
  /* get number of initial, accepting, initial and accepting states */
  init_size = BddEnc_count_states_of_bdd(enc, init);
  acc_size = BddEnc_count_states_of_bdd(enc, accepted);
  inacc_size = BddEnc_count_states_of_bdd(enc, init_and_accepted);
  
  /* get input names */
  inames = ALLOC( const char*, dd_size);
  nusmv_assert((const char**) NULL != inames);
  
  for(lev = 0; lev < dd_size; ++lev) {
    
    /*
    originally we used

         int index = dd_get_index_at_level(dd, lev);
    
    to get the index. this returns wrong names when dynamic reordering happend.
    now we use
    
         index = lev;
    */

    int index = lev;
    
    if(BddEnc_has_var_at_index(enc, index)) {
      inames[lev] = (const char*) sprint_node(wffprint,
                      BddEnc_get_var_name_from_index(enc, index));
    }
    else {
      inames[lev] = (const char*) NULL;
    } 
  }
  
  /* if 'print' is specified as filename, write states to commandline */ 
  if(strcmp(file_name, "print") == 0) {
    
    OStream_printf(stream, "\ninitial states: ");
    Cudd_DumpFormula_modified(dd, 1, &init, inames, out);
    OStream_printf(stream, "\nnumber of initial states: %.20g", init_size);
    OStream_printf(stream, "\n");

    OStream_printf(stream, "accepting states: ");
    Cudd_DumpFormula_modified(dd, 1, &accepted, inames, out);
    OStream_printf(stream, "\nnumber of accepting states: %.20g", acc_size);
    OStream_printf(stream, "\n");
    
    OStream_printf(stream, "initial and accepting states: ");
    Cudd_DumpFormula_modified(dd, 1, &init_and_accepted, inames, out);
    OStream_printf(stream, "\nnumber of initial and accepting states: %.20g", inacc_size);
    OStream_printf(stream, "\n\n");
  }
  
  /* write to file, if filename is specified */
  else {
    if (index_of_spec != 0){
      /* append, if file already exists*/
      out = fopen(file_name, "a");
    }
    else{
      out = fopen(file_name, "w");
    }

    fprintf(out, "CTLSPEC:              ");
    fprintf(out, "%s", ctlspec);
    fprintf(out, "\n");
    
    fprintf(out, "INIT:                 ");
    Cudd_DumpFormula_modified(dd, 1, &init, inames, out);
    fprintf(out, "\nINIT_SIZE:            %.20g", init_size);
    fprintf(out, "\n");
    
    fprintf(out, "ACCEPTING:            ");
    Cudd_DumpFormula_modified(dd, 1, &accepted, inames, out);
    fprintf(out, "\nACCEPTING_SIZE:       %.20g", acc_size);
    fprintf(out, "\n");
    
    fprintf(out, "INITACCEPTING:        ");
    Cudd_DumpFormula_modified(dd, 1, &init_and_accepted, inames, out);
    fprintf(out, "\nINITACCEPTING_SIZE:   %.20g", inacc_size);
    fprintf(out, "\n");
    
    if (Prop_get_status(prop) == Prop_True) {
      fprintf(out, "ANSWER:               TRUE\n\n");
    }
    else{
      fprintf(out, "ANSWER:               FALSE\n\n");
    }
    fclose(out);
    
  }
    
  /* clean up */
  bdd_free(dd,init_and_accepted);
  
  {
    int i;
    /* free inames */
    for( i=0; i < dd_size; ++i) {
      if( (const char*) NULL != inames[i]) { FREE( inames[i]); }
    }
    FREE(inames);
  }
  
}



