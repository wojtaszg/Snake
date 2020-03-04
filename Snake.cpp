// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>

using namespace std;
using namespace sf;

int N = 30, M = 20;
const int blockSize = 25;

int dir, num = 4;

struct snake
{
	int x;
	int y;
}
s[100];

struct fruit
{
	int x;
	int y;
} f;

void tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0)
		s[0].y += 1;
	if (dir == 1)
		s[0].x -= 1;
	if (dir == 2)
		s[0].x += 1;
	if (dir == 3)
		s[0].y -= 1;

	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	if (s[0].x > N)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = N;
	if (s[0].y < 0)
		s[0].y = M;
	if (s[0].y > M)
		s[0].y = 0; 

	for (int i = 1; i < num; i++)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			num = i;
	}

}

int main()
{
	srand(time(0));
	Clock clock;
	float timer = 0, delay = 0.12;
	//int h = M * size;
	RenderWindow window(VideoMode(750, 500), "Snake");
	window.setFramerateLimit(60);

	Event event;
	Texture t1, t2,t3;
	t1.loadFromFile("images/white.jpg");
	t2.loadFromFile("images/green.jpg");
	t3.loadFromFile("images/red.jpg");

	Sprite sprite1(t1);
	sprite1.setScale(0.1,0.1);

	Sprite sprite2(t2);
	sprite2.setScale(0.1, 0.1);

	Sprite sprite3(t3);
	sprite3.setScale(0.1, 0.1);

	f.x = 10;
	f.y = 10;

	while (window.isOpen())
	{
		//
		float time = clock.getElapsedTime().asSeconds();
		//float time = clock();
		clock.restart();
		timer += time;

		window.pollEvent(event);
		if (event.type == Event::Closed)
		{
			window.close();
			break;
		}
		if (timer > delay)
		{
			timer = 0;
			tick();
		}

		
		if(Keyboard::isKeyPressed(Keyboard::Key::Down))
			dir = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			dir = 3;
	
		window.clear();


		for(int i=0; i<N;i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i*blockSize, j*blockSize);
				window.draw(sprite1);
			}

		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x * blockSize, s[i].y * blockSize);
			window.draw(sprite2);
		}

		sprite3.setPosition(f.x*blockSize, f.y*blockSize);
		window.draw(sprite3);
		window.display();
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
