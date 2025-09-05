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

## Featured Techniques
* **Sum of Sines**
  * To create waterlike waves, we use the sum of sines
  * **Sum of Sines**\
$$\sum_{i=1}^n A_i \sin(\omega_i + \phi_i + t)$$\
Where **$$A_i$$** is the amplitude, **$$\omega_i$$** is the angel **$$t$$** is time, and **$$\phi_i$$** is the phase\
Adding a directional vector, we end up with\
$$y = f(x, z, t) = \sum_{i=1}^n A_i \sin(\omega_i(d_{ix}x + d_{iz}z) + \phi_i + t)$$
  * The sum of sines is a great start for our water.\
* **Lambiertian diffuse**
  * We set up our normal vectors for the water, done by taking the **partial derivative** of our **sum of sines**\
    ### $$\frac{\partial f}{\partial x}(x, z, t) = \sum_{i=1}^{n} A_i \, \omega_i d_{ix} \cos\\Big(\omega_i (d_{ix}x + d_{iz}z) + \phi_i + t \Big)$$
    ### $$\frac{\partial f}{\partial z}(x, z, t) = \sum_{i=1}^{n} A_i \, \omega_i d_{iz} \cos\\Big(\omega_i (d_{ix}x + d_{iz}z) + \phi_i + t \Big)$$
  * We use this partial derivative to set up our tangent vectors.
  * Afterwards, we take the cross product and end up with the vector
    ### $$\vec{N} = \Big(-\tfrac{\partial f}{\partial x}, \ 1, \ -\tfrac{\partial f}{\partial z}\Big)$$
  * Now we normalize our normal vector.
  * Now that we have the normals, we just take the difference between the normals and the light position.\
* **Specular lighting**
* **Euler's waves**
  * Regular sum of sines is great, but we replace our sine wave with any different wave function.
  * Two good wave functions for a more ocean-like wave are two options
    * **Gerstner Waves**
      * Gerstner waves work really well; the only downside is that they can loop on themselves, making weird, unrealistic waves if the parameters are not correct.
    * **Euler Waves**
      * Euler waves are also a really good wave for replicating the ocean
      * But they have the benefit of not looping in on themselves, making them much easier to use, making this my wave of choice.
      * This changes our wave function to\
      ### $$e^{(\sin\theta - 1)}$$
* **Fractional Brownian Motion**
   *  The main idea of fractional Brownian motion is to reduce the amplitude of our wave, making it less than one. I've called this gain.
   *  As well as increasing the frequency of our wave, giving each wave a different frequency and amplitude, but also ensuring our amplitude is less than one.

  

# TO DO
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




### Resources:
[https://catlikecoding.com/unity/tutorials/flow/waves/](https://catlikecoding.com/unity/tutorials/flow/waves/)\
[https://www.youtube.com/watch?v=PH9q0HNBjT4&ab_channel=Acerola](https://www.youtube.com/watch?v=PH9q0HNBjT4&ab_channel=Acerola)\
[GPU Gems](https://developer.nvidia.com/gpugems/gpugems/part-i-natural-effects/chapter-1-effective-water-simulation-physical-models)\
[https://iquilezles.org/articles/fbm/](https://iquilezles.org/articles/fbm/)
