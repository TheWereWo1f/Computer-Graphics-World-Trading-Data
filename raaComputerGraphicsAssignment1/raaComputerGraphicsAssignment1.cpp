#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <map>
#include <conio.h>

#include <raaCamera/raaCamera.h>
#include <raaUtilities/raaUtilities.h>
#include <raaMaths/raaMaths.h>
#include <raaMaths/raaVector.h>
#include <raaSystem/raaSystem.h>
#include <raaPajParser/raaPajParser.h>
#include <raaText/raaText.h>

#include "raaConstants.h"
#include "raaParse.h"
#include "raaControl.h"

// NOTES
// look should look through the libraries and additional files I have provided to familarise yourselves with the functionallity and code.
// The data is loaded into the data structure, managed by the linked list library, and defined in the raaSystem library.
// You will need to expand the definitions for raaNode and raaArc in the raaSystem library to include additional attributes for the siumulation process
// If you wish to implement the mouse selection part of the assignment you may find the camProject and camUnProject functions usefull


// core system global data
raaCameraInput g_Input; // structure to hadle input to the camera comming from mouse/keyboard events
raaCamera g_Camera; // structure holding the camera position and orientation attributes
raaSystem g_System; // data structure holding the imported graph of data - you may need to modify and extend this to support your functionallity
raaControl g_Control; // set of flag controls used in my implmentation to retain state of key actions

// global var: parameter name for the file to load
const static char csg_acFileParam[] = { "-input" };

//constants for the continents
const static unsigned int g_uiAfrica = 1;
const static unsigned int g_uiAmerica = 2;
const static unsigned int g_uiEurope = 3;
const static unsigned int g_uiNorthAmerica = 4;
const static unsigned int g_uiOceania = 5;
const static unsigned int g_uiSouthAmerica = 6;

//constants for world system
const static unsigned int g_uiFirstWorld = 1;
const static unsigned int g_uiSecondWorld = 2;
const static unsigned int g_uiThirdWorld = 3;

static unsigned int gs_isRunning = 0;
static unsigned int gs_uiShowHint = 0;

// global var: file to load data from
char g_acFile[256];

// core functions -> reduce to just the ones needed by glut as pointers to functions to fulfill tasks
void display(); // The rendering function. This is called once for each frame and you should put rendering code here
void idle(); // The idle function is called at least once per frame and is where all simulation and operational code should be placed
void reshape(int iWidth, int iHeight); // called each time the window is moved or resived
void keyboard(unsigned char c, int iXPos, int iYPos); // called for each keyboard press with a standard ascii key
void keyboardUp(unsigned char c, int iXPos, int iYPos); // called for each keyboard release with a standard ascii key
void sKeyboard(int iC, int iXPos, int iYPos); // called for each keyboard press with a non ascii key (eg shift)
void sKeyboardUp(int iC, int iXPos, int iYPos); // called for each keyboard release with a non ascii key (eg shift)
void mouse(int iKey, int iEvent, int iXPos, int iYPos); // called for each mouse key event
void motion(int iXPos, int iYPos); // called for each mouse motion event

// Non glut functions
void myInit(); // the myinit function runs once, before rendering starts and should be used for setup
void nodeDisplay(raaNode* pNode); // callled by the display function to draw nodes
void arcDisplay(raaArc* pArc); // called by the display function to draw arcs
void buildGrid(); // 

//My functions
void direction(raaArc* pArc);
void resetForce(raaNode* pNode);
void loopNode(raaNode* pNode);
void loopArc(raaArc* pArc);
void updateNode(raaNode* pNode);
void randomiseLayout(raaNode* pNode);
void centerCamera(raaNode* pNode);
void checkColour(raaNode* pNode);
void menuActions(int value);
void displayText(char* name);
void controlActions(int value);
void distance();
void subMenuHeadsUp();
void subPinned();
void subLayouts();
void showHint();



void nodeDisplay(raaNode* pNode) // function to render a node (called from display())
{
	checkColour(pNode);

	float* pos = pNode->m_afPosition;
	unsigned int uiWorld = pNode->m_uiWorldSystem;

	if (uiWorld == g_uiFirstWorld) {
		float mass = pNode->m_fMass;
		float radius = mathsRadiusOfSphereFromVolume(mass);
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glutSolidSphere(radius, 10, 10);
		glPopMatrix();
	}
	else if (uiWorld == g_uiSecondWorld) {
		float mass = pNode->m_fMass;
		float dimension = mathsDimensionOfCubeFromVolume(mass);
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]); //coords for cube
		glutSolidCube(dimension); // dimensions of the cube
		glPopMatrix(); 
	}
	else if (uiWorld == g_uiThirdWorld) {
		float mass = pNode->m_fMass;
		float radius = mathsRadiusOfConeFromVolume(mass);
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(270, 1.0f, 0.0f, 0.0f);
		if (radius < 50) {
			glutSolidCone(radius, 10, 10, 10);
		}
		else {
			glutSolidCone(radius, 20, 10, 10);
		}
		glPopMatrix();
	}
}

void checkColour(raaNode* pNode) {
	unsigned int continent = pNode->m_uiContinent;

	if (continent == g_uiAfrica) {
		float afCol[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
	else if (continent == g_uiAmerica) {
		float afCol[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
	else if (continent == g_uiEurope) {
		float afCol[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
	else if (continent == g_uiNorthAmerica) {
		float afCol[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
	else if (continent == g_uiOceania) {
		float afCol[] = { 1.0f, 0.0f, 1.0f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
	else if (continent == g_uiSouthAmerica) {
		float afCol[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		utilitiesColourToMat(afCol, 2.0f);
	}
}

void displayText(raaNode* pNode) {

	checkColour(pNode);

	unsigned int uiWorld = pNode->m_uiWorldSystem;

	if (uiWorld == g_uiFirstWorld) {
		glPushMatrix();
		glTranslatef(pNode->m_afPosition[0], pNode->m_afPosition[1] + 20.0f, pNode->m_afPosition[2]);
		glScalef(10.0f, 10.0f, 1.0f);
		outlinePrint(pNode->m_acName, true);
		glPopMatrix();
	}
	else if (uiWorld == g_uiSecondWorld) {
		glPushMatrix();
		glTranslatef(pNode->m_afPosition[0], pNode->m_afPosition[1] + 15.0f, pNode->m_afPosition[2]);
		glScalef(10.0f, 10.0f, 1.0f);
		outlinePrint(pNode->m_acName, true);
		glPopMatrix();
	}
	else if (uiWorld == g_uiThirdWorld) {
		glPushMatrix();
		glTranslatef(pNode->m_afPosition[0], pNode->m_afPosition[1] + 15.0f, pNode->m_afPosition[2]);
		glScalef(10.0f, 10.0f, 1.0f);
		outlinePrint(pNode->m_acName, true);
		glTranslatef(pNode->m_afPosition[0], pNode->m_afPosition[1] + 15.0f, pNode->m_afPosition[2]);
		glPopMatrix();
	}
}
/*
void cameraRotation(raaCamera* pCamera) {
	float* rotation = pCamera->m_fVR;
	glPushMatrix();
	glRotatef(rotation[0], rotation[1], rotation[3], rotation[4]);
	glPopMatrix();
	printf("%f", rotation);
}
*/

void resetForce(raaNode* pNode) {
	if (pNode) vecInit(pNode->m_fResultantForce);
}

void direction(raaArc* pArc)
{
	raaNode* one = pArc->m_pNode0;
	raaNode* two = pArc->m_pNode1;

	float* pos1 = one->m_afPosition;
	float* pos2 = two->m_afPosition;

	float pVSub[4];
	vecSub(pos1, pos2, pVSub);

	float pVNormalise[4];
	vecNormalise(pVSub, pVNormalise);
}

void springForce(raaArc* pArc) {
	raaNode* one = pArc->m_pNode0;
	raaNode* two = pArc->m_pNode1;

	float* pos1 = one->m_afPosition;
	float* pos2 = two->m_afPosition;

	float currentPosition = vecDistance(pos1, pos2);

	float extension = currentPosition - 0.5;
}

void loopNode(raaNode* pNode) {
	vecInitPVec(pNode->m_fResultantForce);
}

void loopArc(raaArc* pArc) {

	float directionVector[4];
	vecInitDVec(directionVector);

	vecSub(pArc->m_pNode0->m_afPosition, pArc->m_pNode1->m_afPosition, directionVector);
	vecNormalise(directionVector, directionVector);

	float distance = vecDistance(pArc->m_pNode0->m_afPosition, pArc->m_pNode1->m_afPosition);
	float extension = (distance - pArc->m_fIdealLen) / pArc->m_fIdealLen;
	float scalarForce = extension * pArc->m_fSpringCoef;

	float scalarForceVector[4];
	vecInitPVec(scalarForceVector);

	vecScalarProduct(directionVector, scalarForce, scalarForceVector);

	vecAdd(pArc->m_pNode1->m_fResultantForce, scalarForceVector, pArc->m_pNode1->m_fResultantForce);
	vecSub(pArc->m_pNode0->m_fResultantForce, scalarForceVector, pArc->m_pNode0->m_fResultantForce);
	//printf("%f", scalarForceVector);
}

void updateNode(raaNode* pNode) {
	if (gs_isRunning == 1) {
		float l_fa[4];
		vecInitPVec(l_fa);

		vecScalarProduct(pNode->m_fResultantForce, 1.0f / pNode->m_fMass, l_fa);

		float l_ftime = 0.01f / 60.0f;

		float l_fs[4];
		vecInitPVec(l_fs);
		float l_fvt[4];
		vecInitPVec(l_fvt);
		vecScalarProduct(pNode->m_fVelocity, l_ftime, l_fvt);
		float l_fatsqrd[4];
		vecInitPVec(l_fatsqrd);
		vecScalarProduct(l_fa, l_ftime * l_ftime, l_fatsqrd);
		float fatsqrdhalved[4];
		vecInitPVec(fatsqrdhalved);
		vecScalarProduct(l_fatsqrd, 0.5f, fatsqrdhalved);
		vecAdd(l_fvt, fatsqrdhalved, l_fs);

		//update postion of nodes
		vecAdd(pNode->m_afPosition, l_fs, pNode->m_afPosition);

		float l_fv[4];
		vecInitPVec(l_fv);
		vecScalarProduct(l_fs, 1.0f / l_ftime, pNode->m_fVelocity);
		vecScalarProduct(pNode->m_fVelocity, 0.90f, pNode->m_fVec);
	}
}

void arcDisplay(raaArc* pArc) // function to render an arc (called from display())
{
	raaNode* m_pNode0 = pArc->m_pNode0;
	raaNode* m_pNode1 = pArc->m_pNode1;

	float* pos1 = m_pNode0->m_afPosition;
	float* pos2 = m_pNode1->m_afPosition;

	glLineWidth(0.4);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(pos1[0], pos1[1], pos1[2]);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(pos2[0], pos2[1], pos2[2]);
	glEnd();
	glPopAttrib();
	// put your arc rendering (ogl) code here
}

void randomiseLayout(raaNode* pNode) {
	float* position = pNode->m_afPosition;
	
	float randPosition[4];

	vecInitCVec(randPosition, 1.0f);

	float out[4];
	vecRand(*randPosition, *position, out);
	
	float test[4];
	vecSet(out[0], out[1], out[2], test);

	glPushMatrix();
	glTranslatef(test[0], test[1], test[2]);
	glutSolidSphere(10, 10, 10);
	glPopMatrix();

	//vecRand(position);
}

// draw the scene. Called once per frame and should only deal with scene drawing (not updating the simulator)
void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear the rendering buffers

	glLoadIdentity(); // clear the current transformation state
	glMultMatrixf(camObjMat(g_Camera)); // apply the current camera transform

	// draw the grid if the control flag for it is true	
	if (controlActive(g_Control, csg_uiControlDrawGrid)) glCallList(gs_uiGridDisplayList);

	glPushAttrib(GL_ALL_ATTRIB_BITS); // push attribute state to enable constrained state changes
	visitNodes(&g_System, nodeDisplay); // loop through all of the nodes and draw them with the nodeDisplay function
	visitArcs(&g_System, arcDisplay); // loop through all of the arcs and draw them with the arcDisplay 
	visitNodes(&g_System, displayText);
	showHint();
	//visitNodes(&g_System, randomiseLayout);
	//cameraRotation(&g_Camera);
	glPopAttrib();

	glFlush(); // ensure all the ogl instructions have been processed
	glutSwapBuffers(); // present the rendered scene to the screen
}

// processing of system and camera data outside of the renderng loop
void idle()
{
	controlChangeResetAll(g_Control); // re-set the update status for all of the control flags
	camProcessInput(g_Input, g_Camera); // update the camera pos/ori based on changes since last render
	camResetViewportChanged(g_Camera); // re-set the camera's viwport changed flag after all events have been processed
	glutPostRedisplay();// ask glut to update the screen
	visitNodes(&g_System, loopNode);
	visitArcs(&g_System, loopArc);
	visitNodes(&g_System, updateNode);
	//visitNodes(&g_System, randomiseLayout);
	//visitNodes(&g_System, centerCamera);
}

// respond to a change in window position or shape
void reshape(int iWidth, int iHeight)
{
	glViewport(0, 0, iWidth, iHeight);  // re-size the rendering context to match window
	camSetViewport(g_Camera, 0, 0, iWidth, iHeight); // inform the camera of the new rendering context size
	glMatrixMode(GL_PROJECTION); // switch to the projection matrix stack 
	glLoadIdentity(); // clear the current projection matrix state
	gluPerspective(csg_fCameraViewAngle, ((float)iWidth) / ((float)iHeight), csg_fNearClip, csg_fFarClip); // apply new state based on re-sized window
	glMatrixMode(GL_MODELVIEW); // swap back to the model view matrix stac
	glGetFloatv(GL_PROJECTION_MATRIX, g_Camera.m_afProjMat); // get the current projection matrix and sort in the camera model
	glutPostRedisplay(); // ask glut to update the screen
}

// detect key presses and assign them to actions
void keyboard(unsigned char c, int iXPos, int iYPos)
{
	switch (c)
	{
	case 'w':
		camInputTravel(g_Input, tri_pos); // mouse zoom
		break;
	case 's':
		camInputTravel(g_Input, tri_neg); // mouse zoom
		break;
	case 'c':
		camPrint(g_Camera); // print the camera data to the comsole
		break;
	case 'g':
		controlToggle(g_Control, csg_uiControlDrawGrid); // toggle the drawing of the grid
		break;
	case 'r':
		if (gs_isRunning == 0) {
			gs_isRunning = 1;
		}
		else if (gs_isRunning == 1) {
			gs_isRunning = 0;
		}
		break;
	//case ''
	}
}

// detect standard key releases
void keyboardUp(unsigned char c, int iXPos, int iYPos)
{
	switch (c)
	{
		// end the camera zoom action
	case 'w':
	case 's':
		camInputTravel(g_Input, tri_null);
		break;
	}
}

void sKeyboard(int iC, int iXPos, int iYPos)
{
	// detect the pressing of arrow keys for ouse zoom and record the state for processing by the camera
	switch (iC)
	{
	case GLUT_KEY_UP:
		camInputTravel(g_Input, tri_pos);
		break;
	case GLUT_KEY_DOWN:
		camInputTravel(g_Input, tri_neg);
		break;
	}
}

void sKeyboardUp(int iC, int iXPos, int iYPos)
{
	// detect when mouse zoom action (arrow keys) has ended
	switch (iC)
	{
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		camInputTravel(g_Input, tri_null);
		break;
	}
}

void mouse(int iKey, int iEvent, int iXPos, int iYPos)
{
	// capture the mouse events for the camera motion and record in the current mouse input state
	if (iKey == GLUT_LEFT_BUTTON)
	{
		camInputMouse(g_Input, (iEvent == GLUT_DOWN) ? true : false);
		if (iEvent == GLUT_DOWN)camInputSetMouseStart(g_Input, iXPos, iYPos);
	}
	else if (iKey == GLUT_MIDDLE_BUTTON)
	{
		camInputMousePan(g_Input, (iEvent == GLUT_DOWN) ? true : false);
		if (iEvent == GLUT_DOWN)camInputSetMouseStart(g_Input, iXPos, iYPos);
	}
	else if (iKey == GLUT_RIGHT_BUTTON)
	{
		int sub = glutCreateMenu(menuActions);

		glutAddMenuEntry("Toggle Status", 13);
		glutAddMenuEntry("Toggle Info", 14);
		glutAddMenuEntry("Toggle Help", 15);
		glutAddMenuEntry("Toggle Performance Trace", 16);
		//glutCreateMenu(menuActions);

		int control = glutCreateMenu(menuActions);

		glutAddMenuEntry("Clear Pinned Nodes", 10);
		glutAddMenuEntry("Swap Pinned Nodes", 11);
		glutAddMenuEntry("Pin All Nodes", 12);
		//glutCreateMenu(menuActions);

		int layouts = glutCreateMenu(menuActions);

		glutAddMenuEntry("Randomise Positions", 7);
		glutAddMenuEntry("World System Layout", 8);
		glutAddMenuEntry("Continent Layout", 9);
		glutCreateMenu(menuActions);

		glutAddSubMenu("Pinned Control", control);
		glutAddSubMenu("Layouts", layouts);
		glutAddSubMenu("Head Up Display", sub);


		glutAddMenuEntry("Toggle Grid", 1);
		glutAddMenuEntry("Toggle Solver", 2);
		glutAddMenuEntry("Center Camera", 3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();

	}
}

void menuActions(int value) {
	switch (value) {
	case 1:
		controlToggle(g_Control, csg_uiControlDrawGrid);
		break;
	case 2:
		if (gs_isRunning == 0) {
			gs_isRunning = 1;
		}
		else if (gs_isRunning == 1) {
			gs_isRunning = 0;
		}
		break;
	case 3:
		camReset(g_Camera);
		break;
	case 7:

		break;
	case 14:
		if (gs_uiShowHint == 0) {
			gs_uiShowHint = 1;
		}
		else if (gs_uiShowHint == 1)
		{
			gs_uiShowHint = 0;
		}
	}
	glutPostRedisplay();
}

void showHint() {
	if (gs_uiShowHint == 1) {
		/*
		char string[] = "Shape denotes world order \n bla bla bla bla";
		//int w;
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
		

		//glRasterPos2f(csg_uiWindowDefinition[3]-300, csg_uiWindowDefinition[4]-200);
		float x = 0.5f;
		glColor3f(1.0f, 0.0f, 0.0f);
		int len = (int)strlen(string);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
		}
		*/
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, 500, 0.0, 200);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(0, 195);
		glColor3f(1.0f, 1.0f, 1.0f);
		char string[] = "Menu here";
		int len = (int)strlen(string);
		//int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
			glutBitmapWidth(GLUT_BITMAP_8_BY_13, string[i]);
			//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, )
		}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
}

void motion(int iXPos, int iYPos)
{
	// if mouse is in a mode that tracks motion pass this to the camera model
	if (g_Input.m_bMouse || g_Input.m_bMousePan) camInputSetMouseLast(g_Input, iXPos, iYPos);
}


void myInit()
{
	// setup my event control structure
	controlInit(g_Control);

	// initalise the maths library
	initMaths();

	// Camera setup
	camInit(g_Camera); // initalise the camera model
	camInputInit(g_Input); // initialise the persistant camera input data 
	camInputExplore(g_Input, true); // define the camera navigation mode

	// opengl setup - this is a basic default for all rendering in the render loop
	glClearColor(csg_afColourClear[0], csg_afColourClear[1], csg_afColourClear[2], csg_afColourClear[3]); // set the window background colour
	glEnable(GL_DEPTH_TEST); // enables occusion of rendered primatives in the window
	glEnable(GL_LIGHT0); // switch on the primary light
	glEnable(GL_LIGHTING); // enable lighting calculations to take place
	glEnable(GL_BLEND); // allows transparency and fine lines to be drawn
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // defines a basic transparency blending mode
	glEnable(GL_NORMALIZE); // normalises the normal vectors used for lighting - you may be able to switch this iff (performance gain) is you normalise all normals your self
	glEnable(GL_CULL_FACE); // switch on culling of unseen faces
	glCullFace(GL_BACK); // set culling to not draw the backfaces of primatives

	// build the grid display list - display list are a performance optimization 
	buildGrid();

	// initialise the data system and load the data file
	initSystem(&g_System);
	parse(g_acFile, parseSection, parseNetwork, parseArc, parsePartition, parseVector);
}

int main(int argc, char* argv[])
{
	// check parameters to pull out the path and file name for the data file
	for (int i = 0; i < argc; i++) if (!strcmp(argv[i], csg_acFileParam)) sprintf_s(g_acFile, "%s", argv[++i]);


	if (strlen(g_acFile))
	{
		// if there is a data file

		glutInit(&argc, (char**)argv); // start glut (opengl window and rendering manager)

		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // define buffers to use in ogl
		glutInitWindowPosition(csg_uiWindowDefinition[csg_uiX], csg_uiWindowDefinition[csg_uiY]);  // set rendering window position
		glutInitWindowSize(csg_uiWindowDefinition[csg_uiWidth], csg_uiWindowDefinition[csg_uiHeight]); // set rendering window size
		glutCreateWindow("raaAssignment1-2017");  // create rendering window and give it a name

		buildFont(); // setup text rendering (use outline print function to render 3D text


		myInit(); // application specific initialisation

		// provide glut with callback functions to enact tasks within the event loop
		glutDisplayFunc(display);
		glutIdleFunc(idle);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutKeyboardUpFunc(keyboardUp);
		glutSpecialFunc(sKeyboard);
		glutSpecialUpFunc(sKeyboardUp);
		glutMouseFunc(mouse);
		glutMotionFunc(motion);
		glutMainLoop(); // start the rendering loop running, this will only		ext when the rendering window is closed 

		killFont(); // cleanup the text rendering process

		return 0; // return a null error code to show everything worked
	}
	else
	{
		// if there isn't a data file 

		printf("The data file cannot be found, press any key to exit...\n");
		_getch();
		return 1; // error code
	}
}

void buildGrid()
{
	if (!gs_uiGridDisplayList) gs_uiGridDisplayList = glGenLists(1); // create a display list

	glNewList(gs_uiGridDisplayList, GL_COMPILE); // start recording display list

	glPushAttrib(GL_ALL_ATTRIB_BITS); // push attrib marker
	glDisable(GL_LIGHTING); // switch of lighting to render lines

	glColor4fv(csg_afDisplayListGridColour); // set line colour

	// draw the grid lines
	glBegin(GL_LINES);
	for (int i = (int)csg_fDisplayListGridMin; i <= (int)csg_fDisplayListGridMax; i++)
	{
		glVertex3f(((float)i) * csg_fDisplayListGridSpace, 0.0f, csg_fDisplayListGridMin * csg_fDisplayListGridSpace);
		glVertex3f(((float)i) * csg_fDisplayListGridSpace, 0.0f, csg_fDisplayListGridMax * csg_fDisplayListGridSpace);
		glVertex3f(csg_fDisplayListGridMin * csg_fDisplayListGridSpace, 0.0f, ((float)i) * csg_fDisplayListGridSpace);
		glVertex3f(csg_fDisplayListGridMax * csg_fDisplayListGridSpace, 0.0f, ((float)i) * csg_fDisplayListGridSpace);
	}
	glEnd(); // end line drawing

	glPopAttrib(); // pop attrib marker (undo switching off lighting)

	glEndList(); // finish recording the displaylist
}