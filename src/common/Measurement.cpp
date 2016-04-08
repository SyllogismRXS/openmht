#include <iostream>

#include "Measurement.h"

using std::cout;
using std::endl;

namespace openmht {
     Measurement::Measurement()
     {
          
     }

     void Measurement::set_position(const Eigen::Vector2d position) 
     { 
          position_ = position; 
     }
     
     Eigen::Vector2d Measurement::position()
     {
          return position_;
     }
}
