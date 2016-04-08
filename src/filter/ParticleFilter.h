#ifndef PARTICLE_FILTER_H_
#define PARTICLE_FILTER_H_
// /// ----------------------------------------------------------------------------
// /// @file ParticleFilter.h
// /// @author Kevin DeMarco <kevin.demarco@gmail.com>
// ///
// /// Time-stamp: <2016-04-08 11:21:47 syllogismrxs>
// ///
// /// @version 1.0
// /// Created: 16 Jan 2013
// ///
// /// ----------------------------------------------------------------------------
// /// @section LICENSE
// /// 
// /// The MIT License (MIT)  
// /// Copyright (c) 2012 Kevin DeMarco
// ///
// /// Permission is hereby granted, free of charge, to any person obtaining a 
// /// copy of this software and associated documentation files (the "Software"), 
// /// to deal in the Software without restriction, including without limitation 
// /// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// /// and/or sell copies of the Software, and to permit persons to whom the 
// /// Software is furnished to do so, subject to the following conditions:
// /// 
// /// The above copyright notice and this permission notice shall be included in 
// /// all copies or substantial portions of the Software.
// /// 
// /// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// /// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// /// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// /// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// /// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// /// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// /// DEALINGS IN THE SOFTWARE.
// /// ----------------------------------------------------------------------------
// /// @section DESCRIPTION
// /// 
// /// The ParticleFilter / Particle classes ...
// /// 
// /// ----------------------------------------------------------------------------
// 
// #include <vector>
// 
// #include <cv.h>
// 
// #include <boost/random/mersenne_twister.hpp>
// 
// using std::cout;
// using std::endl;
// 
// class Particle {
// private:
// protected:
//      cv::Point center_;
//      double heading_;
//      cv::Point2d velocity_;
//      double weight_; // non-normalized weight
//      double alpha_;  // normalized weight
// public:
//      Particle();
//      Particle(cv::Point center, double heading, cv::Point2d velocity, double weight)
//      {
// 	  center_ = center;
// 	  heading_ = heading;
// 	  velocity_ = velocity;
// 	  weight_ = weight;
//      }
// 
//      cv::Point center() { return center_; }
//      double heading() { return heading_; }
//      cv::Point2d velocity() { return velocity_; }
//      
//      void set_center(cv::Point center) { center_ = center; }
//      void set_heading(double heading) { heading_ = heading; }
//      void set_velocity(cv::Point2d velocity) { velocity_ = velocity; }
// 
//      int kinematic_step()
//      {
// 	  center_.x = center_.x + velocity_.x;
// 	  center_.y = center_.y + velocity_.y;
// 	  return 0;
//      }
// 
// //Gaussian(self, mu, sigma, x):
// //        
// //        # calculates the probability of x for 1-dim Gaussian with mean mu and var. sigma
// //        return exp(- (mu - x) ** 2 / (sigma ** 2) / 2.0) / sqrt(2.0 * pi * (sigma ** 2))
//      
//      cv::Point gaussian(double mu, double sigma, cv::Point point)
//      {
// 	  cv::Point distribution;
// 	  distribution.x = exp(- pow(mu - point.x,2) / pow(sigma,2) / 2.0) / sqrt(2.0 * 3.14159 * pow(sigma,2));
// 	  distribution.y = exp(- pow(mu - point.y,2) / pow(sigma,2) / 2.0) / sqrt(2.0 * 3.14159 * pow(sigma,2));
// 	  return distribution;
//      }
// 
// 
//      double importance_weight_update(cv::Point target)
//      {
// 	  double dist = (sqrt ( pow(target.x-center_.x,2) + 
// 	  			pow(target.y-center_.y,2))) ;
// 
// 	  weight_ = 1 / dist;
// 	  return weight_;
//      }
// 
//      double CrossProduct(const cv::Point2d &v1, const cv::Point2d & v2)
//      {
// 	  return (v1.x*v2.y) - (v1.y*v2.x);
//      }
// 
//      double importance_weight_update(cv::Point target, cv::Vec2d velocity)
//      {
// 	  double dist = (sqrt ( pow(target.x-center_.x,2) + 
// 	  			pow(target.y-center_.y,2))) ;
// 
// 	  double crossProduct = CrossProduct(velocity, velocity_);
// 	  
// 	  double alpha = 0.5;
// 	  weight_ = alpha*(1/dist) + (1-alpha)*(1/crossProduct);
// 	  	  
// 	  //double prob = 1.0;
// 	  //double prob_gaussian = gaussian(dist, );
// 
// 	  //weight_ = 1 / dist;
// 	  //weight_ = 1 / crossProduct;
// 
// 	  //cout << "*********************" << endl;
// 	  //cout << "Target | x: " << target.x << " | y:" << target.y << endl;
// 	  //cout << "Center | x: " << center_.x << " | y:" << center_.y << endl;
// 	  //cout << "Weight: " << weight_ << endl;
// 
// 	  return weight_;
//      }
// 
//      int normalize_importance_weight(double wNorm)
//      {
// 	  alpha_ = weight_ / wNorm;
// 	  return 0;
//      }
// 
//      double normalized_weight()
//      {
// 	  return alpha_;
//      }
// 
//      double not_normalized_weight()
//      {
// 	  return weight_;
//      }
// 
// };
// 
// class ParticleFilter {
// private:
// protected:
//      std::vector<Particle> particles_;
//      int num_particles_;
// 
//      double wMax_;
// 
//      boost::mt19937 gen_;
// 
//      // State space ranges:
//      double x_min_;
//      double x_max_;
//      double y_min_;
//      double y_max_;
//      double heading_min_;
//      double heading_max_;
//      double velocity_min_;
//      double velocity_max_;
// 
// public:
//      ParticleFilter() {;}
//      
//      // Particle filter methods
//      int init(int num_particles,
// 	      double x_min, double x_max, 
// 	      double y_min, double y_max,
// 	      double heading_min, double heading_max,
// 	      double velocity_min, double velocity_max);
// 
//      int kinematic_step();
//      int importance_weight_update(cv::Point target);
//      int importance_weight_update(cv::Point target, cv::Point2d velocity);
//      int resample_wheel();
// 
//      // Set / Get methods
//      int getParticles(std::vector<Particle> &particles);
// };
// 
#endif
