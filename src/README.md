<div id="top"></div>
<!-- PROJECT LOGO -->
<br>
<div align="center">
  <a href="https://github.com/Reda96R/NetPractice">
    <img src="https://raw.githubusercontent.com/Reda96R/NetPractice/main/images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h1 align="center">::: Cub3D_42 :::</h1>
</div>

`This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way
`
# Table of Contents
1. [Project Overview](#project-overview)
2. [Background Theory](#background-theory)
   1. [](#what-is-tcpip)
   2. [](#tcpip)
   3. [](#osi)
3. [](#subnetting)
   1. [](#ip-address)
   2. [](#making-a-subnet)
4. [](#acknowledgement)
5. [](#resources)<div id="top"></div>
# Project Overview:
Cub3D is one of the most interesting projects on the 42 network's curriculum, it is intended to discover the concept of **Ray Casting**, and of course we can't say ray casting without mentioning [**Wolfenstein 3D**](https://en.wikipedia.org/wiki/Wolfenstein_3D) developed by [**Id Software**](https://en.wikipedia.org/wiki/Id_Software), 
![wolfenstein](https://www.google.com/url?sa=i&url=https%3A%2F%2Fmakeagif.com%2Fgif%2Fwolfenstein-3d-speed-run-in-02714-i-am-death-incarnate-difficulty-2013-sda-pc-rFNBsd&psig=AOvVaw3DADIsqcR6nuIA5uh3yzsd&ust=1704383366172000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCLj7r_7IwYMDFQAAAAAdAAAAABAg)
this legendary game holds the distinction of being one of the pioneering titles in the FPS genre and is often considered the grandfather of 3D shooters, this popularity is due to being one of the first games to feature a fully realized 3D environment, allowing players to navigate through levels from a first-person perspective, this along with its system requirements that are quite modest, thanks to Ray Casting. In this project we will deep dive into this concept and discover more about it.
# Background Theory:
## What is this 3D magic?
First of all this "3D magic" is called **Computer graphics**, it refers to the creation, manipulation, and representation of visual images and animations using computers, one of its biggest applications is on the game and entertainment industry, and the two most used technics are **Ray casting** and **Ray tracing** and it wouldn't hurt if we had a look at the last one, right?
### Ray Tracing:
![Ray Tracing](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.ionos.co.uk%2Fdigitalguide%2Fserver%2Fknow-how%2Fray-tracing%2F&psig=AOvVaw21shJSIo_jDS9Wv5SaLQS6&ust=1704390449086000&source=images&cd=vfe&opi=89978449&ved=0CBIQjRxqFwoTCNCEhsfjwYMDFQAAAAAdAAAAABAE)
Ray tracing and Ray casting both depend on  rays, wow, as if we already didn't know, no seriously they depend on virtual light rays that are **Casted** or **Traced** from the focal point of the camera to determine what is visible along the path of the ray in the scene, It's a powerful method for generating highly realistic images by mimicking the behavior of light rays.
> "It’s not the trick that deceives, but the illusion that misleads.” `Harry Houdini`
