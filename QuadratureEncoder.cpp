#include "QuadratureEncoder.h"


Encoder::Encoder(){
	greenCablePin = 23;
	yellowCablePin = 22;
}

Encoder::Encoder(WheelFace a){
	faceOfWheel = a;

}

void Encoder::attach(int green,int yellow){
  greenCablePin = green;
  yellowCablePin = yellow;

}

void Encoder::attach(WheelFace a,int green,int yellow){
  faceOfWheel = a;
  greenCablePin = green;
  yellowCablePin = yellow;

}

void Encoder::initialize(){
  encoderTicks = 0;
  pinMode(greenCablePin,INPUT);
  digitalWrite(greenCablePin,LOW);
  pinMode(yellowCablePin,INPUT);
  digitalWrite(yellowCablePin,LOW);

}


inline void Encoder::handleInterruptGreen(){
	_greenSet = digitalRead(greenCablePin);
	_yellowSet = digitalRead(yellowCablePin);
	encoderTicks += parseEncoder();
	_greenPrev = _greenSet;
	_yellowPrev = _yellowSet;
}


inline void Encoder::handleInterruptYellow(){
	_yellowSet = digitalRead(yellowCablePin);
	_greenSet = digitalRead(greenCablePin);
	encoderTicks += parseEncoder();
	_yellowPrev = _yellowSet;
	_greenPrev = _greenSet;

}

inline int Encoder::parseEncoder(){
	int result;
	if(_greenPrev && _yellowPrev) {
		if(!_greenSet && _yellowSet) result = -1;
		if(_greenSet && !_yellowSet) result = 1;
	}
	else if(!_greenPrev && _yellowPrev) {
		if(!_greenSet && !_yellowSet) result = -1;
		if(_greenSet && _yellowSet) result = 1;
	}
	else if(!_greenPrev && !_yellowPrev) {
		if(_greenSet && !_yellowSet) result = -1;
		if(!_greenSet && _yellowSet) result = 1;
	}
	else if(_greenPrev && !_yellowPrev) {
		if(_greenSet && _yellowSet) result = -1;
		if(!_greenSet && !_yellowSet) result = 1;
	}
	return faceOfWheel * result;
}
