// #include <iostream>
// #include <boost/random/mersenne_twister.hpp>
// #include <boost/random/uniform_int.hpp>
// #include <boost/random/uniform_real.hpp>
// 
// #include "ParticleFilter.h"
// 
// using std::cout;
// using std::endl;
// 
// /// Randomly initialize all particles
// int ParticleFilter::init(int num_particles, double x_min, double x_max, 
// 	      double y_min, double y_max,
// 	      double heading_min, double heading_max,
// 	      double velocity_min, double velocity_max)
// {
//      num_particles_ = num_particles;
// 
//      x_min_ = x_min;
//      x_max_ = x_max;
//      y_min_ = y_min;
//      y_max_ = y_max;
//      heading_min_ = heading_min;
//      heading_max_ = heading_max;
//      velocity_min_ = velocity_min;
//      velocity_max_ = velocity_max;
//      
//      boost::uniform_int<> x_dist(x_min_, x_max_);
//      boost::uniform_int<> y_dist(y_min_, y_max_);
//      boost::uniform_int<> heading_dist(heading_min_, heading_max_);
//      boost::uniform_int<> x_velocity_dist(velocity_min_, velocity_max_);
//      boost::uniform_int<> y_velocity_dist(velocity_min_, velocity_max_);
//      
//      for (int i = 0 ; i < num_particles_ ; i++) {
// 	  double x=0, y=0, heading=0, x_velocity=0, y_velocity;
// 
// 	  x = x_dist(gen_);
// 	  y = y_dist(gen_);
// 	  heading = heading_dist(gen_);
// 	  x_velocity = x_velocity_dist(gen_);
// 	  y_velocity = y_velocity_dist(gen_);
// 	  
// 	  cv::Point center(x,y);
// 	  cv::Point2d velocity(x_velocity,y_velocity);
// 
// 	  Particle particle(center,heading,velocity,1.0/num_particles_); 
// 	  particles_.push_back(particle);
//      }
// 
//      return 0;
// }
// 
// /// Use motion model to update particles
// int ParticleFilter::kinematic_step()
// {
//      std::vector<Particle>::iterator it;
//      for (it = particles_.begin(); it != particles_.end(); it++) {
// 	  it->kinematic_step();
//      }
//      return 0;
// }
// 
// int ParticleFilter::importance_weight_update(cv::Point target) 
// {
//      double champ = -9999;
//      double wNorm = 0;
//      std::vector<Particle>::iterator it;
//      for (it = particles_.begin(); it != particles_.end(); it++) {
// 	  double w = it->importance_weight_update(target);
// 	  wNorm += w;
// 
// 	  if (w > champ) {
// 	       champ = w;
// 	  }
//      }
// 
//      wMax_ = champ;
// 
//      for (it = particles_.begin(); it != particles_.end(); it++) {
// 	  it->normalize_importance_weight(wNorm);
//      }
// 
//      return 0;
// }
// 
// int ParticleFilter::importance_weight_update(cv::Point target, cv::Point2d velocity) 
// {
//      double champ = -9999;
//      double wNorm = 0;
//      std::vector<Particle>::iterator it;
//      for (it = particles_.begin(); it != particles_.end(); it++) {
// 	  double w = it->importance_weight_update(target, velocity);
// 	  wNorm += w;
// 
// 	  if (w > champ) {
// 	       champ = w;
// 	  }
//      }
// 
//      wMax_ = champ;
// 
//      for (it = particles_.begin(); it != particles_.end(); it++) {
// 	  it->normalize_importance_weight(wNorm);
//      }
// 
//      return 0;
// }
// 
// 
// 
// int ParticleFilter::resample_wheel()
// {
//      boost::uniform_int<> index_select(0, particles_.size()-1);
//      boost::uniform_real<> beta_select(0, 2*wMax_);
//      
//      std::vector<Particle> newParticles;
// 
//      int index = index_select(gen_);
//      double beta = 0;
// 
//      //std::vector<Particle>::iterator it;
//      //for (it = particles_.begin(); it != particles_.end(); it++) {
//      for (int i = 0 ; i < num_particles_; i++) {
// 	  beta += beta_select(gen_);
// 	  while (beta > particles_[index].not_normalized_weight()) {
// 	       beta -= particles_[index].not_normalized_weight();
// 	       index = (index + 1) % particles_.size(); 
// 	  }
// 	  
// 	  Particle part1 = particles_[index];
// 	  Particle part2 = part1;
// 
// 	  boost::uniform_int<> x1_velocity_dist(velocity_min_, velocity_max_);
// 	  boost::uniform_int<> y1_velocity_dist(velocity_min_, velocity_max_);
// 
// 	  boost::uniform_int<> x2_velocity_dist(velocity_min_, velocity_max_);
// 	  boost::uniform_int<> y2_velocity_dist(velocity_min_, velocity_max_);
//      
// 	  cv::Point2d velocity1, velocity2;
// 	  velocity1.x = x1_velocity_dist(gen_);
// 	  velocity1.y = y1_velocity_dist(gen_);
// 
// 	  velocity2.x = x2_velocity_dist(gen_);
// 	  velocity2.y = y2_velocity_dist(gen_);
// 
// 	  part1.set_velocity(velocity1);
// 	  part2.set_velocity(velocity2);
//      
// 	  newParticles.push_back(part1);
// 	  newParticles.push_back(part2);
//      }
//      particles_ = newParticles;
//      return 0;
// }
// 
// 
// int ParticleFilter::getParticles(std::vector<Particle> &particles)
// {
//      particles = particles_;
//      return 0;
// }
