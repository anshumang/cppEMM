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

//#pragma once
#ifndef _ALLCLASSES_HPP_
#define _ALLCLASSES_HPP_

#include <vector>
#include <set>

typedef std::vector<int> numeric;
typedef std::vector<char> character; //or use std::string??
typedef std::vector<bool> logical;

template<typename T>
class environment
{
  typedef std::set<T> storage;
};

class StreamClustering
{

};

//template<typename T>
class tNN
{
  character measure;
  logical centroids;
  numeric threshold;
  numeric lambda;
  numeric lambda_factor;
  //environment<int> tnn_d; 
};

class SimpleMC
{

};

class TRACDS
{
  numeric lambda;
  numeric lambda_factor;
};

//class EMMInherit : tNN<int>, TRACDS
class EMMInherit : tNN, TRACDS
{

};

class EMMAggregate 
{
 //tNN<int> m_tNN;
 tNN m_tNN;
 TRACDS m_TRACDS; 
};

#endif
