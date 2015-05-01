// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "led-matrix.h"
#include "curl_easy.h"
#include "curl_option.h"

using namespace std;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using curl::curl_easy;
using curl::make_option;

struct MemoryStruct {
	char *memory;
	size_t size;
};

static float temps[9];

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
			canvas->SetPixel(3 + (tank * 10) + i, j, r, g, b);
		}
	}
}

static size_t WriteMemoryCallback(char *contents, size_t size, size_t nmemb,
		void *userp) {

	size_t i, j;
	string str = "";

	j = 0;
	for (i = 0; i < nmemb; i++) {
		if (contents[i] == '\n') {
			try {
				temps[j] = stof(str);
				cout << "f=" << temps[j] << endl;
				j++;
				str = "";
			} catch (...) {
				str = "";
			}
		} else {
			str = str + contents[i];
		}
	}

	return nmemb;
}

static void _DrawTankGradients(Canvas *canvas) {
	/*
	 * Let's create a simple animation. We use the canvas to draw
	 * pixels. We wait between each step to have a slower animation.
	 */

	int i;
	curl_easy easy;
	char data[1024];

	easy.add<CURLOPT_URL>("http://192.168.0.104:14007/temps.txt");
	easy.add<CURLOPT_WRITEFUNCTION>(WriteMemoryCallback);
	easy.add<CURLOPT_WRITEDATA>(data);
	easy.add<CURLOPT_USERAGENT>("libcurl-agent/1.0");
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);

	while (1) {

		try {
			easy.perform();
		} catch (curl_easy_exception error) {
			// If you want to get the entire error stack we can do:
			//auto errors = error.what();
			// Otherwise we could print the stack like this:
			error.print_traceback();
			// Note that the printing the stack will erase it
		}

		_DrawTankTempGradient(canvas, 0, &temps[6]);
		_DrawTankTempGradient(canvas, 1, &temps[0]);
		_DrawTankTempGradient(canvas, 2, &temps[3]);

		for (i = 0; i < 1000; i++) {
			usleep(1 * 10000);  // wait a little to slow down things.
		}
	}
}

int main(void) {
/*
 * Set up GPIO pins. This fails when not running as root.
 */
GPIO io;
if (!io.Init())
	return 1;

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
