/*
 * Randomized tester demonstration.
 * 
 * Member functions not having to
 * return anything are programmed to
 * return "*this" through a reference,
 * so the invocation syntax below is
 * possible.
 * 
 * The object is able to reset and
 * start all over again.
 * 
 * Calls each registered function
 * for each of the random integer
 * pairs in the ensemble, and records
 * success and failure events, reporting
 * at the end. The return values of the
 * 1st C function registered are treated
 * as the golden reference.
 * */

/*
 * Worked on this code on
 *   Dec 22-23, 2022 / Thu-Fri
 * */

#include "updaters_testing.hh"

int
main (void)
{
  using namespace std;
  using namespace updaters_testing;
  
  UpdaterFunctionsRandomizedTester
    obj_test;
  
  obj_test
    .reset()
    .set_ensemble_volume(10)
    .set_interval_limits(-5 , 5)
    .run_randomized_test()
    .report_results();
  
  obj_test
    .reset()
    .set_ensemble_volume(10000)
    .set_interval_limits(-50 , 50)
    .run_randomized_test()
    .report_results();
  
  return 0;
}