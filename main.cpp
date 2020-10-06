#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>

int mandelbrot(double ca, double cb, double max_it);

int main(int argc, const char** argv) {
	GLFWwindow* window;
	
	const double MAX_ITER = 100;
	const double XMAX = 2;
	const double YMAX = 1.5;
	const int HEIGHT = 1080;
	const int WIDTH = 1960;

	if (!glfwInit()) {
		printf("Couldn't init GLFW\n");
		return -1;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot set", NULL, NULL);
	if (!window) {
		printf("couldn't open window\n");
		return -1;
	}
	
	unsigned char* data = new unsigned char[WIDTH * HEIGHT * 3];

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

			double ca = -XMAX + (double(x) / WIDTH) * 2 * XMAX;
			double cb = -YMAX + (double(y) / HEIGHT) * 2 * YMAX;
			int weighting = 255 * (mandelbrot(ca, cb, MAX_ITER) / MAX_ITER);
			if (weighting == 255) {
				weighting = 0;
			}
			//float timeValue = glfwGetTime();
			//255 * (sin(timeValue) / 2.0f + 0.5f) 
			data[y * WIDTH * 3 + x * 3] = weighting;
			data[y * WIDTH * 3 + x * 3 + 1] = 0x00;//weighting;
			data[y * WIDTH * 3 + x * 3 + 2] = weighting;

		}
	}


	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();

	}

	return 0;
}

int mandelbrot(double ca, double cb, double max_it) {
	double za = 0;
	double zb = 0;

	double a = ca;
	double b = cb;
	int n = 0;
	double absz = 0;
	bool check = true;

	while (n < max_it && check) {
		za = a * a - b * b;
		zb = 2 * a * b;

		
		a = za + ca;
		b = zb + cb;

		//absz = sqrt(za * za + zb * zb);
		absz = fabs(za + zb);
		if (absz > 16) {
			check = false;
		}
		n = n + 1;
	}

	return n;
}