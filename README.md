Cube or other objects to vertex should mix as one and one Material.
<br>if you used more than one Material you can cut the Cube or other objects to part.
<br>So you will need to use this engine to read all files.

if you get some problem on reading
<br>try don't name with " " for any object.

Mesh need to have same name with object.

Bones will be correct checked if it contain name don't make it less or <br>more but should as same size.
<br>Ex  if your bone name like

    "Head" and other bone name with "Head.1"

    change it to "Head.0" and "Head.1"

The object you need to export need to add all Used Bones to Vertex Groups for fix bones reader.

Armature should name as Armature or change it to defualt name of blender.

Your blender must be newer or version 3+

Joints|Bone / AnimationBone sequence are following sequence in Vertex Groups.

Try apply location if your model got wrong coord on rendering.

When export Collada you will need to set export all keyframe all bones for OpenGL.

This engine can have bug, won't read or calculate many of it come from the data from Collada file so you will need to check file and debug data runtime when have the problem.

Test Skinning On GPU / RTX3050

if you have lower or higher you can set it more or less of your part for memory used.

compress data can make it render more performance but keep on low data working.