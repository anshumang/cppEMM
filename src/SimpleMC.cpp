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

int SimpleMC::smc_size()
{
  return m_unused.size() - m_top;
}

std::vector<std::string> SimpleMC::smc_states()
{
  std::vector<std::string> states;
  for(auto ic : m_initial_counts)
  {
    if(ic.second == "NA")
      continue;
    states.push_back(ic.second);
  }
  return states;
}

std::vector<int> SimpleMC::smc_names2index(std::vector<std::string> state)
{
  std::vector<int> indices;
  /*TO BE ADDED*/
  return indices;   
}

SimpleMC* SimpleMC::smc_expand()
{
   SimpleMC *new_x = new SimpleMC(2*m_initial_counts.size()); 
  /*TO BE ADDED*/
  return new_x;
}

SimpleMC* SimpleMC::smc_contract()
{
  /*TO BE ADDED*/
  return this;
}

void SimpleMC::smc_fade(double f)
{
  for(int i=0; i<m_counts.size(); i++)
  {
    std::vector<double> vec = m_counts[i];
    for(int j=0; j<vec.size(); j++)
    {
      m_counts[i][j] = f * m_counts[i][j];
    }
  }
}

named_matrix SimpleMC::smc_countMatrix()
{
   std::vector<std::pair<int,bool>> used(m_initial_counts.size());
   int idx=0;
   for(auto ic : m_initial_counts)
   {
      if(ic.second == "NA")
      {
        used.push_back(std::pair<int,bool>(idx,false));
      }
      else
      {
        used.push_back(std::pair<int,bool>(idx,true));
      }
      idx++;
   }
   named_matrix nm;
   if(used.size()<1)
   {
      return nm;
   }
   int r=0, c=0;
   nm.resize(used.size());
   auto ic = m_initial_counts.begin();
   for(auto rr: m_counts)
   {
      nm[r].resize(used.size());
      auto u = used.begin();
      for(auto cc: rr)
      {
         if(u[c].second) /*true*/
         {
           nm[r][c] = std::pair<double, std::string>(rr[c], ic[u[c].first].second); 
           c++;
         }
      }
      r++;
      c=0;
   }
   return nm;
}
