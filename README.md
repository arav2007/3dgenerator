# 3dgenerator

First we define a class **point** which has 3 inputs *(l,b,h)*; it is an *array* and it takes data type *float*

Then we create an array for a 3D object with an array called **corner** , which takes 8 inputs, and each data type is *point* .

We take the base as (*0,0,0)*, the *origin*, and base all of our calculations off of that.

We move on next to creating the six fundamental **viewing points** (or the 6 **faces**):

	a) the xy axis (in front of the viewer)
	b) the xy axis (behind the viewer)
	c) the yz axis (to the right of the viewer)
	d) the yz axis (to the left of the viewer)
	e) the xz axis (ontop of the viewer)
	f) the xz axis (below the viewer)
