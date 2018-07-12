#include"MyWindow.h"

using namespace std;

/*
 * Life Simulator
 * free source, open source
 * 
 * Purpose : to simulization the balance between producers and coumsumers 
 * Current Version : alpha.1.0.1
 * Latstest Change Date : 2018-05-03
 */

int main(int argc, char** argv)
{
	cout << "Starting From Main" << endl;
	MyWindow app(640, 640);
	app.Run();
	return 0;
}
