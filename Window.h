#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	// Camaras
	GLfloat getTopDown() { return topDown; }
	GLfloat getJugador() { return jugador; }
	GLfloat getAvatar() { return avatar; }
	// Flippers movimiento
	GLfloat getFlipper1() { return flipper1; }
	GLfloat getFlipper2() { return flipper2; }
	GLfloat getFlipper3() { return flipper3; }
	// Resorte y palanca
	GLboolean getMouseDerecho() { return mouseDerecho; }
	// Mueve avatar
	GLfloat getTrasladaXFrijolito() { return trasladaXFrijolito; }
	GLfloat getTrasladaZFrijolito() { return trasladaZFrijolito; }
	GLboolean getMueveFrijolitoAdelBool() { return mueveFrijolitoAdelBool; }
	GLboolean getMueveFrijolitoAtrasBool() { return mueveFrijolitoAtrasBool; }
	GLboolean getMueveFrijolitoIzqBool() { return mueveFrijolitoIzqBool; }
	GLboolean getMueveFrijolitoDerBool() { return mueveFrijolitoDerBool; }
	GLfloat getRotaBrazoIzquierdo() { return rotaBrazoIzquierdo; }
	GLfloat getRotaBrazoDerecho() { return rotaBrazoDerecho; }
	GLfloat getRotaPiernaIzquierda() { return rotaPiernaIzquierda; }
	GLfloat getRotaPiernaDerecha() { return rotaPiernaDerecha; }
	// Iluminacion
	GLboolean getapagaAkuDerecha() { return apagaAkuDerecha; }
	GLboolean getapagaAkuIzquierda() { return apagaAkuIzquierda; }
	GLboolean getapagaCinturonArriba() { return apagaCinturonArriba; }
	GLboolean getapagaCinturonAbajo() { return apagaCinturonAbajo; }

	GLboolean getapagaAvatar() { return apagaAvatar; }
	GLboolean getapagaTablero() { return apagaTablero; }
	GLboolean getapagaFlippers() { return apagaFlippers; }

	// Animacion canica
	GLboolean getAlternaAnimacion() { return alternaAnimacion; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	// Camaras
	GLboolean topDown = false;
	GLboolean jugador = true;
	GLboolean avatar = false;
	// Flippers movimiento
	GLfloat flipper1 = 0.0f;
	GLfloat flipper2 = 0.0f;
	GLfloat flipper3 = 0.0f;
	// Resorte y palanca
	GLboolean mouseDerecho = false;
	// Avatar
	GLfloat trasladaXFrijolito = 0.0f;
	GLfloat trasladaZFrijolito = 0.0f;
	GLboolean mueveFrijolitoAdelBool = false;
	GLboolean mueveFrijolitoAtrasBool = false;
	GLboolean mueveFrijolitoIzqBool = false;
	GLboolean mueveFrijolitoDerBool = false;
	GLfloat rotaBrazoIzquierdo = 0.0f;
	GLfloat rotaBrazoDerecho = 0.0f;
	GLfloat rotaPiernaIzquierda = 0.0f;
	GLfloat rotaPiernaDerecha = 0.0f;
	GLboolean rotaBrazoIzqBool = false;
	GLboolean rotaBrazoDerBool = true;
	GLboolean rotaPiernaIzqBool = false;
	GLboolean rotaPiernaDerBool = true;
	// Iluminacion
	GLboolean apagaAkuDerecha = false;
	GLboolean apagaAkuIzquierda = false;
	GLboolean apagaCinturonArriba = false;
	GLboolean apagaCinturonAbajo = false;

	GLboolean apagaAvatar = false;
	GLboolean apagaTablero = false;
	GLboolean apagaFlippers = false;

	GLboolean alternaAnimacion = true;

	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

