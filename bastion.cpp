#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

#define COLOR_BEIGE 245.0f / 255.0f, 245.0f / 255.0f, 220.0f / 255.0f
#define COLOR_GRAY 105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f


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
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	// draw the bastion model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_BEIGE);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// draw body
		glPushMatrix();
		glTranslated(-1, 2.5, -0.5);
		glScaled(2, 1.5, 2.5);
		drawBox(1, 1, 1);
		// draw waist
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GRAY);
		glTranslated(0.5, -0.5, 0.375);
		glScaled(0.5, 1.0/1.5, 1.0/2.5);
		glRotated(-90, 1.0, 0, 0);
		drawCylinder(1, 0.5, 0.5);
		glPopMatrix();

		// draw head
		glPushMatrix();
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_BEIGE);
		glTranslated(-0.5, 4.5, 0);
		drawBox(1, 1, 1);
		// draw neck
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GRAY);
		glTranslated(0.05, -0.5, 0.25);
		glScaled(0.9, 1, 0.5);
		drawBox(1, 1, 1);
		glPopMatrix();

		// draw back turret
		glPushMatrix();
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_BEIGE); 
		glTranslated(0, 3, -1);
		glRotated(-90, 1.0, 0, 0);
		drawCylinder(0.75, 0.5, 0.5);

		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GRAY);
		glTranslated(0, 0, 0.75);
		drawCylinder(2.5, 0.4, 0.4);
		glPopMatrix();

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
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

	ModelerApplication::Instance()->Init(&createBastionModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}