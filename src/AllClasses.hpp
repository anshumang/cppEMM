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
#include <utility>

typedef std::vector<double> numeric;
typedef std::vector<int> integer;
typedef std::string character;
//typedef std::vector<char> character; //or use std::vector<char>??
typedef std::vector<bool> logical;
typedef std::vector<std::vector<double>> matrix; //C++12 : >> ok
typedef std::vector<std::pair<int, std::string>> names;
typedef std::vector<std::vector<std::pair<double, std::string>>> named_matrix;

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
  matrix m_centers;
  numeric m_counts;
  numeric m_var_thresholds;
  character m_last;

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

  static character getMeasure(tNN& tnn)
  {
    return tnn.m_measure;
  }

public:
  //environment<int> tnn_d; 
  tNN(numeric threshold=t_wrap(), character measure=m_wrap(), logical centroids=c_wrap(/*getMeasure(this)*/m_wrap(), std::string("euclidean")), numeric lambda=l_wrap());

  tNN(numeric threshold=t_wrap(), character measure=m_wrap(), numeric lambda=l_wrap());
  matrix cluster_centers();
  character last_clustering(bool remove=false);
};

class SimpleMC
{
  integer m_unused;
  int m_top;
  matrix m_counts;
  names m_initial_counts;

  static integer & u_wrap(int size)
  {
    static integer u(size);
    return u;
  }

  static int & t_wrap(int size)
  {
    static int t=size;
    return t;
  }

  static matrix & c_wrap(int size)
  {
    static matrix c(size, numeric(size,0));
    return c;
  }

  static names & ic_wrap(int size)
  {
    static names ic;
    for(int i=0; i<size; i++)
    {
       ic.push_back(std::pair<double, std::string>(i, "NA"));
    } 
    return ic;
  }

public:
  SimpleMC(int size=10);
  int smc_size();
  std::vector<std::string> smc_states();
  std::vector<int> smc_names2index(std::vector<std::string>);
  SimpleMC* smc_expand();
  SimpleMC* smc_contract();
  void smc_fade(double);
  named_matrix smc_countMatrix();
};

class TRACDS
{
  numeric m_lambda;
  numeric m_lambda_factor;
  SimpleMC* m_mm;
  character m_current_state;

  static numeric & l_wrap()
  {
    static numeric l{0};
    return l;
  }

  static numeric & lf_wrap()
  {
    static numeric lf{1};
    return lf;
  }

public:
  TRACDS();
  TRACDS(numeric lambda=l_wrap());
  int nstates();
  std::vector<std::string> states();
  std::string current_state();
};

//class EMMInherit : tNN<int>, TRACDS
/*class EMMInherit : tNN, TRACDS
{

};*/

//class EMMAggregate 
class EMM 
{
 //tNN<int> m_tNN;
 tNN* m_tNN;
 TRACDS* m_TRACDS; 
public:
 EMM();
 EMM(numeric threshold, character measure, numeric lambda);
 void build();
 void cluster();
 void update();
 EMM* predict();
 matrix transition_matrix();
};

#endif
