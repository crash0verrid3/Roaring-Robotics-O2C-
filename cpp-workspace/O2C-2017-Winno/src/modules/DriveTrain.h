/*
 * DriveTrain.h
 *
 *  Created on: Jun 26, 2017
 *      Author: cryog
 */

#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_


#define MAX_SPEED_FACTOR .95

// Per-controller defines

// Standard (Logitech Dual Action) Controllers
	/* Nothing here yet */
// Type 1 controllers (Logitech Extreme 3D Pro)
#define TYPE_1_CONTROLLER_ROT_DEGREES 25


//

namespace DriveTrainPrivate{
	double maxCorrectPerTick = 50.0;
	double speedFactor = 0.01;
	double minSpeed = .2;
	int speedControl = 0;
	bool lSpeedBtn;
	double avgSpeed;
	double flTi = 1.0;
	double frTi = 1.0;
	double rlTi = 1.0;
	double rrTi = 1.0;
	int ticksSpeed = 1;
	int ticksModTicksSpeed = 0;
	double flDev = 1.0;
	double frDev = 1.0;
	double rlDev = 1.0;
	double rrDev = 1.0;
	int lFl = 0;
	int lFr = 0;
	int lRl = 0;
	int lRr = 0;
	double avgSpd;
	double gflTi;
	double gfrTi;
	double grlTi;
	double grrTi;
}
class DriveTrain : public Module { // The code that drives the robot
public:
	void OperatorControl(){
		double leftAxisX = hw::stick->GetX(); // Gets the left joystick's left<->right movement (from 0.0 to 1.0)
		double leftAxisY = hw::stick->GetY(); // Same thing, with its up<->down movement
		double rightAxisZ = hw::stick->GetZ(); // Now get the right Joystick's left<->right movement

		drive(leftAxisX, leftAxisY, rightAxisZ, false);
	}
	static void drive(double leftAxisX, double leftAxisY, double rightAxisZ, bool correctOverride){
		if(DriveTrainPrivate::ticksModTicksSpeed == 0){
			int iflTi = hw::flE->Get();
			int ifrTi = hw::frE->Get();
			int irlTi = hw::rlE->Get();
			int irrTi = hw::rrE->Get();
			hw::flE->Reset();
			hw::frE->Reset();
			hw::rlE->Reset();
			hw::rrE->Reset();
			/*
			DriveTrainPrivate::lFl = iflTi;
			DriveTrainPrivate::lFr = ifrTi;
			DriveTrainPrivate::lRl = irlTi;
			DriveTrainPrivate::lRr = irrTi;
			*/
			double flTi = -iflTi;
			double frTi = ifrTi;
			double rlTi = irlTi;
			double rrTi = irrTi;

			if(abs(DriveTrainPrivate::flDev) < DriveTrainPrivate::minSpeed) DriveTrainPrivate::flDev = 0.0;
			if(abs(DriveTrainPrivate::frDev) < DriveTrainPrivate::minSpeed) DriveTrainPrivate::frDev = 0.0;
			if(abs(DriveTrainPrivate::rlDev) < DriveTrainPrivate::minSpeed) DriveTrainPrivate::rlDev = 0.0;
			if(abs(DriveTrainPrivate::rrDev) < DriveTrainPrivate::minSpeed) DriveTrainPrivate::rrDev = 0.0;

			// std::cout << flTi << "\n";
			// std::cout << frTi << "\n";
			// std::cout << rlTi << "\n";
			// std::cout << rrTi << "\n";
			// std::cout << "\n";

			DriveTrainPrivate::avgSpeed = (flTi + frTi + rlTi + rrTi) / 4.0;
			double avgRat = DriveTrainPrivate::avgSpd / DriveTrainPrivate::speedFactor;
			if(isnan(avgRat) || avgRat == 0.0){
				avgRat = 1.0;
			}

			// std::cout << DriveTrainPrivate::avgSpeed << "\n\n";
			double flTi2 = DriveTrainPrivate::flDev * avgRat / flTi;
			double frTi2 = DriveTrainPrivate::frDev * avgRat / frTi;
			double rlTi2 = DriveTrainPrivate::rlDev * avgRat / rlTi;
			double rrTi2 = DriveTrainPrivate::rrDev * avgRat / rrTi;
			if(abs(flTi2) > DriveTrainPrivate::maxCorrectPerTick) flTi2 = (flTi2 / abs(flTi2)) * DriveTrainPrivate::maxCorrectPerTick;
			if(abs(frTi2) > DriveTrainPrivate::maxCorrectPerTick) frTi2 = (frTi2 / abs(frTi2)) * DriveTrainPrivate::maxCorrectPerTick;
			if(abs(rlTi2) > DriveTrainPrivate::maxCorrectPerTick) rlTi2 = (rlTi2 / abs(rlTi2)) * DriveTrainPrivate::maxCorrectPerTick;
			if(abs(rrTi2) > DriveTrainPrivate::maxCorrectPerTick) rrTi2 = (rrTi2 / abs(rrTi2)) * DriveTrainPrivate::maxCorrectPerTick;

			if(abs(flTi2) < 1.0 / DriveTrainPrivate::maxCorrectPerTick) flTi2 = (flTi2 / abs(flTi2)) * 1.0 / DriveTrainPrivate::maxCorrectPerTick;
			if(abs(flTi2) < 1.0 / DriveTrainPrivate::maxCorrectPerTick) flTi2 = (frTi2 / abs(frTi2)) * 1.0 / DriveTrainPrivate::maxCorrectPerTick;
			if(abs(flTi2) < 1.0 / DriveTrainPrivate::maxCorrectPerTick) flTi2 = (rlTi2 / abs(rlTi2)) * 1.0 / DriveTrainPrivate::maxCorrectPerTick;
			if(abs(flTi2) < 1.0 / DriveTrainPrivate::maxCorrectPerTick) flTi2 = (rrTi2 / abs(rrTi2)) * 1.0 / DriveTrainPrivate::maxCorrectPerTick;
			if((flTi > 1 && frTi > 1 && rlTi > 1 && rrTi > 1) || correctOverride){
				if(((abs(flTi2) < 1.1 && abs(flTi2) > .9) && (abs(frTi2) < 1.1 && abs(frTi2) > .9) && (abs(rlTi2) < 1.1 && abs(rlTi2) > .9) && (abs(rrTi2) < 1.1 && abs(rrTi2) > .9)) || correctOverride){
					//if(!isAuto){
						DriveTrainPrivate::flTi *= isnan(flTi2) ? 1.0 : flTi2;
						DriveTrainPrivate::frTi *= isnan(frTi2) ? 1.0 : frTi2;
						DriveTrainPrivate::rlTi *= isnan(rlTi2) ? 1.0 : rlTi2;
						DriveTrainPrivate::rrTi *= isnan(rrTi2) ? 1.0 : rrTi2;
					//}
				}
			}

			if(DriveTrainPrivate::flTi == 0.0 || isinf(DriveTrainPrivate::flTi) || isnan(DriveTrainPrivate::flTi)) DriveTrainPrivate::flTi = 1.0;
			if(DriveTrainPrivate::frTi == 0.0 || isinf(DriveTrainPrivate::frTi) || isnan(DriveTrainPrivate::frTi)) DriveTrainPrivate::frTi = 1.0;
			if(DriveTrainPrivate::rlTi == 0.0 || isinf(DriveTrainPrivate::rlTi) || isnan(DriveTrainPrivate::rlTi)) DriveTrainPrivate::rlTi = 1.0;
			if(DriveTrainPrivate::rrTi == 0.0 || isinf(DriveTrainPrivate::rrTi) || isnan(DriveTrainPrivate::rrTi)) DriveTrainPrivate::rrTi = 1.0;


			//std::cout << flTi << " .\n";
			 //std::cout << frTi << " .\n";
			 //std::cout << rlTi << " .\n";
			 //std::cout << rrTi << " .\n";
			// std::cout << DriveTrainPrivate::avgSpeed << " << " << DriveTrainPrivate::avgSpd << "\n";
			 //std::cout << " <\n";
			 //std::cout << "-\n";
		}

#ifdef CONTROLLER_ALT_1
		double rotDeg = TYPE_1_CONTROLLER_ROT_DEGREES * rightAxisZ;
		double magn = sqrt(leftAxisX * leftAxisX + leftAxisY * leftAxisY);
		double angle = atan2(leftAxisX, leftAxisY);
		angle += rotDeg * (PI / 180.8);
		leftAxisX = sin(angle) * magn;
		leftAxisY = cos(angle) * magn;

#endif

		double speedFactor = 0.0;
		bool speedBtn = hw::stick->GetRawButton(12);
		if(speedBtn){
			if(!DriveTrainPrivate::lSpeedBtn){
				DriveTrainPrivate::speedControl = (DriveTrainPrivate::speedControl + 1) % 3;
			}
			DriveTrainPrivate::lSpeedBtn = true;
		} else{
			DriveTrainPrivate::lSpeedBtn = false;
		}
#ifdef CONTROLLER_ALT_1
		speedFactor = MAX_SPEED_FACTOR * (hw::stick->GetThrottle() / 2.0 + 0.5);
#else
		switch(DriveTrainPrivate::speedControl){
		case 0:
			speedFactor = .5 * MAX_SPEED_FACTOR;
			break;
		case 1:
			speedFactor = .75 * MAX_SPEED_FACTOR;
			break;
		case 2:
			speedFactor = MAX_SPEED_FACTOR;
			break;
		}
#endif
		SmartDashboard::PutNumber("DriveTrain speed", speedFactor);

		double ly2 = -leftAxisY; // Extra code that I didn't *really* need
		double rz2 = rightAxisZ; // I needed this line even less
		double lx2 = leftAxisX; // And same here

		double lVel = ly2 + rz2; // calculate the velocity of the wheels on the left side
		double rVel = ly2 - rz2; // calculate the velocity of the wheels on the right side


		double flVel = (lVel + lx2); // Now change the velocities so that the robot can strafe. Remember, 0.0 = stopped and 1.0 = max speed
		double frVel = (rVel - lx2); // Same here, with a different wheel

		double rlVel = (lVel - lx2); // etc.
		double rrVel = (rVel + lx2); // And we made it! Careful where you use +/- in these lines, though

		DriveTrainPrivate::avgSpd = (flVel + frVel + rlVel + rrVel) / 4.0;
		DriveTrainPrivate::flDev = flVel;
		DriveTrainPrivate::frDev = frVel;
		DriveTrainPrivate::rlDev = rlVel;
		DriveTrainPrivate::rrDev = rrVel;


		/*
				-26
				 28
				 27
				 31

			     0.5
			    -0.5
			     0.5
			    -0.5

			    1 and 3 = -
		 */

		// std::cout << flVel << " --\n";
		// std::cout << frVel << " --\n";
		// std::cout << rlVel << " --\n";
		// std::cout << rrVel << " --\n";

		 frc::SmartDashboard::PutNumber("DriveTrainPrivate::flDev", DriveTrainPrivate::flDev);
		 frc::SmartDashboard::PutNumber("DriveTrainPrivate::frDev", DriveTrainPrivate::frDev);
		 frc::SmartDashboard::PutNumber("DriveTrainPrivate::rlDev", DriveTrainPrivate::rlDev);
		 frc::SmartDashboard::PutNumber("DriveTrainPrivate::rrDev", DriveTrainPrivate::rrDev);

		// std::cout << "-><-\n";

		 SmartDashboard::PutNumber("Correction factor fl", DriveTrainPrivate::flTi);
		 SmartDashboard::PutNumber("Correction factor fr", DriveTrainPrivate::frTi);
		 SmartDashboard::PutNumber("Correction factor rl", DriveTrainPrivate::rlTi);
		 SmartDashboard::PutNumber("Correction factor rr", DriveTrainPrivate::rrTi);


		hw::flVictor->Set(std::max(std::min(flVel * DriveTrainPrivate::flTi, 1.0), -1.0) * speedFactor); // Actually set the motor speeds to what we calculated
		hw::frVictor->Set(std::max(std::min(frVel * DriveTrainPrivate::frTi, 1.0), -1.0) * speedFactor); // ^^^ Look here ^^^

		hw::rlVictor->Set(std::max(std::min(rlVel * DriveTrainPrivate::rlTi, 1.0), -1.0) * speedFactor); // ^^^^^^^^^^^^^^^^^
		hw::rrVictor->Set(std::max(std::min(rrVel * DriveTrainPrivate::rrTi, 1.0), -1.0) * speedFactor); // ^^^^^^^^^^^^^^^^^

		DriveTrainPrivate::ticksModTicksSpeed = (DriveTrainPrivate::ticksModTicksSpeed + 1) % DriveTrainPrivate::ticksSpeed;
	}
};


#endif /* DRIVETRAIN_H_ */
