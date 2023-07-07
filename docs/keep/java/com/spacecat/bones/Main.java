package com.spacecat.bones;

import com.spacecat.bones.system.file.FileReader;
import com.spacecat.bones.system.file.FileWriter;
import java.util.ArrayList;

public class Main
{
    public static ArrayList<int[]> bones_xint_arraylist = new ArrayList<int[]>();
    public static ArrayList<Integer> joints_integer_arraylist = new ArrayList<Integer>();
    public static int max_bones = 57;

    public static void main(String[] args)
    {
        FileReader.getIntArrayList("Objects/Joints", ' ', joints_integer_arraylist);
        FileReader.getMixXIntArrayList("Objects/Bones", bones_xint_arraylist);
        FileWriter.writeBones("Results");
    }
}
