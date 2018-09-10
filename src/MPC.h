#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

#define X_IDX     (0U)
#define Y_IDX     (1U)
#define PSI_IDX   (2U)
#define V_IDX     (3U)
#define CTE_IDX   (4U)
#define EPSI_IDX  (5U)
#define A_IDX     (6U)
#define DELTA_IDX (7U)

#define STATE_CNT (EPSI_IDX + 1U)
#define ACTUT_CNT (DELTA_IDX - STATE_CNT + 1U)

class MPC {
 public:
  MPC();

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
