#ifndef PLOT_H_
#define PLOT_H_

#include <vector>
#include <list>
#include <map>
#include <openmht/plot/gnuplot-iostream.h>
#include <boost/shared_ptr.hpp>
#include <Eigen/Dense>

namespace openmht
{
     class Plot {
     public:
          Plot();
                    
          static void gnuplot_test();

          //void plot_frames(std::list<swarm_proto::Frame> &frames, int divide, bool enable_3d);
          
          void plot(std::list< std::map<int, std::list<Eigen::Vector2d> > > &lists, 
                    const std::string &title, 
                    std::list<std::string> &labels,
                    std::list<std::string> &styles,
                    std::string options,
                    std::list<std::string> &objects,
                    bool enable_3d);

          void wait();
          int kbhit();

     private:
          boost::shared_ptr<Gnuplot> gp_;          
     };
}

#endif
