# Water Simulation Graphics Project Using OpenGL.

### My Main Goals with this project
To learn foundational and advanced computer graphics skills while learning and using OpenGL. 
The main point of this project is the learning and not so much the result of this project.

### Current Accomplishments
* Basic OpenGL structure
  * How to set up a context and window
  * How to set up shaders and buffers
  * Using GLSL and adding attributes with shaders.
* Learned basic GLSL
  * Creating a vertex shader with multiple data being passed.
  * Using uniforms in both the vertex and fragment shaders.
  * Using techniques to manipulate meshes (sum of sines for ocean).
* Basic Lightning
  * Used basic Bling Phong lighting model
    * Adding an ambient light, diffuse lighting(I think lambrats diffuse but gotta double check this), and specular lighting.

### Featured Techniques
* Sum of Sines
  * To create waterlike waves, we use the sum of sines
  * **Sum of Sines**\
$$\sum_{i=1}^n A_i \sin(\omega_i + \phi_i + t)$$\
Where **$$A_i$$** is the amplitude, **$$\omega_i$$** is the angel **$$t$$** is time, and **$$\phi_i$$** is the phase\
Adding a directional vector, we end up with\
$$y = f(x, z, t) = \sum_{i=1}^n A_i \sin(\omega_i(d_{ix}x + d_{iz}z) + \phi_i + t)$$
  * The sum of sines is a great start for our water.
* Lambiertian diffuse
  * We set up our normal vectors for the water, done by taking the **partial derivative** of our **sum of sines**\
    #### $$\frac{\partial f}{\partial x}(x, z, t) = \sum_{i=1}^{n} A_i \, \omega_i d_{ix} \cos\!\Big(\omega_i (d_{ix}x + d_{iz}z) + \phi_i + t \Big)$$

### TO DO
* Enhance the lighting system
  * Currently, light is just defined as a position that emits light from this position. want to create a light class and emitters so we can visually see the light source.
* Refactor the program and classes to make them neater and organized
* Add a sun (might relate to the lighting system)
* Add sky
* Add fog
* Fix Camera
  * Everything but mouse movement works with the Camera currently.
* Get IMGui linking to work for the backend side
  * Get a GUI for the number of waves and other parameters




Resources:
https://catlikecoding.com/unity/tutorials/flow/waves/
https://www.youtube.com/watch?v=PH9q0HNBjT4&ab_channel=Acerola
https://developer.nvidia.com/gpugems/gpugems/part-i-natural-effects/chapter-1-effective-water-simulation-physical-models
