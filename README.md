# This project was made to show how is working ps1 Render piplyne.

Ps1 model model drawing is not same like standart 3D work. Ps1's GPU could draw only 300000 polygons. This is very important. Also you should understand one thing: Early gpu could'nt count float nubers(0.02,0.5 etc.) and this called so familiar ps1 snap model. Anyway, it's now very important part of ps1 style)
Okay let's talk about how i created this. Now Opengl is very smart and i can't feed to him my numbers for convert them into coordinate, wich will be use for vertex shader. But i can