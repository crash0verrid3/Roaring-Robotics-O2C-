/*
 * Cubelift.h
 */


#ifndef CUBELIFT_H_
#define CUBELIFT_H_

class Cubelift : public Module {
private:
	double encoderHeight;
	bool hasBeenMoved = false;
	double correct_up_power = .35;
	double correct_down_power = 0.0;
	double correct_accept_range = 0;
	bool a = false;
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
				if (!top){
					hw::actualTalon->Set(ControlMode::PercentOutput, .8);		//upwards motion of cube lift
					hasBeenMoved = true;
					a = false;
				}
			} else if(down){
				if (!bot){
					hw::actualTalon->Set(ControlMode::PercentOutput, -.5); //downwards motion of cube lift
					hasBeenMoved = true;
					a = false;
				}
			} else{
				hw::actualTalon->Set(ControlMode::PercentOutput, 0);		//No motion
			}
			if(hasBeenMoved && !(top || bot)){ // Test whether the correction code should kick in
				if(!a){ // `a` becomes false when the lift is moved, but becomes true when the lift is released. This tells it not to change the saved `encoderHeight` when the lift isn't supposed to be moving
					encoderHeight = quadPos; // Sets `encoderHeight` to the proper value to keep the lift at the right height
					a = true; // Makes sure that `encoderHeight` isn't changed while it's correcting the height
				}
				if(fabs(quadPos - encoderHeight) < correct_accept_range){ // The lift is perfectly located
					hw::actualTalon->Set(ControlMode::PercentOutput, 0);		//No motion
				} else if(quadPos > encoderHeight){ // Move the lift up; the lift is below the proper height
					hw::actualTalon->Set(ControlMode::PercentOutput, correct_up_power);
				} else if(quadPos < encoderHeight){ // Move the lift down; the lift is above the proper height
					hw::actualTalon->Set(ControlMode::PercentOutput, correct_down_power);
				} else{
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



