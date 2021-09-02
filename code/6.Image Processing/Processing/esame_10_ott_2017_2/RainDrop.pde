class RainDrop {
   float posX;
   float posY;
   int speed;
   float dim;
   color d;
   RainDrop (float posX,float posY,int speed,float dim) {
     d=color (0,252,253);
     this.posX=posX;
     this.dim=dim;
     this.posY=posY;
     this.speed=speed;
   }
   void display () {
     stroke (this.d);
     line (posX,posY,posX,posY+dim);
     posY=posY+speed;
   }
   void run () {
     display ();
   }
   void setDim (float size) {
     this.dim=size;  
   }
   void setSpeed (float sp) {
     this.speed=(int)sp;  
   }
}