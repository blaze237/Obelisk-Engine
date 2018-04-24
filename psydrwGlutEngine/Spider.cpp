#include "Spider.h"
#include "Vec2.h"


Spider::Spider(Vec3<float> pos, std::vector<Vec3<float>> velocities, long moveRate)
	:DisplayableObject(pos, Vec3<float>(2, 1, 2), "SPIDER"), velocities(velocities), moveRate(moveRate), bodyTex(Texture2D("../textures/spiderFur.png")), baseTex(Texture2D("../textures/spiderFur2.png"))
{
	kinematic = true;
	//Dont want it to be effected by gravity
	weightless = true;
	velocity = velocities[0];
	AllignSpider();

}


Spider::~Spider()
{
}

void Spider::Render()
{
	glPushMatrix();
	glScalef(0.8, 0.6, 1.2);
	//Draw thorax
	DrawBodyPart(bodyTex);
	glPopMatrix();
	//Draw abdomen
	glPushMatrix();
	glTranslatef(0, 0, -1.4);
	glScalef(0.8, 0.8, 1.2);
	DrawBodyPart(baseTex);
	glPopMatrix();
	
	
	glPushMatrix();
	for (int i = 0; i < 2; ++i)
	{
		//Leg 1
		glTranslatef(0.65, 0, 0.6);
		glPushMatrix();
		i == 0 ? glRotatef(leftLeg1Angle, 0, 1, 0) : glRotatef(-leftLeg1Angle, 0, 1, 0);
		glRotatef(legVertAngle, 0, 0, 1);
		DrawLeg();
		glPopMatrix();

		//leg 2
		glTranslatef(0, 0, -0.4);
		glPushMatrix();
		i == 0 ? glRotatef(leftLeg2Angle, 0, 1, 0) : glRotatef(-leftLeg2Angle, 0, 1, 0);
		glRotatef(-legVertAngle, 0, 0, 1);
		DrawLeg();
		glPopMatrix();

		//leg 3
		glTranslatef(0, 0, -0.3);
		glPushMatrix();
		i == 0 ? glRotatef(leftLeg1Angle, 0, 1, 0) : glRotatef(-leftLeg1Angle, 0, 1, 0);
		glRotatef(legVertAngle, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		DrawLeg();
		glPopMatrix();
		//leg 4
		glTranslatef(0, 0, -0.4);
		glPushMatrix();
		i == 0 ? glRotatef(leftLeg2Angle, 0, 1, 0) : glRotatef(-leftLeg2Angle, 0, 1, 0);
		glRotatef(-legVertAngle, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		DrawLeg();
		glPopMatrix();

		glPopMatrix();

		if (i == 0)
		{
			glPushMatrix();
			glRotatef(180, 0, 1, 0);
		}
	}

}
//minus to l1 + to 2
void Spider::Update(long tCurrent)
{
	//Update timer variables
	tSinceLegMove += (tCurrent - lastTime);
	tSinceLegMoveVert += (tCurrent - lastTime);
	tSinceVelChng += (tCurrent - lastTime);
	lastTime = tCurrent;

	//Check if its time to move the bats wings
	if (tSinceLegMove >= legMoveRate)
	{
		//Reset timer
		tSinceLegMove = 0;

		if (abs(leftLeg1Angle) <= legAngleMax)
		{
			leftLeg1Angle -= angleDelta;
			leftLeg2Angle += angleDelta;
		}
		else
		{
			angleDelta *= -1;
			leftLeg1Angle -= angleDelta;
			leftLeg2Angle += angleDelta;
		}
	}

	//Want peak of the vertical movemeent to be halway through the xz movement animantion
	//Check if its time to move the bats wings
	if (tSinceLegMoveVert >= legMoveRate)
	{
		//Reset timer
		tSinceLegMoveVert = 0;

		if (legVertAngle <= legVertAngleMax && vertAngleDelta > 0)
			legVertAngle += vertAngleDelta;	
		else if (legVertAngle > 0 && vertAngleDelta < 0)
			legVertAngle += vertAngleDelta;
		else
		{
			vertAngleDelta *= -1;
			legVertAngle += vertAngleDelta;
		}
	}

	//Check if its time to update the spiders velocity
	if (tSinceVelChng >= moveRate)
	{
		//Reset timer
		tSinceVelChng = 0;

		//Move to next velocity in the vector (circular)
		velIndex = velIndex < velocities.size() - 1 ? velIndex + 1 : 0;

		//Update bat velocity
		velocity = velocities[velIndex];

		AllignSpider();
	}
}

void Spider::AllignSpider()
{
	//Similar to the code for alligning sprite with cam view direction, but in this case, we wish to allign the normal of the front bbox to be parralell with the spiders normalised velocity

	//We only care about the component of the normal within the x-z plane, so just extract those parts
	Vec2<float> velDir(velocities[velIndex].x, velocities[velIndex].z);
	velDir.Normalise();

	//Get the bats current normal in world space
	Vec3<float> faceNorm = bBox.GetFaces()[0].normal;
	//We only care about the component of the normal within the x-z plane, so just extract those parts
	Vec2<float> curNorm = Vec2<float>(faceNorm.x, faceNorm.z);
	curNorm.Normalise();

	//If allready alligned, do nothing
	if (velDir == curNorm)
		return;

	//Use the dot product and determinent to get the sine and cosine of angle in y between our current normal and desired one
	float dot = curNorm.DotProd(velDir);
	float det = curNorm.Det(velDir);

	//If the bats face and its velocity are perpendicular then cannot align so break out
	if (dot == 0 && det == 0)
		return;

	//Get the angle
	float angle = MathHelp::ToDegrees(atan2(det, dot));
	//Rotate by this angle to align the normal
	orientation.y -= angle;
}

void Spider::DrawLeg()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_CULL_FACE);

	glPushMatrix();
	glRotatef(-70, 0, 0, 1);
	glRotatef(15, 0, 1, 0);
	glScalef(0.1, 0.6, 0.1);
	DrawLegSection(baseTex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.18, 0);
	glRotatef(-85, 0, 0, 1);
	glRotatef(15, 0, 1, 0);
	glScalef(0.1, 0.6, 0.1);
	DrawLegSection(baseTex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6, -0.95, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(15, 0, 1, 0);
	glScalef(0.1, 1.3, 0.1);
	DrawLegSection(baseTex);
	glPopMatrix();

	glPopAttrib();

}

void Spider::DrawLegSection(Texture2D& texture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());

	//Going to loop around the rim of cyldiner of height 1, radius 0.5 and angular some resolution
	float res = 0.05 * M_PI;
	float x = 0.5;
	float z = 0.f;
	float theta = 2 * M_PI;

	while (theta > 0)
	{
		//Precalc the next point around the circle as we need it to calculate the normals
		float xNext = 0.5 * cos(theta - res);
		float zNext = 0.5 * sin(theta - res);


		//Draw a vertical section of the cylinder
		glBegin(GL_QUADS);

		glNormal3f(x, 0, z);

		//Top and bottom of first part of this section
		glTexCoord2f((theta / (2.0 * M_PI)), 1);
		glVertex3f(x, 1, z);
		glTexCoord2f((theta / (2.0 * M_PI)), 0);
		glVertex3f(x, 0.f, z);

		//Move around the circle		
		theta -= res;
		x = xNext;
		z = zNext;
		glNormal3f(x, 0, z);

		//Bottom and top of second half of this section
		glTexCoord2f((theta / (2.0 * M_PI)), 0);
		glVertex3f(x, 0.f, z);
		glTexCoord2f((theta / (2.0 * M_PI)), 1);
		glVertex3f(x, 1, z);

		glEnd();
	}

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}

void Spider::DrawBodyPart(Texture2D& tex)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.getID());

	static const float resolution = 15;
	static const float texTilingX = 1;// 4;
	static const float texTilingZ = 1;// 6;

									  //Body is just a sphere
	float latStep = 2 * PI / resolution;
	float longStep = PI / resolution;


	for (int i = 0; i < resolution; ++i)
	{
		for (int j = 0; j < resolution; ++j)
		{
			//Get angles of lat and long for the two corners of this grid section
			float phi = i * latStep;
			float theta = j * longStep;
			float phiNext = MathHelp::Clamp((i + 1) * latStep, 0.f, (float)(2 * PI));
			float thetaNext = MathHelp::Clamp((j + 1) * longStep, 0.f, (float)PI);

			//Determine the four corners of this grid section using the spheres parametric equation
			Vec3<float> a = SphericalToCartesian(phi, theta);
			Vec3<float> b = SphericalToCartesian(phi, thetaNext);
			Vec3<float> c = SphericalToCartesian(phiNext, theta);
			Vec3<float> d = SphericalToCartesian(phiNext, thetaNext);

			//Plot the verticies
			glBegin(GL_TRIANGLES);

			glTexCoord2f((phi / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(a.x, a.y, a.z);
			glVertex3f(a.x, a.y, a.z);

			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(c.x, c.y, c.z);
			glVertex3f(c.x, c.y, c.z);

			glTexCoord2f((phi / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(b.x, b.y, b.z);
			glVertex3f(b.x, b.y, b.z);

			//Triangle 2
			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(d.x, d.y, d.z);
			glVertex3f(d.x, d.y, d.z);

			glTexCoord2f((phi / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(b.x, b.y, b.z);
			glVertex3f(b.x, b.y, b.z);

			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(c.x, c.y, c.z);
			glVertex3f(c.x, c.y, c.z);

			glEnd();

		}
	}

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);



}
