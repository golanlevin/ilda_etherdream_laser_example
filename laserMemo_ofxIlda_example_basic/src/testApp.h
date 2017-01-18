#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
    ofxIlda::Frame ildaFrame;   // Data structure to store and manage ILDA frame drawings
    ofxEtherdream etherdream;   // The interface to the etherdream device
	
	void addScreenspacePointToMostRecentPolyline (float sx, float sy);
	void addNormalizedPointToMostRecentPolyline (float x01, float y01);
};
