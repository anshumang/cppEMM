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

void EMM::cluster(named_matrix newdata)
{
    stringvec sv(newdata.size(), " ");
    m_tNN->set_last(sv);
    
    for(int i=0; i<newdata.size(); i++)
    {
        named_vector nd = newdata[i]; //nd <- newdata[i,, drop = FALSE]
        if(std::all_of(nd.begin(), nd.end(), [](std::pair<double, std::string> p){ return p.second == "NA"; }))//if(all(is.na(nd))) {
        {
          m_tNN->update_last(i, "NA"); //tnn_d$last[i] <- as.character(NA)
          continue; //next }
        }

        //if(x@lambda>0)
        //tnn_d$counts <- tnn_d$counts * x@lambda_factor
        if(m_lambda>0)
        {
           //std::for_each(m_tNN->m_counts.begin(), m_tNN->m_counts.end(), [](double d){d=d*m_lambda_factor;}); 
           int idx = 0;
           for(auto v : m_tNN->m_counts)
           {
               m_tNN->m_counts[idx] = std::pair<double, std::string>(m_tNN->m_counts[idx].first * m_lambda_factor, m_tNN->m_counts[idx].second);
               idx++;
           }
        }
        /*if(nclusters(x)<1) {
          sel <- "1" 
          rownames(nd) <- sel 
          tnn_d$centers <- nd
          tnn_d$counts[sel] <- 1 
          ## initialize variable threshold
          tnn_d$var_thresholds[sel] <- x@threshold
        }*/
        if(m_tNN->nclusters()<1)
        {
           std::string sel("1");
           int idx=0;
           for(auto nv : nd)
           {
              nd[idx] = std::pair<double, std::string>(nd[idx].first, sel);
              idx++;
           }
           m_tNN->m_centers = nd;
           m_tNN->m_counts.push_back(std::pair<double, std::string>(1,sel));
           m_tNN->m_var_thresholds.push_back(std::pair<double, std::string>(m_threshold, sel));
        }
        else
        {
           /*## find a matching state
           #sel <- find_clusters(x, nd, match_cluster="exact")
           ### all with inside<=0 are matches
           inside <- dist(nd, tnn_d$centers, 
                    method=x@distFun) - tnn_d$var_thresholds
           names(inside) <- rownames(tnn_d$centers)
           ## find all matches  
           matches <- names(inside)[which(inside<0)]
           if(length(matches)==0) { sel <- NA
           }else if(length(matches)==1) { sel <- matches
           }else sel <- matches[which.min(inside[matches])]*/
         /*supports euclidean only*/
           named_matrix inside;
           int row=0, col=0;
           for(auto v : nd)
           {  named_vector r(m_tNN->m_centers.size());
              inside.push_back(r);
              for(auto w : m_tNN->m_centers)
              {
                  inside[row][col] = std::pair<double, std::string>(std::fabs(v.first - w.first) - m_tNN->m_var_thresholds[col].first, w.second);
                  col++;
              }
              row++;
              col=0;
           }
           std::vector<std::string> matches;
           row=0;col=0;
           for(auto r : inside)
           {
               for(auto c: r)
               {
                  if(c.first<0)
                  {
                    matches.push_back(c.second);
                  }
                  col++;
               }
               row++;
               col=0;
           }
           std::string sel("NA");
           if(matches.size()==0)
           {
               sel = "NA";
           }
           else if(matches.size()==1)
           {
               sel = matches[0];
           }
           else
           {
               double min_dist = DBL_MAX;
               for(auto r:inside)
               {
                   auto row = r;
                   for(auto c: row)
                   {
                       auto other_s = c.second;
                       if(std::any_of(matches.begin(), matches.end(), [other_s](std::string s){return other_s==s;}))
                       {
                           if(c.first < min_dist)
                           {
                               sel = c.second; 
                           }
                       }
                   }
               }
           }/*end else matches.size() > 1*/
                    /*## NA means no match -> create a new node
                    if(is.na(sel)) {
                        ## New node
                        ## get new node name (highest node
                        ## number is last entry in count)
                        sel <- as.character(
                                max(suppressWarnings(
                                                as.integer(names(tnn_d$counts))
                                                ), na.rm=TRUE) + 1L)

                        rownames(nd) <- sel
                        tnn_d$centers <- rbind(tnn_d$centers, nd)
                        tnn_d$counts[sel] <- 1
                        ## initialize threshold
                        tnn_d$var_thresholds[sel] <- x@threshold}*/
             if(sel == "NA")
             {
                int max = 0;
                for(auto c: m_tNN->m_counts)
                {
                    max = std::stoi(c.second) > max ? std::stoi(c.second) : max;
                }
                sel = std::to_string(max);
                int idx = 0;
                for(auto n : nd)
                {
                    nd[idx] = std::pair<double, std::string>(n.first, sel);
                    m_tNN->m_centers.push_back(nd[idx]);
                    idx++;
                }
                m_tNN->m_counts.push_back(std::pair<double, std::string>(1,sel));
                m_tNN->m_var_thresholds.push_back(std::pair<double, std::string>(m_threshold, sel));
             }
             else
             {
                        /*## assign observation to existing node

                        ## update center (if we use centroids)
                        if(x@centroids) {

                            ## try moving first
                            nnas <- !is.na(nd)
                            new_center <- tnn_d$centers[sel,]
                            new_center[nnas] <- (new_center[nnas] * tnn_d$counts[sel] +  nd[nnas]) / (tnn_d$counts[sel]+1)

                            ## replace NAs with the new data
                            nas <- is.na(new_center)
                            if(any(nas)) new_center[nas] <- nd[nas]

                            ## check if move is legal (does not enter
                            ## another cluster's threshold)
                            if(length(matches)<2) {
                                tnn_d$centers[sel,] <- new_center
                            }else{
                                violation <- dist(rbind(new_center),
                                        tnn_d$centers[matches,],
                                        method=x@distFun) - tnn_d$var_thresholds[matches]


                                if(sum(violation<0)<2) {
                                    tnn_d$centers[sel,] <- new_center
                                }

                            }

                        }

                        ## update counts
                        tnn_d$counts[sel] <- tnn_d$counts[sel] + 1*/

                        if(m_tNN->m_centroids)
                        {

                        }
             }
         }
      }
}
