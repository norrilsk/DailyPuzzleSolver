#include<iostream>
#include<vector>
#include<array>
#include<cstdint>
#include<queue>
#include<memory>
#include<unordered_map>
#define GS 7
#define GSGS GS*GS
enum direction { L = -1, R = 1, U = -GS, D = GS, X = 0};
/*0b00000011
    00000011
    00000001
    00000001
    00000001
    00000001
    00011111
    11111111 */
const uint64_t base_grid = 0b0000001100000011000000010000000100000001000000010001111111111111;

class Form {
public:
 int num_states(){
    return states.size();
 }

uint64_t state = 0;
uint64_t start = 0;
std::vector<uint64_t> states;
};

class Rect: public Form{
public:
    Rect(){
        states.emplace_back(0b1100000011000000110000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000011100000000000000000000000000000000000000000000000000000);
    }
};


class RectP: public Form{
public:
    RectP(){
        states.emplace_back(0b1000000110000001100000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000001100000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000011000000100000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000011100000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000111000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000011000000010000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000011000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000011000000110000000000000000000000000000000000000000000000);
    }
};
class Chair: public Form{
public:
    Chair(){
        states.emplace_back(0b1000000010000000110000000100000000000000000000000000000000000000);
        states.emplace_back(0b1100001110000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000011000000010000000100000000000000000000000000000000000000);
        states.emplace_back(0b1110000110000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000000110000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000110000001000000010000000000000000000000000000000000000000);
        states.emplace_back(0b1100000001110000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000010000001100000010000000000000000000000000000000000000000);
    }
};

class Lform: public Form{
public:
    Lform(){
        states.emplace_back(0b1000000010000000100000001100000000000000000000000000000000000000);
        states.emplace_back(0b1000011110000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000001000000010000000100000000000000000000000000000000000000);
        states.emplace_back(0b1111000010000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1111000000010000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000010000000100000001000000000000000000000000000000000000000);
        states.emplace_back(0b1000000011110000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000010000000100000011000000000000000000000000000000000000000);
    }
};

class Pistol: public Form{
public:
    Pistol(){
        states.emplace_back(0b1000000011000000100000001000000000000000000000000000000000000000);
        states.emplace_back(0b1000000111100000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000010000001100000001000000000000000000000000000000000000000);
        states.emplace_back(0b1111000000100000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1111000001000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000010000000110000001000000000000000000000000000000000000000);
        states.emplace_back(0b1000001111000000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000110000000100000001000000000000000000000000000000000000000);
    }
};

class Cap: public Form{
public:
    Cap(){
        states.emplace_back(0b1100000010000000110000000000000000000000000000000000000000000000);
        states.emplace_back(0b1010000011100000000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000001000000110000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000010100000000000000000000000000000000000000000000000000000);
    }
};

class ZigZag: public Form{
public:
    ZigZag(){
        states.emplace_back(0b1100000001000000011000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000001110000010000000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000011100000001000000000000000000000000000000000000000000000);
        states.emplace_back(0b1100000010000001100000000000000000000000000000000000000000000000);
    }
};

class Corner: public Form{
public:
    Corner(){
        states.emplace_back(0b1000000010000000111000000000000000000000000000000000000000000000);
        states.emplace_back(0b1000000010000011100000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000000100000001000000000000000000000000000000000000000000000);
        states.emplace_back(0b1110000010000000100000000000000000000000000000000000000000000000);
    }
};

class Solver {
    uint64_t grid  = base_grid;
    std::unordered_map<std::shared_ptr<Form>,int> forms;
    int cur_pos=0;
    public:
    void set_date(int month, int day){
        uint64_t jan = 1ull<<63;
        uint64_t  grid_month = jan >> (month-1);
        if (month > 6) 
            grid_month = grid_month >> 2;
        uint64_t frst_day = (1ull << 63) >> 16;
        uint64_t  grid_day =  (frst_day >> (day-1)) >> day/8;
        grid = grid | grid_day | grid_month;
    }
    Solver(){
        forms[std::make_shared<Rect>()] = 0;
        forms[std::make_shared<RectP>()] = 0;
        forms[std::make_shared<Chair>()] = 0;
        forms[std::make_shared<Lform>()] = 0;
        forms[std::make_shared<Pistol>()] = 0;
        forms[std::make_shared<Cap>()] = 0;
        forms[std::make_shared<ZigZag>()] = 0;
        forms[std::make_shared<Corner>()] = 0;
    }
    uint64_t solve(){
        // place all form
        bool ret_val = true;
        for (auto& [form, is_used] : forms) {
            if (is_used) continue;
            ret_val = false;
            // find next_free_state
            while (grid & (1ull << (63 - cur_pos))) cur_pos+=1;
            // plase state
            //bool placed = false;
            for (auto & state: form->states){
                //shift to curent position
                uint64_t shifted_state = state >> cur_pos;
                // check that we are not overshifted it
                if (shifted_state << cur_pos != state) continue;
                //check that state can be placed
                if ((shifted_state & grid )!= 0) continue;
                //place it
                uint64_t new_grid = grid | shifted_state;
                // call solver 
                Solver s(*this);
                s.forms[form] = 1;
                s.grid = new_grid;
                if (s.solve()){
                    form->state = shifted_state;
                    return true;
                }
            }
        }
        return ret_val;
    }
    void present_solution()
    {
        std::array<int,64> grid ={0};
        int idx = 1;
        for (auto& [form, is_used] : forms) {
            uint64_t state = form->state;
            for (int i =0; i < 64; i++){
                int res = (state & (1ull << (63 -i))) == 0? 0: 1;
                grid[i] += idx * res; 
            }
            idx++;
        }
        std::cout<<"\n";
        for (int j =0; j< 8; j++) {
            for (int i=0; i <8; i++){
                std::cout<<grid[i+j*8]<<" ";
            }
            std::cout<<"\n";
        }
    }
};


int main()
{
    Solver s;
    s.set_date(9,19);
    std::cout<<s.solve();
    s.present_solution();
    return 0;
}
