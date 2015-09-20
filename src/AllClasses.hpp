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
#include <cfloat>
#include <iostream>

typedef std::vector<double> numeric;
typedef std::vector<int> integer;
typedef std::string character;
//typedef std::vector<char> character; //or use std::vector<char>??
typedef std::vector<bool> logical;
typedef std::vector<std::vector<double>> matrix; //C++12 : >> ok
typedef std::vector<std::pair<int, std::string>> names;
typedef std::vector<std::pair<double, std::string>> named_vector;
typedef std::vector<named_vector> named_matrix;
typedef std::vector<std::string> stringvec;

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
public:
  character m_measure;
  /*logical*/bool m_centroids;
  /*numeric*/double m_threshold;
  /*numeric*/double m_lambda;
  /*numeric*/double m_lambda_factor;
  named_matrix m_centers; /*centers can be N-dimensional*/
  named_vector m_counts;
  named_vector m_var_thresholds;
  stringvec m_last;

  static /*numeric*/double & t_wrap()
  {
    static /*numeric*/double t=0.2/*{0.2}*/;
    return t;
  }

  static double & l_wrap()
  {
    static double l=0;
    return l;
  }

  static character & m_wrap()
  {
    static character m("euclidean");
    return m;
  }

  static /*logical*/bool & c_wrap(character lhs, character rhs)
  {
    static /*logical*/bool c{lhs==rhs};
    return c;
  }

  static character getMeasure(tNN& tnn)
  {
    return tnn.m_measure;
  }

  //environment<int> tnn_d; 
  tNN(/*numeric*/double threshold=t_wrap(), character measure=m_wrap(), /*logical*/bool centroids=c_wrap(/*getMeasure(this)*/m_wrap(), std::string("euclidean")), /*numeric*/double lambda=l_wrap());

  tNN(/*numeric*/double threshold=t_wrap(), character measure=m_wrap(), /*numeric*/double lambda=l_wrap());
  named_vector cluster_centers(std::string);
  stringvec last_clustering(bool remove=false);
  void set_last(stringvec);
  void update_last(int, std::string);
  int nclusters();
};

class SimpleMC
{
public:
  integer m_unused;
  int m_top;
  matrix m_counts;
  named_vector m_initial_counts;

  static integer & u_wrap(int size)
  {
    static integer u(size);
    int idx=0;
    for(auto i : u)
    {
       u[idx] = size-idx;
       idx++;
    }
    return u;
  }

  static int & t_wrap(int size)
  {
    static int t=size-1;
    return t;
  }

  static matrix & c_wrap(int size)
  {
    static matrix c(size, numeric(size,0));
    return c;
  }

  static named_vector & ic_wrap(int size)
  {
    static named_vector ic;
    for(int i=0; i<size; i++)
    {
       ic.push_back(std::pair<double, std::string>(i, "NA"));
    } 
    return ic;
  }

  SimpleMC(int size=10);
  int smc_size();
  std::vector<std::string> smc_states();
  std::vector<int> smc_names2index(std::vector<std::string>);
  SimpleMC* smc_expand();
  SimpleMC* smc_contract();
  void smc_fade(double);
  named_matrix smc_countMatrix();
  int add_state(std::string);
};

class TRACDS
{
public:
  /*numeric*/double m_lambda;
  /*numeric*/double m_lambda_factor;
  SimpleMC* m_mm;
  character m_current_state;

  static /*numeric*/double & l_wrap()
  {
    static /*numeric*/double l=0;
    return l;
  }

  static /*numeric*/double & lf_wrap()
  {
    static /*numeric*/double lf=1;
    return lf;
  }

  TRACDS();
  TRACDS(/*numeric*/double lambda=l_wrap());
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
 double m_lambda;
 double m_lambda_factor;
 double m_threshold;
 named_matrix m_new_data;
public:
 EMM();
 EMM(/*numeric*/double threshold, character measure, /*numeric*/double lambda);
 void build(named_matrix);
 void cluster(named_matrix);
 void update();
 std::string predict();
 matrix transition_matrix();
};

#endif
