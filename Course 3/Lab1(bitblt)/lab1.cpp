#include <windows.h> 
 
// public void main(int argc, char *argv[]) analog in WinAPI
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        // Add MessageBox window
        MessageBox(NULL, "Hello world!!!", "Lab1", MB_OK);
        return 0;
}
