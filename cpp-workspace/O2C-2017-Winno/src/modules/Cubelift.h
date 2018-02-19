/*
 * Cubelift.h
 */


#ifndef CUBELIFT_H_
#define CUBELIFT_H_

class Cubelift : public Module {
private:
	double encoderHeight;
	bool hasBeenMoved = false;
	double correct_up_power = .5;
	double correct_down_power = .3;
	double correct_accept_range = 0;
public:
	 void OperatorControl(){
		 if(isDebugMode()){

			 return;
		 }
#ifdef CONTROLLER_ALT_1
			bool up = hw::stick->GetRawButton(6);
			bool down  = hw::stick->GetRawButton(4);

			bool top =false; hw::topBkInput->Get();
			bool bot =false; hw::botBkInput->Get();
#else
			bool up = hw::stick->GetRawButton(8);
			bool down  = hw::stick->GetRawButton(6);
#endif
			double quadPos = hw::actualTalon->GetSensorCollection().GetQuadraturePosition();
			// Buttons to control the upwards and downwards motion of the cube lift
			if(up){
				if (!top)
					hw::actualTalon->Set(ControlMode::PercentOutput, .7);		//upwards motion of cube lift
			} else if(down){
				if (!bot)
					hw::actualTalon->Set(ControlMode::PercentOutput, -.5); //downwards motion of cube lift
			} else{
				if(fabs(quadPos - encoderHeight) < correct_accept_range){
					hw::actualTalon->Set(ControlMode::PercentOutput, 0);		//No motion
				} else if(quadPos > encoderHeight){
					hw::actualTalon->Set(ControlMode::PercentOutput, correct_up_power);
				} else if(quadPos < encoderHeight){
					hw::actualTalon->Set(ControlMode::PercentOutput, correct_down_power);
				}
			}

			SmartDashboard::PutNumber("Talon Encoder (Port 1)", quadPos);

	}

	void Autonomous(){



	}

	void ModuleInit(){

	}
};

#endif /* BUCKET_H_ */



