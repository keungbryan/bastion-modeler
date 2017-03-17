#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	XPOS, YPOS, ZPOS, UPPER_BODY_ROTATE, HEAD_ROTATE, 
	LEFT_SHOULDER_X_ROTATE, LEFT_SHOULDER_Y_ROTATE, LEFT_SHOULDER_Z_ROTATE, LEFT_UPPER_ARM_Y_ROTATE, LEFT_LOWER_ARM_X_ROTATE, LEFT_LOWER_ARM_Y_ROTATE, 
	WRIST_X_ROTATE, WRIST_Y_ROTATE, WRIST_Z_ROTATE, THUMB_PROXIMAL_ROTATE, THUMB_MIDDLE_ROTATE, THUMB_DISTAL_ROTATE, INDEX_PROXIMAL_ROTATE, INDEX_MIDDLE_ROTATE, INDEX_DISTAL_ROTATE, 
	MIDDLE_PROXIMAL_ROTATE, MIDDLE_MIDDLE_ROTATE, MIDDLE_DISTAL_ROTATE, RING_PROXIMAL_ROTATE, RING_MIDDLE_ROTATE, RING_DISTAL_ROTATE, PINKY_PROXIMAL_ROTATE, PINKY_MIDDLE_ROTATE, PINKY_DISTAL_ROTATE,
	RIGHT_SHOULDER_X_ROTATE, RIGHT_SHOULDER_Y_ROTATE, RIGHT_SHOULDER_Z_ROTATE, RIGHT_UPPER_ARM_Y_ROTATE, GUN_X_ROTATE, GUN_Y_ROTATE, GUN_Z_ROTATE,
	LEFT_UPPER_LEG_X_ROTATE, LEFT_UPPER_LEG_Y_ROTATE, LEFT_MIDDLE_LEG_X_ROTATE, LEFT_LOWER_LEG_X_ROTATE, LEFT_FOOT_X_ROTATE,
	RIGHT_UPPER_LEG_X_ROTATE, RIGHT_UPPER_LEG_Y_ROTATE, RIGHT_MIDDLE_LEG_X_ROTATE, RIGHT_LOWER_LEG_X_ROTATE, RIGHT_FOOT_X_ROTATE, 
	LIGHT_TEST, 
	ANIMATE,
	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif