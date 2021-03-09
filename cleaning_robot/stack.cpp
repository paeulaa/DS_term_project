#include <iostream>
#include <fstream>
#include <climits>
#define infinity 2147483647

using namespace std;

int step = 0;
int energy = 0;
int battery = 0;
int c, r;
bool long_path = false;


struct node{
    int row;
    int col;
};


struct record_node{
    bool has_path;
    int energy;
};

node ans[1000000];

class stack_{
public:
    node capacity[1000];
    int t;
    stack_(){t = -1;};
    node top();
    void push(node a);
    void pop();
    bool empty();
    void print();

};
void stack_::print(){
    for(int i=0;i<=t;i++)
        cout<<"("<<capacity[i].row<<","<<capacity[i].col<<")";
    cout<<endl;
}
node stack_::top(){
    return capacity[t];
}

void stack_::push(node num){
    t++;
    capacity[t].col = num.col;
    capacity[t].row = num.row;
}

bool stack_::empty(){
    if(t == -1)
        return true;
    else
        return false;
}

void stack_::pop(){
    if(!empty()){
        t--;
    }
}

void storestack(stack_ s, int**map){
    stack_ copy;
    while(!s.empty()){
        ans[step] = s.top();
        map[s.top().row][s.top().col] = 2;
        step++;
        copy.push(s.top());
        s.pop();
    }
    copy.pop();
    while(!copy.empty()){
        ans[step] = copy.top();
        step++;
        copy.pop();
    }
    step--;
}
void print_record(int (*record)[1000]){
    for(int i=0;i<r;i++){
      for(int j=0;j<c;j++){
        cout<<record[i][j];
      }
      cout<<endl;
    }
    cout<<"--------------------------------------"<<endl;
}


bool path(int **map, struct record_node** my_record, node start, node end, stack_ s, int (*record)[1000])
    s.push(start);
    record[start.row][start.col] = 1;
    energy++;

    //cout<<start.row<<","<<start.col<<endl;
    //print_record(record);

    if(energy > battery/2){
        long_path = true;
        energy--;
        record[start.row][start.col] = 0;
        return false;
    }

    node tmp_r;
    tmp_r.col = start.col+1;
    tmp_r.row = start.row;
    node tmp_d;
    tmp_d.col = start.col;
    tmp_d.row = start.row+1;
    node tmp_l;
    tmp_l.col = start.col-1;
    tmp_l.row = start.row;
    node tmp_u;
    tmp_u.col = start.col;
    tmp_u.row = start.row-1;

    if(start.row == end.row && start.col == end.col){
        storestack(s,map);
        return true;
    }

    if(end.row>start.row){
        if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1 ){
            if(path(map, my_record, tmp_d,end,s,record))
                return true;
        }
        if(end.col>start.col){
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1){
                if(path(map, my_record, tmp_u,end,s,record))
                    return true;
            }


        }
        else{
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1){
                if(path(map, my_record, tmp_u,end,s,record))
                    return true;
            }
        }

    }
	else if(end.row<start.row){
        if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1 ){
            if(path(map, my_record, tmp_u,end,s,record))
                return true;
        }
        if(end.col>start.col){
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1){
                if(path(map, my_record, tmp_d,end,s,record))
                    return true;
            }


        }
        else{
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1){
                if(path(map, my_record, tmp_d,end,s,record))
                    return true;
            }
        }
    }
    else{
        if(end.col>start.col){
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1){
                if(path(map, my_record, tmp_d,end,s,record))
                    return true;
            }

            if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1){
                if(path(map, my_record, tmp_u,end,s,record))
                    return true;
            }
        }
        else{
            if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
                if(path(map, my_record, tmp_l,end,s,record))
                    return true;
            }
            if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
                if(path(map,my_record, tmp_r,end,s,record))
                    return true;
            }
            if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1){
                if(path(map, my_record, tmp_d,end,s,record))
                    return true;
            }

            if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1){
                if(path(map, my_record, tmp_u,end,s,record))
                    return true;
            }
        }
    }
	/*if(map[start.row][start.col+1] != 1 && record[start.row][start.col+1] != 1){
        if(path(map,my_record, tmp_r,end,s,record))
            return true;
    }
    if(map[start.row+1][start.col] != 1 && record[start.row+1][start.col] != 1 ){
        if(path(map, my_record, tmp_d,end,s,record))
            return true;
    }
    if(map[start.row][start.col-1] != 1 && record[start.row][start.col-1] != 1){
        if(path(map, my_record, tmp_l,end,s,record))
            return true;
    }
    if(map[start.row-1][start.col] != 1 && record[start.row-1][start.col] != 1){
        if(path(map, my_record, tmp_u,end,s,record))
            return true;
    }*/
    energy--;
    if(long_path)
        record[start.row][start.col]=0;
    return false;

}

bool check_step(int **answer){
  for(int i = 1; i <= step; i++){
    int one_per_step = (ans[i].row-ans[i-1].row)+(ans[i].col-ans[i-1].col);
    if(one_per_step!=1 && one_per_step!=-1){
      return false;
    }
  }
  return true;
}


bool check_ans(int**map, int** answer){
  if(!check_step(answer))
    return false;
  for(int i = 0; i <= step; i++){
    if(map[ans[i].row][ans[i].col]!=1)
      answer[ans[i].row][ans[i].col]=1;
  }

  for(int i=0;i<r;i++){
    for(int j=0;j<c;j++){
      if(answer[i][j]!=1){
        return false;
      }
    }
  }
  return true;
}
int main(){
    node a;
    node R;
    char **bg;
    int **map;
    int **answer;
    struct record_node **my_record;

    fstream file;
    file.open("case",ios::in);
    if(!file){
        cout<<"open file failed!"<<endl;
    }
    file >> r >> c >> battery;

    bg = new char*[r];
    answer = new int*[r];
    map = new int*[r];
    my_record = new struct record_node*[r];
    for(int i=0;i<r;i++){
        bg[i] = new char[c];
        answer[i] = new int[c];
        map[i] = new int[c];
        my_record[i] = new struct record_node[c];
    }


    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            file >> bg[i][j];
            my_record[i][j].has_path = false;
            my_record[i][j].energy = infinity;
            if(bg[i][j] == '1'){
                map[i][j] = 1;
                answer[i][j]=1;
            }
            if(bg[i][j] == '0')
                map[i][j] = 0;
            if(bg[i][j] == 'R'){
                R.row = i;
                R.col = j;
            }
        }
    }
    file.close();

    //a.row = 1; a.col = 1;
    //R.row = 6; R.col = 4;
    stack_ s_;


    bool has_path = false;
    bool no_path =false;
    for(int i = 0; i < r; i++){
        if(no_path)
          break;
        for(int j = 0; j < c; j++){
            if(map[i][j] == 0){
                cout<<i<<","<<j<<endl;
                energy = 0;
                a.row = i; a.col = j;
                int record[1000][1000] = {0};
                long_path = false;
                has_path = path(map,my_record,a, R, s_, record) ;
                if(!has_path){
                  cout<<"error : "<<i<<","<<j<<endl;
                  no_path=true;
                  break;
                }
            }
        }
    }
	/*for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
             cout << map[i][j];
        }cout << endl;
    }cout << endl;*/
    //cout << "step: " << step << endl;
    if(!no_path){
      for(int i = 0; i < step; i++)
          cout << ans[i].row << " " << ans[i].col << endl;
      cout <<  R.row << " " << R.col << endl;
      if(check_ans(map,answer))
        cout<<"Correct!"<<endl;
      else
        cout<<"Wrong"<<endl;
    }
    else
      cout<<"Illegal map !"<<endl;
    return 0;
}
