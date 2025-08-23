#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>
#include <string>

/**
* Application controls:
*
* Both modes:
* @escape:
*   Toggle to other mode
*
* Edit mode:
*
* @1: place points with left click, pan with right click, auto create line segments, contribute to current polygon
* @2: select nearest point to point with left click, drag originating within select point = move the point
*     (with affordance margin), pan with right click
* @3:
*  left click place the BALL at current mouse position, check if spawn is good, if no, move it to valid position, pan on right click
* @back_space: delete the currently selected item
* @4: left click place an EXIT at current mouse position, clicking on an EXIT makes it the selected item, pan on right click
* @enter:
*   enter while a point is selected 'confirms' the current polygon, subsequent points will belong to a new polygon
* @5: Polygon select mode: If clicking within polygon, that polygon becomes the selected item
*     Allows delection of polygon.
*     Clicking outside of polygon clears current selected item
*       If a polygon is selected, pressing enter cycles the selected item to through the points in the polygon
*
* Design choices (for time expedience) Once a polygon is confirmed, it cannot be edited again, changes? It will have to be
* deleted and then recreated.
*
* Play mode:
* @a: add left spin to the ball
* @d: add right spin to the ball
* @space: vertical jump impulse on the ball
* @back_space: restart level
*/

/*
	Progress goals:
	- Add the PGE extension for panning and zooming, integrate it into the application
	- Draw state string to screen for visibility and explainability
	- Always Init with a basic test level
	  - achieve via play mode always writing some basic level geo to the application game state
	- Implement Play mode
	- Then implement the editor
*/

namespace ngon {
	class Selectable {

	};
	class Polygon {
	public:
		std::vector<olc::vd2d> points;
		Polygon() = default;
	};
	// TODO consider moving these to their own *.h and *.cpp files to clean up this file
	/**
	* The player controls the ball in play mode
	*/
	class Ball {
		olc::vd2d position;
		void tick(float fElapsedTime) {

		}
	};
	class Goal;
	struct GameState {
		// Ngon is built from points. These points are connected to form a line segment
		// The line segments all connect to form the polygon
		std::vector<ngon::Polygon> shapes;
		std::vector<ngon::Goal> goals;
		ngon::Ball ball;
	};
	class ApplicationState;
	class Editing;
}

// Override base class with your custom functionality
class NgonPuzzle : public olc::PixelGameEngine
{
public:
	NgonPuzzle();

	ngon::GameState state;
	ngon::Editing* editing;
	ngon::ApplicationState* applicationState;


public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

namespace ngon {
	class Goal {
		// If the Ball overlaps the Goal then play a simple animation:
		// scale the ball down overtime, and sinusoidal motion rotate it around the goal
		// slowly lerp ball position to goal middle
		olc::vd2d position;
		void tick(float fElapsedTime) {

		}
	};

	static std::string StringFromGameState(GameState* state) {
		if (state == nullptr) {
			return "";
		}
		return "under construction";
	}

	class ApplicationState {
	public:
		NgonPuzzle* app;
		ApplicationState(NgonPuzzle* app) : app(app) { }
		/**
		* Application tick
		*/
		virtual bool OnUserUpdate(float fElapsedTime) = 0;
		/**
		* The first tick while this state is alive. Perform any clean up/set up before subsequent ticks.
		*/
		virtual void OnStateStart() = 0;
		virtual std::string GetStateString() = 0;
	};

	class Editing : public ApplicationState {
	public:
		Editing(NgonPuzzle* app) : ApplicationState(app) {

		}
		/**
		* OnStartEditing => make a new ball at this position
		*/
		olc::v_2d<double> ballPosition;
		// currently selected item
		// editor state: placing | selecting points | placing ball | placing exits | polygon selecting | 
	public:
		void OnStateStart() override {
		}
		bool OnUserUpdate(float fElapsedTime) override {
			return true;
		}
		std::string GetStateString() override {
			return "editing: under construction";
		}

	};

	class Playing : public ApplicationState {
	public:
		Playing(NgonPuzzle* app) : ApplicationState(app) {
		}
		void OnStateStart() override {
			// TEMP
			// Write test level data to the application
			// Later on, all we would do is nothing. Just start ticking straight away
			this->app->state = {
			};
		}
		bool OnUserUpdate(float fElapsedTime) override {
			return true;
		}
		std::string GetStateString() override {
			return "playing: under construction";
		}
	};
}

NgonPuzzle::NgonPuzzle() { sAppName = "Ngon puzzle builder"; }

bool NgonPuzzle::OnUserUpdate(float fElapsedTime) {
	// Clear Screen
	PixelGameEngine::Clear(olc::BLACK);
	// Handle user input
	if (PixelGameEngine::GetKey(olc::Key::ESCAPE).bReleased) {
		if (applicationState == editing) {
			applicationState = new ngon::Playing(this);
		}
		else {
			delete applicationState;
			applicationState = editing;
		}
		applicationState->OnStateStart();
	}
	applicationState->OnUserUpdate(fElapsedTime);
	// Draw
	PixelGameEngine::DrawString({ 0,0 }, applicationState->GetStateString());
	PixelGameEngine::DrawString({ 0,10 }, ngon::StringFromGameState(&this->state));
	return true;
}

bool NgonPuzzle::OnUserCreate() {
	// Called once at the start, so create things here
	editing = new ngon::Editing(this);
	applicationState = editing;
	applicationState->OnStateStart();
	return true;
}

int main()
{
	NgonPuzzle demo;
	if (demo.Construct(640, 480, 2, 2))
		demo.Start();
	return 0;
}

// VS2022, see func overloads? CTRL + Shift + space
