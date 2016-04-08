#ifndef ELLIPSE_H_
#define ELLIPSE_H_
/// ---------------------------------------------------------------------------
/// @file Ellipse.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2016-04-08 11:24:21 syllogismrxs>
///
/// @version 1.0
/// Created: 02 Dec 2015
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
/// The Ellipse class ...
/// 
/// ---------------------------------------------------------------------------
#include <Eigen/Dense>

class Ellipse {
public:
     Ellipse() :
     center_(Eigen::Vector2d(0,0)), axes_(Eigen::Vector2d(1,1)), angle_(0)
     {}
     
     Ellipse(Eigen::Vector2d center, Eigen::Vector2d axes, double angle) :
          center_(center), axes_(axes), angle_(angle) 
     {}
     
     Eigen::Vector2d center() { return center_; }

     // Stores half the minor / major axes size due to cv::ellipse function
     Eigen::Vector2d axes() { return axes_; }
     double angle() { return angle_; }

protected:
     Eigen::Vector2d center_;
     Eigen::Vector2d axes_;
     double angle_;
     
private:     
};

#endif
