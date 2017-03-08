#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

#define COLOR_BEIGE 245.0f / 255.0f, 245.0f / 255.0f, 220.0f / 255.0f
#define COLOR_GRAY 105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f
#define COLOR_CYAN 0.0f, 1.0f, 1.0f
#define COLOR_ORANGE 1.0f ,140.0f / 255.0f , 0.0f
#define COLOR_OLIVE 61.0f / 255.0f, 240.0f / 255.0f , 159.0f / 255.0f

#define NUM_OF_BTMUZZLE 8

// To make a SampleModel, we inherit off of ModelerView
class BastionModel : public ModelerView
{
public:
	BastionModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createBastionModel(int x, int y, int w, int h, char *label)
{
	return new BastionModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void BastionModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
/*	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();
*/
	// draw the bastion model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GRAY);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// translate whole body first
		glTranslated(0, 2, 0.5);

		// draw upper body
		// draw waist
		glPushMatrix();
		glRotated(VAL(UPPER_BODY_ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0, 0); // x' = x, y' = -z, z' = y
		drawCylinder(0.2, 0.85, 0.85);
		glTranslated(0, 0, 0.2);
		drawCylinder(1, 0.5, 0.5);

		// return to origin, reset axis
		glRotated(90, 1.0, 0, 0);
		glTranslated(0, -2, -0.5);

		// draw body (beige)
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_BEIGE);
		// front
		drawTriangle(-1, 4, -0.5, -1, 4, 1.5, 1, 4, -0.5);
		drawTriangle(-1, 4, 1.5, 1, 4, 1.5, 1, 4, -0.5);
		drawTriangle(1, 4, 1.5, -1, 4, 1.5, 0.75, 3.25, 2.5);
		drawTriangle(0.75, 3.25, 2.5, -1, 4, 1.5, -0.75, 3.25, 2.5);
		drawTriangle(0.75, 3.25, 2.5, -0.75, 3.25, 2.5, 0.75, 2.75, 2.25);
		drawTriangle(-0.75, 3.25, 2.5, -0.75, 2.75, 2.25, 0.75, 2.75, 2.25);
		// right side
		drawTriangle(-1, 2.75, 1.75, -0.75, 2.75, 2.25, -0.75, 3.25, 2.5);
		drawTriangle(-0.75, 3.25, 2.5, -1, 4, 1.5, -1, 2.75, 1.75);
		drawTriangle(-1, 4, 1.5, -1, 3, 0.5, -1, 2.75, 1.75);
		drawTriangle(-1, 2.75, 1.75, -1, 3, 0.5, -1, 2.5, 1.25);
		drawTriangle(-1, 3, 0.5, -1, 4, 1.5, -1, 4, 0.5);
		// left side
		drawTriangle(1, 2.75, 1.75, 0.75, 3.25, 2.5, 0.75, 2.75, 2.25);
		drawTriangle(0.75, 3.25, 2.5, 1, 2.75, 1.75, 1, 4, 1.5);
		drawTriangle(1, 4, 1.5, 1, 2.75, 1.75, 1, 3, 0.5);
		drawTriangle(1, 2.75, 1.75, 1, 2.5, 1.25, 1, 3, 0.5);
		drawTriangle(1, 3, 0.5, 1, 4, 0.5, 1, 4, 1.5);
		// bottom
		drawTriangle(-0.75, 2.75, 2.25, -1, 2.75, 1.75, 1, 2.75, 1.75);
		drawTriangle(-0.75, 2.75, 2.25, 1, 2.75, 1.75, 0.75, 2.75, 2.25);
		drawTriangle(-1, 2.75, 1.75, 1, 2.5, 1.25, 1, 2.75, 1.75);
		drawTriangle(-1, 2.75, 1.75, -1, 2.5, 1.25, 1, 2.5, 1.25);
		drawTriangle(-1, 2.5, 1.25, 1, 3, 0.5, 1, 2.5, 1.25);
		drawTriangle(-1, 2.5, 1.25, -1, 3, 0.5, 1, 3, 0.5);
		// gray part
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GRAY);
		// left
		drawTriangle(-1, 4, -0.5, -1, 3, 0.5, -1, 4, 0.5);
		drawTriangle(-1, 4, -0.5, -1, 3, -0.5, -1, 3, 0.5);
		// right
		drawTriangle(1, 4, 0.5, 1, 3, -0.5, 1, 4, -0.5);
		drawTriangle(1, 4, 0.5, 1, 3, 0.5, 1, 3, -0.5);
		// bottom
		drawTriangle(-1, 3, 0.5, -1, 3, -0.5, 1, 3, -0.5);
		drawTriangle(-1, 3, 0.5, 1, 3, -0.5, 1, 3, 0.5);
		// back
		drawTriangle(1, 4, -0.5, -1, 3, -0.5, -1, 4, -0.5);
		drawTriangle(1, 4, -0.5, 1, 3, -0.5, -1, 3, -0.5);


			// draw neck
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(-0.375, 4, 0.25);
			glScaled(0.75, 0.5, 0.5);
			drawBox(1, 1, 1);

			// draw head
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glScaled(0.85 / 0.75, 2, 2);
			glTranslated(-0.05, 0.5, -0.25);
			glTranslated(0.5, 0, 0.5);
			glRotated(VAL(HEAD_ROTATE), 0.0, 1.0, 0.0);
			glTranslated(-0.5, 0, -0.5);
			drawBox(1, 1, 1);

			// draw eye
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_CYAN);
			glScaled(0.25, 0.6, 0.2);
			glTranslated(1.5, 0.5, 5);
			drawBox(1, 1, 1);
			glPopMatrix();



			// draw back turret
			glPushMatrix();

			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0, 3, -1.25);
			glRotated(-90, 1.0, 0, 0);
			drawCylinder(0.75, 0.75, 0.75);

			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0, 0, 0.75);
			drawCylinder(2.5, 0.6, 0.6);

			// draw back turret muzzle
			glTranslated(0, 0, 2.5);
			drawCylinder(0.2, 0.7, 0.7);

			glTranslated(0, 0, 0.2);
			for (int i = 0; i < NUM_OF_BTMUZZLE; i++)
			{
				glTranslated(0, 0.45, 0);
				drawCylinder(0.2, 0.15, 0.15);
				glTranslated(0, -0.45, 0);
				glRotated(360 / NUM_OF_BTMUZZLE, 0.0, 0.0, 1.0);
			}

			glPopMatrix();

			// draw left limb
			// draw left shoulders (movable & shoulder plates)
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_ORANGE);
			glTranslated(1, 3.25, -0.375);
			
			glTranslated(0, 0.5, 0);
			glRotated(VAL(LEFT_ARM_Z_ROTATE), 0.0, 0.0, 1.0);
			glTranslated(0, -0.5, 0);

			glTranslated(0, 0, 0.5);
			glRotated(VAL(LEFT_ARM_Y_ROTATE), 0.0, 1.0, 0.0);
			glTranslated(0, 0, -0.5);

			glTranslated(0, 0.5, 0.5);
			glRotated(-VAL(LEFT_ARM_X_ROTATE), 1.0, 0.0, 0.0);
			glTranslated(0, -0.5, -0.5);

			glScaled(1, 0.5, 0.75);
			drawBox(1, 1, 1);

			// draw shoulder plates
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0.5, 1.25, 0);
			glScaled(1, 0.5, 1);
			drawBox(1, 1, 1);
			glTranslated(0.75, 0, 0);
			glScaled(0.25, -4, 1);
			drawBox(1, 1, 1);

			// reset transformation to start of shoulder
			glScaled(4, -0.25, 1);
			glTranslated(-0.75, 0, 0);
			glScaled(1, 2, 1);
			glTranslated(-0.5, -1.25, 0);
			glScaled(1, 2, 1); // keep z scaled to 0.75

				// draw left upper arm
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_OLIVE);
				glTranslated(0.5, 0, 0);
				glScaled(0.5, -1, 1);
				drawBox(1, 1, 1);

					// draw left lower arm
					glPushMatrix();
					glTranslated(0, 1, 0);
					glScaled(1, 1.5, 1);
					drawBox(1, 1, 1);
						// draw hand
						// draw palm
							// draw thumb
							// draw 4 fingers as a rectangle

					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

			// draw right limb
			// draw right shoulders (movable & shoulder plates)
				// draw right upper arm
					// draw gun

		glPopMatrix();

		
		// draw lower body
		glPushMatrix();
		// draw pelvis
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_OLIVE);
		glTranslated(-0.45, -0.7, -0.45);
		glScaled(0.9, 0.7, 0.9);
		drawBox(1, 1, 1);

			//draw left leg
			//draw right leg


		glPopMatrix();
		//finish drawing lower body


	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[UPPER_BODY_ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[HEAD_ROTATE] = ModelerControl("Head Rotate", -90, 90, 1, 0);
	controls[LEFT_ARM_X_ROTATE] = ModelerControl("Left Arm X Rotate", -70, 150, 1, 0);
	controls[LEFT_ARM_Y_ROTATE] = ModelerControl("Left Arm Y Rotate", -30, 30, 1, 0);
	controls[LEFT_ARM_Z_ROTATE] = ModelerControl("Left Arm Z Rotate", 0, 30, 1, 10);

	ModelerApplication::Instance()->Init(&createBastionModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
