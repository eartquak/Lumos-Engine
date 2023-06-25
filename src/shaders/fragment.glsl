#version 400 core

in vec3 fragmentColor;

out vec4 screenColor;

void main() {
    screenColor = vec4(floor(fragmentColor*10)/10, 1);
}

// #ifdef GL_ES
// precision mediump float;
// #endif

// #extension GL_OES_standard_derivatives : enable

// uniform float time;
// uniform vec2 resolution;

// in vec3 fragmentColor;

// out vec4 screenColor;

// void main( void )
// {
//  vec2 uv = ( gl_FragCoord.xy / resolution.xy );
//  float x=uv.x,y=uv.y;
//  x+=sin(fract(time*0.55)*6.28)*0.05;
//  y+=cos(fract(x*0.9+time*0.55)*6.28)*0.075;
//  bool w = mod(time,1.0)>0.5;
//  if(x>.2&&x<.7&&y<.8&&y>.2) w =! w;
//  if(x>.24&&x<.66&&y<.8&&y>.2) w =! w;
//  if(x>.4&&x<.6&&y<.8&&y>.2) w =! w;
//  if(x>.45&&x<.55&&y<.7&&y>.3) w =! w;
//  if(x>.24&&x<.85&&y<.3&&y>.2) w =! w;
//  if(x>.35&&x<.7&&y<.3&&y>.2) w =! w;
//  screenColor=vec4(w?0.0:1.0);

// }