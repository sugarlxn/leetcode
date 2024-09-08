#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

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

    return 0;
}
