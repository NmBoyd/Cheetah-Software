/*============================= Recovery Stand ==============================*/
/**
 * Transitionary state that is called for the robot to stand up into
 * balance control mode.
 */

#include "FSM_State_BackFlip.h"
#include <Utilities/Utilities_print.h>
#include <ParamHandler/ParamHandler.hpp>


/**
 * Constructor for the FSM State that passes in state specific info to
 * the generic FSM State constructor.
 *
 * @param _controlFSMData holds all of the relevant control data
 */
template <typename T>
FSM_State_BackFlip<T>::FSM_State_BackFlip(ControlFSMData<T>* _controlFSMData)
    : FSM_State<T>(_controlFSMData, FSM_StateName::STAND_UP, "STAND_UP"){
  // Do nothing
  // Set the pre controls safety checks
  this->checkSafeOrientation = false;

  // Post control safety checks
  this->checkPDesFoot = false;
  this->checkForceFeedForward = false;

  zero_vec3.setZero();
  f_ff << 0.f, 0.f, -25.f;



  // From BackFlip Test Constructor
  _data_reader = new DataReader(this->_data->_quadruped->_robotType);

  backflip_ctrl_ = new BackFlipCtrl<T>(_controlFSMData->_quadruped->buildModel(), _data_reader, this->_data->controlParameters->controller_dt);

  if (this->_data->_quadruped->_robotType == RobotType::CHEETAH_3)
    backflip_ctrl_->SetTestParameter("user/WBC_Controller/config/TEST_backflip_cheetah3.yaml");
  else if (this->_data->_quadruped->_robotType == RobotType::MINI_CHEETAH)
    backflip_ctrl_->SetTestParameter("user/WBC_Controller/config/TEST_backflip_mini_cheetah.yaml");
  else {
    printf("[Body Ctrl Test] Invalid robot type\n");
  }

}


template <typename T>
void FSM_State_BackFlip<T>::onEnter() {
  // Default is to not transition
  this->nextStateName = this->stateName;

  // Reset the transition data
  this->transitionData.zero();

  // Reset iteration counter
  iter = 0;
  _state_iter = 0;
  
  // initial configuration, position
  for(size_t i(0); i < 4; ++i) {
    initial_jpos[i] = this->_data->_legController->datas[i].q;
  }

  _motion_start_iter = 0;
}

/**
 * Calls the functions to be executed on each control loop iteration.
 */
template <typename T>
void FSM_State_BackFlip<T>::run() {
  // Set the desired joint positions for the robot before jumping (not sure about this)
  for (int leg = 0; leg < 4; ++leg) {
    jpos[3 * leg] = 0.0;
    jpos[3 * leg + 1] = -0.8;
    jpos[3 *leg + 2] = 1.64;
  }

// Command Computation
  if (_b_running) {
    if (!_Initialization()) {
      ComputeCommand();
    }
  } else {
    //_SafeCommand(data, command); - need to add
  }

  // Note: not sure what to do after robot lands...

  ++_count;
  _curr_time += this->_data->controlParameters->controller_dt;

}


template <typename T>
bool FSM_State_BackFlip<T>::_Initialization() {
  static bool test_initialized(false);
  if (!test_initialized) {
    //_TestInitialization();
    backflip_ctrl_->CtrlInitialization("CTRL_backflip");
    test_initialized = true;
    printf("[Cheetah Test] Test initialization is done\n");
  }
  if (_count < _waiting_count) {
    for (int leg = 0; leg < 4; ++leg) {
      for (int jidx = 0; jidx < 3; ++jidx) {
        this->_data->_legController->commands[leg].tauFeedForward[jidx] = 0.;
        this->_data->_legController->commands[leg].qDes[jidx] = jpos[3 * leg + jidx];
        this->_data->_legController->commands[leg].qdDes[jidx] = 0.;
        this->_data->_legController->commands[leg].kpJoint(jidx,jidx) = 20.; // get from control parameters?
        this->_data->_legController->commands[leg].kdJoint(jidx,jidx) = 2.;
      }
    }
    return true;
  }
  
  return false;
}

template <typename T>
void FSM_State_BackFlip<T>::ComputeCommand() {
  if (_b_first_visit) {
    backflip_ctrl_->FirstVisit(_curr_time);
    _b_first_visit = false;
  }

  backflip_ctrl_->OneStep(_curr_time, this->_data->_legController->commands);

  if (backflip_ctrl_->EndOfPhase(this->_data->_legController->datas)) {
    backflip_ctrl_->LastVisit();
    _b_first_visit = true;
  }
}


template <typename T>
void FSM_State_BackFlip<T>::_SetJPosInterPts(
    const size_t & curr_iter, size_t max_iter, int leg, 
    const Vec3<T> & ini, const Vec3<T> & fin){

    float a(0.f);
    float b(1.f);

    // if we're done interpolating
    if(curr_iter <= max_iter) {
      b = (float)curr_iter/(float)max_iter;
      a = 1.f - b;
    }

    // compute setpoints
    Vec3<T> inter_pos = a * ini + b * fin;

    // do control
    this->jointPDControl(leg, inter_pos, zero_vec3);

    //if(curr_iter == 0){ 
      //printf("flag:%d, curr iter: %lu, state iter: %llu, motion start iter: %d\n", 
        //_flag, curr_iter, _state_iter, _motion_start_iter); 
      //printf("inter pos: %f, %f, %f\n", inter_pos[0], inter_pos[1], inter_pos[2]);
    //}
    //if(curr_iter == max_iter){ 
      //printf("flag:%d, curr iter: %lu, state iter: %llu, motion start iter: %d\n", 
        //_flag, curr_iter, _state_iter, _motion_start_iter); 
      //printf("inter pos: %f, %f, %f\n", inter_pos[0], inter_pos[1], inter_pos[2]);
    //}
}

/**
 * Manages which states can be transitioned into either by the user
 * commands or state event triggers.
 *
 * @return the enumerated FSM state name to transition into
 */
template <typename T>
FSM_StateName FSM_State_BackFlip<T>::checkTransition() {
  this->nextStateName = this->stateName;
  iter++;

  // Switch FSM control mode
  switch ((int)this->_data->controlParameters->control_mode) {
    case K_BACKFLIP:
      break;

    case K_RECOVERY_STAND:
      this->nextStateName = FSM_StateName::RECOVERY_STAND;
      break;

    case K_LOCOMOTION:
      this->nextStateName = FSM_StateName::LOCOMOTION;
      break;

    case K_BOUNDING:
      this->nextStateName = FSM_StateName::BOUNDING;
      break;


    case K_PASSIVE:  // normal c
      this->nextStateName = FSM_StateName::PASSIVE;
      break;

    case K_BALANCE_STAND: 
      this->nextStateName = FSM_StateName::BALANCE_STAND;
      break;

    default:
      std::cout << "[CONTROL FSM] Bad Request: Cannot transition from "
                << K_BACKFLIP << " to "
                << this->_data->controlParameters->control_mode << std::endl;
  }

  // Get the next state
  return this->nextStateName;
}

/**
 * Handles the actual transition for the robot between states.
 * Returns true when the transition is completed.
 *
 * @return true if transition is complete
 */
template <typename T>
TransitionData<T> FSM_State_BackFlip<T>::transition() {
  // Finish Transition
  switch (this->nextStateName) {
    case FSM_StateName::PASSIVE:  // normal
      this->transitionData.done = true;
      break;

    case FSM_StateName::BALANCE_STAND:
      this->transitionData.done = true;
      break;

    case FSM_StateName::LOCOMOTION:
      this->transitionData.done = true;
      break;

    case FSM_StateName::BOUNDING:
      this->transitionData.done = true;
      break;

    case FSM_StateName::RECOVERY_STAND:
      this->transitionData.done = true;
      break;


    default:
      std::cout << "[CONTROL FSM] Something went wrong in transition"
                << std::endl;
  }

  // Return the transition data to the FSM
  return this->transitionData;
}

/**
 * Cleans up the state information on exiting the state.
 */
template <typename T>
void FSM_State_BackFlip<T>::onExit() {
  // Nothing to clean up when exiting
}

// template class FSM_State_BackFlip<double>;
template class FSM_State_BackFlip<float>;
