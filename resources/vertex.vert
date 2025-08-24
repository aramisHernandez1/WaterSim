#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


struct Wave {
	float amplitude;
	float frequency;
	//float speed;
	vec2 direction; //Only move on the XZ plane so vec2
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


	float dfdx = 0.0;
	float dfdz = 0.0;

	for(int i = 0; i < waveCount; i++){
		float angle = float(i) * 12.9898;
		vec2 dir = vec2(sin(angle), cos(angle)); //randomish directions
		Wave currentWave = Wave(amp, freq, dir);
		waves[i] = currentWave;

		//float phase = dot(waves[i].direction, aPos.xz) * waves[i].frequency + time * waves[i].speed;
		float phase = dot(waves[i].direction, aPos.xz) * waves[i].frequency + time;

		//Our wave function is e^[sin(x)-1]
		float wave = exp(sin(phase) - 1.0) * waves[i].amplitude;

		sum += wave;

		//Modify our next wave in fbm.
		freq *= 2.0;
		amp *= 0.5;


		float derivative = exp(sin(phase) - 1.0) * cos(phase) * waves[i].frequency * waves[i].amplitude;

		dfdx += derivative * waves[i].direction.x;
		dfdz += derivative * waves[i].direction.y; //Note direction.y is actually the z axis

		
	}

	normal = normalize(vec3(-dfdx, 1.0, -dfdz));
	return sum;
}


void main()
{
	//float displacement = 0.0;
	//float dfdx = 0.0;
	//float dfdz = 0.0;

	//for(int i = 0; i < waveCount; i++){
		
		//float phase = dot(waves[i].direction, aPos.xz) * waves[i].frequency + time * waves[i].speed;

		//Our wave function is e^[sin(x)-1]
		//float wave = exp(sin(phase) - 1.0) * waves[i].amplitude;

		//displacement += wave;

		//Our shared derivative, we will then apply the direction in the x and z axises
		//float derivative = exp(sin(phase) - 1.0) * cos(phase) * waves[i].frequency * waves[i].amplitude;
		
		//dfdx += derivative * waves[i].direction.x;
		//dfdz += derivative * waves[i].direction.y; //Note direction.y is actually the z axis
		
	//}


	//Offset vertex position in the y-axis.
	float displacement = fbm();
	newPos = aPos + vec3(0.0, displacement, 0.0);


	gl_Position = MVP * vec4(newPos, 1.0);



	//This is our tangent taking the cross product gives us a our normal vector. (I think need to research more to make sure, but works and looks good for now.)
	//vec3 tangentX = normalize(vec3(1.0, dfdx * 0.2, 0.0));
	//vec3 tangentZ = normalize(vec3(0.0, dfdz * 0.2, 1.0));

	//normal = normalize(vec3(-dfdx, 1.0, -dfdz));

	//Note change the position to new position when fixed the normals.
	fragPos = newPos;

}