#include <iostream>

#include "Entity.h"

using std::cout;
using std::endl;

namespace openmht {
     Entity::Entity()
     {                    
          Measurement m;
          m.set_position(Eigen::Vector2d(-1,-1));          
          this->init(-1,m); 
     }

     Entity::Entity(int id, Measurement &meas)
     {
          this->init(id, meas);
     }

     void Entity::set_dt(double dt)
     {
          tracker_.set_dt(dt);
     }

     void Entity::predict_tracker()
     {
          tracker_.predict();
     }

     Eigen::Vector2d Entity::position()
     {
          return tracker_.position();
     }

     void Entity::set_measurement(Measurement &m)
     {          
          tracker_.set_measurement(m.position());
          inc_age();
     }
     
     void Entity::missed()
     {
          occluded_age_++;
     }
     
     void Entity::inc_age()
     {
          age_++;
     }

     bool Entity::is_dead()
     {
          if (occluded_age_ > occluded_dead_age_) {
               return true;
          }
          return false;
     }

     void Entity::init(int id, Measurement &meas)
     {
          occluded_dead_age_ = 10;
          id_ = id;
          age_ = 0;
          tracker_.set_measurement(meas.position());          
     }
}
