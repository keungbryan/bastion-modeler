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
#define COLOR_METAL 224.0f / 255.0f, 224.0f / 255.0f, 224.0f / 255.0f

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
		drawCylinder(0.2, 0.75, 0.75);
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
			glRotated(VAL(LEFT_SHOULDER_Z_ROTATE), 0.0, 0.0, 1.0);
			glTranslated(0, -0.5, 0);

			glTranslated(0, 0, 0.5);
			glRotated(VAL(LEFT_SHOULDER_Y_ROTATE), 0.0, 1.0, 0.0);
			glTranslated(0, 0, -0.5);

			glTranslated(0, 0.5, 0.5);
			glRotated(-VAL(LEFT_SHOULDER_X_ROTATE), 1.0, 0.0, 0.0);
			glTranslated(0, -0.5, -0.5);

			glScaled(1, 0.5, 0.75);
			drawBox(1, 1, 1);

			// draw shoulder plates
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0.5, 1.25, 0);
			glScaled(1, 0.5, 1); // 1, .25, .75
			drawBox(1, 1, 1);
			glTranslated(0.75, 0, 0);
			glScaled(0.25, -4, 1); // .25, -1, .75
			drawBox(1, 1, 1);

			// reset transformation to start of shoulder
			glScaled(4, -0.25, 1);
			glTranslated(-0.75, 0, 0);
			glScaled(1, 2, 1);
			glTranslated(-0.5, -1.25, 0);
			glScaled(1, 2, 1/0.75); 

				// draw left upper arm
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_OLIVE);
				glTranslated(0.5, 0, 0.125);

				glTranslated(0.25, 0, 0.25);
				glRotated(VAL(LEFT_UPPER_ARM_Y_ROTATE), 0.0, -1.0, 0.0);
				glTranslated(-0.25, 0, -0.25);

				glScaled(0.5, -1.5, 0.5);
				drawBox(1, 1, 1);
				// reset scale
				glScaled(2, 1 / -1.5, 2);

					// draw left lower arm
					glPushMatrix();
					glTranslated(0, -1.5, 0);

					glTranslated(0.25, 0, 0.25);
					glRotated(VAL(LEFT_LOWER_ARM_X_ROTATE), -1.0, 0, 0);
					glRotated(VAL(LEFT_LOWER_ARM_Y_ROTATE), 0, 1.0, 0);
					glTranslated(-0.25, 0, -0.25);

					glScaled(0.5, -1.5, 0.5);
					drawBox(1, 1, 1);
					// reset scale
					glScaled(2, 1 / -1.5, 2);
					
						// draw hand
						// draw palm
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glPushMatrix();
						glTranslated(0.125, -1.6, 0);

						glTranslated(0.125, 0, 0);
						glRotated(VAL(LEFT_WRIST_Z_ROTATE), 0, 0, 1.0);
						glTranslated(-0.125, 0, 0);

						drawBox(0.25, -0.5, 0.5);
							// draw thumb
							// proximal phalanx
							glPushMatrix();
							glTranslated(0.1, -0.1, 0.6);
							drawSphere(0.075);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							glRotated(VAL(THUMB_PROXIMAL_ROTATE), -1.0, 0, 0);
							drawCylinder(0.175, 0.075, 0.075);
								// middle phalanx
								glPushMatrix();
								glTranslated(0, 0, 0.2);
								drawSphere(0.075);
								glRotated(VAL(THUMB_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								drawCylinder(0.15, 0.075, 0.07);
									// distal phalanx
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									drawSphere(0.07);
									glRotated(VAL(THUMB_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									drawCylinder(0.1, 0.07, 0.065);
									glTranslated(0, 0, 0.1);
									drawSphere(0.065);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// draw 4 fingers
							// index
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.44);
							drawSphere(0.06);
							glRotated(VAL(INDEX_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							drawCylinder(0.15, 0.06, 0.06);
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.175);
								drawSphere(0.06);
								glRotated(VAL(INDEX_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								drawCylinder(0.15, 0.06, 0.05);
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									drawSphere(0.05);
									glRotated(VAL(INDEX_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									drawCylinder(0.1, 0.05, 0.04);
									glTranslated(0, 0, 0.1);
									drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// middle
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.3);
							drawSphere(0.06);
							glRotated(VAL(MIDDLE_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							drawCylinder(0.2, 0.06, 0.06);
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.225);
								drawSphere(0.06);
								glRotated(VAL(MIDDLE_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								drawCylinder(0.15, 0.06, 0.05);
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									drawSphere(0.05);
									glRotated(VAL(MIDDLE_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									drawCylinder(0.1, 0.05, 0.04);
									glTranslated(0, 0, 0.1);
									drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// ring
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.525, 0.16);
							drawSphere(0.06);
							glRotated(VAL(RING_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.025, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							drawCylinder(0.15, 0.06, 0.06);
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.175);
								drawSphere(0.06);
								glRotated(VAL(RING_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.025);
								drawCylinder(0.15, 0.06, 0.05);
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.175);
									drawSphere(0.05);
									glRotated(VAL(RING_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.025);
									drawCylinder(0.1, 0.05, 0.04);
									glTranslated(0, 0, 0.1);
									drawSphere(0.04);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
							// pinky
							// proximal
							glPushMatrix();
							glTranslated(0.1, -0.52, 0.04);
							drawSphere(0.04);
							glRotated(VAL(PINKY_PROXIMAL_ROTATE), 0, 0, -1.0);
							glTranslated(0, -0.02, 0);
							glRotated(90, 1.0, 0, 0); // x' = x, y' = z, z' = -y
							drawCylinder(0.1, 0.04, 0.04);
								// middle
								glPushMatrix();
								glTranslated(0, 0, 0.115);
								drawSphere(0.04);
								glRotated(VAL(PINKY_MIDDLE_ROTATE), 0, -1.0, 0);
								glTranslated(0, 0, 0.015);
								drawCylinder(0.1, 0.04, 0.03);
									// distal
									glPushMatrix();
									glTranslated(0, 0, 0.115);
									drawSphere(0.03);
									glRotated(VAL(PINKY_DISTAL_ROTATE), 0, -1.0, 0);
									glTranslated(0, 0, 0.015);
									drawCylinder(0.1, 0.03, 0.02);
									glTranslated(0, 0, 0.1);
									drawSphere(0.02);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

			// draw right limb
			// draw right shoulders (movable & shoulder plates)
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_ORANGE);
			glTranslated(-1, 3.25, -0.375);
			//rotations

			glScaled(-1, 0.5, 0.75); // x' = -x
			drawBox(1, 1, 1);

			// draw shoulder plates
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_BEIGE);
			glTranslated(0.5, 1.25, 0);
			glScaled(1, 0.5, 1); // -1, .25, .75
			drawBox(1, 1, 1);
			glTranslated(0.75, 0, 0);
			glScaled(0.25, -4, 1); // -.25, -1, .75
			drawBox(1, 1, 1);

			// reset transformation to start of shoulder
			glScaled(4, -0.25, 1);
			glTranslated(-0.75, 0, 0);
			glScaled(1, 2, 1);
			glTranslated(-0.5, -1.25, 0);
			glScaled(1, 2, 1 / 0.75);

				// draw right upper arm
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_OLIVE);
				glTranslated(0.5, 0, 0.125);
				drawBox(.5, -1.5, .5);
				glScaled(-1, 1, 1);
				glTranslated(-0.25, -2, 0);
					// draw gun
					// cylinders
					glPushMatrix();
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					drawCylinder(.5, 0.25, 0.25);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					glTranslated(0, -0.25, 0.3);
					drawCylinder(.5, .15, .15);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_METAL);
					glTranslated(0, 0, 0.5);
					drawCylinder(.9, .1, .1);
					glTranslated(0, 0, .9);
					
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					drawCylinder(.1, .1, .15);
					glTranslated(0, 0, .1);
					drawCylinder(.6, .15, .15);
					glTranslated(0, 0, .6);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_METAL);
					drawCylinder(.2, .15, .15);
					glTranslated(0, 0, .2);
					drawCylinder(.1, .15, .125);
					glTranslated(0, 0, .1);

					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					drawCylinder(0.3, .1, .1);
					glTranslated(0, 0, .3);
					drawCylinder(.05, .1, .125);
					glTranslated(0, 0, .05);
					drawCylinder(.3, .125, .125);
					glTranslated(0, 0.25, -3.1);


					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_OLIVE);
					// left (olive) outside
					drawTriangle(-0.3, 0.05, 0,		-0.3, -0.25, 0,		-0.3, -0.25, 0.25);
					drawTriangle(-0.3, 0.05, 0.5,	-0.3, 0.05, 0,		-0.3, -0.25, 0.25);
					drawTriangle(-0.3, 0.05, 0.5,	-0.3, -0.25, 0.25,	-0.3, -0.25, 0.65);
					drawTriangle(-0.3, -0.25, 0.65, -0.3, -0.25, 0.25,	-0.3, -0.55, 0.65);
					drawTriangle(-0.3, -0.25, 0.65, -0.3, -0.55, 0.65,	-0.3, -0.25, 0.9);
					drawTriangle(-0.3, -0.25, 0.9,	-0.3, -0.55, 0.65,	-0.3, -0.45, 1.15);
					drawTriangle(-0.3, -0.45, 1.15, -0.3, -0.55, 0.65,	-0.3, -0.55, 1.15);
					// inside
					drawTriangle(-0.25, 0.05, 0,		-0.25, -0.25, 0.25, -0.25, -0.25, 0);
					drawTriangle(-0.25, 0.05, 0.5,		-0.25, -0.25, 0.25, -0.25, 0.05, 0);
					drawTriangle(-0.25, 0.05, 0.5,		-0.25, -0.25, 0.65, -0.25, -0.25, 0.25);
					drawTriangle(-0.25, -0.25, 0.65,	-0.25, -0.55, 0.65, -0.25, -0.25, 0.25);
					drawTriangle(-0.25, -0.25, 0.65,	-0.25, -0.25, 0.9,	-0.25, -0.55, 0.65);
					drawTriangle(-0.25, -0.25, 0.9,		-0.25, -0.45, 1.15, -0.25, -0.55, 0.65);
					drawTriangle(-0.25, -0.45, 1.15,	-0.25, -0.55, 1.15, -0.25, -0.55, 0.65);
					// sides
					drawTriangle(-0.3, 0.05, 0,			-0.3, 0.05, 0.5,	-0.25, 0.05, 0);
					drawTriangle(-0.25, 0.05, 0,		-0.3, 0.05, 0.5,	-0.25, 0.05, 0.5);
					drawTriangle(-0.25, 0.05, 0.5,		-0.3, 0.05, 0.5,	-0.3, -0.25, 0.65);
					drawTriangle(-0.25, 0.05, 0.5,		-0.3, -0.25, 0.65,	-0.25, -0.25, 0.65);
					drawTriangle(-0.25, -0.25, 0.65,	-0.3, -0.25, 0.65,	-0.3, -0.25, 0.9);
					drawTriangle(-0.25, -0.25, 0.65,	-0.3, -0.25, 0.9,	-0.25, -0.25, 0.9);
					drawTriangle(-0.25, -0.25, 0.9,		-0.3, -0.25, 0.9,	-0.3, -0.45, 1.15);
					drawTriangle(-0.25, -0.25, 0.9,		-0.3, -0.45, 1.15,	-0.25, -0.45, 1.15);
					drawTriangle(-0.25, -0.45, 1.15,	-0.3, -0.45, 1.15,	-0.3, -0.55, 1.15);
					drawTriangle(-0.25, -0.45, 1.15,	-0.3, -0.55, 1.15,	-0.25, -0.55, 1.15);
					drawTriangle(-0.25, -0.55, 1.15,	-0.3, -0.55, 1.15,	-0.3, -0.55, 0.65);
					drawTriangle(-0.25, -0.55, 1.15,	-0.3, -0.55, 0.65,	-0.25, -0.55, 0.65);
					drawTriangle(-0.25, -0.55, 0.65,	-0.3, -0.55, 0.65,	-0.3, -0.25, 0.25);
					drawTriangle(-0.25, -0.55, 0.65,	-0.3, -0.25, 0.25,	-0.25, -0.25, 0.25);
					drawTriangle(-0.25, -0.25, 0.25,	-0.3, -0.25, 0.25,	-0.3, -0.25, 0);
					drawTriangle(-0.25, -0.25, 0.25,	-0.3, -0.25, 0,		-0.25, -0.25, 0);
					drawTriangle(-0.25, -0.25, 0,		-0.3, -0.25, 0,		-0.3, 0.05, 0);
					drawTriangle(-0.25, -0.25, 0,		-0.3, 0.05, 0,		-0.25, 0.05, 0);

					// right (olive) outside
					drawTriangle(0.3, 0.05, 0,		0.3, -0.25, 0.25,	0.3, -0.25, 0);
					drawTriangle(0.3, 0.05, 0.5,	0.3, -0.25, 0.25,	0.3, 0.05, 0);
					drawTriangle(0.3, 0.05, 0.5,	0.3, -0.25, 0.65,	0.3, -0.25, 0.25);
					drawTriangle(0.3, -0.25, 0.65,	0.3, -0.55, 0.65,	0.3, -0.25, 0.25);
					drawTriangle(0.3, -0.25, 0.65,	0.3, -0.25, 0.9,	0.3, -0.55, 0.65);
					drawTriangle(0.3, -0.25, 0.9,	0.3, -0.45, 1.15,	0.3, -0.55, 0.65);
					drawTriangle(0.3, -0.45, 1.15,	0.3, -0.55, 1.15,	0.3, -0.55, 0.65);
					// inside
					drawTriangle(0.25, 0.05, 0,		0.25, -0.25, 0,		0.25, -0.25, 0.25);
					drawTriangle(0.25, 0.05, 0.5,	0.25, 0.05, 0,		0.25, -0.25, 0.25);
					drawTriangle(0.25, 0.05, 0.5,	0.25, -0.25,		0.25, 0.25, -0.25, 0.65);
					drawTriangle(0.25, -0.25, 0.65, 0.25, -0.25,		0.25, 0.25, -0.55, 0.65);
					drawTriangle(0.25, -0.25, 0.65, 0.25, -0.55, 0.65,	0.25, -0.25, 0.9);
					drawTriangle(0.25, -0.25, 0.9,	0.25, -0.55, 0.65,	0.25, -0.45, 1.15);
					drawTriangle(0.25, -0.45, 1.15, 0.25, -0.55, 0.65,	0.25, -0.55, 1.15);
					// sides
					drawTriangle(0.3, 0.05, 0,		0.25, 0.05, 0,		0.3, 0.05, 0.5);
					drawTriangle(0.25, 0.05, 0,		0.25, 0.05, 0.5,	0.3, 0.05, 0.5);
					drawTriangle(0.25, 0.05, 0.5,	0.3, -0.25, 0.65,	0.3, 0.05, 0.5);
					drawTriangle(0.25, 0.05, 0.5,	0.25, -0.25, 0.65,	0.3, -0.25, 0.65);
					drawTriangle(0.25, -0.25, 0.65, 0.3, -0.25, 0.9,	0.3, -0.25, 0.65);
					drawTriangle(0.25, -0.25, 0.65, 0.25, -0.25, 0.9,	0.3, -0.25, 0.9);
					drawTriangle(0.25, -0.25, 0.9,	0.3, -0.45, 1.15,	0.3, -0.25, 0.9);
					drawTriangle(0.25, -0.25, 0.9,	0.25, -0.45, 1.15,	0.3, -0.45, 1.15);
					drawTriangle(0.25, -0.45, 1.15, 0.3, -0.55, 1.15,	0.3, -0.45, 1.15);
					drawTriangle(0.25, -0.45, 1.15, 0.25, -0.55, 1.15,	0.3, -0.55, 1.15);
					drawTriangle(0.25, -0.55, 1.15, 0.3, -0.55, 0.65,	0.3, -0.55, 1.15);
					drawTriangle(0.25, -0.55, 1.15, 0.25, -0.55, 0.65,	0.3, -0.55, 0.65);
					drawTriangle(0.25, -0.55, 0.65, 0.3, -0.25, 0.25,	0.3, -0.55, 0.65);
					drawTriangle(0.25, -0.55, 0.65, 0.25, -0.25, 0.25,	0.3, -0.25, 0.25);
					drawTriangle(0.25, -0.25, 0.25, 0.3, -0.25, 0,		0.3, -0.25, 0.25);
					drawTriangle(0.25, -0.25, 0.25, 0.25, -0.25, 0,		0.3, -0.25, 0);
					drawTriangle(0.25, -0.25, 0,	0.3, 0.05, 0,		0.3, -0.25, 0);
					drawTriangle(0.25, -0.25, 0,	0.25, 0.05, 0,		0.3, 0.05, 0);

					// left black bar
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					drawTriangle(-0.2, -0.6, 0.65,		-0.25, -0.65, 0.75,	-0.25, -0.45, 0.75);
					drawTriangle(-0.2, -0.6, 0.65,		-0.25, -0.45, 0.75,	-0.2, -0.45, 0.65);
					drawTriangle(-0.2, -0.45, 0.65,		-0.25, -0.45, 0.75,	-0.2, -0.4, 0.75);
					drawTriangle(-0.2, -0.4, 0.75,		-0.25, -0.45, 0.75,	-0.2, -0.4, 1.85);
					drawTriangle(-0.25, -0.45, 0.75,	-0.25, -0.45, 1.85, -0.2, -0.4, 1.85);
					drawTriangle(-0.25, -0.45, 0.75,	-0.25, -0.65, 1.85, -0.25, -0.45, 1.85);
					drawTriangle(-0.25, -0.45, 0.75,	-0.25, -0.65, 0.75, -0.25, -0.65, 1.85);
					drawTriangle(-0.25, -0.65, 1.85,	-0.2, -0.4, 1.85,	-0.25, -0.45, 1.85);
					drawTriangle(-0.25, -0.65, 1.85,	-0.2, -0.65, 1.85,	-0.2, -0.4, 1.85);
					drawTriangle(-0.25, -0.65, 1.85,	-0.2, -0.65, 0.75,	-0.2, -0.65, 1.85);
					drawTriangle(-0.25, -0.65, 1.85,	-0.25, -0.65, 0.75, -0.2, -0.65, 0.75);
					drawTriangle(-0.2, -0.65, 0.75,		-0.25, -0.65, 0.75, -0.2, -0.6, 0.65);
					drawTriangle(-0.2, -0.4, 0.75,		-0.2, -0.4, 1.85,	-0.2, -0.65, 1.85);
					drawTriangle(-0.2, -0.4, 0.75,		-0.2, -0.65, 1.85,	-0.2, -0.65, 0.75);
					drawTriangle(-0.2, -0.4, 0.75,		-0.2, -0.65, 0.75,	-0.2, -0.6, 0.65);
					drawTriangle(-0.2, -0.4, 0.75,		-0.2, -0.6, 0.65,	-0.2, -0.45, 0.65);

					// right black bar
					drawTriangle(0.2, -0.6, 0.65,	0.25, -0.45, 0.75,	0.25, -0.65, 0.75);
					drawTriangle(0.2, -0.6, 0.65,	0.2, -0.45, 0.65,	0.25, -0.45, 0.75);
					drawTriangle(0.2, -0.45, 0.65,	0.2, -0.4, 0.75,	0.25, -0.45, 0.75);
					drawTriangle(0.2, -0.4, 0.75,	0.2, -0.4, 1.85,	0.25, -0.45, 0.75);
					drawTriangle(0.25, -0.45, 0.75,	0.2, -0.4, 1.85,	0.25, -0.45, 1.85);
					drawTriangle(0.25, -0.45, 0.75,	0.25, -0.45, 1.85,	0.25, -0.65, 1.85);
					drawTriangle(0.25, -0.45, 0.75,	0.25, -0.65, 1.85,	0.25, -0.65, 0.75);
					drawTriangle(0.25, -0.65, 1.85,	0.25, -0.45, 1.85,	0.2, -0.4, 1.85);
					drawTriangle(0.25, -0.65, 1.85,	0.2, -0.4, 1.85,	0.2, -0.65, 1.85);
					drawTriangle(0.25, -0.65, 1.85,	0.2, -0.65, 1.85,	0.2, -0.65, 0.75);
					drawTriangle(0.25, -0.65, 1.85,	0.2, -0.65, 0.75,	0.25, -0.65, 0.75);
					drawTriangle(0.2, -0.65, 0.75,	0.2, -0.6, 0.65,	0.25, -0.65, 0.75);
					drawTriangle(0.2, -0.4, 0.75,	0.2, -0.65, 1.85,	0.2, -0.4, 1.85);
					drawTriangle(0.2, -0.4, 0.75,	0.2, -0.65, 0.75,	0.2, -0.65, 1.85);
					drawTriangle(0.2, -0.4, 0.75,	0.2, -0.6, 0.65,	0.2, -0.65, 0.75);
					drawTriangle(0.2, -0.4, 0.75,	0.2, -0.45, 0.65,	0.2, -0.6, 0.65);

					// back black box
					drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.85, 0.7,	-0.2, -0.675, 0.85);
					drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.675, 0.85,	-0.2, -0.4, 0.85);
					drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.4, 0.85,	-0.2, -0.45, 0.475);
					drawTriangle(-0.2, -0.85, 0.6, -0.2, -0.45, 0.475,	-0.2, -0.65, 0.35);

					drawTriangle(-0.2, -0.85, 0.6,		0.2, -0.85, 0.6,	0.2, -0.85, 0.7);
					drawTriangle(-0.2, -0.85, 0.6,		0.2, -0.85, 0.7,	-0.2, -0.85, 0.7);
					drawTriangle(-0.2, -0.85, 0.7,		0.2, -0.85, 0.7,	0.2, -0.675, 0.85);
					drawTriangle(-0.2, -0.85, 0.7,		0.2, -0.675, 0.85,	-0.2, -0.675, 0.85);
					drawTriangle(-0.2, -0.675, 0.85,	0.2, -0.675, 0.85,	0.2, -0.4, 0.85);
					drawTriangle(-0.2, -0.675, 0.85,	0.2, -0.4, 0.85,	-0.2, -0.4, 0.85);
					drawTriangle(-0.2, -0.4, 0.85,		0.2, -0.4, 0.85,	0.2, -0.45, 0.475);
					drawTriangle(-0.2, -0.4, 0.85,		0.2, -0.45, 0.475,	-0.2, -0.45, 0.475);
					drawTriangle(-0.2, -0.45, 0.475,	0.2, -0.45, 0.475,	0.2, -0.65, 0.35);
					drawTriangle(-0.2, -0.45, 0.475,	0.2, -0.65, 0.35,	-0.2, -0.65, 0.35);
					drawTriangle(-0.2, -0.65, 0.35,		0.2, -0.65, 0.35,	0.2, -0.85, 0.6);
					drawTriangle(-0.2, -0.65, 0.35,		0.2, -0.85, 0.6,	-0.2, -0.85, 0.6);

					drawTriangle(0.2, -0.85, 0.6, 0.2, -0.675, 0.85,	0.2, -0.85, 0.7);
					drawTriangle(0.2, -0.85, 0.6, 0.2, -0.4, 0.85,		0.2, -0.675, 0.85);
					drawTriangle(0.2, -0.85, 0.6, 0.2, -0.45, 0.475,	0.2, -0.4, 0.85);
					drawTriangle(0.2, -0.85, 0.6, 0.2, -0.65, 0.35,		0.2, -0.45, 0.475);

					// beige top
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					drawTriangle(-0.2, 0.25, 0.8, -0.2, 0.25, 0.55,		-0.2, -0.25, 0.55);
					drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.25, 0.55,	-0.2, -0.25, 0.65);
					drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.25, 0.65,	-0.2, -0.1, 0.85);
					drawTriangle(-0.2, 0.25, 0.8, -0.2, -0.1, 0.85,		-0.2, 0.15, 0.9);
					drawTriangle(-0.2, 0.15, 0.9, -0.2, -0.1, 0.85,		-0.2, -0.1, 2.1);
					drawTriangle(-0.2, 0.15, 0.9, -0.2, -0.1, 2.1,		-0.2, 0.15, 2.1);

					drawTriangle(-0.2, 0.25, 0.55, 0.2, 0.25, 0.8, 0.2, 0.25, 0.55);
					drawTriangle(-0.2, 0.25, 0.55, -0.2, 0.25, 0.8, 0.2, 0.25, 0.8);
					drawTriangle(-0.2, 0.25, 0.8, 0.2, 0.15, 0.9, 0.2, 0.25, 0.8);
					drawTriangle(-0.2, 0.25, 0.8, -0.2, 0.15, 0.9, 0.2, 0.15, 0.9);
					drawTriangle(-0.2, 0.15, 0.9, 0.2, 0.15, 2.1, 0.2, 0.15, 0.9);
					drawTriangle(-0.2, 0.15, 0.9, -0.2, 0.15, 2.1, 0.2, 0.15, 2.1);
					drawTriangle(-0.2, 0.15, 2.1, 0.2, -0.1, 2.1, 0.2, 0.15, 2.1);
					drawTriangle(-0.2, 0.15, 2.1, -0.2, -0.1, 2.1, 0.2, -0.1, 2.1);
					drawTriangle(-0.2, -0.1, 2.1, 0.2, -0.1, 0.85, 0.2, -0.1, 2.1);
					drawTriangle(-0.2, -0.1, 2.1, -0.2, -0.1, 0.85, 0.2, -0.1, 0.85);
					drawTriangle(-0.2, -0.1, 0.85, 0.2, -0.25, 0.65, 0.2, -0.1, 0.85);
					drawTriangle(-0.2, -0.1, 0.85, -0.2, -0.25, 0.65, 0.2, -0.25, 0.65);
					drawTriangle(-0.2, -0.25, 0.65, 0.2, -0.25, 0.6, 0.2, -0.25, 0.65);
					drawTriangle(-0.2, -0.25, 0.65, -0.2, -0.25, 0.6, 0.2, -0.25, 0.6);
					drawTriangle(-0.2, -0.25, 0.6, 0.2, 0.25, 0.6, 0.2, -0.25, 0.6);
					drawTriangle(-0.2, -0.25, 0.6, -0.2, 0.25, 0.6, 0.2, 0.25, 0.6);

					drawTriangle(0.2, 0.25, 0.8, 0.2, -0.25, 0.55, 0.2, 0.25, 0.55);
					drawTriangle(0.2, 0.25, 0.8, 0.2, -0.25, 0.65, 0.2, -0.25, 0.55);
					drawTriangle(0.2, 0.25, 0.8, 0.2, -0.1, 0.85, 0.2, -0.25, 0.65);
					drawTriangle(0.2, 0.25, 0.8, 0.2, 0.15, 0.9, 0.2, -0.1, 0.85);
					drawTriangle(0.2, 0.15, 0.9, 0.2, -0.1, 2.1, 0.2, -0.1, 0.85);
					drawTriangle(0.2, 0.15, 0.9, 0.2, 0.15, 2.1, 0.2, -0.1, 2.1);

					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		
		// draw lower body
		glPushMatrix();
			// draw pelvis
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_OLIVE);
			glTranslated(-0.45, -0.9, -0.45);
			glScaled(0.9, 0.9, 0.9);
			drawBox(1, 1, 1);
			glPopMatrix();

			//draw left leg
			glPushMatrix();
			//draw joint
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0.0, -0.45, 0.0);
			glRotated(90 + VAL(LEFT_UPPER_LEG_Y_ROTATE), 0.0, 1.0, 0.0);
			drawCylinder(1.45, 0.25, 0.25);

			glTranslated(0.0, 0.0, 0.65);
			drawCylinder(0.8, 0.4, 0.4);
			glTranslated(0.0, 0.0, -0.65);
				
			glRotated(-90, 0.0, 1.0, 0.0);
				
				//draw left upper leg
				glPushMatrix();	

				glRotated(-VAL(LEFT_UPPER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
				glTranslated(0.65, -1.1, -0.3);

				drawBox(0.8, 1.25, 0.6);

					//draw left upper leg plates
					glPushMatrix();
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_BEIGE);
					glTranslated(-0.1, 0.0, 0.75);
					drawBox(1, 1.1, 0.25);

					glTranslated(0.0, 1.1, 0.0);
					drawTriangle(0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.25, 0.0);
					drawTriangle(0.0, 0.0, 0.25, 0.5, 0.0, 0.25, 0.5, 0.25, 0.25);
					drawTriangle(0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.5, 0.25, 0.25);
					drawTriangle(0.0, 0.0, 0.0, 0.5, 0.25, 0.25, 0.5, 0.25, 0.0);

					glTranslated(0.5, 0.0, 0.0);
					drawBox(0.5, 0.5, 0.25);
					glPopMatrix();


				//draw joint
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_GRAY);
				glTranslated(0.0, 0.0, 0.3);
				glRotated(90, 0.0, 1.0, 0.0);
				drawCylinder(0.8, 0.3, 0.3);
				glRotated(-90, 0.0, 1.0, 0.0);

					
					//draw left middle leg
					glPushMatrix();
					glRotated(VAL(LEFT_MIDDLE_LEG_X_ROTATE), 1.0, 0.0, 0.0);
					glTranslated(0.0, -1.25, -0.3);
					drawBox(0.8, 1.25, 0.6);

						//draw left middle leg plates
						glPushMatrix();
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_OLIVE);
						glTranslated(-0.1, 0.35, 0.75);
						drawBox(1, 0.9, 0.25);
						glPopMatrix();

					//draw joint
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					glTranslated(0.0, 0.0, 0.3);
					glRotated(90, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.35, 0.35);
					glRotated(-90, 0.0, 1.0, 0.0);



						//draw left lower leg
						glPushMatrix();
						glRotated(-VAL(LEFT_LOWER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
						glTranslated(0.0, -1.25, -0.3);
							//draw left lower leg
							glPushMatrix();
							glTranslated(0.075, 0.0, 0.05);
							drawBox(0.65, 1.25, 0.5);
							glPopMatrix();
							//draw left lower leg plates
							glPushMatrix();
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_OLIVE);
							glTranslated(-0.1, 0.0, 0.75);
							drawBox(1, 0.9, 0.25);
							glPopMatrix();

						//draw joint
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glTranslated(0.0, 0.0, 0.3);
						glRotated(90, 0.0, 1.0, 0.0);
						drawCylinder(0.8, 0.3, 0.3);
						glRotated(-90, 0.0, 1.0, 0.0);


							//draw left foot
							glPushMatrix();
							glRotated(VAL(LEFT_FOOT_X_ROTATE), 1.0, 0.0, 0.0);
							glTranslated(-0.225, -0.6, -0.75);

							//draw left foot
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_ORANGE);
							drawBox(1.25, 0.3, 1.5);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
							drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
							drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, -0.3, 1.25, 0.0, 0.0);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.3, -0.3, 1.25, 0.0, 0.0);
							drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
							drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

							glRotated(180, 0.0, 1.0, 0.0);
							glTranslated(-1.25, 0.0, -1.5);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
							drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
							drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.0, 0.0, 1.25, 0.0, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.0, 0.0, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
							drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

							glPopMatrix(); // finish foot

						glPopMatrix(); // finish lower leg

					glPopMatrix(); // finish middle leg

				glPopMatrix(); //finish upper leg

			glPopMatrix();// finish left leg



			//draw right leg
			glPushMatrix();
			//draw joint
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_GRAY);
			glTranslated(0.0, -0.45, 0.0);
			glRotated(-90 - VAL(RIGHT_UPPER_LEG_Y_ROTATE), 0.0, 1.0, 0.0);
			drawCylinder(1.45, 0.25, 0.25);

			glTranslated(0.0, 0.0, 0.65);
			drawCylinder(0.8, 0.4, 0.4);
			glTranslated(0.0, 0.0, -0.65);

			glRotated(90, 0.0, 1.0, 0.0);

				//draw right upper leg
				glPushMatrix();

				glRotated(-VAL(RIGHT_UPPER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
				glTranslated(-0.65-0.8, -1.1, -0.3);

				drawBox(0.8, 1.25, 0.6);

				//draw right upper leg plates
				glPushMatrix();
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_BEIGE);
				glTranslated(-0.1, 0.0, 0.75);
				drawBox(1, 1.1, 0.25);

				glTranslated(0.0, 1.1, 0.0);
				drawBox(0.5, 0.5, 0.25);

				glTranslated(0.5, 0.0, 0.0);
				drawTriangle(0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.25, 0.0);
				drawTriangle(0.0, 0.0, 0.25, 0.5, 0.0, 0.25, 0.0, 0.25, 0.25);
				drawTriangle(0.0, 0.25, 0.0, 0.5, 0.0, 0.25, 0.5, 0.0, 0.0);
				drawTriangle(0.0, 0.25, 0.25, 0.5, 0.0, 0.25, 0.0, 0.25, 0.0);
				glPopMatrix();


				//draw joint
				setAmbientColor(.1f, .1f, .1f);
				setDiffuseColor(COLOR_GRAY);
				glTranslated(0.0, 0.0, 0.3);
				glRotated(90, 0.0, 1.0, 0.0);
				drawCylinder(0.8, 0.3, 0.3);
				glRotated(-90, 0.0, 1.0, 0.0);


					//draw right middle leg
					glPushMatrix();
					glRotated(VAL(RIGHT_MIDDLE_LEG_X_ROTATE), 1.0, 0.0, 0.0);
					glTranslated(0.0, -1.25, -0.3);
					drawBox(0.8, 1.25, 0.6);

						//draw right middle leg plates
						glPushMatrix();
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_OLIVE);
						glTranslated(-0.1, 0.35, 0.75);
						drawBox(1, 0.9, 0.25);
						glPopMatrix();

					//draw joint
					setAmbientColor(.1f, .1f, .1f);
					setDiffuseColor(COLOR_GRAY);
					glTranslated(0.0, 0.0, 0.3);
					glRotated(90, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.35, 0.35);
					glRotated(-90, 0.0, 1.0, 0.0);



						//draw right lower leg
						glPushMatrix();
						glRotated(-VAL(RIGHT_LOWER_LEG_X_ROTATE), 1.0, 0.0, 0.0);
						glTranslated(0.0, -1.25, -0.3);
							//draw right lower leg
							glPushMatrix();
							glTranslated(0.075, 0.0, 0.05);
							drawBox(0.65, 1.25, 0.5);
							glPopMatrix();
							//draw right lower leg plates
							glPushMatrix();
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_OLIVE);
							glTranslated(-0.1, 0.0, 0.75);
							drawBox(1, 0.9, 0.25);
							glPopMatrix();

						//draw joint
						setAmbientColor(.1f, .1f, .1f);
						setDiffuseColor(COLOR_GRAY);
						glTranslated(0.0, 0.0, 0.3);
						glRotated(90, 0.0, 1.0, 0.0);
						drawCylinder(0.8, 0.3, 0.3);
						glRotated(-90, 0.0, 1.0, 0.0);


							//draw right foot
							glPushMatrix();
							glRotated(VAL(RIGHT_FOOT_X_ROTATE), 1.0, 0.0, 0.0);
							glTranslated(-0.225, -0.6, -0.75);

							//draw right foot
							setAmbientColor(.1f, .1f, .1f);
							setDiffuseColor(COLOR_ORANGE);
							drawBox(1.25, 0.3, 1.5);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
							drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
							drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, -0.3, 1.25, 0.0, 0.0);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.3, -0.3, 1.25, 0.0, 0.0);
							drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
							drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

							glRotated(180, 0.0, 1.0, 0.0);
							glTranslated(-1.25, 0.0, -1.5);
							drawTriangle(0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 0.0, 0.6, -0.3, 0.0, 0.3, -0.3);
							drawTriangle(1.25, 0.0, 0.0, 1.25, 0.3, -0.3, 1.25, 0.3, 0.0);
							drawTriangle(1.25, 0.3, 0.0, 1.25, 0.3, -0.3, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.0, 0.0, 1.25, 0.0, 0.0, 0.0, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.0, 0.0, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, 0.0, 1.25, 0.3, 0.0, 0.0, 0.6, -0.3);
							drawTriangle(0.0, 0.6, -0.3, 1.25, 0.3, 0.0, 1.25, 0.6, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 1.25, 0.6, -0.3, 1.25, 0.3, -0.3);
							drawTriangle(0.0, 0.3, -0.3, 0.0, 0.6, -0.3, 1.25, 0.6, -0.3);

							glPopMatrix(); // finish foot

						glPopMatrix(); // finish lower leg

					glPopMatrix(); // finish middle leg

				glPopMatrix(); //finish upper leg

			glPopMatrix();// finish left leg

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
	controls[LEFT_SHOULDER_X_ROTATE] = ModelerControl("Left Shoulder X Rotate", -70, 150, 1, 0);
	controls[LEFT_SHOULDER_Y_ROTATE] = ModelerControl("Left Shoulder Y Rotate", -30, 30, 1, 0);
	controls[LEFT_SHOULDER_Z_ROTATE] = ModelerControl("Left Shoulder Z Rotate", 0, 30, 1, 10);
	controls[LEFT_UPPER_ARM_Y_ROTATE] = ModelerControl("Left Upper Arm Y Rotate", -30, 90, 1, 0);
	controls[LEFT_LOWER_ARM_X_ROTATE] = ModelerControl("Left Lower Arm X Rotate", 0, 150, 1, 45);
	controls[LEFT_LOWER_ARM_Y_ROTATE] = ModelerControl("Left Lower Arm Y Rotate", -90, 90, 1, 0);
	controls[LEFT_WRIST_Z_ROTATE] = ModelerControl("Left Wrist Z Rotate", -90, 90, 1, 0);
	controls[THUMB_PROXIMAL_ROTATE] = ModelerControl("Thumb Proximal Phalanx Rotate", 0, 80, 1, 10);
	controls[THUMB_MIDDLE_ROTATE] = ModelerControl("Thumb Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[THUMB_DISTAL_ROTATE] = ModelerControl("Thumb Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_PROXIMAL_ROTATE] = ModelerControl("Index Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_MIDDLE_ROTATE] = ModelerControl("Index Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[INDEX_DISTAL_ROTATE] = ModelerControl("Index Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_PROXIMAL_ROTATE] = ModelerControl("Middle Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_MIDDLE_ROTATE] = ModelerControl("Middle Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[MIDDLE_DISTAL_ROTATE] = ModelerControl("Middle Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_PROXIMAL_ROTATE] = ModelerControl("Ring Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_MIDDLE_ROTATE] = ModelerControl("Ring Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[RING_DISTAL_ROTATE] = ModelerControl("Ring Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_PROXIMAL_ROTATE] = ModelerControl("Pinky Proximal Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_MIDDLE_ROTATE] = ModelerControl("Pinky Middle Phalanx Rotate", 0, 90, 1, 10);
	controls[PINKY_DISTAL_ROTATE] = ModelerControl("Pinky Distal Phalanx Rotate", 0, 90, 1, 10);
	controls[LEFT_UPPER_LEG_X_ROTATE] = ModelerControl("Left Upper Leg X Rotate", 0, 45, 1, 30);
	controls[LEFT_UPPER_LEG_Y_ROTATE] = ModelerControl("Left Upper Leg Y Rotate", -20, 20, 1, 15);
	controls[LEFT_MIDDLE_LEG_X_ROTATE] = ModelerControl("Left Middle Leg X Rotate", 0, 90, 1, 60);
	controls[LEFT_LOWER_LEG_X_ROTATE] = ModelerControl("Left Lower Leg X Rotate", 0, 60, 1, 40);
	controls[LEFT_FOOT_X_ROTATE] = ModelerControl("Left Foot X Rotate", -30, 30, 1, 10);
	controls[RIGHT_UPPER_LEG_X_ROTATE] = ModelerControl("Left Upper Leg X Rotate", 0, 45, 1, 30);
	controls[RIGHT_UPPER_LEG_Y_ROTATE] = ModelerControl("Left Upper Leg Y Rotate", -20, 20, 1, 15);
	controls[RIGHT_MIDDLE_LEG_X_ROTATE] = ModelerControl("Left Middle Leg X Rotate", 0, 90, 1, 60);
	controls[RIGHT_LOWER_LEG_X_ROTATE] = ModelerControl("Left Lower Leg X Rotate", 0, 60, 1, 40);
	controls[RIGHT_FOOT_X_ROTATE] = ModelerControl("Left Foot X Rotate", -30, 30, 1, 10);
	controls[LIGHT_TEST] = ModelerControl("Light Test", -30, 30, 1, 0);

	ModelerApplication::Instance()->Init(&createBastionModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
