# Ngon Puzzle Builder

## What is this?

My entry for the 2025 OLC code jam. Simple puzzle game. Control a sphere shape, try to reach the exit. Includes level editor, build your own level.

## Controls

### Editor

- 1: Add vertices 
  - Left Click: Add vertices to the current polygon at the mouse position
  - Backspace: Remove the most recently added vertex from the current polygon
  - Enter: Confirm the current polygon and create a new one
- 2: Move vertices 
  - Left Click: Move the nearest vertex to the mouse position
  - Backspace: delete the last moved vertex
- 3: Move Ball
  - Left Click: Move the ball to the mouse position
- 4: Add goals
  - Enter: Add a new goal at the mouse position
  - Left Click: move the nearest goal to the mouse position
  - Backspace: delete the last moved goal
- 5: Polygon select
  - Backspace: delete the selected polygon
  - Left click: select the nearest polygon
- Middle Mouse Button: Pan view
- Scroll Wheel: Zoom in and out
- Escape: Toggle to play mode
- equals (=): print ball physics state


### Gameplay

- A: Roll to the left
- D: Roll to the right
- Space: Jump (while touching a surface)
- equals (=): print ball physics state
- Escape: return to the editor
- Backspace: restart the level

## AI disclosure statement

I used ChatGPT to ask questions about C++ language features, some concrete examples include:
- How to invoke parent class constructor in child class
- How to inline initialize a struct
- How to make purely virtual class

The algorithm for resolving physics impulses in version 1.0.0 was provided by ChatGPT in psuedo code form. This is clearly marked in source code comments.

These could have been answered by Google Search I guess, but LLMs allow for fast follow up questions.

All source code was written by me through physical key tapping :D
