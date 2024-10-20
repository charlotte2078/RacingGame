// CarRace_22072024.cpp: A program using the TL-Engine
// Charlotte Cleary G21107528

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

	// Box colliders for testing
	CCollider_Box MoveableCollider({ 10.0f, 10.0f }, crossMesh);
	TestCam->AttachToParent(MoveableCollider.GetCentre());
	TestCam->SetLocalPosition(0.0f, 60.0f, 0.0f);
	TestCam->RotateX(90.0f);
	MoveableCollider.GetCentre()->MoveZ(-50.0f);
	CollisionData MyData;
	/*CCollider_Box StationaryCollider({ 50.0f, 70.0f }, crossMesh);
	StationaryCollider.GetCentre()->RotateY(50.0f);*/

	// Sphere collider for testing
	Model* TestTank = waterTankMesh->CreateModel(0.0f, 0.0f, -70.0f);
	CCollider_Sphere SphereCollider(10.0f, crossMesh, TestTank);
	

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
	//Model* TankTest = waterTankMesh->CreateModel(-10.0f, 0.0f, -25.0f);
	////CVector2D TestWidthDepth(20.0f, 50.0f);
	////CCollider_Box TankBoxColliderTest(TestWidthDepth, crossMesh, TankTest);
	//CCollider_Sphere TankSphereColliderTest(10.0f, crossMesh, TankTest);

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

		// Testing collisions between two box colliders
		if (myEngine->KeyHeld(Forwards))
		{
			MoveableCollider.GetCentre()->MoveZ(DeltaTime * 20.0f);
		}
		if (myEngine->KeyHeld(Backwards))
		{
			MoveableCollider.GetCentre()->MoveZ(-DeltaTime * 20.0f);
		}
		if (myEngine->KeyHeld(Left))
		{
			MoveableCollider.GetCentre()->MoveX(-DeltaTime * 20.0f);
		}
		if (myEngine->KeyHeld(Right))
		{
			MoveableCollider.GetCentre()->MoveX(DeltaTime * 20.0f);
		}

		/*MyData.ResetData();*/

		//// Test collisions
		//if (MoveableCollider.SATBoxToBox(StationaryCollider, MyData))
		//{
		//	myFont->Draw("box collision detected", 10, 10, Black);

		//	// collision resolution
		//	MoveableCollider.GetCentre()->MoveX(MyData.Penetration * MyData.Normal.X);
		//	MoveableCollider.GetCentre()->MoveZ(MyData.Penetration * MyData.Normal.Y);
		//}

		MyData.ResetData();

		if (MoveableCollider.SATBoxToSphere(SphereCollider, MyData))
		{
			myFont->Draw("sphere collision detected", 10, 10, Black);

			// collision resolution
			MoveableCollider.GetCentre()->MoveX(MyData.Penetration * MyData.Normal.X);
			MoveableCollider.GetCentre()->MoveZ(MyData.Penetration * MyData.Normal.Y);
		}

		//// Game logic!
		////check for key presses
		//bool leftRotateKeyPress = false;
		//bool rightRotateKeyPress = false;

		//// car rotation control
		//if (myEngine->KeyHeld(Left))		leftRotateKeyPress = true;
		//if (myEngine->KeyHeld(Right))		rightRotateKeyPress = true;

		//// car movement
		//float thrustFactor = 0.0f;
		//if (myEngine->KeyHeld(Forwards))
		//{
		//	if (myEngine->KeyHeld(Backwards))
		//	{
		//		thrustFactor = 0.5f;
		//	}
		//	else
		//	{
		//		thrustFactor = 1.0f;
		//	}
		//}
		//else if (myEngine->KeyHeld(Backwards))
		//{
		//	thrustFactor = -0.5f;
		//}

		//// process car boost
		//bool boostKeyPress = false;
		//if (myEngine->KeyHeld(Boost))
		//{
		//	boostKeyPress = true;
		//}

		//PlayerCar.MovementEachFrame(DeltaTime, leftRotateKeyPress, rightRotateKeyPress, boostKeyPress, thrustFactor, CPVec, TotalLaps, WallsVec);

		// Quit game
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

////////////////////// STATES SETUP //////////////////////////////////////////
//
//enum EGameState { gPreRace, gRacing, gRaceOver };
//enum EPreRaceStates { prInitial, prTimer };
//enum EBoxSide { leftSide, rightSide, frontSide, backSide, noSide };
//enum ECameraState { camChase, camFirstPerson };
//
////////////////////// GLOBAL CONSTANTS //////////////////////////////////////
//
//const int kDisplayX = 1280;
//const int kDisplayY = 720;
//
//// scaling constants
//const float kDegreesToRadians = 3.1415927f / 180.0f;
//const float kModelScale = 0.3f; // in metres/TL-Engine unit
//const float kKmPerHourFactor = 3.6f; // to convert from m/s to km/h
//
//// car constants
//// MOVED TO CHoverCar_Player.h
//const int kCarHealthMinBoost = 30;
//const int kCarDefaultHealth = 100;
//const float kCarDefaultRotationSpeed = 90.0f;
//const float kCarDragCoefficient = 1.5f;
//const float kCarMaxBoostTime = 3.0f;
//const float kCarBoostMaxMultiplier = 1.5f;
//const float kCarDragMaxMultiplier = 2.0f;
//const float kCarRadius = 3.0f;
//const float kCarMaxThrustMagnitude = 100.0f;
//const float kCarBoostMaxCooldownTime = 5.0f;
//const float kCarBoostWarningTime = 1.0f;
//const float kCarBounceCoefficient = 0.8f;
//
//// car bobble/tilt/lift constants
//// MOVED TO CHoverCar.h
//const float kCarMinY = 0.0f;
//const float kCarMaxY = 0.3f;
//const float kCarBobbleSpeed = 0.2f;
//const float kCarTiltSpeed = 3.5f;		// degrees/sec
//const float kCarTiltReturnSpeed = 5.0f;	// degrees/sec
//const float kCarTiltLimit = 5.0f;		// degrees
//const float kCarLiftSpeed = 8.0f;		// degrees/sec
//const float kCarLiftReturnSpeed = 4.0f;	// degrees/sec
//const float kCarLiftUpperLimit = 5.0f;	// degrees
//const float kCarLiftLowerLimit = -2.0f;	// degrees
//
//// npc car constants
//const std::string npcCarSkinName = "carNPCSkin.jpg";
//const float npcDefaultSpeed = 30.0f;
//const float npcMaxBounceTime = 1.0f;
//const float npcAcc = 10.0f;
//const float kNpcWaypointPrecision = 1.0f;
//
//// MOVED TO CTank_LI
//// tank constants
//const float kTankSinkHeight = -8.0f;
//const float kTankRadius = 3.0f;
//
//// MOVED TO CCheckpoint_LI
//// checkpoint constants
//const float kStrutRadius = 1.3f;
//const float kDistCpToStrut = 8.56f;
//const int kNumStrutsPerCheckpoint = 2;
//const float kCpWidth = 14.52f;
//const float kCpDepth = 2.6f;
//
//// MOVED TO CCross
//const float kCrossLifeTimer = 2.0f;
//const float kCrossVisibleHeight = 5.0f;
//const float kCrossHiddenHeight = -20.0f;
//const float kCrossScaleFactor = 0.5f;
//
//// wall/isle constants
//// MOVED TO CWallSection_LI
//const float kWallColliderWidth = 5.0f;
//const float kWallColliderDepth = 38.3f;
//
///////////////////////////// STRUCTURES //////////////////////////////////////
//
//struct SLevelItem
//{
//	std::string type;
//	float xPos;
//	float zPos;
//	float yRotation;
//};
//
//struct SVector3D
//{
//	float x;
//	float y;
//	float z;
//};
//
//// Will be replaced by CVector2D
//struct SVector2D
//{
//	float x;
//	float y;
//
//	float magnitude() { return sqrt(x * x + y * y); }
//
//	float squareMagnitude() { return (x * x + y * y); }
//};
//
//// adds two Vector2D together and returns the result
//// WILL BE REPLACED BY OPERATOR OVERLOADING IN CVECTOR2D
//SVector2D Vector2DAddition(const SVector2D& vec1, const SVector2D& vec2)
//{
//	return { vec1.x + vec2.x, vec1.y + vec2.y };
//}
//
//// subtracts Vector2D vec2 from Vector2D vec1 and returns the result
//// WILL BE REPLACED BY OPERATOR OVERLOADING IN CVECTOR2D
//SVector2D Vector2DSubtraction(const SVector2D& vec1, const SVector2D& vec2)
//{
//	return { vec1.x - vec2.x, vec1.y - vec2.y };
//}
//
//// multiplies a Vector2D by a scalar float and returns the result
//// DEPRECATED BY CVector2D
//SVector2D ScalarMultiplication(const float& k, SVector2D vec)
//{
//	vec.x *= k;
//	vec.y *= k;
//
//	return vec;
//}
//
//// calculates the dot product of two Vector2D and returns the result
//// DEPRECATED BY CVector2D
//float DotProduct(const SVector2D& vec1, const SVector2D& vec2)
//{
//	return vec1.x * vec2.x + vec1.y * vec2.y;
//}
//
//// normalises a Vector2D and returns the result
//// DEPRECATED BY CVector2D
//SVector2D NormaliseVector2D(SVector2D vec)
//{
//	const float length = vec.magnitude();
//	vec.x /= length;
//	vec.y /= length;
//
//	return vec;
//}
//
//// DEPRECATED BY CCollider_Box
//struct SBoxCollider
//{
//	SVector2D posXZ;
//	SVector2D widthDepth;
//};
//
//// DEPRECATED BY CCross
//struct SCross
//{
//	IModel* model;
//	float lifeTimer;
//	bool isVisible;
//};
//
//// DEPRECATED BY CCheckpoint
//struct SCheckpoint
//{
//	SVector2D position;
//	float rotation;
//	IModel* model;
//	SVector2D strutsPos[kNumStrutsPerCheckpoint];
//	SCross cross;
//	float width;
//	float depth;
//};
//
//// TO BE DEPRECATED BY CWaypoint
//struct SWaypoint
//{
//	IModel* dummyModel;
//	SVector2D position;
//	float speed;
//};

//////////////////////////////// FUNCTION PROTOTYPES ///////////////////////////////////
//
//void OpenFile(std::ifstream&, const std::string&);
//void CloseFile(std::ifstream&);
//void ReadWholeFileLineByLine(std::ifstream& readFile, std::vector <SLevelItem>& v);
//void CameraRotation(ICamera*& camera, const float& x, const float& y);
//float DistanceXZModel(IModel*, IModel*);
//bool PointToBoxXZ(IModel*, IModel*, const float&, const float&);
//bool SphereToBoxXZ(IModel*, IModel*, const float&, const float&, const float&);
//float DistanceXZPoints(const SVector2D&, const SVector2D&);
//bool SphereToSphereXZ(const SVector2D&, const SVector2D&, const float&, const float&);
//EBoxSide EnhancedSphereToBoxXZ(IModel*, const SVector2D&, const float&, const SVector2D&, const SVector2D&);
//bool SphereToSphereXZModel(IModel*, IModel*, const float&, const float&);
//SVector2D ReflectVectorInVector(const SVector2D&, const SVector2D&);

//////////////////////////////// CAR CLASS//////////////////////////////////////////////
//
//class CCar
//{
//protected:
//	IModel* mDummyModel;
//	IModel* mModel;
//	SVector2D mInitalPos;
//	float mInitialRotation;
//	SVector2D mFacingVec;
//	SVector2D mMomentumVec;
//	int mHealth;
//	float mRotationSpeed;
//	std::vector <SWaypoint> mWaypointsVec;
//	int mWaypointCounter;
//	int mCheckpointCounter;
//	int mLapCounter;
//
//	// protected methods
//	void CheckCurrentWaypoint();
//	void MoveToInitialPosRot();
//
//public:
//	// constructors
//	CCar();
//	CCar(IMesh*, IMesh*, const SVector2D&, const float&);
//
//	// destructor
//	~CCar();
//
//	// getters
//	IModel* GetDummyModel() const { return mDummyModel; };
//	IModel* GetModel() const { return mModel; };
//	SVector2D GetMomentumVec() const { return mMomentumVec; };
//	int GetHealth() const { return mHealth; };
//	int GetCheckpointCounter() const { return mCheckpointCounter; };
//	int GetLapCounter() const { return mLapCounter; };
//
//	// other public methods
//	void SetWaypointsVec(const std::vector <SWaypoint>&);
//};
//
//// default constructor
//CCar::CCar() :
//	mDummyModel(nullptr),
//	mModel(nullptr),
//	mHealth(kCarDefaultHealth),
//	mRotationSpeed(kCarDefaultRotationSpeed),
//	mWaypointCounter(0),
//	mCheckpointCounter(0),
//	mLapCounter(0)
//{
//	// base inital pos and rotation is 0
//	mInitalPos = { 0.0f, 0.0f };
//	mInitialRotation = 0.0f;
//	mMomentumVec = { 0.0f, 0.0f };
//	mFacingVec = { 0.0f, 1.0f };
//}
//
//// constructor with meshes, inital pos, initial rot passed in
//CCar::CCar(IMesh* dummyMesh, IMesh* carMesh, const SVector2D& pos, const float& rot) :
//	mHealth(kCarDefaultHealth),
//	mRotationSpeed(kCarDefaultRotationSpeed),
//	mInitalPos(pos),
//	mInitialRotation(rot),
//	mWaypointCounter(0),
//	mCheckpointCounter(0),
//	mLapCounter(0)
//{
//	mMomentumVec = { 0.0f, 0.0f };
//	mFacingVec = { sin(rot * kDegreesToRadians), cos(rot * kDegreesToRadians) };
//
//	// create dummy model and move to initial pos and rotation
//	mDummyModel = dummyMesh->CreateModel(mInitalPos.x, 0.0f, mInitalPos.y);
//	mDummyModel->RotateY(mInitialRotation);
//
//	// create car model and attach it to dummy model
//	mModel = carMesh->CreateModel();
//	mModel->AttachToParent(mDummyModel);
//}
//
//// destructor does nothing
//CCar::~CCar()
//{
//
//}
//
//// Sets the car waypoints vec to the waypoints vec passed in
//void CCar::SetWaypointsVec(const std::vector <SWaypoint>& levelWPVec)
//{
//	mWaypointsVec = levelWPVec;
//}
//
//// Checks for the car passing the current wawypoint. If it does then increases the waypoint counter.
//void CCar::CheckCurrentWaypoint()
//{
//	if (DistanceXZPoints({ mDummyModel->GetX(), mDummyModel->GetZ() },
//		mWaypointsVec.at(mWaypointCounter).position) <= kNpcWaypointPrecision)
//	{
//		mWaypointCounter++;
//
//		// reset so goes around the track forever
//		if (mWaypointCounter == mWaypointsVec.size())
//		{
//			mWaypointCounter = 0;
//		}
//	}
//}
//
//void CCar::MoveToInitialPosRot()
//{
//	mDummyModel->SetX(mInitalPos.x);
//	mDummyModel->SetZ(mInitalPos.y);
//	mModel->ResetOrientation();
//	mDummyModel->ResetOrientation();
//	mDummyModel->RotateY(mInitialRotation);
//}
//
////////////////////////////// NPC CAR CLASS////////////////////////////////
//
//class CNpcCar : public CCar
//{
//private:
//	float mMaxMoveSpeed;
//	bool mIsMovingForward;
//	float mBounceTimer;
//	float mCurrentMoveSpeed;
//	float mCurrentAcc;
//
//	// private methods
//	void CheckBounceTimer();
//	void DecreaseBounceTimer(const float&);
//	void SetSkin(const std::string&);
//
//public:
//	// constructors
//	CNpcCar();
//	CNpcCar(IMesh*, IMesh*, const SVector2D&, const float&);
//
//	// destructor
//	~CNpcCar();
//
//	// other public methods
//	void ProcessMovement(const float&);
//	void Bounce(const float&);
//	void Reset();
//};
//
//// default constructor
//CNpcCar::CNpcCar() :
//	mMaxMoveSpeed(npcDefaultSpeed),
//	mIsMovingForward(true),
//	mBounceTimer(npcMaxBounceTime),
//	mCurrentMoveSpeed(0.0f),
//	mCurrentAcc(npcAcc)
//{
//
//}
//
//// constructor with dummy mesh, car mesh, initial pos, initial rot passed in
//CNpcCar::CNpcCar(IMesh* dummyMesh, IMesh* carMesh, const SVector2D& pos, const float& rot) :
//	CCar(dummyMesh, carMesh, pos, rot),
//	mMaxMoveSpeed(npcDefaultSpeed),
//	mIsMovingForward(true),
//	mBounceTimer(npcMaxBounceTime),
//	mCurrentMoveSpeed(0.0f),
//	mCurrentAcc(npcAcc)
//{
//	mModel->SetSkin(npcCarSkinName);
//}
//
//// destructor - takes no action
//CNpcCar::~CNpcCar()
//{
//
//}
//
//// Sets skin of NPC car
//void CNpcCar::SetSkin(const std::string& skin)
//{
//	mModel->SetSkin(npcCarSkinName);
//}
//
//// The NPC car looks towards the next waypoint and moves along its local Z axis until it reaches it.
//// The speed it moves at depends on the waypoint's max speed. It will accelerate/decelerate to meet this
//// speed.
//void CNpcCar::ProcessMovement(const float& deltaTime)
//{
//	// look at current waypoint
//	mDummyModel->LookAt(mWaypointsVec.at(mWaypointCounter).dummyModel);
//
//	// get max speed
//	if (mIsMovingForward)
//	{
//		mCurrentAcc = npcAcc;
//		mMaxMoveSpeed = mWaypointsVec.at(mWaypointCounter).speed;
//	}
//	else
//	{
//		mCurrentAcc = 5.0f * npcAcc;
//		mMaxMoveSpeed = 0.0f;
//	}
//
//	// accelerate/decelerate appropriatley
//	if (mCurrentMoveSpeed < mMaxMoveSpeed)	mCurrentMoveSpeed += npcAcc * deltaTime;
//	else if (mCurrentMoveSpeed > mMaxMoveSpeed)	mCurrentMoveSpeed -= npcAcc * deltaTime;
//
//	// move car forwards or backwards
//	if (mIsMovingForward)
//	{
//		mDummyModel->MoveLocalZ(mCurrentMoveSpeed * deltaTime);
//	}
//	else
//	{
//		mDummyModel->MoveLocalZ(-mCurrentMoveSpeed * deltaTime);
//		DecreaseBounceTimer(deltaTime);
//	}
//
//	CheckCurrentWaypoint();
//}
//
//// Makes the npc car move backwards
//void CNpcCar::Bounce(const float& deltaTime)
//{
//	mIsMovingForward = false;
//	ProcessMovement(deltaTime);
//}
//
//// Decreases the time for npc bounce.
//void CNpcCar::DecreaseBounceTimer(const float& deltaTime)
//{
//	mBounceTimer -= deltaTime;
//
//	CheckBounceTimer();
//}
//
//// Checks for the bounce timer running out. If it does, it resets the timer to max
//// and lets the car move forwards again
//void CNpcCar::CheckBounceTimer()
//{
//	if (mBounceTimer <= 0.0f)
//	{
//		mIsMovingForward = true;
//		mBounceTimer = npcMaxBounceTime;
//	}
//}
//
//// Resets the npc car to its initial state so the race can restart.
//void CNpcCar::Reset()
//{
//	MoveToInitialPosRot();
//	mFacingVec = mFacingVec = { sin(mInitialRotation * kDegreesToRadians), cos(mInitialRotation * kDegreesToRadians) };
//	mMomentumVec = { 0.0f, 0.0f };
//	mHealth = kCarDefaultHealth;
//	mWaypointCounter = 0;
//	mCheckpointCounter = 0;
//	mLapCounter = 0;
//	mMaxMoveSpeed = npcDefaultSpeed;
//	mIsMovingForward = true;
//	mBounceTimer = npcMaxBounceTime;
//	mCurrentMoveSpeed = 0.0f;
//	mCurrentAcc = 0.0f;
//}
//
//////////////////////////// PLAYER CAR CLASS //////////////////////////////
//
//class CPlayerCar : public CCar
//{
//private:
//	bool mIsAlive;				//= true;
//	bool mCanBoost;				//= true;
//	bool mIsBoosting;			//= false;
//	bool mIsBoostCooldown;		//= false;
//	float mBoostMultiplier;		//= 1.0f;
//	float mBoostTimer;			//= 0.0f;
//	float mBoostCooldownTimer;	//= 0.0f;
//	float mDragMultiplier;		//= 1.0f;
//	bool mIsMovingUp;			//= true;
//	float mTiltAngle;			//= 0.0f;
//	float mLiftAngle;			//= 0.0f;
//
//	// private methods
//	SVector2D CalculateThrust(const float&);
//	void CalculateNewMomentum(const float&, const float&);
//	void MoveByMomentum(const float&);
//	void UpdateFacingVector();
//	SVector2D CalculateDrag();
//	void ProcessBoost(const bool&, const float&);
//	void Bobble(const float&);
//	void ProcessRotation(const bool&, const bool&, const float&);
//	void Tilt(const float&, const bool&, const bool&);
//	void CheckHealth();
//	void Lift(const float&, const float&);
//	void CheckWaypoints();
//	void CheckpointCollision(std::vector <SCheckpoint>&, const float&, EGameState&);
//	void CheckpointStrutsCollision(std::vector <SCheckpoint>&, const SVector2D&, EGameState&);
//	void WallCollision(std::vector <SBoxCollider>&, const SVector2D&, EGameState&);
//	void TanksCollision(std::vector <IModel*>, const SVector2D&, EGameState&);
//	void NpcCollision(const CNpcCar&, const SVector2D&, EGameState&);
//	void TakeDamage();
//	void TakeDamageCheckEndGame(EGameState&);
//
//public:
//	// constructors
//	CPlayerCar();
//	CPlayerCar(IMesh*, IMesh*, const SVector2D&, const float&);
//
//	// destructor
//	~CPlayerCar();
//
//	// getters
//	bool GetIsAlive() const { return mIsAlive; };
//	bool GetIsBoosting() const { return mIsBoosting; };
//	float GetBoostTimer() const { return mBoostTimer; };
//	float GetBoostCooldownTimer() const { return mBoostCooldownTimer; };
//	bool GetBoostIsCooldown() const { return mIsBoostCooldown; };
//
//	// other public methods
//	void MovementEachFrame(const float&, const bool&, const bool&, const bool&, const float&,
//		std::vector <SCheckpoint>&, const float&,
//		EGameState&, std::vector <SBoxCollider>&, std::vector <IModel*>, const CNpcCar&);
//	void Reset();
//};
//
//// constructor - gives initial values to all attributes
//CPlayerCar::CPlayerCar() :
//	mIsAlive(true),
//	mCanBoost(true),
//	mIsBoosting(false),
//	mIsBoostCooldown(false),
//	mBoostMultiplier(1.0f),
//	mBoostTimer(0.0f),
//	mBoostCooldownTimer(0.0f),
//	mDragMultiplier(1.0f),
//	mIsMovingUp(true),
//	mTiltAngle(0.0f),
//	mLiftAngle(0.0f)
//{
//
//}
//
//// constructor with meshes, inital pos, initla rot passed in
//CPlayerCar::CPlayerCar(IMesh* dummyMesh, IMesh* carMesh, const SVector2D& pos, const float& rot) :
//	CCar(dummyMesh, carMesh, pos, rot),
//	mIsAlive(true),
//	mCanBoost(true),
//	mIsBoosting(false),
//	mIsBoostCooldown(false),
//	mBoostMultiplier(1.0f),
//	mBoostTimer(0.0f),
//	mBoostCooldownTimer(0.0f),
//	mDragMultiplier(1.0f),
//	mIsMovingUp(true),
//	mTiltAngle(0.0f),
//	mLiftAngle(0.0f)
//{
//
//}
//
//// destructor - takes no action
//CPlayerCar::~CPlayerCar()
//{
//
//}
//
//// Reduces player health by 1. Calls CheckHealth()
//void CPlayerCar::TakeDamage()
//{
//	mHealth--;
//
//	CheckHealth();
//}
//
//// Checks player health to see if player is alive and if they can boost
//void CPlayerCar::CheckHealth()
//{
//	if (mHealth < 0)
//	{
//		mIsAlive = false;
//	}
//	else if (mHealth < kCarHealthMinBoost)
//	{
//		mCanBoost = false;
//	}
//}
//
//// Calculates thrust for the frame (in direction of facing vector)
//SVector2D CPlayerCar::CalculateThrust(const float& thrustFactor)
//{
//	return ScalarMultiplication(thrustFactor * kCarMaxThrustMagnitude * mBoostMultiplier, mFacingVec);
//}
//
//// Calculates drag for the frame (in opposite direction to momentum)
//SVector2D CPlayerCar::CalculateDrag()
//{
//	return ScalarMultiplication(-kCarDragCoefficient * mDragMultiplier, mMomentumVec);
//}
//
//// Calculates new momentum using resultant force, multiplies force by deltaTime
//void CPlayerCar::CalculateNewMomentum(const float& deltaTime, const float& thrustFactor)
//{
//	SVector2D resultantForce = Vector2DAddition(CalculateDrag(), CalculateThrust(thrustFactor));
//	mMomentumVec = Vector2DAddition(ScalarMultiplication(deltaTime, resultantForce), mMomentumVec);
//}
//
//// Moves the car using its momentum vector multiplied by deltaTime
//void CPlayerCar::MoveByMomentum(const float& deltaTime)
//{
//	mDummyModel->MoveX(mMomentumVec.x * deltaTime);
//	mDummyModel->MoveZ(mMomentumVec.y * deltaTime);
//}
//
//// Updates the facing vector for the car
//void CPlayerCar::UpdateFacingVector()
//{
//	float matrix[4][4];
//	mDummyModel->GetMatrix(&matrix[0][0]);
//
//	mFacingVec = { matrix[2][0],matrix[2][2] };
//}
//
//// Changes boost timers and multipliers. If the player can boost and they press the boost key,
//// the max. thrust is increased by kCarBoostMaxMultiplier. They can only boost for a limited time,
//// (determined by kCarMaxBoostTime). If the player boosts for too long the drag is doubled for a time
//// (kCarBoostMaxCooldownTime)
//void CPlayerCar::ProcessBoost(const bool& boostKeyPress, const float& deltaTime)
//{
//	// process states
//	if (boostKeyPress)
//	{
//		if (mCanBoost && !mIsBoostCooldown)
//		{
//			mIsBoosting = true;
//		}
//		else
//		{
//			mIsBoosting = false;
//		}
//	}
//	else
//	{
//		mIsBoosting = false;
//		mBoostMultiplier = 1.0f;
//	}
//
//	// process boost timers
//	if (mIsBoosting)
//	{
//		mBoostTimer += deltaTime;
//		mBoostMultiplier = kCarBoostMaxMultiplier;
//
//		// check if boost timer exceeds max - if it does then set mIsBoostCooldown true & set mBoostCooldownTimer to max
//		if (mBoostTimer >= kCarMaxBoostTime)
//		{
//			mIsBoostCooldown = true;
//			mBoostCooldownTimer = kCarBoostMaxCooldownTime;
//			mBoostTimer = 0.0f;
//			mDragMultiplier = kCarDragMaxMultiplier;
//			mBoostMultiplier = 1.0f;
//		}
//	}
//	else if (mIsBoostCooldown)
//	{
//		mBoostCooldownTimer -= deltaTime;
//		// check for the cooldown running out of time!
//		if (mBoostCooldownTimer <= 0)
//		{
//			mIsBoostCooldown = false;
//			mDragMultiplier = 1.0f;
//		}
//	}
//	else // !mIsBoosting && !mIsBoostCooldown
//	{
//		if (mBoostTimer > 0.0f)
//		{
//			mBoostTimer -= deltaTime;
//		}
//	}
//
//}
//
//// The car bobs up and down slowly
//void CPlayerCar::Bobble(const float& deltaTime)
//{
//	if (mIsMovingUp)
//	{
//		mModel->MoveY(kCarBobbleSpeed * deltaTime);
//
//		if (mModel->GetY() >= kCarMaxY)
//		{
//			mIsMovingUp = false;
//		}
//	}
//	else // !mIsMovingUp
//	{
//		mModel->MoveY(-kCarBobbleSpeed * deltaTime);
//
//		if (mModel->GetY() <= kCarMinY)
//		{
//			mIsMovingUp = true;
//		}
//	}
//}
//
//// The car rotates left/right when the player presses the left/right keys
//void CPlayerCar::ProcessRotation(const bool& leftKeyPress, const bool& rightKeyPress, const float& deltaTime)
//{
//	if (leftKeyPress)	mDummyModel->RotateY(-kCarDefaultRotationSpeed * deltaTime);
//	if (rightKeyPress)	mDummyModel->RotateY(kCarDefaultRotationSpeed * deltaTime);
//}
//
//// The car tilts slowly left/right when the player steers left/right
//void CPlayerCar::Tilt(const float& deltaTime, const bool& rightKeyPress, const bool& leftKeyPress)
//{
//	//steering right tilt
//	if (rightKeyPress && mTiltAngle >= -kCarTiltLimit)
//	{
//		mModel->RotateZ(-kCarTiltSpeed * deltaTime);
//		mTiltAngle -= kCarTiltSpeed * deltaTime;
//	}
//	else if (mTiltAngle <= 0.0f)
//	{
//		mModel->RotateZ(kCarTiltReturnSpeed * deltaTime);
//		mTiltAngle += kCarTiltReturnSpeed * deltaTime;
//	}
//
//	//steering left tilt
//	if (leftKeyPress && mTiltAngle <= kCarTiltLimit)
//	{
//		mModel->RotateZ(kCarTiltSpeed * deltaTime);
//		mTiltAngle += kCarTiltSpeed * deltaTime;
//	}
//	else if (mTiltAngle >= 0.0f)
//	{
//		mModel->RotateZ(-kCarTiltReturnSpeed * deltaTime);
//		mTiltAngle -= kCarTiltReturnSpeed * deltaTime;
//	}
//}
//
//// The car leans up slightly at the front when accelerating, and back slightly when decelerating
//void CPlayerCar::Lift(const float& deltaTime, const float& thrustFactor)
//{
//	if (thrustFactor > 0.0f)
//	{
//		if (mLiftAngle <= kCarLiftUpperLimit)
//		{
//			mModel->RotateX(kCarLiftSpeed * deltaTime);
//			mLiftAngle += kCarLiftSpeed * deltaTime;
//		}
//	}
//	else if (thrustFactor < 0.0f)
//	{
//		if (mLiftAngle >= kCarLiftLowerLimit)
//		{
//			mModel->RotateX(-kCarLiftSpeed * deltaTime);
//			mLiftAngle -= kCarLiftSpeed * deltaTime;
//		}
//	}
//	else // thrustFactor == 0.0f
//	{
//		if (mLiftAngle >= 0.0f)
//		{
//			mModel->RotateX(-kCarLiftReturnSpeed * deltaTime);
//			mLiftAngle -= kCarLiftReturnSpeed * deltaTime;
//		}
//		else if (mLiftAngle <= 0.0f)
//		{
//			mModel->RotateX(kCarLiftReturnSpeed * deltaTime);
//			mLiftAngle += kCarLiftReturnSpeed * deltaTime;
//		}
//	}
//}
//
//// Checks if the game should end when the car takes damage
//void CPlayerCar::TakeDamageCheckEndGame(EGameState& gameState)
//{
//	TakeDamage();
//
//	if (!mIsAlive)
//	{
//		gameState = gRaceOver;
//	}
//}
//
//// Check for collisions with <counter> checkpoint (point to box)
//void CPlayerCar::CheckpointCollision(std::vector <SCheckpoint>& cpVec, const float& numLaps, EGameState& gameState)
//{
//	if (PointToBoxXZ(mDummyModel, cpVec.at(mCheckpointCounter).model, cpVec.at(mCheckpointCounter).width, cpVec.at(mCheckpointCounter).depth))
//	{
//		// make cross appear
//		cpVec.at(mCheckpointCounter).cross.lifeTimer = kCrossLifeTimer;
//		cpVec.at(mCheckpointCounter).cross.model->SetY(kCrossVisibleHeight);
//		cpVec.at(mCheckpointCounter).cross.isVisible = true;
//
//		// increase checkpoint counter
//		mCheckpointCounter++;
//
//		// reset checkpoint counter to 0 when a lap completes and increase lap counter.
//		if (mCheckpointCounter == cpVec.size())
//		{
//			mLapCounter++;
//			mCheckpointCounter = 0;
//
//			// check for finishing the race
//			if (mLapCounter == numLaps)
//			{
//				gameState = gRaceOver;
//			}
//		}
//	}
//}
//
//// Check for collisions with struts of checkpoints (sphere to sphere)
//void CPlayerCar::CheckpointStrutsCollision(std::vector <SCheckpoint>& cpVec, const SVector2D& oldCarPos, EGameState& gameState)
//{
//	for (int i = 0; i < cpVec.size(); i++)
//	{
//		const SVector2D carCurrentPos = { mDummyModel->GetX(), mDummyModel->GetZ() };
//
//		for (int j = 0; j < kNumStrutsPerCheckpoint; j++)
//		{
//			if (SphereToSphereXZ(carCurrentPos, cpVec.at(i).strutsPos[j], kCarRadius, kStrutRadius))
//			{
//				// resolve collision
//				mDummyModel->SetX(oldCarPos.x);
//				mDummyModel->SetZ(oldCarPos.y);
//
//				// bounce the car - reflect the current momentum in the vector that is normal to the tangent at point of collision
//				SVector2D strutToCarVec = Vector2DSubtraction(carCurrentPos, cpVec.at(i).strutsPos[j]);
//				mMomentumVec = ScalarMultiplication(kCarBounceCoefficient, ReflectVectorInVector(mMomentumVec, strutToCarVec));
//
//				// car takes damage
//				TakeDamageCheckEndGame(gameState);
//			}
//		}
//	}
//}
//
//// enhanced collision with walls (enhanced sphere to box)
//void CPlayerCar::WallCollision(std::vector <SBoxCollider>& wallColliders, const SVector2D& oldCarPos, EGameState& gameState)
//{
//	for (int i = 0; i < wallColliders.size(); i++)
//	{
//		const EBoxSide collisionSide = EnhancedSphereToBoxXZ(mDummyModel, wallColliders.at(i).posXZ, kCarRadius,
//			wallColliders.at(i).widthDepth, oldCarPos);
//
//		if (collisionSide != noSide)
//		{
//			// car takes damage
//			TakeDamageCheckEndGame(gameState);
//
//			// reverse appropriate momentum component based on collision side
//			if (collisionSide == leftSide || collisionSide == rightSide)
//			{
//				mDummyModel->SetX(oldCarPos.x);
//
//				// change momentum vector - reverse x momentum
//				mMomentumVec.x *= -kCarBounceCoefficient;
//			}
//			else if (collisionSide == frontSide || collisionSide == backSide)
//			{
//				mDummyModel->SetZ(oldCarPos.y);
//
//				// change momentum vector - reverse z momentum
//				mMomentumVec.y *= -kCarBounceCoefficient;
//			}
//		}
//	}
//}
//
//// check for collisions with water tanks (sphere to sphere)
//void CPlayerCar::TanksCollision(std::vector <IModel*> tanksVec, const SVector2D& oldCarPos, EGameState& gameState)
//{
//	for (int i = 0; i < tanksVec.size(); i++)
//	{
//		const SVector2D carCurrentPos = { mDummyModel->GetX(), mDummyModel->GetZ() };
//
//		if (SphereToSphereXZModel(mDummyModel, tanksVec.at(i), kCarRadius, kTankRadius))
//		{
//			// resolve collision
//			mDummyModel->SetX(oldCarPos.x);
//			mDummyModel->SetZ(oldCarPos.y);
//
//			// bounce the car - reflect the current momentum in the vector that is normal to the tangent at point of collision
//			SVector2D tankPos = { tanksVec.at(i)->GetX(), tanksVec.at(i)->GetZ() };
//			SVector2D tankToCarVec = Vector2DSubtraction(carCurrentPos, tankPos);
//			mMomentumVec = ScalarMultiplication(kCarBounceCoefficient, ReflectVectorInVector(mMomentumVec, tankToCarVec));
//
//			// car takes damage
//			TakeDamageCheckEndGame(gameState);
//		}
//	}
//}
//
//// check for collisions with npc car (sphere to sphere)
//void CPlayerCar::NpcCollision(const CNpcCar& npcCar, const SVector2D& oldCarPos, EGameState& gameState)
//{
//	if (SphereToSphereXZModel(mDummyModel, npcCar.GetModel(), kCarRadius, kCarRadius))
//	{
//		// car takes damage
//		TakeDamageCheckEndGame(gameState);
//
//		// reset position of player car
//		mDummyModel->SetX(oldCarPos.x);
//		mDummyModel->SetZ(oldCarPos.y);
//
//		// get npc car pos
//		const SVector2D npcCarPos = { npcCar.GetModel()->GetX(), npcCar.GetModel()->GetZ() };
//
//		// bounce the player car
//		const SVector2D npcToPlayerVec = Vector2DSubtraction(oldCarPos, npcCarPos);
//		mMomentumVec = ScalarMultiplication(kCarBounceCoefficient, ReflectVectorInVector(mMomentumVec, npcToPlayerVec));
//	}
//}
//
//// Calls all movement and collision functions for the player car in the appropriate order
//void CPlayerCar::MovementEachFrame(const float& deltaTime, const bool& leftKeyPress, const bool& rightKeyPress,
//	const bool& boostKeyPress, const float& thrustFactor, std::vector <SCheckpoint>& cpVec, const float& numLaps,
//	EGameState& gameState, std::vector <SBoxCollider>& wallColliders, std::vector <IModel*> tanksVec,
//	const CNpcCar& npcCar)
//{
//	const SVector2D oldCarPos = { mDummyModel->GetX(),mDummyModel->GetZ() };
//
//	// base movement
//	ProcessRotation(leftKeyPress, rightKeyPress, deltaTime);
//	UpdateFacingVector();
//	ProcessBoost(boostKeyPress, deltaTime);
//	CalculateNewMomentum(deltaTime, thrustFactor);
//	MoveByMomentum(deltaTime);
//	Bobble(deltaTime);
//	Tilt(deltaTime, rightKeyPress, leftKeyPress);
//	Lift(deltaTime, thrustFactor);
//
//	// collisions
//	WallCollision(wallColliders, oldCarPos, gameState);
//	CheckpointCollision(cpVec, numLaps, gameState);
//	CheckpointStrutsCollision(cpVec, oldCarPos, gameState);
//	TanksCollision(tanksVec, oldCarPos, gameState);
//	NpcCollision(npcCar, oldCarPos, gameState);
//}
//
//// Resets player car attributes for race reset
//void CPlayerCar::Reset()
//{
//	// move to initial position/rotation
//	MoveToInitialPosRot();
//
//	// reset attributes
//	mIsAlive = true;
//	mCanBoost = true;
//	mIsBoosting = false;
//	mIsBoostCooldown = false;
//	mBoostMultiplier = 1.0f;
//	mBoostTimer = 0.0f;
//	mBoostCooldownTimer = 0.0f;
//	mDragMultiplier = 1.0f;
//	mIsMovingUp = true;
//	mTiltAngle = 0.0f;
//	mLiftAngle = 0.0f;
//	mMomentumVec = { 0.0f, 0.0f };
//	mHealth = kCarDefaultHealth;
//	mWaypointCounter = 0;
//	mCheckpointCounter = 0;
//	mLapCounter = 0;
//	mFacingVec = mFacingVec = { sin(mInitialRotation * kDegreesToRadians), cos(mInitialRotation * kDegreesToRadians) };
//}



	//// read checkpoints, walls, isles, from file into a vector of <SLevelItem>
	//std::vector <SLevelItem> levelItemsVec;
	//const std::string level1FileName = "level1.txt";
	//std::ifstream level1ReadFile;
	//OpenFile(level1ReadFile, level1FileName);
	//ReadWholeFileLineByLine(level1ReadFile, levelItemsVec);
	//CloseFile(level1ReadFile);

	//// vectors for checkpoints, walls, isles
	//std::vector <SCheckpoint> checkpointsVec;
	//std::vector <IModel*> wallsVec;
	//std::vector <IModel*> islesVec;
	//std::vector <IModel*> tanksVec;
	//std::vector <SWaypoint> levelWaypointsVec;
	//std::vector <SBoxCollider> wallColliders;

	//// for reading in from file
	//SVector2D playerInitialPos;
	//float playerInitialRot;
	//SVector2D npcInitialPos;
	//float npcInitialRot;

	//// use levelItemsVec to load items into the game
	//for (int i = 0; i < levelItemsVec.size(); i++)
	//{
	//	if (levelItemsVec.at(i).type == "Checkpoint")
	//	{
	//		// add to checkpointsVec with SCheckpoint
	//		checkpointsVec.push_back({ {levelItemsVec.at(i).xPos, levelItemsVec.at(i).zPos},
	//										levelItemsVec.at(i).yRotation,
	//										checkpointMesh->CreateModel() });

	//		const int cpIndex = checkpointsVec.size() - 1;

	//		// move checkpoint to correct position
	//		checkpointsVec.at(cpIndex).model->SetX(checkpointsVec.at(cpIndex).position.x);
	//		checkpointsVec.at(cpIndex).model->SetZ(checkpointsVec.at(cpIndex).position.y);

	//		// rotate checkpoint
	//		checkpointsVec.at(cpIndex).model->RotateY(checkpointsVec.at(cpIndex).rotation);

	//		// create struts
	//		checkpointsVec.at(cpIndex).strutsPos[0].x = checkpointsVec.at(cpIndex).position.x -
	//			kDistCpToStrut * cos(checkpointsVec.at(cpIndex).rotation * kDegreesToRadians);
	//		checkpointsVec.at(cpIndex).strutsPos[1].x = checkpointsVec.at(cpIndex).position.x +
	//			kDistCpToStrut * cos(checkpointsVec.at(cpIndex).rotation * kDegreesToRadians);
	//		checkpointsVec.at(cpIndex).strutsPos[0].y = checkpointsVec.at(cpIndex).position.y +
	//			kDistCpToStrut * sin(checkpointsVec.at(cpIndex).rotation * kDegreesToRadians);
	//		checkpointsVec.at(cpIndex).strutsPos[1].y = checkpointsVec.at(cpIndex).position.y -
	//			kDistCpToStrut * sin(checkpointsVec.at(cpIndex).rotation * kDegreesToRadians);

	//		// add to checkpointsWidthDepth and struts
	//		if (levelItemsVec.at(i).yRotation == 90.0f)
	//		{
	//			checkpointsVec.at(cpIndex).width = kCpDepth;
	//			checkpointsVec.at(cpIndex).depth = kCpWidth;
	//		}
	//		else
	//		{
	//			checkpointsVec.at(cpIndex).width = kCpWidth;
	//			checkpointsVec.at(cpIndex).depth = kCpDepth;
	//		}

	//		// create cross
	//		checkpointsVec.at(cpIndex).cross.model = crossMesh->CreateModel(checkpointsVec.at(cpIndex).position.x, kCrossHiddenHeight, checkpointsVec.at(cpIndex).position.y);
	//		checkpointsVec.at(cpIndex).cross.model->RotateY(checkpointsVec.at(cpIndex).rotation);
	//		checkpointsVec.at(cpIndex).cross.model->Scale(kCrossScaleFactor);
	//		checkpointsVec.at(cpIndex).cross.isVisible = false;
	//		checkpointsVec.at(cpIndex).cross.lifeTimer = 0.0f;
	//	}
	//	else if (levelItemsVec.at(i).type == "Isle")
	//	{
	//		// add new isle to islesVec
	//		islesVec.push_back(isleMesh->CreateModel());

	//		const int islesIndex = islesVec.size() - 1;

	//		// move isle to correct position
	//		islesVec.at(islesIndex)->SetX(levelItemsVec.at(i).xPos);
	//		islesVec.at(islesIndex)->SetZ(levelItemsVec.at(i).zPos);

	//		// rotate isle
	//		islesVec.at(islesIndex)->RotateY(levelItemsVec.at(i).yRotation);
	//	}
	//	else if (levelItemsVec.at(i).type == "Wall")
	//	{
	//		// add new wall to wallsVec
	//		wallsVec.push_back(wallMesh->CreateModel());

	//		const int wallsIndex = wallsVec.size() - 1;

	//		// move wall to correct position
	//		wallsVec.at(wallsIndex)->SetX(levelItemsVec.at(i).xPos);
	//		wallsVec.at(wallsIndex)->SetZ(levelItemsVec.at(i).zPos);

	//		// rotate wall
	//		wallsVec.at(wallsIndex)->RotateY(levelItemsVec.at(i).yRotation);
	//	}
	//	else if (levelItemsVec.at(i).type == "TankSmall1")
	//	{
	//		// add new tank to tanksVec
	//		tanksVec.push_back(waterTankMesh->CreateModel());

	//		const int tanksIndex = tanksVec.size() - 1;

	//		tanksVec.at(tanksIndex)->SetX(levelItemsVec.at(i).xPos);
	//		tanksVec.at(tanksIndex)->SetZ(levelItemsVec.at(i).zPos);

	//		// obstacle tanks
	//		if (levelItemsVec.at(i).yRotation != 0.0f)
	//		{
	//			tanksVec.at(tanksIndex)->RotateX(levelItemsVec.at(i).yRotation);
	//			tanksVec.at(tanksIndex)->SetY(kTankSinkHeight);
	//		}
	//	}
	//	else if (levelItemsVec.at(i).type == "Waypoint")
	//	{
	//		// add new waypoint to waypointsVec
	//		SWaypoint newWaypoint;
	//		newWaypoint.dummyModel = dummyMesh->CreateModel();
	//		newWaypoint.dummyModel->SetX(levelItemsVec.at(i).xPos);
	//		newWaypoint.dummyModel->SetZ(levelItemsVec.at(i).zPos);
	//		newWaypoint.position = { levelItemsVec.at(i).xPos, levelItemsVec.at(i).zPos };
	//		newWaypoint.speed = levelItemsVec.at(i).yRotation;

	//		levelWaypointsVec.push_back(newWaypoint);
	//	}
	//	else if (levelItemsVec.at(i).type == "WallCollider")
	//	{
	//		// add new BoxCollider to wallColliders vector
	//		SBoxCollider newCollider;
	//		newCollider.posXZ = { levelItemsVec.at(i).xPos, levelItemsVec.at(i).zPos };
	//		if (levelItemsVec.at(i).yRotation == 90.0f)
	//		{
	//			newCollider.widthDepth = { kWallColliderDepth, kWallColliderWidth };
	//		}
	//		else
	//		{
	//			newCollider.widthDepth = { kWallColliderWidth, kWallColliderDepth };
	//		}

	//		wallColliders.push_back(newCollider);
	//	}
	//	else if (levelItemsVec.at(i).type == "Player")
	//	{
	//		// get player initial position and rotation
	//		playerInitialPos = { levelItemsVec.at(i).xPos, levelItemsVec.at(i).zPos };
	//		playerInitialRot = levelItemsVec.at(i).yRotation;
	//	}
	//	else if (levelItemsVec.at(i).type == "NPC")
	//	{
	//		// get npc initial position and rotation
	//		npcInitialPos = { levelItemsVec.at(i).xPos, levelItemsVec.at(i).zPos };
	//		npcInitialRot = levelItemsVec.at(i).yRotation;
	//	}
	//}

	//// skybox setup
	//SVector3D skyboxPos = { 0.0f, -960.0f, 0.0f };
	//IModel* skybox = skyboxMesh->CreateModel();
	//skybox->SetPosition(skyboxPos.x, skyboxPos.y, skyboxPos.z);

	//// floor setup
	//IModel* floor = floorMesh->CreateModel();

	//// ui backdrop setup
	//const SVector2D backdropPos = { 0.0f, 620.0f };
	//ISprite* uiBackground = myEngine->CreateSprite("ui_background.jpg", backdropPos.x, backdropPos.y);

	//// ui text setup
	//IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);
	//const std::string preRaceString = "Hit space to start";
	//const std::string timerString[] = { "GO!", "1", "2", "3" };
	//const std::string raceOverString = "Race complete";
	//const std::string carDiedString = "YOU DIED";
	//const std::string restartString = "Press R to Restart";
	//const SVector2D gameStateTextPos = { 640.0f, 670.0f };
	//const SVector2D timerTextPos = { 640.0f, 700.0f };
	//const SVector2D speedReadoutTextPos = { 262.0f, 620.0f };
	//const SVector2D healthTextPos = { 262.0f, 670.0f };
	//const SVector2D boostReadoutTextPos = { 1164.0f, 645.0f };
	//const SVector2D boostWarningTextPos = { 1164.0f, 695.0f };
	//const SVector2D lapTextPos = { 10.0f, 620.0f };
	//const SVector2D cpTextPos = { 10.0f, 670.0f };
	//const SVector2D posTextPos = { 962.0f, 670.0f };
	//const SVector2D restartStringPos = { 640.0f, 640.0f };

	//// camera
	//ICamera* camera = myEngine->CreateCamera(kManual);
	//const SVector3D camChaseLocalPos = { 0.0f, 10.0f, -20.0f };
	//const SVector3D camFirstPersonLocalPos = { 0.0f, 6.0f, 0.0f };
	//const float cameraSpeed = 5.0f;
	//const float cameraRotationSpeed = 180.0f; // in degrees / sec
	//const float cameraInitialXRotation = 15.0f; // in degrees
	//const float cameraXRotationLimitLower = -90.0f;
	//const float cameraXRotationLimitUpper = 90.0f;
	//float cameraXRotation = cameraInitialXRotation;
	//float cameraYRotation = 0.0f;
	//camera->RotateX(cameraInitialXRotation);
	//bool isMouseCapture = true;
	//myEngine->StartMouseCapture();

	//// player car setup
	//CPlayerCar playerCar(dummyMesh, carMesh, playerInitialPos, playerInitialRot);
	//playerCar.SetWaypointsVec(levelWaypointsVec);

	//// attach camera to player car
	//camera->AttachToParent(playerCar.GetDummyModel());
	//camera->SetLocalPosition(camChaseLocalPos.x, camChaseLocalPos.y, camChaseLocalPos.z);
	//ECameraState cameraState = camChase;

	//// npc player car setup
	//CNpcCar npcCar(dummyMesh, carMesh, npcInitialPos, npcInitialRot);
	//npcCar.SetWaypointsVec(levelWaypointsVec);

	//// control keys
	//const EKeyCode quitKey = Key_Escape;
	//const EKeyCode cameraForwardKey = Key_Up;
	//const EKeyCode cameraBackwardKey = Key_Down;
	//const EKeyCode cameraRightKey = Key_Right;
	//const EKeyCode cameraLeftKey = Key_Left;
	//const EKeyCode carForwardKey = Key_W;
	//const EKeyCode carBackwardKey = Key_S;
	//const EKeyCode carRightKey = Key_D;
	//const EKeyCode carLeftKey = Key_A;
	//const EKeyCode mouseCaptureKey = Key_Tab;
	//const EKeyCode cameraChaseKey = Key_1;
	//const EKeyCode cameraFirstPersonKey = Key_2;
	//const EKeyCode startKey = Key_Space;
	//const EKeyCode boostKey = Key_Space;
	//const EKeyCode restartKey = Key_R;

	//// initialise game states and countdowns
	//EGameState gameState = gPreRace;
	//EPreRaceStates preRaceState = prInitial;
	//int preRaceCountdownInt = 0;
	//const float preRaceMaxCountdown = 3.0f;
	//float preRaceCountdown = preRaceMaxCountdown;
	//const int numLaps = 3;

	//// timing
	//float raceTimer = 0.0f;
	//myEngine->Timer();

	//// The main game loop, repeat until engine is stopped
	//while (myEngine->IsRunning())
	//{
	//	// Draw the scene
	//	myEngine->DrawScene();

	//	/**** Update your scene each frame here ****/

	//	// timing
	//	const float deltaTime = myEngine->Timer();

	//	if (gameState == gPreRace)
	//	{
	//		// tell player to press start button to start. then countdown and move to racing state

	//		if (preRaceState == prInitial)
	//		{
	//			// initial dialogue
	//			myFont->Draw(preRaceString, gameStateTextPos.x, gameStateTextPos.y, kBlack, kCentre, kVCentre);

	//			// hit space -> timer
	//			if (myEngine->KeyHit(startKey))	preRaceState = prTimer;
	//		}
	//		else if (preRaceState == prTimer)
	//		{
	//			preRaceCountdown -= deltaTime;
	//			preRaceCountdownInt = preRaceCountdown + 1;
	//			myFont->Draw(timerString[preRaceCountdownInt], gameStateTextPos.x, gameStateTextPos.y, kBlack,
	//				kCentre, kVCentre);

	//			if (preRaceCountdownInt == 0)
	//			{
	//				gameState = gRacing;

	//				// stop a sudden mouse moevment jump when the race starts
	//				myEngine->GetMouseMovementX();
	//				myEngine->GetMouseMovementY();
	//			}
	//		}
	//	}
	//	else if (gameState == gRacing)
	//	{
	//		// allow player to move car, control camera. npc car moves around track

	//		// increase racing timer
	//		raceTimer += deltaTime;

	//		// decrease life time for any visible crosses
	//		for (int i = 0; i < checkpointsVec.size(); i++)
	//		{
	//			if (checkpointsVec.at(i).cross.isVisible)
	//			{
	//				checkpointsVec.at(i).cross.lifeTimer -= deltaTime;

	//				if (checkpointsVec.at(i).cross.lifeTimer <= 0.0f)
	//				{
	//					checkpointsVec.at(i).cross.lifeTimer = 0.0f;
	//					checkpointsVec.at(i).cross.model->SetY(kCrossHiddenHeight);
	//					checkpointsVec.at(i).cross.isVisible = false;
	//				}
	//			}
	//		}

	//		//////////////////////////////////////// NPC MOVEMENT ///////////////////////////////////////////

	//		// npc car movement
	//		npcCar.ProcessMovement(deltaTime);

	//		// check for collisions with player car
	//		if (SphereToSphereXZModel(playerCar.GetModel(), npcCar.GetModel(), kCarRadius, kCarRadius))
	//		{
	//			npcCar.Bounce(deltaTime);
	//		}

	//		//////////////////////////////////////// CAMERA CONTROL ///////////////////////////////////////////

	//		// camera control
	//		if (myEngine->KeyHeld(cameraForwardKey))	camera->MoveLocalZ(cameraSpeed * deltaTime);
	//		if (myEngine->KeyHeld(cameraBackwardKey))	camera->MoveLocalZ(-cameraSpeed * deltaTime);
	//		if (myEngine->KeyHeld(cameraLeftKey))		camera->MoveLocalX(-cameraSpeed * deltaTime);
	//		if (myEngine->KeyHeld(cameraRightKey))		camera->MoveLocalX(cameraSpeed * deltaTime);

	//		// rotate camera left and right - no limits
	//		const int mouseMovementX = myEngine->GetMouseMovementX();
	//		cameraYRotation += mouseMovementX * cameraRotationSpeed * deltaTime;

	//		// rotate camera up and down
	//		const int mouseMovementY = myEngine->GetMouseMovementY();
	//		// check camera rotation limit
	//		if (cameraXRotation >= cameraXRotationLimitLower && cameraXRotation <= cameraXRotationLimitUpper)
	//		{
	//			cameraXRotation += mouseMovementY * cameraRotationSpeed * deltaTime;
	//		}
	//		else if (cameraXRotation < cameraXRotationLimitLower)
	//		{
	//			cameraXRotation = cameraXRotationLimitLower;
	//		}
	//		else if (cameraXRotation > cameraXRotationLimitUpper)
	//		{
	//			cameraXRotation = cameraXRotationLimitUpper;
	//		}
	//		// rotate camera
	//		CameraRotation(camera, cameraXRotation, cameraYRotation);

	//		// toggle mouse capture
	//		if (myEngine->KeyHit(mouseCaptureKey))
	//		{
	//			isMouseCapture = !isMouseCapture;

	//			if (isMouseCapture) myEngine->StartMouseCapture();
	//			else				myEngine->StopMouseCapture();
	//		}

	//		// reset chase camera position
	//		if (myEngine->KeyHit(cameraChaseKey))
	//		{
	//			camera->SetLocalPosition(camChaseLocalPos.x, camChaseLocalPos.y, camChaseLocalPos.z);
	//			cameraXRotation = cameraInitialXRotation;
	//			cameraYRotation = 0.0f;
	//			CameraRotation(camera, cameraXRotation, cameraYRotation);
	//			cameraState = camChase;
	//		}
	//		// reset first person cam position
	//		else if (myEngine->KeyHit(cameraFirstPersonKey))
	//		{
	//			camera->SetLocalPosition(camFirstPersonLocalPos.x, camFirstPersonLocalPos.y, camFirstPersonLocalPos.z);
	//			cameraXRotation = 0.0f;
	//			cameraYRotation = 0.0f;
	//			CameraRotation(camera, cameraXRotation, cameraYRotation);
	//			cameraState = camFirstPerson;
	//		}

	//		//////////////////////////////////////// PLAYER MOVEMENT ///////////////////////////////////////////

	//		// check for key presses
	//		bool leftRotateKeyPress = false;
	//		bool rightRotateKeyPress = false;

	//		// car rotation control
	//		if (myEngine->KeyHeld(carLeftKey))		leftRotateKeyPress = true;
	//		if (myEngine->KeyHeld(carRightKey))		rightRotateKeyPress = true;

	//		// car movement
	//		float thrustFactor = 0.0f;
	//		if (myEngine->KeyHeld(carForwardKey))
	//		{
	//			if (myEngine->KeyHeld(carBackwardKey))
	//			{
	//				thrustFactor = 0.5f;
	//			}
	//			else
	//			{
	//				thrustFactor = 1.0f;
	//			}
	//		}
	//		else if (myEngine->KeyHeld(carBackwardKey))
	//		{
	//			thrustFactor = -0.5f;
	//		}

	//		// process car boost
	//		bool boostKeyPress = false;
	//		if (myEngine->KeyHeld(boostKey))
	//		{
	//			boostKeyPress = true;
	//		}

	//		playerCar.MovementEachFrame(deltaTime, leftRotateKeyPress, rightRotateKeyPress, boostKeyPress, thrustFactor,
	//			checkpointsVec, numLaps, gameState, wallColliders, tanksVec, npcCar);

	//		///////////////////////////////////////////// UI UPDATE///////////////////////////////////////////////////

	//		// UI text update
	//		if (playerCar.GetCheckpointCounter() == 0)
	//		{
	//			if (playerCar.GetLapCounter() == 0)
	//			{
	//				myFont->Draw(timerString[preRaceCountdownInt], gameStateTextPos.x, gameStateTextPos.y, kBlack,
	//					kCentre, kVCentre);
	//			}
	//			else
	//			{
	//				std::stringstream stageText;
	//				stageText << "Lap " << playerCar.GetLapCounter() << " complete";
	//				myFont->Draw(stageText.str(), gameStateTextPos.x, gameStateTextPos.y, kBlack, kCentre, kVCentre);
	//			}
	//		}
	//		else
	//		{
	//			// draw text "stage <counter> completed
	//			std::stringstream stageText;
	//			stageText << "Stage " << playerCar.GetCheckpointCounter() << " complete";
	//			myFont->Draw(stageText.str(), gameStateTextPos.x, gameStateTextPos.y, kBlack, kCentre, kVCentre);
	//		}

	//		// lap counter text 
	//		std::stringstream lapText;
	//		lapText << "Lap: " << playerCar.GetLapCounter() + 1 << "/" << numLaps;
	//		myFont->Draw(lapText.str(), lapTextPos.x, lapTextPos.y, kBlack);

	//		// checkpoint counter text
	//		std::stringstream cpText;
	//		cpText << "Checkpoint: " << playerCar.GetCheckpointCounter() << "/" << checkpointsVec.size();
	//		myFont->Draw(cpText.str(), cpTextPos.x, cpTextPos.y, kBlack);

	//		// show boost on the UI
	//		if (playerCar.GetIsBoosting())
	//		{
	//			std::stringstream boostReadoutText;
	//			boostReadoutText << "BOOSTING!!!!";
	//			myFont->Draw(boostReadoutText.str(), boostReadoutTextPos.x, boostReadoutTextPos.y, kBlack, kCentre, kVCentre);

	//			if (playerCar.GetBoostTimer() > (kCarMaxBoostTime - kCarBoostWarningTime))
	//			{
	//				std::stringstream boostWarningText;
	//				boostWarningText << "WARNING!";
	//				myFont->Draw(boostWarningText.str(), boostWarningTextPos.x, boostWarningTextPos.y, kBlack, kCentre, kVCentre);
	//			}
	//		}
	//		else if (playerCar.GetBoostIsCooldown())
	//		{
	//			const int boostIntTimer = playerCar.GetBoostCooldownTimer();
	//			std::stringstream boostWarningText;
	//			boostWarningText << "Boost ready in: " << boostIntTimer + 1;
	//			myFont->Draw(boostWarningText.str(), boostWarningTextPos.x, boostWarningTextPos.y, kBlack, kCentre, kVCentre);
	//		}

	//		// show speed on the UI
	//		std::stringstream speedReadoutText;
	//		const float speed = playerCar.GetMomentumVec().magnitude() * kModelScale * kKmPerHourFactor;
	//		const int speedInt = speed;
	//		speedReadoutText << "Speed: " << speedInt << " km/h";
	//		myFont->Draw(speedReadoutText.str(), speedReadoutTextPos.x, speedReadoutTextPos.y, kBlack);
	//		speedReadoutText.str("");

	//		// show health on the UI
	//		std::stringstream healthText;
	//		healthText << "Health: " << playerCar.GetHealth();
	//		myFont->Draw(healthText.str(), healthTextPos.x, healthTextPos.y, kBlack);

	//	}
	//	else if (gameState == gRaceOver)
	//	{
	//		// show race complete/you died on the UI
	//		if (playerCar.GetIsAlive())
	//		{
	//			myFont->Draw(raceOverString, gameStateTextPos.x, gameStateTextPos.y, kBlack, kCentre, kVCentre);

	//			std::stringstream timerText;
	//			timerText << "You finished the race in " << trunc(raceTimer) << " seconds!";
	//			myFont->Draw(timerText.str(), timerTextPos.x, timerTextPos.y, kBlack, kCentre, kVCentre);
	//		}
	//		else
	//		{
	//			myFont->Draw(carDiedString, gameStateTextPos.x, gameStateTextPos.y, kBlack, kCentre, kVCentre);
	//		}

	//		// show restart info on screen
	//		myFont->Draw(restartString, restartStringPos.x, restartStringPos.y, kBlack, kCentre, kVCentre);

	//		if (myEngine->KeyHit(restartKey))
	//		{
	//			// change game state
	//			gameState = gPreRace;

	//			// race timer
	//			raceTimer = 0.0f;

	//			// pre-race timer and pre-race state
	//			preRaceCountdown = preRaceMaxCountdown;
	//			preRaceState = prInitial;

	//			// player car reset
	//			playerCar.Reset();
	//			// npc car reset
	//			npcCar.Reset();
	//		}
	//	}

	//	// close when hit quit key
	//	if (myEngine->KeyHit(quitKey))	myEngine->Stop();
	//}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

//// Rotates the camera around the x and y axes by x degrees and y degrees respectively
//void CameraRotation(ICamera*& camera, const float& x, const float& y)
//{
//	camera->ResetOrientation();
//	camera->RotateX(x);
//	camera->RotateY(y);
//}
//
//// Calculates the distance in X-Z plane between two IModel and returns it
//float DistanceXZModel(IModel* model1, IModel* model2)
//{
//	float xDist = model2->GetX() - model1->GetX();
//	float zDist = model2->GetZ() - model1->GetZ();
//
//	return sqrt(xDist * xDist + zDist * zDist);
//}
//
//// Returns true when point to box collision occurs. Must pass in the IModel* of the point and box, 
//// and the width (along x axis) and depth (along z axis) of the box.
//bool PointToBoxXZ(IModel* point, IModel* box, const float& boxWidth, const float& boxDepth)
//{
//	SVector2D pointPos = { point->GetX(), point->GetZ() };
//	SVector2D boxPos = { box->GetX(), box->GetZ() };
//
//	SVector2D min = { boxPos.x - 0.5f * boxWidth, boxPos.y - 0.5f * boxDepth };
//	SVector2D max = { min.x + boxWidth, min.y + boxDepth };
//
//	return (pointPos.x <= max.x && pointPos.x >= min.x && pointPos.y <= max.y && pointPos.y >= min.y);
//}
//
//// returns true if a collision occurs between the sphere and the box. Requires the IModel* of the sphere and box to be 
//// passed in. Also requires the sphere radius, boxWidth, and boxDepth to be passed in.
//bool SphereToBoxXZ(IModel* sphere, IModel* box, const float& sphereRadius, const float& boxWidth, const float& boxDepth)
//{
//	SVector2D spherePos = { sphere->GetX(), sphere->GetZ() };
//	SVector2D boxPos = { box->GetX(), box->GetZ() };
//
//	// bounding box min & max values
//	SVector2D min = { box->GetX() - 0.5f * boxWidth - sphereRadius, box->GetZ() - 0.5f * boxDepth - sphereRadius };
//	SVector2D max = { box->GetX() + 0.5f * boxWidth + sphereRadius, box->GetZ() + 0.5f * boxDepth + sphereRadius };
//
//	return (spherePos.x <= max.x && spherePos.x >= min.x && spherePos.y <= max.y && spherePos.y >= min.y);
//}
//
///* Checks for collision between a sphere and a box.Returns the side of the box hit.
//Need to provide sphere radius, box width and depth, old sphere positions for x and z as parameters. */
//EBoxSide EnhancedSphereToBoxXZ(IModel* sphere, const SVector2D& boxPos, const float& sphereRadius, const SVector2D& boxWidthDepth, const SVector2D& sphereOldPos)
//{
//	EBoxSide result = noSide;
//
//	// find minX and maxX
//	SVector2D minXZ = { boxPos.x - (0.5f * boxWidthDepth.x) - sphereRadius , boxPos.y - (0.5f * boxWidthDepth.y) - sphereRadius };
//	SVector2D maxXZ = { boxPos.x + (0.5f * boxWidthDepth.x) + sphereRadius , boxPos.y + (0.5f * boxWidthDepth.y) + sphereRadius };
//
//	// collision if the sphere is within the bounds defined by minX, maxX, minZ, and maxZ
//	if (sphere->GetX() > minXZ.x && sphere->GetX() < maxXZ.x && sphere->GetZ() > minXZ.y && sphere->GetZ() < maxXZ.y)
//	{
//		if (sphereOldPos.x <= minXZ.x) result = leftSide;
//		else if (sphereOldPos.x >= maxXZ.x) result = rightSide;
//		else if (sphereOldPos.y <= minXZ.y) result = frontSide;
//		else result = backSide;
//	}
//
//	return result;
//}
//
//// returns true if a collision occurs between two spheres. Requires the IModel* and the radii of the two spheres to be passed in.
//bool SphereToSphereXZModel(IModel* sphere1, IModel* sphere2, const float& radius1, const float& radius2)
//{
//	return (DistanceXZModel(sphere1, sphere2) <= radius1 + radius2);
//}
//
//// Calculates the distance between two VectorXZ points and returns it.
//float DistanceXZPoints(const SVector2D& p1, const SVector2D& p2)
//{
//	float xDist = p2.x - p1.x;
//	float zDist = p2.y - p1.y;
//
//	return (sqrt(xDist * xDist + zDist * zDist));
//}
//
//// returns true if a collision occurs between two spheres. must pass in the positions of the centre of the spheres and the radii of the spheres.
//bool SphereToSphereXZ(const SVector2D& sphere1Pos, const SVector2D& sphere2pos, const float& sphere1radius, const float& sphere2radius)
//{
//	return (DistanceXZPoints(sphere1Pos, sphere2pos) <= sphere1radius + sphere2radius);
//}
//
//// opens the read file with the name passed in
//void OpenFile(std::ifstream& readFile, const std::string& filename)
//{
//	readFile.open(filename);
//}
//
//// closes the passd in read file
//void CloseFile(std::ifstream& readFile)
//{
//	readFile.close();
//}
//
//// Reads in a level file in the form (item type, xPos, zPos, yRotation) and adds each item to the level items vector.
//void ReadWholeFileLineByLine(std::ifstream& readFile, std::vector <SLevelItem>& v)
//{
//	while (!readFile.eof())
//	{
//		// read single line from file
//		std::string line;
//		getline(readFile, line);
//
//		// split the line into its components with the stringstream
//		std::stringstream ss(line);
//
//		SLevelItem newItem;
//		ss >> newItem.type;
//		ss >> newItem.xPos;
//		ss >> newItem.zPos;
//		ss >> newItem.yRotation;
//
//		// add to vector
//		v.push_back(newItem);
//	}
//}
//
//// Returns the vec1 reflected in vec2.
//// WILL BE DEPRECATED BY CVector2D
//SVector2D ReflectVectorInVector(const SVector2D& vec1, const SVector2D& vec2)
//{
//	SVector2D vec2Normalised = NormaliseVector2D(vec2);
//	const float coefficientOfReflection = 2.0f * DotProduct(vec1, vec2Normalised);
//	SVector2D reflection = Vector2DSubtraction(vec1, ScalarMultiplication(coefficientOfReflection, vec2Normalised));
//
//	return reflection;
//}