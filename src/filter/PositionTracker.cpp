#include <iostream>

#include "PositionTracker.h"

using std::cout;
using std::endl;

namespace openmht {

     PositionTracker::PositionTracker() : initialized_(false)
     {  
          A_.resize(4,4);     // State transition
          B_.resize(4,2);     // Input matrix
          H_.resize(2,4);     // Measurement matrix
          Q_.resize(4,4);     // Process noise
          R_.resize(2,2);     // Measurement noise
          x0_.resize(4,1);    // Initial state
          P_.resize(4,4);    // Covariance matrix
               
          this->set_dt(0.066666667);

          // Inputs are from velocity
          B_ << 0, 0,
               0, 0,
               1, 0,
               0, 1;

          // Measurements are from x/y positions
          H_ << 1, 0, 0, 0,
               0, 1, 0, 0;

          double r = 10;
          R_ << r, 0,
               0, r;               

          z_.resize(2,1);
          z_ << 0,0;
     
          u_.resize(2,1);
          u_ << 0, 0;     

          P_ << Eigen::MatrixXf::Identity(A_.rows(), A_.cols()) * 100;
     
          kf_.setModel(A_, B_, H_, Q_, R_);
     }

     void PositionTracker::set_dt(double dt)
     {
          double T = dt;
          A_ << 1, 0, T, 0,
               0, 1, 0, T,
               0, 0, 1, 0,
               0, 0, 0, 1;

          double q = 1 * T;
          Q_ = Eigen::MatrixXf::Identity(A_.rows(), A_.cols()) * q;
     }

     Eigen::MatrixXf PositionTracker::R()
     {
          return kf_.R();
     }

     void PositionTracker::set_Q(double q)
     {
          Q_ = Eigen::MatrixXf::Identity(A_.rows(), A_.cols()) * q;
          kf_.setModel(A_, B_, H_, Q_, R_);
     }
     void PositionTracker::set_R(double r)
     {
          R_ << r, 0,
               0, r;

          kf_.setModel(A_, B_, H_, Q_, R_);
     }

     void PositionTracker::set_R(double r0, double r1, double r2, double r3)
     {
          R_ << r0, r1,
               r2, r3;

          kf_.setModel(A_, B_, H_, Q_, R_);
     }

     void PositionTracker::set_P(double p)
     {
          P_ << Eigen::MatrixXf::Identity(A_.rows(), A_.cols()) * p;
          kf_.init(kf_.state(), P_);
     }

     void PositionTracker::set_measurement(Eigen::Vector2d m)
     {
          if (initialized_) {          
               z_ << m(0,0) , m(1,0);
               kf_.update(z_);
          } else {
               initialized_ = true;
               x0_ << m(0,0) , m(1,0), 0, 0;          
               kf_.init(x0_,P_);
          }
     }

     void PositionTracker::predict()
     {
          if (initialized_) {
               kf_.predict(u_);
          }
     }

     Eigen::Vector2d PositionTracker::position()
     {
          Eigen::MatrixXf s = kf_.state();
          Eigen::Vector2d p(s(0,0), s(1,0));
          return p;
     }

     Eigen::Vector2d PositionTracker::velocity()
     {
          Eigen::MatrixXf s = kf_.state();
          Eigen::Vector2d v(s(2,0), s(3,0));     
          return v;
     }

     Ellipse PositionTracker::error_ellipse(double confidence)
     {
          return kf_.error_ellipse(confidence);
     }

     bool PositionTracker::is_within_region(Eigen::Vector2d z, double std)
     {
          z_ << z(0,0), z(1,0);
          return kf_.is_within_region(z_, std);
     }

     Eigen::MatrixXd PositionTracker::meas_covariance()
     {
          return kf_.meas_covariance().cast<double>();
     }

     void PositionTracker::set_position(Eigen::Vector2d p)
     {
          Eigen::MatrixXf x(4,1);
          x << p(0,0), p(1,0), 0, 0;
          kf_.set_state(x);
     }

     void PositionTracker::print()
     {
          kf_.print();
     }

}
