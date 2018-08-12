
#include <stdio.h>
#include <iostream>
#include <GL/glut.h> //Contains gl.h and glu.h
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.14159

#define N 15

float d=40;
float thita=PI/4.0;
float phi = PI/3.0;

int thesix,thesiy,thesiz;
int trexon[4][4][4];
int plegma[N][N][N]; 
int paused=0;
int msecond=1000;

void fotismos();
void neosxhma(int A[4][4][4]);
void zografise(int A[4][4][4]);
void zografise_plegma();
void arxikopoihsh_plegma();
int elegxos_sygkrousis(int A[4][4][4]);


int rotate_y(int A[4][4][4]);
int rotate_z(int A[4][4][4]);
int rotate_x(int A[4][4][4]);

//responsing to key presses handler
void keyPressed(unsigned char key, int x, int y)
{
	float alpha;
	float camy;
	if(key=='-') d+=1;
	else if(key=='+') d-=1;
	else if(key=='o') thita+=PI/100.0;
	else if(key=='l') thita-=PI/100.0;
	else if(key=='i'){
		camy = d*cos(phi);
		if(camy<2*N){
			alpha = sqrt((d*d)-(camy*camy));
			d=sqrt( (camy+1.0)*(camy+1.0) + alpha*alpha);
			phi = PI/2.0 - atan((camy+1.0)/alpha);
		}
	}
	else if(key=='k'){
		camy = d*cos(phi);
		if(camy>-2*N){
			alpha = sqrt((d*d)-(camy*camy));
			d=sqrt( (camy-1.0)*(camy-1.0) + alpha*alpha);
			phi = PI/2.0 - atan((camy-1.0)/alpha);
			//printf("phi: %f\n",phi);
		}
	}
	else if(key=='n'){
		neosxhma(trexon);
	}
	else if(key=='p'){
		if(paused==0) paused=1;
		else if(paused==1) paused=0;
	}
	else if(key=='s'){
		rotate_z(trexon);
	}
	else if(key=='d'){
		rotate_y(trexon);
	}
	else if(key=='f'){
		rotate_x(trexon);
	}
	else if(key=='1'){
		msecond+=200;
	}
	else if(key=='2'){
		msecond-=200;
	}

	if(d<5) d=5;
	if(d>4*N) d=4*N;
	glutPostRedisplay();
}

//responsing to special key presses handler
void specialKeyPressed(int key, int x, int y)
{
	//1. actions to take when user presses a key

	switch(key){
		case GLUT_KEY_UP:
			thesiz--;
			if(elegxos_sygkrousis(trexon)==1){
				thesiz++;
			}
			break;
		case GLUT_KEY_DOWN:
			thesiz++;
			if(elegxos_sygkrousis(trexon)==1){
				thesiz--;
			}
			break;
		case GLUT_KEY_LEFT:
			thesix--;
			if(elegxos_sygkrousis(trexon)==1){
				thesix++;
			}
			break;
		case GLUT_KEY_RIGHT:
			thesix++;
			if(elegxos_sygkrousis(trexon)==1){
				thesix--;
			}
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

//size changing handling function
void changeSize(int w, int h) 
{
	//0. handling special cases

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	//1. set projection

	float ratio =  w * 1.0 / h;
	//use the projection matrix
	glMatrixMode(GL_PROJECTION);
	//reset matrix
	glLoadIdentity();
	//set the viewport to be the entire window
	glViewport(0, 0, w, h);
	//set the correct perspective.
	gluPerspective(45, ratio, 1,100);

	//2. set modelview

	//get back to the modelview
	glMatrixMode(GL_MODELVIEW);
}


void axones()
{
	int i;

	glColor3f(1,1,1); //aspro
	//epipedo x z
	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(i,0,0);
		glVertex3f(i,0,N);
		glEnd();
	}
	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(0,0,i);
		glVertex3f(N,0,i);
		glEnd();
	}

	//epipedo yz
	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(0,i,0);
		glVertex3f(0,i,N);
		glEnd();
	}
	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(0,0,i);
		glVertex3f(0,N,i);
		glEnd();
	}


	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(0,i,0);
		glVertex3f(N,i,0);
		glEnd();
	}
	for(i=1; i<=N; i++){
		glBegin(GL_LINES);
		glVertex3f(i,0,0);
		glVertex3f(i,N,0);
		glEnd();
	}
	glBegin(GL_LINES);
	//axonas y
	glColor3f(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(0,N,0);
	glEnd();

	glBegin(GL_LINES);
	//axonas x
	glColor3f(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(N,0,0);
	glEnd();

	glBegin(GL_LINES);
	//axonas z
	glColor3f(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,N);
	glEnd();

	
}



void display()
{
	float camx,camy,camz;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camx = d*cos(thita)*sin(phi);
	camz = d*sin(thita)*sin(phi);
	camy = d*cos(phi);
	
	gluLookAt(camx,camy,camz, 0,0,0, 0,1,0);
	glColor3f(1.0f, 0.0f, 0.0f);

	axones();
	
	zografise_plegma();
	glTranslated(thesix,thesiy,thesiz);
	zografise(trexon);
	glutSwapBuffers();
}

//initialize projection and set needed buffers
static void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float) 800/600;
	gluPerspective(40, ratio, 0.1, 20); 
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void fotismos()
{
	glClearDepth( 1.0f );														
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

	GLfloat mat_specular[] = { 1, 1, 1, 1};      // RGBA for material
	GLfloat mat_shininess[] = { 100.0 };                   // Shininess for material
	GLfloat light_position[] = { 15.0, 15.0, 15.0, 0.0 }; // Position of light
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat amb_light[] = { 0.5, 0.5, 0.5, 0.8 };
	glShadeModel (GL_SMOOTH);
    glEnable( GL_COLOR_MATERIAL ); 


	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    // Set specular light for material
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  // Set shininess for material
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);    // Set light position
	glEnable(GL_LIGHT0);                                
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_LIGHTING);                           
	glEnable(GL_LIGHT0);     

	glClearColor(0.0, 0.0, 0.0, 1.0);                           
	
}

void topothetisi(int A[4][4][4])
{
	int i,j,k;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					plegma[thesix+i][thesiy+j][thesiz+k]=1;
				}
			}
		}
	}
}

void pese(int x)
{
	if(paused==0){
		thesiy--;
		if(elegxos_sygkrousis(trexon)==1){
			thesiy++;
			topothetisi(trexon);
			neosxhma(trexon);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(msecond,pese,0);
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGL-GLUT 3D Tutorial");
	init();
	neosxhma(trexon);
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutIdleFunc(display);
	glutTimerFunc(msecond,pese,0);
	fotismos();
	glutMainLoop();

	return 1;
}


//dhmiourgei ena neo sxhma kai to apothikeuei ston pinaka A
void neosxhma(int A[4][4][4])
{
	int num,i;
	int x,y,z;
	int flag;

	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			for(z=0; z<4; z++){
				A[x][y][z] = 0;
			}
		}
	}
	
	srand(time(NULL));
	num = 1+rand()%4; 
	//to prwto etsi kai alliws tha mpei
	x = rand()%4;
	y = rand()%4;
	z = rand()%4;
	A[x][y][z]=1;
	for(i=1; i<num; i++){
		do{
			flag=0; //gia na 3erw an exw geitona
			x = rand()%4;
			y = rand()%4;
			z = rand()%4;
			//tha elegxw an exei geitoniko
			if(x>0 && A[x-1][y][z]==1) flag=1;
			if(x<3 && A[x+1][y][z]==1) flag=1;
			if(y>0 && A[x][y-1][z]==1) flag=1;
			if(y<3 && A[x][y+1][z]==1) flag=1;
			if(z>0 && A[x][y][z-1]==1) flag=1;
			if(z<3 && A[x][y][z+1]==1) flag=1;
		}while(A[x][y][z]==1 || flag==0);  //3anaparw shmeio an einai kateillhmenh h den exw geitona
		A[x][y][z]=1;
	} 
	thesix=0;
	thesiy=N-4;
	thesiz=0;
}


void zografise(int A[4][4][4])
{
	int i,j,k;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					glTranslated(i+0.5,j+0.5,k+0.5);
					glColor3f(1,0,0);
					glutSolidCube(1);
					
					glTranslated(-0.5,-0.5,-0.5);
					glColor3f(0,0,0);
					glLineWidth(2);

					glBegin(GL_LINES);
					//aristeri pleura

					if((j==0 || A[i][j-1][k]==0) && (i==0 || A[i-1][j][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(0,0,1);
					}
					if((k==0 || A[i][j][k-1]==0) && (i==0 || A[i-1][j][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(0,1,0);
					}
					
					if((j==3 || A[i][j+1][k]==0) && (i==0 || A[i-1][j][k]==0)){
						glVertex3d(0,1,0);
						glVertex3d(0,1,1);
					}
					
					if((k==3 || A[i][j][k+1]==0) && (i==0 || A[i-1][j][k]==0)){
						glVertex3d(0,1,1);
						glVertex3d(0,0,1);
					}

					//dexia pleura
					if((j==0 || A[i][j-1][k]==0) && (i==3 || A[i+1][j][k]==0)){
						glVertex3d(1,0,0);
						glVertex3d(1,0,1);
					}

					if((k==0 || A[i][j][k-1]==0) && (i==3 || A[i+1][j][k]==0)){
						glVertex3d(1,0,0);
						glVertex3d(1,1,0);
					}

					if((j==3 || A[i][j+1][k]==0) && (i==3 || A[i+1][j][k]==0)){
						glVertex3d(1,1,0);
						glVertex3d(1,1,1);
					}

					if((k==3 || A[i][j][k+1]==0) && (i==3 || A[i+1][j][k]==0)){
						glVertex3d(1,1,1);
						glVertex3d(1,0,1);
					}

					//pisw
					if((k==0 || A[i][j][k-1]==0) && (j==0 || A[i][j-1][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(1,0,0);
					}

					if((k==0 || A[i][j][k-1]==0) && (j==3 || A[i][j+1][k]==0)){
						glVertex3d(0,1,0);
						glVertex3d(1,1,0);
					}

					//mprosta
					if((k==3 || A[i][j][k+1]==0) && (j==0 || A[i][j-1][k]==0)){
						glVertex3d(0,0,1);
						glVertex3d(1,0,1);
					}
					
					if((k==3 || A[i][j][k+1]==0) && (j==3 || A[i][j+1][k]==0)){
						glVertex3d(0,1,1);
						glVertex3d(1,1,1);
					}
					glEnd();

					glTranslated(-i,-j,-k);
				}
			}
		}
	}
	glLineWidth(1);
}



void arxikopoihsh_plegma()
{
	int i,j,k;
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				plegma[i][j][k]=0;
			}
		}
	}
}


void zografise_plegma()
{
	int i,j,k;
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				if(plegma[i][j][k]==1){
					glTranslated(i+0.5,j+0.5,k+0.5);
					glColor3f(0.6,0,0);
					glutSolidCube(1);
					
					glTranslated(-0.5,-0.5,-0.5);
					glColor3f(0,0,0);
					glLineWidth(2);

					glBegin(GL_LINES);
					//aristeri pleura

					if((j==0 || plegma[i][j-1][k]==0) && (i==0 || plegma[i-1][j][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(0,0,1);
					}
					if((k==0 || plegma[i][j][k-1]==0) && (i==0 || plegma[i-1][j][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(0,1,0);
					}
					
					if((j==N-1 || plegma[i][j+1][k]==0) && (i==0 || plegma[i-1][j][k]==0)){
						glVertex3d(0,1,0);
						glVertex3d(0,1,1);
					}
					
					if((k==N-1 || plegma[i][j][k+1]==0) && (i==0 || plegma[i-1][j][k]==0)){
						glVertex3d(0,1,1);
						glVertex3d(0,0,1);
					}

					//dexia pleura
					if((j==0 || plegma[i][j-1][k]==0) && (i==N-1 || plegma[i+1][j][k]==0)){
						glVertex3d(1,0,0);
						glVertex3d(1,0,1);
					}

					if((k==0 || plegma[i][j][k-1]==0) && (i==N-1 || plegma[i+1][j][k]==0)){
						glVertex3d(1,0,0);
						glVertex3d(1,1,0);
					}

					if((j==N-1 || plegma[i][j+1][k]==0) && (i==N-1 || plegma[i+1][j][k]==0)){
						glVertex3d(1,1,0);
						glVertex3d(1,1,1);
					}

					if((k==N-1 || plegma[i][j][k+1]==0) && (i==N-1 || plegma[i+1][j][k]==0)){
						glVertex3d(1,1,1);
						glVertex3d(1,0,1);
					}

					//pisw
					if((k==0 || plegma[i][j][k-1]==0) && (j==0 || plegma[i][j-1][k]==0)){
						glVertex3d(0,0,0);
						glVertex3d(1,0,0);
					}

					if((k==0 || plegma[i][j][k-1]==0) && (j==N-1 || plegma[i][j+1][k]==0)){
						glVertex3d(0,1,0);
						glVertex3d(1,1,0);
					}

					//mprosta
					if((k==N-1 || plegma[i][j][k+1]==0) && (j==0 || plegma[i][j-1][k]==0)){
						glVertex3d(0,0,1);
						glVertex3d(1,0,1);
					}
					
					if((k==N-1 || plegma[i][j][k+1]==0) && (j==N-1 || plegma[i][j+1][k]==0)){
						glVertex3d(0,1,1);
						glVertex3d(1,1,1);
					}
					glEnd();

					glTranslated(-i,-j,-k);
				}
			}
		}
	}
}

int elegxos_sygkrousis(int A[4][4][4])
{
	int i,j,k;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					if(thesix+i<0) return 1; 
					if(thesix+i>=N) return 1;
					if(thesiy+j<0) return 1;
					if(thesiy+j>=N) return 1;
					if(thesiz+k<0) return 1;
					if(thesiz+k>=N) return 1;
					//elegxos an yparxei sygkrousi me to plegma
					if(plegma[thesix+i][thesiy+j][thesiz+k]==1) return 1;
				}
			}
		}
	}
	return 0;
}


int rotate_y(int A[4][4][4])
{
	int i,j,k;
	int found=0;
	int minx,miny,minz;
	int newx,newy,newz;
	int temp[N][N][N];

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				temp[i][j][k]=0;
			}
		}
	}
	
	//gia na vrw thn mikroteri x,z syntetagmenh
	for(i=0; i<4 && found==0; i++){
		for(k=0; k<4 && found==0; k++){
			for(j=0; j<4 && found==0; j++){
				if(A[i][j][k]==1){
					minx=i+thesix;
					miny=j+thesiy;
					minz=k+thesiz;
					found=1;
					break;
				}
			}
		}
	}
	if(found==0){
		printf("Impossible!!!\n");
	}
	
	//tha metakinhsw ola ta koutakia symfwna me ton pinaka metasxhmatismou
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					newx = -(thesiz+k) +(minx+minz);
					newy = (thesiy+j);
					newz = (minz-minx)+(thesix+i);
					//printf("Old: (%d,%d,%d)\tNew: (%d,%d,%d)\n",thesix+i,thesiy+j, thesiz+k,newx,newy,newz);
					if(newx<0 || newx>=N) return 0;
					if(newy<0 || newy>=N) return 0;
					if(newz<0 || newz>=N) return 0;
					if(plegma[newx][newy][newz]==1) return 0;
					temp[newx][newy][newz] = 1;
				}
			}
		}
	}

	//psaxnw na vrw poia einai h arxh tou neou 4x4x4
	//gia na vrw to elaxisto x
	found = 0;
	for(i=0; i<N && found==0; i++){
		for(k=0; k<N && found==0; k++){
			for(j=0; j<N && found==0; j++){
				if(temp[i][j][k]==1){
					found=1;
					minx=i;
					break;
				}
			}
		}
	}
	//gia na vrw to elaxisto z
	found = 0;
	for(k=0; k<N && found==0; k++){
		for(i=0; i<N && found==0; i++){
			for(j=0; j<N && found==0; j++){
				if(temp[i][j][k]==1){
					found=1;
					minz=k;
					break;
				}
			}
		}
	}

	printf("Before:(%d,%d,%d) After: (%d,%d,%d)\n",thesix,thesiy,thesiz,minx,thesiy,minz);
	thesix=minx;
	//paramenei idio to thesiy
	thesiz=minz;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				A[i][j][k] = temp[thesix+i][thesiy+j][thesiz+k];
			}
		}
	}
}


//return 0 if we dont have rotation 
//return 1 if we do
int rotate_z(int A[4][4][4])
{
	int i,j,k;
	int found=0;
	int minx,miny,minz;
	int newx,newy,newz;
	int temp[N][N][N];

	//temp set up
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				temp[i][j][k]=0;
			}
		}
	}
	
	//gia na vrw thn mikroteri x,z syntetagmenh
	for(i=0; i<4 && found==0; i++){
		for(j=0; j<4 && found==0; j++){
			for(k=0; k<4 && found==0; k++){
				if(A[i][j][k]==1){
					minx=i+thesix;
					miny=j+thesiy;
					minz=k+thesiz;
					found=1;
					break;
				}
			}
		}
	}
	if(found==0){
		printf("Impossible!!!\n");
	}
	
	//tha metakinhsw ola ta koutakia symfwna me ton pinaka metasxhmatismou
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					newx = -(thesiy+j) + (minx+miny);	//-(thesiz+k) +(minx+minz);
					newy = (miny-minx)+(thesix+i);  	//(thesiy+j);
					newz = (thesiz+k);			//(minz-minx)+(thesix+i);
					
					if(newx<0 || newx>=N) return 0;
					if(newy<0 || newy>=N) return 0;
					if(newz<0 || newz>=N) return 0;
					if(plegma[newx][newy][newz]==1) return 0;
					temp[newx][newy][newz] = 1;
				}
			}
		}
	}

	//min x
	found = 0;
	for(i=0; i<N && found==0; i++){
		for(k=0; k<N && found==0; k++){
			for(j=0; j<N && found==0; j++){
				if(temp[i][j][k]==1){
					found=1;
					minx=i;
					break;
				}
			}
		}
	}
	//min y 
	found = 0;
	for(i=0; i<N && found==0; i++){
		for(j=0; j<N && found==0; j++){	
			for(k=0; k<N && found==0; k++){
				if(temp[i][j][k]==1){
					found=1;
					miny=j;
					break;
				}
			}
		}
	}

	printf("Before:(%d,%d,%d) After: (%d,%d,%d)\n",thesix,thesiy,thesiz,minx,thesiy,minz);
	thesix=minx;
	thesiy=miny;
	//thesiz stay the same 
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				A[i][j][k] = temp[thesix+i][thesiy+j][thesiz+k];
			}
		}
	}
}

int rotate_x(int A[4][4][4])
{
	int i,j,k;
	int found=0;
	int minx,miny,minz;
	int newx,newy,newz;
	int temp[N][N][N];

	//temp set up
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				temp[i][j][k]=0;
			}
		}
	}
	
	//min x,z
	for(j=0; j<4 && found==0; j++){
		for(k=0; k<4 && found==0; k++){
			for(i=0; i<4 && found==0; i++){
				if(A[i][j][k]==1){
					minx=i+thesix;
					miny=j+thesiy;
					minz=k+thesiz;
					found=1;
					break;
				}
			}
		}
	}
	if(found==0){
		printf("Impossible!!!\n");
	}
	
	//tha metakinhsw ola ta koutakia symfwna me ton pinaka metasxhmatismou
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				if(A[i][j][k]==1){
					newx = (thesix+i);			//-(thesiz+k) +(minx+minz);
					newy = -(thesiz+k) +(miny+minz);  	//(thesiy+j);
					newz = (minz-miny)+(thesiy+j);		//(minz-minx)+(thesix+i);
					
					if(newx<0 || newx>=N) return 0;
					if(newy<0 || newy>=N) return 0;
					if(newz<0 || newz>=N) return 0;
					if(plegma[newx][newy][newz]==1) return 0;
					temp[newx][newy][newz] = 1;
				}
			}
		}
	}

	//psaxnw na vrw poia einai h arxh tou neou 4x4x4
	//min y 
	found = 0;
	for(k=0; k<N && found==0; k++){
		for(j=0; j<N && found==0; j++){
			for(i=0; i<N && found==0; i++){
				if(temp[i][j][k]==1){
					found=1;
					miny=j;
					break;
				}
			}
		}
	}
	//min z
	found = 0;
	for(k=0; k<N && found==0; k++){
		for(i=0; i<N && found==0; i++){
			for(j=0; j<N && found==0; j++){
				if(temp[i][j][k]==1){
					found=1;
					minz=k;
					break;
				}
			}
		}
	}

	printf("Before:(%d,%d,%d) After: (%d,%d,%d)\n",thesix,thesiy,thesiz,minx,thesiy,minz);

	//paramenei idio to thesix
	thesiy=miny;
	thesiz=minz;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
				A[i][j][k] = temp[thesix+i][thesiy+j][thesiz+k];
			}
		}
	}
}



