#kennametal_project 
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


Next we project the object onto a *canvas*, which then hits our view. Let us take the canvas as 1 unit away from us. Let the distance between the cube and the canvas be **x**.

Now let us take proportions.

Let us assume that the canvas is *y x y* units. Let us take one face of the cube which is *h x l*. For simplicity sake, we will assume *h=l*.

Now the distance between the face and our eye is *x+1* units, and the distance between the canvas and our eye is 1 unit.

If we assume the face to shrink to canvas level, and we assume the canvas has the same dimensions as the face, then:

	y=h/(x+1) {or instead of h, it can be l or b}

This expression of *y* refers to the **compressed** version of the edge when it is superimposed onto the canvas.

We also need to set the initial coordinates of the user, depending on which plane we start in.
     a) if we start in plane 1 our coordinates become $(l/2,-x-1,h/2)$.
	b) if we start in plane 2 our coordinates become $(l/2,b+x+1,h/2)$
	c) if we start in plane 3 our coordinates become $(l+x+1,b/2,h/2)$
	d) if we start in plane 4 our coordinates become $(-x-1,b/2,h/2)$
	e) if we start in plane 5 our coordinates become $(l/2,b/2,h+x+1)$
	f) if we start in plane 6 our coordinates become $(l/2,b/2,-x-1)$
	


.