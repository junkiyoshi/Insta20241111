#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 24;
	auto x_span = radius * sqrt(3);
	auto flg = true;

	auto x_seed = ofRandom(1000);
	auto y_seed = ofRandom(1000);

	for (float y = 0; y <= 720 + radius; y += radius * 1.5) {

		for (float x = 0; x <= 720 + radius; x += x_span) {

			glm::vec3 location;
			if (flg) {

				location = glm::vec3(x, y, 0);
			}
			else {

				location = glm::vec3(x + (x_span / 2), y, 0);
			}

			ofPushMatrix();
			ofTranslate(location);
			ofRotate(90);

			for (int deg = 0; deg < 360; deg += 1) {

				int draw_radius = radius * 0.9;
				int param = deg % 60;

				glm::vec2 vertex;
				if (param == 0) {

					vertex = glm::vec2(draw_radius * cos(deg * DEG_TO_RAD), draw_radius * sin(deg * DEG_TO_RAD));
				}
				else {

					int p1 = deg / 60;
					int p2 = p1 + 1;

					auto p1_deg = p1 * 60;
					auto p2_deg = p2 * 60;

					auto source = glm::vec2(draw_radius * cos(p1_deg * DEG_TO_RAD), draw_radius * sin(p1_deg * DEG_TO_RAD));
					auto target = glm::vec2(draw_radius * cos(p2_deg * DEG_TO_RAD), draw_radius * sin(p2_deg * DEG_TO_RAD));

					vertex = source + ((target - source) / 60 * param);
				}

				glm::vec2 next;
				int next_deg = deg + 1;
				int next_param = next_deg % 60;
				if (next_param == 0) {

					next = glm::vec2(draw_radius * cos(next_deg * DEG_TO_RAD), draw_radius * sin(next_deg * DEG_TO_RAD));
				}
				else {

					int p1 = next_deg / 60;
					int p2 = p1 + 1;

					auto p1_deg = p1 * 60;
					auto p2_deg = p2 * 60;

					auto source = glm::vec2(draw_radius * cos(p1_deg * DEG_TO_RAD), draw_radius * sin(p1_deg * DEG_TO_RAD));
					auto target = glm::vec2(draw_radius * cos(p2_deg * DEG_TO_RAD), draw_radius * sin(p2_deg * DEG_TO_RAD));

					next = source + ((target - source) / 60 * next_param);
				}


				auto noise_value = ofNoise((location.x + vertex.x) * 0.005, (location.y + vertex.y) * 0.005, ofGetFrameNum() * 0.01);
				
				if (noise_value > 0.25 && noise_value < 0.75) {
					
					ofDrawLine(vertex, next);
				}
			}

			ofPopMatrix();
		}
		flg = !flg;
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}