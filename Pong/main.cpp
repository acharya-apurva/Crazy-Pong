#include "raylib.h"
//#include <iostream>
//using namespace std;


//rectangle always starts drawing from the top left that is why all the off sets

struct Ball //struct is a collection of variables and methods for Ball
{
	float x, y, speedX, speedY, radius;
	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, YELLOW);
	}
};

struct Rect
{
	float x, y, speed, width, height;
	Rectangle GetRect() {
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}
	void Draw()
	{
		DrawRectangleRec(GetRect(), YELLOW);
	}
};

int main()
{
	//the thing that pops up while pressing play above is the console window not the application window
	InitWindow(800, 600, "Pong"); // for application window
	//when ever you create something you also have to detroy it or you will have a memory leak thus closewindow
	SetWindowState(FLAG_VSYNC_HINT); // to settle the refresh rate to the refrest rate of the monitor

	Ball b;
	b.x = GetScreenWidth() / 2.0f;
	b.y = GetScreenHeight() / 2.0f;
	b.speedX = 300;
	b.speedY = 300;
	b.radius = 5;

	Rect r1;
	r1.width = 10;
	r1.height = 100;
	r1.x = 50;
	r1.y = GetScreenHeight() / 2 ;
	r1.speed = 500;

	Rect r2;
	r2.width = 10;
	r2.height = 100;
	r2.x = GetScreenWidth() - 50 ;
	r2.y = GetScreenHeight() / 2;
	r2.speed = 500;

	const char* winnerText = nullptr;
	const char* helpText = "Press space to play again";

	while (!WindowShouldClose()) { // game loop to keep the window open for its entire lifetime we will break out of the loop when we press
		//the X button or the key to exit out of window
		b.x += b.speedX * GetFrameTime(); //since we dont want the ball to move faster on systems with heigher fps, multiplying it with get
		//frame time makes ballX smaller if frame rates are higher (making up for the frame rate difference)
		b.y += b.speedY * GetFrameTime();
		
		//we want the ball to bounce back if it is going off the screen
		if (b.y < 0)
		{
			b.y = 0;
			b.speedY *= -1; 
		}
		if (b.y > GetScreenHeight()) //bottom of the screen
		{
			b.y = GetScreenHeight(); 
			b.speedY *= -1;
		}

		if (IsKeyDown(KEY_W))
		{
			if (r1.y > 0 + r1.height/2) {
				r1.y -= r1.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_S))
		{
			if (r1.y < GetScreenHeight() - r1.height/2) {
				r1.y += r1.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_A))
		{
			if (r1.x > 0 + r1.width/2 ) {
				r1.x -= r1.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_D))
		{
			if (r1.x < (GetScreenWidth() / 2) - (r2.width / 2) - (b.radius * 2) - 50)
			{
				r1.x += r1.speed * GetFrameTime();
			}
		}

		if (IsKeyDown(KEY_UP))
		{
			if (r2.y > 0 + r2.height / 2) {
				r2.y -= r2.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_DOWN))
		{
			if (r2.y < GetScreenHeight() - r2.height / 2) {
				r2.y += r2.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_LEFT))
		{
			if (r2.x > (GetScreenWidth()/2) + r2.width/2 + (b.radius*2) + 50) {
				r2.x -= r2.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			if (r2.x < GetScreenWidth() - r2.width / 2) {
				r2.x += r2.speed * GetFrameTime();
			}
		}

		


		if (CheckCollisionCircleRec(Vector2{ b.x,b.y }, 5, r1.GetRect()))
		{
			if (b.speedX < 0) {
				b.speedX *= -1.1f; //if its still touching the paddle after it already touched once it goes on the same direction again thats why inside the condition
				b.speedY = (b.y - r1.y) / (r1.height / 2) * b.speedX ; //so that the ball goes up when it hits the lower side of the rectangle and vice versa
				//versa basically making sure that the value is between 1 and -1 and multiplying by the speed x to increase speed

			}
		}
		if (CheckCollisionCircleRec(Vector2{ b.x,b.y }, 5, r2.GetRect()))
		{
			if (b.speedX > 0)
			{
				b.speedX *= -1.1f; //by .1f to speed up the ball everytime 
				b.speedY = (b.y - r2.y) / (r2.height / 2) * -b.speedX ;
			}
		}
		if (b.x < 0)
		{
			winnerText = "Player 2 is the winner";
		}
		if (b.x > GetScreenWidth())
		{
			winnerText = "Player 1 is the winner";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)) //resetting the game when space is pressed
		{
			b.x = GetScreenWidth() / 2;
			b.y = GetScreenHeight() / 2;
			b.speedX = 300;
			b.speedY = 300;
			winnerText = nullptr;
		}



		BeginDrawing(); // to start the rendering process
			ClearBackground(BLACK); //so that we can color the background of the window
			b.Draw();
			r1.Draw();
			r2.Draw();
			//DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //rectangle draws from the top left of its position
			//DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE);

			if (winnerText) //winnerText is not a null pointer
			{
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
				int textWidth2 = MeasureText(helpText, 20);
				DrawText(helpText, GetScreenWidth() / 2 - textWidth2 / 2, GetScreenHeight() / 2 - 30 * 2 - 20, 20, WHITE);
			}

			DrawFPS(10, 10); // to show the frames per second and 10 10 is like the cartesian coordinate system
		EndDrawing(); //ends the drawing process and pulls some event always have begindrawing,clearbackground, and enddrawing
	}
	CloseWindow();
	return 0;

	//everything is function of raylib from the raylib cheatsheet
	//https://www.youtube.com/watch?v=LvpS3ILwQNA
}