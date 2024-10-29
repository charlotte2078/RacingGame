// CarRace_22072024.cpp: A program using the TL-Engine
// Charlotte Cleary

#include <TL-Engine11.h>	// TL-Engine include file and namespace
#include <sstream>		// for text on screen
#include <iostream>		// std::cout for debug to console
#include <fstream>		// for reading in level files
#include <vector>		// std::vector for storing level items

#include "CTank_LI.h"
#include "CWallSection_LI.h"
#include "CCheckpoint_LI.h"
#include "CollisionData.h"
#include "CHoverCar_Player.h"

using namespace tle;

const int gDisplayX = 1280;
const int gDisplayY = 720;
const float gDegreesToRadians = 3.1415927f / 180.0f;

int main()
{

	// Create a 3D engine (using TLX engine here) and open a window for it
	TLEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed(gDisplayX, gDisplayY);

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder(".\\Media");			// folder with media provided for assignment
	myEngine->AddMediaFolder(".\\AdditionalMedia"); // additional models/textures not provided

	/**** Set up your scene here ****/

	// meshes
	Mesh* checkpointMesh = myEngine->LoadMesh("Checkpoint.x");
	Mesh* isleMesh = myEngine->LoadMesh("IsleStraight.x");
	Mesh* wallMesh = myEngine->LoadMesh("Wall.x");
	Mesh* waterTankMesh = myEngine->LoadMesh("TankSmall1.x");
	Mesh* carMesh = myEngine->LoadMesh("race2.x");
	Mesh* skyboxMesh = myEngine->LoadMesh("Skybox 07.x");
	Mesh* floorMesh = myEngine->LoadMesh("ground.x");
	Mesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	Mesh* crossMesh = myEngine->LoadMesh("Cross.x");

	// skybox setup
	Model* skybox = skyboxMesh->CreateModel();
	skybox->SetPosition(0.0f, -960.0f, 0.0f);

	// floor setup
	Model* floor = floorMesh->CreateModel();

	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);

	// Camera for testing
	Camera* TestCam = myEngine->CreateCamera(ManualCamera);

	// Testing car movement without any collisions
	CHoverCar_Player PlayerCar(dummyMesh, carMesh, { 0.0f, 0.0f }, 0.0f);
	PlayerCar.AttachCamera(TestCam);

	//// Wall section testing
	//Vector2D WallPosition1(-10, 56); // no rotation
	//Vector2D WallPosition2(106, 46); // 90 degree rotation
	//Vector2D WallPosition3(50, 20);

	//CWallSection_LI Wall1(dummyMesh, wallMesh, isleMesh, WallPosition1, 0.0f);
	//CWallSection_LI Wall2(dummyMesh, wallMesh, isleMesh, WallPosition2, 90.0f);
	//CWallSection_LI Wall3(dummyMesh, wallMesh, isleMesh, WallPosition3, 50.0f);

	//// Checkpoint constructor testing
	//Vector2D CheckpointPos1(10, 120); // 90 degree rotation
	//Vector2D CheckpointPos2(25, 56); // 0 degree rotation
	//Vector2D CheckpointPos3(100, 100); // 45 degree rotation

	//CCheckpoint_LI CP1(checkpointMesh, CheckpointPos1, 90.0f, crossMesh, dummyMesh);
	//CCheckpoint_LI CP2(checkpointMesh, CheckpointPos2, 0.0f, crossMesh, dummyMesh);
	//CCheckpoint_LI CP3(checkpointMesh, CheckpointPos3, 45.0f, crossMesh, dummyMesh);


	//// Testing box colliders
	Model* TankTest = waterTankMesh->CreateModel(-10.0f, 0.0f, -25.0f);
	////CVector2D TestWidthDepth(20.0f, 50.0f);
	//CCollider_Box TankBoxColliderTest(TestWidthDepth, crossMesh, TankTest);
	CCollider_Sphere TankSphereColliderTest(10.0f, crossMesh, TankTest);

	CCollider_Box TestBoxCollider({ 20.0f, 20.0f }, crossMesh);
	TestBoxCollider.GetCentre()->MoveZ(50.0f);

	//Model* CarTest = carMesh->CreateModel();
	////CCollider_Sphere CarSphereColliderTest(kCarRadius, crossMesh, CarTest);
	//CCollider_Point CarPointColliderTest(crossMesh, CarTest);
	//const float TestCarSpeed = 10.0f;
	//const float TestCarRotate = 90.0f;
	//Camera* CarTestCam = myEngine->CreateCamera(ManualCamera);
	//CarTestCam->AttachToParent(CarTest);
	//CarTestCam->RotateX(20.0f);

	//// Testing HoverCar constructor
	//CHoverCar HoverCarTest1(dummyMesh, carMesh, { 0.0f, 0.0f }, 0.0f);
	//CHoverCar HoverCarTest2(dummyMesh, carMesh, { 20.0f, 0.0f }, 90.0f);
	//CHoverCar HoverCarTest3(dummyMesh, carMesh, { 0.0f, 50.0f }, 270.0f);

	// Testing player car collision with checkpoints - need a vec of checkpoints and a moveable player car.
	//std::vector<CCheckpoint_LI> CPVec;
	//CPVec.push_back(CP1);
	//CPVec.push_back(CP2);
	//CPVec.push_back(CP3);
	const int TotalLaps = 1;
	const EKeyCode Forwards = Key_W;
	const EKeyCode Backwards = Key_S;
	const EKeyCode Left = Key_A;
	const EKeyCode Right = Key_D;
	const EKeyCode Boost = Key_Space;
	//CHoverCar_Player PlayerCar(dummyMesh, carMesh, {0.0f, 0.0f}, 0.0f);

	// Main game loop
	while (myEngine->IsRunning())
	{
		// Draw frame
		myEngine->DrawScene();

		const float DeltaTime = myEngine->FrameTime();

		// Testing collisions with player car and the stationary box collider


		/*MyData.ResetData();*/

		//// Test collisions
		//if (MoveableCollider.SATBoxToBox(StationaryCollider, MyData))
		//{
		//	myFont->Draw("box collision detected", 10, 10, Black);

		//	// collision resolution
		//	MoveableCollider.GetCentre()->MoveX(MyData.Penetration * MyData.Normal.X);
		//	MoveableCollider.GetCentre()->MoveZ(MyData.Penetration * MyData.Normal.Y);
		//}

		//MyData.ResetData();

		//if (MoveableCollider.SATBoxToSphere(SphereCollider, MyData))
		//{
		//	myFont->Draw("sphere collision detected", 10, 10, Black);

		//	// collision resolution
		//	MoveableCollider.GetCentre()->MoveX(MyData.Penetration * MyData.Normal.X);
		//	MoveableCollider.GetCentre()->MoveZ(MyData.Penetration * MyData.Normal.Y);
		//}

		// Game logic!
		//check for key presses
		bool leftRotateKeyPress = false;
		bool rightRotateKeyPress = false;

		// car rotation control
		if (myEngine->KeyHeld(Left))		leftRotateKeyPress = true;
		if (myEngine->KeyHeld(Right))		rightRotateKeyPress = true;

		// car movement
		float thrustFactor = 0.0f;
		if (myEngine->KeyHeld(Forwards))
		{
			if (myEngine->KeyHeld(Backwards))
			{
				thrustFactor = 0.5f;
			}
			else
			{
				thrustFactor = 1.0f;
			}
		}
		else if (myEngine->KeyHeld(Backwards))
		{
			thrustFactor = -0.5f;
		}

		// process car boost
		bool boostKeyPress = false;
		if (myEngine->KeyHeld(Boost))
		{
			boostKeyPress = true;
		}

		PlayerCar.MovementEachFrame(DeltaTime, leftRotateKeyPress, rightRotateKeyPress, boostKeyPress, thrustFactor);
		
		// Check for collisions
		if (PlayerCar.TestSphereCollision(TankSphereColliderTest))
		{
			myFont->Draw("sphere collision detected", 10, 10, Black);
		}

		if (PlayerCar.TestBoxCollision(TestBoxCollider))
		{
			myFont->Draw("box collision detected", 10, 10, Black);
		}

		// Quit game
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
