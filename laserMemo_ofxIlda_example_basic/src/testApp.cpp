#include "testApp.h"
#include "ofxIldaFrame.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
    etherdream.setup();
    etherdream.setPPS(30000);
	
	/*
	int nPoints = 40;
	for (int i=0; i<nPoints; i++){
		ofxIlda::Point ildaPoint;
		ofFloatColor ptCol;
		ofPoint ptLoc;
		
		float t = ofMap(i, 0, nPoints, 0, TWO_PI);
		float px = 0.5 + 0.2*cos(t);
		float py = 0.5 + 0.2*sin(t);
		px = ofClamp(px, 0,1);
		py = ofClamp(py, 0,1);
		ptLoc.set(px, py);
		
		float hue = ofMap(i, 0, nPoints, 0, 255);
		ptCol = ofColor::fromHsb(hue, 255, 255);
		
		ildaPoint.set(ptLoc, ptCol);
	}
	 */
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
}



//--------------------------------------------------------------
void testApp::draw() {
    // do your thang
    ildaFrame.update();
    
    // draw to the screen
    ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // send points to the etherdream
    etherdream.setPoints(ildaFrame);
    
    ofSetColor(255);
    ofDrawBitmapString(ildaFrame.getString(), 10, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
        case 'f': ofToggleFullscreen(); break;
			
		case '-':
			ildaFrame.params.output.color.r -= 0.05;
			ildaFrame.params.output.color.g -= 0.05;
			ildaFrame.params.output.color.b -= 0.05;
			ildaFrame.params.output.color.r = MAX(ildaFrame.params.output.color.r , 0.0);
			ildaFrame.params.output.color.g = MAX(ildaFrame.params.output.color.g , 0.0);
			ildaFrame.params.output.color.b = MAX(ildaFrame.params.output.color.b , 0.0);
			break;
		case '=':
			ildaFrame.params.output.color.r += 0.05;
			ildaFrame.params.output.color.g += 0.05;
			ildaFrame.params.output.color.b += 0.05;
			ildaFrame.params.output.color.r = MIN(ildaFrame.params.output.color.r , 1.0);
			ildaFrame.params.output.color.g = MIN(ildaFrame.params.output.color.g , 1.0);
			ildaFrame.params.output.color.b = MIN(ildaFrame.params.output.color.b , 1.0);
			break;
			
            // clear the frame
        case 'c':
		case ' ':
			ildaFrame.clear(); break;
            
            // draw rectangle
        case 'r': {
            ofPolyline p = ofPolyline::fromRectangle(ofRectangle(ofRandomuf()/2, ofRandomuf()/2, ofRandomuf()/2, ofRandomuf()/2));
            ildaFrame.addPoly(p);
        }
            break;

            // change color
        case 'R': ildaFrame.params.output.color.r = 1 - ildaFrame.params.output.color.r; break;
        case 'G': ildaFrame.params.output.color.g = 1 - ildaFrame.params.output.color.g; break;
        case 'B': ildaFrame.params.output.color.b = 1 - ildaFrame.params.output.color.b; break;

            // toggle draw lines (on screen only)
        case 'l': ildaFrame.params.draw.lines ^= true; break;
            
            // toggle loop for last poly
        case 'o': ildaFrame.getLastPoly().setClosed(ildaFrame.getLastPoly().isClosed()); break;
            
            // toggle draw points (on screen only)
        case 'p': ildaFrame.params.draw.points ^= true; break;
            
            // adjust point count
        case '.': ildaFrame.polyProcessor.params.targetPointCount++; break;
        case ',': if(ildaFrame.polyProcessor.params.targetPointCount > 10) ildaFrame.polyProcessor.params.targetPointCount--; break;

            // adjust point count quicker
        case '>': ildaFrame.polyProcessor.params.targetPointCount += 10; break;
        case '<': if(ildaFrame.polyProcessor.params.targetPointCount > 20) ildaFrame.polyProcessor.params.targetPointCount -= 10; break;
            
            // flip image
        case 'x': ildaFrame.params.output.transform.doFlipX ^= true; break;
        case 'y': ildaFrame.params.output.transform.doFlipY ^= true; break;

            // cap image
        case 'X': ildaFrame.params.output.doCapX ^= true; break;
        case 'Y': ildaFrame.params.output.doCapY ^= true; break;

            // move output around
        case OF_KEY_UP: ildaFrame.params.output.transform.offset.y -= 0.05; break;
        case OF_KEY_DOWN: ildaFrame.params.output.transform.offset.y += 0.05; break;
        case OF_KEY_LEFT: ildaFrame.params.output.transform.offset.x -= 0.05; break;
        case OF_KEY_RIGHT: ildaFrame.params.output.transform.offset.x += 0.05; break;
            
            // scale output
        case 'w': ildaFrame.params.output.transform.scale.y += 0.05; break;
        case 's': ildaFrame.params.output.transform.scale.y -= 0.05; break;
        case 'a': ildaFrame.params.output.transform.scale.x -= 0.05; break;
        case 'd': ildaFrame.params.output.transform.scale.x += 0.05; break;
            
        case 'C': ildaFrame.drawCalibration(); break;
		case 'Q':
			etherdream.setup();
			break;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	addScreenspacePointToMostRecentPolyline (x, y);

	ildaFrame.params.output.transform.doFlipY = true;
	ildaFrame.params.output.transform.doFlipX = true;
}



//--------------------------------------------------------------
void testApp::addScreenspacePointToMostRecentPolyline (float sx, float sy){
	// draw a line to the (e.g) cursor (normalized coordinates) in the last poly created
	float x01 = sx / (float)ofGetWidth();
	float y01 = sy / (float)ofGetHeight();
	x01 = ofClamp(x01, 0,1);
	y01 = ofClamp(y01, 0,1);
	ildaFrame.getLastPoly().lineTo(x01, y01);
	
}

//--------------------------------------------------------------
void testApp::addNormalizedPointToMostRecentPolyline (float x01, float y01){
	x01 = ofClamp(x01, 0,1);
	y01 = ofClamp(y01, 0,1);
	ildaFrame.getLastPoly().lineTo(x01, y01);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    // create a new poly in the ILDA frame
    ildaFrame.addPoly();
}
