#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/version.hpp>
#include <vector>
#include <algorithm>

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

    //NOTE: using accumulators feature max and min
    accumulator_set<double, boost::accumulators::features<tag::min, tag::max>> acc_test2;   
    acc_test2(1.0);
    acc_test2(2.0);
    acc_test2(3.0);
    cout << "acc_test2 max=" << boost::accumulators::max(acc_test2) << " " << "acc_test2 min=" << boost::accumulators::min(acc_test2) << endl;

    //NOTE: using vector to store the data and accumulate the data
    std::vector<double> data={1.0, 2.0, 3.0, 4.0, 5.0};
    accumulator_set<double, features<tag::mean, tag::max>> acc_test3;
    //NOTE: std::for_each is a function in algorithm header file
    acc_test3 = std::for_each(data.begin(), data.end(), acc_test3);
    cout << "acc_test3 mean=" << boost::accumulators::mean(acc_test3) << " " << "acc_test3 max=" << boost::accumulators::max(acc_test3) << endl;

    //NOTE: Another way to extract the result from an accumulator_set
    cout << "acc_test3 mean=" << boost::accumulators::extract_result<tag::mean>(acc_test3) << " " << "acc_test3 max=" << boost::accumulators::extract_result<tag::max>(acc_test3) << endl;

    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
    
    cout << "Boost version:" << BOOST_VERSION << endl;

    return 0;
}
