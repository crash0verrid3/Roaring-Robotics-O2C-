/*
 * Bucket.h
 */


#ifndef BUCKET_H_
#define BUCKET_H_

class Bucket : public Module {
	 void OperatorControl(){
		 if(isDebugMode()){

			 return;
		 }
#ifdef CONTROLLER_ALT_1
			bool rightTrigger = hw::stick->GetRawButton(6);
			bool rightBumper  = hw::stick->GetRawButton(4);
			bool grab = hw::stick->GetRawButton(1);			//Change these buttons later!!
			bool eject  = hw::stick->GetRawButton(2);

			bool top = hw::topBkInput->Get();
			bool bot = hw::botBkInput->Get();
#else
			bool rightTrigger = hw::stick->GetRawButton(8);
			bool rightBumper  = hw::stick->GetRawButton(6);
#endif

			// Buttons to control the upwards and downwards motion of the cube lift
			if(rightBumper){
				if (!top)
					hw::bkTalon->Set(.7);		//upwards motion of cube lift
			} else if(rightTrigger){
				if (!bot)
					hw::bkTalon->Set(-.7); //downwards motion of cube lift
			} else{
				hw::bkTalon->Set(0);		//No motion
			}

			if(grab){
				hw::lgrTalon->Set(.7);		//rotate motors to grab cube (left)
				hw::rgrTalon->Set(.7);		//rotate motors to grab cube (right)
			} else if(eject){
					hw::lgrTalon->Set(-.7); //rotate motors opposite direction to eject cube (left)
					hw::rgrTalon->Set(-.7); //rotate motors opposite direction to eject cube (right)
			} else{
				hw::lgrTalon->Set(0);		//No motion (left)
				hw::rgrTalon->Set(0);		//No motion (right)
			}
	}

	void Autonomous(){



	}

};

#endif /* BUCKET_H_ */



