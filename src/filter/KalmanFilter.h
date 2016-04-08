#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
/// ----------------------------------------------------------------------------
/// @file KalmanFilter.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2016-04-08 11:08:27 syllogismrxs>
///
/// @version 1.0
/// Created: 16 Jan 2013
///
/// ----------------------------------------------------------------------------
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
/// ----------------------------------------------------------------------------
/// @section DESCRIPTION
/// 
/// The KalmanFilter class ...
/// 
/// ----------------------------------------------------------------------------

#include <Eigen/Dense>

#include <openmht/common/Ellipse.h>

namespace openmht {
     class KalmanFilter {
     protected:
	  Eigen::MatrixXf F_; // System dynamics
	  Eigen::MatrixXf B_; // Control matrix
	  Eigen::MatrixXf H_; // Measurement matrix
	  
          Eigen::MatrixXf Q_; // Process variance     ; V*V'
          Eigen::MatrixXf R_; // Measurement variance ; W*W'
	  	  
	  // Matrices / vectors for Kalman step
	  Eigen::MatrixXf x_; // Estimated state
	  Eigen::MatrixXf P_; // State variance matrix
	  Eigen::MatrixXf K_; // Kalman gain
	  Eigen::MatrixXf eye_;// = Eigen::Matrix<float, 2, 2>::Identity();
          
     public:
	  KalmanFilter();
	  KalmanFilter(const Eigen::MatrixXf &F, const Eigen::MatrixXf &B, 
		       const Eigen::MatrixXf &H, const Eigen::MatrixXf &Q, 
		       const Eigen::MatrixXf &R);
	  
	  int setModel(const Eigen::MatrixXf &F, const Eigen::MatrixXf &B, 
		       const Eigen::MatrixXf &H, const Eigen::MatrixXf &Q, 
		       const Eigen::MatrixXf &R);

	  int init(const Eigen::MatrixXf &x0, const Eigen::MatrixXf &P0);

          void set_state(const Eigen::MatrixXf &x0);

	  int predict(const Eigen::MatrixXf &u);
	  int update(const Eigen::MatrixXf &z);

	  Eigen::MatrixXf state() const;
	  Eigen::MatrixXf covariance() const;
          Eigen::MatrixXf R() { return R_; }
          Ellipse error_ellipse(double confidence);
          bool is_within_region(Eigen::MatrixXf Zm, double std);          

          void set_R(Eigen::MatrixXf R) { R_ = R; }
          void set_P(Eigen::MatrixXf P) { P_ = P; }
                    
          Eigen::MatrixXf meas_covariance();

          bool operator==(const KalmanFilter& other)
          {
               double eps = 0.10;
               bool state_check = (this->x_ - other.x_).isMuchSmallerThan(eps);
               bool covar_check = (this->P_ - other.P_).isMuchSmallerThan(eps);
          
               return (state_check && covar_check);
          }

          void print();
     };     
}


#endif
