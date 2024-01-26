xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 36;
 -0.91272;-7.57326;1.07296;,
 -0.19046;-7.57328;1.40128;,
 -0.19046;4.83198;1.40128;,
 -0.91272;4.83200;1.07296;,
 0.53180;-7.57328;1.07296;,
 0.53180;4.83198;1.07296;,
 0.83096;-7.57326;0.28032;,
 0.83096;4.83198;0.28032;,
 0.53180;-7.57328;-0.51232;,
 0.53180;4.83200;-0.51232;,
 -0.19046;-7.57326;-0.84066;,
 -0.19046;4.83196;-0.84066;,
 -0.91272;-7.57326;-0.51232;,
 -0.91272;4.83198;-0.51232;,
 -1.21188;-7.57326;0.28032;,
 -1.21188;4.83198;0.28032;,
 -0.91272;-7.57326;1.07296;,
 -0.91272;4.83200;1.07296;,
 -0.19046;-7.57328;1.40128;,
 -0.91272;-7.57326;1.07296;,
 -0.19046;-7.57328;0.28032;,
 0.53180;-7.57328;1.07296;,
 0.83096;-7.57326;0.28032;,
 0.53180;-7.57328;-0.51232;,
 -0.19046;-7.57326;-0.84066;,
 -0.91272;-7.57326;-0.51232;,
 -1.21188;-7.57326;0.28032;,
 -0.91272;4.83200;1.07296;,
 -0.19046;4.83198;1.40128;,
 -0.19046;4.83198;0.28032;,
 0.53180;4.83198;1.07296;,
 0.83096;4.83198;0.28032;,
 0.53180;4.83200;-0.51232;,
 -0.19046;4.83196;-0.84066;,
 -0.91272;4.83198;-0.51232;,
 -1.21188;4.83198;0.28032;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,18,20;,
 3;22,21,20;,
 3;23,22,20;,
 3;24,23,20;,
 3;25,24,20;,
 3;26,25,20;,
 3;19,26,20;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;31,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;34,35,29;,
 3;35,27,29;;
 
 MeshMaterialList {
  5;
  24;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.288000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.672000;0.264000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288000;0.272000;0.304000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  -0.729969;0.000000;0.683480;,
  -0.000000;0.000000;1.000000;,
  0.729969;0.000000;0.683480;,
  1.000000;0.000000;0.000000;,
  0.729977;0.000000;-0.683472;,
  -0.000000;0.000000;-1.000000;,
  -0.729977;0.000000;-0.683472;,
  -1.000000;0.000000;0.000000;,
  -0.000007;-1.000000;-0.000004;,
  0.000000;1.000000;-0.000004;,
  -0.000014;-1.000000;0.000000;,
  -0.000023;-1.000000;0.000004;,
  0.000010;-1.000000;-0.000009;,
  0.000019;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000014;-1.000000;-0.000018;,
  -0.000014;-1.000000;-0.000013;,
  -0.000019;-1.000000;0.000000;,
  0.000014;1.000000;-0.000013;,
  0.000014;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000013;,
  -0.000024;1.000000;0.000004;,
  -0.000014;1.000000;-0.000018;,
  0.000010;1.000000;-0.000009;,
  0.000000;1.000000;-0.000013;;
  24;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
  3;10,11,8;,
  3;12,10,8;,
  3;13,12,8;,
  3;14,13,8;,
  3;15,14,8;,
  3;16,15,8;,
  3;17,16,8;,
  3;11,17,8;,
  3;18,19,9;,
  3;19,20,9;,
  3;20,21,9;,
  3;21,22,9;,
  3;22,23,9;,
  3;23,24,9;,
  3;24,25,9;,
  3;25,18,9;;
 }
 MeshTextureCoords {
  36;
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.687500;,
  0.437500;0.311560;,
  0.468750;0.687500;,
  0.468750;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.531250;0.687500;,
  0.531250;0.311560;,
  0.562500;0.687500;,
  0.562500;0.311560;,
  0.593750;0.687500;,
  0.593750;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610485;0.954235;,
  0.500000;0.850000;,
  0.389515;0.954235;,
  0.343750;0.843750;,
  0.389515;0.733265;,
  0.500000;0.687500;,
  0.610485;0.733265;,
  0.656250;0.843750;,
  0.610485;0.045765;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.500000;0.312500;,
  0.610485;0.266735;,
  0.656250;0.156250;;
 }
}
