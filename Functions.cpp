#pragma once
#include <TL-Engine.h>
#include "Functions.h"

using namespace tle;

///////////////// barrel flames
const int kTotalBarrels = 4;
float barrelXPositions[4] = { -100.0f, -100.0f, 120.0f, 100.0f };
float barrelZPositions[4] = { 300.0f, -345.0f, -7.0f, 150.0f };
const float barrelFlameYPos = 18.0f;
const int kTotalParticles = 1600;  // count of particles in the scene
const int kParticlesPerBarrel = 400;  // count of particles in the scene
const float kParicleResetPosY = 43.0f;  // position y of the particle that is reset
const float kStartVelocity = -1.0f;  // inital move speed for particles
const float kGravity = -70.0f;  // reduce move speed of particles

vector2D scalar(float s, vector2D v)
{
	return { s * v.x, s * v.z };
}


void readMap(int &numberOfWalls, int &numberOfBoxes, int & numberOfTargets, int &numberOfWallBoxes, vector<model> &wall, vector<collision> &wallCollision, vector<model> &box, vector<target> &targetThief, string &mapName)
{

	mapName = ("Map2.txt");
	float worldMultiplier = 1.0f;;
	string linetest;
	string comment;
	float temp;

	if (mapName == "Map1.txt")
	{
		worldMultiplier = 20.0f;
	}

	vector<IModel*>xModelLine;

	ifstream fileInput;
	fileInput.open(mapName); // opens the input file

	if (fileInput.is_open()) // Checks to see that the file has been opened sucessfully
	{
		// For loop to read in file
		//fileInput >> temp; // reads in the first value from the file and sets the qty variable


		// reads in the levels walls

		fileInput >> numberOfWalls;

		for (int i = 0; i < numberOfWalls; i++) // runs through the whole file, based on the value from the first line of the file
		{
			model wallBlock;
			fileInput >> temp;// inputs the x elements from the file
			wallBlock.XPos = temp * worldMultiplier;

			fileInput >> temp;	// inputs the z elements from the file
			wallBlock.ZPos = temp * worldMultiplier;

			fileInput >> temp;
			wallBlock.rotation = temp;

			wallBlock.xSize = 15.0f;
			wallBlock.ySize = 22.5f;
			wallBlock.zSize = 15.0f;

			wall.insert(wall.begin(), wallBlock);
		}


		// reads in seperate collisions for walls

		if (mapName == "Map1.txt")
		{

			fileInput >> numberOfWallBoxes;

			for (int i = 0; i < numberOfWallBoxes; i++) // runs through the whole fil
			{
				collision wallBox;
				fileInput >> temp;// inputs the x elements from the file
				wallBox.xPosition = temp * worldMultiplier;

				fileInput >> temp;	// inputs the z elements from the file
				wallBox.zPosition = temp * worldMultiplier;

				fileInput >> temp;
				wallBox.xSize = temp * worldMultiplier;

				wallBox.ySize = 22.5f;

				fileInput >> temp;
				wallBox.zSize = temp * worldMultiplier;

				/*fileInput >> temp;
				wallBox.rotationAmount = temp;*/

				/*if (wallBox.rotationAmount == 90.0f)
				{
				temp = wallBox.xSize;
				wallBox.xSize = wallBox.zSize;
				wallBox.zSize = temp;
				}*/

				wallCollision.insert(wallCollision.begin(), wallBox);
			}

		}
		// reads in the levels boxes
		fileInput >> numberOfBoxes;

		for (int i = 0; i < numberOfBoxes; i++) // runs through the whole file, based on the value from the first line of the file
		{
			model boxBlock;
			fileInput >> temp;// inputs the x elements from the file
			boxBlock.XPos = temp * worldMultiplier;

			fileInput >> temp;	// inputs the z elements from the file
			boxBlock.ZPos = temp * worldMultiplier;

			box.insert(box.begin(), boxBlock);
		}

		// reads in the levels boxes
		fileInput >> numberOfTargets;

		for (int i = 0; i < numberOfTargets; i++)// runs through the whole file, based on the value from the first line of the file
		{
			target targetBlock;
			fileInput >> temp;// inputs the x elements from the file
			targetBlock.xPosition = temp * worldMultiplier;

			fileInput >> temp;	// inputs the z elements from the file
			targetBlock.zPosition = temp * worldMultiplier;

			fileInput >> temp;	// inputs the z elements from the file
			targetBlock.rotationAmount = temp;

			targetBlock.hostage = false;

			cout << targetBlock.xPosition / 15 << " " << targetBlock.zPosition / 15 << endl;

			targetThief.insert(targetThief.begin(), targetBlock);
		}

		fileInput.close(); // Closes the file


	}

}

void weaponAnimation(float &animationTimer, IModel* M4Colt, IModel* player, float frameTime)
{
	animationTimer -= frameTime;
	if (animationTimer < 0.1f && animationTimer > 0.05f)
	{
		// move weapon backwards
		M4Colt->MoveLocalZ(-frameTime * 5);
	}
	else if (animationTimer > 0.0f && animationTimer <= 0.05f)
	{
		// move weapon forwards

		M4Colt->MoveLocalZ(frameTime * 5);
	}

	else if (animationTimer < 0.0f)
	{
		M4Colt->SetPosition(player->GetX(), player->GetY(), player->GetZ());
		M4Colt->SetLocalX(2.0f);
		M4Colt->SetLocalY(10.0f);
		M4Colt->SetLocalZ(7.0f);
	}

	float x = M4Colt->GetX();
	float y = M4Colt->GetY();
	float z = M4Colt->GetZ();



}

void desertEagleAnimation(float &animationTimer, IModel* desertEagle, IModel* player, float frameTime)
{
	animationTimer -= frameTime;
	if (animationTimer < 0.1f && animationTimer > 0.05f)
	{
		// move weapon backwards
		desertEagle->MoveLocalZ(-frameTime * 2);
		desertEagle->MoveLocalY(frameTime * 2);
		desertEagle->RotateLocalX(-frameTime * 800);
	}
	else if (animationTimer > 0.0f && animationTimer <= 0.05f)
	{
		// move weapon forwards

		desertEagle->MoveLocalZ(frameTime * 2);
		desertEagle->MoveLocalY(-frameTime * 2);
		desertEagle->RotateLocalX(frameTime * 800);
	}

	else if (animationTimer < 0.0f)
	{
		desertEagle->SetPosition(player->GetX(), player->GetY(), player->GetZ());
		desertEagle->SetLocalX(2.0f);
		desertEagle->SetLocalY(10.0f);
		desertEagle->SetLocalZ(7.0f);
		desertEagle->ResetOrientation();
	}

	float x = desertEagle->GetX();
	float y = desertEagle->GetY();
	float z = desertEagle->GetZ();



}
int nextInArray(int i, int arraySize) // Function to select the next point in a patrol (or cycle through any array)
{
	int lastCheckpoint = i; // number in the array for current checkpoint (one reached)
	int nextCheckpoint;  // number in the array for the next checkpoint

	nextCheckpoint = (lastCheckpoint + 1) % arraySize;  // cycles to the next member of the array using modulus (remainder) 0>1>2>3>4>0

	return nextCheckpoint;
}

int previousInArray(int i, int arraySize) // Function to select the previous point in a patrol (or cycle through any array)
{
	int lastCheckpoint = i; // number in the array for current checkpoint (one reached)
	int previousCheckpoint;  // number in the array for the next checkpoint

	previousCheckpoint = (lastCheckpoint - 1) % arraySize;  // cycles to the previous member of the array using modulus (remainder) 0>1>2>3>4>0

	if (previousCheckpoint == -1)
	{
		previousCheckpoint = 25;
	}

	return previousCheckpoint;
}

void ExtraSceneSetup(I3DEngine* myEngine)
{
	///////////////////////////////
	//Barrels
	/////////

	float barrelScale = 20.0f; //scale barrel by 

	IMesh* barrelMesh = myEngine->LoadMesh("PlasticDrum1.x");
	IModel* barrel  = barrelMesh->CreateModel(barrelXPositions[0], 0.0f, barrelZPositions[0]);
	IModel* barrel2 = barrelMesh->CreateModel(barrelXPositions[1], 0.0f, barrelZPositions[1]);
	IModel* barrel3 = barrelMesh->CreateModel(barrelXPositions[2], 0.0f, barrelZPositions[2]);
	IModel* barrel4 = barrelMesh->CreateModel(barrelXPositions[3], 0.0f, barrelZPositions[3]);

	barrel->Scale(barrelScale);
	barrel2->Scale(barrelScale);
	barrel3->Scale(barrelScale);
	barrel4->Scale(barrelScale);

	//Barrels End////////////////////////

	////////////////////////
	//Partical (flames/smaok)
	////////////////////////

	//set up flames here

	//CBarrelFlame* barrelFlame = new CBarrelFlame(myEngine, BARREL_DIAMETER, barrel->GetX(), barrel->GetY(), barrel->GetZ());
	//CBarrelFlame* barrelFlame2 = new CBarrelFlame(myEngine, BARREL_DIAMETER, barrel2->GetX(), barrel2->GetY(), barrel2->GetZ());
	//CBarrelFlame* barrelFlame3 = new CBarrelFlame(myEngine, BARREL_DIAMETER, barrel3->GetX(), barrel3->GetY(), barrel3->GetZ());
	//CBarrelFlame* barrelFlame4 = new CBarrelFlame(myEngine, BARREL_DIAMETER, barrel4->GetX(), barrel4->GetY(), barrel4->GetZ());

	// Flames / Smoak End ////////////////////////

	////////////////////
	//Cargo Container
	///////////////////


	IMesh* cargoMesh = myEngine->LoadMesh("CargoContainer.x");
	IModel* container[8];

	container[0] = cargoMesh->CreateModel(-300.0f, 0.0f, 500.0f);
	container[0]->Scale(19.0f);
	container[0]->RotateLocalY(90.0f);
	container[0]->SetSkin("CargoRust.tga");

	container[1] = cargoMesh->CreateModel(-120.0f, 0.0f, -400.0f);
	container[1]->Scale(19.0f);
	container[1]->RotateLocalY(90.0f);
	container[1]->SetSkin("CargoRed.tga");

	container[2] = cargoMesh->CreateModel(200.0f, 0.0f, 280.0f);
	container[2]->Scale(19.0f);
	container[2]->RotateLocalY(-37.0f);
	container[2]->SetSkin("CargoLightBlue.tga");

	container[3] = cargoMesh->CreateModel(220.0f, 0.0f, 0.0f);
	container[3]->Scale(19.0f);
	container[3]->RotateLocalY(90.0f);
	container[3]->SetSkin("CargoGrey.tga");

	container[4] = cargoMesh->CreateModel(-300.0f, 0.0f, -500.0f);
	container[4]->Scale(19.0f);
	container[4]->RotateLocalY(15.0f);


	container[5] = cargoMesh->CreateModel(-300.0f, 50.0f, 500.0f);
	container[5]->Scale(19.0f);
	container[5]->RotateLocalY(90.0f);
	container[5]->SetSkin("CargoGreen.tga");

	container[6] = cargoMesh->CreateModel(370.0f, 0.0f, -260.0f);
	container[6]->Scale(19.0f);
	container[6]->RotateLocalY(-37.0f);
	container[6]->SetSkin("CargoPurple.tga");

	container[7] = cargoMesh->CreateModel(225.0f, 0.0f, -475.0f);
	container[7]->Scale(19.0f);
	container[7]->RotateLocalY(29.0f);
	container[7]->SetSkin("CargoNeonRed.tga");

	// Cargo Container End ///////////////


	///////////////
	//factory walls
	///////////////

	IMesh* outerWallMesh = myEngine->LoadMesh("Wall.x");

	IModel* outerWall = outerWallMesh->CreateModel(0.0f, 0.0f, 600.0f);
	outerWall->SetSkin("brickWallGrey3.jpg");
	outerWall->ScaleX(30.0f);
	outerWall->ScaleY(30.0f);
	outerWall->ScaleZ(0.10f);

	IModel* outerWall2 = outerWallMesh->CreateModel(-300.0f, 0.0f, 600.0f);
	outerWall2->SetSkin("brickWallGrey3.jpg");
	outerWall2->ScaleX(30.0f);
	outerWall2->ScaleY(30.0f);
	outerWall2->ScaleZ(0.10f);

	IModel* outerWall3 = outerWallMesh->CreateModel(-600.0f, 0.0f, 600.0f);
	outerWall3->SetSkin("brickWallGrey3.jpg");
	outerWall3->ScaleX(30.0f);
	outerWall3->ScaleY(30.0f);
	outerWall3->ScaleZ(0.10f);

	IModel* outerWall4 = outerWallMesh->CreateModel(300.0f, 0.0f, 600.0f);
	outerWall4->SetSkin("brickWallGrey3.jpg");
	outerWall4->ScaleX(30.0f);
	outerWall4->ScaleY(30.0f);
	outerWall4->ScaleZ(0.10f);

	IModel* outerWall5 = outerWallMesh->CreateModel(450.0f, 0.0f, 450.0f);
	outerWall5->SetSkin("brickWallGrey3.jpg");
	outerWall5->ScaleX(30.0f);
	outerWall5->ScaleY(30.0f);
	outerWall5->ScaleZ(0.10f);
	outerWall5->RotateLocalY(90.0f);

	IModel* outerWall6 = outerWallMesh->CreateModel(450.0f, 0.0f, 150.0f);
	outerWall6->SetSkin("brickWallGrey3.jpg");
	outerWall6->ScaleX(30.0f);
	outerWall6->ScaleY(30.0f);
	outerWall6->ScaleZ(0.10f);
	outerWall6->RotateLocalY(90.0f);

	IModel* outerWall7 = outerWallMesh->CreateModel(450.0f, 0.0f, -150.0f);
	outerWall7->SetSkin("brickWallGrey3.jpg");
	outerWall7->ScaleX(30.0f);
	outerWall7->ScaleY(30.0f);
	outerWall7->ScaleZ(0.10f);
	outerWall7->RotateLocalY(90.0f);

	IModel* outerWall8 = outerWallMesh->CreateModel(450.0f, 0.0f, -450.0f);
	outerWall8->SetSkin("brickWallGrey3.jpg");
	outerWall8->ScaleX(30.0f);
	outerWall8->ScaleY(30.0f);
	outerWall8->ScaleZ(0.10f);
	outerWall8->RotateLocalY(90.0f);

	IModel* outerWall9 = outerWallMesh->CreateModel(0.0f, 0.0f, -600.0f);
	outerWall9->SetSkin("brickWallGrey3.jpg");
	outerWall9->ScaleX(30.0f);
	outerWall9->ScaleY(30.0f);
	outerWall9->ScaleZ(0.10f);
	outerWall9->RotateLocalY(180.0f);

	IModel* outerWall10 = outerWallMesh->CreateModel(-300.0f, 0.0f, -600.0f);
	outerWall10->SetSkin("brickWallGrey3.jpg");
	outerWall10->ScaleX(30.0f);
	outerWall10->ScaleY(30.0f);
	outerWall10->ScaleZ(0.10f);
	outerWall10->RotateLocalY(180.0f);

	IModel* outerWall11 = outerWallMesh->CreateModel(-600.0f, 0.0f, -600.0f);
	outerWall11->SetSkin("brickWallGrey3.jpg");
	outerWall11->ScaleX(30.0f);
	outerWall11->ScaleY(30.0f);
	outerWall11->ScaleZ(0.10f);
	outerWall11->RotateLocalY(180.0f);

	IModel* outerWall12 = outerWallMesh->CreateModel(300.0f, 0.0f, -600.0f);
	outerWall12->SetSkin("brickWallGrey3.jpg");
	outerWall12->ScaleX(30.0f);
	outerWall12->ScaleY(30.0f);
	outerWall12->ScaleZ(0.10f);
	outerWall12->RotateLocalY(180.0f);

	IModel* outerWall13 = outerWallMesh->CreateModel(-450.0f, 0.0f, 450.0f);
	outerWall13->SetSkin("brickWallGrey3.jpg");
	outerWall13->ScaleX(30.0f);
	outerWall13->ScaleY(30.0f);
	outerWall13->ScaleZ(0.10f);
	outerWall13->RotateLocalY(-90.0f);

	IModel* outerWall14 = outerWallMesh->CreateModel(-450.0f, 0.0f, 150.0f);
	outerWall14->SetSkin("brickWallGrey3.jpg");
	outerWall14->ScaleX(30.0f);
	outerWall14->ScaleY(30.0f);
	outerWall14->ScaleZ(0.10f);
	outerWall14->RotateLocalY(-90.0f);

	IModel* outerWall15 = outerWallMesh->CreateModel(-450.0f, 0.0f, -150.0f);
	outerWall15->SetSkin("brickWallGrey3.jpg");
	outerWall15->ScaleX(30.0f);
	outerWall15->ScaleY(30.0f);
	outerWall15->ScaleZ(0.10f);
	outerWall15->RotateLocalY(-90.0f);

	IModel* outerWall16 = outerWallMesh->CreateModel(-450.0f, 0.0f, -450.0f);
	outerWall16->SetSkin("brickWallGrey3.jpg");
	outerWall16->ScaleX(30.0f);
	outerWall16->ScaleY(30.0f);
	outerWall16->ScaleZ(0.10f);
	outerWall16->RotateLocalY(-90.0f);

	IModel* outerWall17 = outerWallMesh->CreateModel(0.0f, 145.0f, 0.0f);
	outerWall17->SetSkin("celingTileStained.jpg");
	outerWall17->ScaleX(130.0f);
	outerWall17->ScaleY(130.0f);
	outerWall17->ScaleZ(0.10f);
	outerWall17->RotateLocalX(-90.0f);


	//Factory Walls End//////////////

	///////////
	//Column
	///////////

	IModel* collumn[4];

	collumn[0] = outerWallMesh->CreateModel(200.0f, 0.0f, 200.0f);
	collumn[0]->SetSkin("Concrete13.jpg");
	collumn[0]->ScaleX(1.0f);
	collumn[0]->ScaleY(130.0f);
	collumn[0]->ScaleZ(1.10f);

	collumn[1] = outerWallMesh->CreateModel(-200.0f, 0.0f, 200.0f);
	collumn[1]->SetSkin("Concrete13.jpg");
	collumn[1]->ScaleX(1.0f);
	collumn[1]->ScaleY(130.0f);
	collumn[1]->ScaleZ(1.10f);

	collumn[2] = outerWallMesh->CreateModel(200.0f, 0.0f, -200.0f);
	collumn[2]->SetSkin("Concrete13.jpg");
	collumn[2]->ScaleX(1.0f);
	collumn[2]->ScaleY(130.0f);
	collumn[2]->ScaleZ(1.10f);

	collumn[3] = outerWallMesh->CreateModel(-200.0f, 0.0f, -200.0f);
	collumn[3]->SetSkin("Concrete13.jpg");
	collumn[3]->ScaleX(1.0f);
	collumn[3]->ScaleY(130.0f);
	collumn[3]->ScaleZ(1.10f);

	//Column End /////////////////

	//////////////////
	//Factory Windows
	//////////////////

	IMesh* windowMesh = myEngine->LoadMesh("window.x");
	IModel* window[33];

	window[0] = windowMesh->CreateModel(0.0f, 100.0f, 598.0f);
	window[1] = windowMesh->CreateModel(-30.0f, 100.0f, 598.0f);
	window[2] = windowMesh->CreateModel(-60.0f, 100.0f, 598.0f);
	window[3] = windowMesh->CreateModel(-90.0f, 100.0f, 598.0f);
	window[4] = windowMesh->CreateModel(-120.0f, 100.0f, 598.0f);
	window[5] = windowMesh->CreateModel(-150.0f, 100.0f, 598.0f);
	window[6] = windowMesh->CreateModel(-180.0f, 100.0f, 598.0f);
	window[7] = windowMesh->CreateModel(-210.0f, 100.0f, 598.0f);

	window[8] = windowMesh->CreateModel(0.0f, 100.0f, -598.0f);
	window[9] = windowMesh->CreateModel(-30.0f, 100.0f, -598.0f);
	window[10] = windowMesh->CreateModel(-60.0f, 100.0f, -598.0f);
	window[11] = windowMesh->CreateModel(-90.0f, 100.0f, -598.0f);
	window[12] = windowMesh->CreateModel(-120.0f, 100.0f, -598.0f);
	window[13] = windowMesh->CreateModel(-150.0f, 100.0f, -598.0f);
	window[14] = windowMesh->CreateModel(-180.0f, 100.0f, -598.0f);
	window[15] = windowMesh->CreateModel(-210.0f, 100.0f, -598.0f);

	for (int i = 8; i < 16; i++)
	{
		window[i]->RotateLocalY(180.0f);
	}

	window[16] = windowMesh->CreateModel(447.0f, 100.0f, 0.0f);
	window[17] = windowMesh->CreateModel(447.0f, 100.0f, 30.0f);
	window[18] = windowMesh->CreateModel(447.0f, 100.0f, 60.0f);
	window[19] = windowMesh->CreateModel(447.0f, 100.0f, 90.0f);
	window[20] = windowMesh->CreateModel(447.0f, 100.0f, 120.0f);
	window[21] = windowMesh->CreateModel(447.0f, 100.0f, 150.0f);
	window[22] = windowMesh->CreateModel(447.0f, 100.0f, 180.0f);
	window[23] = windowMesh->CreateModel(447.0f, 100.0f, 210.0f);

	for (int i = 16; i < 24; i++)
	{
		window[i]->RotateLocalY(90.0f);
	}

	window[24] = windowMesh->CreateModel(-447.0f, 100.0f, 0.0f);
	window[25] = windowMesh->CreateModel(-447.0f, 100.0f, -30.0f);
	window[26] = windowMesh->CreateModel(-447.0f, 100.0f, -60.0f);
	window[27] = windowMesh->CreateModel(-447.0f, 100.0f, -90.0f);
	window[28] = windowMesh->CreateModel(-447.0f, 100.0f, -120.0f);
	window[29] = windowMesh->CreateModel(-447.0f, 100.0f, -150.0f);
	window[30] = windowMesh->CreateModel(-447.0f, 100.0f, -180.0f);
	window[31] = windowMesh->CreateModel(-447.0f, 100.0f, -210.0f);

	for (int i = 24; i < 32; i++)
	{
		window[i]->RotateLocalY(-90.0f);
	}

	//Factory Windows End/////////


	/////////////
	//Factory Door
	//////////////

	IModel* door = windowMesh->CreateModel(110.0f, 20.0f, 607.0f);
	door->SetSkin("Door.jpg");
	door->RotateLocalZ(90.0f);
	door->Scale(5.0f);

	IMesh* markingsMesh = myEngine->LoadMesh("Square.x");
	IModel* markings = markingsMesh->CreateModel(110.0f, -99.7, 490.0f);
	markings->Scale(20.0f);
	markings->RotateLocalY(90.0f);
	markings->RotateLocalX(90.0f);
	markings->SetSkin("markings.png");

	//Factory Door End///////////////



	//////////
	//Card Board Boxes
	//////////////////

	IMesh* cardBoardMesh = myEngine->LoadMesh("CardboardBox1.x");
	IMesh* cardBoardMesh2 = myEngine->LoadMesh("CardboardBox2.x");

	IModel* box2[10];
	box2[0] = cardBoardMesh->CreateModel(95.0f, 3.5f, 55.0f);
	box2[0]->Scale(7.0f);

	box2[1] = cardBoardMesh->CreateModel(95.0f, 10.5f, 55.0f);
	box2[1]->Scale(7.0f);

	box2[2] = cardBoardMesh->CreateModel(85.0f, 3.5f, 50.0f);
	box2[2]->Scale(7.0f);

	box2[3] = cardBoardMesh->CreateModel(85.0f, 10.5f, 50.0f);
	box2[3]->Scale(7.0f);

	box2[4] = cardBoardMesh->CreateModel(93.0f, 3.5f, 45.0f);
	box2[4]->Scale(7.0f);

	box2[5] = cardBoardMesh->CreateModel(93.0f, 10.5f, 45.0f);
	box2[5]->Scale(7.0f);

	box2[6] = cardBoardMesh->CreateModel(85.0f, 17.5f, 50.0f);
	box2[6]->Scale(7.0f);

	box2[7] = cardBoardMesh->CreateModel(-362.0f, 3.5f, -75.0f);
	box2[7]->Scale(7.0f);

	box2[8] = cardBoardMesh->CreateModel(-362.0f, 10.5f, -75.0f);
	box2[8]->Scale(7.0f);

	box2[9] = cardBoardMesh->CreateModel(-365.0f, 17.5f, -55.0f);
	box2[9]->Scale(7.0f);


	IModel* box3[6];
	box3[0] = cardBoardMesh2->CreateModel(95.0f, 3.5f, -55.0f);
	box3[0]->Scale(7.0f);

	box3[1] = cardBoardMesh2->CreateModel(95.0f, 10.5f, -55.0f);
	box3[1]->Scale(7.0f);

	box3[2] = cardBoardMesh2->CreateModel(85.0f, 3.5f, 50.0f);
	box3[2]->Scale(7.0f);

	box3[3] = cardBoardMesh2->CreateModel(-365.0f, 3.5f, -55.0f);
	box3[3]->Scale(7.0f);

	box3[4] = cardBoardMesh2->CreateModel(-365.0f, 10.5f, -55.0f);
	box3[4]->Scale(7.0f);

	box3[5] = cardBoardMesh2->CreateModel(-355.0f, 3.5f, -50.0f);
	box3[5]->Scale(7.0f);

	//Card Board Boxes End////////////////

	//////////
	//Wood Pallet
	/////////////

	IMesh* palletMesh = myEngine->LoadMesh("WoodPallet1.x");
	IModel* pallet = palletMesh->CreateModel(90.0f, 0.0f, 50.0f);
	pallet->Scale(20.0f);

	IModel* pallet2 = palletMesh->CreateModel(90.0f, 0.0f, -50.0f);
	pallet2->Scale(20.0f);

	IModel* pallet3 = palletMesh->CreateModel(-360.0f, 0.0f, -50.0f);
	pallet3->Scale(20.0f);
	IModel* pallet4 = palletMesh->CreateModel(-360.0f, 0.0f, -28.0f);
	pallet4->Scale(20.0f);
	IModel* pallet5 = palletMesh->CreateModel(-360.0f, 3.5f, -28.0f);
	pallet5->Scale(20.0f);
	IModel* pallet6 = palletMesh->CreateModel(-357.0f, 0.0f, -78.0f);
	pallet6->Scale(20.0f);

	//Wood Pallet End ///////////////


	////////
	//Dumpster
	//////////

	IMesh* dumpsterMesh = myEngine->LoadMesh("Dumpster1.x");
	IModel* dumpster = dumpsterMesh->CreateModel(-80.0f, 0.0f, 585.0f);
	dumpster->Scale(15.0f);
	dumpster->RotateLocalY(180.0f);


	IModel* dumpster2 = dumpsterMesh->CreateModel(0.0f, 0.0f, 585.0f);
	dumpster2->SetSkin("DmpstrA2.tga");
	dumpster2->Scale(15.0f);
	dumpster2->RotateLocalY(180.0f);

	//Dumpster End///////////

	///////////
	//Plastic Drum
	//////////////

	IMesh* drumMesh = myEngine->LoadMesh("PlasticDrum2.x");
	IModel* drum = drumMesh->CreateModel(-100.0f, 0.0f, 100.0f);
	drum->Scale(20.0f);

	IModel* drum2 = drumMesh->CreateModel(-100.0f, 0.0f, 140.0f);
	drum2->Scale(20.0f);

	IModel* drumMod[9];

	drumMod[0] = drumMesh->CreateModel(-435.0f, 0.0f, 200.0f);
	drumMod[1] = drumMesh->CreateModel(-435.0f, 18.0f, 200.0f);
	drumMod[2] = drumMesh->CreateModel(-410.0f, 0.0f, 170.0f);
	drumMod[3] = drumMesh->CreateModel(-435.0f, 0.0f, 230.0f);
	drumMod[4] = drumMesh->CreateModel(-435.0f, 18.0f, 230.0f);
	drumMod[5] = drumMesh->CreateModel(-405.0f, 0.0f, 200.0f);
	drumMod[6] = drumMesh->CreateModel(-405.0f, 18.0f, 200.0f);
	drumMod[7] = drumMesh->CreateModel(-400.0f, 0.0f, 290.0f);
	drumMod[8] = drumMesh->CreateModel(-385.0f, 6.0f, 148.0f);

	for (int i = 0; i < 9; i++)
	{
		drumMod[i]->Scale(20.0f);
	}

	drumMod[8]->RotateLocalX(90.0f);

	//Plastic Drum End ////////////////

	////////////////////
	//Safety Warning Post
	/////////////////////

	IModel* postA = drumMesh->CreateModel(30.0f, 0.0f, 590.0f);
	postA->SetSkin("post.tga");
	postA->ScaleX(5.0f);
	postA->ScaleZ(5.0f);
	postA->ScaleY(20.0f);

	IModel* postB = drumMesh->CreateModel(190.0f, 0.0f, 590.0f);
	postB->SetSkin("post.tga");
	postB->ScaleX(5.0f);
	postB->ScaleZ(5.0f);
	postB->ScaleY(20.0f);

	//Safety Warning Post End //////////////////


	/////////
	//Piping
	////////

	IMesh* pipeMesh = myEngine->LoadMesh("pipeLarge2.x");

	IModel* largePipe = pipeMesh->CreateModel(-435.0f, 0.0f, 80.0f);
	largePipe->Scale(8.0f);
	largePipe->RotateLocalY(-90.0f);

	IModel* drum3 = barrelMesh->CreateModel(-447.0f, -2.0f, 100.0f);
	drum3->SetSkin("PlasDrmA5.tga");
	drum3->ScaleX(5.0f);
	drum3->ScaleZ(5.0f);
	drum3->ScaleY(50.0f);
	IModel* drum4 = barrelMesh->CreateModel(-447.0f, 44.0f, 100.0f);
	drum4->SetSkin("PlasDrmA5.tga");
	drum4->ScaleX(5.0f);
	drum4->ScaleZ(5.0f);
	drum4->ScaleY(50.0f);
	IModel* drum5 = barrelMesh->CreateModel(-447.0f, 84.0f, 100.0f);
	drum5->SetSkin("PlasDrmA5.tga");
	drum5->ScaleX(5.0f);
	drum5->ScaleZ(5.0f);
	drum5->ScaleY(50.0f);
	IModel* drum6 = barrelMesh->CreateModel(-447.0f, 124.0f, 100.0f);
	drum6->SetSkin("PlasDrmA5.tga");
	drum6->ScaleX(5.0f);
	drum6->ScaleZ(5.0f);
	drum6->ScaleY(50.0f);

	IModel* pipe[14];

	pipe[0] = barrelMesh->CreateModel(-447.0f, -2.0f, 120.0f);
	pipe[0]->SetSkin("PlasDrmA5.tga");
	pipe[0]->ScaleX(5.0f);
	pipe[0]->ScaleZ(5.0f);
	pipe[0]->ScaleY(50.0f);

	pipe[1] = barrelMesh->CreateModel(-447.0f, 44.0f, 120.0f);
	pipe[1]->SetSkin("PlasDrmA5.tga");
	pipe[1]->ScaleX(5.0f);
	pipe[1]->ScaleZ(5.0f);
	pipe[1]->ScaleY(50.0f);

	pipe[2] = barrelMesh->CreateModel(-447.0f, 84.0f, 120.0f);
	pipe[2]->SetSkin("PlasDrmA5.tga");
	pipe[2]->ScaleX(5.0f);
	pipe[2]->ScaleZ(5.0f);
	pipe[2]->ScaleY(50.0f);

	pipe[3] = barrelMesh->CreateModel(-447.0f, 124.0f, 120.0f);
	pipe[3]->SetSkin("PlasDrmA5.tga");
	pipe[3]->ScaleX(5.0f);
	pipe[3]->ScaleZ(5.0f);
	pipe[3]->ScaleY(50.0f);

	float incrementY = -2.0f;

	for (int i = 4; i < 8; i++)
	{
		pipe[i] = barrelMesh->CreateModel(-447.0f, incrementY, 140.0f);
		pipe[i]->SetSkin("PlasDrmA5.tga");
		pipe[i]->ScaleX(5.0f);
		pipe[i]->ScaleZ(5.0f);
		pipe[i]->ScaleY(50.0f);

		incrementY = incrementY + 40.0f;
	}

	incrementY = -2.0f;

	for (int i = 8; i < 12; i++)
	{
		pipe[i] = barrelMesh->CreateModel(-447.0f, incrementY, 160.0f);
		pipe[i]->SetSkin("PlasDrmA5.tga");
		pipe[i]->ScaleX(7.0f);
		pipe[i]->ScaleZ(7.0f);
		pipe[i]->ScaleY(50.0f);

		incrementY = incrementY + 40.0f;
	}

	pipe[12] = barrelMesh->CreateModel(-447.0f, 84.0f, 160.0f);
	pipe[12]->SetSkin("PlasDrmA5.tga");
	pipe[12]->RotateLocalX(90.0f);
	pipe[12]->ScaleX(5.0f);
	pipe[12]->ScaleZ(5.0f);
	pipe[12]->ScaleY(50.0f);

	pipe[13] = barrelMesh->CreateModel(-447.0f, 84.0f, 200.0f);
	pipe[13]->SetSkin("PlasDrmA5.tga");
	pipe[13]->ScaleX(5.0f);
	pipe[13]->ScaleZ(5.0f);
	pipe[13]->ScaleY(65.0f);

	//Piping End /////////////////



	//////////
	//poster
	////////////

	IMesh* posterMesh = myEngine->LoadMesh("Square.x");
	IModel* poster[9];

	poster[0] = posterMesh->CreateModel(10.0f, -4.7f, -25.0f);
	poster[1] = posterMesh->CreateModel(32.3f, 17.0f, -69.70f);
	poster[2] = posterMesh->CreateModel(-10.0f, -4.7f, 35.0f);
	poster[3] = posterMesh->CreateModel(40.0f, 64.7f, -628.9f);
	poster[4] = posterMesh->CreateModel(-483.3f, 57.0f, -39.70f);
	poster[5] = posterMesh->CreateModel(-10.0f, 17.7f, 117.9f);
	poster[6] = posterMesh->CreateModel(280.0f, 60.7f, 628.0f);
	poster[7] = posterMesh->CreateModel(274.0f, 113.7f, 628.0f);
	poster[8] = posterMesh->CreateModel(-244.0f, 63.7f, 628.0f);

	poster[0]->SetSkin("poster01.png");
	poster[0]->RotateLocalX(90.0f);

	poster[1]->SetSkin("poster02.png");
	poster[1]->RotateLocalZ(190.0f);
	poster[1]->RotateLocalY(180.0f);

	poster[2]->SetSkin("poster03.png");
	poster[2]->RotateLocalX(90.0f);
	poster[2]->RotateLocalZ(90.0f);

	poster[3]->SetSkin("poster04.png");

	poster[3]->RotateLocalZ(-180.0f);
	poster[3]->RotateLocalY(180.0f);
	poster[3]->Scale(6.0f);

	poster[4]->SetSkin("poster05.png");
	poster[4]->RotateLocalZ(180.0f);
	poster[4]->RotateLocalY(90.0f);
	poster[4]->Scale(7.0f);

	poster[5]->SetSkin("poster03.png");
	poster[5]->RotateLocalX(180.0f);
	poster[5]->RotateLocalY(180.0f);

	poster[6]->SetSkin("poster06.png");
	poster[6]->RotateLocalX(180.0f);
	poster[6]->RotateLocalY(180.0f);

	poster[6]->Scale(6.0f);

	poster[7]->SetSkin("poster07.png");
	poster[7]->RotateLocalX(180.0f);
	poster[7]->RotateLocalY(180.0f);
	poster[7]->Scale(6.0f);

	poster[8]->SetSkin("poster03.png");
	poster[8]->RotateLocalX(180.0f);
	poster[8]->RotateLocalY(180.0f);
	poster[8]->Scale(6.0f);


	//Poster End ////////////////

	///////////
	//Air Ducts
	///////////


	IMesh* ductMesh = myEngine->LoadMesh("airDuct.x");

	IModel* duct = ductMesh->CreateModel(0.0f, 130.0f, -450.0f);
	IModel* duct2 = ductMesh->CreateModel(0.0f, 130.0f, -150.0f);
	IModel* duct3 = ductMesh->CreateModel(0.0f, 130.0f, 5.0f);
	duct3->RotateLocalY(90.0f);
	IModel* vent = posterMesh->CreateModel(10.5f, 130.0f, -580.0f);
	vent->SetSkin("vent.png");
	vent->RotateLocalY(90.0f);

	IModel* vents[40];
	float z = -550.0f;
	float z2 = -580.0f;
	float x = 105.0f;

	for (int i = 0; i < 20; i++)
	{

		vents[i] = posterMesh->CreateModel(10.5f, 130.0f, z);
		vents[i]->SetSkin("vent.png");
		vents[i]->RotateLocalY(90.0f);

		z = z + 30.0f;
	}

	for (int i = 20; i < 40; i++)
	{

		vents[i] = posterMesh->CreateModel(-10.5f, 130.0f, z2);
		vents[i]->SetSkin("vent.png");
		vents[i]->RotateLocalY(270.0f);

		z2 = z2 + 30.0f;
	}


	vents[19]->SetLocalPosition(135.0f, 130.0f, 5.5f);
	vents[19]->RotateLocalY(90.0f);

	IModel* vents2[9];
	for (int i = 0; i < 9; i++)
	{
		vents2[i] = posterMesh->CreateModel(x, 130.0f, 5.5f);
		vents2[i]->SetSkin("vent.png");
		vents2[i]->RotateLocalY(180.0f);
		x = x - 30.0f;
	}


	//Air ducts End ////////////

	////////////////////////
	//Duct celing attachment
	////////////////////////

	IMesh* postMesh = myEngine->LoadMesh("post2.x");
	IModel* post[30];

	float incZ = -580;
	float incX = 135.0f;

	for (int i = 0; i < 20; i++)
	{
		post[i] = postMesh->CreateModel(0.0f, 140.0f, incZ);

		incZ = incZ + 30;
	}

	for (int i = 20; i < 30; i++)
	{
		post[i] = postMesh->CreateModel(incX, 140.0f, 5.0f);

		incX = incX - 30;
	}


	//duct celing attatchment End ///////////

	//////////
	//lightbox
	//////////

	IMesh* lightMesh = myEngine->LoadMesh("boxLight.x");
	//IModel* lightBox = lightMesh->CreateModel(0.0f, 145.0f, 20.0f);
	//lightBox->Scale(4.0f);

	IModel* lightBox2[30];
	float Xinc = 500;

	for (int i = 0; i < 5; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, 500.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}

	Xinc = 500;

	for (int i = 5; i < 10; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, 300.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}

	Xinc = 500;

	for (int i = 10; i < 15; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, 100.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}

	Xinc = 500;

	for (int i = 15; i < 20; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, -100.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}

	Xinc = 500;

	for (int i = 20; i < 25; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, -300.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}

	Xinc = 500;

	for (int i = 25; i < 30; i++)
	{
		lightBox2[i] = lightMesh->CreateModel(Xinc, 145.0f, -500.0f);
		lightBox2[i]->Scale(4.0f);

		Xinc = Xinc - 200.0f;
	}


	//lighbox End ///////////////////


	float frameTimer = myEngine->Timer(); // frame time for partical flames ((can be replaced with main frame time))

}

//void fireWeapon(player player, IModel* playerDummy, IModel* cameraDummy, IModel* bulletTracer[], vector3D facingVector, float lengthOfFV, vector3D fvNormal, vector3D dummyPosition, int bulletTracerSelection, const int kNumBulletTracers, string mapName,
//				wall mapWall,)
//{
//	float pMatrix[4][4];
//	float cMatrix[4][4];
//
//	if (player.currentWeapon.ammo <= 0 && player.currentWeapon.currentWeaponState != reloading)
//	{
//		player.currentWeapon.currentWeaponState = reloading;
//		player.currentWeapon.reloadTimer = 0.0f;
//	}
//	if (player.currentWeapon.currentWeaponState == active)
//	{
//		playerDummy->GetMatrix(&pMatrix[0][0]); // calls the matrix for the player, recording both the facing vector and the world position
//		cameraDummy->GetMatrix(&cMatrix[0][0]); // calls the matrix for the camera, recording both the facing vector and the world position
//
//		facingVector = { pMatrix[2][0], cMatrix[2][1], pMatrix[2][2] };
//		lengthOfFV = sqrt((pMatrix[2][0] * pMatrix[2][0]) + (cMatrix[2][1] * cMatrix[2][1]) + (pMatrix[2][2] * pMatrix[2][2]));
//		fvNormal = { pMatrix[2][0] / lengthOfFV, cMatrix[2][1] / lengthOfFV, pMatrix[2][2] / lengthOfFV };
//
//		dummyPosition = { pMatrix[3][0], pMatrix[3][1], pMatrix[3][2] };
//
//		bulletTracerSelection = (bulletTracerSelection + 1) % kNumBulletTracers;
//
//		bool wallHit = false;
//		if (mapName == "Map1.txt")
//		{
//			if (mapWall.size() != 0)
//			{
//				wallHit = raycastWall(fvNormal, dummyPosition, mapWall, bulletTracer[bulletTracerSelection], numberOfTargets, numberOfWalls);
//			}
//		}
//		if (!wallHit)
//		{
//			raycastShoot(fvNormal, dummyPosition, mapTarget, bulletTracer[bulletTracerSelection], numberOfTargets);//, 12.0f, 12.0f, 2.0f);
//		}
//
//		player.currentWeapon.ammo -= 1;
//		player.animationTimer = 0.1f;
//	}
//}
bool compare(const highScore& a, const  highScore& b)
{
	return (a.score > b.score);
}

// define a particle
struct SParticle
{
	IModel* mModel;
	float mMoveVector[3];
	float mVelocity;
	bool mActive = false;
};

SParticle particles[kTotalParticles];

void InitializeBarrelFires(I3DEngine* myEngine)
{
	// create particles

	// list of various particle skin file names
	const int totalParticleSkins = 3;
	const string particleSkinNames[totalParticleSkins] = { "009_tlxadd.tga", "010_tlxadd.tga", "010_tlxadd.tga" };

	IMesh* particleMesh = myEngine->LoadMesh("particle.x");

	for (int b = 0; b < kTotalBarrels; b++)
	{
		for (int i = 0; i < kParticlesPerBarrel; i++)
		{
			int particleNumber = i + (b * kParticlesPerBarrel);

			// create model
			particles[particleNumber].mModel = particleMesh->CreateModel((barrelXPositions[b] + Random(-5.0f, 5.0f)), barrelFlameYPos, (barrelZPositions[b] + Random(-3.0f, 7.0f)));

			particles[particleNumber].mModel->LookAt(0.0f, 20.0f, 0.0f);

			// set random skin
			int num = (int)Random(0, totalParticleSkins);
			particles[particleNumber].mModel->SetSkin(particleSkinNames[num]);

			// set random move vectors
			particles[particleNumber].mMoveVector[0] = Random(-1, 1);  // X move

			particles[particleNumber].mMoveVector[2] = Random(-1, 1);  // Z move
		}
	}
}

void BarrelUpdate(float frameTime/*, ICamera* myCamera*/)
{

	// activate next particle
	EmitBarrelParticle();

	// update particles
	UpdateBarrelParticles(frameTime);

}


// Find an inactive particle and activate it
void EmitBarrelParticle()
{
	for (int i = 0; i < kTotalParticles; i++)
	{
		// check if active
		if (particles[i].mActive == false)
		{
			// activate and skip rest
			particles[i].mActive = true;
		}
	}
}

// Update each particle based on their state
void UpdateBarrelParticles(/* ICamera* camera,*/ float& frameTime)
{
	
		for (int b = 0; b < kTotalBarrels; b++)
		{
			for (int i = 0; i < kParticlesPerBarrel; i++)
			{
				int particleNumber = i + (b * kParticlesPerBarrel);

				// check if active
				if (particles[particleNumber].mActive)
				{

					// update velocity
					particles[particleNumber].mVelocity = particles[particleNumber].mVelocity + (kGravity * frameTime);

					// move particle
					particles[particleNumber].mModel->MoveLocalX( particles[particleNumber].mMoveVector[0] * frameTime);
					particles[particleNumber].mModel->MoveLocalY(-particles[particleNumber].mVelocity * frameTime);
					particles[particleNumber].mModel->MoveLocalZ( particles[particleNumber].mMoveVector[2] * frameTime);

					// check if hit max height
					if (particles[particleNumber].mModel->GetLocalY() > Random(25, 50))
					{
						particles[particleNumber].mVelocity = kStartVelocity;
						particles[particleNumber].mModel->SetPosition(barrelXPositions[b] + Random(-5.0f, 5.0f), barrelFlameYPos, barrelZPositions[b] + Random(-5.0f, 5.0f));
						particles[particleNumber].mActive = false;
					}
				}
			}
		}
}


// Return a random number in the range between rangeMin and rangeMax inclusive
// range_min <= random number <= range_max
float Random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}