#include <iostream>
#include "VisualDebugger.h"

using namespace std;

/*
	- GitHub (made public at submission)
		- https://github.com/nixonjoshua98/physx-pinball

	- HUD <JN_PinballScene::CustomRender>
		- Shows controls, score, and a basic 'Game Over' text when the game ends

	- Input
		- Press 'P' to restart the game once the player has lost
		- Kept default camera movement controls

	- Convex
		- Hexagon <JN_Hexagan> created using cos & sin with a bouncy material

	- Modifed <Renderer.cpp line 308>
		- Allow for hidden/non-rendered shapes - Used to hide the triggers and frame roof

	- <JN_TriggerBox> - Invisible box trigger
		- Want to see the triggers? Comment out <JN_TriggerBox.cppline 17> and you will see a white rectangle at the bottom of the frame

	- RevoluteJoint 'motor - <JN_Spinner>
		- Constant spinning object

	- <JN_Paddle>
		- Controllable paddles which use a RevoluteJoint to rotate
		- Has a rotation limit, for example, they cannot do a full spin

	- Score system
		- Gain points by hitting hexagons, paddles and spinners
		- Score increases passively with time
		- Lose points by losing a ball - 'dead ball'

	- Filters & collision groups
		- Examples
			- <JN_Sphere::JN_Sphere> SetupFiltering(JN_FilterGroup::BALLS, JN_FilterGroup::HEXAGONS | JN_FilterGroup::SPINNERS | JN_FilterGroup::PADDLES);
			- <JN_Paddle::JN_Paddle> SetupFiltering(JN_FilterGroup::PADDLES, JN_FilterGroup::BALLS);

	- Model loader - <JN_ModelLoader/JN_Model>:
		- File format: http://paulbourke.net/dataformats/obj/
		- Parses and cooks triangulated .obj files
		- Creates a compound object from the parsed data - not just one single mesh
			- Allows for materials to be given to individual shapes

	- Filter shader <JN_Scene line 9>
		- Added CCD (continous contact detection)

	- <JN_PinballFrame>
		- Compound object loaded using <JN_ModelLoader> with slight bouncy materials applied to shapes

	- Bumpers
		- Two bumpers part of the frame with bouncy materials (located at the top of the frame)		
*/
int main()
{
	try 
	{ 
		VisualDebugger::Init("Pinball | Joshua Nixon", 800, 800); 
	}
	catch (Exception exc) 
	{ 
		cerr << exc.what() << endl;
		return 0; 
	}

	VisualDebugger::Start();

	return 0;
}