package com.spacecat.bones.objects.math;

public class V3
{
    public float x, y, z;

    public V3(float x, float y, float z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public void multiply(float x, float y, float z)
    {
        this.x *= x;
        this.y *= y;
        this.z *= z;
    }

    public void multiply(float v)
    {
        this.x *= v;
        this.y *= v;
        this.z *= v;
    }

    public void add(V3 v3)
    {
        this.x += v3.x;
        this.y += v3.y;
        this.z += v3.z;
    }
}
