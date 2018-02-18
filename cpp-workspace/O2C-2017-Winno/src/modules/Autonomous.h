/*
 * AutonomousMain.h
 *
 *  Created on: Jul 1, 2017
 *      Author: cryog
 */

#ifndef AUTONOMOUSMAIN_H_
#define AUTONOMOUSMAIN_H_


namespace AutonomousPrivate{
	frc::Timer* autoTimer = new frc::Timer();
	bool running;
}
class AutonomousMain : public Module{
	void ModuleInit(){
		frc::SmartDashboard::SetDefaultNumber("Starting position (1, 2 or 3)", 0);
		AutonomousPrivate::autoTimer->Reset();
		AutonomousPrivate::autoTimer->Stop();
	}
	void Autonomous(){
	}
	void ModeChange(){
		AutonomousPrivate::autoTimer->Reset();
		AutonomousPrivate::autoTimer->Stop();
	}
	void registerAutoModule(Module m){

	}
};


#endif /* AUTONOMOUSMAIN_H_ */
