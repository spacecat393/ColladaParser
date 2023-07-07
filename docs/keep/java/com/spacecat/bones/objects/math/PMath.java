package com.spacecat.bones.objects.math;

public class PMath
{
    public static double TIME = 0.6662F;

    public static Quaternion makeQuaternion(double x, double y, double z)
    {
        //pi / 180 = 0.01745329251
        double f = x * 0.017453292F;
        double f1 = y * 0.017453292F;
        double f2 = z * 0.017453292F;
        double f3 = Math.sin(0.5F * f);
        double f4 = Math.cos(0.5F * f);
        double f5 = Math.sin(0.5F * f1);
        double f6 = Math.cos(0.5F * f1);
        double f7 = Math.sin(0.5F * f2);
        double f8 = Math.cos(0.5F * f2);
        return new Quaternion(f3 * f6 * f8 + f4 * f5 * f7, f4 * f5 * f8 - f3 * f6 * f7, f3 * f5 * f8 + f4 * f6 * f7, f4 * f6 * f8 - f3 * f5 * f7);
    }

    public static M4x4 makeM4x4(Quaternion quaternion)
    {
        final double xy = quaternion.x * quaternion.y;
		final double xz = quaternion.x * quaternion.z;
		final double xw = quaternion.x * quaternion.w;
		final double yz = quaternion.y * quaternion.z;
		final double yw = quaternion.y * quaternion.w;
		final double zw = quaternion.z * quaternion.w;
		final double x_squared = quaternion.x * quaternion.x;
		final double y_squared = quaternion.y * quaternion.y;
		final double z_squared = quaternion.z * quaternion.z;

        M4x4 m4x4 = new M4x4();
		m4x4.mat[0][0] = (float)(1 - 2 * (y_squared + z_squared));
		m4x4.mat[0][1] = (float)(2 * (xy - zw));
		m4x4.mat[0][2] = (float)(2 * (xz + yw));
		//m4x4.mat[0][3] = 0;
		m4x4.mat[1][0] = (float)(2 * (xy + zw));
		m4x4.mat[1][1] = (float)(1 - 2 * (x_squared + z_squared));
		m4x4.mat[1][2] = (float)(2 * (yz - xw));
		//m4x4.mat[1][3] = 0;
		m4x4.mat[2][0] = (float)(2 * (xz - yw));
		m4x4.mat[2][1] = (float)(2 * (yz + xw));
		m4x4.mat[2][2] = (float)(1 - 2 * (x_squared + y_squared));
		//m4x4.mat[2][3] = 0;
		//m4x4.mat[3][0] = 0;
		//m4x4.mat[3][1] = 0;
		//m4x4.mat[3][2] = 0;
		//m4x4.mat[3][3] = 1;

        return m4x4;
    }

    // public static float radian(float degree)
    // {
    //     return degree * 3.14159265359F / 180.0F;
    // }

    // public static float degree(float radian)
    // {
    //     return radian * 180.0F / 3.14159265359F;
    // }

    public static float interpolate(float value, float max, float min)
    {
        return (max - min) * value + min;
        //min * (1 - value) + max * value
        //(max * value) + ((1 - value) * min)
    }

    public static float linear_interpolate(float value, float max0, float min0, float max1, float min1)
    {
        return (max0 - value) / (max0 - min0) * min1 + (min0 - value) / (min0 - max0) * max1;
    }
}
