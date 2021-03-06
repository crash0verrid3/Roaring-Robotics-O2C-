/*
 * Climber.h
 *
 *  Created on: Feb 10, 2018
 *      Author: epeterson
 */

#ifndef SRC_MODULES_CLIMBER_H_
#define SRC_MODULES_CLIMBER_H_

class Climber : public Module {
public:
	void OperatorControl(){
		bool winch1 = hw::stick->GetRawButton(8); // Right side of the robot
		bool winch2 = hw::stick->GetRawButton(7); // Left side of the robot
		isLifting = winch1 || winch2; // If either of them are pressed, then isLifting = true

		if(winch1){
			hw::winchVictor1->Set((fmax(0, hw::stick->GetX()) + 3.0) / 4.0);		//Activate winch. The power is between 0.75 and 1.0, relative to where the joystick is on the x-axis
		} else{
			hw::winchVictor1->Set(0);		//Turn off winch
		}
		if(winch2){
			hw::winchVictor2->Set((fmin(0, hw::stick->GetX()) - 3.0) / 4.0);
		} else{
			hw::winchVictor2->Set(0);
		}
	}
};




#endif /* SRC_MODULES_CLIMBER_H_ */
