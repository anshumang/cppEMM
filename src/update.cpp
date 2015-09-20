/***********************************************************************
* cppEMM - Extensible Markov Model (EMM) for Data Stream Clustering in C++
* Copyrigth (C) 2015 Michael Hahsler, Anshuman Goswami
*
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
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "AllClasses.hpp"

void EMM::update(named_matrix newdata)
{
   //std::cout << "EMM::update()" << std::endl;
   /*
	    tracds_d <- x@tracds_d  ### get the environment
	    
	    counts <- tracds_d$mm@counts ### get matrix for performance
					 ### otherwise R copies the matrix
					 ### for each update
   */
   std::vector<std::string> s = m_TRACDS->states();
   int pos_current = 0;
   std::string cs = m_TRACDS->current_state();
   int idx = 0;
   for(auto v : s)
   {
     if(v == cs)
     {
       pos_current = idx;
     }
     idx++;
   }
   for(int i=0;i<newdata.size();i++)
   {

   }
}

int EMM::add_state()
{
          /*
		## expand?
		if(tracds_d$mm@top < 1) {
		    old_size <- nstates(x)

		    new_size <- old_size*2L
		    
		    if(verbose) cat("Resizing matrix from", old_size ,"to",
			    new_size,"\n")
		    
		    new_counts <- matrix(0, ncol=new_size, nrow=new_size)
		    #new_counts[1:old_size, 1:old_size] <- tracds_d$mm@counts
		    #tracds_d$mm@counts <- new_counts
		    new_counts[1:old_size, 1:old_size] <- counts
		    counts <<- new_counts

		    new_initial_counts <- numeric(new_size)
		    new_initial_counts[1:old_size] <- tracds_d$mm@initial_counts
		    names(new_initial_counts)[1:old_size] <- names(tracds_d$mm@initial_counts)
		    tracds_d$mm@initial_counts <- new_initial_counts

		    new_unused <- new_size:1
		    new_unused[(old_size+1):length(new_unused)] <- tracds_d$mm@unused
		    tracds_d$mm@unused <- new_unused

		    tracds_d$mm@top <- old_size+tracds_d$mm@top
		}

		## add node
		pos <- tracds_d$mm@unused[tracds_d$mm@top]
		tracds_d$mm@unused[tracds_d$mm@top] <- NA
		tracds_d$mm@top <- tracds_d$mm@top-1L
		names(tracds_d$mm@initial_counts)[pos] <- name

		tracds_d$mm@initial_counts[pos] <- 0 

		pos
         */
}
