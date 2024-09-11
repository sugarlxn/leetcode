#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/version.hpp>


using namespace boost::accumulators;
using namespace std;

int main(int argc, char * argv[]){
    // define an accumulator set for calculating the mean and the 2nd moment
    // 2nd moment

    accumulator_set<double, stats<tag::mean, tag::moment<2>>> acc;
    //push in some data
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    //display the results
    cout << "Mean: " << mean(acc) << endl;
    cout << "Moment" << moment<2>(acc) << endl;

    //accumulator fectrue
    accumulator_set<double, features<tag::mean>> acc_feature;
    // add the features of tag::min
    //accumulator_set<double, features<tag::min, tag::mean>> acc_features;
    acc_feature(1.0);
    acc_feature(3.0);
    acc_feature(2.0);

    cout << "acc_feature mean = " << mean(acc_feature) << endl;

    //NOTE: using the max and min feature, boost::accumulators::max and boost::accumulators::min
    accumulator_set<int, stats<tag::max, tag::min>> acc_test;
    acc_test(1);
    acc_test(2);
    cout << "acc_test max=" << boost::accumulators::max(acc_test) << " " << "acc_test min=" << boost::accumulators::min(acc_test) << endl;


    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
    
    cout << "Boost version:" << BOOST_VERSION << endl;

    return 0;
}
