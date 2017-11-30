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
  \brief Header file for print accepting states addon.
  
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

#ifndef __NUSMV_CORE_MC_MCPRINT_H__
#define __NUSMV_CORE_MC_MCPRINT_H__

void print_accepting_states(NuSMVEnv_ptr env,
		  Prop_ptr prop,
		  DDMgr_ptr dd,
		  BddEnc_ptr enc,
		  const OptsHandler_ptr opts,
		  const StreamMgr_ptr streams,
		  bdd_ptr init, 
		  bdd_ptr accepted);

#endif /* __NUSMV_CORE_MC_MCPRINT_H__ */