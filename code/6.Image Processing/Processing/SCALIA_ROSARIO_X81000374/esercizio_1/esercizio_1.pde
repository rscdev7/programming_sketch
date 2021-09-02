ArrayList<Heart> a;
int x=150;
int y=150;
float p=0.05;
void setup() {
  size(512,512);
  frameRate(60);
  background(0,0,255);
  a=new ArrayList<Heart>();
}

void draw() {
  fill(0,0,140,40);
  noStroke();
  rect(0,0,512,512);
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      a.get(i).run();  
    }
  }
  if (random(0,1)<p) {
    a.add(new Heart(random(0,512),505,random(-5,5),random(-3,-7)));
  }
}

void mousePressed () {
   for (int i=0;i<a.size();i++) {
      a.get(i).check();   
    }
}