/*
 * Balls.h
 *
 *  Created on: Jul 15, 2017
 *      Author: cryog
 */

#ifndef BALLS_H_
#define BALLS_H_


class Balls : public Module {
private:
	bool activationState = false;
	bool activationTicks = 0;
public:
	void OperatorControl(){
		bool shootBtn = hw::stick->GetRawButton(3);
		bool shootBtn2 = hw::stick->GetRawButton(1);
		if(shootBtn){
			hw::pneurelay->Set(hw::pneurelay->Value::kReverse);
		} else if(shootBtn2){
			hw::pneurelay->Set(hw::pneurelay->Value::kForward);
		} else{
			hw::pneurelay->Set(hw::pneurelay->Value::kOff);
		}
	}
};
#endif /* BALLS_H_ */
