#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <GL\glut.h>

const double PI = 3.1415926553589793;

int i;
void init() { //inisialisasi 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //source untuk mengubah warna RGBA (Red, Green, Blue, Alfa) 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200, 0.0, 600);
}

void lingkaran(int jari2, int jumlah_titik, int x_tengah, int y_tengah, int shape)
{
	glBegin(GL_POLYGON);
	if (shape == 1) { // 1/2
		for (i = 0; i <= 180; i++)
		{
			float sudut = i*(2 * PI / jumlah_titik);
			float x = x_tengah + jari2*cos(sudut);
			float y = y_tengah + jari2*sin(sudut);
			glVertex2f(x, y);
		}
		glVertex2f(x_tengah, y_tengah);
	}
	else if (shape == 2) { // 1/4
		for (int i = 0; i <= 90; i++)
		{
			float sudut = i*(2 * PI / jumlah_titik);
			float x = x_tengah + jari2*cos(sudut);
			float y = y_tengah + jari2*sin(sudut);
			glVertex2f(x, y);
		}
		glVertex2f(x_tengah, y_tengah);
	}
	else if (shape == 3) { //full
		for (int i = 0; i <= 360; i++)
		{
			float sudut = i*(2 * PI / jumlah_titik);
			float x = x_tengah + jari2*cos(sudut);
			float y = y_tengah + jari2*sin(sudut);
			glVertex2f(x, y);
		}
	}

	glEnd();
}

void brick(int startX, int startY, int endX, int tingkat, int cek)
{
	int curX, curY, campur;
	curX = startX;
	curY = startY;
	campur = 1;
	while (curX < endX)
	{
		if (campur % 2 == 0)
			glColor3f(0.804f, 0.522f, 0.247f);
		else
			glColor3f(0.824f, 0.412f, 0.118f);
		glBegin(GL_POLYGON);
		glVertex2i(curX, curY);       //kiri bawah
		glVertex2i(curX, curY + 10);     //kiri atas
		if (curX + 20 > endX)
			glVertex2i(curX + (endX - curX), curY + 10);
		else
			glVertex2i(curX + 20, curY + 10);  //kanan atas
		if (curX + 20 > endX)
			glVertex2i(curX + (endX - curX), curY);
		else
			glVertex2i(curX + 20, curY);    //kanan bawah
		glEnd();
		campur++;
		curX = curX + 20;
	}
	curX = startX;
	curY = startY;
	campur = 1;
	while (curX < endX)
	{
		if (campur % 2 == 0)
			glColor3f(0.545f, 0.271f, 0.075f);
		else
			glColor3f(0.627f, 0.322f, 0.176f);
		glBegin(GL_POLYGON);
		glVertex2i(curX, curY + 10);       //kiri bawah
		glVertex2i(curX, curY + 20);     //kiri atas
		if (curX == startX)
		{
			glVertex2i(curX + 10, curY + 20);
		}
		else if (curX + 20 > endX)
			glVertex2i(curX + (endX - curX), curY + 20);
		else
			glVertex2i(curX + 20, curY + 20);  //kanan atas
		if (curX == startX)
		{
			glVertex2i(curX + 10, curY + 10);
			curX = curX - 10;
		}
		else if (curX + 20 > endX)
			glVertex2i(curX + (endX - curX), curY + 10);
		else
			glVertex2i(curX + 20, curY + 10);    //kanan bawah
		glEnd();
		campur++;
		curX = curX + 20;
	}
	if (cek != tingkat)
	{
		startY = startY + 20;
		cek++;
		brick(startX, startY, endX, tingkat, cek);
	}
}

void rumah()
{
	//Menghapus window dan memberi warna sesuai dengan yang di definisikan pada glClearColor 
	glClear(GL_COLOR_BUFFER_BIT);

	//langit 
	//glColor3f(0,0,0); //night 
	glColor3f(0.529f, 0.808f, 0.980f); //day 
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(0, 768);
	glVertex2i(1260, 768);
	glVertex2i(1260, 0);
	glEnd();

	//Rumput
	glColor3f(0.133f, 0.545f, 0.133f);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, 240);
	glVertex2i(1260, 240);
	glVertex2i(1260, 0);
	glEnd();

	//source untuk membuat tembok depan tengah lt1 rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.810f, 0.810f, 0.810f);
	glVertex2i(300, 200);
	glVertex2i(300, 300);
	glColor3f(0.690f, 0.690f, 0.690f);
	glVertex2i(375, 300);
	glVertex2i(375, 200);
	glEnd();

	//source untuk membuat pintu rumah 
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f);
	glVertex2i(312, 200);
	glVertex2i(312, 280);
	glVertex2i(363, 280);
	glVertex2i(363, 200);
	glEnd();

	//source untuk membuat gerendel pintu depan yang warna orange 
	glColor3f(0.855f, 0.647f, 0.125f);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(355, 240);
	glEnd();

	//source untuk membuat tembok depan kiri lt1 rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.850f, 0.850f, 0.850f);
	glVertex2i(150, 184);
	glVertex2i(150, 300);
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(300, 300);
	glVertex2i(300, 184);
	glEnd();

	//source untuk membuat jendela lt1 rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // kusen
	glVertex2i(187, 225); glVertex2i(187, 295);
	glVertex2i(261, 295); glVertex2i(261, 225); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(192, 230); glVertex2i(192, 290);
	glVertex2i(222, 290); glVertex2i(222, 230); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(226, 230); glVertex2i(226, 290);
	glVertex2i(256, 290); glVertex2i(256, 230); glEnd();

	//source untuk membuat pagar rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); //atas
	glVertex2i(175, 210); glVertex2i(175, 215);
	glVertex2i(275, 215); glVertex2i(275, 210); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah1
	glVertex2i(180, 185); glVertex2i(180, 214);
	glVertex2i(185, 214); glVertex2i(185, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah2
	glVertex2i(190, 185); glVertex2i(190, 214);
	glVertex2i(195, 214); glVertex2i(195, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah3
	glVertex2i(200, 185); glVertex2i(200, 214);
	glVertex2i(205, 214); glVertex2i(205, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah4
	glVertex2i(210, 185); glVertex2i(210, 214);
	glVertex2i(215, 214); glVertex2i(215, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah5
	glVertex2i(220, 185); glVertex2i(220, 214);
	glVertex2i(225, 214); glVertex2i(225, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah6
	glVertex2i(230, 185); glVertex2i(230, 214);
	glVertex2i(235, 214); glVertex2i(235, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah7
	glVertex2i(240, 185); glVertex2i(240, 214);
	glVertex2i(245, 214); glVertex2i(245, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah8
	glVertex2i(250, 185); glVertex2i(250, 214);
	glVertex2i(255, 214); glVertex2i(255, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah9
	glVertex2i(260, 185); glVertex2i(260, 214);
	glVertex2i(265, 214); glVertex2i(265, 185); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // bilah10
	glVertex2i(270, 185); glVertex2i(270, 214);
	glVertex2i(275, 214); glVertex2i(275, 185); glEnd();

	//source untuk membuat pilar kiri rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // tiang
	glVertex2i(152, 220); glVertex2i(154, 299);
	glVertex2i(166, 299); glVertex2i(168, 220); glEnd();
	brick(145, 184, 175, 2, 1); //bata
	glEnd();

	//source untuk membuat pilar kanan rumah 
	glVertex2i(305, 220); glVertex2i(305, 184); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // tiang
	glVertex2i(282, 220); glVertex2i(284, 299);
	glVertex2i(296, 299); glVertex2i(298, 220); glEnd();
	brick(275, 184, 305, 2, 1); //bata
	glEnd();

	//source untuk membuat tangga rumah 
	glBegin(GL_POLYGON); glColor3f(0.760f, 0.760f, 0.760f); //teras
	glVertex2i(305, 200); glVertex2i(305, 184);
	glVertex2i(375, 184); glVertex2i(375, 200); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.735f, 0.735f, 0.735f); //sisi samping
	glVertex2i(140, 184); glVertex2i(140, 160);
	glVertex2i(375, 160); glVertex2i(375, 184); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.700f, 0.700f, 0.700f); //tangga
	glVertex2i(290, 170); glVertex2i(290, 155);
	glVertex2i(375, 155); glVertex2i(375, 170); glEnd();

	//source untuk membuat tembok garasi rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f);
	glVertex2i(375, 155);
	glVertex2i(375, 300);
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(600, 300);
	glVertex2i(600, 155);
	glEnd();

	//source untuk membuat bata garasi rumah 
	brick(375, 155, 600, 4, 1);
	glEnd();

	//source untuk membuat pintu garasi rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); //tralis
	glVertex2i(412, 155); glVertex2i(412, 270);
	glVertex2i(562, 270); glVertex2i(562, 155); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.65f, 0.65f, 0.65f); //atas
	glVertex2i(407, 270); glVertex2i(407, 290);
	glVertex2i(567, 290); glVertex2i(567, 270); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.8f, 0.8f, 0.8f); //grendel
	glVertex2i(477, 165); glVertex2i(477, 170);
	glVertex2i(497, 170); glVertex2i(497, 165); glEnd();

	//jalan depan garasi
	glBegin(GL_QUADS); glColor3f(0.502f, 0.502f, 0.502f);
	glVertex2i(412, 0); glVertex2i(412, 155); glVertex2i(562, 155);
	glVertex2i(700, 0); glEnd();
	glBegin(GL_QUADS); glColor3f(0.502f, 0.502f, 0.502f);
	glVertex2i(250, 100); glVertex2i(290, 155);
	glVertex2i(412, 155); glVertex2i(412, 100); glEnd();

	//source untuk membuat atap lt1 rumah 
	glBegin(GL_POLYGON); glColor3f(0.32f, 0.32f, 0.32f); // atap
	glVertex2i(125, 300); glColor3f(0.15f, 0.15f, 0.15f); 
	glVertex2i(125, 350); glVertex2i(625, 350); 
	glVertex2i(625, 300); glEnd();
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // list
	glVertex2i(120, 300); glVertex2i(120, 310);
	glVertex2i(630, 310); glVertex2i(630, 300); glEnd();

	//source untuk membuat tembok depan kiri lt2 rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.753f, 0.753f, 0.753f);
	glVertex2i(150, 350); // kiri bawah
	glVertex2i(150, 400); // kiri atas
	glColor3f(0.65, 0.65f, 0.65f);
	glVertex2i(275, 400); // kanan atas 
	glVertex2i(275, 350); // kanan bawah
	glEnd();

	//source untuk membuat jendela lt2 rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); //1
	glVertex2i(165, 360); glVertex2i(165, 390);
	glVertex2i(195, 390); glVertex2i(195, 360); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f);
	glVertex2i(170, 365); glVertex2i(170, 385);
	glVertex2i(190, 385); glVertex2i(190, 365); glEnd();

	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); //2
	glVertex2i(210, 360); glVertex2i(210, 390); 
	glVertex2i(240, 390); glVertex2i(240, 360); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f);
	glVertex2i(215, 365); glVertex2i(215, 385);
	glVertex2i(235, 385); glVertex2i(235, 365); glEnd();

	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); //3
	glVertex2i(255, 360); glVertex2i(255, 390);
	glVertex2i(285, 390); glVertex2i(285, 360); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f);
	glVertex2i(260, 365); glVertex2i(260, 385);
	glVertex2i(280, 385); glVertex2i(280, 365); glEnd();

	//source untuk membuat atap segitiga lt1 kiri rumah 
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f);
	glVertex2i(150, 320); // kiri bawah
	glVertex2i(225, 370); // kiri atas
	glVertex2i(225, 370); // kanan atas 
	glVertex2i(300, 320); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f); //wall segitiga
	glVertex2i(178, 330); // kiri bawah
	glVertex2i(225, 361); // kiri atas
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(225, 361); // kanan atas 
	glVertex2i(272, 330); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f);
	glVertex2i(188, 320); // kiri bawah
	glVertex2i(188, 330); // kiri atas
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(262, 330); // kanan atas 
	glVertex2i(262, 320); // kanan bawah
	glEnd();

	//source untuk membuat tembok depan kanan lt2 rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.827f, 0.827f, 0.827f);
	glVertex2i(275, 345); // kiri bawah
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(275, 430); // kiri atas
	glVertex2i(600, 430); // kanan atas 
	glVertex2i(600, 345); // kanan bawah
	glEnd();

	//source untuk membuat jendela lt2 rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // kusen
	glVertex2i(493, 350); glVertex2i(493, 425);
	glVertex2i(567, 425); glVertex2i(567, 350); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(498, 355); glVertex2i(498, 420);
	glVertex2i(528, 420); glVertex2i(528, 355); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(562, 355); glVertex2i(562, 420);
	glVertex2i(532, 420); glVertex2i(532, 355); glEnd();


	//source untuk membuat tembok depan tengah lt2 rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f);
	glVertex2i(365, 340); // kiri bawah
	glVertex2i(365, 430); // kiri atas
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(460, 430); // kanan atas 
	glVertex2i(460, 340); // kanan bawah
	glEnd();

	//source untuk membuat jendela lt2 rumah 
	glBegin(GL_POLYGON); glColor3f(1.000f, 1.000f, 0.941f); // kusen
	glVertex2i(375, 355); glVertex2i(375, 425);
	glVertex2i(450, 425); glVertex2i(450, 355); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(380, 360); glVertex2i(380, 420);
	glVertex2i(410, 420); glVertex2i(410, 360); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.686f, 0.933f, 0.933f); // kaca1
	glVertex2i(445, 360); glVertex2i(445, 420);
	glVertex2i(415, 420); glVertex2i(415, 360); glEnd();

	//source untuk membuat atap segitiga lt1 kanan rumah 
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f);
	glVertex2i(407, 320); // kiri bawah
	glVertex2i(487, 370); // kiri atas
	glVertex2i(487, 370); // kanan atas 
	glVertex2i(567, 320); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f); //wall segitiga
	glVertex2i(435, 330); // kiri bawah
	glVertex2i(487, 361); // kiri atas
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(487, 361); // kanan atas 
	glVertex2i(539, 330); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f);
	glVertex2i(445, 320); // kiri bawah
	glVertex2i(445, 330); // kiri atas
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex2i(529, 330); // kanan atas 
	glVertex2i(529, 320); // kanan bawah
	glEnd();

	//source untuk membuat atap lt2 kiri rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.32f, 0.32f, 0.32f);//atap
	glVertex2i(125, 400); // kiri bawah
	glVertex2i(125, 500); // kiri atas
	glColor3f(0.15f, 0.15f, 0.15f);
	glVertex2i(275, 500); // kanan atas 
	glVertex2i(275, 400); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f);//list
	glVertex2i(120, 400); // kiri bawah
	glVertex2i(120, 410); // kiri atas
	glVertex2i(275, 410); // kanan atas 
	glVertex2i(275, 400); // kanan bawah
	glEnd();
	
	//source untuk membuat atap lt2 kanan rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.32f, 0.32f, 0.32f); //atap
	glVertex2i(250, 430); // kiri bawah
	glVertex2i(250, 530); // kiri atas
	glColor3f(0.15f, 0.15f, 0.15f);
	glVertex2i(520, 530); // kanan atas 
	glVertex2i(625, 430); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.32f, 0.32f, 0.32f); //segitiga
	glVertex2i(345, 430); // kiri bawah
	glVertex2i(485, 580); // kiri atas
	glVertex2i(485, 580); // kanan atas
	glColor3f(0.15f, 0.15f, 0.15f);
	glVertex2i(625, 430); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f); //list segitiga
	glVertex2i(397, 475); // kiri bawah
	glVertex2i(485, 570); // kiri atas
	glVertex2i(485, 570); // kanan atas 
	glVertex2i(573, 475); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.827f, 0.827f, 0.827f); //wall segitiga
	glVertex2i(415, 485); // kiri bawah
	glVertex2i(485, 560); // kiri atas
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(485, 560); // kanan atas 
	glVertex2i(555, 485); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.827f, 0.827f, 0.827f);
	glVertex2i(435, 475); // kiri bawah
	glVertex2i(435, 485); // kiri atas
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(530, 485); // kanan atas 
	glVertex2i(530, 475); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f); //list
	glVertex2i(245, 430); // kiri bawah
	glVertex2i(245, 440); // kiri atas
	glVertex2i(630, 440); // kanan atas 
	glVertex2i(630, 430); // kanan bawah
	glEnd();

	//source untuk membuat atap lt2 tengah rumah 
	glBegin(GL_POLYGON);
	glColor3f(0.32f, 0.32f, 0.32f);//list
	glVertex2i(339, 430); // kiri bawah
	glVertex2i(413, 486); // kiri atas
	glVertex2i(413, 486); // kanan atas 
	glVertex2i(486, 430); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.000f, 1.000f, 0.941f);
	glVertex2i(340, 430); // kiri bawah
	glVertex2i(413, 485); // kiri atas
	glVertex2i(413, 485); // kanan atas 
	glVertex2i(485, 430); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f); //wall segitiga
	glVertex2i(365, 440); // kiri bawah
	glVertex2i(413, 475); // kiri atas
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(413, 475); // kanan atas 
	glVertex2i(460, 440); // kanan bawah
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.863f, 0.863f, 0.863f);
	glVertex2i(380, 430); // kiri bawah
	glVertex2i(380, 440); // kiri atas
	glColor3f(0.73f, 0.73f, 0.73f);
	glVertex2i(445, 440); // kanan atas 
	glVertex2i(445, 430); // kanan bawah
	glEnd();

	//source untuk membuat lampu taman
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(795, 0); // kiri bawah
	glVertex2i(795, 200); // kiri atas
	glVertex2i(805, 200); // kanan atas 
	glVertex2i(805, 0); // kanan bawah
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	lingkaran(35, 360, 800, 200, 3);

	//source untuk membuat pohon
	glBegin(GL_POLYGON); glColor3f(0.545f, 0.271f, 0.075f);
	glVertex2i(644, 270); glVertex2i(725, 230);
	glVertex2i(715, 230); glVertex2i(658, 270); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.545f, 0.271f, 0.075f);
	glVertex2i(750, 270); glVertex2i(725, 230);
	glVertex2i(715, 230); glVertex2i(744, 270); glEnd();
	glBegin(GL_POLYGON); glColor3f(0.545f, 0.271f, 0.075f);
	glVertex2i(690, 150); glVertex2i(725, 230);
	glVertex2i(715, 230); glVertex2i(710, 150); glEnd();
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(20, 360, 640, 270, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(25, 360, 660, 290, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(25, 360, 680, 275, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(35, 360, 695, 315, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(30, 360, 725, 295, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(25, 360, 750, 280, 3);
	glColor3f(0.000f, 0.502f, 0.000f);
	lingkaran(15, 360, 715, 270, 3);

	glFlush();
}

int main(int argc, char ** argv)
{
	// inisialisasi GLUT 
	glutInit(&argc, argv);
	// Output pada console nama anggota kelompok
	printf("Anggota Kelompok : \n\n");
	printf("Iin Firlyana\t\t 4616010013\n");
	printf("Mohammad Yasin\t\t 4616010045\n");
	printf("M. Rizky Pradana\t 4616010025\n");
	printf("Shiddiq Asy Syuhada\t 4616010017");
	// Set display mode 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set Posisi window saat program dijalankan 
	glutInitWindowPosition(150, 100);
	//Resolusi Jendela Program 
	glutInitWindowSize(1200,600);
	//Memberikan Title pada Window 
	glutCreateWindow("Projek UTS Rumah Komplek");
	// Menjalankan Prosedur Inisialisasi 
	init();
	// Menjalankan fungsi untuk menampilkan visual pada program 
	glutDisplayFunc(rumah);
	// Menjalankan program, tidak langsung exit 
	glutMainLoop();
}