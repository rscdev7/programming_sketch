Magnet y;
ArrayList<Iron> a;
int verso;
void setup() {
  size (500,500);
  background (255);
  y=new Magnet();
  a=new ArrayList<Iron> ();
  verso=1;
}

void draw () {
  background (255);
  y.run();
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      a.get(i).run(y,verso);
    }
  }
}

void mousePressed () {
  verso=1;
}
void mouseReleased () {
  verso=-1;
}

void keyPressed () {
   if (key=='R'||key=='r') {
     setup();  
   }
   if (key=='N'||key=='n') {
       for (int i=0;i<10;i++) {
         a.add(new Iron (int(random (2,16)),random (0,501),random(0,501)));
       }
   }
}