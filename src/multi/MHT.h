#ifndef MHT_H_
#define MHT_H_
/// ---------------------------------------------------------------------------
/// @file MHT.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2016-04-08 14:46:51 syllogismrxs>
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
/// The MHT class ...
/// 
/// ---------------------------------------------------------------------------
#include <list>
#include <openmht/common/Entity.h>
#include <openmht/common/Measurement.h>

namespace openmht {
     class MHT {
     public:

          typedef enum Mode {
               munkres = 0,
               cluster,
               gate,
               mht,
               jpdaf
          }Mode_t;
          
          MHT();

          void set_dt(double dt) { dt_ = dt; }
          void process_measurements(std::list<Measurement> &measurements);
          void set_mode(Mode_t mode) { mode_ = mode; }          
          
          std::list<Entity> & entities() { return ents_; }
          
     protected:
          int next_id_;
          Mode_t mode_;          
          std::list<Entity> ents_;          

          int next_available_id();
          
          void assign_munkres(std::list<Measurement> &meas,
                              std::list<Entity> &tracks,
                              std::list<Entity> &fused);
          double dt_;
     private:
     };
}

#endif
