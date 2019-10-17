#include <iostream>
#include <fstream>

using namespace std;

#define BG_WIDTH 100
#define BG_HEIGHT 100
int background[BG_HEIGHT][BG_WIDTH] = { 0 };
#define B_WIDTH 4
#define B_HEIGHT 4


class block{
public:
    int bloc[B_WIDTH][B_HEIGHT];
    int row;
    block();
    void shape_T(int n);
    void shape_L(int n);
    void shape_J(int n);
    void shape_S(int n);
    void shape_Z(int n);
    void shape_I(int n);
    void shape_O();
};

class start{
public: 
    block cur_b;
    int h_;
    int w_;
    int init;
    start(int h, int w);
    void print_board();
    void print_block();
    void createnewbloc(char letter, int num, int col);
    void clearblock();
};

block::block(){
    row = -1;
    for(int i = 0 ; i < B_HEIGHT; i++){
        for(int j = 0; j < B_WIDTH; j++){
             bloc[i][j] = 0;
        }
    }
}

void block:: shape_T(int n){
    if( n == 1 ) bloc[2][0] = bloc[2][1] = bloc[2][2] = bloc[3][1] = 1;
    if( n == 2 ) bloc[1][1] = bloc[2][0] = bloc[2][1] = bloc[3][1] = 1;
    if( n == 3 ) bloc[2][1] = bloc[3][0] = bloc[3][1] = bloc[3][2] = 1;
    if( n == 4 ) bloc[1][0] = bloc[2][0] = bloc[2][1] = bloc[3][0] = 1;
}

void block:: shape_L(int n){
    if( n == 1 ) bloc[1][0] = bloc[2][0] = bloc[3][0] = bloc[3][1] = 1;
    if( n == 2 ) bloc[2][0] = bloc[2][1] = bloc[2][2] = bloc[3][0] = 1;
    if( n == 3 ) bloc[1][0] = bloc[1][1] = bloc[2][1] = bloc[3][1] = 1;
    if( n == 4 ) bloc[2][2] = bloc[3][0] = bloc[3][1] = bloc[3][2] = 1;
}

void block:: shape_J(int n){
    if( n == 1 ) bloc[1][1] = bloc[2][1] = bloc[3][0] = bloc[3][1] = 1;
    if( n == 2 ) bloc[2][0] = bloc[3][0] = bloc[3][1] = bloc[3][2] = 1;
    if( n == 3 ) bloc[1][0] = bloc[1][1] = bloc[2][0] = bloc[3][0] = 1;
    if( n == 4 ) bloc[2][0] = bloc[2][1] = bloc[2][2] = bloc[3][2] = 1;
}

void block:: shape_S(int n){
    if( n == 1 ) bloc[2][1] = bloc[2][2] = bloc[3][0] = bloc[3][1] = 1;
    if( n == 2 ) bloc[1][0] = bloc[2][0] = bloc[2][1] = bloc[3][1] = 1;
}

void block:: shape_Z(int n){
    if( n == 1 ) bloc[2][0] = bloc[2][1] = bloc[3][1] = bloc[3][2] = 1;
    if( n == 2 ) bloc[1][1] = bloc[2][0] = bloc[2][1] = bloc[3][0] = 1;
}

void block:: shape_I(int n){
    if( n == 1 ) bloc[0][0] = bloc[1][0] = bloc[2][0] = bloc[3][0] = 1;
    if( n == 2 ) bloc[3][0] = bloc[3][1] = bloc[3][2] = bloc[3][3] = 1;
}

void block:: shape_O(){
    bloc[2][0] = bloc[2][1] = bloc[3][0] = bloc[3][1] = 1;
}

start:: start(int h, int w){
    h_ = h + 3;
    w_ = w + 2;
}

void start:: print_board(){
    for(int i = 3; i < h_; i++){
        for(int  j = 1; j < w_ -1; j++)
            cout << background[i][j];
        cout << endl;
    }
}

void start:: print_block(){
    for(int i = 0; i < 4; i++){
        for(int  j = 0; j < 4 ; j++)
            cout << cur_b.bloc[i][j];
        cout << endl;
    }
}

void start:: createnewbloc(char letter, int num, int col){
    init = col;
    if( letter ==  'T')  cur_b.shape_T(num);
    if( letter ==  'L')  cur_b.shape_L(num);
    if( letter ==  'J')  cur_b.shape_J(num);
    if( letter ==  'S')  cur_b.shape_S(num);
    if( letter ==  'Z')  cur_b.shape_Z(num);
    if( letter ==  'I')  cur_b.shape_I(num);
    if( letter ==  'O')  cur_b.shape_O();
}

void start:: clearblock(){
    cur_b.row = -1;
    for(int i = 0; i < B_HEIGHT; i++){
            for(int j = 0; j < B_WIDTH; j++){
                    cur_b.bloc[i][j] = 0;
            }
    }
}

void update_screen(start* a, int clear_row){
     for(int i = clear_row; i >= 0; i--){
             for(int j = 0; j < a->w_; j++){
                      if(i)
                        background[i][j] = background[i-1][j];
                      else
                        background[i][j] = 0;
             }
     }
}

void clear_line(start* a){
     for(int i = a->h_; i >= 3; i--){
             int clear = 1;
             for(int j = 1; j < a->w_ - 1; j++){
                     if(background[i][j] == 0){
                           clear = 0;
                           break;
                     }
             }
             if(clear){
                update_screen(a, i);
                i++;
             }
     }
}

bool can_down(start* a){
    if(a->cur_b.row == a->h_-1) return false;
    else{
        for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                  if(a->cur_b.bloc[i][j] == 1 && i == 3){
                       int next_row = a->cur_b.row-(3-i)+1;
                        int col = a->init + j;
                        //cout << "::" << next_row << "," << col <<":"<<background[next_row][col]<<" ";
                        //cout <<" init:" << a->init << endl;
                        if(next_row>=0){  // check if i row of block move 1 down will appear in screen
                                if(background[next_row][col]){
                                        return false;
                                }
                        }
                  }
                  else if(a->cur_b.bloc[i][j] == 1 && a->cur_b.bloc[i+1][j] != 1){
                        int next_row = a->cur_b.row-(3-i)+1;
                        int col = a->init + j;
                        //cout << "::" << next_row << "," << col <<":"<<background[next_row][col]<<" ";
                        //cout <<" init:" << a->init << endl;
                        if(next_row>=0){  // check if i row of block move 1 down will appear in screen
                                if(background[next_row][col]){
                                        return false;
                                }
                        }
                  }
                }
        }
        return true;
    }
}

void Move(start* a){
    for(int i=3;i>=0;i--){
        for(int j=3;j>=0;j--){
            if(a->cur_b.bloc[i][j]==1){
                   int next_row = a->cur_b.row-(3-i)+1;
                   int col = a->init + j;
                   if(next_row>=0){  
                        if(background[next_row][col]){
                           cout << "collision wrong!" << endl;
                        }
                        background[next_row][col] = 1;
                        background[next_row-1][col] = 0;
                        //clear_line(a);
                   }
                
            }
        }
        //clear_line(a);
    }
    a->cur_b.row++;
}

bool check_gameover(start* a){
     for(int j = 1; j < a->w_; j++)
          if(background[2][j] == 1 )//|| background[i][a->w_-1] == 1)
                   return true;
      return false;             
}


int main(){
    fstream file;
    file.open("test1",ios::in);
    if(!file){
        cout<<"open file failed!"<<endl;
    }
    else{
        int size1, size2;
        file >> size1 >> size2;
        start* a = new start(size1, size2);

        while(1){          
                char ch = '0';
                int n, c;
                file >> ch;
                if(ch == 'E')
                      break;
                if(ch == 'O'){
                      file >> c;
                      a->createnewbloc(ch, 0, c);
                }
                else{
                      file >> n >> c;
                      a->createnewbloc(ch, n, c);   
                }
                while(can_down(a)){
                        Move(a);
                        //clear_line(a);
                }
                a->clearblock();
                clear_line(a);
                if(check_gameover(a)){
                   break;
                } 
                
               int x;
               //a->print_board();
               //cin >> x;
        }
        file.close();
        a->print_board();
  }

    return 0;
}
