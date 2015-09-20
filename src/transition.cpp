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
#include <numeric>

matrix EMM::transition_matrix()
{
  matrix m(m_TRACDS->m_mm->m_counts.size(), std::vector<double>(m_TRACDS->m_mm->m_counts.size(), 0));
  /*TO BE ADDED*/
  m_TRACDS->m_mm->smc_countMatrix();
  /*prior equals TRUE not supported yet*/
  //if(prior) m <- m+1
 
  /*Only supporting type = probability now*/
  //if(type=="counts") return(m)

  //rs <- rowSums(m)
  //prob <- m/rs

  //## we have to handle absorbing states here (row sum is 0)
  //absorbing <- which(rs==0)
  //prob[absorbing,] <- 0
  //for(i in absorbing) prob[i,i] <- 1

  std::vector<int> absorbing;
  int row=0, col=0;
  for(auto r : m_TRACDS->m_mm->m_counts)
  {
     double rowsum = std::accumulate(r.begin(), r.end(), 0);
     if(rowsum == 0)
     {
       std::fill(m[row].begin(), m[row].end(), 0);
       m[row][row] = 1; 
     }
     else
     {
       std::transform(r.begin(), r.end(), m[row].begin(), [rowsum](double val){return val/rowsum;});
     /*for(auto c : r)
     {
        m[row][col] = c[col]/rowsum;
        col++;
     }*/
     }
     row++;
     col=0;
  }

  return m;
}
