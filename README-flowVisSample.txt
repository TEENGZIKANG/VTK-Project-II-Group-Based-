#Appropriate scale proposed

1. HedgeHog-based

A. testData1.vtk
- appropriate : scale 5

B. testData2.vtk
- appropriate : scale 3

C. carotid.vtk
- appropriate : scale 3

2.Glyph-based

A.testData1.vtk
- appropriate : scale 5

B.testData1.vtk
- appropriate : scale 3
- radius = 0.2

C.testData1.vtk
- appropriate : scale 3
- radius = 0.2

#The hedhehogscaling factors is not feasible as the user need to redefine the scaling factor each time for loading different vtk model. Another issue about hedgehog visualization method is lack of efficiency in displaying the flow data (Vector data), compared to glyph-based method. 