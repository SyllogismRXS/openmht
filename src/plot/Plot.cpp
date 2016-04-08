#include <iostream>
#include <fstream>
#include <string>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <map>

#include <openmht/plot/gnuplot-iostream.h>
#include <openmht/plot/Plot.h>

#include <boost/make_shared.hpp>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using std::cout;
using std::endl;

namespace openmht
{
     Plot::Plot()
     {          
          gp_ = boost::make_shared<Gnuplot>();
     }

     //void Plot::plot_frames(std::list<swarm_proto::Frame> &frames, int divide, bool enable_3d)
     //{
     //     int count = 0;
     //     std::map<int,std::list<swarm_proto::Vector3d> > tracks;
     //     for (std::list<swarm_proto::Frame>::iterator it = frames.begin();
     //          it != frames.end(); it++, count++) {
     //                         
     //          if (count % divide == 0) {               
     //               for (int i = 0; i < it->contact_size(); i++) {
     //                    swarm_proto::Vector3d pos;
     //                    pos.set_x(it->contact(i).state().position().x());
     //                    pos.set_y(it->contact(i).state().position().y());
     //                    pos.set_z(it->contact(i).state().position().z());
     //
     //                    tracks[it->contact(i).id().id()].push_back(pos);
     //               }               
     //          }
     //     }
     //
     //     // Convert map into list
     //     std::list< std::list<swarm_proto::Vector3d> > lists;
     //     std::list<std::string> labels;
     //     std::list<std::string> styles;          
     //     
     //     for(std::map<int,std::list<swarm_proto::Vector3d> >::iterator it = tracks.begin();
     //         it != tracks.end(); it++) {
     //          lists.push_back(it->second);
     //          labels.push_back(swarm::int2str(it->first));
     //          styles.push_back("linespoints");
     //     }
     //
     //     std::string title = "Swarm Tracks";
     //     std::list<std::string> objects;
     //     
     //     std::string options = "";                    
     //     //options += "set size ratio -1\n";
     //     //options += "set view equal xy\n";
     //     //options += "set size 1,1\n";
     //
     //     options += "set xlabel \"X\"\n";
     //     options += "set ylabel \"Y\"\n";
     //     options += "set ticslevel 0\n";
     //     options += "set key outside\n";
     //     options += "set grid xtics ytics\n";
     //
     //     this->plot(lists, title, labels, styles, options, objects, enable_3d);
     //}
     //
     void Plot::plot(std::list< std::map<int, std::list<Eigen::Vector2d> > > &lists,
                     const std::string &title, 
                     std::list<std::string> &labels,
                     std::list<std::string> &styles,
                     std::string options,
                     std::list<std::string> &objects,
                     bool enable_3d)
     {
          (*gp_) << "reset\n";
          (*gp_) << "set title '" << title << "'\n";          
          
          if (options != "") {
               (*gp_) << options;
          }          
          
          // Draw objects
          for(std::list<std::string>::iterator it = objects.begin(); 
              it != objects.end(); it++) {
               (*gp_) << *it << endl;               
          }
          
          if (enable_3d) {
               (*gp_) << "splot";
          } else {
               (*gp_) << "plot";
          }
          
          std::list<std::string>::iterator it_styles = styles.begin();
          std::list<std::string>::iterator it_labels = labels.begin();
          for (std::list< std::map<int, std::list<Eigen::Vector2d> > >::iterator it = lists.begin(); it != lists.end(); it++) {
               for (std::map<int, std::list<Eigen::Vector2d> >::iterator it_map = it->begin(); it_map != it->end(); it_map++) {
                    
                    std::list<double> xLocs;
                    std::list<double> yLocs;
                    std::list<double> zLocs;
                    
                    std::list<Eigen::Vector2d>::iterator it2;
                    for (it2 = it_map->second.begin() ; it2 != it_map->second.end() ; it2++) {
                         xLocs.push_back((*it2)(0,0));
                         yLocs.push_back((*it2)(1,0));
                         zLocs.push_back(0);
                    } 
               
                    if (enable_3d) {
                         (*gp_) << (*gp_).file1d(std::make_tuple(xLocs,yLocs,zLocs));
                    } else {
                         (*gp_) << (*gp_).file1d(std::make_pair(xLocs,yLocs));
                    }
                    (*gp_) << "with " << *it_styles  << " title '" << it_map->first << "-" << *it_labels << "'";

                    if (++it_map != it->end()) {
                         (*gp_) << ",";
                    }
                    --it_map;
               }    
               if (++it != lists.end()) {
                    (*gp_) << ",";
               }
               --it;
               
               it_styles++;
               it_labels++;
          }         
          it_styles = styles.begin();
          it_labels = labels.begin();
               
          (*gp_) << endl;
     }

     void Plot::wait() 
     {
          cout << "Hit any key to continue." << endl;
          while(kbhit() == 0);
     }

     int Plot::kbhit()
     {
          struct termios oldt, newt;
          int ch;
          int oldf;

          tcgetattr(STDIN_FILENO, &oldt);
          newt = oldt;
          newt.c_lflag &= ~(ICANON | ECHO);
          tcsetattr(STDIN_FILENO, TCSANOW, &newt);
          oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
          fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

          ch = getchar();

          tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
          fcntl(STDIN_FILENO, F_SETFL, oldf);

          if(ch != EOF)
          {
               ungetc(ch, stdin);
               return 1;
          }

          return 0;
     }
    
     void Plot::gnuplot_test()
     {
          //Gnuplot gp;
          Gnuplot gp("gnuplot -persist");
          // Create a script which can be manually fed into gnuplot later:
          //    Gnuplot gp(">script.gp");
          // Create script and also feed to gnuplot:
          //    Gnuplot gp("tee plot.gp | gnuplot -persist");
          // Or choose any of those options at runtime by setting the GNUPLOT_IOSTREAM_CMD
          // environment variable.

          // Gnuplot lists (i.e. arrows) require four columns: (x,y,dx,dy)
          std::list<boost::tuple<double, double, double, double> > pts_A;

          // You can also use a separate container for each column, like so:
          std::list<double> pts_B_x;
          std::list<double> pts_B_y;
          std::list<double> pts_B_dx;
          std::list<double> pts_B_dy;

          // You could also use:
          //   std::list<std::list<double> >
          //   boost::tuple of four std::list's
          //   std::list of std::tuple (if you have C++11)
          //   arma::mat (with the Armadillo library)
          //   blitz::Array<blitz::TinyList<double, 4>, 1> (with the Blitz++ library)
          // ... or anything of that sort

          for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
               double theta = alpha*2.0*3.14159;
               pts_A.push_back(boost::make_tuple(
                                    cos(theta),
                                    sin(theta),
                                    -cos(theta)*0.1,
                                    -sin(theta)*0.1
                                    ));

               pts_B_x .push_back( cos(theta)*0.8);
               pts_B_y .push_back( sin(theta)*0.8);
               pts_B_dx.push_back( sin(theta)*0.1);
               pts_B_dy.push_back(-cos(theta)*0.1);
          }

          // Don't forget to put "\n" at the end of each line!
          gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
          // '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
          gp << "plot '-' with vectors title 'pts_A', '-' with vectors title 'pts_B'\n";
          gp.send1d(pts_A);
          gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));          
     }     
}
