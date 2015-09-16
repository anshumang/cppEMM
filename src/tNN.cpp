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

matrix tNN::cluster_centers()
{
   return m_centers;
}

stringvec tNN::last_clustering(bool remove)
{
   if(remove)
   {
     m_last.resize(1); 
     m_last.push_back("NA");
   }
   return m_last; 
}

void tNN::set_last(stringvec sv)
{
   m_last = sv;
}

void tNN::update_last(int i, std::string s)
{
   m_last[i] = s;
}
