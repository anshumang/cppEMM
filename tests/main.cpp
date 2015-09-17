/**********************************************************************
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

#include "../src/AllClasses.hpp"
#include <iostream>

int main(int)
{
  std::cout << "Staring main...." << std::endl;
  EMM emm(0.1, "euclidean", 0.01);
  named_matrix train_table;
  named_vector train_row;
  train_row.push_back(std::pair<double, std::string>(1, "1"));
  train_row.push_back(std::pair<double, std::string>(2, "1"));
  train_table.push_back(train_row);
  train_row[0] = std::pair<double, std::string>(4, "2");
  train_row[1] = std::pair<double, std::string>(8, "2");
  train_table.push_back(train_row);
  emm.build(train_table);
  return 0;
}
