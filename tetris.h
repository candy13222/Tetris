struct Square{
    int dx;
    int dy;
};

struct Tetromino{
    Square s[4];
};

Tetromino t[7] = {
                    -1,0, 0,0, 1,0, 2,0 ,   //0
                    -1,-1, -1,0, 0,0, 1,0 , //1
                    -1,0, 0,0, 1,0, 1,-1 ,  //2
                    0,0, 1,0, 0,1, 1,1 ,    //3
                    -1,0, 0,0, 0,-1, 1,-1 , //4 
                    -1,0, 0,0, 0,-1, 1,0 ,  //5
                    -1,-1, 0,-1, 0,0, 1,0   //6
                 }; //(x,y)

String num[7]={
    String("0"), String("1"), String("2"),
    String("3"), String("4"), String("5"),
    String("6")
};

int nHeight = nBottomBorder - nTopBorder - 1;
int nWidth = nRightBorder * 2 - 2 - nLeftBorder * 2 - 2;
bool occupied[nBottomBorder - nTopBorder - 1 + 100][nRightBorder - nLeftBorder - 1 + 100] = {false};
int occupied_color[nBottomBorder - nTopBorder - 1 + 100][nRightBorder - nLeftBorder - 1 + 100] = {0};
int get_score = 0;


class CTetromino{
    public:
        CTetromino(unsigned short id, unsigned short x, unsigned short y = 0){
            String scor("Score : ");
            scor.show(2, nLeftBorder * 2 - 15);
            type_id = id;
            if(x % 2 == 1)
                pos_x = x + 31;
            else if (x % 2 == 0)
                pos_x = x + 30;
            pos_y = y;
        }


        bool true_false(int k){
            bool detect[4];
            for(int i = 0; i < 4; i++){
                if(occupied [3 + pos_y + t[type_id].s[i].dy][pos_x + k + t[type_id].s[i].dx * 2] == true)
                    return true;
            } 
            return false;
        }

        bool limit_move(int limit, int k){
            for(int i = 0; i < 4; i++){
                if(pos_x + t[type_id].s[i].dx * 2 == limit * 2 + k)
                    return true;
            }
            return false;
        }

        void Draw(void){
            int i;
            String sqar("  ");
            for(i = 0; i < 4; i++)
                sqar.show(2 + pos_y + t[type_id].s[i].dy, pos_x + t[type_id].s[i].dx * 2, type_id + 1);
            num[type_id].show(2 + pos_y + t[type_id].s[0].dy, pos_x + t[type_id].s[0].dx * 2, type_id + 1);
        }

        void Erase(void){
            int i;
            String sqar("  ");
            for(i = 0; i < 4; i++)
                sqar.show(2 + pos_y + t[type_id].s[i].dy, pos_x + t[type_id].s[i].dx * 2, 0);
        }

        int detect_confliction(void){
            for(int i = 0; i < 4; i++){
                if(occupied [2][pos_x + t[type_id].s[i].dx * 2] == true)
                    return 1;
            }
            return 0;
        }

        void update_occupy(){
            int i, j, detect, times = 0;
            bool k = 0;
            for(j = 2; j <= nBottomBorder - 1; j++){
                detect = 0;
                for(i = nLeftBorder * 2 + 2; i <= nRightBorder * 2 - 2; i++){
                    if(occupied[j][i] == true)
                        detect++;
                    else 
                        break;
                }

                if(detect == nRightBorder * 2 - nLeftBorder * 2 - 3){
                    times++;
                    check_horizontal(j);
                    fall_down(j);
                    k = 1;
                }
            }

            if(times == 1){
                get_score += 20;
                get_point();
            }
            else if(times == 2){
                get_score += 80;
                get_point();
            }
            else if(times == 3){
                get_score += 180;
                get_point();
            }

            if(k == 0){
                for(i = 0; i < 4; i++){
                    occupied [2 + pos_y + t[type_id].s[i].dy][pos_x  + t[type_id].s[i].dx * 2] = true;
                    occupied [2 + pos_y + t[type_id].s[i].dy][pos_x + 1 + t[type_id].s[i].dx * 2] = true;
                    occupied_color [2 + pos_y + t[type_id].s[i].dy][pos_x + t[type_id].s[i].dx * 2] = type_id + 1;
                    occupied_color [2 + pos_y + t[type_id].s[i].dy][pos_x + 1 + t[type_id].s[i].dx * 2] = type_id + 1;
                }
            }
        }

        void fall_down(int col){
            String sp("  ");
            int i, k, flag;
            for(k = col - 1; k >= 2; k--){
                flag = 0;
                for (i = nLeftBorder * 2 + 2 ; i <= nRightBorder * 2 - 1; i += 2){
                    if(occupied[k][i] == true){
                        flag = 1;
                        sp.show(k , i, 0);
                        sp.show(k + 1, i , occupied_color[k][i]);
                    }
                }
                for (i = nLeftBorder * 2 + 2 ; i <= nRightBorder * 2 ; i++){
                    if(flag == 1){
                        occupied_color[k + 1][i] = occupied_color[k][i];
                        occupied_color[k][i] = 0;
                        occupied[k + 1][i] = occupied[k][i];
                        occupied[k][i] = false;
                    }
                }
                
            }
        }

        void check_horizontal(int j){
            String blink("                          ");
            blink.show(j, nLeftBorder * 2 + 2, 3);
            myScreen.redraw();
            Sleep(150);
            blink.show(j, nLeftBorder * 2 + 2, 0); 
        }

        void get_point(void){
            int get_num = get_score / 2;
            int i = 0, j;
            char c[100] = {0};
            while(1){
                if(get_num / 10 == 0){
                    c[i] = get_num % 10 + '0';
                    break;
                }
                c[i] = get_num % 10 + '0';
                get_num /= 10;
                i++;
            }
            for(j = 0; j <= i; j++){
                String get(c[j], 2, nLeftBorder * 2 - 7 + i - j);
                get.show();

            }

        }

        int Move(int dire){
            Draw();
            int a;
            switch(dire){
                case 0:
                    Erase();
                    if((pos_y == nBottomBorder - 3 && type_id != 0)||(pos_y == nBottomBorder - 4 && type_id == 0 ))
                        return 0;
                        
                    else if(2 + pos_y + t[type_id].s[0].dy == nBottomBorder - 1
                          ||2 + pos_y + t[type_id].s[1].dy == nBottomBorder - 1
                          ||2 + pos_y + t[type_id].s[2].dy == nBottomBorder - 1
                          ||2 + pos_y + t[type_id].s[3].dy == nBottomBorder - 1)
                            return 0;

                    else if(true_false(0) == true||true_false(1) == true||true_false(-1) == true
                          ||true_false(2) == true)
                          return 0;

                    else{
                        for(int i = 0; i < 4; i++){
                            a = t[type_id].s[i].dy;
                            t[type_id].s[i].dy = - t[type_id].s[i].dx ;
                            t[type_id].s[i].dx = a ;
                            while(pos_x + t[type_id].s[i].dx * 2 < nLeftBorder * 2 + 2){
                                pos_x++;
                            }
                            while(pos_x + t[type_id].s[i].dx * 2 > nRightBorder * 2 - 2){
                                pos_x--;
                            }
                        }
                        Draw();
                        return 1;
                    }
                        
                case 1:
                    Erase();
                    if(2 + pos_y + t[type_id].s[0].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[1].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[2].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[3].dy == nBottomBorder - 1){
                        Draw();
                        update_occupy();
                        get_score++;
                        get_point();
                        return 0;
                    }

                    else if(true_false(0) == true || true_false(1) == true){
                        Draw();
                        update_occupy();
                        get_score++;
                        get_point();
                        return 0;
                    }

                    else{
                        pos_y++;
                        Draw();
                        return 1;
                    }

                case 2:
                    Erase(); 
                    if(2 + pos_y + t[type_id].s[0].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[1].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[2].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[3].dy == nBottomBorder - 1)
                        return 0;
                    else if(limit_move(nLeftBorder, 2)|| true_false(0) == true || true_false(-1) == true )
                        return 0;

                    else{
                        pos_x-=2;
                        Draw();
                        return 1;
                    }

                case 3:
                    Erase();
                    if(2 + pos_y + t[type_id].s[0].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[1].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[2].dy == nBottomBorder - 1
                      ||2 + pos_y + t[type_id].s[3].dy == nBottomBorder - 1)
                        return 0;

                    else if(limit_move(nRightBorder, -2) || true_false(1) == true|| true_false(2) == true)
                        return 0;

                    else{
                        pos_x+=2;
                        Draw();
                        return 1;
                    }
            }
            return 0;
        }
    
    private: 
        unsigned short type_id;
        unsigned short pos_x;
        unsigned short pos_y;
};