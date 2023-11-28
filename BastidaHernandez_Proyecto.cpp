/*
Semestre 2024-1
Proyecto Final de
	Karen Mariel Bastida Vargas
	Humberto Ignacio Hernández Olvera
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
bool cambiaNumeroVisible = false;
float cambiaNumeroVisibleOffset = 0.0f;
bool cambiaNumeroDecenas = false;
float cambiaNumeroOffset = 0.0f;

// ANIMACION DE DIA Y NOCHE
float tiempoDiaNoche = 0.0f, maxTiempo = 150;

// ANIMACION DE INICIO
float retraeResorte = 1.0f, retraeResorteOffset = 0.05f;
float muevePalanca = 0.0f, muevePalancaOffset = 0.5f;
float iniciaCanica = 0.0f, iniciaCanicaOffset = 0.5f;
float rotaCanicaInicio = 0.0f, rotaCanicaInicioOffset = 10.0f;
float mueveAku = 60.0f, mueveAkuOffset = 0.1f;
float rotaAku = 0.0f, rotaAkuOffset = 2.0f;
float mueveCinturon = 30.0f, mueveCinturonOffset = 0.15f;
float rotaCinturon = 0.0f, rotaCinturonOffset = 10.0f;
float rotaAntebrazoSamurai = 100.0f, rotaAntebrazoSamuraiOffset = 2.0f;
float rotaConejitoSamurai = 100.0f, rotaConejitoSamuraiOffset = 2.0f;
float mueveSamurai = 0.0f, mueveSamuraiOffset = 0.2f;
bool akuTraslacion = true, cinturonTraslacion = true, cinturonRotacion = true;
bool antebrazoRotacion = true, conejitoRotacion = true, samuraiTraslacion = true;
bool iniciaAnimacionPrincipal = false, canicaEnJuego = false;
bool liberaResorte = false;

// ANIMACION DE CANICA 1
float mueveCanica1 = 0.0f, mueveCanica1Offset = 1.0f;
float mueveXCanica1 = 0.0f, mueveXCanica1Offset = 0.5f;
float rotaAdelanteCanica1 = 0.0f, rotaAdelanteCanica1Offset = 10.0f;
float rotaYCanica1 = 0.0f, rotaYCanica1Offset = 5.0f;
bool subeCanica = true, enCurva1 = false, enCurva2 = false, saleCurva = false, pegaFlipper = false;
bool pegaSimbolo = false, pegaParedFinal = false, rebotaPierde = false;

// ANIMACION DE PERDIDA
float deslizaCanica = 0.0f, deslizaCanicaOffset = 0.5f;
float rotaCanicaDesliza = 0.0f, rotaCanicaDeslizaOffset = 10.0f;
bool derrota = false;

// ANIMACION PUNTUACION
int punt0 = 0, punt1 = 0, punt2 = 5, punt3 = 7, punt4 = 9, punt5 = 9, punt6 = 9, punt7 = 9, punt8 = 9;

// VARIABLES KEYFRAMES
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;
float ciclomenosX, ciclomenosX2, ciclomasZ, ciclomasZ2, ciclomenosZ, ciclomenosZ2, ciclorota, ciclorota2, ciclorotaY, ciclorotaY2;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

// --------------------------- Texturas
// Texturas del pinball
Texture AceroTexture;
Texture pisoTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;
Texture Numero3Texture;
Texture Numero4Texture;
Texture Numero5Texture;
Texture Numero6Texture;
Texture Numero7Texture;
Texture Numero8Texture;
Texture Numero9Texture;
Texture Numero0Texture;

// Texturas de mucha lucha
Texture cinturonTexture;

// Texturas de samurai jack
Texture akuTexture;

//--------------------------- Modelos
// Modelos del pinball
Model PinballCarcasa_M;
Model PinballCristal_M;
Model CanicaMetalica_M;
Model Flipper1_M;
Model Flipper2_M;
Model Flipper3_M;
Model Resorte_M;
Model Palanca_M;
Model Moneda_M;
Model Palito_M;

// Modelos de mucha lucha
Model FrijolitoCuerpo_M;
Model FrijolitoBrazoIzq_M;
Model FrijolitoBrazoDer_M;
Model FrijolitoPiernaIzq_M;
Model FrijolitoPiernaDer_M;
Model LaPulga_M;
Model Bus_M;
Model Microfono_M;
Model Ring_M;

// Modelos de samurai jack
Model SamuraiJackEspada_M;
Model SamuraiJackCuerpo_M;
Model SamuraiJackAntebrazo_M;
Model SamuraiJackConejito_M;
Model SamuraiJackSimbolo_M;
Model SamuraiJackSimboloHuellitas_M;
Model SamuraiJackAku_M;

Skybox skybox;
Skybox skyboxNoche;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
DirectionalLight mainLight2;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights1[MAX_POINT_LIGHTS]; //Luz que tiene al final
PointLight pointLights2[MAX_POINT_LIGHTS]; //Luz que tiene al final
PointLight pointLights3[MAX_POINT_LIGHTS];
PointLight pointLights4[MAX_POINT_LIGHTS];
PointLight pointLights5[MAX_POINT_LIGHTS];

SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights1[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

std::vector<float> getCoordsTexture(int numeroRenderizar) {
	std::vector<float> temp;
	/*if (toffsetnumerocambiau > 1.0)
		toffsetnumerocambiau = 0.0;*/
	switch (numeroRenderizar)
	{
	case 1:
		temp.push_back(0.0);
		temp.push_back(1.0);
		break;
	case 2:
		temp.push_back(0.25);
		temp.push_back(1.0);
		break;
	case 3:
		temp.push_back(0.50);
		temp.push_back(1.0);
		break;
	case 4:
		temp.push_back(0.75);
		temp.push_back(1.0);
		break;
	case 5:
		temp.push_back(0.0);
		temp.push_back(0.66);
		break;
	case 6:
		temp.push_back(0.25);
		temp.push_back(0.66);
		break;
	case 7:
		temp.push_back(0.50);
		temp.push_back(0.66);
		break;
	case 8:
		temp.push_back(0.75);
		temp.push_back(0.66);
		break;
	case 9:
		temp.push_back(0.0);
		temp.push_back(0.33);
		break;
	case 0:
		temp.push_back(0.25);
		temp.push_back(0.33);
		break;
	default:
		temp.push_back(0.0);
		temp.push_back(0.0);
		break;
	}
	return temp; // (toffsetnumerocambiau, toffsetnumerov)
}

//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

}

// meshList[7]
void CrearPrimitiva1()
{
	unsigned int primitiva1_indices[] = {
		// down
		0, 1, 2, //ABC
		1, 3, 4, //BDE
		4, 5, 6, //EFG
		2, 5, 7, //CFH
		1, 2, 5, //BCF
		1, 4, 5, //BEF

		// up
		8, 9, 10,	//A1B1C1
		9, 11, 12,	//B1D1E1
		12, 13, 14, //E1F1G1
		10, 13, 15,	//C1F1H1
		9, 10, 13,	//B1C1F1
		9, 12, 13,	//B1E1F1

		//sides
		16, 17, 18,//AA1B1
		16, 18, 19,//AB1B
		19, 18, 20,//BB1D1
		19, 20, 21,//BD1D
		21, 20, 22,//DD1E1
		21, 22, 23,//DE1E
		23, 22, 24,//EE1G1
		23, 24, 25,//EG1G
		25, 24, 26,//GG1F1
		25, 26, 27,//GF1F
		27, 26, 28,//FF1H1
		27, 28, 29,//FH1H
		29, 28, 30,//HH1C1
		29, 30, 31,//HC1C
		31, 30, 32,//CC1A1
		31, 32, 33,//CA1A


	};

	GLfloat primitiva1_vertices[] = {

		//x			y		z		S		T		NX		NY		NZ

		 0.0f,		0.0f,	0.6,	0.5f,	1.0f,	0.0f,	1.0f,	0.0f, //A
		 -0.2f,		0.0f,	0.2f,	0.25f,	0.75f,	0.0f,	1.0f,	0.0f, //B
		 0.2,		0.0f,	0.2f,	0.75,	0.75f,	0.0f,	1.0f,	0.0f, //C
		 -0.6f,		0.0f,	0.0f,	0.0f,	0.5f,	0.0f,	1.0f,	0.0f, //D
		 -0.2f,		0.0f,	-0.2f,	0.25,	0.25f,	0.0f,	1.0f,	0.0f, //E
		 0.2f,		0.0f,	-0.2f,	0.75f,	0.25f,	0.0f,	1.0f,	0.0f, //F
		 0.0f,		0.0f,	-0.6f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f, //G
		 0.6f,		0.0f,	0.0f,	1.0,	0.5f,	0.0f,	1.0f,	0.0f, //H

		 0.0f,		1.0f,	0.6,	0.5f,	1.0f,	0.0f,	-1.0f,	0.0f, //A1
		 -0.2f,		1.0f,	0.2f,	0.25f,	0.75f,	0.0f,	-1.0f,	0.0f, //B1
		 0.2,		1.0f,	0.2f,	0.75,	0.75f,	0.0f,	-1.0f,	0.0f, //C1
		 -0.6f,		1.0f,	0.0f,	0.0f,	0.5f,	0.0f,	-1.0f,	0.0f, //D1
		 -0.2f,		1.0f,	-0.2f,	0.25,	0.25f,	0.0f,	-1.0f,	0.0f, //E1
		 0.2f,		1.0f,	-0.2f,	0.75f,	0.25f,	0.0f,	-1.0f,	0.0f, //F1
		 0.0f,		1.0f,	-0.6f,	0.5f,	0.0f,	0.0f,	-1.0f,	0.0f, //G1
		 0.6f,		1.0f,	0.0f,	1.0,	0.5f,	0.0f,	-1.0f,	0.0f, //H1

		0.0f,		0.0f,	0.6,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //A//AA1B1
		 0.0f,		1.0f,	0.6,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //A1//AB1B

		-0.2f,		1.0f,	0.2f,	0.0,	0.3f,	0.0f,	0.0f,	0.0f, //B1//BB1D1
		-0.2f,		0.0f,	0.2f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //B//BD1D

		-0.6f,		1.0f,	0.0f,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //D1//DD1E1
		-0.6f,		0.0f,	0.0f,	0.0,	0.3f,	0.0f,	0.0f,	0.0f, //D//DD1E

		-0.2f,		1.0f,	-0.2f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //E1//EE1G1
		-0.2f,		0.0f,	-0.2f,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //E//EE1G

		0.0f,		1.0f,	-0.6f,	0.0,	0.3f,	0.0f,	0.0f,	0.0f, //G1//GG1F1
		0.0f,		0.0f,	-0.6f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //G//GG1F

		0.2f,		1.0f,	-0.2f,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //F1//FF1H1
		0.2f,		0.0f,	-0.2f,	0.0f,	0.3f,	0.0f,	0.0f,	0.0f, //F//FF1H

		0.6f,		1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //H1//HH1C1
		0.6f,		0.0f,	0.0f,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //H//HH1C

		0.2,		1.0f,	0.2f,	0.0,	0.3f,	0.0f,	0.0f,	0.0f, //C1//CC1A1
		0.2,		0.0f,	0.2f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f, //C//CC1A

		0.0f,		1.0f,	0.6,	0.3f,	0.0f,	0.0f,	0.0f,	0.0f, //A1
		0.0f,		0.0f,	0.6,	0.0,	0.3f,	0.0f,	0.0f,	0.0f, //A



	};

	Mesh* primitiva1 = new Mesh();
	primitiva1->CreateMesh(primitiva1_vertices, primitiva1_indices, 272, 84); //vertices //indices
	meshList.push_back(primitiva1);

}

// meshList[8]
void CrearPrimitiva2()
{
	unsigned int primitiva2_indices[] = {
		// down
		0, 1, 2, //ABC
		0, 2, 3, //ACL

		2, 3, 4, //CLK
		2, 4, 5, //CKD

		5, 4, 6, //DKE
		4, 6, 7, //KEJ

		7, 6, 8, //JEF
		7, 8, 9, //JFI

		9, 8, 10,//IFG
		9, 10, 11,//IGH

		//up
		12, 13, 14, //A1B1C1
		12, 14, 15, //A1C1L1

		14, 15, 16,//C1L1K1
		14, 16, 17,//C1K1D1

		17, 16, 18,//D1K1E1
		16, 18, 19,//K1E1J1

		19, 18, 20,//J1E1F1
		19, 20, 21, //J1F1I1

		21, 20, 22,//I1F1G1
		21, 22, 23,//I1G1H1

		//sides
		24, 25, 26, //AA1B1
		24, 26, 27, //AB1B
		27, 26, 28, //BB1C1
		27, 28, 29, //BC1C
		29, 28, 30, //CC1D1
		29, 30, 31, //CD1D
		31, 30, 32, //DD1E1
		31, 32, 33, //DE1E
		33, 32, 34, //EE1F1
		33, 34, 35, //EF1F
		35, 34, 36, //FF1G1
		35, 36, 37, //FG1G
		37, 36, 38, //GG1H1
		37, 38, 39, //GH1H
		39, 38, 40, //HH1I1
		39, 40, 41, //HI1I
		41, 40, 42, //II1J1
		41, 42, 43, //IJ1J
		43, 42, 44, //JJ1K1
		43, 44, 45, //JK1K
		45, 44, 46, //KK1L1
		45, 46, 47, //KL1L
		47, 46, 48, //LL1A1
		47, 48, 49, //LA1A

	};

	GLfloat primitiva2_vertices[] = {

		//x			y		z		S		T		NX		NY		NZ

		0.0f,		0.0f,	0.35,	0.0f,	0.7f,	0.0f,	1.0f,	0.0f, //A
		0.0f,		0.0f,	0.15f,	0.0f,	0.3f,	0.0f,	1.0f,	0.0f, //B
		0.25,		0.0f,	0.15f,	0.25f,	0.3f,	0.0f,	1.0f,	0.0f, //C
		0.25f,		0.0f,	0.35f,	0.25f,	0.7f,	0.0f,	1.0f,	0.0f, //L
		0.35f,		0.0f,	0.4f,	0.35f,	0.8f,	0.0f,	1.0f,	0.0f, //K
		0.35f,		0.0f,	0.1f,	0.35f,	0.2f,	0.0f,	1.0f,	0.0f, //D
		0.65f,		0.0f,	0.1f,	0.65f,	0.2f,	0.0f,	1.0f,	0.0f, //E
		0.65f,		0.0f,	0.4f,	0.65f,	0.8f,	0.0f,	1.0f,	0.0f, //J
		0.75f,		0.0f,	0.15,	0.75f,	0.3f,	0.0f,	1.0f,	0.0f, //F
		0.75f,		0.0f,	0.35f,	0.75f,	0.7f,	0.0f,	1.0f,	0.0f, //I
		1.0,		0.0f,	0.15f,	1.0f,	0.3f,	0.0f,	1.0f,	0.0f, //G
		1.0f,		0.0f,	0.35f,	1.0f,	0.7f,	0.0f,	1.0f,	0.0f, //H

		0.0f,		0.2f,	0.35,	1.0f,	0.7f,	0.0f,	-1.0f,	0.0f, //A1
		0.0f,		0.2f,	0.15f,	1.0f,	0.3f,	0.0f,	-1.0f,	0.0f, //B1
		0.25,		0.2f,	0.15f,	0.75f,	0.3f,	0.0f,	-1.0f,	0.0f, //C1
		0.25f,		0.2f,	0.35f,	0.75f,	0.7f,	0.0f,	-1.0f,	0.0f, //L1
		0.35f,		0.2f,	0.4f,	0.65f,	0.8f,	0.0f,	-1.0f,	0.0f, //K1
		0.35f,		0.2f,	0.1f,	0.65f,	0.2f,	0.0f,	-1.0f,	0.0f, //D1
		0.65f,		0.2f,	0.1f,	0.35f,	0.2f,	0.0f,	-1.0f,	0.0f, //E1
		0.65f,		0.2f,	0.4f,	0.35f,	0.8f,	0.0f,	-1.0f,	0.0f, //J1
		0.75f,		0.2f,	0.15,	0.25f,	0.3f,	0.0f,	-1.0f,	0.0f, //F1
		0.75f,		0.2f,	0.35f,	0.25f,	0.7f,	0.0f,	-1.0f,	0.0f, //I1
		1.0,		0.2f,	0.15f,	0.0f,	0.3f,	0.0f,	-1.0f,	0.0f, //G1
		1.0f,		0.2f,	0.35f,	0.0f,	0.7f,	0.0f,	-1.0f,	0.0f, //H1
		//S		T
	   0.0f,		0.0f,	0.35,	0.0f,	0.8f,	1.0f,	0.0f,	1.0f, //A
	   0.0f,		0.2f,	0.35,	0.1f,	0.8f,	1.0f,	0.0f,	1.0f, //A1
	   0.0f,		0.2f,	0.15f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f, //B1
	   0.0f,		0.0f,	0.15f,	0.1f,	1.0f,	1.0f,	0.0f,	1.0f, //B
	   0.25,		0.2f,	0.15f,	0.0f,	0.8f,	1.0f,	0.0f,	1.0f, //C1
	   0.25,		0.0f,	0.15f,	0.1f,	0.8f,	1.0f,	0.0f,	1.0f, //C
	   0.35f,		0.2f,	0.1f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f, //D1
	   0.35f,		0.0f,	0.1f,	0.1f,	1.0f,	1.0f,	0.0f,	1.0f, //D
	   0.65f,		0.2f,	0.1f,	0.0f,	0.8f,	-1.0f,	0.0f,	1.0f, //E1
	   0.65f,		0.0f,	0.1f,	0.1f,	0.8f,	-1.0f,	0.0f,	1.0f, //E
	   0.75f,		0.2f,	0.15,	0.0f,	1.0f,	-1.0f,	0.0f,	1.0f, //F1
	   0.75f,		0.0f,	0.15,	0.1f,	1.0f,	-1.0f,	0.0f,	1.0f, //F
	   1.0,		0.2f,	0.15f,	0.0f,	0.8f,	-1.0f,	0.0f,	1.0f, //G1
	   1.0,		0.0f,	0.15f,	0.1f,	0.8f,	-1.0f,	0.0f,	1.0f, //G
	   1.0f,		0.2f,	0.35f,	0.0f,	1.0f,	-1.0f,	0.0f,	-1.0f, //H1
	   1.0f,		0.0f,	0.35f,	0.1f,	1.0f,	-1.0f,	0.0f,	-1.0f, //H
	   0.75f,		0.2f,	0.35f,	0.0f,	0.8f,	-1.0f,	0.0f,	-1.0f, //I1
	   0.75f,		0.0f,	0.35f,	0.1f,	0.8f,	-1.0f,	0.0f,	-1.0f, //I
	   0.65f,		0.2f,	0.4f,	0.0f,	1.0f,	-1.0f,	0.0f,	-1.0f, //J1
	   0.65f,		0.0f,	0.4f,	0.1f,	1.0f,	-1.0f,	0.0f,	-1.0f, //J
	   0.35f,		0.2f,	0.4f,	0.0f,	0.8f,	1.0f,	0.0f,	-1.0f, //K1
	   0.35f,		0.0f,	0.4f,	0.1f,	0.8f,	1.0f,	0.0f,	-1.0f, //K
	   0.25f,		0.2f,	0.35f,	0.0f,	1.0f,	1.0f,	0.0f,	-1.0f, //L1
	   0.25f,		0.0f,	0.35f,	0.1f,	1.0f,	1.0f,	0.0f,	-1.0f, //L
	   0.0f,		0.2f,	0.35,	0.0f,	0.8f,	0.0f,	0.0f,	-1.0f, //A1
	   0.0f,		0.0f,	0.35,	0.1f,	0.8f,	0.0f,	0.0f,	-1.0f, //A

	};

	Mesh* primitiva2 = new Mesh();
	primitiva2->CreateMesh(primitiva2_vertices, primitiva2_indices, 400, 132); //vertices //indices
	meshList.push_back(primitiva2);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void inputKeyframes(bool* keys);

//NEW// Keyframes
float movCanica_x = 0.0f, movCanica_z = 0.0f;

float rotaPulga = 0.0f, rotaFlipper = 0.0f, escalaResorte = 0.0f, desplazaPalanca = 0.0f, rotaDomino5 = 0.0f;
bool cambiaDirx = false, cambiaDirz = false;

float cicloMovz1 = 0.0f, cicloMovz2 = 0.0f;
float cicloCambiaDirx1 = 0.0f, cicloCambiaDirx2 = 0.0f;
float cicloCambiaDirz1 = 0.0f, cicloCambiaDirz2 = 0.0f;
float cicloRotaPulga1 = 0.0f, cicloRotaPulga2 = 0.0f;
float cicloFlipper1 = 0.0f, cicloFlipper2 = 0.0f;
float cicloResorte1 = 0.0f, cicloResorte2 = 0.0f;
float cicloPalanca1 = 0.0f, cicloPalanca2 = 0.0f;
float ciclo1Domino5 = 0.0f, ciclo2Domino5 = 0.0f;

#define MAX_FRAMES 100 // Valor segun los cuadros que debemos tener para no desperdiciar espacios
int i_max_steps = 50; // mayor valor mas fluidez y mas poder de computo
int i_curr_steps = 38;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movCanica_x;		//Variable para PosicionX
	float movCanica_xInc;	//Variable para IncrementoX
	float movCanica_z;		//Variable para PosicionX
	float movCanica_zInc;	//Variable para IncrementoX
	float rotaPulga;
	float rotaPulga_inc;
	float rotaFlipper;
	float rotaFlipper_inc;
	float escalaResorte;
	float escalaResorte_inc;
	float desplazaPalanca;
	float desplazaPalanca_inc;
	float rotaDomino5;
	float rotaDomino5_inc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 38;		//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame() //tecla L
{
	printf("frameindex %d\n", FrameIndex);
	KeyFrame[FrameIndex].movCanica_x = movCanica_x;
	KeyFrame[FrameIndex].movCanica_z = movCanica_z;
	KeyFrame[FrameIndex].rotaPulga = rotaPulga;
	KeyFrame[FrameIndex].rotaFlipper = rotaFlipper;
	KeyFrame[FrameIndex].escalaResorte = escalaResorte;
	KeyFrame[FrameIndex].desplazaPalanca = desplazaPalanca;
	KeyFrame[FrameIndex].rotaDomino5 = rotaDomino5;
	printf("Guardando\n");
	FrameIndex++;
}

void resetElements(void) //Tecla 0
{
	movCanica_x = KeyFrame[0].movCanica_x;
	movCanica_z = KeyFrame[0].movCanica_z;
	rotaPulga = KeyFrame[0].rotaPulga;
	rotaFlipper = KeyFrame[0].rotaFlipper;
	escalaResorte = KeyFrame[0].escalaResorte;
	desplazaPalanca = KeyFrame[0].desplazaPalanca;
	rotaDomino5 = KeyFrame[0].rotaDomino5;
}

void interpolation(void)
{
	KeyFrame[playIndex].movCanica_xInc = (KeyFrame[playIndex + 1].movCanica_x - KeyFrame[playIndex].movCanica_x) / i_max_steps;
	KeyFrame[playIndex].movCanica_zInc = (KeyFrame[playIndex + 1].movCanica_z - KeyFrame[playIndex].movCanica_z) / i_max_steps;
	KeyFrame[playIndex].rotaPulga_inc = (KeyFrame[playIndex + 1].rotaPulga - KeyFrame[playIndex].rotaPulga) / i_max_steps;
	KeyFrame[playIndex].rotaFlipper_inc = (KeyFrame[playIndex + 1].rotaFlipper - KeyFrame[playIndex].rotaFlipper) / i_max_steps;
	KeyFrame[playIndex].escalaResorte_inc = (KeyFrame[playIndex + 1].escalaResorte - KeyFrame[playIndex].escalaResorte) / i_max_steps;
	KeyFrame[playIndex].desplazaPalanca_inc = (KeyFrame[playIndex + 1].desplazaPalanca - KeyFrame[playIndex].desplazaPalanca) / i_max_steps;
	KeyFrame[playIndex].rotaDomino5_inc = (KeyFrame[playIndex + 1].rotaDomino5 - KeyFrame[playIndex].rotaDomino5) / i_max_steps;

}

void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			movCanica_x += KeyFrame[playIndex].movCanica_xInc;
			movCanica_z += KeyFrame[playIndex].movCanica_zInc;
			rotaPulga += KeyFrame[playIndex].rotaPulga_inc;
			rotaFlipper += KeyFrame[playIndex].rotaFlipper_inc;
			escalaResorte += KeyFrame[playIndex].escalaResorte_inc;
			desplazaPalanca += KeyFrame[playIndex].desplazaPalanca_inc;
			rotaDomino5 += KeyFrame[playIndex].rotaDomino5_inc;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearPrimitiva1();
	CrearPrimitiva2();

	//camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -45.0f, 0.5f, 0.5f); // la de jugador
	camera = Camera(glm::vec3(0.0f, 150.0f, 90.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -45.0f, 0.5f, 0.5f); // la de jugador
	//camera = Camera(glm::vec3(10.0f, 50.0f, -6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, -90.0f, 0.5f, 0.5f); // Ya mira hacia abajo

	// Carga de texturas
	pisoTexture = Texture("Textures/ring_concrete.jpg");
	pisoTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();
	Numero3Texture = Texture("Textures/numero3.tga");
	Numero3Texture.LoadTextureA();
	Numero4Texture = Texture("Textures/numero4.tga");
	Numero4Texture.LoadTextureA();
	Numero5Texture = Texture("Textures/numero5.tga");
	Numero5Texture.LoadTextureA();
	Numero6Texture = Texture("Textures/numero6.tga");
	Numero6Texture.LoadTextureA();
	Numero7Texture = Texture("Textures/numero7.tga");
	Numero7Texture.LoadTextureA();
	Numero8Texture = Texture("Textures/numero8.tga");
	Numero8Texture.LoadTextureA();
	Numero9Texture = Texture("Textures/numero9.tga");
	Numero9Texture.LoadTextureA();
	Numero0Texture = Texture("Textures/numero0.tga");
	Numero0Texture.LoadTextureA();
	akuTexture = Texture("Textures/aku.tga");
	akuTexture.LoadTextureA();
	cinturonTexture = Texture("Textures/muchalucha_cinturon.jpeg");
	cinturonTexture.LoadTextureA();

	// Carga de modelos
	PinballCarcasa_M = Model();
	PinballCarcasa_M.LoadModel("Models/carcasa.obj");
	PinballCristal_M = Model();
	PinballCristal_M.LoadModel("Models/cristal.obj");
	CanicaMetalica_M = Model();
	CanicaMetalica_M.LoadModel("Models/canica1.obj");
	Flipper1_M = Model();
	Flipper1_M.LoadModel("Models/sword1.obj");
	Flipper2_M = Model();
	Flipper2_M.LoadModel("Models/sword2.obj");
	Flipper3_M = Model();
	Flipper3_M.LoadModel("Models/sword3.obj");
	Resorte_M = Model();
	Resorte_M.LoadModel("Models/resorte.obj");
	Palanca_M = Model();
	Palanca_M.LoadModel("Models/palanca.obj");
	Moneda_M = Model();
	Moneda_M.LoadModel("Models/moneda.obj");
	Palito_M = Model();
	Palito_M.LoadModel("Models/palito.obj");

	FrijolitoCuerpo_M = Model();
	FrijolitoCuerpo_M.LoadModel("Models/frijolito_cuerpo.obj");
	FrijolitoBrazoIzq_M = Model();
	FrijolitoBrazoIzq_M.LoadModel("Models/frijolito_brazo_izq.obj");
	FrijolitoBrazoDer_M = Model();
	FrijolitoBrazoDer_M.LoadModel("Models/frijolito_brazo_der.obj");
	FrijolitoPiernaIzq_M = Model();
	FrijolitoPiernaIzq_M.LoadModel("Models/frijolito_pierna_izq.obj");
	FrijolitoPiernaDer_M = Model();
	FrijolitoPiernaDer_M.LoadModel("Models/frijolito_pierna_der.obj");
	LaPulga_M = Model();
	LaPulga_M.LoadModel("Models/flea.obj");
	Bus_M = Model();
	Bus_M.LoadModel("Models/bus.obj");
	Microfono_M = Model();
	Microfono_M.LoadModel("Models/microfono.obj");
	Ring_M = Model();
	Ring_M.LoadModel("Models/ring.obj");

	SamuraiJackCuerpo_M = Model();
	SamuraiJackCuerpo_M.LoadModel("Models/samurai_body.obj");
	SamuraiJackAntebrazo_M = Model();
	SamuraiJackAntebrazo_M.LoadModel("Models/samurai_antebrazo.obj");
	SamuraiJackConejito_M = Model();
	SamuraiJackConejito_M.LoadModel("Models/samurai_conejito.obj");
	SamuraiJackSimbolo_M = Model();
	SamuraiJackSimbolo_M.LoadModel("Models/simbolo.obj");
	SamuraiJackSimboloHuellitas_M = Model();
	SamuraiJackSimboloHuellitas_M.LoadModel("Models/huellitas1.obj");
	SamuraiJackAku_M = Model();
	SamuraiJackAku_M.LoadModel("Models/aku.obj");

	std::vector<std::string> skyboxFacesDia;
	std::vector<std::string> skyboxFacesNoche;

	skyboxFacesDia.push_back("Textures/Skybox/ring_crowd_1.png");
	skyboxFacesDia.push_back("Textures/Skybox/ring_crowd_1.png");
	skyboxFacesDia.push_back("Textures/Skybox/ring_floor.png");
	skyboxFacesDia.push_back("Textures/Skybox/ring_ceiling.tga");
	skyboxFacesDia.push_back("Textures/Skybox/ring_crowd_1.png");
	skyboxFacesDia.push_back("Textures/Skybox/ring_crowd_1.png");

	skyboxFacesNoche.push_back("Textures/Skybox/ring_night.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/ring_night.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/ring_floor_night.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/ring_ceiling_night.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/ring_night.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/ring_night.tga");

	skybox = Skybox(skyboxFacesDia);
	skyboxNoche = Skybox(skyboxFacesNoche);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);

	mainLight2 = DirectionalLight(0.41f, 0.41f, 0.41f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;

	//Cinturon Arriba
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f, //RGB
		10.0f, 1.0f, //Intensidad ambiental, intensidad difusa
		19.0f, 55.5f, -22.0f, // X Y Z
		10.0f, 1.0f, 1.0f);
	pointLightCount++;

	////Cinturon abajo
	pointLights[1] = PointLight(1.0f, 0.0f, 0.0f, //RGB
		10.0f, 1.0f, //Intensidad ambiental, intensidad difusa
		-18.0f, 49.0f, 40.0f, // X Y Z
		10.0f, 1.0f, 1.0f);
	pointLightCount++;

	//Aku Arriba Izquierda
	pointLights[2] = PointLight(0.0f, 0.0f, 1.0f, //RGB
		10.0f, 1.0f, //Intensidad ambiental, intensidad difusa
		-28.44f, 56.1f, -4.7f, // X Y Z
		10.0f, 1.0f, 1.0f);
	pointLightCount++;

	////Aku derecha
	pointLights[3] = PointLight(0.0f, 0.0f, 1.0f, //RGB
		10.0f, 1.0f, //Intensidad ambiental, intensidad difusa
		5.0f, 56.7f, -34.1f, // X Y Z
		10.0f, 1.0f, 1.0f);
	pointLightCount++;
	//Cinturon Arriba, Cinturon Abajo, Aku Izquierda, Aku Derecha

	pointLights1[0] = pointLights[3]; // aku derecha
	pointLights1[1] = pointLights[0]; // cint arriba
	pointLights1[2] = pointLights[1]; // cint abajo
	pointLights1[3] = pointLights[2]; // aku izq

	pointLights2[0] = pointLights[2]; // aku izq
	pointLights2[1] = pointLights[3]; // aku derecha
	pointLights2[2] = pointLights[0]; // cint arriba
	pointLights2[3] = pointLights[1]; // cint abajo	

	pointLights3[0] = pointLights[1]; // cint abajo
	pointLights3[1] = pointLights[2]; // aku izq
	pointLights3[2] = pointLights[3]; // aku derecha
	pointLights3[3] = pointLights[0]; // cint arriba

	pointLights4[0] = pointLights[3]; // aku derecha
	pointLights4[1] = pointLights[1]; // cint abajo
	pointLights4[2] = pointLights[2]; // aku izq
	pointLights4[3] = pointLights[0]; // cint arriba

	pointLights5[0] = pointLights[2]; // aku izq
	pointLights5[1] = pointLights[0]; // cint arriba
	pointLights5[2] = pointLights[3]; // aku derecha
	pointLights5[3] = pointLights[1]; // cint abajo

	//Avatar
	spotLights[0] = SpotLight(0.0f, 1.0f, 1.0f,
		10.0f, 2.0f,
		7.0f, 55.0f, -7.0f,
		0.0f, 0.0f, -1.0f,
		10.5f, 10.2f, 1.1f,
		20.0f);
	spotLightCount++;

	//Tablero
	spotLights[1] = SpotLight(0.0f, 1.0f, 1.0f,
		200.0f, 2.0f,
		0.0f, 60.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		10.5f, 10.2f, 1.1f,
		100.0f);
	spotLightCount++;

	//FLippers
	spotLights[2] = SpotLight(0.0f, 1.0f, 0.0f,
		100.0f, 1.5f,
		5.0f, 50.0f, 55.0f,
		0.0f, -1.0f, -1.0f,
		10.5f, 10.2f, 1.1f,
		80.0f);
	spotLightCount++;

	// Avatar Tablero Flippers

	spotLights1[0] = spotLights[1]; // Tablero
	spotLights1[1] = spotLights[2]; // Flippers
	spotLights1[2] = spotLights[0]; // Avatar

	spotLights2[0] = spotLights[2]; // Flippers
	spotLights2[1] = spotLights[0]; // Avatar
	spotLights2[2] = spotLights[1]; // Tablero

	KeyFrame[0].movCanica_x = 0.0;
	KeyFrame[0].movCanica_z = 0.0;
	KeyFrame[0].escalaResorte = 0.0;
	KeyFrame[0].desplazaPalanca = 0.0;
	KeyFrame[0].rotaPulga = 0.0;
	KeyFrame[0].rotaFlipper = 0.0;

	KeyFrame[1].movCanica_x = 0.0;
	KeyFrame[1].movCanica_z = 5.5;
	KeyFrame[1].escalaResorte = -0.6;
	KeyFrame[1].desplazaPalanca = 5.0;
	KeyFrame[1].rotaPulga = 0.0;
	KeyFrame[1].rotaFlipper = 0.0;

	KeyFrame[2].movCanica_x = 0.0;
	KeyFrame[2].movCanica_z = 0.0;
	KeyFrame[2].escalaResorte = 0.0;
	KeyFrame[2].desplazaPalanca = 0.0;
	KeyFrame[2].rotaPulga = 0.0;
	KeyFrame[2].rotaFlipper = 0.0;

	KeyFrame[3].movCanica_x = 0.0;
	KeyFrame[3].movCanica_z = -15.0;
	KeyFrame[3].escalaResorte = 0.0;
	KeyFrame[3].desplazaPalanca = 0.0;
	KeyFrame[3].rotaPulga = 0.0;
	KeyFrame[3].rotaFlipper = 0.0;

	KeyFrame[4].movCanica_x = 0.0;
	KeyFrame[4].movCanica_z = -30.0;
	KeyFrame[4].escalaResorte = 0.0;
	KeyFrame[4].desplazaPalanca = 0.0;
	KeyFrame[4].rotaPulga = 0.0;
	KeyFrame[4].rotaFlipper = 0.0;

	KeyFrame[5].movCanica_x = 0.0;
	KeyFrame[5].movCanica_z = -45.0;
	KeyFrame[5].escalaResorte = 0.0;
	KeyFrame[5].desplazaPalanca = 0.0;
	KeyFrame[5].rotaPulga = 0.0;
	KeyFrame[5].rotaFlipper = 0.0;

	KeyFrame[6].movCanica_x = 0.0;
	KeyFrame[6].movCanica_z = -60.0;
	KeyFrame[6].escalaResorte = 0.0;
	KeyFrame[6].desplazaPalanca = 0.0;
	KeyFrame[6].rotaPulga = 0.0;
	KeyFrame[6].rotaFlipper = 0.0;

	KeyFrame[7].movCanica_x = 0.0;
	KeyFrame[7].movCanica_z = -75.0;
	KeyFrame[7].escalaResorte = 0.0;
	KeyFrame[7].desplazaPalanca = 0.0;
	KeyFrame[7].rotaPulga = 0.0;
	KeyFrame[7].rotaFlipper = 0.0;

	KeyFrame[8].movCanica_x = 0.0;
	KeyFrame[8].movCanica_z = -90.0;
	KeyFrame[8].escalaResorte = 0.0;
	KeyFrame[8].desplazaPalanca = 0.0;
	KeyFrame[8].rotaPulga = 0.0;
	KeyFrame[8].rotaFlipper = 0.0;

	KeyFrame[9].movCanica_x = 0.0;
	KeyFrame[9].movCanica_z = -105.0;
	KeyFrame[9].escalaResorte = 0.0;
	KeyFrame[9].desplazaPalanca = 0.0;
	KeyFrame[9].rotaPulga = 0.0;
	KeyFrame[9].rotaFlipper = 0.0;

	KeyFrame[10].movCanica_x = -2.0;
	KeyFrame[10].movCanica_z = -112.5;
	KeyFrame[10].escalaResorte = 0.0;
	KeyFrame[10].desplazaPalanca = 0.0;
	KeyFrame[10].rotaPulga = 0.0;
	KeyFrame[10].rotaFlipper = 0.0;

	KeyFrame[11].movCanica_x = -8.0;
	KeyFrame[11].movCanica_z = -119.5;
	KeyFrame[11].escalaResorte = 0.0;
	KeyFrame[11].desplazaPalanca = 0.0;
	KeyFrame[11].rotaPulga = 0.0;
	KeyFrame[11].rotaFlipper = 0.0;

	KeyFrame[12].movCanica_x = -14.5;
	KeyFrame[12].movCanica_z = -125.5;
	KeyFrame[12].escalaResorte = 0.0;
	KeyFrame[12].desplazaPalanca = 0.0;
	KeyFrame[12].rotaPulga = 0.0;
	KeyFrame[12].rotaFlipper = 0.0;

	KeyFrame[13].movCanica_x = -21.5;
	KeyFrame[13].movCanica_z = -131.5;
	KeyFrame[13].escalaResorte = 0.0;
	KeyFrame[13].desplazaPalanca = 0.0;
	KeyFrame[13].rotaPulga = 0.0;
	KeyFrame[13].rotaFlipper = 0.0;

	KeyFrame[14].movCanica_x = -33.5;
	KeyFrame[14].movCanica_z = -129.0;
	KeyFrame[14].escalaResorte = 0.0;
	KeyFrame[14].desplazaPalanca = 0.0;
	KeyFrame[14].rotaPulga = 0.0;
	KeyFrame[14].rotaFlipper = 0.0;

	KeyFrame[15].movCanica_x = -45.0;
	KeyFrame[15].movCanica_z = -123.5;
	KeyFrame[15].escalaResorte = 0.0;
	KeyFrame[15].desplazaPalanca = 0.0;
	KeyFrame[15].rotaPulga = 0.0;
	KeyFrame[15].rotaFlipper = 0.0;

	KeyFrame[16].movCanica_x = -60.0;
	KeyFrame[16].movCanica_z = -112.5;
	KeyFrame[16].escalaResorte = 0.0;
	KeyFrame[16].desplazaPalanca = 0.0;
	KeyFrame[16].rotaPulga = 0.0;
	KeyFrame[16].rotaFlipper = 0.0;

	KeyFrame[17].movCanica_x = -57.0;
	KeyFrame[17].movCanica_z = -99.5;
	KeyFrame[17].escalaResorte = 0.0;
	KeyFrame[17].desplazaPalanca = 0.0;
	KeyFrame[17].rotaPulga = 0.0;
	KeyFrame[17].rotaFlipper = 0.0;

	KeyFrame[18].movCanica_x = -55.0;
	KeyFrame[18].movCanica_z = -90.5;
	KeyFrame[18].escalaResorte = 0.0;
	KeyFrame[18].desplazaPalanca = 0.0;
	KeyFrame[18].rotaPulga = 0.0;
	KeyFrame[18].rotaFlipper = 0.0;

	KeyFrame[19].movCanica_x = -47.0;
	KeyFrame[19].movCanica_z = -83.0;
	KeyFrame[19].escalaResorte = 0.0;
	KeyFrame[19].desplazaPalanca = 0.0;
	KeyFrame[19].rotaPulga = 0.0;
	KeyFrame[19].rotaFlipper = 0.0;

	KeyFrame[20].movCanica_x = -44.0;
	KeyFrame[20].movCanica_z = -85.0;
	KeyFrame[20].escalaResorte = 0.0;
	KeyFrame[20].desplazaPalanca = 0.0;
	KeyFrame[20].rotaPulga = 0.0;
	KeyFrame[20].rotaFlipper = 10.0;

	KeyFrame[21].movCanica_x = -40.0;
	KeyFrame[21].movCanica_z = -90.0;
	KeyFrame[21].escalaResorte = 0.0;
	KeyFrame[21].desplazaPalanca = 0.0;
	KeyFrame[21].rotaPulga = 0.0;
	KeyFrame[21].rotaFlipper = 40.0;

	KeyFrame[22].movCanica_x = -32.0;
	KeyFrame[22].movCanica_z = -99.0;
	KeyFrame[22].escalaResorte = 0.0;
	KeyFrame[22].desplazaPalanca = 0.0;
	KeyFrame[22].rotaPulga = 0.0;
	KeyFrame[22].rotaFlipper = 40.0;

	KeyFrame[23].movCanica_x = -26.5;
	KeyFrame[23].movCanica_z = -92.5;
	KeyFrame[23].escalaResorte = 0.0;
	KeyFrame[23].desplazaPalanca = 0.0;
	KeyFrame[23].rotaPulga = 10.0;
	KeyFrame[23].rotaFlipper = 40.0;

	KeyFrame[24].movCanica_x = -20.0;
	KeyFrame[24].movCanica_z = -83.5;
	KeyFrame[24].escalaResorte = 0.0;
	KeyFrame[24].desplazaPalanca = 0.0;
	KeyFrame[24].rotaPulga = 20.0;
	KeyFrame[24].rotaFlipper = 40.0;

	KeyFrame[25].movCanica_x = -10.0;
	KeyFrame[25].movCanica_z = -71.0;
	KeyFrame[25].escalaResorte = 0.0;
	KeyFrame[25].desplazaPalanca = 0.0;
	KeyFrame[25].rotaPulga = 30.0;
	KeyFrame[25].rotaFlipper = 40.0;

	KeyFrame[26].movCanica_x = -20.5;
	KeyFrame[26].movCanica_z = -63.0;
	KeyFrame[26].escalaResorte = 0.0;
	KeyFrame[26].desplazaPalanca = 0.0;
	KeyFrame[26].rotaPulga = 40.0;
	KeyFrame[26].rotaFlipper = 30.0;

	KeyFrame[27].movCanica_x = -39.0;
	KeyFrame[27].movCanica_z = -50.5;
	KeyFrame[27].escalaResorte = 0.0;
	KeyFrame[27].desplazaPalanca = 0.0;
	KeyFrame[27].rotaPulga = 30.0;
	KeyFrame[27].rotaFlipper = 30.0;

	KeyFrame[28].movCanica_x = -55.5;
	KeyFrame[28].movCanica_z = -40.5;
	KeyFrame[28].escalaResorte = 0.0;
	KeyFrame[28].desplazaPalanca = 0.0;
	KeyFrame[28].rotaPulga = 20.0;
	KeyFrame[28].rotaFlipper = 20.0;

	KeyFrame[29].movCanica_x = -64.0;
	KeyFrame[29].movCanica_z = -30.5;
	KeyFrame[29].escalaResorte = 0.0;
	KeyFrame[29].desplazaPalanca = 0.0;
	KeyFrame[29].rotaPulga = 10.0;
	KeyFrame[29].rotaFlipper = 10.0;

	KeyFrame[30].movCanica_x = -72.5;
	KeyFrame[30].movCanica_z = -21.0;
	KeyFrame[30].escalaResorte = 0.0;
	KeyFrame[30].desplazaPalanca = 0.0;
	KeyFrame[30].rotaPulga = 0.0;
	KeyFrame[30].rotaFlipper = 0.0;

	KeyFrame[31].movCanica_x = -63.5;
	KeyFrame[31].movCanica_z = -10.5;
	KeyFrame[31].escalaResorte = 0.0;
	KeyFrame[31].desplazaPalanca = 0.0;
	KeyFrame[31].rotaPulga = 0.0;
	KeyFrame[31].rotaFlipper = 0.0;

	KeyFrame[32].movCanica_x = -46.0;
	KeyFrame[32].movCanica_z = -8.5;
	KeyFrame[32].escalaResorte = 0.0;
	KeyFrame[32].desplazaPalanca = 0.0;
	KeyFrame[32].rotaPulga = 0.0;
	KeyFrame[32].rotaFlipper = 0.0;

	KeyFrame[33].movCanica_x = -36.0;
	KeyFrame[33].movCanica_z = -5.0;
	KeyFrame[33].escalaResorte = 0.0;
	KeyFrame[33].desplazaPalanca = 0.0;
	KeyFrame[33].rotaPulga = 0.0;
	KeyFrame[33].rotaFlipper = 0.0;

	KeyFrame[34].movCanica_x = -36.0;
	KeyFrame[34].movCanica_z = -3.5;
	KeyFrame[34].escalaResorte = 0.0;
	KeyFrame[34].desplazaPalanca = 0.0;
	KeyFrame[34].rotaPulga = 0.0;
	KeyFrame[34].rotaFlipper = 0.0;

	KeyFrame[35].movCanica_x = -25.5;
	KeyFrame[35].movCanica_z = -3.5;
	KeyFrame[35].escalaResorte = 0.0;
	KeyFrame[35].desplazaPalanca = 0.0;
	KeyFrame[35].rotaPulga = 0.0;
	KeyFrame[35].rotaFlipper = 0.0;

	KeyFrame[36].movCanica_x = -7.5;
	KeyFrame[36].movCanica_z = -1.5;
	KeyFrame[36].escalaResorte = 0.0;
	KeyFrame[36].desplazaPalanca = 0.0;
	KeyFrame[36].rotaPulga = 0.0;
	KeyFrame[36].rotaFlipper = 0.0;

	KeyFrame[37].movCanica_x = 0.0;
	KeyFrame[37].movCanica_z = 0.0;
	KeyFrame[37].escalaResorte = 0.0;
	KeyFrame[37].desplazaPalanca = 0.0;
	KeyFrame[37].rotaPulga = 0.0;
	KeyFrame[37].rotaFlipper = 0.0;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	glm::vec3 posicionFrijolito(1.0);
	glm::vec3 posicionFrijolitoLux(1.0);
	std::vector<float> coordsTexture;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Animacion de primitivas y modelos que comienzan cuando se ejecuta
		//---------------------------------------------------------------------------------------------------------------------------------
		if (akuTraslacion) {
			rotaAku -= rotaAkuOffset * deltaTime;
			if (mueveAku > -2) {
				mueveAku -= mueveAkuOffset * deltaTime;
			}
			else {
				akuTraslacion = false;
			}
		}
		else {
			rotaAku -= rotaAkuOffset * deltaTime;
			if (mueveAku < 2) {
				mueveAku += mueveAkuOffset * deltaTime;
			}
			else {
				akuTraslacion = true;
			}
		}

		if (cinturonRotacion) {
			rotaCinturon += rotaCinturonOffset * deltaTime;
			if (rotaCinturon > 100) {
				cinturonRotacion = false;
			}
		}
		else {
			rotaCinturon -= rotaCinturonOffset * deltaTime;
			if (rotaCinturon < -100) {
				cinturonRotacion = true;
			}
		}

		if (cinturonTraslacion) {
			if (mueveCinturon > -2) {
				mueveCinturon -= mueveCinturonOffset * deltaTime;
			}
			else {
				cinturonTraslacion = false;
			}
		}
		else {
			if (mueveCinturon < 2) {
				mueveCinturon += mueveCinturonOffset * deltaTime;
			}
			else {
				cinturonTraslacion = true;
			}
		}

		if (antebrazoRotacion) {
			rotaAntebrazoSamurai += rotaAntebrazoSamuraiOffset * deltaTime;
			if (rotaAntebrazoSamurai > 80) {
				antebrazoRotacion = false;
			}
		}
		else {
			rotaAntebrazoSamurai -= rotaAntebrazoSamuraiOffset * deltaTime;
			if (rotaAntebrazoSamurai < -80) {
				antebrazoRotacion = true;
			}
		}

		if (conejitoRotacion) {
			rotaConejitoSamurai += rotaConejitoSamuraiOffset * deltaTime;
			if (rotaConejitoSamurai > 45) {
				conejitoRotacion = false;
			}
		}
		else {
			rotaConejitoSamurai -= rotaConejitoSamuraiOffset * deltaTime;
			if (rotaConejitoSamurai < -45) {
				conejitoRotacion = true;
			}
		}

		if (samuraiTraslacion) {
			mueveSamurai += mueveSamuraiOffset * deltaTime;
			if (mueveSamurai > 10) {
				samuraiTraslacion = false;
			}
		}
		else {
			mueveSamurai -= mueveSamuraiOffset * deltaTime;
			if (mueveSamurai < -10) {
				samuraiTraslacion = true;
			}
		}

		//Animaciones de canica
		//---------------------------------------------------------------------------------------------------------------------------------------
		if (mainWindow.getAlternaAnimacion()) {
			if (mainWindow.getMouseDerecho()) {
				if (retraeResorte > 0.25) {
					retraeResorte -= retraeResorteOffset * deltaTime;
					muevePalanca += muevePalancaOffset * deltaTime;
					iniciaCanica += iniciaCanicaOffset * deltaTime;
					rotaCanicaInicio += rotaCanicaInicioOffset * deltaTime;
				}
				else {
					liberaResorte = true;
				}
			}
			else if (!mainWindow.getMouseDerecho()) {
				retraeResorte = 1.0f;
				muevePalanca = 0.0f;
				iniciaCanica = 0.0f;
				rotaCanicaInicio = 0.0f;
				if (liberaResorte) {
					iniciaAnimacionPrincipal = true;
					subeCanica = true;
					liberaResorte = false;
				}
			}

			if (iniciaAnimacionPrincipal) {
				if (subeCanica) {
					if (mueveCanica1 > -110) {
						mueveCanica1 -= mueveCanica1Offset * deltaTime;
					}
					else {
						subeCanica = false;
						enCurva1 = true;
					}
				}

				if (enCurva1) {
					if (mueveXCanica1 > -30) {
						mueveCanica1 -= (mueveCanica1Offset * 0.33) * deltaTime;
						mueveXCanica1 -= mueveXCanica1Offset * deltaTime;
					}
					else {
						enCurva1 = false;
						enCurva2 = true;
					}
				}

				if (enCurva2) {
					if (mueveXCanica1 > -60) {
						mueveCanica1 += (mueveCanica1Offset * 0.33) * deltaTime;
						mueveXCanica1 -= mueveXCanica1Offset * deltaTime;
					}
					else {
						enCurva2 = false;
						saleCurva = true;
					}
				}

				if (saleCurva) {
					if (mueveCanica1 < -40) {
						mueveCanica1 += (mueveCanica1Offset * 0.7) * deltaTime;
						mueveXCanica1 += mueveXCanica1Offset * deltaTime;
					}
					else {
						saleCurva = false;
						pegaParedFinal = true;
					}
				}

				if (pegaParedFinal) {
					if (mainWindow.getFlipper3()) {
						if (mueveXCanica1 > -27) {
							mueveCanica1 += (mueveCanica1Offset * 0.4) * deltaTime;
							mueveXCanica1 -= mueveXCanica1Offset * deltaTime;
						}
						else {
							if (mueveXCanica1 > -35) {
								mueveCanica1 -= (mueveCanica1Offset * 0.4) * deltaTime;
								mueveXCanica1 -= mueveXCanica1Offset * deltaTime;
							}
							else {
								if (mueveCanica1 < -5) {
									mueveCanica1 += (mueveCanica1Offset) * deltaTime;
								}
								else {
									pegaParedFinal = false;
										derrota = true;
								}
							}
						}
					}
					else {
						if (mueveXCanica1 > -40) {
							mueveCanica1 += (mueveCanica1Offset * 0.6) * deltaTime;
							mueveXCanica1 -= mueveXCanica1Offset * deltaTime;
						}
						else {
							pegaParedFinal = false;
							derrota = true;
						}
					}
				}

				if (derrota) {
					if (mueveCanica1 < 10) {
						mueveCanica1 += (mueveCanica1Offset * 0.1) * deltaTime;
					}
					else {
						mueveCanica1 = 0;
						mueveXCanica1 = 0;
						iniciaAnimacionPrincipal = false;
						derrota = false;
					}
				}
			}
		}
		else {
			//-------Para Keyframes
			inputKeyframes(mainWindow.getsKeys());
			animate();
		}

		//---------------------------------------------------------------------------------------------------------------------------------
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);

		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tiempoDiaNoche += 1.0f;
		if (tiempoDiaNoche < (maxTiempo * 5)) {
			skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (tiempoDiaNoche >= (maxTiempo * 5) && tiempoDiaNoche < (maxTiempo * 10)) {
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		// Cambio de camara
		if (mainWindow.getTopDown()) {
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix(glm::vec3(-10.0f, 150.0f, -6.0f))));
		}
		else if (mainWindow.getJugador()) {
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix(glm::vec3(0.0f, 150.0f, 90.0f))));
		}
		else if (mainWindow.getAvatar()) {
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix(posicionFrijolito)));
		}

		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::vec3 luzAvatar = posicionFrijolitoLux;
		luzAvatar.z += 0.3f;
		spotLights[0].SetFlash(luzAvatar, glm::vec3(0.0f, -1.0f, -1.0f));
		spotLights1[2].SetFlash(luzAvatar, glm::vec3(0.0f, -1.0f, -1.0f));
		spotLights2[1].SetFlash(luzAvatar, glm::vec3(0.0f, -1.0f, -1.0f));

		glm::vec3 luzTablero = glm::vec3(00.0f, 60.0f, 0.0f);
		luzTablero.z += 0.3f;
		spotLights[1].SetFlash(luzTablero, glm::vec3(0.0f, -1.0f, 0.0f));
		spotLights1[0].SetFlash(luzTablero, glm::vec3(0.0f, -1.0f, 0.0f));
		spotLights2[2].SetFlash(luzTablero, glm::vec3(0.0f, -1.0f, 0.0f));

		glm::vec3 luzFlippers = glm::vec3(0.0f, 50.0f, 55.0f);
		luzFlippers.z += 0.3f;
		spotLights[2].SetFlash(luzFlippers, glm::vec3(0.0f, -1.0f, -1.0f));
		spotLights1[1].SetFlash(luzFlippers, glm::vec3(0.0f, -1.0f, -1.0f));
		spotLights2[0].SetFlash(luzFlippers, glm::vec3(0.0f, -1.0f, -1.0f));

		if (tiempoDiaNoche < (maxTiempo * 5)) {
			shaderList[0].SetDirectionalLight(&mainLight);
		}
		else if (tiempoDiaNoche >= (maxTiempo * 5) && tiempoDiaNoche < (maxTiempo * 10)) {
			shaderList[0].SetDirectionalLight(&mainLight2);
		}
		else if (tiempoDiaNoche >= (maxTiempo * 10)) {
			tiempoDiaNoche = 0.0f;
		}

		// ILUMINACION
		// cint arriba, cint abajo, aku izq, aku der -> 0
		// cint abajo, aku izq, aku der, cint arriba -> 1
		// aku izq, aku der, cint arriba, cint abajo -> 2
		// aku der, cint arriba, cint abajo, aku izq -> 3
		// cint abajo, aku der, aku izq, cint arriba -> 4
		// cint arriba, aku izq, aku der, cint abajo -> 5
		if (mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {	// todos
			shaderList[0].SetPointLights(pointLights, pointLightCount - 4);
		}
		else if (mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {	// cint arriba
			shaderList[0].SetPointLights(pointLights3, pointLightCount - 1);
		}
		else if (!mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {	// cint abajo
			shaderList[0].SetPointLights(pointLights2, pointLightCount - 1);
		}
		else if (!mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {	// aku izq
			shaderList[0].SetPointLights(pointLights1, pointLightCount - 1);
		}
		else if (!mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {	// aku der
			shaderList[0].SetPointLights(pointLights, pointLightCount - 1);
		}
		else if (mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {		// cint arriba y abajo
			shaderList[0].SetPointLights(pointLights2, pointLightCount - 2);
		}
		else if (!mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// aku izq y der
			shaderList[0].SetPointLights(pointLights, pointLightCount - 2);
		}
		else if (mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {		// cint arriba, aku izq
			shaderList[0].SetPointLights(pointLights4, pointLightCount - 2);
		}
		else if (mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// cint arriba, aku der
			shaderList[0].SetPointLights(pointLights3, pointLightCount - 2);
		}
		else if (!mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {		// cint abajo, aku izq
			shaderList[0].SetPointLights(pointLights1, pointLightCount - 2);
		}
		else if (!mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// cint abajo, aku der
			shaderList[0].SetPointLights(pointLights5, pointLightCount - 2);
		}
		else if (mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// cint abajo ,arriba, aku der
			shaderList[0].SetPointLights(pointLights2, pointLightCount - 3);
		}
		else if (mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {		// cint abajo ,arriba, aku izq
			shaderList[0].SetPointLights(pointLights1, pointLightCount - 3);
		}
		else if (mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// aku izq, der, cint arriba
			shaderList[0].SetPointLights(pointLights3, pointLightCount - 3);
		}
		else if (!mainWindow.getapagaCinturonArriba() && mainWindow.getapagaCinturonAbajo() && mainWindow.getapagaAkuIzquierda() && mainWindow.getapagaAkuDerecha()) {		// aku izq, der, cint abajo
			shaderList[0].SetPointLights(pointLights, pointLightCount - 3);
		}
		else if (!mainWindow.getapagaCinturonArriba() && !mainWindow.getapagaCinturonAbajo() && !mainWindow.getapagaAkuIzquierda() && !mainWindow.getapagaAkuDerecha()) {	// ninguno
			shaderList[0].SetPointLights(pointLights, spotLightCount);
		}

		//SpotLights
		if (!mainWindow.getapagaAvatar() && !mainWindow.getapagaTablero() && mainWindow.getapagaFlippers()) {	// flippers
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		}
		else if (!mainWindow.getapagaAvatar() && mainWindow.getapagaTablero() && !mainWindow.getapagaFlippers()) {	// tablero
			shaderList[0].SetSpotLights(spotLights2, spotLightCount - 1);
		}
		else if (mainWindow.getapagaAvatar() && !mainWindow.getapagaTablero() && !mainWindow.getapagaFlippers()) {	// avatar
			shaderList[0].SetSpotLights(spotLights1, spotLightCount - 1);
		}
		else if (!mainWindow.getapagaAvatar() && mainWindow.getapagaTablero() && mainWindow.getapagaFlippers()) {	// flippers, tablero
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
		}
		else if (mainWindow.getapagaAvatar() && !mainWindow.getapagaTablero() && mainWindow.getapagaFlippers()) {	// flippers, avatar
			shaderList[0].SetSpotLights(spotLights1, spotLightCount - 2);
		}
		else if (mainWindow.getapagaAvatar() && mainWindow.getapagaTablero() && !mainWindow.getapagaFlippers()) {	// tablero, avatar
			shaderList[0].SetSpotLights(spotLights2, spotLightCount - 2);
		}
		else if (mainWindow.getapagaAvatar() && mainWindow.getapagaTablero() && mainWindow.getapagaFlippers()) {	// todos
			shaderList[0].SetSpotLights(spotLights2, spotLightCount - 3);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}

		//shaderList[0].SetDirectionalLight(&mainLight);
		/*shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);*/

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PinballCarcasa_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(36.6f, 47.0f, 70.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, retraeResorte + escalaResorte));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Resorte_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(37.0f, 46.0f, 86.0f + muevePalanca + desplazaPalanca));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palanca_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 46.0f, 86.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Moneda_M.RenderModel();

		// Canica 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(37.5f, 48.0f, 54.0f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		if (!iniciaAnimacionPrincipal) {
			model = glm::translate(model, glm::vec3(0, 0, iniciaCanica));
			model = glm::rotate(model, rotaCanicaInicio * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		model = glm::translate(model, glm::vec3(mueveXCanica1 + movCanica_x, 0, mueveCanica1 + movCanica_z));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CanicaMetalica_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.5f, 48.0f, 54.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CanicaMetalica_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.5f, 48.0f, 54.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CanicaMetalica_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, 49.0f, 31.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getFlipper3()), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flipper3_M.RenderModel(); //Abajo derecha

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, 57.0f, -30.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getFlipper2()) + (rotaFlipper * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flipper2_M.RenderModel(); //Arriba al fondo

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 50.0f, 30.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getFlipper1()), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flipper2_M.RenderModel(); //Abajo izquierda

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, 49.0f, 18.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Microfono_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, 55.0f, -6.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(mainWindow.getTrasladaXFrijolito(), 0.0f, 0.0 + mainWindow.getTrasladaZFrijolito()));
		posicionFrijolitoLux = model[3];
		modelaux = model;
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoCuerpo_M.RenderModel();
		model = glm::translate(model, glm::vec3(-5.0, 5.0f, 0.0f));
		posicionFrijolito = model[3];

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 0.05f, -0.35f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotaBrazoIzquierdo()), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoBrazoIzq_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 0.15f, 0.35f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotaBrazoDerecho()), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoBrazoDer_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.05f, -0.4f, -0.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotaPiernaIzquierda()), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoPiernaIzq_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.05f, -0.4f, 0.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotaPiernaDerecha()), glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoPiernaDer_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f + mueveSamurai, 50.0f, 11.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackCuerpo_M.RenderModel();

		model = glm::translate(model, glm::vec3(1.05f, 7.9f, 1.35f));
		model = glm::rotate(model, rotaAntebrazoSamurai * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackConejito_M.RenderModel();

		model = glm::translate(model, glm::vec3(0.4f, -0.1f, 1.3f));
		model = glm::rotate(model, rotaAntebrazoSamurai * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackAntebrazo_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 52.0f, 18.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ring_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, 57.0f, -21.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bus_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-32.0f, 70.0f, -51.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackSimbolo_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 60.0f, -50.0f));
		model = glm::rotate(model, rotaPulga * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LaPulga_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, 56.0f, -6.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackAku_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, 53.0f, 26.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackSimboloHuellitas_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.3f, 52.3f, 36.8f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SamuraiJackSimboloHuellitas_M.RenderModel(); //Izquierda

		//PRIMITIVAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f + mueveAku, 56.7f, -34.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotaAku * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		akuTexture.UseTexture(); // Al fondo
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.44f + mueveAku, 56.1f, -4.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 5.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rotaAku * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		akuTexture.UseTexture();
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(mueveAku + 15.0f, 52.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 2.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotaAku * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		akuTexture.UseTexture();
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 53.0f + mueveCinturon, -5.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 1.75f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 + rotaCinturon * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cinturonTexture.UseTexture();
		meshList[8]->RenderMesh(); //Arriba izquierda

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, 55.0f + mueveCinturon, -18.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 1.75f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 + rotaCinturon * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cinturonTexture.UseTexture();
		meshList[8]->RenderMesh(); //Arriba derecha

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, 49.0f + mueveCinturon, 40.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palito_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 1.75f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 + rotaCinturon * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cinturonTexture.UseTexture();
		meshList[8]->RenderMesh(); //Abajo	

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (cambiaNumeroVisibleOffset > 100.0) {
			cambiaNumeroVisibleOffset = 0.0;
			punt0 += 1;
		}
		else {
			cambiaNumeroVisibleOffset += 0.3;
		}

		if (punt0 > 9) {
			punt1 += 1;
			punt0 = 0;
		}

		coordsTexture = getCoordsTexture(punt0);

		/* 0.00 -> 1,2,3,4
		 0.33 -> 9,0,simbolos
		 0.66 -> 5,6,7,8*/
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt1 > 9) {
			punt1 = 0;
			punt2 += 1;
		}

		coordsTexture = getCoordsTexture(punt1);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt2 > 9) {
			punt2 = 0;
			punt3 += 1;
		}

		coordsTexture = getCoordsTexture(punt2);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt3 > 9) {
			punt3 = 0;
			punt4 += 1;
		}

		coordsTexture = getCoordsTexture(punt3);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt4 > 9) {
			punt4 = 0;
			punt5 += 1;
		}

		coordsTexture = getCoordsTexture(punt4);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt5 > 9) {
			punt5 = 0;
			punt6 += 1;
		}

		coordsTexture = getCoordsTexture(punt5);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt6 > 9) {
			punt6 = 0;
			punt7 += 1;
		}

		coordsTexture = getCoordsTexture(punt6);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt7 > 9) {
			punt7 = 0;
			punt8 += 1;
		}

		coordsTexture = getCoordsTexture(punt7);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		if (punt8 > 9) {
			punt8 = 0;
		}

		coordsTexture = getCoordsTexture(punt8);
		toffset = glm::vec2(coordsTexture[0], coordsTexture[1]);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-37.0f, 130.0f, -80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 70.0f, 0.0));
		//model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//PinballCristal_M.RenderModel();

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_F5])
	{
		if (cicloCambiaDirx1 < 1)
		{
			cambiaDirx = !cambiaDirx;
			printf("Cambio direccion\n");
			cicloCambiaDirx1++;
			cicloCambiaDirx2 = 0;
			printf("\n Presiona la tecla F6 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_F6] && GLFW_PRESS)
	{
		if (cicloCambiaDirx2 < 1 && cicloCambiaDirx1>0)
		{
			cicloCambiaDirx1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla F5\n");
		}
	}

	if (keys[GLFW_KEY_F7])
	{
		if (cicloCambiaDirz1 < 1)
		{
			cambiaDirz = !cambiaDirz;
			printf("Cambio direccion\n");
			cicloCambiaDirz1++;
			cicloCambiaDirz2 = 0;
			printf("\n Presiona la tecla F7 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_F8] && GLFW_PRESS)
	{
		if (cicloCambiaDirz2 < 1 && cicloCambiaDirz1>0)
		{
			cicloCambiaDirz1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla F8\n");
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animacion'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animacion con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movCanica_x es: %f\n", movCanica_x);
			printf("movCanica_z es: %f\n", movCanica_z);
			printf("escalaResorte es: %f\n", escalaResorte);
			printf("desplazaPalanca es: %f\n", desplazaPalanca);
			printf("rotaPulga es: %f\n", rotaPulga);
			printf("rotaFlipper es: %f\n", rotaFlipper);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1 && guardoFrame > 0)
		{
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			if (cambiaDirx)
				movCanica_x += 0.5f;
			else
				movCanica_x -= 0.5f;
			printf("movCanica_x es: %f\n", movCanica_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_2] && GLFW_PRESS)
	{
		if (ciclo2 < 1 && ciclo>0)
		{
			ciclo = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

	if (keys[GLFW_KEY_3])
	{
		if (cicloMovz1 < 1)
		{
			if (cambiaDirz)
				movCanica_z += 0.5f;
			else
				movCanica_z -= 0.5f;
			printf("movCanica_z es: %f\n", movCanica_z);
			cicloMovz1++;
			cicloMovz2 = 0;
			printf("\n Presiona la tecla 4 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_4] && GLFW_PRESS)
	{
		if (cicloMovz2 < 1 && cicloMovz1>0)
		{
			cicloMovz1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 3\n");
		}
	}

	if (keys[GLFW_KEY_5])
	{
		if (cicloRotaPulga1 < 1)
		{
			rotaPulga += 5.0f;
			printf("rotaPulga es: %f\n", rotaPulga);
			cicloMovz1++;
			cicloRotaPulga2 = 0;
			printf("\n Presiona la tecla 6 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_6] && GLFW_PRESS)
	{
		if (cicloRotaPulga2 < 1 && cicloRotaPulga1>0)
		{
			cicloRotaPulga1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 5\n");
		}
	}

	if (keys[GLFW_KEY_E])
	{
		if (cicloFlipper1 < 1)
		{
			rotaFlipper += 5.0f;
			printf("rotaFlipper es: %f\n", rotaFlipper);
			cicloFlipper1++;
			cicloFlipper2 = 0;
			printf("\n Presiona la tecla R para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_R] && GLFW_PRESS)
	{
		if (cicloFlipper2 < 1 && cicloFlipper1>0)
		{
			cicloFlipper1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla E\n");
		}
	}

	if (keys[GLFW_KEY_T])
	{
		if (cicloResorte1 < 1)
		{
			if (cambiaDirz)
				escalaResorte -= 0.1f;
			else
				escalaResorte += 0.1f;
			printf("escalaResorte es: %f\n", escalaResorte);
			cicloResorte1++;
			cicloResorte2 = 0;
			printf("\n Presiona la tecla Y para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_Y] && GLFW_PRESS)
	{
		if (cicloResorte2 < 1 && cicloResorte1>0)
		{
			cicloResorte1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla T\n");
		}
	}

	if (keys[GLFW_KEY_U])
	{
		if (cicloPalanca1 < 1)
		{
			if (cambiaDirz)
				desplazaPalanca += 0.1f;
			else
				desplazaPalanca -= 0.1f;
			printf("desplazaPalanca es: %f\n", desplazaPalanca);
			cicloPalanca1++;
			cicloPalanca2 = 0;
			printf("\n Presiona la tecla I para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_I] && GLFW_PRESS)
	{
		if (cicloPalanca2 < 1 && cicloPalanca1>0)
		{
			cicloPalanca1 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla I\n");
		}
	}

	if (keys[GLFW_KEY_O])
	{
		if (ciclo1Domino5 < 1)
		{
			rotaDomino5 += 5.0f;
			printf("rotaDomino5 es: %f\n", rotaDomino5);
			ciclo1Domino5++;
			ciclo2Domino5 = 0;
			printf("\n Presiona la tecla P para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_P] && GLFW_PRESS)
	{
		if (ciclo2Domino5 < 1 && ciclo1Domino5>0)
		{
			ciclo1Domino5 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla O\n");
		}
	}

}