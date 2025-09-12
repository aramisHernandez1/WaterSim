#version 330 core

/*
Some optimizations that may be needed. 

1. Reduce the math inside of this shader, The math for the wave and derivative are very costly on the GPU, computing the math on CPU then passing into gpu may perform better.

*/

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


struct Wave {
	float amplitude;
	float frequency;
	//float speed;
	vec2 direction; //Only move on the XZ plane so vec2

	float derivative;
};


uniform mat4 MVP;
uniform float time;


#define MAX_WAVES 300

uniform int waveCount;
Wave waves[MAX_WAVES];


vec3 newPos;

out vec3 normal;
out vec3 fragPos;


float fbm(){
	float sum = 0.0;

	float amp = 0.5;
	float freq = 1.0;
	float norm = 0.0;

	float gain = 0.70;


	float dfdx = 0.0;
	float dfdz = 0.0;

	for(int i = 1; i <= waveCount; i++){ //Note start at i = 1 because of domain warping might need to look at better solutions for this problem though.
		float angle = float(i);
		vec2 dir = vec2(sin(angle), cos(angle)); //randomish directions
		Wave currentWave = Wave(amp, freq, dir, 0); //Init derivative to 0 for now will define it late
		waves[i] = currentWave;

		//float phase = dot(waves[i].direction, aPos.xz) * waves[i].frequency + time * waves[i].speed;
		float phase = dot(waves[i].direction, aPos.xz) * waves[i].frequency + time;

		//Our wave function is e^[sin(x)-1]
		float wave = exp(sin(phase) - 1.0) * waves[i].amplitude;
		currentWave.derivative = exp(sin(phase) - 1.0) * cos(phase) * waves[i].frequency * waves[i].amplitude;

		sum += wave + waves[i-1].derivative; //Add the previous waves derivatie to give us domain warping
		norm += amp;


		//Modify our next wave in fbm.
		freq *= 1.23;
		amp *= gain;


		//float derivative = exp(sin(phase) - 1.0) * cos(phase) * waves[i].frequency * waves[i].amplitude;

		dfdx += currentWave.derivative * waves[i].direction.x;
		dfdz += currentWave.derivative * waves[i].direction.y; //Note direction.y is actually the z axis

		
	}

	normal = normalize(vec3(-dfdx, 1.0, -dfdz));
	return sum/max(norm, 1e-6) ;
}


void main()
{
	float displacement = fbm();
	newPos = aPos + vec3(0.0, displacement, 0.0);


	gl_Position = MVP * vec4(newPos, 1.0);


	fragPos = newPos;

}