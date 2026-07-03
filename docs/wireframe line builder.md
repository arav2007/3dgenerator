#kennametal_project 
The wireframe line builder is the next step after the basic 3D viewer — instead of displaying a fixed object, the user **constructs** geometry themselves, line by line.

## Core Idea

A 3D line segment is defined by two points: a **starting point** and an **ending point**. The ending point of one line becomes the starting point of the next — this is how segments **chain** together into a connected path.

Each new endpoint is computed by adding the user's input distances to the current starting point:

	endingpoint.x = x + startingpoint.x
	endingpoint.y = y + startingpoint.y
	endingpoint.z = z + startingpoint.z

Where `x, y, z` are the distances the user enters (space separated). This works for **any direction** — axis-aligned (`1 0 0`) or diagonal (`1 1 1` or `2 -1 0.5`).

## The Vector — Storing All Points

The critical insight: **you can't just store one startingpoint and one endingpoint** — every new line overwrites the previous one. To draw *all* segments simultaneously, every point must be remembered.

This is done with a `std::vector<Vector3>`:

```cpp
vector<Vector3> points;
points.push_back(startingpoint);   // always start from origin
```

Every time a new line is committed, the endpoint gets added:

```cpp
points.push_back(endingpoint);
startingpoint = endingpoint;       // chain: end of this line = start of next
```

Then in the render loop, **all** lines are drawn by iterating through the vector:

```cpp
for (int i = 0; i + 1 < (int)points.size(); i++) {
    DrawLine3D(points[i], points[i+1], SKYBLUE);
}
```

`points[i]` to `points[i+1]` draws each segment in order. The dots at each joint:

```cpp
for (int i = 0; i < (int)points.size(); i++) {
    DrawSphere(points[i], 0.05f, YELLOW);
}
```

## The Structure (two phases)

**Phase 1 — terminal input loop:**
The user enters lines one by one. Each answer adds a point to the vector and advances the starting point. When done (input 0), the loop exits.

**Phase 2 — window opens once:**
`InitWindow` is called **after** the input loop, not inside it. The render loop draws everything from the `points` vector. The orbit camera (spherical coordinates — see [[transformation matrices;]]) lets the user view from any angle.

> Key rule: `InitWindow` and `CloseWindow` are called **once each**, outside all input loops. Opening a window inside a loop creates a new window every iteration — a common structural bug.

## Scope Trap (important)
Variables declared inside `{}` blocks only exist within those braces. A variable needed outside the loop (like the camera radius `b`) must be declared **before** the loop, not inside it:

```cpp
float b = 1;           // declared outside — lives for the whole function

while (lines) {
    if (lines) {
        b = sqrtf(x*x + y*y + z*z);   // updates the outer b (no float keyword)
    }
}

float radius = b;      // can see b because it was declared in the outer scope
```

## Arbitrary Angles
The builder accepts any `x y z` combination — the user is not restricted to axis-aligned lines. A line from `(0,0,0)` to `(1,2,3)` is equally valid as one to `(1,0,0)`. This is the foundation for the coplanar detection step — since points are no longer axis-aligned, the general scalar triple product test is needed to find coplanar groups.

**Real Time Version**:

In this one we use *keys* to draw lines along the *x, y and z axis*, and to *commit lines* and *backspace* them too if necessary.


		if (IsKeyDown(KEY_W)) {endingpoint.x+=stepsize; }
        if (IsKeyDown(KEY_S)) {endingpoint.x-=stepsize; }
        if (IsKeyDown(KEY_RIGHT)) {endingpoint.y+=stepsize; }
        if (IsKeyDown(KEY_LEFT)) {endingpoint.y-=stepsize; }
        if (IsKeyDown(KEY_UP)) {endingpoint.z+=stepsize; }
        if (IsKeyDown(KEY_DOWN)) {endingpoint.z-=stepsize; }
        
        if (IsKeyPressed(KEY_SPACE)) {points.push_back(endingpoint); startingpoint=endingpoint; i+=1;}
        if (IsKeyPressed(KEY_BACKSPACE) && points.size()>1) {points.pop_back(); startingpoint=points.back(); endingpoint=startingpoint;}




