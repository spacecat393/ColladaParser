package com.spacecat.bones.system.file;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

import com.spacecat.bones.objects.math.M4x4;

public class FileReader
{
    // public static byte[] readString(String path_string)
    // {
    //     try
    //     {
    //         File file = new File(path_string);

    //         if (file.exists())
    //         {
    //             return Files.readAllBytes(Paths.get(path_string));
    //         }
    //     }
    //     catch (IOException ioexception)
    //     {
    //         ioexception.printStackTrace();
    //     }

    //     return null;
    // }

    // public static int getListLength(String path_string)
    // {
    //     File directory = new File(path_string);
    //     return directory.list().length;
    // }

    public static void getXFloatArrayList(String path_string, ArrayList<float[]> xfloat_arraylist, int max_size)
    {
        try
        {
            ArrayList<Float> float_arraylist = new ArrayList<Float>();
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            byte state = 1;

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    float_arraylist.add(Float.parseFloat(number_string));
                    number_string = "";

                    if (state == max_size)
                    {
                        float[] float_array = new float[max_size];

                        for (int l = 0; l < float_array.length; ++l)
                        {
                            float_array[l] = float_arraylist.get(l);
                        }
    
                        float_arraylist.clear();
    
                        xfloat_arraylist.add(float_array);

                        state = 1;
                    }
                    else
                    {
                        ++state;
                    }
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            float_arraylist.add(Float.parseFloat(number_string));

            float[] float_array = new float[max_size];

            for (int l = 0; l < float_array.length; ++l)
            {
                float_array[l] = float_arraylist.get(l);
            }
    
            xfloat_arraylist.add(float_array);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getXIntArrayList(String path_string, ArrayList<int[]> xint_arraylist, int max_size)
    {
        try
        {
            ArrayList<Integer> int_arraylist = new ArrayList<Integer>();
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            byte state = 1;

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    int_arraylist.add(Integer.parseInt(number_string));
                    number_string = "";

                    if (state == max_size)
                    {
                        int[] int_array = new int[max_size];

                        for (int l = 0; l < int_array.length; ++l)
                        {
                            int_array[l] = int_arraylist.get(l);
                        }
    
                        int_arraylist.clear();
    
                        xint_arraylist.add(int_array);

                        state = 1;
                    }
                    else
                    {
                        ++state;
                    }
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            int_arraylist.add(Integer.parseInt(number_string));

            int[] int_array = new int[max_size];

            for (int l = 0; l < int_array.length; ++l)
            {
                int_array[l] = int_arraylist.get(l);
            }
    
            xint_arraylist.add(int_array);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getXM4x4ArrayList(String path_string, ArrayList<M4x4[]> xm4x4_arraylist, int max_size)
    {
        try
        {
            int max_matrix_size = 16;
            int matrix_dimension_size = 4;

            ArrayList<Float> float_arraylist = new ArrayList<Float>();
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            int state = 1;

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    float_arraylist.add(Float.parseFloat(number_string));
                    number_string = "";

                    if (state == max_matrix_size * max_size)
                    {
                        M4x4[] m4x4_arraylist = new M4x4[max_size];
                        int l = 0;

                        for (int z = 0; z < max_size; ++z)
                        {
                            M4x4 m4x4 = new M4x4();

                            for (int x = 0; x < matrix_dimension_size; ++x)
                            {
                                for (int y = 0; y < matrix_dimension_size; ++y)
                                {
                                    m4x4.mat[x][y] = float_arraylist.get(x + l + y);
                                }
    
                                l += 3;
                            }

                            l += 4;

                            m4x4_arraylist[z] = m4x4;
                        }

                        float_arraylist.clear();
    
                        xm4x4_arraylist.add(m4x4_arraylist);

                        state = 1;
                    }
                    else
                    {
                        ++state;
                    }
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            float_arraylist.add(Float.parseFloat(number_string));

            M4x4[] m4x4_arraylist = new M4x4[max_size];
            int l = 0;

            for (int z = 0; z < max_size; ++z)
            {
                M4x4 m4x4 = new M4x4();

                for (int x = 0; x < matrix_dimension_size; ++x)
                {
                    for (int y = 0; y < matrix_dimension_size; ++y)
                    {
                        m4x4.mat[x][y] = float_arraylist.get(x + l + y);
                    }

                    l += 3;
                }

                l += 4;

                m4x4_arraylist[z] = m4x4;
            }

            xm4x4_arraylist.add(m4x4_arraylist);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getM4x4ArrayList(String path_string, ArrayList<M4x4> m4x4_arraylist)
    {
        try
        {
            int max_matrix_size = 16;
            int matrix_dimension_size = 4;

            ArrayList<Float> float_arraylist = new ArrayList<Float>();
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            byte state = 1;

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    float_arraylist.add(Float.parseFloat(number_string));
                    number_string = "";

                    if (state == max_matrix_size)
                    {
                        M4x4 m4x4 = new M4x4();
                        int l = 0;

                        for (int x = 0; x < matrix_dimension_size; ++x)
                        {
                            for (int y = 0; y < matrix_dimension_size; ++y)
                            {
                                m4x4.mat[x][y] = float_arraylist.get(x + l + y);
                            }

                            l += 3;
                        }
    
                        float_arraylist.clear();
    
                        m4x4_arraylist.add(m4x4);

                        state = 1;
                    }
                    else
                    {
                        ++state;
                    }
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            float_arraylist.add(Float.parseFloat(number_string));

            M4x4 m4x4 = new M4x4();
            int l = 0;

            for (int x = 0; x < matrix_dimension_size; ++x)
            {
                for (int y = 0; y < matrix_dimension_size; ++y)
                {
                    m4x4.mat[x][y] = float_arraylist.get(x + l + y);
                }

                l += 3;
            }
    
            m4x4_arraylist.add(m4x4);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getMixXIntArrayList(String path_string, ArrayList<int[]> xint_arraylist)
    {
        try
        {
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            ArrayList<Integer> integer_arraylist = new ArrayList<Integer>();

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    integer_arraylist.add(Integer.parseInt(number_string));
                    number_string = "";
                }
                else if (data_string.charAt(i) == '\n')
                {
                    integer_arraylist.add(Integer.parseInt(number_string));
                    number_string = "";

                    int[] int_array = new int[integer_arraylist.size()];

                    for (int l = 0; l < int_array.length; ++l)
                    {
                        int_array[l] = integer_arraylist.get(l);
                    }

                    integer_arraylist.clear();

                    xint_arraylist.add(int_array);
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            integer_arraylist.add(Integer.parseInt(number_string));

            int[] int_array = new int[integer_arraylist.size()];

            for (int l = 0; l < int_array.length; ++l)
            {
                int_array[l] = integer_arraylist.get(l);
            }

            xint_arraylist.add(int_array);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getIntArrayList(String path_string, char end_char, ArrayList<Integer> integer_arraylist)
    {
        try
        {
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == end_char)
                {
                    integer_arraylist.add(Integer.parseInt(number_string));
                    number_string = "";
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            integer_arraylist.add(Integer.parseInt(number_string));
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public static void getMixXStringArrayList(String path_string, ArrayList<String[]> xstring_arraylist)
    {
        try
        {
            String data_string = new String(Files.readAllBytes(Paths.get(path_string)));
            String number_string = "";
            ArrayList<String> string_arraylist = new ArrayList<String>();

            for (int i = 0; i < data_string.length(); ++i)
            {
                if (data_string.charAt(i) == ' ')
                {
                    string_arraylist.add(number_string);
                    number_string = "";
                }
                else if (data_string.charAt(i) == '\n')
                {
                    string_arraylist.add(number_string);
                    number_string = "";

                    String[] string_array = new String[string_arraylist.size()];

                    for (int l = 0; l < string_array.length; ++l)
                    {
                        string_array[l] = string_arraylist.get(l);
                    }

                    string_arraylist.clear();

                    xstring_arraylist.add(string_array);
                }
                else
                {
                    number_string += data_string.charAt(i);
                }
            }

            string_arraylist.add(number_string);

            String[] string_array = new String[string_arraylist.size()];

            for (int l = 0; l < string_array.length; ++l)
            {
                string_array[l] = string_arraylist.get(l);
            }

            xstring_arraylist.add(string_array);
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }
}
