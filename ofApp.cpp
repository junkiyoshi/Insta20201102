#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	float R = 200;
	for (int i = 0; i < 8; i++) {

		auto noise_param_1 = ofRandom(1000);
		auto noise_param_2 = ofRandom(1000);
		for (float v = 0; v < 360; v += 1) {

			auto noise_location = glm::vec2(R * cos(v * DEG_TO_RAD), R * sin(v * DEG_TO_RAD));

			float u = ofMap(ofNoise(noise_param_1, noise_location.x * 0.005, noise_location.y * 0.005, ofGetFrameNum() * 0.01), 0, 1, -360, 360);
			float r = ofMap(ofNoise(noise_param_2, noise_location.x * 0.002, noise_location.y * 0.002, ofGetFrameNum() * 0.01), 0, 1, 50, 50);

			this->mesh.addVertex(this->make_point(R, r, u, v));
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			if (glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 15) {

				this->mesh.addIndex(i); this->mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.drawWireframe();
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofDrawSphere(this->mesh.getVertex(i), 1.5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}