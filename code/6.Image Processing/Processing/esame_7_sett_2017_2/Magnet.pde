class Magnet {
  float posX;
  float posY;
  color colore;
  float diametro;
  color cl_re_1;
  float bs_re_1;
  float h_re_1;
  color cl_re_2;
  float bs_re_2;
  float h_re_2;
  Magnet () {
    this.colore=color (128,128,128);
    this.diametro=30;
    this.cl_re_1=color(255,0,0);
    this.bs_re_1=5;
    this.h_re_1=30;
    this.cl_re_2=color(0,0,255);
    this.bs_re_2=30;
    this.h_re_2=5;
  }
  void display () {
    noStroke();
    fill(this.colore);
    ellipse (posX,posY,diametro,diametro);
    rectMode (CENTER);
    fill(this.cl_re_1);
    rect(posX,posY,bs_re_1,h_re_1);
    fill(this.cl_re_2);
    rect(posX,posY,bs_re_2,h_re_2);
  }
  void move () {
    posX=mouseX;
    posY=mouseY;
  }
  void run () {
    move();
    display();
  }
  float getX () {
    return posX;
  }
  float getY() {
    return posY;
  }
}