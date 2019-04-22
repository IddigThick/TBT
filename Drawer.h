#ifndef DRAWER_H
#define DRAWER_H


class Drawer {
  public:
    Drawer();
    ~Drawer() {}
  private:
    void draw_status_bar(int y, int x,int minimum, int maximum);
    void player_status();
    void borders();
    void update();
    void exit();
    void npcs();
    void items();
    int holder;
};

#endif // DRAWER_H
