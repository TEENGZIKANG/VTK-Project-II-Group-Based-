By
Abraham Loh Tze Lung (A20EC0001)
Goh Chai Seng (B20EC3004)
Tee Ng Zikang (A20EC0161)
Zhao Xin (A20EC4053)


This note summarizes the steps taken to run the VTK programs, namely isosurface.cpp and raymarching.cpp given by lecturer.

Step 1: create a folder on desktop and name it "isosurface" or anything of your preference.

Step 2: Open the newly created folder and create another empty sub-folder "build".

Step 3: Move the isosurface.cpp downloaded from elearning to "isosurface" folder and rename it to isosurface.cxx.

Step 4: Copy cmakelist.txt from the last tutorial (FullHead) to "isosurface" folder

Step 5: Open cmakelist.txt and replace every "MedicalDemo3" to "isosurface" (same name as source file name).

Step 6: Open Cmake and set the right file path as follow:

Where is the source code: C:/Users/.../Desktop/isosurface
Where to build the binary: C:/Users/.../Desktop/isosurface/build

Step 7: Configure, generate and run.

Step 8: Open cmakelist.txt again and replace the segment of codes to as follow:

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
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
)

Step 9: Build the project

Step 10: run it in cmd as follow: C:/Users/.../Desktop/isosurface/build/debug/isosurface.exe