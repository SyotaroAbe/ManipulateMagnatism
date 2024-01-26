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
 47;
 -1.78904;-8.81914;3.41896;,
 1.14292;-8.78260;3.42152;,
 2.24192;-6.79524;5.43724;,
 -2.83634;-6.85852;5.43282;,
 2.60686;-8.73438;0.63596;,
 4.77756;-6.71170;0.61252;,
 1.13888;-8.72268;-2.15216;,
 2.23494;-6.69144;-4.21666;,
 -1.79308;-8.75922;-2.15472;,
 -2.84334;-6.75474;-4.22108;,
 -3.25702;-8.80744;0.63084;,
 -5.37898;-6.83828;0.60364;,
 -1.78904;-8.81914;3.41896;,
 -2.83634;-6.85852;5.43282;,
 2.69704;-1.74094;6.12014;,
 -3.16686;-1.81400;6.11502;,
 5.62494;-1.64446;0.54902;,
 2.68896;-1.62108;-5.02722;,
 -3.17494;-1.69416;-5.03234;,
 -6.10284;-1.79062;0.53878;,
 -3.16686;-1.81400;6.11502;,
 2.35128;2.15950;5.32362;,
 -2.72700;2.09622;5.31918;,
 4.88692;2.24304;0.49888;,
 2.27066;2.34600;-4.03586;,
 -2.80762;2.28272;-4.04028;,
 -5.26964;2.11646;0.49002;,
 -2.72700;2.09622;5.31918;,
 1.30100;4.16398;3.25724;,
 -1.63094;4.12746;3.25468;,
 2.76496;4.21222;0.47168;,
 1.29696;4.22390;-2.31644;,
 -1.63498;4.18738;-2.31900;,
 -3.09894;4.13914;0.46656;,
 -1.63094;4.12746;3.25468;,
 -0.33084;-9.24236;0.63938;,
 -0.33084;-9.24236;0.63938;,
 -0.33084;-9.24236;0.63938;,
 -0.33084;-9.24236;0.63938;,
 -0.33084;-9.24236;0.63938;,
 -0.33084;-9.24236;0.63938;,
 -0.16124;4.64712;0.46314;,
 -0.16124;4.64712;0.46314;,
 -0.16124;4.64712;0.46314;,
 -0.16124;4.64712;0.46314;,
 -0.16124;4.64712;0.46314;,
 -0.16124;4.64712;0.46314;;
 
 36;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 3;1,0,35;,
 3;4,1,36;,
 3;6,4,37;,
 3;8,6,38;,
 3;10,8,39;,
 3;12,10,40;,
 3;29,28,41;,
 3;28,30,42;,
 3;30,31,43;,
 3;31,32,44;,
 3;32,33,45;,
 3;33,34,46;;
 
 MeshMaterialList {
  5;
  36;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  38;
  -0.208679;-0.915793;0.343185;,
  0.226299;-0.912827;0.339906;,
  0.437089;-0.899375;-0.008864;,
  0.223936;-0.908563;-0.352655;,
  -0.205371;-0.911852;-0.355456;,
  -0.424800;-0.905248;-0.008393;,
  -0.451466;-0.494464;0.742754;,
  0.455839;-0.499353;0.736789;,
  0.875952;-0.482381;-0.004103;,
  0.450871;-0.506851;-0.734723;,
  -0.445259;-0.503139;-0.740673;,
  -0.880925;-0.473245;-0.003259;,
  -0.001288;0.033385;0.999442;,
  0.999847;0.016974;-0.004299;,
  0.880524;0.014633;-0.473775;,
  0.000336;0.042931;-0.999078;,
  -0.999355;0.035916;-0.000614;,
  -0.245190;0.603485;0.758741;,
  0.234387;0.603915;0.761806;,
  0.868642;0.495421;-0.004248;,
  0.565986;0.577467;-0.588381;,
  -0.244951;0.600479;-0.761199;,
  -0.864325;0.502922;0.003407;,
  -0.223933;0.908565;0.352652;,
  0.205370;0.911852;0.355457;,
  0.426788;0.904338;0.005032;,
  0.211538;0.908637;-0.360043;,
  -0.227383;0.907755;-0.352530;,
  -0.436787;0.899518;0.009215;,
  0.012056;-0.999873;-0.010432;,
  -0.012057;0.999873;0.010432;,
  0.884984;0.015340;0.465369;,
  -0.883796;0.027698;-0.467052;,
  -0.884215;0.035840;0.465704;,
  0.870893;0.171275;0.460663;,
  -0.002173;0.242226;-0.970217;,
  -0.868537;0.186343;-0.459261;,
  -0.868247;0.190873;0.457947;;
  36;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,0,6,11;,
  4;6,7,12,12;,
  4;7,8,13,31;,
  4;8,9,14,13;,
  4;9,10,15,15;,
  4;10,11,16,32;,
  4;11,6,33,16;,
  4;12,12,18,17;,
  4;31,13,19,34;,
  4;13,14,20,19;,
  4;15,15,21,35;,
  4;32,16,22,36;,
  4;16,33,37,22;,
  4;17,18,24,23;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,17,23,28;,
  3;1,0,29;,
  3;2,1,29;,
  3;3,2,29;,
  3;4,3,29;,
  3;5,4,29;,
  3;0,5,29;,
  3;23,24,30;,
  3;24,25,30;,
  3;25,26,30;,
  3;26,27,30;,
  3;27,28,30;,
  3;28,23,30;;
 }
 MeshTextureCoords {
  47;
  0.000000;0.833333;,
  0.166667;0.833333;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.833333;,
  0.333333;0.666667;,
  0.500000;0.833333;,
  0.500000;0.666667;,
  0.666667;0.833333;,
  0.666667;0.666667;,
  0.833333;0.833333;,
  0.833333;0.666667;,
  1.000000;0.833333;,
  1.000000;0.666667;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.500000;0.333333;,
  0.666667;0.333333;,
  0.833333;0.333333;,
  1.000000;0.333333;,
  0.166667;0.166667;,
  0.000000;0.166667;,
  0.333333;0.166667;,
  0.500000;0.166667;,
  0.666667;0.166667;,
  0.833333;0.166667;,
  1.000000;0.166667;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;;
 }
}
