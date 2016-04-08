#ifndef ENTITY_H_
#define ENTITY_H_
/// ---------------------------------------------------------------------------
/// @file Entity.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2016-04-08 14:44:47 syllogismrxs>
///
/// @version 1.0
/// Created: 08 Apr 2016
///
/// ---------------------------------------------------------------------------
/// @section LICENSE
/// 
/// The MIT License (MIT)  
/// Copyright (c) 2012 Kevin DeMarco
///
/// Permission is hereby granted, free of charge, to any person obtaining a 
/// copy of this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation 
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the 
/// Software is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in 
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
/// DEALINGS IN THE SOFTWARE.
/// ---------------------------------------------------------------------------
/// @section DESCRIPTION
/// 
/// The Entity class ...
/// 
/// ---------------------------------------------------------------------------
#include <Eigen/Dense>
#include <openmht/filter/PositionTracker.h>
#include <openmht/common/Measurement.h>

namespace openmht {
     class Entity {
     public:
          Entity();
          Entity(int id, Measurement &meas);

          void set_id(int id) { id_ = id; }
          int id() { return id_; }
          
          bool is_dead();
          void set_age(int age) { age_ = age; }
          int age() { return age_; }

          void predict_tracker();
          void set_measurement(Measurement &m);
          
          Eigen::Vector2d position();

          PositionTracker & tracker() { return tracker_; }          

          void missed();

          void init(int id, Measurement &meas);

          void set_dt(double dt);
          
     protected:
          
          void inc_age();          
          
          int id_;
          int age_;
          int occluded_age_;

          int occluded_dead_age_;

          PositionTracker tracker_;
          
     private:     
     };
}

#endif
