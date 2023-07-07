package com.spacecat.bones.system.file;

import com.spacecat.bones.Main;
import java.io.File;
import java.io.IOException;

public class FileWriter
{
    public static int writeBones(String path_string)
    {
        java.io.FileWriter filewriter = null;

        try
        {
            int offset = 0;
            File file = null;

            do
            {
                file = new File(path_string + '/' + offset);
                ++offset;
            }
            while (file.exists());

            filewriter = new java.io.FileWriter(file);

            int[] max_bones = new int[Main.max_bones];

            int l = 0;
            for (int i = 0; i < Main.bones_xint_arraylist.size(); ++i)
            {
                l += Main.bones_xint_arraylist.get(i).length;
                max_bones[i] = l;
            }

            for (int i = 0; i < Main.joints_integer_arraylist.size(); ++i)
            {
                if (Main.joints_integer_arraylist.get(i) != -1)
                {
                    filewriter.write("" + max_bones[Main.joints_integer_arraylist.get(i)]);
                }
                else
                {
                    filewriter.write("-1");
                }

                if (i < (Main.joints_integer_arraylist.size() - 1))
                {
                    filewriter.write(' ');
                }
            }

            filewriter.write("\n");

            for (int i = 0; i < Main.joints_integer_arraylist.size(); ++i)
            {
                if (Main.joints_integer_arraylist.get(i) != -1)
                {
                    filewriter.write("" + (max_bones[Main.joints_integer_arraylist.get(i)] - Main.bones_xint_arraylist.get(Main.joints_integer_arraylist.get(i)).length));
                }
                else
                {
                    filewriter.write("-1");
                }

                if (i < (Main.joints_integer_arraylist.size() - 1))
                {
                    filewriter.write(' ');
                }
            }

            filewriter.write("\n");

            return offset - 1;
        }
        catch (IOException ioexception)
        {
            ioexception.printStackTrace();
        }
        finally
        {
            try
            {
                filewriter.close();
            }
            catch (IOException ioexception)
            {
                ioexception.printStackTrace();
            }
        }

        return -1;
    }
}
