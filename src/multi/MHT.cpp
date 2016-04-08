#include <iostream>

#include "MHT.h"

#include "munkres.h"
#include "boostmatrixadapter.h"

using std::cout;
using std::endl;

namespace openmht {
     MHT::MHT()
     {
          next_id_ = 0;
          mode_ = munkres;
     }

     int MHT::next_available_id()
     {
          return next_id_++;
     }     
     
     void MHT::process_measurements(std::list<Measurement> &measurements)
     {
          // Filter model predictions                    
          for(std::list<Entity>::iterator it = ents_.begin(); 
              it != ents_.end(); it++) {               
               it->set_dt(dt_);
               it->predict_tracker();               
          }
          
          std::list<Entity> fused;
          
          switch (mode_) {
          case munkres:
               assign_munkres(measurements, ents_, fused);
               break;          
          default:
               break;
          }

          // Cull dead entities
          std::list<Entity>::iterator it = fused.begin();
          while(it != fused.end()) {
               if (it->is_dead()) {
                    it = fused.erase(it);
               } else {
                    it++;
               }
          }

          // Copy fused to ents_
          ents_ = fused;
     }

     void MHT::assign_munkres(std::list<Measurement> &meas,
                              std::list<Entity> &tracks,
                              std::list<Entity> &fused)
     {
          // Create cost matrix using the euclidean distance between previous and
          // current blob centroids
          int meas_count = meas.size();
          int tracks_count = tracks.size();

          // Determine max of meas_count and tracks
          int rows = -1, cols = -1;
          if (meas_count == tracks_count) {               
               rows = cols = meas_count;
          } else if (meas_count > tracks_count) {               
               rows = cols = meas_count;
          } else {               
               rows = cols = tracks_count;
          }

          Matrix<double> matrix(rows, cols);
          
          // New measurements are along the Y-axis (left hand side)
          // Previous tracks are along x-axis (top-side)          
          int r = 0;
          for(std::list<Measurement>::iterator it = meas.begin(); it != meas.end(); 
              it++) {               
               std::list<Entity>::iterator it_prev = tracks.begin();
               int c = 0;
               for (; it_prev != tracks.end(); it_prev++) {
                    
                    double dist = (it->position() - it_prev->position()).squaredNorm();
                    matrix(r,c) = dist;
                    c++;
               }
               r++;
          }
          
          Munkres<double> m;
          m.solve(matrix);
          
          // Use the assignment to update the old tracks with new blob measurement
          r = 0;
          std::list<Measurement>::iterator it = meas.begin();
          for(int r = 0; r < rows; r++) {
               std::list<Entity>::iterator it_prev = tracks.begin();
               for (int c = 0; c < cols; c++) {
                    if (matrix(r,c) == 0) {
          
                         if (r < meas_count && c < tracks_count) {
                              // Does the measurement fall within 3 std's of
                              // the track?
                              if (it_prev->tracker().is_within_region(it->position(),3)) {
                                   // Found an assignment. Update the new measurement
                                   // with the track ID and age of older track. Add
                                   // to fused list
                                   //it->matched_track(*it_prev);
                                   it_prev->set_measurement(*it);
                                   fused.push_back(*it_prev);
                              } else {                                                            
                                   // TOO MUCH OF A JUMP IN POSITION                                                            
                                   // Probably a missed track or a new track
                                   it_prev->missed();
                                   fused.push_back(*it_prev);                                   
          
                                   // And a new track
                                   fused.push_back(Entity(next_available_id(),*it));                                   
                              }
                         } else if (r >= meas_count) {
                              it_prev->missed();
                              fused.push_back(*it_prev);
                         } else if (c >= tracks_count) {
                              // Possible new track
                              fused.push_back(Entity(next_available_id(),*it));
                         }
                         break; // There is only one assignment per row
                    }
                    if (c < tracks_count-1) {
                         it_prev++;
                    }
               }
               if (r < meas_count-1) {
                    it++;
               }
          }
     }
}
