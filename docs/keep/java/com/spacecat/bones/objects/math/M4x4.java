package com.spacecat.bones.objects.math;

public class M4x4
{
    public float[][] mat = new float[][]
    {
        { 1.0F, 0.0F, 0.0F, 0.0F },
        { 0.0F, 1.0F, 0.0F, 0.0F },
        { 0.0F, 0.0F, 1.0F, 0.0F },
        { 0.0F, 0.0F, 0.0F, 1.0F }
    };

    // public void identify()
    // {
    //     this.mat = new float[][]
    //     {
    //         { 1.0F, 0.0F, 0.0F, 0.0F },
    //         { 0.0F, 1.0F, 0.0F, 0.0F },
    //         { 0.0F, 0.0F, 1.0F, 0.0F },
    //         { 0.0F, 0.0F, 0.0F, 1.0F }
    //     };
    // }

    public void inverse()
    {
        int i, j, k;
        M4x4 s = new M4x4();
        M4x4 t = this;

        // Forward elimination
        for (i = 0; i < 3 ; i++)
        {
            int pivot = i;

            float pivotsize = t.mat[i][i];

            if (pivotsize < 0)
                pivotsize = -pivotsize;

            for (j = i + 1; j < 4; j++)
            {
                float tmp = t.mat[j][i];

                if (tmp < 0)
                    tmp = -tmp;

                if (tmp > pivotsize)
                {
                    pivot = j;
                    pivotsize = tmp;
                }
            }

            if (pivotsize == 0)
            {
                // Cannot invert singular matrix
                this.mat = new float[][]
                {
                    { 1.0F, 0.0F, 0.0F, 0.0F },
                    { 0.0F, 1.0F, 0.0F, 0.0F },
                    { 0.0F, 0.0F, 1.0F, 0.0F },
                    { 0.0F, 0.0F, 0.0F, 1.0F }
                };

                return;
            }

            if (pivot != i)
            {
                for (j = 0; j < 4; j++)
                {
                    float tmp;

                    tmp = t.mat[i][j];
                    t.mat[i][j] = t.mat[pivot][j];
                    t.mat[pivot][j] = tmp;

                    tmp = s.mat[i][j];
                    s.mat[i][j] = s.mat[pivot][j];
                    s.mat[pivot][j] = tmp;
                }
            }

            for (j = i + 1; j < 4; j++)
            {
                float f = t.mat[j][i] / t.mat[i][i];

                for (k = 0; k < 4; k++)
                {
                    t.mat[j][k] -= f * t.mat[i][k];
                    s.mat[j][k] -= f * s.mat[i][k];
                }
            }
        }

        // Backward substitution
        for (i = 3; i >= 0; --i)
        {
            float f;

            if ((f = t.mat[i][i]) == 0)
            {
                // Cannot invert singular matrix
                this.mat = new float[][]
                {
                    { 1.0F, 0.0F, 0.0F, 0.0F },
                    { 0.0F, 1.0F, 0.0F, 0.0F },
                    { 0.0F, 0.0F, 1.0F, 0.0F },
                    { 0.0F, 0.0F, 0.0F, 1.0F }
                };

                return;
            }

            for (j = 0; j < 4; j++)
            {
                t.mat[i][j] /= f;
                s.mat[i][j] /= f;
            }

            for (j = 0; j < i; j++)
            {
                f = t.mat[j][i];

                for (k = 0; k < 4; k++)
                {
                    t.mat[j][k] -= f * t.mat[i][k];
                    s.mat[j][k] -= f * s.mat[i][k];
                }
            }
        }

        this.mat = s.mat;
    }

    public void rotateX(float x)
    {
        this.mat[1][1] = (float)Math.cos(x);
        this.mat[1][2] = (float)Math.sin(x);
        this.mat[2][1] = (float)-Math.sin(x);
        this.mat[2][2] = (float)Math.cos(x);
    }

    public void rotateY(float y)
    {
        this.mat[0][0] = (float)Math.cos(y);
        this.mat[0][2] = (float)-Math.sin(y);
        this.mat[2][0] = (float)Math.sin(y);
        this.mat[2][2] = (float)Math.cos(y);
    }

    public void rotateZ(float z)
    {
        this.mat[0][0] = (float)Math.cos(z);
        this.mat[0][1] = (float)Math.sin(z);
        this.mat[1][0] = (float)-Math.sin(z);
        this.mat[1][1] = (float)Math.cos(z);
    }

    public void translate(float x, float y, float z)
    {
        this.mat[0][3] = x;
        this.mat[1][3] = y;
        this.mat[2][3] = z;
    }

    public void translatePlus(float x, float y, float z)
    {
        this.mat[0][3] += x;
        this.mat[1][3] += y;
        this.mat[2][3] += z;
    }

    public void scale(float x, float y, float z)
    {
        this.mat[0][0] *= x;
        this.mat[1][1] *= y;
        this.mat[2][2] *= z;
    }

    // public void transformPlusX(float x)
    // {
    //     this.mat[2][3] += x;
    // }

    // public void transformPlusY(float y)
    // {
    //     this.mat[2][3] += y;
    // }

    // public void transformPlusZ(float z)
    // {
    //     this.mat[2][3] += z;
    // }

    public void multiplyM4x4(V3 v3, float wv)
    {
        V3 v30 = new V3(0, 0, 0);

        v30.x = v3.x * this.mat[0][0] + v3.y * this.mat[0][1] + v3.z * this.mat[0][2] + wv * this.mat[0][3];
        v30.y = v3.x * this.mat[1][0] + v3.y * this.mat[1][1] + v3.z * this.mat[1][2] + wv * this.mat[1][3];
        v30.z = v3.x * this.mat[2][0] + v3.y * this.mat[2][1] + v3.z * this.mat[2][2] + wv * this.mat[2][3];

        // float w = v3.x * this.mat[3][0] + v3.y * this.mat[3][1] + v3.z * this.mat[3][2] + wv * this.mat[3][3];

        // if (w != 1)
        // {
        //     v30.x /= w;
        //     v30.y /= w;
        //     v30.z /= w;
        // }

        v3.x = v30.x;
        v3.y = v30.y;
        v3.z = v30.z;
    }

    // public V3 toV3()
    // {
    //     V3 v3 = new V3(0, 0, 0);

    //     v3.x = this.mat[0][0] + this.mat[0][1] + this.mat[0][2] + this.mat[0][3];
    //     v3.y = this.mat[1][0] + this.mat[1][1] + this.mat[1][2] + this.mat[1][3];
    //     v3.z = this.mat[2][0] + this.mat[2][1] + this.mat[2][2] + this.mat[2][3];

    //     return v3;
    // }

    // public void addM4x4(M4x4 m4x4)
    // {
    //     M4x4 m4x40 = new M4x4();

    //     for (int i = 0; i < 4; i++)
    //     {
    //         for (int j = 0; j < 4; j++)
    //         {
    //             m4x40.mat[i][j] = this.mat[i][j] + m4x4.mat[i][j];
    //         }
    //     }

    //     this.mat = m4x40.mat;
    // }


    // public void transpose()
    // {
    //     M4x4 m4x40 = new M4x4();

    //     for (int i = 0; i < 4; i++)
    //     {
    //         for (int j = 0; j < 4; j++)
    //         {
    //             m4x40.mat[i][j] = this.mat[j][i];
    //         }
    //     }

    //     this.mat = m4x40.mat;
    // }

    // public void multiple(float v)
    // {
    //     M4x4 m4x40 = new M4x4();

    //     for (int i = 0; i < 4; i++)
    //     {
    //         for (int j = 0; j < 4; j++)
    //         {
    //             m4x40.mat[i][j] *= v;
    //         }
    //     }

    //     this.mat = m4x40.mat;
    // }

    public void multiply(M4x4 m4x4)
    {
        M4x4 m4x40 = new M4x4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m4x40.mat[i][j] = this.mat[i][0] * m4x4.mat[0][j] + this.mat[i][1] * m4x4.mat[1][j] + this.mat[i][2] * m4x4.mat[2][j] + this.mat[i][3] * m4x4.mat[3][j];
            }
        }

        this.mat = m4x40.mat;
    }

    // public void add(M4x4 m4x4)
    // {
    //     M4x4 m4x40 = new M4x4();

    //     for (int i = 0; i < 4; i++)
    //     {
    //         for (int j = 0; j < 4; j++)
    //         {
    //             m4x40.mat[i][j] = this.mat[i][j] + m4x4.mat[i][j];
    //         }
    //     }

    //     this.mat = m4x40.mat;
    // }
}
