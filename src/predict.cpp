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
#include <cassert>

int EMM::prob_max(std::vector<double> x)
{
   auto max = std::max_element(x.begin(), x.end());
   /*choose the first occurence - FIXME - need to randomize choice*/
   auto result = std::find(std::begin(x), std::end(x), max[0]);
   return std::distance(x.begin(), result);
}

std::string EMM::predict(std::string current_state, int n)
{
   std::string sel("NA");
   /*TO BE ADDED*/
   if(current_state == "NULL")
   {
       current_state = m_TRACDS->current_state();
   }
   int current_state_i=-1;
   std::vector<std::string> states = m_TRACDS->states();
   //std::cout << "Current state " << current_state <<  " states.size() " << states.size() <<  " states.back() " << states.back() << std::endl;
   //std::cout << "predict " << current_state << std::endl;
   int idx=0;
   for(auto s: states)
   {
      if(s == current_state)
      {
          current_state_i = idx;
          break; //current_state is singleton?
      }
      idx++;
   }
   assert(current_state_i>=0);
   matrix P = transition_matrix();
   if(n>1)
   {
     /*matrix product of P - not supported yet*/
     assert(n==1);
   }
   std::vector<double> prob;
   for(auto v : P[current_state_i])
   {
     prob.push_back(v);
   }

   //std::cout << "Predicted state " << prob_max(prob) << std::endl;
   sel = states[prob_max(prob)];
   
   return sel;
}
