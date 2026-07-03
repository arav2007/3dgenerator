#kennametal_project 
So far our viewer only shows the cube from the **6 fixed planes**. To look at it from *any* angle, we need to **rotate** the object. Rotation (and moving, and scaling) are all done with **transformation matrices**.

## Why matrices?

A point in 3D is $(x,y,z)$. A transformation is a rule that takes that point and gives us a *new* point. A **matrix** is just that rule written as a grid of numbers. To apply it, we **multiply** the matrix by the point.

The key idea (from Axler): a matrix's **columns are just where the basis vectors land**. Ask "where does $(1,0,0)$ go? where does $(0,1,0)$ go? where does $(0,0,1)$ go?" — stack those answers as columns, and that *is* your matrix.

## The homogeneous trick (the 4th coordinate)

We write points as $(x,y,z,1)$ — a 4th number, always 1. This lets a single $4\times4$ matrix do **everything** (rotate, scale, AND move) in one multiply. A plain $3\times3$ matrix cannot *translate* (move) a point; the extra coordinate fixes that. This is called **homogeneous coordinates**.

## Translation (moving) matrix

This is the one already in our code (`translation[4][4]`). To move a point by $(a,b,c)$:

$$
T = \begin{bmatrix} 1 & 0 & 0 & a \\ 0 & 1 & 0 & b \\ 0 & 0 & 1 & c \\ 0 & 0 & 0 & 1 \end{bmatrix}
$$

Multiplying $T$ by $(x,y,z,1)$ gives $(x+a,\; y+b,\; z+c,\; 1)$.

## Scaling (resizing) matrix

To stretch by $(s_x, s_y, s_z)$:

$$
S = \begin{bmatrix} s_x & 0 & 0 & 0 \\ 0 & s_y & 0 & 0 \\ 0 & 0 & s_z & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}
$$

## Rotation matrices (the new part)

Rotation is a transformation that **preserves length and angle** (in Axler terms, an *orthogonal operator*). In 2D, that requirement forces the whole matrix: rotate the axis $(1,0)$ by angle $\theta$ → it lands at $(\cos\theta, \sin\theta)$; rotate $(0,1)$ → it lands at $(-\sin\theta, \cos\theta)$. Those landing spots become the columns:

$$
R(\theta) = \begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix}
$$

In 3D we rotate **around an axis** — that axis stays fixed, the other two spin.

**Rotation about X** (x fixed, y & z spin):

$$
R_x = \begin{bmatrix} 1 & 0 & 0 \\ 0 & \cos\theta & -\sin\theta \\ 0 & \sin\theta & \cos\theta \end{bmatrix}
$$

**Rotation about Y** (y fixed, x & z spin):

$$
R_y = \begin{bmatrix} \cos\theta & 0 & \sin\theta \\ 0 & 1 & 0 \\ -\sin\theta & 0 & \cos\theta \end{bmatrix}
$$

**Rotation about Z** (z fixed, x & y spin):

$$
R_z = \begin{bmatrix} \cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix}
$$

**This is why trigonometry is everywhere in 3D — sine and cosine are what spin things.**

## Rotating at any angle = chaining the three

Any orientation is built by composing the three simple rotations:

$$
R_{total} = R_z \cdot R_y \cdot R_x
$$

Apply $R_x$ first, then $R_y$, then $R_z$. **Order matters** — matrix multiplication is not commutative ($AB \neq BA$).

> One trap: rotate **around the object's center**, not the origin. If the cube's corner is at the origin, rotating spins it around that corner instead of in place. So we **subtract the center → rotate → add the center back**. (Our corners run 0..l, 0..b, 0..h, so the center is $(l/2, b/2, h/2)$.)

## The code 

Each rotation matrix, written as a function that takes a point and returns where it lands:

```cpp
// Rotation about X — x stays, y & z spin
void rotateX(float p[3], float a, float out[3]) {
    float c = cosf(a), s = sinf(a);
    out[0] = p[0];
    out[1] = p[1]*c - p[2]*s;
    out[2] = p[1]*s + p[2]*c;
}

// Rotation about Y — y stays, x & z spin
void rotateY(float p[3], float a, float out[3]) {
    float c = cosf(a), s = sinf(a);
    out[0] =  p[0]*c + p[2]*s;
    out[1] =  p[1];
    out[2] = -p[0]*s + p[2]*c;
}

// Rotation about Z — z stays, x & y spin
void rotateZ(float p[3], float a, float out[3]) {
    float c = cosf(a), s = sinf(a);
    out[0] = p[0]*c - p[1]*s;
    out[1] = p[0]*s + p[1]*c;
    out[2] = p[2];
}
```

Chaining them (rotate each corner about the cube's center):

```cpp
for (int i = 0; i < 8; i++) {
    // 1. shift so the cube center is at the origin
    float p[3] = { corners[i][0]-cx, corners[i][1]-cy, corners[i][2]-cz };
    float t1[3], t2[3], t3[3];
    // 2. apply R_x, then R_y, then R_z
    rotateX(p,  angleX, t1);
    rotateY(t1, angleY, t2);
    rotateZ(t2, angleZ, t3);
    // 3. shift back to world position
    rotated[i] = { t3[0]+cx, t3[1]+cy, t3[2]+cz };
}
```

## How this connects to the rest of the viewer

- The **corners** and **6 planes** come from [[3d engine;]].
- Rotation lets us leave the 6 fixed planes and view from **any** angle.
- After rotating, the points are projected to the screen — either by the compression formula $y = \text{edge}/(x+1)$ from [[3d engine;]], or (in the raylib version) by the GPU's perspective camera.
- Full pipeline: **define corners → rotate (matrices) → project (compression / camera) → draw.**
- [[Raylib;]]for understanding the 3d rendering library.


