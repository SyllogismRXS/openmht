#include <iostream>
#include <stdio.h>

#include <Eigen/Dense>

#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

using namespace boost::numeric;

using std::cout;
using std::endl;

#include "KalmanFilter.h"

namespace openmht {

     KalmanFilter::KalmanFilter()
     {
     }

     KalmanFilter::KalmanFilter(const Eigen::MatrixXf &F, 
				const Eigen::MatrixXf &B, 
				const Eigen::MatrixXf &H, 
				const Eigen::MatrixXf &Q, 
				const Eigen::MatrixXf &R)
     {
	  setModel(F, B, H, Q, R);
     }

     int KalmanFilter::setModel(const Eigen::MatrixXf &F, 
				const Eigen::MatrixXf &B, 
				const Eigen::MatrixXf &H, 
				const Eigen::MatrixXf &Q, 
				const Eigen::MatrixXf &R)
     {
	  F_ = F;
	  B_ = B;
	  H_ = H;
          Q_ = Q;
          R_ = R;
	  eye_ = Eigen::MatrixXf::Identity(F.rows(), F.cols());

	  return 0;
     }

     int KalmanFilter::init(const Eigen::MatrixXf &x0, 
			    const Eigen::MatrixXf &P0)
     {
	  x_ = x0;
	  P_ = P0;
	  return 0;
     }

     int KalmanFilter::predict(const Eigen::MatrixXf &u)
     {
          x_ = F_*x_ + B_*u;
          P_ = F_*P_*F_.transpose() + Q_;              
          
	  return 0;
     }
     
     int KalmanFilter::update(const Eigen::MatrixXf &z)
     {                    
	  K_ = P_*H_.transpose()*(H_*P_*H_.transpose() + R_).inverse();
	  x_ = x_ + K_*(z - H_*x_);
          P_ = (eye_ - K_*H_)*P_;
	  return 0;
     }
     
     Eigen::MatrixXf KalmanFilter::state() const
     {
	  return x_;
     }

     void KalmanFilter::set_state(const Eigen::MatrixXf &x)
     {
          x_ = x;
     }
     
     Eigen::MatrixXf KalmanFilter::covariance() const
     {
	  return P_;
     }

     Ellipse KalmanFilter::error_ellipse(double confidence)
     {
          if (confidence < 0) {
               confidence = 0;
          } else if (confidence > 1) {
               confidence = 1;
          }
          
          // Compute the eigenvectors and eigenvalues of the measurement
          // covariance matrix
          Eigen::MatrixXf B = this->meas_covariance();          
          Eigen::EigenSolver<Eigen::MatrixXf> es(B);
          Eigen::EigenSolver< Eigen::MatrixXf >::EigenvectorsType evecs = es.eigenvectors();
          Eigen::EigenSolver< Eigen::MatrixXf >::EigenvectorsType evalues = es.eigenvalues();
          
          // Find the larger (1st) eigenvalue / eigenvector
          double eig0 = evalues(0).real();
          double eig1 = evalues(1).real();

          double lambda0, lambda1;
          int eig_1st_index;
          if (eig0 >= eig1) {
               eig_1st_index = 0;
               lambda0 = eig0;
               lambda1 = eig1;
          } else {
               eig_1st_index = 1;
               lambda0 = eig1;
               lambda1 = eig0;
          }
          
          // Determine the angle of the ellipse
          double q0x = evecs.col(eig_1st_index)(0).real();
          double q0y = evecs.col(eig_1st_index)(1).real();
          double angle = 180.0/3.14159265359 * atan2(q0y,q0x);                 
          
          double p = confidence; // 0.0 - 1.0

          // The major and minor axes of the ellipse are stored as "half" of
          // the major axes because cv::ellipse accepts half sizes for input
          double r0 = sqrt(-2.0*log(1.0-p/1.00)*lambda0) / 2.0;
          double r1 = sqrt(-2.0*log(1.0-p/1.00)*lambda1) / 2.0;
          
          Eigen::Vector2d center(x_(0,0),x_(1,0));
          //cv::Point2d center(160,120);
          return Ellipse(center, Eigen::Vector2d(r0,r1), angle);
     }

     bool KalmanFilter::is_within_region(Eigen::MatrixXf Zm, double std) 
     {
          Eigen::MatrixXf B = this->meas_covariance();
          Eigen::MatrixXf diff = Zm - H_*x_;
          Eigen::MatrixXf dist_mat = diff.transpose()*B.inverse()*diff;          
          double dist = dist_mat(0,0);
          //if (dist <= pow(nsigma,2)) {
          if (dist <= std) {
               return true;
          } else {
               return false;
          }
     }

     Eigen::MatrixXf KalmanFilter::meas_covariance()
     {          
          return H_ * P_ * H_.transpose() + R_;
     }

     void KalmanFilter::print()
     {
          cout << "State: " << endl << x_ << endl;
          cout << "Covar: " << endl << P_ << endl;
          cout << "R: " << endl << R_ << endl;
     }
}

