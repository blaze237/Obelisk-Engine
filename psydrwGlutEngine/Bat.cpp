#include "Bat.h"
#include "Vec2.h"


Bat::Bat(Vec3<float> pos, std::vector<Vec3<float>> velocities, long moveRate)
	:DisplayableObject(pos, Vec3<float>(4, 1, 2), "BAT"), velocities(velocities), moveRate(moveRate), bodyTex(Texture2D("../textures/batFur.png")), leftWingTex(Texture2D("../textures/batWingLeft.png")), rightWingTex(Texture2D("../textures/batWingRight.png"))
{
	kinematic = true;
	//Dont want it to be effected by gravity
	weightless = true;

	velocity = velocities[0];
	AllignBat();
}


Bat::~Bat()
{
}

void Bat::Render()
{
	//Draw the bats body. A strectched sphere
	glPushMatrix();
	glScalef(1, 1, 1.5);
	DrawBody();
	glPopMatrix();

	//Draw the wings. Each one is a two sided plane
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(-2.2, 0, 0.7);
	//Want to rotate about pivot point 
	glTranslatef(1.2, 0, 0);
	glRotatef(-wingAngle, 0, 0, 1);
	glTranslatef(-1.2, 0, 0);
	glScalef(3.4, 1.7, 1.7);
	glDisable(GL_CULL_FACE);
	DrawWing(leftWingTex);
	glPopAttrib();
	glPopMatrix();

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(2.2, 0, 0.7);
	//Want to rotate about pivot point 
	glTranslatef(-1.2, 0, 0);
	glRotatef(wingAngle, 0, 0, 1);
	glTranslatef(1.2, 0, 0);	
	glScalef(3.4, 1.7, 1.7);
	glDisable(GL_CULL_FACE);
	DrawWing(rightWingTex);
	glPopAttrib();
	glPopMatrix();

}

void Bat::Update(long tCurrent)
{

	//Update timer variables
	tSinceFlap += (tCurrent - lastTime);
	tSinceVelChng += (tCurrent - lastTime);
	lastTime = tCurrent;

	//Check if its time to move the bats wings
	if (tSinceFlap >= wingFlapRate)
	{
		//Reset timer
		tSinceFlap = 0;

		if (abs(wingAngle) < wingAngleMax)
			wingAngle += angleDelta;
		else
		{
			angleDelta *= -1;
			wingAngle += angleDelta;
		}
	}

	//Check if its time to update the bats velocity
	if (tSinceVelChng >= moveRate)
	{
		//Reset timer
		tSinceVelChng = 0;

		//Move to next velocity in the vector (circular)
		velIndex = velIndex < velocities.size() - 1 ? velIndex + 1 : 0;

		//Update bat velocity
		velocity = velocities[velIndex];

		AllignBat();
	}
}

void Bat::AllignBat()
{
	//Similar to the code for alligning sprite with cam view direction, but in this case, we wish to allign the normal of the front bbox to be parralell with the bats normalised velocity

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

void Bat::DrawWing(Texture2D & tex)
{
	static const float resolution = 2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.getID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	float step = 1.0f / resolution;
	for (int x = -resolution / 2; x < resolution / 2; ++x)
	{
		for (int z = -resolution / 2; z < resolution / 2; ++z)
		{

			//1
			glNormal3f(0, 1, 0);
			glTexCoord2f(((x + resolution / 2) * step), ((z + resolution / 2) * step + step));
			glVertex3f(x * step, 0, z * step + step);
			//2
			glTexCoord2f(((x + resolution / 2)* step + step), ((z + resolution / 2) * step + step));
			glVertex3f(x * step + step, 0, z * step + step);
			//3
			glTexCoord2f(((x + resolution / 2) * step + step), ((z + resolution / 2) * step));
			glVertex3f(x * step + step, 0, z* step);
			//4
			glTexCoord2f(((x + resolution / 2) * step), ((z + resolution / 2) * step));
			glVertex3f(x * step, 0, z * step);

		}
	}

	glEnd();

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}

void Bat::DrawBody()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bodyTex.getID());

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
