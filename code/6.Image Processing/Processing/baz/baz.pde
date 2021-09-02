void setup () {
  size(500,500);
  background(255);
  float x=250;
  float y=250;
  /*strokeWeight (10);
  point (x,y);
  point (x+70,y-80);
  point (x+45,y-120);
  point(x,y-80);*/
  fill(255,0,0);
  bezier(x,y,x+70,y-80,x+45,y-120,x,y-80);
  bezier(x,y,x-70,y-80,x-45,y-120,x,y-80);
}

void draw () {  
  
  
}