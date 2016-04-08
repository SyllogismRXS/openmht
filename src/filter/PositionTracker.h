#ifndef POSITIONTRACKER_H_
#define POSITIONTRACKER_H_
/// ---------------------------------------------------------------------------
/// @file PositionTracker.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2016-04-08 14:39:32 syllogismrxs>
///
/// @version 1.0
/// Created: 20 Mar 2016
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
/// The PositionTracker class ...
/// 
/// ---------------------------------------------------------------------------
#include <Eigen/Dense>
#include <openmht/filter/KalmanFilter.h>

namespace openmht {

     class PositionTracker {
     public:
          PositionTracker();     

          void set_dt(double dt);
          void set_measurement(Eigen::Vector2d m);
          void predict();
          Eigen::Vector2d position();
          Eigen::Vector2d velocity();
          Ellipse error_ellipse(double confidence);
          bool is_within_region(Eigen::Vector2d z, double std);
          Eigen::MatrixXd meas_covariance();
          void set_position(Eigen::Vector2d p);
          void set_R(double r);
          void set_R(double r0, double r1, double r2, double r3);
          void set_P(double p);
          void set_Q(double q);
          Eigen::MatrixXf R();
          void print();
     
     protected:
          KalmanFilter kf_;
          Eigen::MatrixXf A_;     // system matrix
          Eigen::MatrixXf B_;     // input matrix
          Eigen::MatrixXf H_;     // measurement matrix
          Eigen::MatrixXf Q_;     // process noise matrix
          Eigen::MatrixXf R_;     // measurement noise matrix
     
          Eigen::MatrixXf x0_;    // initial position
          Eigen::MatrixXf P_;     // initial state covariance matrix 
     
          Eigen::MatrixXf u_;     // Input acceleration 
          Eigen::MatrixXf z_;     // Measurement (position)     

          bool initialized_;
     private:
     };

}

#endif
