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
#include <string>
#include <algorithm>
#include <cmath>

typedef std::vector<double> numeric;
typedef std::vector<int> integer;
typedef std::string character;
//typedef std::vector<char> character; //or use std::vector<char>??
typedef std::vector<bool> logical;
typedef std::vector<std::vector<int>> matrix; //C++11 : >> ok

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
  character m_measure;
  logical m_centroids;
  numeric m_threshold;
  numeric m_lambda;
  numeric m_lambda_factor;

  static numeric & t_wrap()
  {
    static numeric t{0.2};
    return t;
  }

  static numeric & l_wrap()
  {
    static numeric l{0};
    return l;
  }

  static character & m_wrap()
  {
    static character m("euclidean");
    return m;
  }

  static logical & c_wrap(character lhs, character rhs)
  {
    static logical c{lhs==rhs};
    return c;
  }

  //environment<int> tnn_d; 
  tNN(numeric threshold=t_wrap(), character measure=m_wrap(), logical centroids=c_wrap(/*getMeasure(this)*/m_wrap(), std::string("euclidean")), numeric lambda=l_wrap());

  static character getMeasure(tNN& tnn)
  {
    return tnn.m_measure;
  }
};

class SimpleMC
{
  integer m_unused;
  integer m_top;
  matrix m_counts;
  numeric m_initial_counts;

  static integer & u_wrap()
  {
    static integer u(10);
    return u;
  }

  SimpleMC(integer unused=u_wrap());
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
