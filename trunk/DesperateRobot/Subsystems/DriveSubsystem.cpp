// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/DriveCommand.h"
#include <math.h>

DriveSubsystem::DriveSubsystem() : Subsystem("DriveSubsystem") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	speedController1 = RobotMap::driveSubsystemSpeedController1;
	speedController2 = RobotMap::driveSubsystemSpeedController2;
	speedController3 = RobotMap::driveSubsystemSpeedController3;
	speedController4 = RobotMap::driveSubsystemSpeedController4;
	robotDriveMecanum = RobotMap::driveSubsystemRobotDriveMecanum;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void DriveSubsystem::InitDefaultCommand() {
	//printf("DriveSubsystem::InitiDefaultCommand -> Called.\n");
	
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new DriveCommand());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

static const float TWIST_TOLERANCE_MIN = -0.1;
static const float TWIST_TOLERANCE_MAX = 0.1;

void DriveSubsystem::MecanumDrive(float x, float y, float twist) { 
	
	printf("DriveSubsystem: x = %f, y = %f, twist = %f\n", x, y, twist);
	
	if ((twist >= TWIST_TOLERANCE_MIN) && (twist <= TWIST_TOLERANCE_MAX))
	{
		twist = 0.0;
	}
	
	
	robotDriveMecanum->MecanumDrive_Cartesian(x, y, -twist);
}

#if 0
const float DriveToleranceX = 0.1;
const float DriveToleranceY = 0.1;
float pi = 3.1415926535;
float radians;


void DriveSubsystem::MecanumDrive(float x, float y, float twist) { 
	//printf ("DriveSubsystem::MecanumDrive -> Entered.\n");
	// This is shorthand for assignment based on an if statement.
	// It says that if (abs(y) > DriveTolerance) 
	// then use the current value of y.
	// otherwise use 0.0
	// Do the same for x as well.
	
	//y = (y > DriveToleranceY) ? y : 0.0;
	//x = (x > DriveToleranceX) ? x : 0.0;
	
	if (x > -DriveToleranceX && x < 0) {x=0;}
	if (y > -DriveToleranceY && y < 0) {y=0;}
	
	if (x < DriveToleranceX && x > 0) {x=0;}
	if (y < DriveToleranceY && y > 0) {y=0;}
	
	if (twist > 0.1 && twist > 0){twist=0;}
	if (twist < -0.1 && twist < 0){twist=0;}
		
	  float theta;
	  float magnitude;
	  magnitude = sqrt(pow(x,2) + pow(y,2));
	  
	  radians = asin(x/magnitude);

	  theta = (180*radians)/pi;
	  
	

	
	
	 
		  // This code is for a manually defined
		  // mecanum drive. Easy to tweak.
		  
		
		
		  
	//Base Formulas -- DO NOT MODIFY OR UN-COMMENT
	// where 'theta' is the desired angle of motion
	//
	//speedController1 = (theta * sin(theta+45))+twist;
	//speedController2 = (theta * cos(theta+45))-twist;
	//speedController3 = (theta * cos(theta+45))+twist;
	//speedController4 = (theta * sin(theta+45))-twist;
		  
		  if (y>0 && x>0) {theta = 90-theta;}
		  if (y<0 && x<0) {theta = 90+theta;}
	  	  if (y<0 && x<0) {theta = 270-theta;}
	  	  if (y>0 && x<0) {theta = 270+theta;}
		  
		  
		  // Front Left Wheel
		 
		  //float Speed1 = (magnitude*(sin(theta*(pi/180))));
		  // Front Right Wheel
		    
		  //float Speed2 = (magnitude*(cos(theta*(pi/180))));
		  // Rear Left Wheel 	    
		    
		//  float Speed3 = (magnitude*(cos(theta*(pi/180))));
		  // Rear Right Wheel
		    
	//	  float Speed4 = (magnitude*(sin(theta*(pi/180))));
		   
		  
		  	robotDriveMecanum->MecanumDrive_Cartesian(x, y, twist);
		/*
		 speedController1->Set(Speed1);
		 speedController2->Set(Speed2);
		 speedController3->Set(Speed3);
		 speedController4->Set(Speed4);
		 
		 
		  //*/
//	printf("x = %f, y = %f, twist = %f, theta = %f, magnitude = %f\n", x, y, twist, theta,  magnitude);
//	printf("1 = %f, 2 = %f, 3 = %f, 4 = %f, \n", Speed1, Speed2, Speed3, Speed4);
	
	/*
	if (Speed1>0){printf("Front Left Forward<\       ");}
	else if (Speed1<0){printf("Front Left Backward\>       ");}
	else {printf("Front Left Zero        ");}
	
	if (Speed2>0){printf("Front Right Forward/>       ");}
	else if (Speed2<0){printf("Front Right Backward</       ");}
	else {printf("Front Right Zero         ");}
	
	if (Speed3>0){printf("\nRear Left Forward<\       ");}
	else if (Speed3<0){printf("\nRear Left Backward\>       ");}
	else {printf("\nRear Left Zero         ");}
	
	if (Speed4>0){printf("Rear Right Forward/>       ");}
	else if (Speed4<0){printf("Rear Right Backward</       ");}
	else {printf("Rear Right Zero         ");}*/
}
#endif
