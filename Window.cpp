#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Cambio de camara
	if (key == GLFW_KEY_F1) {
		theWindow->topDown = true;
		theWindow->jugador = false;
		theWindow->avatar = false;
	}

	if (key == GLFW_KEY_F2) {
		theWindow->jugador = true;
		theWindow->topDown = false;
		theWindow->avatar = false;
	}

	if (key == GLFW_KEY_F3) {
		theWindow->avatar = true;
		theWindow->topDown = false;
		theWindow->jugador = false;
	}

	if (key == GLFW_KEY_F4 && action == GLFW_PRESS) {
		theWindow->alternaAnimacion = !(theWindow->alternaAnimacion);
	}

	// Movimiento avatar
	if (key == GLFW_KEY_W) {
		theWindow->trasladaXFrijolito += 0.1f;

		// MOVIMIENTO DE LOS BRAZOS
		if (theWindow->rotaBrazoDerecho < 45 && theWindow->rotaBrazoDerBool) {
			theWindow->rotaBrazoDerecho += 10.0f;
			theWindow->rotaBrazoIzquierdo -= 10.0f;
			
		}
		else if (theWindow->rotaBrazoDerecho > 45) {
			theWindow->rotaBrazoDerBool = false;
		}
		
		if (theWindow->rotaBrazoDerecho > -45 && !theWindow->rotaBrazoDerBool) {
			theWindow->rotaBrazoDerecho -= 10.0f;
			theWindow->rotaBrazoIzquierdo += 10.0f;
		}
		else if (theWindow->rotaBrazoDerecho < -45) {
			theWindow->rotaBrazoDerBool = true;
		}

		// MOVIMIENTO DE LAS PIERNAS
		if (theWindow->rotaPiernaDerecha > -45 && theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha -= 10.0f;
			theWindow->rotaPiernaIzquierda += 10.0f;

		}
		else if (theWindow->rotaPiernaDerecha < -45) {
			theWindow->rotaPiernaDerBool = false;
		}

		if (theWindow->rotaPiernaDerecha < 45 && !theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha += 10.0f;
			theWindow->rotaPiernaIzquierda -= 10.0f;
		}
		else if (theWindow->rotaPiernaDerecha > 45) {
			theWindow->rotaPiernaDerBool = true;
		}
		
		if (action == GLFW_RELEASE)
		{
			theWindow->mueveFrijolitoAdelBool = false;
			theWindow->rotaBrazoDerecho = 0.0f;
			theWindow->rotaBrazoIzquierdo = 0.0f;
			theWindow->rotaPiernaDerecha = 0.0f;
			theWindow->rotaPiernaIzquierda = 0.0f;
		}
	}

	if (key == GLFW_KEY_S) {
		theWindow->trasladaXFrijolito -= 0.1f;
		if (theWindow->rotaBrazoDerecho > -45 && theWindow->rotaBrazoDerBool) {
			theWindow->rotaBrazoDerecho -= 10.0f;
			theWindow->rotaBrazoIzquierdo += 10.0f;

		}
		else if (theWindow->rotaBrazoDerecho < -45) {
			theWindow->rotaBrazoDerBool = false;
		}

		if (theWindow->rotaBrazoDerecho < 45 && !theWindow->rotaBrazoDerBool) {
			theWindow->rotaBrazoDerecho += 10.0f;
			theWindow->rotaBrazoIzquierdo -= 10.0f;
		}
		else if (theWindow->rotaBrazoDerecho > 45) {
			theWindow->rotaBrazoDerBool = true;
		}

		if (theWindow->rotaPiernaDerecha < 45 && theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha += 10.0f;
			theWindow->rotaPiernaIzquierda -= 10.0f;

		}
		else if (theWindow->rotaPiernaDerecha > 45) {
			theWindow->rotaPiernaDerBool = false;
		}

		if (theWindow->rotaPiernaDerecha > -45 && !theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha -= 10.0f;
			theWindow->rotaPiernaIzquierda += 10.0f;
		}
		else if (theWindow->rotaPiernaDerecha < -45) {
			theWindow->rotaPiernaDerBool = true;
		}		
		
		if (action == GLFW_RELEASE)
		{
			theWindow->mueveFrijolitoAtrasBool = false;
			theWindow->rotaBrazoDerecho = 0.0f;
			theWindow->rotaBrazoIzquierdo = 0.0f;
			theWindow->rotaPiernaDerecha = 0.0f;
			theWindow->rotaPiernaIzquierda = 0.0f;
		}
	}

	if (key == GLFW_KEY_A) {
		theWindow->trasladaZFrijolito -= 0.1f;
		
		// MOVIMIENTO DE LAS PIERNAS
		if (theWindow->rotaPiernaDerecha > -45 && theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha -= 10.0f;
			theWindow->rotaPiernaIzquierda += 10.0f;

		}
		else if (theWindow->rotaPiernaDerecha < -45) {
			theWindow->rotaPiernaDerBool = false;
		}

		if (theWindow->rotaPiernaDerecha < 45 && !theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha += 10.0f;
			theWindow->rotaPiernaIzquierda -= 10.0f;
		}
		else if (theWindow->rotaPiernaDerecha > 45) {
			theWindow->rotaPiernaDerBool = true;
		}
		
		if (action == GLFW_RELEASE)
		{
			theWindow->mueveFrijolitoIzqBool = false;
			theWindow->rotaPiernaDerecha = 0.0f;
			theWindow->rotaPiernaIzquierda = 0.0f;
		}
	}

	if (key == GLFW_KEY_D) {
		theWindow->trasladaZFrijolito += 0.1f;
		
		// MOVIMIENTO DE LAS PIERNAS
		if (theWindow->rotaPiernaDerecha > -45 && theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha -= 10.0f;
			theWindow->rotaPiernaIzquierda += 10.0f;

		}
		else if (theWindow->rotaPiernaDerecha < -45) {
			theWindow->rotaPiernaDerBool = false;
		}

		if (theWindow->rotaPiernaDerecha < 45 && !theWindow->rotaPiernaDerBool) {
			theWindow->rotaPiernaDerecha += 10.0f;
			theWindow->rotaPiernaIzquierda -= 10.0f;
		}
		else if (theWindow->rotaPiernaDerecha > 45) {
			theWindow->rotaPiernaDerBool = true;
		}

		if (action == GLFW_RELEASE)
		{
			theWindow->mueveFrijolitoDerBool = false;
			theWindow->rotaPiernaDerecha = 0.0f;
			theWindow->rotaPiernaIzquierda = 0.0f;
		}
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		theWindow->apagaCinturonArriba = !(theWindow->apagaCinturonArriba);
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		theWindow->apagaCinturonAbajo = !(theWindow->apagaCinturonAbajo);
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		theWindow->apagaAkuDerecha = !(theWindow->apagaAkuDerecha);
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		theWindow->apagaAkuIzquierda = !(theWindow->apagaAkuIzquierda);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		theWindow->apagaAvatar = !(theWindow->apagaAvatar);
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		theWindow->apagaTablero = !(theWindow->apagaTablero);
	}

	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		theWindow->apagaFlippers = !(theWindow->apagaFlippers);
	}

	if (key == GLFW_KEY_Z)
	{
		if (action == GLFW_PRESS) {
			theWindow->flipper1 = 40.0f;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->flipper1 = 0.0f;
		}
	}

	if (key == GLFW_KEY_X)
	{
		if (action == GLFW_PRESS) {
			theWindow->flipper2 = 40.0f;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->flipper2 = 0.0f;
		}
	}

	if (key == GLFW_KEY_M)
	{
		if (action == GLFW_PRESS) {
			theWindow->flipper3 = -40.0f;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->flipper3 = 0.0f;
		}
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			theWindow->mouseDerecho = true;
		}
		else {
			theWindow->mouseDerecho = false;
		}
	}
	
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
