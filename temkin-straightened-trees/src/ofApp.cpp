#include "ofApp.h"

constexpr const char* PROJECT_NAME = "Straightened Trees";
constexpr const char* CREATOR = "Daniel Temkin";
constexpr const char* RECREATOR = "Violet Graham";

constexpr const bool exportImages = true;

int index = 0;

void ofApp::setup() {

  ofSetLogLevel(OF_LOG_VERBOSE);

  for (int i = 0; i < 13; ++i) {
    string num = to_string(i);
    while (num.size() < 2) {
      num = "0" + num;
    }
    sources.emplace_back();
    sources.back().loadImage("sources/" + num + ".png");
  }

  for (int i = 0; i < 13; ++i) {
    string num = to_string(i);
    while (num.size() < 2) {
      num = "0" + num;
    }
    lines.emplace_back();
    lines.back().loadImage("lines/" + num + ".png");
  }

  calculateOffsets();
  extendOffsets();
  applyOffsets();

  ofSetFrameRate(10);

  if (exportImages) {
    for (size_t i = 0; i < sources.size(); ++i) {
      string num = to_string(i);
      while (num.size() < 2) {
        num = "0" + num;
      }
      sources[i].saveImage("out/" + num + ".png");
    }
  }

}

void ofApp::update() {
  title();
}

void ofApp::draw() {
  sources[index].draw(0, 0, ofGetWidth(), ofGetHeight());
  //lines[index].draw(0, 0, ofGetWidth(), ofGetHeight());
  index++;
  if (index > 12) {
    index = 0;
  }
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR << " - " << RECREATOR
    << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}

void ofApp::calculateOffsets() {

  for (size_t i = 0; i < lines.size(); ++i) {
    //ofLog() << '[';

    const int middle = lines[i].getWidth() / 2;
    vector<int> off;
    off.reserve(lines[i].getHeight());

    for (size_t j = 0; j < lines[i].getHeight(); ++j) {
      off.push_back(0);
      int count = 0;

      for (size_t k = 0; k < lines[i].getWidth(); ++k) {
        //cout << lines[i].getColor(k, j) << ' ' << lines[i].getColor(k, j).r << '\n';
        if (lines[i].getColor(k, j).a != 0) {
          off.back() += k - middle;
          count++;
        }
      }

      if (count) {
        off.back() /= count;
      }

      //cout << off.back() << ' ';

    }

    offsets.push_back(off);

    //cout << ']' << '\n';
  }

  cout << flush;
}

void ofApp::extendOffsets() {
  for (size_t i = 0; i < offsets.size(); ++i) {

    size_t firstIndex;
    int first = 0;
    size_t lastIndex;
    int last;

    for (size_t j = 0; j < offsets[i].size(); ++j) {
      if (offsets[i][j] != 0) {
        if (first == 0) {
          first = offsets[i][j];
          firstIndex = j;
        }
        last = offsets[i][j];
        lastIndex = j;
      }
    }

    for (size_t j = 0; j < firstIndex; ++j) {
      offsets[i][j] = first;
    }

    for (size_t j = lastIndex; j < offsets[i].size(); ++j) {
      offsets[i][j] = last;
    }

  }
}

void ofApp::applyOffsets() {

  for (size_t i = 0; i < sources.size(); ++i) {

    for (size_t j = 0; j < sources[i].getHeight(); ++j) {

      auto temp = make_unique<ofColor[]>(sources[i].getWidth());

      for (size_t k = 0; k < sources[i].getWidth(); ++k) {
        int destination = k + offsets[i][j];
        //int destination = k - offsets[i][j];
        while (destination < 0) {
          destination += sources[i].getWidth();
        }
        while (destination >= sources[i].getWidth()) {
          destination -= sources[i].getWidth();
        }

        temp[destination] = sources[i].getColor(k, j);
      }

      for (size_t k = 0; k < sources[i].getWidth(); ++k) {
        sources[i].setColor(k, j, temp[k]);
      }

    }

    sources[i].update();

  }

}
