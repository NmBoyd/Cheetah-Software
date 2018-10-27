#ifndef PROJECT_DYNAMICSSIMULATOR_H
#define PROJECT_DYNAMICSSIMULATOR_H

#include "orientation_tools.h"
#include "FloatingBaseModel.h"
#include "spatial.h"

using namespace ori;
using namespace spatial;


/*!
 * Type of the list of forces to apply to bodies.
 */
template<typename T>
using ForceList = typename std::vector<SVec<T>>;

/*!
 * Class (containing state) for dynamics simulation of a floating-base system
 */
template<typename T>
class DynamicsSimulator {
public:
  DynamicsSimulator(FloatingBaseModel<T>& model); //! Initialize simulator with given model
  void step(T dt, const DVec<T>& tau); //! Simulate forward one step
  void runABA(const DVec<T>& tau); //! Find _dstate with the articulated body algorithm

  /*!
   * Set the state of the robot being simulated
   */
  void setState(const FBModelState<T>& state) {
    _state = state;
  }

  /*!
   * Get the state of the robot
   * @return
   */
  const FBModelState<T>& getState() const {
    return _state;
  }

  /*!
   * Get the most recently calculated state derivative (updated by runABA)
   * @return
   */
  const FBModelStateDerivative<T>& getDState() const {
    return _dstate;
  }

  /*!
   * Add external forces. These are added on top of the ground reaction forces
   * The i-th force is the spatial force applied to body i.
   */
  void setAllExternalForces(const ForceList<T>& forces) {
    _externalForces = forces;
  }

  /*!
   * Reset any external forces
   */
  void resetExternalForces() {
    for(size_t i = 0; i < _nb; i++) {
      _externalForces[i] = SVec<T>::Zero();
    }
  }

private:
  void updateCollisions(); //! Update ground collision list
  void updateGroundForces(); //! Compute ground reaction forces

  void integrate(T dt); //! Integrate to find new _state

  FBModelState<T> _state;
  FBModelStateDerivative<T> _dstate;

  // aba stuff
  vector<Mat6<T>, Eigen::aligned_allocator<Mat6<T>>> _Xup, _Xuprot, _IA, _Xa;
  vector<SVec<T>, Eigen::aligned_allocator<SVec<T>>> _v, _vrot, _a, _c, _crot, _U, _Urot, _Utot, _S, _Srot, _pA, _pArot;
  vector<T> _d, _u;

  FloatingBaseModel<T>& _model;
  size_t _nb;


  ForceList<T> _externalForces;
};


#endif //PROJECT_DYNAMICSSIMULATOR_H
