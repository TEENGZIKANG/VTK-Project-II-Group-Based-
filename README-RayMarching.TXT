By
Abraham Loh Tze Lung (A20EC0001)
Goh Chai Seng (B20EC3004)
Tee Ng Zikang (A20EC0161)
Zhao Xin (A20EC4053)


This note summarizes the steps taken to run the VTK programs, namely isosurface.cpp and raymarching.cpp given by lecturer.

Step 1: create a folder on desktop and name it "raymarching" or anything of your preference.

Step 2: Open the newly created folder and create another empty sub-folder "build".

Step 3: Move the raymarching.cpp downloaded from elearning to "raymarching" folder and rename it to raymarching.cxx.

Step 4: Copy cmakelist.txt from the last tutorial (FullHead) to "raymarching" folder

Step 5: Open cmakelist.txt and replace every "MedicalDemo3" to "raymarching" (same name as source file name).

Step 6: Open Cmake and set the right file path as follow:

Where is the source code: C:/Users/.../Desktop/isosurface
Where to build the binary: C:/Users/.../Desktop/isosurface/build

Step 7: Configure, generate and run.

Step 8: Open cmakelist.txt again and replace the segment of codes to as follow:

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  CommonMath
  FiltersCore
  FiltersGeometry
  FiltersModeling
  IOImage
  IOLegacy
  ImagingCore
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingVolume
  RenderingVolumeOpenGL2
)

Step 9: Build the project

Step 10: run it in cmd as follow: C:/Users/.../Desktop/isosurface/build/debug/raymarching.exe


inside the source file, the code segment:

    reader->SetDataDimensions(256, 256);
    reader->SetImageRange(1, 256);
    reader->SetDataByteOrderToLittleEndian();
    reader->SetFilePrefix("../data/aneurism/aneurism");
    reader->SetDataSpacing(1, 1, 1);


*for SetDataDimensions, 64 will be used for head volume, the rest will be using (256,256).
*for SetImageRange, the second parameter will be depends on how many slice data exist.
*for SetFilePrefix, set the file path correctly according to file location and name.
*for SetDataSpacing, the parameters were provided in the project instruction.
*keypress event included, by press "=" to increase the sampling distance and "_" for decrease.