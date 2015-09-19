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
#include <fstream>
#include <sstream>
#include <sys/time.h>

int main(int)
{
  std::cout << "Starting main...." << std::endl;
  EMM emm(0.1, "euclidean", 0.01);
  named_matrix train_table;
  named_vector train_row;
  train_row.push_back(std::pair<double, std::string>(1, "1"));
  train_row.push_back(std::pair<double, std::string>(2, "1"));
  train_table.push_back(train_row);
  train_row[0] = std::pair<double, std::string>(4, "2");
  train_row[1] = std::pair<double, std::string>(8, "2");
  train_table.push_back(train_row);

  std::ifstream file("0.out");
  named_matrix data;
  std::string line;
  long num_lines = 0;
  int num_words = 0;
  long value = -1;
  while(std::getline(file, line))
  {
     num_lines++;
     std::stringstream linestream(line);
     named_vector line_data;
     num_words = 0;
     while(linestream >> value)
     {
       num_words++;
       if(num_words > 2)
       {
         line_data.push_back(std::pair<double, std::string>(std::log10(value), std::to_string(num_lines)));
       }
     }
     if(num_lines % 100000 == 0)
     {
        for(auto w : line_data)
        {
            std::cout << w.first << " ";
        }
        std::cout << std::endl;
     }
     data.push_back(line_data);
  }
  std::cout << num_words << " " << num_lines << " " << value << std::endl;
  
  struct timeval start, end;
  gettimeofday(&start, NULL);
  double avg=0, num_epochs=0;
  for(int i=0; i<data.size(); i++)
  {
        if(i%432 == 0)
        {
           num_epochs++;
           gettimeofday(&end, NULL);
           avg = (avg*num_epochs + (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/(num_epochs+1);
           std::cout << i << " " << (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec) << " " << avg << std::endl;
           gettimeofday(&start, NULL);
        }
    named_matrix data_subset;
    data_subset.push_back(data[i]);
    emm.build(data_subset);
  }
  //emm.build(train_table);

  return 0;
}
