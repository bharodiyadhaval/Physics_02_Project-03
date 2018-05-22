#include"myPhysics.h"


//Get the string token and find it in the File and Get the cursor there
void myPhysics::ReadFileToToken(std::ifstream &file, std::string token)
{
	bool bKeepReading = true;
	std::string garbage;
	do
	{
		file >> garbage;		// Title_End??
		if (garbage == token)
		{
			return;
		}
	} while (bKeepReading);
	return;
}


//Read the Scene File and get the details for physics class instance
std::vector<myPhysics::PhysicsObject> myPhysics::InitializePhysics(std::string file)
{

	std::vector <PhysicsObject> myvec;
	PhysicsObject TempObj;
	std::ifstream SceneFile(file.c_str());

	if (!SceneFile.is_open())
	{	// Didn't open file, so return

	}


	ReadFileToToken(SceneFile, "models");
	int count;
	SceneFile >> count;

	for (int i = 1; i <= count; i++)
	{

		ReadFileToToken(SceneFile, std::to_string(i));
		ReadFileToToken(SceneFile, "position");
		SceneFile >> TempObj.pos.x;
		SceneFile >> TempObj.pos.y;
		SceneFile >> TempObj.pos.z;

		ReadFileToToken(SceneFile, "orientation");
		SceneFile >> TempObj.ori.x;
		SceneFile >> TempObj.ori.y;
		SceneFile >> TempObj.ori.z;


		ReadFileToToken(SceneFile, "orientation2");
		SceneFile >> TempObj.or2.x;
		SceneFile >> TempObj.or2.y;
		SceneFile >> TempObj.or2.z;

		ReadFileToToken(SceneFile, "scale");
		SceneFile >> TempObj.scale;

		ReadFileToToken(SceneFile, "color");
		SceneFile >> TempObj.color.a;
		SceneFile >> TempObj.color.r;
		SceneFile >> TempObj.color.g;
		SceneFile >> TempObj.color.b;

		ReadFileToToken(SceneFile, "name");
		SceneFile >> TempObj.name;

		ReadFileToToken(SceneFile, "type");
		SceneFile >> TempObj.typer;
		if (TempObj.typer == "sphere")
		{
			TempObj.type = eTypeOfObject::SPHERE;
		}
		else
		{
			TempObj.type = eTypeOfObject::PLANE;
		}

		ReadFileToToken(SceneFile, "physics");
		SceneFile >> TempObj.phys;

		myvec.push_back(TempObj);

	}
	return myvec;
}





//Main Physics method
void myPhysics::PhysicsStep(double deltaTime, force &wforce, force &sforce, force &leftforce, force &rightforce, force &upforce, std::vector<glm::vec3> &Displacement, std::vector<glm::vec3> &Rotation, std::vector<PhysicsObject> &PhysicsToGraphics, std::vector<int> &collision)
{
	

	if (collision.size() != PhysicsToGraphics.size())
	{
		for (int i = 0; i < PhysicsToGraphics.size(); i++)
		{
			collision.push_back(0);
		}
	}
	
	const glm::vec3 GRAVITY = glm::vec3(0.0f, -5.0f, 0.0f);
	for (int index = 0; index < PhysicsToGraphics.size(); index++)
	{

		PhysicsObject pCurGo = PhysicsToGraphics[index];
		if (!pCurGo.phys)
		{
			continue;
		}

		glm::vec3 a;
		a = (GRAVITY);
		glm::vec3 deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 2.0f)) + (a*(float)deltaTime)) / 4.0f;
		glm::vec3 deltaVelocity2 = ((float)deltaTime * a);
		if (index != 8)
		{

		}
		switch (pCurGo.type)
		{


		case eTypeOfObject::SPHERE:

			const float SURFACEOFGROUND = -1.5f;
			const float LEFTSIDEWALL = 14.5f;
			const float RIGHTSIDEWALL = -13.5f;

			const float BACKWALL = -13.5f;
			const float FRONTWALL = 14.5f;
			


			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Yellow Ball Moved with forces with this portion:

			if (index == 1)
			{
				if (wforce.on == 1 && collision[index] != 1)
				{
					a = (wforce.direction * wforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 6.0f;

					pCurGo.vel += deltaVelocity;


				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (sforce.on == 1 && collision[index] != 1)
				{
					a = (-wforce.direction * wforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 6.0f;

					pCurGo.vel += deltaVelocity;

				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (leftforce.on == 1 && collision[index] != 1)
				{
					a = (leftforce.direction * leftforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 4.0f;

					pCurGo.vel += deltaVelocity;

				}

				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (rightforce.on == 1 && collision[index] != 1)
				{
					a = (rightforce.direction * rightforce.strength * glm::vec3(1, 0, 1)) * 15.0f;
					deltaVelocity = ((a*(float)deltaTime / 4.0f) + ((a*(float)deltaTime / 2.0f)) + (3.0f*(a*(float)deltaTime / 4.0f)) + (a*(float)deltaTime)) / 4.0f;

					pCurGo.vel += deltaVelocity;

				}
				else
				{
					if (abs(pCurGo.vel.x) > 0 || abs(pCurGo.vel.z) > 0)
						pCurGo.vel -= pCurGo.vel  * glm::vec3(1, 0, 1) / 20.0f;
				}

				if (upforce.on == 1 && collision[index] != 1)
				{
					deltaVelocity += upforce.direction * upforce.strength;
					pCurGo.vel += deltaVelocity;
				}
				else
				{
					if ((pCurGo.vel.y) > 0)
						pCurGo.vel.y -= pCurGo.vel.y / 2.0f;
				}

				if (collision[index] == 1)
				{
					PhysicsToGraphics[index].vel = 5.0f*PhysicsToGraphics[index].vel*glm::vec3(1, 0, 1);
				}


			}

			//////////////////////////////////////////////////////////////////////////////////////////////////
			//Applies the ball spring forces to the balls:
			//int gridy=5, gridz=5;
			//float distance = 4;
			//float strength = 1;
			//for (int i = 6; i <= 6 + gridy * (gridz - 1); i += gridy)
			//{
			//	for (int j = i; j < i + gridy - 1; j++)
			//	{
			//		
			//		float dampdiff = abs(distance - glm::distance(PhysicsToGraphics[j].pos, PhysicsToGraphics[j + 1].pos)) / 50;
			//		if (glm::distance(PhysicsToGraphics[j].pos, PhysicsToGraphics[j + 1].pos) > 5.0f)
			//		{
			//			//PhysicsToGraphics[j].vel -= glm::normalize(PhysicsToGraphics[j].pos - PhysicsToGraphics[j + 1].pos) * PhysicsToGraphics[j].vel;
			//			PhysicsToGraphics[j].vel += glm::normalize(PhysicsToGraphics[j+1].pos - PhysicsToGraphics[j].pos) * strength * dampdiff;

			//			//PhysicsToGraphics[j+1].vel -= glm::normalize(PhysicsToGraphics[j+1].pos - PhysicsToGraphics[j].pos) * PhysicsToGraphics[j+1].vel;
			//			PhysicsToGraphics[j+1].vel += glm::normalize(PhysicsToGraphics[j].pos - PhysicsToGraphics[j+1].pos) * strength * dampdiff;
			//		}
			//		if (glm::distance(PhysicsToGraphics[j].pos, PhysicsToGraphics[j + 1].pos) < 5.0f)
			//		{

			//			PhysicsToGraphics[j].vel -= glm::normalize(PhysicsToGraphics[j + 1].pos - PhysicsToGraphics[j].pos) * strength* dampdiff;
			//			PhysicsToGraphics[j + 1].vel -= glm::normalize(PhysicsToGraphics[j].pos - PhysicsToGraphics[j + 1].pos) * strength* dampdiff;

			//		}
			//		if (glm::distance(PhysicsToGraphics[j].pos, PhysicsToGraphics[j + 1].pos) == 5.0f)
			//		{
			//			PhysicsToGraphics[j].vel -= PhysicsToGraphics[j].vel / 200.f;
			//			PhysicsToGraphics[j + 1].vel -= PhysicsToGraphics[j+1].vel / 200.f;
			//		}
			//	}
			//}
			














			//////////////////////////////////////////////////////////////////////////////////////////////////
			//Collision Detection and resolution
			for (int j = 0; j < PhysicsToGraphics.size(); j++)
			{
				if (PhysicsToGraphics[j].type == eTypeOfObject::SPHERE && index != j)
				{


					if (glm::distance(PhysicsToGraphics[index].pos, PhysicsToGraphics[j].pos) <= PhysicsToGraphics[index].scale + PhysicsToGraphics[j].scale)
					{


						//PhysicsToGraphics[j].vel += (PhysicsToGraphics[j].pos - PhysicsToGraphics[index].pos)*(float)deltaTime / 2.0f + PhysicsToGraphics[index].vel*(float)deltaTime;
						PhysicsToGraphics[j].vel += 0.1f*glm::normalize(PhysicsToGraphics[j].pos - PhysicsToGraphics[index].pos)*std::sqrt(PhysicsToGraphics[index].vel.x*PhysicsToGraphics[index].vel.x + PhysicsToGraphics[index].vel.z*PhysicsToGraphics[index].vel.z) ;
						

						
						collision[index] = 1;
						collision[j] = 1;
						//PhysicsToGraphics[index].vel += (PhysicsToGraphics[index].pos - PhysicsToGraphics[index].pos)*(float)deltaTime / 2.0f + PhysicsToGraphics[j].vel*(float)deltaTime;

					}
					else
					{

						if (abs(PhysicsToGraphics[j].vel.x) > 0 || abs(PhysicsToGraphics[j].vel.z) > 0)
						{
							PhysicsToGraphics[j].vel -= PhysicsToGraphics[j].vel  * glm::vec3(1, 0, 1) * PhysicsToGraphics[j].scale / 400.0f;
							collision[j] = 2;
						}



					}
				}
			}

			//

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Restrict the balls within the walls and floor
			if ((pCurGo.pos.y - pCurGo.scale / 2.0f) <= SURFACEOFGROUND && upforce.on == 0)
			{
				pCurGo.vel.y = 0;
				deltaVelocity.y = 0;
			}

			if ((pCurGo.pos.x - pCurGo.scale / 2.0f) <= RIGHTSIDEWALL && (float)deltaTime*pCurGo.vel.x < 0)
			{
				pCurGo.vel.x = 0;
				deltaVelocity.x = 0;
			}

			if ((pCurGo.pos.x - pCurGo.scale / 2.0f) >= LEFTSIDEWALL && (float)deltaTime*pCurGo.vel.x > 0)
			{
				pCurGo.vel.x = 0;
				deltaVelocity.x = 0;

			}

			if ((pCurGo.pos.z - pCurGo.scale / 2.0f) <= BACKWALL && (float)deltaTime*pCurGo.vel.z < 0)
			{
				pCurGo.vel.z = 0;
				deltaVelocity.z = 0;
			}

			if ((pCurGo.pos.z - pCurGo.scale / 2.0f) >= FRONTWALL && (float)deltaTime*pCurGo.vel.z > 0)
			{
				pCurGo.vel.z = 0;
				deltaVelocity.z = 0;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//Control penitration for the user controlled ball
			if (collision[index] == 1 && index == 1)
			{
				PhysicsToGraphics[index].vel = -PhysicsToGraphics[index].vel*glm::vec3(1, 0, 1);
			}


			//Accumulate the values
			pCurGo.vel = pCurGo.vel + deltaVelocity;

			glm::vec3 deltaPosition = (float)deltaTime * pCurGo.vel;

			//Hold the balls upright for the springs
			//And change the color to see the strands differently
			if (index==6 || index == 11 || index == 16 || index == 21 || index == 26 )
			{
				if (index == 6)
				{
					for (int i = index; i < index + 5; i++)
					{
						PhysicsToGraphics[i].color = glm::vec4(1, 0, 0, 1);
					}
				}
				if (index == 11)
				{
					for (int i = index; i < index + 5; i++)
					{
						PhysicsToGraphics[i].color = glm::vec4(1, 1, 0, 1);
					}
				}
				if (index == 16)
				{
					for (int i = index; i < index + 5; i++)
					{
						PhysicsToGraphics[i].color = glm::vec4(1, 0, 1, 1);
					}
				}
				if (index == 21)
				{
					for (int i = index; i < index + 5; i++)
					{
						PhysicsToGraphics[i].color = glm::vec4(0, 0, 1, 1);
					}
				}
					
				

			}
			else
			{
				Rotation[index] = (glm::cross(glm::vec3(0, 1, 0), deltaPosition) / 2.0f);
				Displacement[index] = (deltaPosition);
				PhysicsToGraphics[index].vel = pCurGo.vel;
				PhysicsToGraphics[index].pos += deltaPosition;
				PhysicsToGraphics[index].or2 += ((glm::cross(glm::vec3(0, 1, 0), deltaPosition) / 2.0f));

				if (deltaPosition.x <= 0.001f && deltaPosition.z <= 0.001f)
				{
					collision[index] = 0;
				}
			}
			
			break;
		};

	}

	return;
}



