

Raylib is a c++ library that allows 3d rendering and camera setup. #kennametal_project

Different functions:
	a) **Vector 3**; this is just an *inbuilt struct* that represents a vector with 3 parameters
	b) **InitWindow**;  this initializes the window with 3 parameters - *Height, Width, and title*.
	c) `Camera3d camera = {0}` initializes a struct, which we name *camera*.
	d) `camera.position` is set to `planecam[0]`, which is our initial plane of *reference*.
	e)  `camera.target` is set to the *original coordinates*, which is the *centre* of the cube.
	f)  `camera.up` is set to the *Z axis*, which in this case is the axis for *vertical movement*.
	g)  `camera.fovy` is set to the `60.0f`, which is our *frame of view*. 
	h)  `camera.projection` is set to `CAMERA_PERSPECTIVE`, which is the default perspective of raylib.
	i) `SetTargetFPS(60)`,  sets our *fps* to 60.
	j)  **autorotate**; this is a *boolean* value, for the *automatic rotation* of the cube, and it is set to 1, by default.
	k) **WindowShouldClose**: this is a function that regulates the *closing* of the window.
	l) **IsKeyPressed()**, this function checks if a particular key is pressed
	m) `for (int k = 0; k < 6; k++) {`
            `if (IsKeyPressed(KEY_ONE + k)) {`
                `camera.position = planeCam[k];`
                `camera.up = (k < 4) ? (Vector3){0,0,1} : (Vector3){0,1,0};`
                `currentPlane = k + 1;`
            `}`
        This program checks which specific key is pressed down.
        `if (IsKeyPressed(KEY_ONE + k))`, checks if the key is pressed. The *for* loop iterates through all 6 different numbers. `KEY_ONE` is the command for checking if *key one* is pressed, and `+ k`, adds the *variable k*, so it cycles through all 6 numbers.
    n) **BeginDrawing**, *begins* the rendering of the 3d graphics. 
    o) **DrawText**, draws the specific text. Its parameters are `(TextFormat("sentence %x",a),x,y,z,colour)`, where `%x` is the *placeholder*, `a` is the variable, `(x,y,z)` are the *dimension* parameters, and `colour` is the *colour* of the text.  
    p) `float radius = ((l+b+h)/6) + x +1`. Our *initial distance* of camera from the canvas is *1 unit* away, the distance of the *canvas* from the surfaces is *x units*, and since it can be either a *cube/cuboid*, we take the *mean* of *l,b* and *h*, and then divide it by 2, since our *reference point* is the *middle* of the object.
    q) `yaw` refers to the angle around the *height axis*, which is in this case the *z axis*, which can be changed using `camera.up = {0,0,1}`, which means Z is the one which is up. 
    r) `pitch` refers to the *vertical angle (up or down)*.
    s) `GetMouseDelta()` refers to getting the information from the mouse. It is type *Vector2* and has 2 bits of information, one for *horizontal traversal*, one for *vertical traversal*. `vector2.x` refers to the *x axis* and `vector2.y` refers to the *y axis*.
    t) `Mesh meshname`is the function for generating a *mesh*, and `meshname` is the variable. The format for input is GenMeshCube
    
