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

void EMM::update()
{
   //std::cout << "EMM::update()" << std::endl;
   /*
	    tracds_d <- x@tracds_d  ### get the environment
	    
	    counts <- tracds_d$mm@counts ### get matrix for performance
					 ### otherwise R copies the matrix
					 ### for each update
   */
   std::vector<std::string> s = m_TRACDS->states();
   int pos_current = -1;
   std::string cs = m_TRACDS->current_state();
   //matrix counts = m_TRACDS->m_mm->m_counts;
   int idx = 0;
   //## get position of current date in matrix
   //pos_current <- which(states(x) == current_state(x)) //Can pos_current be a vector?
   for(auto v : s)
   {
     if(v == cs)
     {
       pos_current = idx;
     }
     idx++;
   }
   std::string sel("NA");
   for(auto i : m_new_data)
   {
     //## cluster returns NA if we start a new sequence.
     if(i[0].second == "NA")
     {
        pos_current = -1;
        continue;
     }

     //## fade TRACDS structure?
     //### FIXME: counts!!!
     if(m_lambda > 0)
     {
           int idx = 0;
           for(auto v : m_TRACDS->m_mm->m_initial_counts)
           {
               m_TRACDS->m_mm->m_initial_counts[idx] = std::pair<double, std::string>(m_TRACDS->m_mm->m_initial_counts[idx].first * m_lambda_factor, m_TRACDS->m_mm->m_initial_counts[idx].second);
               idx++;
           }
           int row=0, col=0;
           for (auto r : m_TRACDS->m_mm->m_counts)
           {
              for(auto c : r)
              {
                 m_TRACDS->m_mm->m_counts[row][col] = m_TRACDS->m_mm->m_counts[row][col] * m_lambda_factor;
                 col++;
              }
              row++; col=0;
           }
     }     
     //## state exists?
     //pos_new <- which(states(x) == sel) //can pos_new be a vector?
     int pos_new = -1;
     int idx=0;
     for(auto v : s)
     {
       if(v == i[0].second)
       {
         pos_new = idx;
       }
       idx++;
     }

     //## no: create state
     //if(!length(pos_new)) pos_new <- .addState(sel)
     if(pos_new < 0)
     {
       m_TRACDS->m_mm->add_state(i[0].second);
     }

     //## add transition
     //## no current state?
     /*if(!length(pos_current)) {
	   tracds_d$mm@initial_counts[pos_new] <- tracds_d$mm@initial_counts[pos_new] + 1 
     }else{
           ## tracds_d$mm@counts[pos_current, pos_new] <- tracds_d$mm@counts[pos_current, pos_new] + 1
	   counts[pos_current, pos_new] <- counts[pos_current, pos_new] + 1
     }*/
     if(pos_current < 0)
     {
          m_TRACDS->m_mm->m_initial_counts[pos_new] = std::pair<double, std::string>(m_TRACDS->m_mm->m_initial_counts[pos_new].first + 1, m_TRACDS->m_mm->m_initial_counts[pos_new].second);
     }
     else
     {
          m_TRACDS->m_mm->m_counts[pos_current][pos_new] = m_TRACDS->m_mm->m_counts[pos_current][pos_new] + 1;
     }
     //## update current_state
     //pos_current <- pos_new
     pos_current = pos_new;
     sel = i[0].second;
   }

   //## save the last state as current
   //tracds_d$current_state <- sel
   m_TRACDS->m_current_state = sel;
}

int SimpleMC::add_state(std::string name)
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
         */
         if(m_top < 0)
         {
            int old_size = smc_size();
            int new_size = old_size * 2;
            matrix new_counts(new_size, std::vector<double>(new_size, 0));
            int r=0;
            for(auto m : m_counts)
            {
               std::copy(m_counts[r].begin(), m_counts[r].end(), new_counts[r].begin());
               r++;
            }
            m_counts = new_counts;

            named_vector new_initial_counts(new_size);
            int idx=0;
            for(auto i : new_initial_counts)
            {
                if(idx < m_initial_counts.size())
                {
                   new_initial_counts[idx] = m_initial_counts[idx];
                }
                else
                {
                   new_initial_counts[idx] = std::pair<double, std::string>(0, "NA");
                }
                idx++;
            } 
            m_initial_counts = new_initial_counts;

            std::vector<int> new_unused(new_size);
            idx = 0;
            for(auto v : new_unused)
            {
                if(idx < old_size)
                {
                   new_unused[idx] = new_size - idx;
                }
                else
                {
                   new_unused[idx] = m_unused[idx-old_size];
                }
                idx++;
            }

            m_top = m_top + old_size - 1;
         }

         /*
		## add node
		pos <- tracds_d$mm@unused[tracds_d$mm@top]
		tracds_d$mm@unused[tracds_d$mm@top] <- NA
		tracds_d$mm@top <- tracds_d$mm@top-1L
		names(tracds_d$mm@initial_counts)[pos] <- name

		tracds_d$mm@initial_counts[pos] <- 0 

		pos
         */
         int pos = m_unused[m_top];
         m_unused[m_top] = -1;
         m_top = m_top - 1;
         m_initial_counts[pos-1] = std::pair<double, std::string>(0, name);
}
