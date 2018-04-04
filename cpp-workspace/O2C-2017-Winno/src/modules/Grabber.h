/*
 * Grabber.h
 */


#ifndef GRABBER_H_
#define GRABBER_H_

class Grabber : public Module {
	 void OperatorControl(){
			bool grab = hw::stick->GetRawButton(1); // Trigger
			bool eject  = hw::stick->GetRawButton(2); // Button on the side of the joystick (whatever it's called, the one you press with your thumb)

			if(grab){
				hw::lgrVic->Set(-.7);		//rotate motors to grab cube (left)
				hw::rgrVic->Set(-.7);		//rotate motors to grab cube (right)
			} else if(eject){
					hw::lgrVic->Set(.7); //rotate motors opposite direction to eject cube (left)
					hw::rgrVic->Set(.7); //rotate motors opposite direction to eject cube (right)
			} else{
				hw::lgrVic->Set(0);		//No motion (left)
				hw::rgrVic->Set(0);		//No motion (right)
			}
	}

	void Autonomous(){
		if(DriveTrainPrivate::spit){
			hw::lgrVic->Set(1.0);		//rotate motors to grab cube (left)
			hw::rgrVic->Set(1.0);		//rotate motors to grab cube (right)
		} else{
			if(!DriveTrainPrivate::cubeGrabbed){
				hw::lgrVic->Set(-.7);		//rotate motors to grab cube (left)
				hw::rgrVic->Set(-.7);		//rotate motors to grab cube (right)
			} else{
				hw::lgrVic->Set(0.0);		//rotate motors to grab cube (left)
				hw::rgrVic->Set(0.0);		//rotate motors to grab cube (right)
			}
		}
	}
};

#endif /* GRABBER_H_ */



