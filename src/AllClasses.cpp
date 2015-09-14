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

tNN::tNN(numeric threshold, character measure, logical centroids, numeric lambda)
 : m_threshold(threshold),
   m_measure(measure),
   m_centroids(centroids),
   m_lambda(lambda)
{
   std::transform(m_lambda.begin(), m_lambda.begin(), m_lambda_factor.begin(), [](double l) {return std::pow(2, (-l));});
}

tNN::tNN(numeric threshold, character measure, numeric lambda)
 : m_threshold(threshold),
   m_measure(measure),
   m_lambda(lambda)
{
   std::transform(m_lambda.begin(), m_lambda.begin(), m_lambda_factor.begin(), [](double l) {return std::pow(2, (-l));});
}

SimpleMC::SimpleMC(int size)
{
 m_unused=u_wrap(size); 
 m_top=t_wrap(size); 
 m_counts=c_wrap(size);
 m_initial_counts=ic_wrap(size);
}

TRACDS::TRACDS()
{
  m_lambda=l_wrap();
  m_lambda_factor=lf_wrap();
}

TRACDS::TRACDS(numeric lambda)
:m_lambda(lambda)
{
  m_lambda_factor=lf_wrap();
}

EMM::EMM(numeric threshold, character measure, numeric lambda) /*variadic constructors - HOWTO?*/
: m_tNN(new tNN(threshold, measure, lambda)),
  m_TRACDS(new TRACDS(lambda))
{
}
