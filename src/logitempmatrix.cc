// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

static void _DrawTankTempGradient(Canvas *canvas, unsigned int tank,
		float temps[]) {
	int mtemp;
	int i, j, r, g, b;

	for (i = 1; i < 31; i++) {
		canvas->SetPixel(2 + (tank * 10), i, 100, 100, 100);
		canvas->SetPixel(10 + (tank * 10), i, 100, 100, 100);
	}

	for (i = 0; i < 8; i++) {
		canvas->SetPixel((2 + tank * 10) + i, 1, 100, 100, 100);
	}

	mtemp = (((temps[0] + temps[1] + temps[2]) / 3) - 35);

	cout << "mtemp = " << mtemp << endl;

	if (mtemp > 29) {
		mtemp = 29;
	} else {
		if (mtemp < 0) {
			mtemp = 0;
		}
	}

	for (j = 30; j > (30 - mtemp); j--) {
		r = (255 * j) / 30;
		g = (255 * (30 - j)) / 30;
		b = 0;

		for (i = 0; i < 7; i++) {
			canvas->SetPixel(3 + (tank * 10)+ i, j, r, g, b);
		}
	}
}

static void _DrawTankGradients(Canvas *canvas) {
	/*
	 * Let's create a simple animation. We use the canvas to draw
	 * pixels. We wait between each step to have a slower animation.
	 */

	int i;
	float temps[3 * 3];
	string str;

	while (1) {

		remove("temps.txt");
		system("wget http://192.168.0.104:14007/temps.txt");

		fstream myFile("temps.txt", std::ios_base::in);

		getline(myFile, str);
		cout << str << endl;

		for (i = 0; i < 9; i++) {
			myFile >> temps[i];
		}

		myFile.close();

		_DrawTankTempGradient(canvas, 0, &temps[6]);
		_DrawTankTempGradient(canvas, 1, &temps[0]);
		_DrawTankTempGradient(canvas, 2, &temps[3]);

		for (i = 0; i < 1000; i++) {
			usleep(1 * 10000);  // wait a little to slow down things.
		}
	}
}

int main(int argc, char *argv[]) {
	/*
	 * Set up GPIO pins. This fails when not running as root.
	 */
	GPIO io;
	if (!io.Init())
		return 1;

	cout << "Hello world" << endl;

	/*
	 * Set up the RGBMatrix. It implements a 'Canvas' interface.
	 */
	int rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
	int chain = 2;    // Number of boards chained together.
	int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
	Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);

	_DrawTankGradients(canvas);    // Using the canvas.

	// Animation finished. Shut down the RGB matrix.
	//canvas->Clear();
	delete canvas;

	return 0;
}
